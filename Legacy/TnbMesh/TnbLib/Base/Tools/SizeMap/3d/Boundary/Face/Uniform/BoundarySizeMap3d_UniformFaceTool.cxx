#include <BoundarySizeMap3d_UniformFaceTool.hxx>

#include <BoundarySizeMap3d_UniformFaceTool_Info.hxx>
#include <Mesh_SetSourcesNode.hxx>
#include <Mesh3d_Element.hxx>
#include <MeshBase_Tools.hxx>
#include <Discret3d_Surface.hxx>
#include <Discret3d_SurfaceInfo.hxx>
#include <Discret3d_Surface_UniformSizeFun.hxx>
#include <Discret2d_Curve.hxx>
#include <Discret2d_CurveOnSurface_UniLengthFun.hxx>
#include <Discret_CurveInfo.hxx>
#include <Discret_Curve_UniformSamples.hxx>
#include <TModel_Tools.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Wire.hxx>
#include <TModel_Edge.hxx>
#include <TModel_ParaCurve.hxx>
#include <Cad_Tools.hxx>
#include <Cad_GeomSurface.hxx>
#include <Geo3d_PatchCloud.hxx>
#include <Geo3d_ApprxSurfPatch.hxx>
#include <Geo3d_ApprxSurfPatch_Info.hxx>
#include <Geo3d_ApprxSurfPatch_hSizeFunMode.hxx>
#include <GeoMesh_Background_Info.hxx>
#include <GeoMesh3d_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo3d_BalPrTree.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_ItemMerge.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_Tools.hxx>
#include <Geo3d_DelTri_Fade3d.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Entity2d_Polygon.hxx>
#include <TecPlot.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Poly_Triangulation.hxx>


namespace tnbLib
{

	typedef Mesh_SetSourcesNode<Pnt3d, void> sourceNode;
	typedef Mesh_SetSourcesNode<Pnt3d, Standard_Real> hNode;

	auto RetrieveBackMesh(const std::shared_ptr<TModel_Surface>& theSurface, const Entity2d_Box& theDomain)
	{
		const auto poly = theSurface->RetrieveTriangulation();
		if (NOT poly)
		{
			FatalErrorIn(FunctionSIG)
				<< "no triangulation on surface has been found." << endl
				<< abort(FatalError);
		}
		if (NOT poly->HasUVNodes())
		{
			FatalErrorIn(FunctionSIG)
				<< "no uv-nodes has been found." << endl
				<< abort(FatalError);
		}
		auto tri = Cad_Tools::ParaTriangulation(*poly);

		auto& pts = tri->Points();
		pts = Geo_Tools::DistributeInDomain(pts, theDomain.Expanded(theDomain.Diameter()*1.0E-5));

		auto back = std::make_shared<GeoMesh2d_Data>();
		Debug_Null_Pointer(back);
		back->Construct(*tri);
		return std::move(back);
	}

	auto RetrieveInnerCoords(const std::vector<Pnt2d>& theCoords, const GeoMesh2d_Data& theBack)
	{
		auto firstElemnt = theBack.FirstElement();
		std::vector<Pnt2d> coords;
		coords.reserve(theCoords.size());
		for (const auto& x : theCoords)
		{
			auto elemt = theBack.TriangleLocation(firstElemnt, x);
			if (elemt)
			{
				coords.push_back(x);
				firstElemnt = elemt;
			}
		}
		return std::move(coords);
	}

	namespace faceTools
	{

		void InsertToEngine(Pnt3d&& theCoord, const Standard_Real theTol, Geo_AdTree<std::shared_ptr<Pnt3d>>& engine)
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

		void InsertCorners(Geo_AdTree<std::shared_ptr<Pnt3d>>& theEngine)
		{
			const auto& b = theEngine.GeometryBoundingBox();
			{
				auto pt = b.Corner(Box3d_PickAlgorithm_Aft_SW);
				auto node = std::make_shared<Pnt3d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
			{
				auto pt = b.Corner(Box3d_PickAlgorithm_Aft_SE);
				auto node = std::make_shared<Pnt3d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
			{
				auto pt = b.Corner(Box3d_PickAlgorithm_Aft_NE);
				auto node = std::make_shared<Pnt3d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
			{
				auto pt = b.Corner(Box3d_PickAlgorithm_Aft_NW);
				auto node = std::make_shared<Pnt3d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}

			{
				auto pt = b.Corner(Box3d_PickAlgorithm_Fwd_SW);
				auto node = std::make_shared<Pnt3d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
			{
				auto pt = b.Corner(Box3d_PickAlgorithm_Fwd_SE);
				auto node = std::make_shared<Pnt3d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
			{
				auto pt = b.Corner(Box3d_PickAlgorithm_Fwd_NE);
				auto node = std::make_shared<Pnt3d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
			{
				auto pt = b.Corner(Box3d_PickAlgorithm_Fwd_NW);
				auto node = std::make_shared<Pnt3d>(std::move(pt));
				theEngine.InsertToGeometry(node);
			}
		}

		auto RetrieveNodes(const Geo3d_BalPrTree<std::shared_ptr<sourceNode>>& theEngine, const std::vector<Pnt3d>& theCoords, const Entity3d_Box& theDomain, const Standard_Real theTol)
		{
			std::vector<Geo3d_BalPrTree<std::shared_ptr<sourceNode>>::leafNode*> leaves;
			theEngine.RetrieveLeavesTo(leaves);

			std::vector<std::shared_ptr<Entity3d_Box>> boxes;
			boxes.reserve(leaves.size());
			for (const auto& x : leaves)
			{
				Debug_Null_Pointer(x);
				const auto& b = x->Box();
				boxes.push_back(b);
			}

			Geo_AdTree<std::shared_ptr<Pnt3d>> engine;
			engine.SetGeometryCoordFunc([](const std::shared_ptr<Pnt3d>& x)-> const auto& {return *x; });
			engine.SetGeometryRegion(theDomain);

			InsertCorners(engine);
			/*Geo3d_BalPrTree<std::shared_ptr<Pnt3d>> engine;
			engine.SetGeometryCoordFunc([](const std::shared_ptr<Pnt3d>& x)-> const auto& {return *x; });
			engine.SetGeometryRegion(theDomain);
			engine.SetMaxUnbalancing(2);
			engine.BUCKET_SIZE = 4;*/

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
			}

			/*std::vector<std::shared_ptr<sourceNode>> sNodes;
			theEngine.RetrieveFromGeometryTo(sNodes);
			for (const auto& x : sNodes)
			{
				auto pt = x->Coord();
				InsertToEngine(std::move(pt), theTol, engine);
			}*/

			for (auto x : theCoords)
			{
				InsertToEngine(std::move(x), theTol, engine);
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

		auto GetPolygon
		(
			const std::shared_ptr<Cad_ParaCurve>& theCurve,
			const std::shared_ptr<Discret2d_Curve_Function>& theFunc,
			const std::shared_ptr<Discret_CurveInfo>& theInfo
		)
		{
			auto alg = std::make_shared<Discret2d_Curve>();
			alg->SetCurve(theCurve);
			alg->SetU0(theCurve->FirstParameter());
			alg->SetU1(theCurve->LastParameter());
			alg->SetFunction(theFunc);
			alg->SetInfo(theInfo);	

			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

			return alg->Mesh();
		}

		auto GetPolygon
		(
			const TModel_Wire& theWire, 
			const std::shared_ptr<Discret2d_Curve_Function>& theFun,
			const std::shared_ptr<Discret_CurveInfo>& theInfo
		)
		{
			std::vector<Pnt2d> pts;
			for (const auto& x : *theWire.Edges())
			{
				const auto& curve = x->ParaCurve();
				Debug_Null_Pointer(curve);
				auto pl = GetPolygon(curve, theFun, theInfo);
				for (auto p : *pl)
				{
					auto pt = curve->Value(p);
					pts.push_back(std::move(pt));
				}
			}
			return std::move(pts);
		}

		auto GetPolygon(const std::vector<Pnt2d>& thePts, const Standard_Real theTol)
		{
			Debug_If_Condition(thePts.size() < 3);
			std::vector<Pnt2d> coords;
			coords.reserve(thePts.size() - 1);
			coords.push_back(thePts.at(0));
			for (size_t i = 1; i < thePts.size(); i++)
			{
				const auto& p0 = thePts.at(i - 1);
				const auto& p1 = thePts.at(i);

				if (p0.Distance(p1) > theTol)
				{
					coords.push_back(p1);
				}
			}
			auto poly = std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
			return std::move(poly);
		}

		auto DiscreteBoundaries
		(
			const TModel_Surface& theSurface,
			const std::shared_ptr<Discret2d_Curve_Function>& theFun,
			const std::shared_ptr<Discret_CurveInfo>& theInfo,
			const Standard_Real theTol
		)
		{
			const auto& outer = theSurface.Outer();
			auto outerPoly = GetPolygon(GetPolygon(*outer, theFun, theInfo), theTol);
			const auto& inners = theSurface.Inner();

			auto innerPolys = std::make_shared<std::vector<std::shared_ptr<Entity2d_Polygon>>>();
			if (inners)
			{
				innerPolys->reserve(inners->size());
				for (const auto& x : *inners)
				{
					auto ipl = GetPolygon(GetPolygon(*x, theFun, theInfo), theTol);
					innerPolys->push_back(std::move(ipl));
				}
			}
			auto t = std::make_pair(std::move(outerPoly), std::move(innerPolys));
			return std::move(t);
		}

	}
}

void tnbLib::BoundarySizeMap3d_UniformFaceTool::Perform()
{
	if (NOT Model())
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

	if (NOT AlgInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Cloud())
	{
		FatalErrorIn(FunctionSIG)
			<< "no cloud has been found." << endl
			<< abort(FatalError);
	}
	
	auto faces = RetrieveFaces();
	if (faces.empty())
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

	const auto mergCrit = 1.0E-5*expB.Diameter();

	//AlgInfo()->ApprxSurfInfo()->SetTolerance(elemSize);

	//auto funMode = std::make_shared<Geo3d_ApprxSurfPatch_hSizeFunMode>(AlgInfo()->NbSamples());
	auto samplesPoints = std::make_shared<Discret_Curve_UniformSamples>();
	samplesPoints->SetNbSamples(5);

	auto elemSize1 = 4 * elemSize;

	auto discretCrvInfo = std::make_shared<Discret_CurveInfo>();
	discretCrvInfo->SetMaxSubdivide(10);
	discretCrvInfo->SetMinSubdivide(4);

	auto discretSrfInfo = std::make_shared<Discret3d_SurfaceInfo>();
	discretSrfInfo->SetMaxNbSubs(10);
	discretSrfInfo->SetMinNbSubs(4);
	discretSrfInfo->SetTolerance(mergCrit);

	auto discretSrfFun = std::make_shared<Discret3d_Surface_UniformSizeFun>();
	discretSrfFun->SetSamples(samplesPoints);
	discretSrfFun->SetSize(elemSize1);

	Standard_Integer nbSources = 0;

	Geo3d_BalPrTree<std::shared_ptr<sourceNode>> engine;
	engine.SetMaxUnbalancing(AlgInfo()->UnBalancing());
	engine.SetGeometryCoordFunc(&sourceNode::GetCoord);
	engine.SetGeometryRegion(expB);
	//engine0.BUCKET_SIZE = AlgInfo()->BucketSize();
	engine.BUCKET_SIZE = 8;

	//OFstream myFIle1("samplesPoints2D.plt");

	std::vector<Pnt3d> srcCoords;
	std::vector<std::shared_ptr<hNode>> sources;
	{ // Approximating space scope [9/5/2022 Amir]

		

		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		for (const auto& x : faces)
		{
			Debug_Null_Pointer(x);
			if (NOT x->GeomSurface())
			{
				FatalErrorIn(FunctionSIG)
					<< "the face has no geometry!" << endl
					<< abort(FatalError);
			}

			/*const auto& poly = x->RetrieveTriangulation();
			if (NOT poly)
			{
				FatalErrorIn(FunctionSIG)
					<< "the surface has no triangulation." << endl
					<< abort(FatalError);
			}*/
			const auto& geometry = x->GeomSurface();

			auto discretFun = std::make_shared<Discret2d_CurveOnSurface_UniLengthFun>();
			discretFun->SetSamples(samplesPoints);
			discretFun->SetSize(elemSize1);
			discretFun->SetSurface(geometry);

			auto[outerPoly, innersPoly] = ::tnbLib::faceTools::DiscreteBoundaries(*x, discretFun, discretCrvInfo, mergCrit);
			auto alg = std::make_shared<Discret3d_Surface>();
			Debug_Null_Pointer(alg);

			alg->SetSurface(x->GeomSurface());

			auto d = x->ParaBoundingBox();
			d.Expand(d.Diameter()*1.0E-5);
			
			alg->SetDomain(std::make_shared<Entity2d_Box>(std::move(d)));

			alg->SetInfo(discretSrfInfo);
			alg->SetSizeFun(discretSrfFun);

			alg->SetOuter(outerPoly);
			alg->SetInners(innersPoly);

			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");
			
			const auto& samples = *alg->Samples();

			//Io::ExportPoints(samples, myFIle1);
			//std::cout << "nb of samples: " << samples.size() << std::endl;
			//const auto b = std::make_shared<Entity2d_Box>(x->ParaBoundingBox());

			//auto back = RetrieveBackMesh(x, *b);

			/*auto approx = 
				std::make_shared<Geo3d_ApprxSurfPatch>
				(
					geometry->Geometry(), b, back,
					funMode, AlgInfo()->ApprxSurfInfo()
					);
			Debug_Null_Pointer(approx);
			approx->Perform();
			Debug_If_Condition_Message(NOT approx->IsDone(), "the application is not performed.");

			auto inners = RetrieveInnerCoords(*approx->Approximated(), *back);*/

			//auto tri = Cad_Tools::ParaTriangulation(*poly);
			//auto samples = Cloud()->CalcCloud(*tri);

			//for (const auto& p2 : inners)
			//size_t kk = 0;
			for (const auto& p2 : samples)
			{
				//std::cout << ++kk << std::endl;
				auto p = geometry->Value(p2);
				auto b = Geo_BoxTools::GetBox<Pnt3d>(p, mergCrit);

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
					srcCoords.push_back(std::move(p));
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
						srcCoords.push_back(std::move(p));
					}
					else
					{
						// do nothing [8/25/2022 Amir]
					}
				}
			}
		}
	}

	//Geo3d_BalPrTree<std::shared_ptr<sourceNode>> engine;
	//engine.SetMaxUnbalancing(AlgInfo()->UnBalancing());
	//engine.SetGeometryCoordFunc(&sourceNode::GetCoord);
	//engine.SetGeometryRegion(expB);
	//engine.BUCKET_SIZE = AlgInfo()->BucketSize();

	//{ // Approximating space scope [9/5/2022 Amir]
	//	Global_Timer timer;
	//	timer.SetInfo(Global_TimerInfo_ms);

	//	for (const auto& x : faces)
	//	{
	//		Debug_Null_Pointer(x);
	//		if (NOT x->GeomSurface())
	//		{
	//			FatalErrorIn(FunctionSIG)
	//				<< "the face has no geometry!" << endl
	//				<< abort(FatalError);
	//		}

	//		const auto& poly = x->RetrieveTriangulation();
	//		if (NOT poly)
	//		{
	//			FatalErrorIn(FunctionSIG)
	//				<< "the surface has no triangulation." << endl
	//				<< abort(FatalError);
	//		}
	//		const auto& geometry = x->GeomSurface();
	//		//const auto b = std::make_shared<Entity2d_Box>(x->ParaBoundingBox());

	//		//auto back = RetrieveBackMesh(x, *b);

	//		/*auto approx =
	//			std::make_shared<Geo3d_ApprxSurfPatch>
	//			(
	//				geometry->Geometry(), b, back,
	//				funMode, AlgInfo()->ApprxSurfInfo()
	//				);
	//		Debug_Null_Pointer(approx);
	//		approx->Perform();
	//		Debug_If_Condition_Message(NOT approx->IsDone(), "the application is not performed.");

	//		auto inners = RetrieveInnerCoords(*approx->Approximated(), *back);*/

	//		auto tri = Cad_Tools::ParaTriangulation(*poly);
	//		//auto samples = Cloud()->CalcCloud(*tri);

	//		//for (const auto& p2 : inners)
	//		for (const auto& p2 : tri->Points())
	//		{
	//			auto p = geometry->Value(p2);
	//			auto b = Geo_BoxTools::GetBox<Pnt3d>(p, mergCrit);

	//			std::vector<std::shared_ptr<sourceNode>> items;
	//			engine.GeometrySearch(b, items);
	//			if (items.empty())
	//			{
	//				auto h = std::make_shared<hNode>(p, 0);
	//				auto node = std::make_shared<sourceNode>(std::move(p));
	//				Debug_Null_Pointer(node);
	//				engine.InsertToGeometry(node);
	//			}
	//			else
	//			{
	//				Standard_Real minDis = RealLast();
	//				for (const auto& i : items)
	//				{
	//					auto dis = i->Coord().Distance(p);
	//					if (dis < minDis)
	//					{
	//						minDis = dis;
	//					}
	//				}
	//				if (minDis > mergCrit)
	//				{
	//					auto h = std::make_shared<hNode>(p, 0);
	//					auto node = std::make_shared<sourceNode>(std::move(p));
	//					Debug_Null_Pointer(node);
	//					engine.InsertToGeometry(node);
	//				}
	//				else
	//				{
	//					// do nothing [8/25/2022 Amir]
	//				}
	//			}
	//		}
	//	}
	//}


	if (verbose)
	{
		Info << endl
			<< " - the space is approximated in: " << global_time_duration << " ms." << endl;
	}

	if (AlgInfo()->ApplyPostBalance())
	{
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			//std::cout << "is balanced? " << engine.IsBalanced() << std::endl;
			engine.SetMaxUnbalancing(8);
			engine.PostBalance();
			//std::cout << "is balanced? " << engine.IsBalanced() << std::endl;
		}

		if (verbose)
		{
			Info << endl
				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
		}
	}

	/*std::vector<Geo3d_BalPrTree<std::shared_ptr<sourceNode>>::leafNode*> leaves;
	engine.RetrieveLeavesTo(leaves);

	std::vector<std::shared_ptr<Entity3d_Box>> boxes;
	for (const auto& x : leaves)
	{
		Debug_Null_Pointer(x);
		const auto& b = x->Box();
		boxes.push_back(b);
	}*/

	auto myTet = std::make_shared<Entity3d_Tetrahedralization>();
	Debug_Null_Pointer(myTet);
	// Triangulation [8/25/2022 Amir]
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		auto pnts = faceTools::RetrieveNodes(engine, srcCoords, expB, mergCrit);
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

	auto meshData = std::make_shared<GeoMesh3d_Data>();
	Debug_Null_Pointer(meshData);

	// constructing a background mesh data [8/25/2022 Amir]
	meshData->Construct(*myTet);

	//meshData->ExportToPlt(myFile);
	const auto bMesh = std::make_shared<GeoMesh3d_SingleBackground>();
	Debug_Null_Pointer(bMesh);

	bMesh->LoadData(std::move(meshData));

	// initiate the current element [8/1/2022 Amir]
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(std::move(expB));
	bMesh->Sources().resize(myTet->NbPoints(), ReferenceValues()->BaseSize());

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

	MeshBase_Tools::SetSourcesToMeshNearestPoint(sources, ReferenceValues()->BaseSize(), hvInfo->Factor(), *bMesh);
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
	//std::cout << "finished" << std::endl;
	Change_IsDone() = Standard_True;
}

//void tnbLib::BoundarySizeMap3d_UniformFaceTool::Perform()
//{
//	if (NOT Model())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "no model has been found." << endl
//			<< abort(FatalError);
//	}
//	if (NOT Domain())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "no domain has been set!" << endl
//			<< abort(FatalError);
//	}
//
//	auto faces = RetrieveFaces();
//	if (verbose)
//	{
//		Info << " - nb. of faces: " << faces.size() << endl
//			<< endl;
//	}
//	if (faces.empty()) return;
//
//	//! Retrieve sizes
//	Standard_Real elemSize, minElemSize, spanAngle;
//	RetrieveValues(elemSize, minElemSize, spanAngle);
//
//	if (verbose)
//	{
//		Info << " - Target element size: " << elemSize << endl;
//		Info << " - Min. element size: " << minElemSize << endl;
//		Info << " - Span size angle: " << spanAngle << endl;
//		Info << endl;
//	}
//
//	Standard_Real radius = 0;
//	if (MeshConditions()->CustomBoundaryGrowthRate())
//		radius =
//		MeshBase_Tools::CalcRadius
//		(
//			Mesh_VariationRate::Rate(MeshValues()->BoundaryGrowthRate()),
//			elemSize,
//			ReferenceValues()->BaseSize()
//		);
//	else
//		radius =
//		MeshBase_Tools::CalcRadius
//		(
//			Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate()),
//			elemSize,
//			ReferenceValues()->BaseSize()
//		);
//	if (radius IS_EQUAL 0)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "invalid radius value has been detected!" << endl
//			<< abort(FatalError);
//	}
//
//	if (verbose > 1)
//	{
//		Info << " - Radius: " << radius << endl;
//		Info << endl;
//	}
//	//const auto b = *Domain();
//	const auto expB = *Domain();
//
//	const auto mergCrit = 1.0E-5*expB.Diameter();
//
//	if (verbose)
//	{
//		Info << " Approximating the whole domain..." << endl;
//		Info << endl;
//	}
//
//	std::vector<std::shared_ptr<meshLib::faceTool::Node>> sources;
//	std::vector<std::shared_ptr<Entity3d_Box>> boxes;
//	{
//		Geo3d_BalPrTree<std::shared_ptr<meshLib::faceTool::Node>> approxSpace;
//		approxSpace.SetMaxUnbalancing(2);
//		approxSpace.SetGeometryCoordFunc(&meshLib::faceTool::Node::GetCoord);
//		approxSpace.SetGeometryRegion(expB);
//
//		{ // Approximating space scope [7/10/2022 Amir]
//			Global_Timer timer;
//			timer.SetInfo(Global_TimerInfo_ms);
//
//			for (const auto& x : faces)
//			{
//				auto poly = x->RetrieveTriangulation();
//				if (NOT poly)
//				{
//					FatalErrorIn(FunctionSIG)
//						<< "the edge has no triangulation with itself!" << endl
//						<< abort(FatalError);
//				}
//				for (Standard_Integer i = 1; i < poly->NbNodes(); i++)
//				{
//					const auto& pt = poly->Node(i);
//					auto b = Geo_BoxTools::GetBox<Pnt3d>(pt, mergCrit);
//
//					std::vector<std::shared_ptr<meshLib::faceTool::Node>> items;
//					approxSpace.GeometrySearch(b, items);
//					if (items.empty())
//					{
//						auto node = std::make_shared<meshLib::faceTool::Node>(pt, elemSize);
//						Debug_Null_Pointer(node);
//						approxSpace.InsertToGeometry(node);
//						sources.push_back(std::move(node));
//					}
//					else
//					{
//						Standard_Real minDis = RealLast();
//						for (const auto& i : items)
//						{
//							auto dis = i->Coord().Distance(pt);
//							if (dis < minDis)
//							{
//								minDis = dis;
//							}
//						}
//						if (minDis > mergCrit)
//						{
//							auto node = std::make_shared<meshLib::faceTool::Node>(pt, elemSize);
//							Debug_Null_Pointer(node);
//							approxSpace.InsertToGeometry(node);
//							sources.push_back(std::move(node));
//						}
//					}
//				}
//			}
//		}
//
//		if (verbose)
//		{
//			Info << endl
//				<< " - the space is approximated in: " << global_time_duration << " ms." << endl;
//		}
//
//		// Post Balancing [7/10/2022 Amir]
//		{
//			Global_Timer timer;
//			timer.SetInfo(Global_TimerInfo_ms);
//
//			approxSpace.PostBalance();
//		}
//
//		if (verbose)
//		{
//
//			Info << endl
//				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
//		}
//
//		std::vector<Geo3d_BalPrTree<std::shared_ptr<meshLib::faceTool::Node>>::leafNode*> leaves;
//		approxSpace.RetrieveLeavesTo(leaves);
//
//		for (const auto& x : leaves)
//		{
//			const auto& b = x->Box();
//			boxes.push_back(b);
//		}
//	}
//
//	auto myTet = std::make_shared<Entity3d_Tetrahedralization>();
//	Debug_Null_Pointer(myTet);
//	// Triangulation [7/10/2022 Amir]
//	{
//		Global_Timer timer;
//		timer.SetInfo(Global_TimerInfo_ms);
//
//		Geo_BoxTools::GetTriangulation(boxes, *myTet);
//	}
//
//	if (verbose)
//	{
//		Info << endl
//			<< " - the domain is triangulated in: " << global_time_duration << " ms." << endl;
//	}
//
//	if (verbose)
//	{
//		Info << " Constructing the background mesh..." << endl;
//		Info << endl;
//	}
//
//	const auto bMesh = std::make_shared<GeoMesh3d_Background>();
//	Debug_Null_Pointer(bMesh);
//
//	bMesh->Mesh()->Construct(*myTet);
//	bMesh->InitiateCurrentElement();
//	bMesh->SetBoundingBox(std::move(expB));
//
//	if (verbose)
//	{
//		Info << " Setting the sources into the background mesh..." << endl;
//		Info << endl;
//	}
//	MeshBase_Tools::SetSourcesToMesh3d(sources, ReferenceValues()->BaseSize(), *bMesh);
//	sources.clear();
//
//	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
//	Debug_Null_Pointer(hvInfo);
//	hvInfo->SetMaxNbIters(MaxNbCorrIters());
//
//	if (MeshConditions()->CustomBoundaryGrowthRate())
//		hvInfo->SetFactor(Mesh_VariationRate::Rate(ReferenceValues()->BoundaryGrowthRate()));
//	else
//		hvInfo->SetFactor(Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate()));
//
//	if (verbose)
//	{
//		Info << " Applying Hv-correction..." << endl;
//		Info << " - Max. nb. of iterations: " << hvInfo->MaxNbIters() << endl;
//		Info << endl;
//	}
//	bMesh->HvCorrection(hvInfo);
//
//	ChangeBackMesh() = std::move(bMesh);
//	Change_IsDone() = Standard_True;
//}