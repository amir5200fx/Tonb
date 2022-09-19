#include <BoundarySizeMap3d_UniformFaceTool.hxx>

#include <BoundarySizeMap3d_UniformFaceTool_Info.hxx>
#include <Mesh_SetSourcesNode.hxx>
#include <Mesh3d_Element.hxx>
#include <MeshBase_Tools.hxx>
#include <TModel_Tools.hxx>
#include <TModel_Surface.hxx>
#include <Cad_Tools.hxx>
#include <Cad_GeomSurface.hxx>
#include <Geo3d_ApprxSurfPatch.hxx>
#include <Geo3d_ApprxSurfPatch_Info.hxx>
#include <Geo3d_ApprxSurfPatch_hSizeFunMode.hxx>
#include <GeoMesh_Background_Info.hxx>
#include <GeoMesh3d_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo3d_BalPrTree.hxx>
#include <Geo_ItemMerge.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Poly_Triangulation.hxx>

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

	AlgInfo()->ApprxSurfInfo()->SetTolerance(elemSize);

	Geo3d_BalPrTree<std::shared_ptr<sourceNode>> engine;
	engine.SetMaxUnbalancing(AlgInfo()->UnBalancing());
	engine.SetGeometryCoordFunc(&sourceNode::GetCoord);
	engine.SetGeometryRegion(expB);
	engine.BUCKET_SIZE = AlgInfo()->BucketSize();

	auto funMode = std::make_shared<Geo3d_ApprxSurfPatch_hSizeFunMode>(AlgInfo()->NbSamples());

	Standard_Integer nbSources = 0;

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
			const auto& geometry = x->GeomSurface();
			const auto b = std::make_shared<Entity2d_Box>(x->ParaBoundingBox());

			auto back = RetrieveBackMesh(x, *b);

			auto approx = 
				std::make_shared<Geo3d_ApprxSurfPatch>
				(
					geometry->Geometry(), b, back,
					funMode, AlgInfo()->ApprxSurfInfo()
					);
			Debug_Null_Pointer(approx);
			approx->Perform();
			Debug_If_Condition_Message(NOT approx->IsDone(), "the application is not performed.");

			auto inners = RetrieveInnerCoords(*approx->Approximated(), *back);
			for (const auto& p2 : inners)
			{
				auto p = geometry->Value(p2);
				auto b = Geo_BoxTools::GetBox<Pnt3d>(p, mergCrit);

				std::vector<std::shared_ptr<sourceNode>> items;
				engine.GeometrySearch(b, items);
				if (items.empty())
				{
					auto h = std::make_shared<hNode>(p, elemSize);
					auto node = std::make_shared<sourceNode>(std::move(p));
					Debug_Null_Pointer(node);
					engine.InsertToGeometry(node);

					++nbSources;

					sources.push_back(std::move(h));
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
						auto node = std::make_shared<sourceNode>(std::move(p));
						Debug_Null_Pointer(node);
						engine.InsertToGeometry(node);

						++nbSources;

						sources.push_back(std::move(h));
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

	if (AlgInfo()->ApplyPostBalance())
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		//engine.PostBalance();
	}

	if (verbose)
	{
		Info << endl
			<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
	}

	std::vector<Geo3d_BalPrTree<std::shared_ptr<sourceNode>>::leafNode*> leaves;
	engine.RetrieveLeavesTo(leaves);

	std::vector<std::shared_ptr<Entity3d_Box>> boxes;
	for (const auto& x : leaves)
	{
		Debug_Null_Pointer(x);
		const auto& b = x->Box();
		boxes.push_back(b);
	}

	auto myTet = std::make_shared<Entity3d_Tetrahedralization>();
	Debug_Null_Pointer(myTet);
	// Triangulation [8/25/2022 Amir]
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

	auto meshData = std::make_shared<GeoMesh3d_Data>();
	Debug_Null_Pointer(meshData);

	// constructing a background mesh data [8/25/2022 Amir]
	meshData->Construct(*myTet);

	//meshData->ExportToPlt(myFile);
	const auto bMesh = std::make_shared<GeoMesh3d_Background>();
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

	MeshBase_Tools::SetSourcesToMesh3d(sources, ReferenceValues()->BaseSize(), *bMesh);
	sources.clear();

	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
	Debug_Null_Pointer(hvInfo);
	hvInfo->SetMaxNbIters(MaxNbCorrIters());

	//std::cout << MeshConditions()->CustomBoundaryGrowthRate() << std::endl;
	if (MeshConditions()->CustomBoundaryGrowthRate())
		hvInfo->SetFactor(Mesh_VariationRate::Rate(this->MeshValues()->BoundaryGrowthRate()));
	else
		hvInfo->SetFactor(Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate()));

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