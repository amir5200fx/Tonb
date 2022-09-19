#include <Geo3d_ApprxSurfPatch.hxx>

#include <GeoMesh2d_Data.hxx>
#include <Geo3d_ApprxSurfPatch_Info.hxx>
#include <Geo3d_ApprxSurfPatch_FunMode.hxx>
#include <Geo2d_ApprxSpace.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <algorithm>

#include <Geom_Surface.hxx>

Standard_Boolean 
tnbLib::Geo3d_ApprxSurfPatch::QuadTreeObject::doSubdivide
(
	const Entity2d_Box & theRegion,
	const QuadTreeObject * theObject
)
{
	Debug_Null_Pointer(theObject);
	return theObject->Function().DoSubdivide(theRegion, theObject->Geometry(), theObject->Tolerance());
}

const std::shared_ptr<std::vector<tnbLib::Pnt2d>>& 
tnbLib::Geo3d_ApprxSurfPatch::Approximated() const
{
	CheckDone((*this));
	return theCoords_;
}

namespace tnbLib
{
	auto RetrieveCorners(const Entity2d_Box& b)
	{
		auto p0 = b.P0();
		auto p1 = b.Corner(Box2d_PickAlgorithm_SE);
		auto p2 = b.P1();
		auto p3 = b.Corner(Box2d_PickAlgorithm_NW);
		auto t = std::make_tuple(std::move(p0), std::move(p1), std::move(p2), std::move(p3));
		return std::move(t);
	}

	void InsertToEngine
	(
		Geo_AdTree<Geo3d_ApprxSurfPatch::Node*>& engine,
		Pnt2d&& theCoord,
		const Standard_Real theTol
	)
	{
		auto b = Entity2d_Box::Box(theCoord, theTol);
		std::vector<Geo3d_ApprxSurfPatch::Node*> items;
		engine.GeometrySearch(b, items);
		if (items.empty())
		{
			auto node = new Geo3d_ApprxSurfPatch::Node(std::move(theCoord));
			engine.InsertToGeometry(node);
		}
		else
		{
			Standard_Real minDis = RealLast();
			for (const auto& x : items)
			{
				Debug_Null_Pointer(x);
				auto dis = x->Coord().Distance(theCoord);
				if (dis < minDis)
				{
					minDis = dis;
				}
			}
			if (minDis < theTol)
			{
				// do nothing [9/5/2022 Amir]
			}
			else
			{
				auto node = new Geo3d_ApprxSurfPatch::Node(std::move(theCoord));
				engine.InsertToGeometry(node);
			}
		}
	}

	auto RetrieveCoords
	(
		const std::vector<Entity2d_Box>& theBoxes, 
		const Entity2d_Box& theDomain,
		const Standard_Real theTol
	)
	{
		Geo_AdTree<Geo3d_ApprxSurfPatch::Node*> tree;
		tree.SetGeometryRegion(theDomain);
		tree.SetGeometryCoordFunc(&Geo3d_ApprxSurfPatch::Node::GetCoord);

		for (const auto& x : theBoxes)
		{
			auto[p0, p1, p2, p3] = RetrieveCorners(x);
			std::vector<Geo3d_ApprxSurfPatch::Node*> items;

			InsertToEngine(tree, std::move(p0), theTol);
			InsertToEngine(tree, std::move(p1), theTol);
			InsertToEngine(tree, std::move(p2), theTol);
			InsertToEngine(tree, std::move(p3), theTol);
		}

		std::vector<Geo3d_ApprxSurfPatch::Node*> nodes;
		tree.RetrieveFromGeometryTo(nodes);
		std::vector<Pnt2d> coords;
		coords.reserve(nodes.size());
		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			coords.push_back(x->Coord());
		}
		return std::move(coords);
	}

	void SortCoords(std::vector<Pnt2d>& theCoords, const Pnt2d& theP0)
	{
		std::vector<std::pair<Pnt2d, Standard_Real>> norms;
		norms.reserve(theCoords.size());
		for (auto& x : theCoords)
		{
			auto d = theP0.Distance(x);
			auto t = std::make_pair(std::move(x), d);
			norms.push_back(std::move(t));
		}
		std::sort
		(
			norms.begin(), norms.end(), 
			[]
		(
			const std::pair<Pnt2d, Standard_Real>& p0, 
			const std::pair<Pnt2d, Standard_Real>& p1
			) {return p0.second < p1.second; }
		);
		theCoords.clear();
		theCoords.reserve(norms.size());
		for (const auto& x : norms)
		{
			theCoords.push_back(std::move(x.first));
		}
	}

	void RetrieveDomainCoords(std::vector<Pnt2d>& theCoords, const GeoMesh2d_Data& theBack)
	{
		auto firstElmnt = theBack.FirstElement();
		std::vector<Pnt2d> pnts;
		pnts.reserve(theCoords.size());
		for (auto& x : theCoords)
		{
			if (auto elm = theBack.TriangleLocation(firstElmnt, x))
			{
				pnts.push_back(std::move(x));
				firstElmnt = elm;
			}
		}
		theCoords.clear();
		theCoords = std::move(pnts);
	}
}

void tnbLib::Geo3d_ApprxSurfPatch::Perform()
{
	static const Standard_Real mergeTol = 1.0E-4;
	if (NOT Patch())
	{
		FatalErrorIn(FunctionSIG)
			<< "no surface patch has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< "no parametric domain has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Backgound())
	{
		FatalErrorIn(FunctionSIG)
			<< "no background mesh has been found." << endl
			<< abort(FatalError);
	}

	if (NOT AlgInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found." << endl
			<< abort(FatalError);
	}

	std::vector<Pnt2d> coords;
	{
		std::vector<Entity2d_Box> boxes;
		{
			QuadTreeObject approxObj(*Function(), *Patch(), AlgInfo()->Tolerance());

			Geo2d_ApprxSpace<QuadTreeObject> approx;
			approx.SetDomain(*Domain());
			approx.SetObject(&approxObj);
			approx.SetSubdivider(&QuadTreeObject::doSubdivide);

			approx.SetMinLevel(AlgInfo()->MinSubdivide());
			approx.SetMaxLevel(AlgInfo()->MaxSubdivie());
			approx.SetMaxUnbalancingLevel(AlgInfo()->MaxUnbalancing());

			approx.Init();
			approx.Perform();

			approx.RetrieveBoxesTo(boxes);
		}
		coords = RetrieveCoords(boxes, *Domain(), 0.02*mergeTol);
	}
	SortCoords(coords, Domain()->P0());

	RetrieveDomainCoords(coords, *Backgound());

	theCoords_ = std::make_shared<std::vector<Pnt2d>>(std::move(coords));
	Change_IsDone() = Standard_True;
}