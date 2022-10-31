#include <Mesh3d_UnionSizeMap.hxx>

#include <Geo3d_PatchCloud.hxx>
#include <GeoMesh3d_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <Mesh3d_Node.hxx>
#include <Cad_TModel.hxx>
#include <Cad_Tools.hxx>
#include <TModel_Surface.hxx>
#include <Cad_GeomSurface.hxx>
#include <Geo3d_BalPrTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo3d_DelTri_Fade3d.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Poly_Triangulation.hxx>

unsigned short tnbLib::Mesh3d_UnionSizeMap::verbose(0);
const Standard_Integer tnbLib::Mesh3d_UnionSizeMap::DEFAULT_MAX_UNBALANCING(2);
const Standard_Real tnbLib::Mesh3d_UnionSizeMap::DEFAULT_TOELRANCE(1.0E-6);

Standard_Real
tnbLib::Mesh3d_UnionSizeMap::ElementSize
(
	const Pnt3d & theCoord
) const
{
	Standard_Real minSize = RealLast();
	for (const auto& x : Backgrounds())
	{
		Debug_Null_Pointer(x);
		auto size = x->InterpolateAt(theCoord);
		if (size < minSize)
		{
			minSize = size;
		}
	}
	return minSize;
}

void tnbLib::Mesh3d_UnionSizeMap::UpdateSources
(
	const std::shared_ptr<GeoMesh3d_Background>& theMesh
) const
{
	Debug_Null_Pointer(theMesh);
	Debug_Null_Pointer(theMesh->Mesh());

	std::vector<std::shared_ptr<Mesh3d_Node>> nodes;
	theMesh->Mesh()->RetrieveNodesTo(nodes);

	auto& sources = theMesh->Sources();
	sources.resize(nodes.size());
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x);
		const auto& pt = x->Coord();
		auto h = ElementSize(pt);
		Debug_If_Condition_Message(h <= gp::Resolution(), "invalid element size has been detected!");
		sources.at(Index_Of(x->Index())) = h;
	}
}

std::vector<tnbLib::Pnt3d> 
tnbLib::Mesh3d_UnionSizeMap::RetrieveCoords
(
	const Cad_TModel & theModel,
	const Geo3d_PatchCloud& theCloud
)
{
	auto faces = theModel.RetrieveFaces();
	std::vector<Pnt3d> coords;
	for (const auto& x : faces)
	{
		Debug_Null_Pointer(x);
		if (NOT x->GeomSurface())
		{
			FatalErrorIn(FunctionSIG)
				<< "the face has no geometry!" << endl
				<< abort(FatalError);
		}
		const auto& geometry = x->GeomSurface();

		auto poly = x->RetrieveTriangulation();
		auto tri = Cad_Tools::ParaTriangulation(*poly);
		auto samples = theCloud.CalcCloud(*tri);

		for (const auto& pm : samples)
		{
			auto p = geometry->Value(pm);
			coords.push_back(std::move(p));
		}
	}
	return std::move(coords);
}

std::vector<tnbLib::Pnt3d> 
tnbLib::Mesh3d_UnionSizeMap::RetrieveCoords
(
	const std::vector<std::shared_ptr<Cad_TModel>>& theModels,
	const Geo3d_PatchCloud& theCloud
)
{
	std::vector<Pnt3d> coords;
	for (const auto& x : theModels)
	{
		Debug_Null_Pointer(x);
		auto pts = RetrieveCoords(*x, theCloud);
		for (auto& p : pts)
		{
			coords.push_back(std::move(p));
		}
	}
	return std::move(coords);
}

namespace tnbLib
{

	namespace unionTools
	{

		void InsertToEngine(Pnt3d&& theCoord, const Standard_Real theTol, Geo3d_BalPrTree<std::shared_ptr<Pnt3d>>& engine)
		{
			auto b = Geo_BoxTools::GetBox<Pnt3d>(theCoord, theTol);

			std::vector<std::shared_ptr<Pnt3d>> items;
			engine.GeometrySearch(b, items);
			if (items.empty())
			{
				auto node = std::make_shared<Pnt3d>(std::move(theCoord));
				Debug_Null_Pointer(node);
				engine.InsertToGeometry(node);
			}
			else
			{
				Standard_Real minDis = RealLast();
				for (const auto& i : items)
				{
					auto dis = i->Distance(theCoord);
					if (dis < minDis)
					{
						minDis = dis;
					}
				}
				if (minDis > theTol)
				{
					auto node = std::make_shared<Pnt3d>(std::move(theCoord));
					Debug_Null_Pointer(node);
					engine.InsertToGeometry(node);
				}
				else
				{
					// do nothing [8/25/2022 Amir]
				}
			}
		}

		auto RetrieveNodes(const Geo3d_BalPrTree<std::shared_ptr<Pnt3d>>& theEngine, const Entity3d_Box& theDomain, const Standard_Real theTol)
		{
			std::vector<Geo3d_BalPrTree<std::shared_ptr<Pnt3d>>::leafNode*> leaves;
			theEngine.RetrieveLeavesTo(leaves);

			std::vector<std::shared_ptr<Entity3d_Box>> boxes;
			boxes.reserve(leaves.size());
			for (const auto& x : leaves)
			{
				Debug_Null_Pointer(x);
				const auto& b = x->Box();
				boxes.push_back(b);
			}

			Geo3d_BalPrTree<std::shared_ptr<Pnt3d>> engine;
			engine.SetGeometryCoordFunc([](const std::shared_ptr<Pnt3d>& x)-> const auto& {return *x; });
			engine.SetGeometryRegion(theDomain);
			engine.SetMaxUnbalancing(4);
			engine.BUCKET_SIZE = 4;

			for (const auto& x : boxes)
			{
				auto p0 = x->Corner(Box3d_PickAlgorithm_Aft_SW);
				InsertToEngine(std::move(p0), theTol, engine);

				auto p1 = x->Corner(Box3d_PickAlgorithm_Aft_SE);
				InsertToEngine(std::move(p1), theTol, engine);

				auto p2 = x->Corner(Box3d_PickAlgorithm_Aft_NE);
				InsertToEngine(std::move(p2), theTol, engine);

				auto p3 = x->Corner(Box3d_PickAlgorithm_Aft_NW);
				InsertToEngine(std::move(p3), theTol, engine);

				auto p4 = x->Corner(Box3d_PickAlgorithm_Fwd_SW);
				InsertToEngine(std::move(p4), theTol, engine);

				auto p5 = x->Corner(Box3d_PickAlgorithm_Fwd_SE);
				InsertToEngine(std::move(p5), theTol, engine);

				auto p6 = x->Corner(Box3d_PickAlgorithm_Fwd_NE);
				InsertToEngine(std::move(p6), theTol, engine);

				auto p7 = x->Corner(Box3d_PickAlgorithm_Fwd_NW);
				InsertToEngine(std::move(p7), theTol, engine);

				/*auto pm = x->CalcCentre();
				InsertToEngine(std::move(pm), theTol, engine);*/
			}

			std::vector<std::shared_ptr<Pnt3d>> sNodes;
			theEngine.RetrieveFromGeometryTo(sNodes);
			for (const auto& x : sNodes)
			{
				auto pt = x->Coord();
				InsertToEngine(std::move(pt), theTol, engine);
			}

			std::vector<std::shared_ptr<Pnt3d>> items;
			engine.RetrieveFromGeometryTo(items);

			std::vector<Pnt3d> coords;
			coords.reserve(items.size());
			for (const auto& x : items)
			{
				coords.push_back(*x);
			}
			return std::move(coords);
		}
	}
}

void tnbLib::Mesh3d_UnionSizeMap::Perform()
{
	if(Models().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no model has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< "no domain has been found." << endl
			<< abort(FatalError);
	}

	if (NOT Cloud())
	{
		FatalErrorIn(FunctionSIG)
			<< "no patch cloud has been found." << endl
			<< abort(FatalError);
	}

	//verbose = 1;

	const auto& models = Models();
	const auto coords = RetrieveCoords(models, *Cloud());

	//const auto b = Geo_BoxTools::GetBox(coords, 0);
	auto expB = *Domain();

	auto mergCrit = Tolerance()*expB.Diameter();

	//std::vector<std::shared_ptr<Entity3d_Box>> boxes;
	Geo3d_BalPrTree<std::shared_ptr<Pnt3d>> approxSpace;
	approxSpace.SetMaxUnbalancing(MaxUnbalancing());
	approxSpace.SetGeometryCoordFunc([](const std::shared_ptr<Pnt3d>& pt)-> const auto&{return *pt; });
	approxSpace.SetGeometryRegion(expB);
	approxSpace.BUCKET_SIZE = 4;
	{

		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			for (const auto& x : coords)
			{
				//std::cout << "x: " << x << std::endl;
				auto b = Geo_BoxTools::GetBox(x, mergCrit);
				std::vector<std::shared_ptr<Pnt3d>> items;
				approxSpace.GeometrySearch(b, items);
				if (items.empty())
				{
					auto node = std::make_shared<Pnt3d>(x);
					Debug_Null_Pointer(node);

					approxSpace.InsertToGeometry(node);
				}
				else
				{
					Standard_Real minDis = RealLast();
					for (const auto& i : items)
					{
						auto dis = (*i).Distance(x);
						if (dis < minDis)
						{
							minDis = dis;
						}
					}
					if (minDis > mergCrit)
					{
						auto node = std::make_shared<Pnt3d>(x);
						Debug_Null_Pointer(node);

						approxSpace.InsertToGeometry(node);
					}
				}
			}
		}

		if (verbose)
		{
			Info << endl
				<< " - the space is approximated in: " << global_time_duration << " ms." << endl;
		}

		// Post balancing [7/16/2022 Amir]
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			//approxSpace.PostBalance();
		}

		if (verbose)
		{

			Info << endl
				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
		}

		/*std::vector<Geo3d_BalPrTree<std::shared_ptr<Pnt3d>>::leafNode*> leaves;
		approxSpace.RetrieveLeavesTo(leaves);

		for (const auto& x : leaves)
		{
			const auto& b = x->Box();
			boxes.push_back(b);
		}*/
	}

	/*{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		approxSpace.SetMaxUnbalancing(4);
		approxSpace.PostBalance();
	}

	if (verbose)
	{
		Info << endl
			<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
	}*/

	auto myTet = std::make_shared<Entity3d_Tetrahedralization>();
	Debug_Null_Pointer(myTet);

	// Triangulation [7/16/2022 Amir]
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		auto pnts = unionTools::RetrieveNodes(approxSpace, expB, mergCrit);
		fadeLib::Geo3d_DelTri delTri(pnts);
		delTri.Perform();

		myTet = delTri.Triangulation();
		//Geo_BoxTools::GetTriangulation(boxes, *myTet);
	}

	if (verbose)
	{
		Info << endl
			<< " - the domain is triangulated in: " << global_time_duration << " ms." << endl;
	}

	if (verbose)
	{
		Info << " Constructing the background mesh..." << endl;
		Info << endl;
	}

	auto dMesh = std::make_shared<GeoMesh3d_Data>();
	Debug_Null_Pointer(dMesh);
	dMesh->Construct(*myTet);

	const auto bMesh = std::make_shared<GeoMesh3d_Background>();
	Debug_Null_Pointer(bMesh);

	bMesh->LoadData(std::move(dMesh));
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(std::move(expB));

	if (verbose)
	{
		Info << " Setting the sources into the background mesh..." << endl;
		Info << endl;
	}

	UpdateSources(bMesh);

	bMesh->HvCorrection(SmoothingInfo());

	theUnifiedMap_ = std::move(bMesh);

	Change_IsDone() = Standard_True;
}