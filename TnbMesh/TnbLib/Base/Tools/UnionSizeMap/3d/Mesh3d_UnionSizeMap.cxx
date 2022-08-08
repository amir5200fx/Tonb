#include <Mesh3d_UnionSizeMap.hxx>

#include <GeoMesh3d_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <Mesh3d_Node.hxx>
#include <Cad_TModel.hxx>
#include <TModel_Surface.hxx>
#include <Geo3d_BalPrTree.hxx>
#include <Geo_BoxTools.hxx>
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
	const Cad_TModel & theModel
)
{
	auto faces = theModel.RetrieveFaces();
	std::vector<Pnt3d> coords;
	for (const auto& x : faces)
	{
		Debug_Null_Pointer(x);
		auto poly = x->RetrieveTriangulation();
		for (Standard_Integer i = 1; i <= poly->NbNodes(); i++)
		{
			coords.push_back(poly->Node(i));
		}
	}
	return std::move(coords);
}

std::vector<tnbLib::Pnt3d> 
tnbLib::Mesh3d_UnionSizeMap::RetrieveCoords
(
	const std::vector<std::shared_ptr<Cad_TModel>>& theModels
)
{
	std::vector<Pnt3d> coords;
	for (const auto& x : theModels)
	{
		Debug_Null_Pointer(x);
		auto pts = RetrieveCoords(*x);
		for (auto& p : pts)
		{
			coords.push_back(std::move(p));
		}
	}
	return std::move(coords);
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

	const auto& models = Models();
	const auto coords = RetrieveCoords(models);

	const auto b = Geo_BoxTools::GetBox(coords, 0);
	const auto expB = *Domain();

	auto mergCrit = Tolerance()*expB.Diameter();

	std::vector<std::shared_ptr<Entity3d_Box>> boxes;
	{
		Geo3d_BalPrTree<std::shared_ptr<Pnt3d>> approxSpace;
		approxSpace.SetMaxUnbalancing(MaxUnbalancing());
		approxSpace.SetGeometryCoordFunc([](const std::shared_ptr<Pnt3d>& pt)-> const auto&{return *pt; });
		approxSpace.SetGeometryRegion(expB);

		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			for (const auto& x : coords)
			{
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

			approxSpace.PostBalance();
		}

		if (verbose)
		{

			Info << endl
				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
		}

		std::vector<Geo3d_BalPrTree<std::shared_ptr<Pnt3d>>::leafNode*> leaves;
		approxSpace.RetrieveLeavesTo(leaves);

		for (const auto& x : leaves)
		{
			const auto& b = x->Box();
			boxes.push_back(b);
		}
	}

	auto myTet = std::make_shared<Entity3d_Tetrahedralization>();
	Debug_Null_Pointer(myTet);

	// Triangulation [7/16/2022 Amir]
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		Geo_BoxTools::GetTriangulation(boxes, *myTet);
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

	const auto bMesh = std::make_shared<GeoMesh3d_Background>();
	Debug_Null_Pointer(bMesh);

	bMesh->Mesh()->Construct(*myTet);
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