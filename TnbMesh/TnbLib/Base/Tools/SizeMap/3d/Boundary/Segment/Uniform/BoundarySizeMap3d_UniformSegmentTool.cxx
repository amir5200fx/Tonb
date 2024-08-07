//#include <BoundarySizeMap3d_UniformSegmentTool.hxx>
//
//#include <Mesh3d_SetEdgeSources.hxx>
//#include <Mesh3d_Element.hxx>
//#include <MeshBase_Tools.hxx>
//#include <TModel_Tools.hxx>
//#include <TModel_Paired.hxx>
//#include <GeoMesh_Background_Info.hxx>
//#include <GeoMesh3d_Background.hxx>
//#include <GeoMesh3d_Data.hxx>
//#include <Geo3d_BalPrTree.hxx>
//#include <Geo_ItemMerge.hxx>
//#include <Geo_BoxTools.hxx>
//#include <Geo_Tools.hxx>
//#include <Geo3d_LinTessellatePolygon.hxx>
//#include <Entity3d_Box.hxx>
//#include <Entity3d_Tetrahedralization.hxx>
//#include <Entity3d_Polygon.hxx>
//#include <Entity3d_Chain.hxx>
//#include <Global_Timer.hxx>
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//
//namespace tnbLib
//{
//
//	namespace meshLib
//	{
//
//		namespace segmentTool
//		{
//
//			class Node
//			{
//
//				/*Private Data*/
//
//				Pnt3d theCoord_;
//
//				Standard_Real theValue_;
//
//			public:
//
//				typedef Pnt3d ptType;
//
//				// default constructor [7/9/2022 Amir]
//
//				Node()
//					: theCoord_(Pnt3d::null)
//					, theValue_(0)
//				{}
//
//
//				// constructors [7/9/2022 Amir]
//
//				Node(const Pnt3d& theCoord, const Standard_Real h)
//					: theCoord_(theCoord)
//					, theValue_(h)
//				{}
//
//				Node(Pnt3d&& theCoord, const Standard_Real h)
//					: theCoord_(std::move(theCoord))
//					, theValue_(h)
//				{}
//
//				// public functions and operators [7/9/2022 Amir]
//
//				const auto& Coord() const
//				{
//					return theCoord_;
//				}
//
//				auto H() const
//				{
//					return theValue_;
//				}
//
//				static const auto& GetCoord(const std::shared_ptr<Node>& node)
//				{
//					return node->Coord();
//				}
//			};
//		}
//	}
//
//	auto RetrieveMeshes(const std::vector<std::shared_ptr<TModel_Paired>>& theEdges)
//	{
//		std::map<Standard_Integer, std::shared_ptr<Entity3d_Polygon>> meshes;
//		for (const auto& x : theEdges)
//		{
//			Debug_Null_Pointer(x);
//			const auto& mesh = x->Mesh();
//			if (mesh->NbPoints() < 4)
//			{
//				if (mesh->NbPoints() < 2)
//				{
//					FatalErrorIn(FunctionSIG)
//						<< "invalid edge mesh has been detected." << endl
//						<< abort(FatalError);
//				}
//				Geo3d_LinTessellatePolygon tess(mesh);
//				tess.Tessellate(2);
//				Debug_If_Condition_Message(NOT tess.IsDone(), "the application is not performed.");
//				auto paired = std::make_pair(x->Index(), tess.Tessellated());
//				auto iter = meshes.insert(std::move(paired));
//				if (NOT iter.second)
//				{
//					FatalErrorIn(FunctionSIG)
//						<< "duplicate data has been found." << endl
//						<< abort(FatalError);
//				}
//			}
//			else
//			{
//				auto paired = std::make_pair(x->Index(), mesh);
//				auto iter = meshes.insert(std::move(paired));
//				if (NOT iter.second)
//				{
//					FatalErrorIn(FunctionSIG)
//						<< "duplicate data has been found." << endl
//						<< abort(FatalError);
//				}
//			}	
//		}
//		return std::move(meshes);
//	}
//
//	auto RetrieveChain(const std::map<Standard_Integer, std::shared_ptr<Entity3d_Polygon>>& theMeshes)
//	{
//		auto tMesh = std::make_shared<Entity3d_Chain>();
//		for (const auto& x : theMeshes)
//		{
//			Debug_Null_Pointer(x.second);
//			auto chain = Geo_Tools::RetrieveChain(*x.second);
//			tMesh->Add(*chain);
//		}
//		return std::move(tMesh);
//	}
//
//	auto RetrieveChain(const TModel_Paired& theEdge)
//	{
//		if (NOT theEdge.HasMesh())
//		{
//			FatalErrorIn(FunctionSIG)
//				<< "the edge has no mesh." << endl
//				<< abort(FatalError);
//		}
//		const auto& mesh = theEdge.Mesh();
//
//		if (mesh->NbPoints() < 4)
//		{
//			if (mesh->NbPoints() < 2)
//			{
//				FatalErrorIn(FunctionSIG)
//					<< "invalid edge mesh has been detected." << endl
//					<< abort(FatalError);
//			}
//			Geo3d_LinTessellatePolygon tess(mesh);
//			tess.Tessellate(2);
//			Debug_If_Condition_Message(NOT tess.IsDone(), "the application is not performed.");
//
//			auto chain = Geo_Tools::RetrieveChain(*tess.Tessellated());
//			return std::move(chain);
//		}
//		else
//		{
//			auto chain = Geo_Tools::RetrieveChain(*mesh);
//			return std::move(chain);
//		}
//	}
//
//	auto RetrieveChain(const std::vector<std::shared_ptr<TModel_Paired>>& theEdges)
//	{
//		auto chain = std::make_shared<Entity3d_Chain>();
//		Debug_Null_Pointer(chain);
//
//		for (const auto& x : theEdges)
//		{
//			Debug_Null_Pointer(x);
//			auto c = RetrieveChain(*x);
//			chain->Add(*c);
//		}
//		return std::move(chain);
//	}
//
//	auto MakeHs(const Entity3d_Chain& theChain, const Standard_Real h)
//	{
//		const auto& pts = theChain.Points();
//		std::vector<Standard_Real> hs;
//		hs.resize(pts.size(), h);
//		return std::move(hs);
//	}
//}
//
//void tnbLib::BoundarySizeMap3d_UniformSegmentTool::Perform()
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
//	auto segments = RetrieveSegments();
//	auto meshes = RetrieveMeshes(segments);
//	auto chain = ::tnbLib::RetrieveChain(meshes);
//	if (verbose)
//	{
//		Info << " - nb. of segments: " << segments.size() << endl
//			<< endl;
//	}
//	if (segments.empty()) return;
//
//	//! Retrieve sizes
//	Standard_Real elemSize, minElemSize, spanAngle;
//	RetrieveValues(elemSize, minElemSize, spanAngle);
//
//	if (verbose)
//	{
//		Info << " - Base size: " << this->GetBaseSize() << endl;
//		Info << " - Target element size: " << elemSize << endl;
//		Info << " - Min. element size: " << minElemSize << endl;
//		Info << " - Span size angle: " << spanAngle << endl;
//		Info << endl;
//	}
//
//	auto hs = ::tnbLib::MakeHs(*chain, elemSize);
//
//	Standard_Real radius = 0;
//	if (MeshConditions().CustomBoundaryGrowthRate())
//		radius =
//		MeshBase_Tools::CalcRadius
//		(
//			Mesh_VariationRate::Rate(MeshValues().BoundaryGrowthRate()),
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
//	//std::vector<std::shared_ptr<meshLib::segmentTool::Node>> sources;
//	std::vector<std::shared_ptr<Entity3d_Box>> boxes;
//	{
//		Geo3d_BalPrTree<std::shared_ptr<meshLib::segmentTool::Node>> approxSpace;
//		approxSpace.SetMaxUnbalancing(2);
//		approxSpace.SetGeometryCoordFunc(&meshLib::segmentTool::Node::GetCoord);
//		approxSpace.SetGeometryRegion(expB);
//		approxSpace.BUCKET_SIZE = 1;
//
//		{ // Approximating space scope [7/10/2022 Amir]
//			Global_Timer timer;
//			timer.SetInfo(Global_TimerInfo_ms);
//
//			for (const auto& x : meshes)
//			{
//				auto poly = x.second;
//				if (NOT poly)
//				{
//					FatalErrorIn(FunctionSIG)
//						<< "the edge has no triangulation with itself!" << endl
//						<< abort(FatalError);
//				}
//				const auto& nodes = poly->Points();
//				for (const auto& pt : nodes)
//				{
//					auto b = Geo_BoxTools::GetBox<Pnt3d>(pt, mergCrit);
//
//					std::vector<std::shared_ptr<meshLib::segmentTool::Node>> items;
//					approxSpace.GeometrySearch(b, items);
//					if (items.empty())
//					{
//						auto node = std::make_shared<meshLib::segmentTool::Node>(pt, elemSize);
//						Debug_Null_Pointer(node);
//						//std::cout << "insert to empty" << std::endl;
//						approxSpace.InsertToGeometry(node);
//						//sources.push_back(std::move(node));
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
//						//std::cout << "minDis: " << minDis << ", crit: " << mergCrit << std::endl;
//						if (minDis > mergCrit)
//						{
//							//std::cout << "insert..." << std::endl;
//							auto node = std::make_shared<meshLib::segmentTool::Node>(pt, elemSize);
//							Debug_Null_Pointer(node);
//							approxSpace.InsertToGeometry(node);
//							//sources.push_back(std::move(node));
//						}
//						else
//						{
//							//std::cout << "not insert" << std::endl;
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
//			//approxSpace.PostBalance();
//		}
//
//		if (verbose)
//		{
//
//			Info << endl
//				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
//		}
//
//		std::vector<Geo3d_BalPrTree<std::shared_ptr<meshLib::segmentTool::Node>>::leafNode*> leaves;
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
//	const auto nbSources = myTet->NbPoints();
//	/*OFstream myFile("back.plt");
//	myTet->ExportToPlt(myFile);
//	std::exit(1);*/
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
//	auto meshData = std::make_shared<GeoMesh3d_Data>();
//	Debug_Null_Pointer(meshData);
//
//	// constructing a background mesh data [8/1/2022 Amir]
//	meshData->Construct(*myTet);
//
//	
//	//meshData->ExportToPlt(myFile);
//	const auto bMesh = std::make_shared<GeoMesh3d_Background>();
//	Debug_Null_Pointer(bMesh);
//
//	bMesh->LoadData(std::move(meshData));
//
//	// initiate the current element [8/1/2022 Amir]
//	bMesh->InitiateCurrentElement();
//	bMesh->SetBoundingBox(std::move(expB));
//	bMesh->Sources().resize(nbSources, ReferenceValues()->BaseSize());
//	
//	
//	if (verbose)
//	{
//		Info << " Setting the sources into the background mesh..." << endl;
//		Info << endl;
//	}
//	//MeshBase_Tools::SetSourcesToMesh3d(sources, ReferenceValues()->BaseSize(), *bMesh);
//	Mesh3d_SetEdgeSources setSources(hs, chain, bMesh);
//	setSources.Perform();
//	Debug_If_Condition_Message(NOT setSources.IsDone(), "the application is not performed.");
//	//sources.clear();
//
//	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
//	Debug_Null_Pointer(hvInfo);
//	hvInfo->SetMaxNbIters(MaxNbCorrIters());
//
//	if (MeshConditions().CustomBoundaryGrowthRate())
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
//	if (verbose)
//	{
//		Info << " The Hv-Correction is performed, successfully." << endl;
//	}
//
//	ChangeBackMesh() = std::move(bMesh);
//	Change_IsDone() = Standard_True;
//}