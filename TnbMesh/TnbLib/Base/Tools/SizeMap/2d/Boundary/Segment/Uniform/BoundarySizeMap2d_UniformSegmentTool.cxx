#include <BoundarySizeMap2d_UniformSegmentTool.hxx>

#include <BoundarySizeMap2d_UniformSegmentTool_Info.hxx>
#include <Mesh_SetSourcesNode.hxx>
#include <Mesh_ApproxCurveInfo.hxx>
#include <Mesh2d_ApproxCurve.hxx>
#include <MeshBase_Tools.hxx>
#include <GeoMesh2d_Data.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Geo2d_DelTri_CGAL.hxx>
#include <Geo2d_BasicApprxCurve.hxx>
#include <Geo2d_BasicApprxCurveAdaptor.hxx>
#include <Geo2d_BalPrTree.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Box.hxx>
#include <Pnt2d.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef Mesh_SetSourcesNode<Pnt2d, void> sourceNode;
	typedef Mesh_SetSourcesNode<Pnt2d, Standard_Real> hNode;

	namespace segmentTools
	{

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

#ifdef NonApprox_Curve
				auto pc = x->CalcCentre();

				InsertToEngine(std::move(pc), theTol, engine);

#endif // NonApprox_Curve

			}

#ifdef NonApprox_Curve
			for (auto x : theCoords)
			{
				InsertToEngine(std::move(x), theTol, engine);
			}
#endif // NonApprox_Curve

			/*std::vector<std::shared_ptr<sourceNode>> sNodes;
			theEngine.RetrieveFromGeometryTo(sNodes);
			for (const auto& x : sNodes)
			{
				auto pt = x->Coord();
				InsertToEngine(std::move(pt), theTol, engine);
			}*/

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
}

void tnbLib::BoundarySizeMap2d_UniformSegmentTool::Perform()
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

	if (NOT ApproxInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no approx. info has been found." << endl
			<< abort(FatalError);
	}

	auto segments = RetrieveSegments();
	if (segments.empty())
	{
		Change_IsDone() = Standard_True;
		return;
	}

	const auto elemSize = this->GetTargetSurfaceSize();
	if (verbose)
	{
		Info << " - Base element size: " << this->GetBaseSize() << endl;
		Info << " - Target element size: " << elemSize << endl;
		Info << endl;
	}

	const auto expB = *Domain();

	const auto mergCrit = 1.0E-5 * expB.Diameter();

	ApproxInfo()->ApproxInfo()->SetApprox(2.0 * elemSize);
	ApproxInfo()->ApproxInfo()->SetMinSize(1.9 * elemSize);
	ApproxInfo()->ApproxInfo()->SetInitNbSubdivision(4);

	auto approxInfo = std::make_shared<Mesh_ApproxCurveInfo>();
	approxInfo->SetMinSize(2.0 * elemSize);
	approxInfo->SetTargetSize(1.95 * elemSize);
	approxInfo->SetNbSamples(ApproxInfo()->ApproxInfo()->NbSamples());
	approxInfo->SetMinNbSubdivisions(4);
	approxInfo->SetMaxNbSubdivisions(10);

	Geo2d_BalPrTree<std::shared_ptr<sourceNode>> engine;
	engine.SetMaxUnbalancing(ApproxInfo()->UnBalancing());
	engine.SetGeometryCoordFunc(&sourceNode::GetCoord);
	engine.SetGeometryRegion(expB);
	engine.BUCKET_SIZE = ApproxInfo()->BucketSize();

	Standard_Integer nbSources = 0;

	std::vector<Pnt2d> srcCoords;
	std::vector<std::shared_ptr<hNode>> sources;
	{// approximation scope [6/23/2023 Payvand]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);
		for (const auto& x : segments)
		{
			Debug_Null_Pointer(x);
			const auto& curve = x->Curve();
			Debug_Null_Pointer(curve);
			Debug_Null_Pointer(curve->Geometry());

			//gen->Mesh()->ExportToPlt(myFile);
			auto adaptor = std::make_shared<Geo2d_BasicApprxCurveAdaptor>(curve->Geometry());

			Mesh_ApproxCurve<Handle(Geom2d_Curve)> approx;
			approx.SetCurve(curve->Geometry());
			approx.SetU0(curve->FirstParameter());
			approx.SetU1(curve->LastParameter());
			approx.SetInfo(approxInfo);
			//approx.LoadCurve(adaptor, curve->FirstParameter(), curve->LastParameter(), ApproxInfo());
			approx.Perform();
			Debug_If_Condition_Message(NOT approx.IsDone(), "the application is not performed.");

			const auto& poly = approx.Mesh();
			//std::cout << "nb of points: " << poly->NbPoints() << std::endl;
			for (const auto& p : poly->Points())
			{
				auto b = Geo_BoxTools::GetBox<Pnt2d>(p, mergCrit);

				std::vector<std::shared_ptr<sourceNode>> items;
				engine.GeometrySearch(b, items);
				if (items.empty())
				{
					auto h = std::make_shared<hNode>(p, elemSize);
					auto node = std::make_shared<sourceNode>(p);
					Debug_Null_Pointer(node);
					engine.InsertToGeometry(node);

					++nbSources;

					sources.push_back(std::move(h));
					//srcCoords.push_back(std::move(p));
				}
				else
				{
					Standard_Real minDis = RealLast();
					for (const auto& i : items)
					{
						auto dis = i->Coord().Distance(p);
						if (dis < minDis)
						{
							minDis = dis;
						}
					}
					if (minDis > mergCrit)
					{
						auto h = std::make_shared<hNode>(p, elemSize);
						auto node = std::make_shared<sourceNode>(p);
						Debug_Null_Pointer(node);
						engine.InsertToGeometry(node);

						++nbSources;

						sources.push_back(std::move(h));
						//srcCoords.push_back(std::move(p));
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

	if (ApproxInfo()->PostBalance())
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

	auto myTris = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(myTris);

	// Triangulation [6/23/2023 Payvand]
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		auto pnts = segmentTools::RetrieveNodes(engine, srcCoords, expB, mergCrit);
		cgalLib::Geo2d_DelTri delTri(pnts);
		delTri.Perform();

		myTris = delTri.Triangulation();
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
	bMesh->SetBoundingBox(std::move(expB));
	bMesh->Sources().resize(myTris->NbPoints(), ReferenceValues()->BaseSize());

	if (verbose)
	{
		Info << " Setting the sources into the background mesh..." << endl;
		Info << endl;
	}

	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
	Debug_Null_Pointer(hvInfo);
	hvInfo->SetMaxNbIters(MaxNbCorrIters());

	//std::cout << MeshConditions()->CustomBoundaryGrowthRate() << std::endl;
	if (MeshConditions()->CustomBoundaryGrowthRate())
		hvInfo->SetFactor(Mesh_VariationRate::Rate(this->MeshValues()->BoundaryGrowthRate()));
	else
		hvInfo->SetFactor(Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate()));

	MeshBase_Tools::SetSourcesToMesh(sources, ReferenceValues()->BaseSize(), hvInfo->Factor(), *bMesh);
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

	ChangeBackMesh() = std::move(bMesh);
	Change_IsDone() = Standard_True;
}