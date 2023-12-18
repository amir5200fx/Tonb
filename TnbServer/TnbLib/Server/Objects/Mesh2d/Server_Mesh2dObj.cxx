#include <Aft2d_MetricPrcsrFwd.hxx>
#include <Server_Mesh2dObj.hxx>

#include <Aft_MetricPrcsr_Info.hxx>
#include <Mesh2d_ReferenceValues.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Vertex.hxx>
#include <Cad_EntityManager.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Entity2d_Box.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <json.hpp>

#include <StdFail_NotDone.hxx>

void tnbLib::Server_Mesh2dObj_MetricPrcsr_Settings::Construct(const std::string& theValue)
{
	std::shared_ptr<NumAlg_AdaptiveInteg_Info> info;
	std::stringstream stream;
	stream << theValue;
	TNB_iARCH_FILE_TYPE ia(stream);
	ia >> info;
	try
	{
		if (!info)
		{
			throw Server_Error("the adaptive integration object is null.");
		}
		auto value = std::make_shared<Aft_MetricPrcsr_Info>(info);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

#include <Aft2d_MetricPrcsr.hxx>

const std::string tnbLib::Server_Mesh2dObj_MetricPrcsr::Params::size_fun("size_fun");
const std::string tnbLib::Server_Mesh2dObj_MetricPrcsr::Params::settings("settings");
const std::string tnbLib::Server_Mesh2dObj_MetricPrcsr::Params::dim("dim");

void tnbLib::Server_Mesh2dObj_MetricPrcsr::Construct(const std::string& theValue)
{
	std::shared_ptr<Geo2d_SizeFunction> size_fun;
	double dim;
	std::shared_ptr<Aft_MetricPrcsr_Info> settings;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_fun);
		}
		{
			loadTnbServerObject(dim);
		}
		{
			loadTnbServerObject(settings);
		}
	}
	try
	{
		if (!size_fun)
		{
			throw Server_Error("the size function object is null.");
		}
		if (!settings)
		{
			throw Server_Error("the metric processor setting object is null.");
		}
		auto value = std::make_shared<Aft2d_MetricPrcsr>(size_fun, settings);
		value->SetDimSize(dim);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_OptPoint::Params::tol("tol");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_OptPoint::Params::ur("ur");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_OptPoint::Params::max_lev("max_lev");

#include <Mesh_CurveOptmPoint_Correction_Info.hxx>

void tnbLib::Server_Mesh2dObj_Mesh_Curve_OptPoint::Construct(const std::string& theValue)
{
	double tol = 0;
	double ur = 0;
	int max_lev = 0;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(tol);
		}
		{
			loadTnbServerObject(ur);
		}
		{
			loadTnbServerObject(max_lev);
		}
	}
	auto value = std::make_shared<Mesh_CurveOptmPoint_Correction_Info>();
	value->SetTolerance(tol);
	value->SetUnderRelaxation(ur);
	value->SetMaxLevel(max_lev);
	streamGoodTnbServerObject(value);
}

const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_Settings::Params::length_integ("length_integ");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_Settings::Params::iter_integ("iter_integ");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_Settings::Params::newton_solver("newton_solver");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_Settings::Params::opt_point("opt_point");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_Settings::Params::bisect_solver("bisect_solver");

const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_Settings::Params::length_max_lev_sub("length_max_lev_sub");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_Settings::Params::ignore_non_conv("ignore_non_conv");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve_Settings::Params::ur("ur");

#include <Mesh_Curve_Info.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>
#include <NumAlg_BisectionSolver_Info.hxx>

void tnbLib::Server_Mesh2dObj_Mesh_Curve_Settings::Construct(const std::string& theValue)
{
	std::shared_ptr<NumAlg_AdaptiveInteg_Info> length_integ;
	std::shared_ptr<NumAlg_AdaptiveInteg_Info> iter_integ;
	std::shared_ptr<NumAlg_NewtonSolver_Info> newton_solver;
	std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info> opt_point;
	std::shared_ptr<NumAlg_BisectionSolver_Info> bisect_solver;

	int length_max_lev_sub;
	bool ignore_non_conv;
	double ur;
	defineTnbServerParser(theValue);
	{
		loadTnbServerObject(length_integ);
	}
	{
		loadTnbServerObject(iter_integ);
	}
	{
		loadTnbServerObject(newton_solver);
	}
	{
		loadTnbServerObject(opt_point);
	}
	{
		loadTnbServerObject(bisect_solver);
	}

	{
		loadTnbServerObject(length_max_lev_sub);
	}
	{
		loadTnbServerObject(ur);
	}
	{
		loadTnbServerObject(ignore_non_conv);
	}
	try
	{
		if (!length_integ)
		{
			throw Server_Error("the length integration object is null.");
		}
		if (!iter_integ)
		{
			throw Server_Error("the iteration integration object is null.");
		}
		if (!newton_solver)
		{
			throw Server_Error("the Newton solver object is null.");
		}
		if (!opt_point)
		{
			throw Server_Error("the optimum point object is null.");
		}
		if (!bisect_solver)
		{
			throw Server_Error("the Bisect solver object is null.");
		}
		auto value = std::make_shared<Mesh_Curve_Info>();

		value->SetLengthCalcMaxLevel(length_max_lev_sub);
		value->SetUnderRelaxation(ur);
		value->SetIgnoreNonConvergency(ignore_non_conv);

		value->OverrideOverallLengthIntgInfo(length_integ);
		value->OverrideNewtonIntgInfo(iter_integ);
		value->OverrideNewtonIterInfo(newton_solver);
		value->OverrideCorrAlgInfo(opt_point);
		value->OverrideBisectAlgInfo(bisect_solver);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve::Params::curve("curve");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve::Params::metrics("metrics");
const std::string tnbLib::Server_Mesh2dObj_Mesh_Curve::Params::settings("settings");

#include <Mesh2d_Curve.hxx>
#include <Aft2d_MetricPrcsr.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>

void tnbLib::Server_Mesh2dObj_Mesh_Curve::Construct(const std::string& theValue)
{
	std::shared_ptr<Pln_Edge> curve;
	std::shared_ptr<Aft2d_MetricPrcsr> metrics;
	std::shared_ptr<Mesh_Curve_Info> settings;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(curve);
		}
		{
			loadTnbServerObject(metrics);
		}
		{
			loadTnbServerObject(settings);
		}
	}
	try
	{
		if (!curve)
		{
			throw Server_Error("the curve object is null.");
		}
		if (!metrics)
		{
			throw Server_Error("the metrics object is null.");
		}
		if (!settings)
		{
			throw Server_Error("the settings object is null.");
		}
		auto alg = std::make_shared<Mesh2d_Curve>();
		const auto& g = curve->Curve();
		alg->LoadCurve(g->Geometry(), g->FirstParameter(), g->LastParameter());
		alg->LoadMap(metrics);
		alg->LoadInfo(settings);
		alg->Perform();
		auto value = alg->Parameters();
		//std::stringstream stream;
		//boost::archive::polymorphic_text_oarchive oa(stream);
		//oa << (value);
		nlohmann::json jData;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = value;
		theStream_ << jData;
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::curve_settings("curve_settings");
const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::metric_settings("metric_settings");
const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::size_fun("size_fun");
const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::area("area");
const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::node_gen("node_gen");

#include <Aft2d_MetricPrcsr.hxx>
#include <Aft2d_Element.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Aft2d_StdOptNode.hxx>
#include <Aft2d_SolutionData.hxx>
#include <Aft2d_BoundaryOfPlane_Info.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Aft2d_PlnWire.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Mesh_Physic.hxx>
#include <Mesh2d_PlnCurve.hxx>

void tnbLib::Server_Mesh2dObj_SoluData::Construct(const std::string& theValue)
{
	std::shared_ptr<Mesh_Curve_Info> curve_settings;
	std::shared_ptr<Aft_MetricPrcsr_Info> metric_settings;
	std::shared_ptr<Geo2d_SizeFunction> size_fun;
	std::shared_ptr<Cad2d_Plane> area;
	std::string node_gen;
	defineTnbServerParser(theValue);
	{
		loadTnbServerObject(curve_settings);
	}
	{
		loadTnbServerObject(size_fun);
	}
	{
		loadTnbServerObject(metric_settings);
	}
	{
		loadTnbServerObject(area);
	}
	{
		loadTnbServerString(node_gen);
	}
	try
	{
		if (!curve_settings)
		{
			throw Server_Error("the curve settings object is null.");
		}
		if (!metric_settings)
		{
			throw Server_Error("the metric settings object is null.");
		}
		if (!size_fun)
		{
			throw Server_Error("the size function object is null.");
		}
		if (!area)
		{
			throw Server_Error("the area object is null.");
		}
		std::shared_ptr<Aft2d_OptNode_Calculator> node_gen_alg;
		if (node_gen == "standard")
		{
			node_gen_alg = std::make_shared<Aft2d_StdOptNode>();
		}
		else
		{
			std::stringstream stream;
			stream << " Unrecognized node generator has been detected. The list of the node generators are:\n"
				<< " - standard\n";
			throw Server_Error(stream.str());
		}
		auto value = std::make_shared<Aft2d_SolutionData>();
		value->LoadGlobalMetricInfo(metric_settings);
		value->LoadGlobalCurveInfo(curve_settings);

		value->LoadSizeFunction(size_fun);
		value->LoadPlane(area);
		value->LoadNodeCalculator(node_gen_alg);
		{// creating the metric processor
			auto metrics = std::make_shared<Aft2d_MetricPrcsr>(value->SizeFunction(), value->GlobalMetricInfo());
			auto b = value->Plane()->BoundingBox(0);
			metrics->SetDimSize(b.Diameter());
			value->SetMetric(metrics);
		}
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

#include <Entity2d_Triangulation.hxx>

void tnbLib::Server_Mesh2dObj_SoluData_ExportMeshToPlt::Construct(const std::string& theValue)
{
	std::shared_ptr<Aft2d_SolutionData> data;
	{
		loadNonJSONTnbServer(data);
	}
	try
	{
		auto tri = data->Mesh();
		if (!tri)
		{
			throw Server_Error("found no mesh!");
		}
		std::stringstream stream;
		tri->StreamToPlt(stream);
		nlohmann::json jData;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = stream.str();
		theStream_ << jData;
	}
	catchTnbServerErrors()
}


const std::string tnbLib::Server_Mesh2dObj_Region::Params::solu_data("solu_data");
const std::string tnbLib::Server_Mesh2dObj_Region::Params::tol("tol");

namespace tnbLib
{
	auto retrieve_max_tol(const std::shared_ptr<Cad2d_Plane>& plane, double min_tol) -> double
	{
		std::vector<std::shared_ptr<Pln_Entity>> vertices;
		plane->RetrieveCornersTo(vertices);

		auto max_tol = min_tol;
		for (const auto& x : vertices)
		{
			if (const auto vtx = std::dynamic_pointer_cast<Pln_Vertex>(x))
			{
				if (vtx->Precision() > max_tol)
				{
					max_tol = vtx->Precision();
				}
			}
		}
		return max_tol;
	}

	auto retrieve_curves(const Aft2d_RegionPlane& theRegion)
	{
		std::vector<std::shared_ptr<Aft2d_PlnWire>> wires;
		theRegion.RetrieveWiresTo(wires);
		std::map<int, std::shared_ptr<Mesh2d_PlnCurve>> curves;
		for (const auto& w : wires)
		{
			for (const auto& x : w->Curves())
			{
				auto paired = std::make_pair(x->Index(), x);
				if (NOT curves.insert(std::move(paired)).second)
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate curve no. has been detected." << endl
						<< " - id: " << x->Index() << endl
						<< abort(FatalError);
				}
			}
		}
		return std::move(curves);
	}

	void set_physics(const Cad2d_Plane& plane, const std::shared_ptr<Aft2d_RegionPlane>& theRegion)
	{
		auto curvesMap = retrieve_curves(*theRegion);
		const auto& segments = plane.Segments();
		for (const auto& x : segments->Blocks())
		{
			for (const auto& e : x.second->RetrieveEntities())
			{
				const auto& c = e->Curve();
				auto iter = curvesMap.find(c->Index());
				if (iter IS_EQUAL curvesMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "couldn't find the curve in the block." << endl
						<< " id: " << c->Index() << endl
						<< abort(FatalError);
				}
				auto physic = std::make_shared<Mesh_Physic>(0, x.first);
				iter->second->SetPhysic(std::move(physic));
			}
		}
	}
}

void tnbLib::Server_Mesh2dObj_Region::Construct(const std::string& theValue)
{
	std::shared_ptr<Aft2d_SolutionData> solu_data;
	double tol;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(solu_data);
		}
		{
			loadTnbServerObject(tol);
		}
	}
	try
	{
		if (!solu_data)
		{
			throw Server_Error("the solution data object is null.");
		}
		if (!solu_data->Plane())
		{
			throw Server_Error("no plane in the solution data has been found.");
		}
		tol = retrieve_max_tol(solu_data->Plane(), tol);

		auto info = std::make_shared<Aft2d_BoundaryOfPlane_Info>();
		info->SetMergeTolerance(tol * 1.05);
		info->SetOverrideInfo(true);

		info->OverrideGlobalCurve(solu_data->GlobalCurveInfo());
		info->OverrideGlobalMetricPrcsr(solu_data->GlobalMetricInfo());
		info->Curve() = solu_data->CurveInfo();

		solu_data->SetBoundaryInfo(info);
		{// creating the region
			auto region = Aft2d_RegionPlane::MakePlane(solu_data->Plane());
			set_physics(*solu_data->Plane(), region);

			solu_data->SetRegion(std::move(region));
		}
		streamGoodTnbServerObject(solu_data);
	}
	catchTnbServerErrors()
}

#include <Aft2d_BoundaryOfPlane.hxx>

void tnbLib::Server_Mesh2dObj_BndMesh::Construct(const std::string& theValue)
{
	std::shared_ptr<Aft2d_SolutionData> solu_data;
	{
		loadNonJSONTnbServer(solu_data);
	}
	try
	{
		if (!solu_data)
		{
			throw Server_Error("the solution data is null.");
		}
		if (!solu_data->Region())
		{
			throw Server_Error("no region has been defined!");
		}
		if (!solu_data->BoundaryInfo())
		{
			throw Server_Error("no boundary settings has been found!");
		}
		if (!solu_data->Metric())
		{
			throw Server_Error("no metrics processor has been found.");
		}
		auto bnd = std::make_shared<Aft2d_BoundaryOfPlane>(solu_data->BoundaryInfo());
		bnd->LoadMetricProcessor(solu_data->Metric());
		bnd->LoadPlane(solu_data->Region());

		bnd->Perform();
		solu_data->SetBoundaryEdges(bnd->Boundaries());
		streamGoodTnbServerObject(solu_data);
	}
	catchTnbServerErrors()
}

#include <Aft2d_StdOptNode.hxx>

void tnbLib::Server_Mesh2dObj_NodeGen_Std::Construct(const std::string& theValue)
{
	std::shared_ptr<Aft2d_OptNode_Calculator> value = std::make_shared<Aft2d_StdOptNode>();
	streamGoodTnbServerObject(value);
}


#include <Aft2d_Model.hxx>
#include <Aft_Tools.hxx>
#include <Aft2d_StdOptNode.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>
#include <MeshPost2d_LaplacianSmoothing.hxx>
#include <MeshPost2d_LaplacianSmoothing_AdjEdges.hxx>
#include <MeshPost2d_QualityMap_Vlrms2Ratio.hxx>
#include <Mesh_BndLayer_Info.hxx>

const std::string tnbLib::Server_Mesh2dObj_Mesh::Params::solu_data("solu_data");
const std::string tnbLib::Server_Mesh2dObj_Mesh::Params::node_gen("node_gen");

void tnbLib::Server_Mesh2dObj_Mesh::Construct(const std::string& theValue)
{
	std::shared_ptr<Aft2d_SolutionData> solu_data;
	std::shared_ptr<Aft2d_OptNode_Calculator> node_gen;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(solu_data);
		}
		{
			loadTnbServerObject(node_gen);
		}
	}
	try
	{
		if (!solu_data)
		{
			throw Server_Error("the solution data is null.");
		}
		if (!node_gen)
		{
			throw Server_Error("node generator object is null!");
		}
		if (!solu_data->Region())
		{
			throw Server_Error("no region has been defined!");
		}
		if (!solu_data->BoundaryInfo())
		{
			throw Server_Error("no boundary settings has been found!");
		}
		if (!solu_data->Metric())
		{
			throw Server_Error("no metrics processor has been found.");
		}
		const auto& boundaries = solu_data->BoundaryEdges();
		if (boundaries.empty())
		{
			throw Server_Error("no boundary edge has been found!");
		}
		solu_data->LoadNodeCalculator(node_gen);
		solu_data->NodeCalculator()->SetMetricMap(solu_data->Metric());
		if (!solu_data->NodeCalculator())
		{
			throw Server_Error("no node generator has been found!");
		}
		Aft_Tools::Connect(boundaries);

		auto alg = std::make_shared<Aft2d_Model>();
		alg->LoadMetricMap(solu_data->Metric());
		alg->LoadBoundaryMetricMap(solu_data->Metric());
		alg->LoadBoundaryEdges(Aft_Tools::UpCast(solu_data->BoundaryEdges()));
		alg->LoadNodeCalculator(solu_data->NodeCalculator());

		alg->Perform();
		const auto& elm_map = alg->RetrieveElements();
		std::vector<std::shared_ptr<Aft2d_Element>> elements;
		elements.reserve(elm_map.size());
		for (const auto& x: elm_map)
		{
			elements.emplace_back(x.second);
		}
		/**/
		solu_data->SetElements(std::move(elements));
		streamGoodTnbServerObject(solu_data);
	}
	catchTnbServerErrors()
}

#include <MeshPost2d_LaplacianSmoothing_AdjEdges.hxx>
#include <MeshPost2d_QualityMap_Vlrms2Ratio.hxx>
#include <MeshPost_LaplacianSmoothing_Info.hxx>

void tnbLib::Server_Mesh2dObj_Mesh_QualFun_Vlrms2Ratio::Construct(const std::string& /*theValue*/)
{
	auto value = std::make_shared<MeshPost2d_QualityMap_Vlrms2Ratio>();
	streamGoodTnbServerObject(value);
}

void tnbLib::Server_Mesh2dObj_Mesh_LaplacSmooth_AdjEdgesFun::Construct(const std::string& /*theValue*/)
{
	auto value = std::make_shared<MeshPost2d_LaplacianSmoothing_AdjEdges>();
	streamGoodTnbServerObject(value);
}


const std::string tnbLib::Server_Mesh2dObj_LaplacSmooth::Params::avg_fun("avg_fun");
const std::string tnbLib::Server_Mesh2dObj_LaplacSmooth::Params::nb_iters("nb_iters");
const std::string tnbLib::Server_Mesh2dObj_LaplacSmooth::Params::qual_fun("qual_fun");
const std::string tnbLib::Server_Mesh2dObj_LaplacSmooth::Params::solu_data("solu_data");
const std::string tnbLib::Server_Mesh2dObj_LaplacSmooth::Params::ur("ur");

void tnbLib::Server_Mesh2dObj_LaplacSmooth::Construct(const std::string& theValue)
{
	std::shared_ptr<Aft2d_SolutionData> solu_data;
	std::shared_ptr<MeshPost2d_LaplacianSmoothing_AdjEdges> avg_fun;
	std::shared_ptr<MeshPost2d_QualityMap_Vlrms2Ratio> qual_fun;
	int nb_iters;
	double ur;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(solu_data);
		}
		{
			loadTnbServerObject(avg_fun);
		}
		{
			loadTnbServerObject(qual_fun);
		}
		{
			loadTnbServerObject(nb_iters);
		}
		{
			loadTnbServerObject(ur);
		}
	}
	try
	{
		if (!solu_data)
		{
			throw Server_Error("the solution data is null.");
		}
		const auto& elements = solu_data->Elements();
		auto nodes_ref = Aft_Tools::RetrieveNodes(elements);
		auto nodes = std::make_shared<std::vector<std::shared_ptr<Aft2d_Node>>>(std::move(nodes_ref));
		if (!avg_fun)
		{
			throw Server_Error("no avg. function has been found.");
		}
		avg_fun->SetMetrics(solu_data->Metric());
		if (!qual_fun)
		{
			throw Server_Error("no qual. function has been found.");
		}
		qual_fun->SetMetrics(solu_data->Metric());

		auto info = std::make_shared<MeshPost_LaplacianSmoothing_Info>();
		info->SetNbLevels(nb_iters);
		info->SetUnderRelaxation(ur);

		auto smooth_alg = std::make_shared<MeshPost2d_LaplacianSmoothing>();
		smooth_alg->SetAvgFun(avg_fun);
		smooth_alg->SetQualityFun(qual_fun);
		smooth_alg->SetInfo(info);
		smooth_alg->SetNodes(nodes);

		smooth_alg->Perform();

		streamGoodTnbServerObject(solu_data);
	}
	catchTnbServerErrors()

	
}

const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::base_size("base_size");
const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::growth_rate("growth_rate");
const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::boundary_growth_rate("boundary_growth_rate");
const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::size_adapt_method("size_adapt_method");
const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::size_type("size_type");
const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::min_size("min_size");
const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::target_size("target_size");
const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::curvature_status("curvature_status");
const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::span_angle("span_angle");
const std::string tnbLib::Server_Mesh2dObj_RefValues::Params::area("area");

void tnbLib::Server_Mesh2dObj_RefValues::Construct(const std::string& theValue)
{
	double base_size = 0;

	std::string growth_rate;
	std::string boundary_growth_rate;
	std::string size_adapt_method;
	std::string size_type;

	double min_size = 0;
	double target_size = 0;

	std::string curvature_status;

	double span_angle = 0;

	std::shared_ptr<Cad2d_Plane> area;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(base_size);
		}
		{
			loadTnbServerString(growth_rate);
		}
		{
			loadTnbServerString(boundary_growth_rate);
		}
		{
			loadTnbServerString(size_adapt_method);
		}
		{
			loadTnbServerString(size_type);
		}
		{
			loadTnbServerObject(min_size);
		}
		{
			loadTnbServerObject(target_size);
		}
		{
			loadTnbServerString(curvature_status);
		}
		{
			loadTnbServerObject(span_angle);
		}
		{
			loadTnbServerObject(area);
		}
	}
	auto b = area->BoundingBox(0);
	auto ref = std::make_shared<Mesh2d_ReferenceValues>(base_size, std::make_shared<Entity2d_Box>(b));
	ref->SetBaseSize(base_size);

	try
	{
		if (growth_rate IS_EQUAL "verySlow")
		{
			ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::verySlow);
		}
		else if (growth_rate IS_EQUAL "slow")
		{
			ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::slow);
		}
		else if (growth_rate IS_EQUAL "moderate")
		{
			ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::moderate);
		}
		else if (growth_rate IS_EQUAL "fast")
		{
			ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::fast);
		}
		else if (growth_rate IS_EQUAL "custom")
		{
			ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::custom);
		}
		else
		{
			std::stringstream msg;
			msg
				<< "unspecified rate of the growth has been detected. valid growth rates are: \n"
				<< " - verySlow\n"
				<< " - slow\n"
				<< " - moderate\n"
				<< " - fast\n"
				<< " - custom\n"
				<< " # current value: " << growth_rate << "\n";
			throw Server_Error(msg.str());
		}

		if (boundary_growth_rate IS_EQUAL "very_slow")
		{
			ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::verySlow);
		}
		else if (boundary_growth_rate IS_EQUAL "slow")
		{
			ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::slow);
		}
		else if (boundary_growth_rate IS_EQUAL "moderate")
		{
			ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::moderate);
		}
		else if (boundary_growth_rate IS_EQUAL "fast")
		{
			ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::fast);
		}
		else if (boundary_growth_rate IS_EQUAL "custom")
		{
			ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::custom);
		}
		else
		{
			std::stringstream msg;
			msg
				<< "unspecified rate of the growth has been detected. valid growth rates are:\n"
				<< " - verySlow\n"
				<< " - slow\n"
				<< " - moderate\n"
				<< " - fast\n"
				<< " - custom\n";
			throw Server_Error(msg.str());
		}

		{
			auto& size_ref = *ref->SurfaceSizeRef();
			if (size_adapt_method IS_EQUAL "min_only")
			{
				size_ref.SetSizeMethod(Mesh_SizeMethodInfo::minOnly);
			}
			else if (size_adapt_method IS_EQUAL "min_and_target")
			{
				size_ref.SetSizeMethod(Mesh_SizeMethodInfo::minAndTerget);
			}
			else
			{
				std::stringstream msg;
				msg
					<< "Unspecified the method of the surface size value has been detected!\n"
					<< "The valid methods are:\n"
					<< " - min_only\n"
					<< " - min_and_target\n"
					<< " # current value: " << size_adapt_method << "\n";
				throw Server_Error(msg.str());
			}

			if (size_type IS_EQUAL "relative")
			{
				size_ref.SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo::relativeToBase);
			}
			else if (size_type IS_EQUAL "absolute")
			{
				size_ref.SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo::absolute);
			}
			else
			{
				std::stringstream msg;
				msg
					<< "Unspecified the method of the value has been detected!\n"
					<< "The valid methods are:\n"
					<< " - relative\n"
					<< " - absolute\n"
					<< " # Current value: " << size_type << "\n";
				throw Server_Error(msg.str());
			}

			size_ref.SetMinSize(min_size);
			size_ref.SetTargetSize(target_size);
		}
		{
			auto& curvature_values = *ref->SurfaceCurvatureRef();
			if (curvature_status IS_EQUAL "continum")
			{
				curvature_values.SetCurvatureInfo(Mesh_SurfaceCurvatureInfo::continum);
			}
			else if (curvature_status IS_EQUAL "custom")
			{
				curvature_values.SetCurvatureInfo(Mesh_SurfaceCurvatureInfo::custom);
			}
			else if (curvature_status IS_EQUAL "disable")
			{
				curvature_values.SetCurvatureInfo(Mesh_SurfaceCurvatureInfo::disable);
			}
			else
			{
				std::stringstream msg;
				msg
					<< "Unspecified the method of the curvature has been detected!\n"
					<< "The valid methods are:\n"
					<< " - continum\n"
					<< " - custom\n"
					<< " - disable\n";
				throw Server_Error(msg.str());
			}
			curvature_values.SetSpanAngle(span_angle);
		}
		streamGoodTnbServerObject(ref);
	}
	catchTnbServerErrors()

}

namespace tnbLib
{
	// Forward Declarations
	class SupEdge;

	class SupNode
		: public Global_Indexed
	{

		/*Private Data*/

		std::shared_ptr<Aft2d_Node> theNode_;
		std::shared_ptr<Aft2d_Node> theOffset_;

		std::weak_ptr<SupEdge> theBackward_;
		std::weak_ptr<SupEdge> theForward_;

	public:

		// default constructor

		SupNode()
			= default;

		// constrcutors

		SupNode(const Standard_Integer theIndex, const std::shared_ptr<Aft2d_Node>& theNode)
			: Global_Indexed(theIndex)
			, theNode_(theNode)
		{}

		// Public functions and operators

		Standard_Integer NbEdges() const;
		Standard_Boolean HasBackward() const;
		Standard_Boolean HasForward() const;
		Standard_Boolean IsManifold() const;

		Pnt2d Coord() const;

		const auto& Node() const { return theNode_; }
		const auto& Offset() const { return theOffset_; }

		const auto& Backward() const { return theBackward_; }
		const auto& Forward() const { return theForward_; }

		std::shared_ptr<SupNode> Next() const;

		void SetNode(const std::shared_ptr<Aft2d_Node>& theNode) { theNode_ = theNode; }
		void SetBackward(const std::weak_ptr<SupEdge>& theEdge) { theBackward_ = theEdge; }
		void SetForward(const std::weak_ptr<SupEdge>& theEdge) { theForward_ = theEdge; }
		void SetOffset(const std::shared_ptr<Aft2d_Node>& theNode) { theOffset_ = theNode; }
		void SetOffset(std::shared_ptr<Aft2d_Node>&& theNode) { theOffset_ = std::move(theNode); }

	};

	class SupEdge
		: public Global_Indexed
	{

		/*Private Data*/

		std::shared_ptr<Aft2d_SegmentEdge> theEdge_;
		std::shared_ptr<Aft2d_SegmentEdge> theOffset_;

		std::shared_ptr<SupNode> theNode0_;
		std::shared_ptr<SupNode> theNode1_;

	public:

		// default constructor

		SupEdge()
			= default;

		// constructors

		SupEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SupNode>& theNode0,
			const std::shared_ptr<SupNode>& theNode1
		)
			: Global_Indexed(theIndex)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
		{}

		// Public functions and operators

		const auto& Node0() const { return theNode0_; }
		const auto& Node1() const { return theNode1_; }

		const auto& Edge() const { return theEdge_; }
		const auto& Offset() const { return theOffset_; }

		void SetEdge(const std::shared_ptr<Aft2d_SegmentEdge>& theEdge) { theEdge_ = theEdge; }
		void SetOffset(const std::shared_ptr<Aft2d_SegmentEdge>& theEdge) { theOffset_ = theEdge; }
		void SetOffset(std::shared_ptr<Aft2d_SegmentEdge>&& theEdge) { theOffset_ = std::move(theEdge); }

	};

	template<class EdgeType>
	struct EdgeSet
	{
		std::vector<std::shared_ptr<EdgeType>> edges;
	};

	template<class EdgeType>
	struct WireSet
	{
		std::vector<std::shared_ptr<EdgeType>> edges;
	};



	namespace tools
	{

		std::vector<std::shared_ptr<Aft2d_Node>>
			RetrieveNodes(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&);
		std::vector<std::shared_ptr<SupEdge>>
			RetrieveSupEdges(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&);
		std::shared_ptr<Entity2d_Polygon> RetrievePolygon(const std::vector<std::shared_ptr<SupEdge>>&);
		std::vector<std::shared_ptr<SupNode>> RetrieveNodes(const std::vector<std::shared_ptr<SupEdge>>&);
		std::vector<std::shared_ptr<SupNode>> TrackNodes(const std::shared_ptr<SupNode>&);

		std::map<Standard_Integer, std::shared_ptr<EdgeSet<Aft2d_SegmentEdge>>>
			RetrieveBoundaries(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&);

		std::vector<std::shared_ptr<WireSet<SupEdge>>> RetrieveWires(const std::map<Standard_Integer, std::shared_ptr<EdgeSet<Aft2d_SegmentEdge>>>&, const std::vector<Standard_Integer>& theIds);
		std::vector<std::shared_ptr<WireSet<SupEdge>>> RetrieveWires(const std::vector<std::shared_ptr<SupEdge>>&);

		std::shared_ptr<Entity2d_Polygon> ClosePolygon(const Entity2d_Polygon&);
		std::shared_ptr<Entity2d_Polygon> RetrievePolygon(const WireSet<SupEdge>&);
		std::vector<std::shared_ptr<Entity2d_Polygon>> RetrieveInnerPolygons(const std::vector<std::shared_ptr<WireSet<SupEdge>>>&);

		std::vector<std::shared_ptr<Aft2d_SegmentEdge>> CreateEdges(const Entity2d_Polygon&);

		void CheckWire(const std::vector<std::shared_ptr<SupEdge>>&);

	}

	namespace bndLayer
	{

		std::pair<std::vector<std::shared_ptr<Aft2d_SegmentEdge>>, std::shared_ptr<Entity2d_QuadMesh>>
			CalcBndLayer(const std::vector<std::shared_ptr<SupEdge>>&, const Mesh_BndLayer_Info& theInfo);

		void SetOffsets(const std::vector<std::shared_ptr<SupNode>>&, const Entity2d_Polygon&);
		void CalcOffsetEdges(const std::vector<std::shared_ptr<SupEdge>>&);
	}
}

#include <Aft2d_Element.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_SegmentNode.hxx>
#include <Aft2d_Node.hxx>
#include <Mesh_PlnCurve.hxx>
#include <MeshBLayer2d_Offset.hxx>
#include <Geo2d_OffsetPolygon_Exterior.hxx>
#include <Global_Tools.hxx>

#ifdef Handle
#undef Handle
#endif
#include <Entity2d_PolygonTools.hxx>

#include <set>

std::vector<std::shared_ptr<tnbLib::Aft2d_Node>>
tnbLib::tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>>& theEdges
)
{
	static auto cmp = [](const std::shared_ptr<Aft2d_Node>& n0, const std::shared_ptr<Aft2d_Node>& n1)
	{
		return n0->Index() < n1->Index();
	};
	std::set<std::shared_ptr<Aft2d_Node>, decltype(cmp)> comp_nodes(cmp);
	for (const auto& x : theEdges)
	{
		comp_nodes.insert(x->Node0());
		comp_nodes.insert(x->Node1());
	}
	std::vector<std::shared_ptr<Aft2d_Node>> nodes;
	std::copy(comp_nodes.begin(), comp_nodes.end(), std::back_inserter(nodes));
	std::sort
	(
		nodes.begin(),
		nodes.end(),
		[](
			const std::shared_ptr<Aft2d_Node>& n0,
			const std::shared_ptr<Aft2d_Node>& n1
			) {return n0->Index() < n1->Index(); }
	);
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::SupEdge>>
tnbLib::tools::RetrieveSupEdges
(
	const std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>>& theEdges
)
{
	// retrieving the nodes
	const auto nodes = RetrieveNodes(theEdges);
	std::map<Standard_Integer, std::shared_ptr<SupNode>> sup_nodes;
	// Creating the super nodes
	for (const auto& x : nodes)
	{
		auto node = std::make_shared<SupNode>(x->Index(), x);
		Global_Tools::InsertIgnoreDup(node->Index(), node, sup_nodes);
	}
	std::vector<std::shared_ptr<SupEdge>> sup_edges;
	// Creating the super edges
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		auto edge =
			std::make_shared<SupEdge>
			(
				x->Index(),
				sup_nodes.at(n0->Index()),
				sup_nodes.at(n1->Index())
			);
		sup_nodes.at(n0->Index())->SetForward(edge);
		sup_nodes.at(n1->Index())->SetBackward(edge);
		sup_edges.emplace_back(std::move(edge));
	}
	return std::move(sup_edges);
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::tools::RetrievePolygon
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges
)
{
	const auto start = FirstItem(theEdges)->Node0();
	Debug_Null_Pointer(start);
	const auto nodes = TrackNodes(start);
	if (nodes.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid polygon." << endl
			<< abort(FatalError);
	}
	std::vector<Pnt2d> coords;
	coords.reserve(nodes.size() + 1);
	for (size_t i = 0; i < nodes.size(); i++)
	{
		coords.emplace_back(nodes.at(i)->Coord());
	}
	coords.emplace_back(FirstItem(nodes)->Coord());
	auto poly = std::make_shared<Entity2d_Polygon>
		(std::move(coords), 0);
	return std::move(poly);
}

std::vector<std::shared_ptr<tnbLib::SupNode>>
tnbLib::tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges
)
{
	const auto start = FirstItem(theEdges)->Node0();
	Debug_Null_Pointer(start);
	const auto nodes = TrackNodes(start);
	if (nodes.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid polygon." << endl
			<< abort(FatalError);
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::SupNode>>
tnbLib::tools::TrackNodes
(
	const std::shared_ptr<SupNode>& theNode
)
{
	std::vector<std::shared_ptr<SupNode>> nodes;
	auto start = theNode;
	nodes.emplace_back(start);
	auto next = start->Next();
	while (next NOT_EQUAL start)
	{
		nodes.emplace_back(next);
		next = next->Next();
		if (NOT next)
		{
			break;
		}
	}
	return std::move(nodes);
}

std::map<Standard_Integer, std::shared_ptr<tnbLib::EdgeSet<tnbLib::Aft2d_SegmentEdge>>>
tnbLib::tools::RetrieveBoundaries(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>& theEdges)
{
	std::map<Standard_Integer, std::shared_ptr<EdgeSet<Aft2d_SegmentEdge>>> comp_edges;
	for (const auto& x : theEdges)
	{
		const auto curve = x->Curve().lock();
		if (NOT curve)
		{
			FatalErrorIn(FunctionSIG)
				<< "No curve has been assigned to the edge." << endl
				<< abort(FatalError);
		}
		const auto curve_id = curve->Index();
		if (auto iter = comp_edges.find(curve_id); iter IS_EQUAL comp_edges.end())
		{
			auto new_set = std::make_shared<EdgeSet<Aft2d_SegmentEdge>>();
			comp_edges.insert({ curve_id,std::move(new_set) });
		}
		comp_edges.at(curve_id)->edges.emplace_back(x);
	}
	return std::move(comp_edges);
}

std::vector<std::shared_ptr<tnbLib::WireSet<tnbLib::SupEdge>>>
tnbLib::tools::RetrieveWires
(
	const std::map<Standard_Integer, std::shared_ptr<EdgeSet<Aft2d_SegmentEdge>>>& theEdges,
	const std::vector<Standard_Integer>& theIds
)
{
	std::vector<std::shared_ptr<Aft2d_SegmentEdge>> edges;
	for (const auto id : theIds)
	{
		const auto& selected = theEdges.at(id);
		for (const auto& x : selected->edges)
		{
			edges.emplace_back(x);
		}
	}
	// with the helps of the super edge concept I can be able to identify the wires
	const auto sup_edges = tools::RetrieveSupEdges(edges);
	// retrieve the wires
	const auto wires = RetrieveWires(sup_edges);
	/*
	 * Now we need to identify the inner wires
	 */
	std::vector<std::shared_ptr<WireSet<SupEdge>>> inner_wires;
	for (const auto& x : wires)
	{
		Debug_Null_Pointer(x);
		auto poly = RetrievePolygon(*x);
		if (Entity2d_PolygonTools::GetOrientation(*poly) IS_EQUAL Entity2d_PolygonOrientation::cw)
		{
			inner_wires.emplace_back(x);
		}
	}
	/*
	 * NOW, the inner wires have been identified
	 */
	return std::move(inner_wires);
}

std::vector<std::shared_ptr<tnbLib::WireSet<tnbLib::SupEdge>>>
tnbLib::tools::RetrieveWires
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges
)
{
	static auto cmp = [](const std::shared_ptr<SupEdge>& e0, const std::shared_ptr<SupEdge>& e1)
	{
		return e0->Index() < e1->Index();
	};
	std::set<std::shared_ptr<SupEdge>, decltype(cmp)> compare(cmp);
	for (const auto& x : theEdges)
	{
		compare.insert(x);
	}
	std::vector<std::shared_ptr<WireSet<SupEdge>>> wires;
	while (compare.size())
	{
		const auto edge = *compare.begin();
		auto start = edge->Node0();
		auto prev = start;
		auto next = start->Next();
		std::vector<std::shared_ptr<SupEdge>> sup_edges;
		Standard_Boolean is_wire = Standard_True;
		while (next NOT_EQUAL start)
		{
			sup_edges.emplace_back(prev->Forward().lock());
			if (NOT compare.erase(prev->Forward().lock()))
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "something went wrong: the item is not in the tree." << endl
					<< abort(FatalError);
			}
			prev = next;
			next = next->Next();
			if (NOT next)
			{
				is_wire = Standard_False;
				break;
			}
		}
		if (next)
		{
			sup_edges.emplace_back(prev->Forward().lock());
			if (NOT compare.erase(prev->Forward().lock()))
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "something went wrong: the item is not in the tree." << endl
					<< abort(FatalError);
			}
		}
		if (is_wire)
		{
			auto wire_set_ref = WireSet<SupEdge>{ std::move(sup_edges) };
			auto wire_set = std::make_shared<WireSet<SupEdge>>(std::move(wire_set_ref));
			wires.emplace_back(std::move(wire_set));
		}
	}
	return std::move(wires);
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::tools::ClosePolygon(const Entity2d_Polygon& thePolygon)
{
	std::vector<Pnt2d> coords;
	coords.reserve(thePolygon.NbPoints() + 1);
	for (const auto& x : thePolygon.Points())
	{
		coords.emplace_back(x);
	}
	coords.emplace_back(coords.at(0));
	auto poly = std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
	return std::move(poly);
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::tools::RetrievePolygon
(
	const WireSet<SupEdge>& theWire
)
{
	std::vector<Pnt2d> coords;
	for (const auto& x : theWire.edges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		Debug_Null_Pointer(n0);
		coords.emplace_back(n0->Coord());
	}
	auto poly = std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
	return std::move(poly);
}

std::vector<std::shared_ptr<tnbLib::Entity2d_Polygon>>
tnbLib::tools::RetrieveInnerPolygons
(
	const std::vector<std::shared_ptr<WireSet<SupEdge>>>& theWires
)
{
	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		auto poly = RetrievePolygon(*x);
		if (Entity2d_PolygonTools::GetOrientation(*poly) IS_EQUAL Entity2d_PolygonOrientation::cw)
		{
			polygons.emplace_back(std::move(poly));
		}
	}
	return std::move(polygons);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>>
tnbLib::tools::CreateEdges(const Entity2d_Polygon& thePolygon)
{
	std::vector<std::shared_ptr<Aft2d_Node>> nodes;
	Standard_Integer nb_nodes = 0;
	const auto& coords = thePolygon.Points();
	for (size_t i = 0; i < coords.size() - 1; i++)
	{
		auto node = std::make_shared<Aft2d_SegmentNode>(++nb_nodes, coords.at(i));
		nodes.emplace_back(std::move(node));
	}
	nodes.emplace_back(FirstItem(nodes));
	Standard_Integer nb_edges = 0;
	std::vector<std::shared_ptr<Aft2d_SegmentEdge>> edges;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& node0 = nodes.at(i - 1);
		const auto& node1 = nodes.at(i);
		auto segment =
			std::make_shared<Aft2d_SegmentEdge>
			(++nb_edges, node0, node1);
		edges.emplace_back(std::move(segment));
	}
	return std::move(edges);
}


void tnbLib::tools::CheckWire
(
	const std::vector<std::shared_ptr<tnbLib::SupEdge>>& theEdges
)
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		if (NOT n0->IsManifold())
		{
			FatalErrorIn(FunctionSIG)
				<< "the node is not manifold." << endl
				<< abort(FatalError);
		}
		if (NOT n1->IsManifold())
		{
			FatalErrorIn(FunctionSIG)
				<< "the node is not manifold." << endl
				<< abort(FatalError);
		}
	}
}

Standard_Integer
tnbLib::SupNode::NbEdges() const
{
	Standard_Integer nb_edges = 0;
	if (HasBackward()) nb_edges++;
	if (HasForward()) nb_edges++;
	return nb_edges;
}

Standard_Boolean
tnbLib::SupNode::HasBackward() const
{
	return static_cast<Standard_Boolean>(theBackward_.lock());
}

Standard_Boolean
tnbLib::SupNode::HasForward() const
{
	return static_cast<Standard_Boolean>(theForward_.lock());
}

Standard_Boolean
tnbLib::SupNode::IsManifold() const
{
	return NbEdges() == 2;
}

tnbLib::Pnt2d
tnbLib::SupNode::Coord() const
{
	Debug_Null_Pointer(Node());
	return Node()->Coord();
}

std::shared_ptr<tnbLib::SupNode>
tnbLib::SupNode::Next() const
{
	if (const auto x = Forward().lock())
	{
		return x->Node1();
	}
	return nullptr;
}

std::pair
<
	std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>>,
	std::shared_ptr<tnbLib::Entity2d_QuadMesh>
>
tnbLib::bndLayer::CalcBndLayer
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges,
	const Mesh_BndLayer_Info& theInfo
)
{
	// retrieving the polygon
	const auto polygon = tools::RetrievePolygon(theEdges);
	const auto nodes = tools::RetrieveNodes(theEdges);
	/*
	 * We need to reverse the polygon due to the fact that the offseting algorithm
	 * needs the polygon to be counter clockwise and we alredy know that an inner polygon is
	 * clockwise.
	 */
	polygon->Reverse(); // the polygon is reversed here.
	std::vector<std::shared_ptr<Entity2d_Polygon>> offsets;
	{
		const auto alg =
			std::make_shared<Geo2d_OffsetPolygon_Exterior>
			(polygon, theInfo.OuterLayerThick());
		alg->Perform();
		offsets = alg->Offsets();
	}
	if (offsets.size() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Unable to create boundary layer: Invalid type of boundary layer has been detected." << endl
			<< abort(FatalError);
	}
	/*
	 * according to the algorithm the second one should be the offset polygon.
	 */
	const auto offset = offsets.at(1);
	polygon->Reverse();
	offset->Reverse(); // We need to reverse it back.
	/*
	 * Calculating the offset nodes
	 */
	SetOffsets(nodes, *offset);
	//CalcOffsetEdges(theEdges);
	std::shared_ptr<Entity2d_QuadMesh> mesh;
	{
		const auto alg = std::make_shared<MeshBLayer2d_Offset>();
		alg->SetClusterSize(theInfo.NbLayars());
		alg->SetRate(theInfo.GrowthRate());
		alg->SetPolygon(polygon);
		alg->SetOffset(offset);
		alg->Perform();
		mesh = alg->Mesh();
	}
	return { tools::CreateEdges(*offset), mesh };
}

void tnbLib::bndLayer::SetOffsets
(
	const std::vector<std::shared_ptr<SupNode>>& theNodes,
	const Entity2d_Polygon& thePoly
)
{
	const auto& pnts = thePoly.Points();
	for (size_t i = 0; i < theNodes.size(); i++)
	{
		const auto& x = theNodes.at(i);
		x->Node()->SetCoord(pnts.at(i));
		//auto node = std::make_shared<Aft2d_SegmentNode>(x->Index(), pnts.at(i));
		//x->SetOffset(std::move(node));
	}
}

void tnbLib::bndLayer::CalcOffsetEdges
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges
)
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		auto seg =
			std::make_shared<Aft2d_SegmentEdge>
			(x->Index(), n0->Offset(), n1->Offset());
		x->SetOffset(std::move(seg));
	}
}

#include <MeshBLayer2d_Offset.hxx>
#include <Merge2d_QuadMesh.hxx>

implementTnbServerParam(Server_Mesh2dObj_BndLayer_F1, solu_data, "solu_data");
implementTnbServerParam(Server_Mesh2dObj_BndLayer_F1, thick, "thick");
implementTnbServerParam(Server_Mesh2dObj_BndLayer_F1, curves, "curves");
implementTnbServerParam(Server_Mesh2dObj_BndLayer_F1, rate, "rate");
implementTnbServerParam(Server_Mesh2dObj_BndLayer_F1, cluster_size, "cluster_size");

void tnbLib::Server_Mesh2dObj_BndLayer_F1::Construct(const std::string& theValue)
{
	std::shared_ptr<Aft2d_SolutionData> solu_data;
	double thick;
	std::vector<int> curves;
	double rate;
	int cluster_size;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(solu_data);
		}
		{
			loadTnbServerObject(thick);
		}
		{
			loadTnbServerObject(rate);
		}
		{
			loadTnbServerObject(cluster_size);
		}
		{
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::curves).get<std::string>());
			if (json_array.is_array())
			{
				for (const auto& element : json_array) {
					curves.emplace_back(element.get<int>());
				}
			}
			else
			{
				throw Server_Error("Couldn't load the volume list");
			}
		}
	}
	try
	{
		auto boundaries = solu_data->BoundaryEdges();
		const auto& metrics = solu_data->Metric();
		if (NOT metrics)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "No metric processor has been found." << endl
				<< abort(FatalError);
		}
		const auto& bnd_info = solu_data->GlobalBndLayerInfo();
		const auto myInfo = std::make_shared<Mesh_BndLayer_Info>();
		//myInfo->SetFirstLayerThick(myThick);
		myInfo->SetGrowthRate(rate);
		myInfo->SetNbLayers(cluster_size);
		myInfo->SetOuterLayerThick(thick);
		if (boundaries.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no boundary edge has been detected!" << endl
				<< abort(FatalError);
		}
		//const auto& bnd_layer_list = soluData->BndLayerList();
		if (!curves.empty())
		{
			std::vector<std::shared_ptr<Entity2d_QuadMesh>> meshes;
			/*
			 * Retrieving the boundary map
			 */
			const auto bnd_sets = tools::RetrieveBoundaries(boundaries);
			/*
			 * Getting the inner wires
			 */
			const auto wires = tools::RetrieveWires(bnd_sets, curves);
			for (const auto& x : wires)
			{// for every wire on the list we need to create a bounady layer mesh.
				/*
				 * Check the wire if it's closed
				 * The new offset edges will be saved on the super edges.
				 */
				tools::CheckWire(x->edges);
				auto [outer_layer, mesh] =
					bndLayer::CalcBndLayer(x->edges, *myInfo);
				const auto merge_alg = std::make_shared<Merge2d_QuadMesh>();
				merge_alg->Import(*mesh);
				merge_alg->Perform();
				mesh = merge_alg->Merged();
				meshes.emplace_back(std::move(mesh));
				/*
				 * The new offset edges has been saved on the super edges.
				 * We just need to replace the boundary layer edges with the offset ones.
				 * Both of them have been saved on the super edge.
				 */
				{// replacing the boundary layer edges
					std::map<int, std::shared_ptr<SupEdge>> sup_map;
					for (const auto& e : x->edges)
					{
						Global_Tools::InsertIgnoreDup(e->Index(), e, sup_map);
					}
					for (auto& bnd : boundaries)
					{
						if (auto iter = sup_map.find(bnd->Index()); iter NOT_EQUAL sup_map.end())
						{
							//bnd = iter->second->Edge();
							const auto& n0 = bnd->Node0();
							const auto& n1 = bnd->Node1();
							bnd->SetCharLength(metrics->CalcDistance(n0->Coord(), n1->Coord()));
							bnd->SetCentre(MEAN(n0->Coord(), n1->Coord()));
						}
					}
				}
			}
			solu_data->SetBndlayerMeshes(meshes);
			solu_data->SetBoundaryEdges(std::move(boundaries));
		}
		else
		{
			Info << WarningIn(FunctionSIG) << endl
				<< " No boundary curve has been selected." << endl;
		}
		streamGoodTnbServerObject(solu_data);
	}
	catchTnbServerErrors()
}

#include <MeshIO2d_FEA.hxx>
#include <Entity2d_CmpMesh.hxx>

namespace tnbLib
{

	struct Node
	{
		typedef Pnt2d ptType;
		int id;
		Pnt2d coord;
	};

	void find_physics
	(
		const std::shared_ptr<Entity2d_CmpMesh>& myMesh,
		const std::map<word, std::vector<std::shared_ptr<Entity2d_Polygon>>>& theMap,
		std::map<word, std::shared_ptr<std::vector<connectivity::dual>>>& myPhysics
	)
	{
		auto b = myMesh->CalcBoundingBox();
		Geo_AdTree<std::shared_ptr<Node>> engine;
		engine.SetGeometryRegion(b->Expanded(b->Diameter() * 0.15));
		engine.SetGeometryCoordFunc([](const std::shared_ptr<Node>& x)-> const auto& {return x->coord; });
		int k = 0;
		for (const auto& x : myMesh->Coords())
		{
			auto node = std::make_shared<Node>(Node{ ++k,x });
			engine.InsertToGeometry(node);
		}

		for (const auto& x : theMap)
		{
			auto physic = x.first;
			std::vector<connectivity::dual> indices;
			for (const auto& poly : x.second)
			{
				const auto& pnts = poly->Points();
				for (size_t i = 1; i < pnts.size(); i++)
				{
					const auto& p0 = pnts.at(i - 1);
					const auto& p1 = pnts.at(i);

					int i0, i1;
					{
						auto bi = Entity2d_Box::Box(p0, 1.0E-6);
						std::vector<std::shared_ptr<Node>> items;
						engine.GeometrySearch(bi, items);
						std::shared_ptr<Node> node;
						double min_dist = RealLast();
						for (const auto& it : items)
						{
							auto dist = p0.Distance(it->coord);
							if (dist < min_dist)
							{
								min_dist = dist;
							}
							if (dist <= 1.0E-10)
							{
								node = it;
								break;
							}
						}
						if (NOT node)
						{
							FatalErrorIn(FunctionSIG)
								<< "contradictory data between the boundary mesh and the mesh has been detected." << endl
								<< " min distance = " << min_dist << endl
								<< abort(FatalError);
						}
						i0 = node->id;
					}
					{
						auto bi = Entity2d_Box::Box(p1, 1.0E-6);
						std::vector<std::shared_ptr<Node>> items;
						engine.GeometrySearch(bi, items);
						std::shared_ptr<Node> node;
						for (const auto& it : items)
						{
							if (p1.Distance(it->coord) <= 1.0E-10)
							{
								node = it;
								break;
							}
						}
						if (NOT node)
						{
							FatalErrorIn(FunctionSIG)
								<< "contradictory data between the boundary mesh and the mesh has been detected." << endl
								<< abort(FatalError);
						}
						i1 = node->id;
					}

					connectivity::dual d;
					d.Value(0) = i0;
					d.Value(1) = i1;

					indices.push_back(std::move(d));
				}
			}
			auto paired = std::make_pair(physic, std::make_shared<std::vector<connectivity::dual>>(std::move(indices)));
			myPhysics.insert(std::move(paired));
		}
	}
}

void tnbLib::Server_Mesh2dObj_ExportToFEA::Construct(const std::string& theValue)
{
	std::shared_ptr<Aft2d_SolutionData> data;
	{
		loadNonJSONTnbServer(data);
	}
	try
	{
		std::map<word, std::shared_ptr<std::vector<connectivity::dual>>> myPhysics;
		std::map<word, std::vector<std::shared_ptr<Entity2d_Polygon>>> physicMap;
		const auto& elements = data->Elements();
		if (elements.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no element has been detected!" << endl
				<< abort(FatalError);
		}
		auto mesh = std::make_shared<Entity2d_CmpMesh>();
		if (!data->BndLayerMeshes().empty()) // check if there is any boundary layer mesh
		{
			const auto& bnd_meshes = data->BndLayerMeshes();
			for (const auto& bnd : bnd_meshes)
			{
				mesh->Add(*bnd);
			}
		}
		{
			const auto tri_mesh = Aft_Tools::RetrieveTriangleMesh(elements);
			mesh->Add(*tri_mesh);
		}
		Entity2d_CmpMesh::Merge(*mesh);
		Entity2d_CmpMesh::CheckInverseElements(*mesh);

		const auto& region = data->Region();
		std::vector<std::shared_ptr<Aft2d_PlnWire>> wires;
		region->RetrieveWiresTo(wires);

		for (const auto& w : wires)
		{
			//std::cout << "nb of curves = " << w->NbCurves() << std::endl;
			//int k = 0;
			for (const auto& c : w->Curves())
			{
				//std::cout << " - k = " << k++ << std::endl;
				const auto& bmesh = c->GetMesh();
				if (NOT bmesh)
				{
					FatalErrorIn(FunctionSIG)
						<< "the curve has no mesh." << endl
						<< " - Name: " << c->Curve()->Name() << endl
						<< " - id: " << c->Index() << endl
						//<< " - first = " << c->Curve()->FirstCoord() << endl
						//<< " - last = " << c->Curve()->LastCoord() << endl
						<< abort(FatalError);
				}
				auto physic = c->Physic()->Name();
				auto iter = physicMap.find(physic);
				if (iter IS_EQUAL physicMap.end())
				{
					auto paired = std::make_pair(physic, std::vector<std::shared_ptr<Entity2d_Polygon>>());
					physicMap.insert(std::move(paired));
				}
				physicMap.at(physic).push_back(bmesh);
			}
		}
		auto nodes = Aft_Tools::RetrieveNodes(data->Elements());
		std::vector<std::shared_ptr<Aft2d_Node>> bnodes;
		for (const auto& x : nodes)
		{
			if (x->IsBoundary())
			{
				bnodes.push_back(x);
			}
		}

		find_physics(mesh, physicMap, myPhysics);
		auto fea = std::make_shared<MeshIO2d_FEA>();
		fea->SetMesh(mesh);
		fea->SetBoundaries(myPhysics);

		streamGoodTnbServerObject(fea);
	}
	catchTnbServerErrors()
}

#include <MeshPost2d_OFTopology.hxx>
#include <MeshPost_Extrude.hxx>
#include <Geo3d_FVMesh.hxx>

implementTnbServerParam(Server_Mesh2dObj_Extrude_FEA, fea_mesh, "fea_mesh");
implementTnbServerParam(Server_Mesh2dObj_Extrude_FEA, extrusion, "extrusion");
implementTnbServerParam(Server_Mesh2dObj_Extrude_FEA, title, "title");

implementTnbServerConstruction(Server_Mesh2dObj_Extrude_FEA)
{
	std::shared_ptr<MeshIO2d_FEA> fea_mesh;
	double extrusion;
	std::string title;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(fea_mesh);
		}
		{
			loadTnbServerObject(extrusion);
		}
		{
			loadTnbServerString(title);
		}
	}
	try
	{
		const auto topology = std::make_shared<MeshPost2d_OFTopology>();
		topology->SetMeshIO(fea_mesh);
		topology->Perform();

		const auto convertor = std::make_shared<MeshPost_Extrude>();
		convertor->SetMesh2d(topology);
		convertor->SetTitle(title);
		convertor->SetValue(extrusion);
		convertor->Perform();

		auto fv = convertor->RetrieveIO();
		streamGoodTnbServerObject(fv);
	}
	catchTnbServerErrors()
}