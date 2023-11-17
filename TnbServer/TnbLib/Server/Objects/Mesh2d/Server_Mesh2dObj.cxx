#include <Aft2d_MetricPrcsrFwd.hxx>
#include <Server_Mesh2dObj.hxx>

#include <Aft_MetricPrcsr_Info.hxx>
#include <Mesh2d_ReferenceValues.hxx>
#include <Cad2d_Plane.hxx>
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
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::curve_settings("curve_settings");
const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::metric_settings("metric_settings");
const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::size_fun("size_fun");
const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::area("area");
const std::string tnbLib::Server_Mesh2dObj_SoluData::Params::node_gen("node_gen");

#include <Aft2d_Element.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Aft2d_StdOptNode.hxx>
#include <Aft2d_SolutionData.hxx>

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

		streamGoodTnbServerObject(value);
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
				<< " - custom\n";
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
					<< " - minOnly\n"
					<< " - minAndTarget\n";
				throw Server_Error(msg.str());
			}

			if (size_type IS_EQUAL "relative_to_base")
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
					<< " - relativeToBase\n"
					<< " - absolute\n";
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
