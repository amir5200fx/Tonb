#include <BoundarySizeMap3d_UniformSegmentTool.hxx>

#include <Mesh3d_SetSourcesNode.hxx>
#include <GeoMesh_Background_Info.hxx>
#include <MeshBase_Tools.hxx>
#include <Mesh_SetSourcesNode.hxx>
#include <Geo3d_BasicApprxCurve.hxx>
#include <Geo3d_BasicApprxCurveAdaptor.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Edge.hxx>
#include <TModel_GeneratedEdge.hxx>
#include <TModel_Curve.hxx>
#include <Geo3d_BalPrTree.hxx>
#include <Geo_BoxTools.hxx>
#include <GeoMesh3d_Data.hxx>
#include <GeoMesh3d_Background.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::Geo_BasicApprxCurve_Info> tnbLib::BoundarySizeMap3d_UniformSegmentTool::DEFAULT_INFO =
std::make_shared<tnbLib::Geo_BasicApprxCurve_Info>();

Standard_Boolean tnbLib::BoundarySizeMap3d_UniformSegmentTool::POST_BALANCE = Standard_True;
Standard_Integer tnbLib::BoundarySizeMap3d_UniformSegmentTool::DEFAULT_BUCKET_SIZE = 4;
Standard_Integer tnbLib::BoundarySizeMap3d_UniformSegmentTool::DEFAULT_UNBALANCING = 2;

namespace tnbLib
{

	class BoundarySizeMap3d_UniformSegmentTool_RunTimeInfoSetting
	{

		/*Private Data*/

	public:

		// default constructor [8/25/2022 Amir]

		BoundarySizeMap3d_UniformSegmentTool_RunTimeInfoSetting()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

void tnbLib::BoundarySizeMap3d_UniformSegmentTool_RunTimeInfoSetting::SetInfo()
{
	const auto& info = BoundarySizeMap3d_UniformSegmentTool::DEFAULT_INFO;
	info->SetInitNbSubdivision(4);
	info->SetMaxNbSubdivision(8);
	info->SetNbSamples(5);
}

static const tnbLib::BoundarySizeMap3d_UniformSegmentTool_RunTimeInfoSetting
BoundarySizeMap3d_UniformSegmentTool_RunTimeInfoSettingObj;

namespace tnbLib
{

	std::shared_ptr<TModel_Curve> RetrieveEdge(const TModel_Paired& theEdge)
	{
		auto edges = theEdge.RetrieveEdges();
		if (edges.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid paired segment has been detected." << endl
				<< abort(FatalError);
		}
		auto edge = std::dynamic_pointer_cast<TModel_GeneratedEdge>(edges.at(0));
		if (NOT edge)
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge is degenerated." << endl
				<< abort(FatalError);
		}
		return edge->Curve();
	}

	typedef Mesh_SetSourcesNode<Pnt3d, void> sourceNode;
	typedef Mesh_SetSourcesNode<Pnt3d, Standard_Real> hNode;
}

void tnbLib::BoundarySizeMap3d_UniformSegmentTool::Perform()
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

	const auto mergCrit = 1.0E-5*expB.Diameter();

	Geo3d_BalPrTree<std::shared_ptr<sourceNode>> engine;
	engine.SetMaxUnbalancing(UnBalancing());
	engine.SetGeometryCoordFunc(&sourceNode::GetCoord);
	engine.SetGeometryRegion(expB);
	engine.BUCKET_SIZE = BucketSize();

	ApproxInfo()->SetApprox(elemSize);
	ApproxInfo()->SetMinSize(0.9*elemSize);

	Standard_Integer nbSources = 0;

	std::vector<std::shared_ptr<hNode>> sources;
	{ // Approximating space scope [8/25/2022 Amir]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		for (const auto& x : segments)
		{
			Debug_Null_Pointer(x);
			auto curve = ::tnbLib::RetrieveEdge(*x);
			Debug_Null_Pointer(curve);
			Debug_Null_Pointer(curve->Geometry());

			auto adaptor = std::make_shared<Geo3d_BasicApprxCurveAdaptor>(curve->Geometry());

			Geo3d_BasicApprxCurve approx;
			approx.LoadCurve(adaptor, curve->FirstParameter(), curve->LastParameter(), ApproxInfo());
			approx.Perform();
			Debug_If_Condition_Message(NOT approx.IsDone(), "the application is not performed.");

			const auto& poly = approx.Chain();
			for (auto& p : poly->Points())
			{
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

	if (PostBalance())
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