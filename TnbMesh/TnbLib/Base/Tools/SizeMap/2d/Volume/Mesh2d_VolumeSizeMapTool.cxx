#include <Mesh2d_VolumeSizeMapTool.hxx>

#include <MeshBase_Tools.hxx>
#include <Mesh2d_VolumeSizeMapTool_Info.hxx>
#include <Mesh_SetSourcesNode.hxx>
#include <GeoMesh2d_Data.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Discret2d_Wire.hxx>
#include <Discret_CurveInfo.hxx>
#include <Discret2d_PlnCurve_UniLengthFun.hxx>
#include <Discret_Curve_UniformSamples.hxx>
#include <Cad2d_Plane.hxx>
#include <Geo2d_DelTri_CGAL.hxx>
#include <Geo2d_DelTri.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo2d_BalPrTree.hxx>
#include <Geo_AdTree.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_Tools.hxx>
#include <Global_Timer.hxx>
#include <TecPlot.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	typedef Mesh_SetSourcesNode<Pnt2d, void> sourceNode;
	typedef Mesh_SetSourcesNode<Pnt2d, Standard_Real> hNode;
}

namespace tnbLib
{

	namespace plnTools
	{

		void InsertToEngine
		(
			Pnt2d&& theCoord,
			const Standard_Real theTol, 
			Geo_AdTree<std::shared_ptr<Pnt2d>>& engine
		)
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
			engine.SetGeometryCoordFunc([](const std::shared_ptr<Pnt2d>& x)-> const auto& {return *x; });
			engine.SetGeometryRegion(theDomain);

			InsertCorners(engine);

			for (const auto& x : boxes)
			{
				auto p0 = x->Corner(Box2d_PickAlgorithm_SW);
				InsertToEngine(std::move(p0), theTol, engine);

				auto p1 = x->Corner(Box2d_PickAlgorithm_SE);
				InsertToEngine(std::move(p1), theTol, engine);

				auto p2 = x->Corner(Box2d_PickAlgorithm_NE);
				InsertToEngine(std::move(p2), theTol, engine);

				auto p3 = x->Corner(Box2d_PickAlgorithm_NW);
				InsertToEngine(std::move(p3), theTol, engine);
			}

			std::vector<std::shared_ptr<Pnt2d>> enginePts;
			engine.RetrieveFromGeometryTo(enginePts);

			for (auto x : theCoords)
			{
				InsertToEngine(std::move(x), theTol, engine);
			}

			std::vector<std::shared_ptr<Pnt2d>> items;
			engine.RetrieveFromGeometryTo(items);

			std::vector<Pnt2d> coords;
			coords.reserve(items.size());
			for (const auto& x : items)
			{
				coords.push_back(*x);
			}
			/*OFstream myFile("sizeMap.plt");
			Io::ExportPoints(coords, myFile);*/
			auto t = std::make_pair(std::move(coords), std::move(enginePts));
			return std::move(t);
		}
	}
}

void tnbLib::Mesh2d_VolumeSizeMapTool::Perform()
{
	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< "no model has been found." << endl
			<< abort(FatalError);
	}
	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< "no domain has been set!" << endl
			<< abort(FatalError);
	}

	const auto& shapes = Shapes();
	if (shapes.empty()) return;

	const auto elemSize = this->GetTargetSurfaceSize();
	if (verbose)
	{
		Info << " - Base element size: " << this->GetBaseSize() << endl;
		Info << " - Target element size: " << elemSize << endl;
		Info << endl;
	}

	auto expB = *Domain();
	for (const auto& x : shapes)
	{
		Debug_Null_Pointer(x.second);
		expB = Geo_BoxTools::Union(expB, x.second->BoundingBox(0));
	}

	const auto mergCrit = 1.0E-5 * expB.Diameter();

	auto discretCrvInfo = std::make_shared<Discret_CurveInfo>();
	discretCrvInfo->SetMaxSubdivide(10);
	discretCrvInfo->SetMinSubdivide(4);

	auto samplesPoints = std::make_shared<Discret_Curve_UniformSamples>();
	samplesPoints->SetNbSamples(AlgInfo()->NbSamples());

	auto elemSize1 = 2 * elemSize;

	auto discretFun = std::make_shared<Discret2d_PlnCurve_UniLengthFun>();
	discretFun->SetSamples(samplesPoints);
	discretFun->SetSize(elemSize1);

	Geo2d_BalPrTree<std::shared_ptr<sourceNode>> engine;
	engine.SetMaxUnbalancing(AlgInfo()->Unbalancing());
	engine.SetGeometryCoordFunc(&sourceNode::GetCoord);
	engine.SetGeometryRegion(expB);
	engine.BUCKET_SIZE = AlgInfo()->BucketSize();

	Standard_Integer nbSources = 0;

	std::vector<Pnt2d> srcCoords;
	std::vector<std::shared_ptr<hNode>> sources;
	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	{// Approximation scope [7/13/2023 Payvand]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		for (const auto& x : shapes)
		{
			const auto& shape = x.second;
			Debug_Null_Pointer(x);

			const auto& wire = shape->OuterWire();

			auto alg = std::make_shared<Discret2d_Wire>();
			alg->SetWire(wire);
			alg->SetInfo(discretCrvInfo);
			alg->SetFunction(discretFun);

			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

			const auto& poly = alg->Polygon();
			polygons.push_back(poly);
			for (const auto& pt : poly->Points())
			{
				auto h = std::make_shared<hNode>(pt, elemSize);
				sources.push_back(std::move(h));
			}
			for (const auto& pt : poly->Points())
			{
				auto b = Geo_BoxTools::GetBox<Pnt2d>(pt, mergCrit);

				std::vector<std::shared_ptr<sourceNode>> items;
				engine.GeometrySearch(b, items);
				if (items.empty())
				{
					//auto h = std::make_shared<hNode>(pt, elemSize);
					auto node = std::make_shared<sourceNode>(pt);
					Debug_Null_Pointer(node);
					engine.InsertToGeometry(node);

					++nbSources;

					//sources.push_back(std::move(h));
					srcCoords.push_back(std::move(pt));
				}
				else
				{
					Standard_Real minDis = RealLast();
					for (const auto& i : items)
					{
						auto dis = i->Coord().Distance(pt);
						if (dis < minDis)
						{
							minDis = dis;
						}
					}
					if (minDis > mergCrit)
					{
						//auto h = std::make_shared<hNode>(pt, elemSize);
						auto node = std::make_shared<sourceNode>(pt);
						Debug_Null_Pointer(node);
						engine.InsertToGeometry(node);

						++nbSources;

						//sources.push_back(std::move(h));
						srcCoords.push_back(std::move(pt));
					}
					else
					{
						// do nothing [8/25/2022 Amir]
					}
				}
			}
		}
	}

	if (verbose)
	{
		Info << endl
			<< " - the space is approximated in: " << global_time_duration << " ms." << endl;
	}

	//if (AlgInfo()->PostBalance())
	{
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			//std::cout << "is balanced? " << engine.IsBalanced() << std::endl;
			engine.SetMaxUnbalancing(/*AlgInfo()->Unbalancing()*/2);
			engine.PostBalance();
			//std::cout << "is balanced? " << engine.IsBalanced() << std::endl;
		}

		if (verbose)
		{
			Info << endl
				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
		}
	}
	
	auto tris = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tris);
	{// Triangulation [7/13/2023 Payvand]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		auto [pnts, enginePts] = plnTools::RetrieveNodes(engine, srcCoords, expB, mergCrit);
		for (const auto& pol : polygons)
		{
			auto innerPts = RetrieveInsidePoints(enginePts, *pol);
			for (const auto& pt : innerPts)
			{
				auto h = std::make_shared<hNode>(pt, elemSize);
				sources.push_back(std::move(h));
			}
		}

		//cgalLib::Geo2d_DelTri delTri(pnts);
		Geo2d_DelTri delTri(pnts);
		//delTri.Perform();
		delTri.Triangulate();
		Debug_If_Condition_Message(NOT delTri.IsDone(), "the application is not performed.");

		//tris = delTri.Triangulation();
		tris = delTri.Data();
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

	// constructing a background mesh data [8/25/2022 Amir]
	meshData->Construct(*tris);

	/*OFstream myFile("sizeMap.plt");
	tris->ExportToPlt(myFile);*/
	//meshData->ExportToPlt(myFile);
	const auto bMesh = std::make_shared<GeoMesh2d_SingleBackground>();
	Debug_Null_Pointer(bMesh);

	bMesh->LoadData(std::move(meshData));

	// initiate the current element [8/1/2022 Amir]
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(std::move(expB));
	bMesh->Sources().resize(tris->NbPoints(), ReferenceValues()->BaseSize());

	if (verbose)
	{
		Info << " Setting the sources into the background mesh..." << endl;
		Info << endl;
	}

	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
	Debug_Null_Pointer(hvInfo);
	hvInfo->SetMaxNbIters(AlgInfo()->MaxNbCorrIters());

	//std::cout << MeshConditions()->CustomBoundaryGrowthRate() << std::endl;
	if (MeshConditions()->CustomBoundaryGrowthRate())
		hvInfo->SetFactor(Mesh_VariationRate::Rate(this->MeshValues()->BoundaryGrowthRate()));
	else
		hvInfo->SetFactor(Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate()));

	MeshBase_Tools::SetSourcesToMeshNearestPoint
	(sources, ReferenceValues()->BaseSize(), hvInfo->Factor(), *bMesh);
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
	OFstream myFile("sizeMap0.plt");
	bMesh->ExportToPlt(myFile);
	ChangeBackMesh() = std::move(bMesh);
	//std::cout << "finished" << std::endl;
	Change_IsDone() = Standard_True;
}

void tnbLib::Mesh2d_VolumeSizeMapTool::ImportShape
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Cad2d_Plane>& theShape
)
{
	Global_Tools::Insert(theIndex, theShape, theShapes_);
}

void tnbLib::Mesh2d_VolumeSizeMapTool::RemoveShape
(
	const Standard_Integer theIndex
)
{
	auto iter = theShapes_.find(theIndex);
	if (iter IS_EQUAL theShapes_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the item is not found." << endl
			<< " - id: " << theIndex << endl
			<< abort(FatalError);
	}
	theShapes_.erase(iter);
}