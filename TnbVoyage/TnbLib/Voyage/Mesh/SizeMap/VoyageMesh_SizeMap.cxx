#include <VoyageMesh_SizeMap.hxx>

#include <Voyage_Tools.hxx>
#include <VoyageGeo_Path2.hxx>
#include <Mesh_SetSourcesNode.hxx>
#include <MeshBase_Tools.hxx>
#include <GeoMesh2d_Data.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Geo2d_DelTri_CGAL.hxx>
#include <Geo2d_DelTri.hxx>
#include <Geo2d_BalPrTree.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer tnbLib::VoyageMesh_SizeMap::DEFAULT_MAX_NB_CORRS = 5;
Standard_Real tnbLib::VoyageMesh_SizeMap::DEFAULT_SMOOTH_FACTOR = 0.85;
Standard_Real tnbLib::VoyageMesh_SizeMap::DEFAULT_BASE_SIZE = 1.0E-4;

unsigned short tnbLib::VoyageMesh_SizeMap::verbose = 0;

namespace tnbLib
{

	typedef Mesh_SetSourcesNode<Pnt2d, Standard_Real> sourceNode;
	typedef Mesh_SetSourcesNode<Pnt2d, Standard_Real> hNode;

	void InsertToEngine(Pnt2d&& theCoord, const Standard_Real theTol, Geo_AdTree<std::shared_ptr<Pnt2d>>& engine)
	{
		auto b = Geo_BoxTools::GetBox<Pnt2d>(theCoord, theTol);

		std::vector<std::shared_ptr<Pnt2d>> items;
		engine.GeometrySearch(b, items);
		if (items.empty())
		{
			auto node = std::make_shared<Pnt2d>(std::move(theCoord));
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
				auto node = std::make_shared<Pnt2d>(std::move(theCoord));
				Debug_Null_Pointer(node);
				engine.InsertToGeometry(node);
			}
			else
			{
				// do nothing [8/25/2022 Amir]
			}
		}
	}

	void InsertCorners(Geo_AdTree<std::shared_ptr<Pnt2d>>& theEngine)
	{
		const auto& b = theEngine.GeometryBoundingBox();
		{
			auto pt = b.Corner(Box2d_PickAlgorithm_SW);
			auto node = std::make_shared<Pnt2d>(std::move(pt));
			theEngine.InsertToGeometry(node);
		}
		{
			auto pt = b.Corner(Box2d_PickAlgorithm_SE);
			auto node = std::make_shared<Pnt2d>(std::move(pt));
			theEngine.InsertToGeometry(node);
		}
		{
			auto pt = b.Corner(Box2d_PickAlgorithm_NE);
			auto node = std::make_shared<Pnt2d>(std::move(pt));
			theEngine.InsertToGeometry(node);
		}
		{
			auto pt = b.Corner(Box2d_PickAlgorithm_NW);
			auto node = std::make_shared<Pnt2d>(std::move(pt));
			theEngine.InsertToGeometry(node);
		}
	}

	auto MergePath(const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePolygons)
	{
		std::vector<Pnt2d> pnts;
		for (const auto& poly : thePolygons)
		{
			for (const auto& x : poly->Points())
			{
				pnts.push_back(x);
			}
		}
		return std::move(pnts);
	}

	auto RetrieveNodes
	(
		const Geo2d_BalPrTree<std::shared_ptr<sourceNode>>& theEngine,
		const std::vector<Pnt2d>& theCoords,
		const Entity2d_Box& theDomain,
		const Standard_Real theTol
	)
	{
		std::vector<Geo2d_BalPrTree<std::shared_ptr<sourceNode>>::leafNode*> leaves;
		theEngine.RetrieveLeavesTo(leaves);

		std::vector<std::shared_ptr<Entity2d_Box>> boxes;
		boxes.reserve(leaves.size());
		for (const auto& x : leaves)
		{
			Debug_Null_Pointer(x);
			const auto& b = x->Box();
			boxes.push_back(b);
		}

		Geo_AdTree<std::shared_ptr<Pnt2d>> engine;
		engine.SetGeometryCoordFunc
		([](const std::shared_ptr<Pnt2d>& x)-> const auto& {return *x; });
		engine.SetGeometryRegion(theDomain);

		InsertCorners(engine);

		for (const auto& x : boxes)
		{
			auto p0 = x->Corner(Box2d_PickAlgorithm_SW);
			auto p1 = x->Corner(Box2d_PickAlgorithm_SE);
			auto p2 = x->Corner(Box2d_PickAlgorithm_NE);
			auto p3 = x->Corner(Box2d_PickAlgorithm_NW);

			InsertToEngine(std::move(p0), theTol, engine);
			InsertToEngine(std::move(p1), theTol, engine);
			InsertToEngine(std::move(p2), theTol, engine);
			InsertToEngine(std::move(p3), theTol, engine);

		}

		std::vector<std::shared_ptr<Pnt2d>> items;
		engine.RetrieveFromGeometryTo(items);

		std::vector<Pnt2d> coords;
		coords.reserve(items.size());
		for (const auto& x : items)
		{
			coords.push_back(*x);
		}
		return std::move(coords);
	}
}

void tnbLib::VoyageMesh_SizeMap::Perform()
{
	if (NOT Path())
	{
		FatalErrorIn(FunctionSIG)
			<< "No path has been loaded." << endl
			<< abort(FatalError);
	}
	if (Hs())
	{
		FatalErrorIn(FunctionSIG)
			<< "No bas size has been loaded." << endl
			<< abort(FatalError);
	}
	const auto& path = Path();
	const auto& hs = *Hs();

	auto polygons = Voyage_Tools::RetrievePolygons(*path);
	auto d = Voyage_Tools::CalcBoundingBox(polygons, 1.0E-4);

	Geo2d_BalPrTree<std::shared_ptr<sourceNode>> engine;
	engine.SetMaxUnbalancing(2);
	engine.SetGeometryCoordFunc(&sourceNode::GetCoord);
	engine.SetGeometryRegion(*d);
	engine.BUCKET_SIZE = 4;

	Standard_Integer nbSources = 0;
	const Standard_Real mergCrit = 1.0E-4 * d->Diameter();
	Standard_Real baseSize = 1.0E-4;

	//std::vector<std::shared_ptr<hNode>> sources;
	{// approximation scope [8/14/2023 aamir]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);
		size_t polygon_nb = 0;
		for (const auto& ipoly : polygons)
		{
			const auto& hsi = hs.at(polygon_nb++);
			size_t k = 0;
			for (const auto& x : ipoly->Points())
			{
				auto b = Geo_BoxTools::GetBox<Pnt2d>(x, mergCrit);
				auto elmSize = hsi.at(k++);
				std::vector<std::shared_ptr<sourceNode>> items;
				engine.GeometrySearch(b, items);
				if (items.empty())
				{
					//auto h = std::make_shared<hNode>(x, elmSize);
					auto node = std::make_shared<sourceNode>(x, elmSize);
					Debug_Null_Pointer(node);
					engine.InsertToGeometry(node);

					++nbSources;

					//sources.push_back(std::move(h));
				}
				else
				{
					Standard_Real minDis = RealLast();
					std::shared_ptr<sourceNode> founded;
					for (const auto& i : items)
					{
						auto dis = i->Coord().Distance(x);
						if (dis < minDis)
						{
							minDis = dis;
							founded = i;
							break;
						}
					}
					if (minDis > mergCrit)
					{
						//auto h = std::make_shared<hNode>(x, elmSize);
						auto node = std::make_shared<sourceNode>(x, elmSize);
						Debug_Null_Pointer(node);
						engine.InsertToGeometry(node);

						++nbSources;

						//sources.push_back(std::move(h));
					}
					else
					{
						// Update the size [8/19/2023 aamir]
						founded->SetH(std::min(founded->H(), elmSize));
					}
				}
			}
		}
		//for (const auto& x: ::tnbLib::MergePath(polygons))
		//{
		//	
		//	auto b = Geo_BoxTools::GetBox<Pnt2d>(x, mergCrit);
		//	std::vector<std::shared_ptr<sourceNode>> items;
		//	engine.GeometrySearch(b, items);
		//	if (items.empty())
		//	{
		//		auto h = std::make_shared<hNode>(x, elmSize);
		//		auto node = std::make_shared<sourceNode>(x);
		//		Debug_Null_Pointer(node);
		//		engine.InsertToGeometry(node);

		//		++nbSources;

		//		sources.push_back(std::move(h));
		//	}
		//	else
		//	{
		//		Standard_Real minDis = RealLast();
		//		for (const auto& i : items)
		//		{
		//			auto dis = i->Coord().Distance(x);
		//			if (dis < minDis)
		//			{
		//				minDis = dis;
		//			}
		//		}
		//		if (minDis > mergCrit)
		//		{
		//			auto h = std::make_shared<hNode>(x, elmSize);
		//			auto node = std::make_shared<sourceNode>(x);
		//			Debug_Null_Pointer(node);
		//			engine.InsertToGeometry(node);

		//			++nbSources;

		//			sources.push_back(std::move(h));
		//			//srcCoords.push_back(std::move(p));
		//		}
		//		else
		//		{
		//			// do nothing [8/25/2022 Amir]
		//		}
		//	}
		//}
	}
	
	if (verbose)
	{
		Info << endl
			<< " - the space is approximated in: " << global_time_duration << " ms." << endl;
	}

	if (true)
	{
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			engine.SetMaxUnbalancing(8);
			engine.PostBalance();
		}

		if (verbose)
		{
			Info << endl
				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
		}
	}

	std::shared_ptr<Entity2d_Triangulation> myTris;
	std::vector<Pnt2d> srcCoords;
	// Triangulation [8/14/2023 aamir]
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		auto pnts = RetrieveNodes(engine, srcCoords, *d, mergCrit);
		Geo2d_DelTri delTri(pnts);
		delTri.Triangulate();

		myTris = delTri.Data();
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

	auto meshData = std::make_shared<GeoMesh2d_Data>();
	Debug_Null_Pointer(meshData);

	// constructing a background mesh data [6/23/2023 Payvand]
	meshData->Construct(*myTris);

	const auto bMesh = std::make_shared<GeoMesh2d_SingleBackground>();
	Debug_Null_Pointer(bMesh);

	bMesh->LoadData(std::move(meshData));

	// initiate the current element [8/1/2022 Amir]
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(*d);
	bMesh->Sources().resize(myTris->NbPoints(), baseSize);

	if (verbose)
	{
		Info << " Setting the sources into the background mesh..." << endl;
		Info << endl;
	}

	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
	Debug_Null_Pointer(hvInfo);
	hvInfo->SetMaxNbIters(MaxNbCorrs());
	hvInfo->SetFactor(SmoothingFactor());

	std::vector<std::shared_ptr<sourceNode>> sources;
	engine.RetrieveFromGeometryTo(sources);
	MeshBase_Tools::SetSourcesToMesh(sources, BaseSize(), hvInfo->Factor(), *bMesh);
	sources.clear();

	if (verbose)
	{
		Info << " Applying Hv-correction..." << endl;
		Info << " - Max. nb. of iterations: " << hvInfo->MaxNbIters() << endl;
		Info << endl;
	}

	bMesh->HvCorrection(hvInfo);

	if (verbose)
	{
		Info << " The Hv-Correction is performed, successfully." << endl;
	}
	theBackMesh_ = std::move(bMesh);
	Change_IsDone() = Standard_True;
}