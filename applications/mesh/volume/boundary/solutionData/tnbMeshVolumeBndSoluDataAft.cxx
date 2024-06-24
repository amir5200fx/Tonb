#include <Aft3d_SolutionData_SurfVol.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <Cad_Volume.hxx>
#include <Geo_SizeFunction.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>

namespace tnbLib
{
	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_EXETAG_OBJ;

	TNB_SET_VERBOSE_FUN;

	static std::shared_ptr<Geo3d_SizeFunction> my_size_fun;
	static std::shared_ptr<Cad_Volume> my_volume;

	static auto my_curve_info = std::make_shared<Mesh_Curve_Info>();
	static auto my_metric_info = std::make_shared<Aft_MetricPrcsrAnIso_Info>();

	static int CURVE_CONFIG_OVERALL_LEN_MAX_NB_ITERS = 500;
	static int CURVE_CONFIG_OVERALL_LEN_NB_INIT_ITERS = 10;
	static double CURVE_CONFIG_OVERALL_LEN_TOL = 1.E-6;

	static int CURVE_CONFIG_INTEG_MAX_NB_ITERS = 50;
	static int CURVE_CONFIG_INTEG_NB_INIT = 4;
	static double CURVE_CONFIG_INTEG_TOL = 1.E-4;

	static int CURVE_CONFIG_ITER_MAX_NB_ITERS = 50;
	static double CURVE_CONFIG_ITER_SMALL = 1.E-6;
	static double CURVE_CONFIG_ITER_ZERO = 1.E-8;
	static double CURVE_CONFIG_ITER_TOL = 1.E-4;
	static double CURVE_CONFIG_ITER_UR = 0.85;

	static int CURVE_CONFIG_CORR_MAX_LEV = 5;
	static double CURVE_CONFIG_CORR_TOL = 1.E-3;
	static double CURVE_CONFIG_CORR_UR = 0.85;


	static double METRIC_CONFIG_TOL = 0.005;
	static int METRIC_CONFIG_NB_ITERS = 4;
	static int METRIC_CONFIG_NB_SAMPLES = 3;

	static int METRIC_CONFIG_INTEG_MAX_NB_ITERS = 40;
	static double METRIC_CONFIG_INTEG_TOL = 1.E-4;
	static int METRIC_CONFIG_INTEG_INIT_ITERS = 4;


	RunTimeConfigs(Mesh_Curve_Info);
	SetRunTimeConfigs(Mesh_Curve_Info)
	{
		const auto& obj = my_curve_info;
		const auto& overall_len = obj->OverallLengthIntgInfo();
		const auto& integ = obj->NewtonIntgInfo();
		const auto& iter = obj->NewtonIterInfo();
		const auto& corr = obj->CorrAlgInfo();

		overall_len->SetMaxNbIterations(CURVE_CONFIG_OVERALL_LEN_MAX_NB_ITERS);
		overall_len->SetNbInitIterations(CURVE_CONFIG_OVERALL_LEN_NB_INIT_ITERS);
		overall_len->SetTolerance(CURVE_CONFIG_OVERALL_LEN_TOL);

		integ->SetMaxNbIterations(CURVE_CONFIG_INTEG_MAX_NB_ITERS);
		integ->SetNbInitIterations(CURVE_CONFIG_INTEG_NB_INIT);
		integ->SetTolerance(CURVE_CONFIG_INTEG_TOL);

		iter->SetMaxIterations(CURVE_CONFIG_ITER_MAX_NB_ITERS);
		iter->SetSmall(CURVE_CONFIG_ITER_SMALL);
		iter->SetZero(CURVE_CONFIG_ITER_ZERO);
		iter->SetTolerance(CURVE_CONFIG_ITER_TOL);
		iter->SetUnderRelaxation(CURVE_CONFIG_ITER_UR);

		corr->SetMaxLevel(CURVE_CONFIG_CORR_MAX_LEV);
		corr->SetTolerance(CURVE_CONFIG_CORR_TOL);
		corr->SetUnderRelaxation(CURVE_CONFIG_CORR_UR);
	}

	RunTimeConfigs(MetricPrcsrAnIso_Info);
	SetRunTimeConfigs(MetricPrcsrAnIso_Info)
	{
		my_metric_info->SetTolerance(METRIC_CONFIG_TOL);
		my_metric_info->SetNbIters(METRIC_CONFIG_NB_ITERS);
		my_metric_info->SetNbSamples(METRIC_CONFIG_NB_SAMPLES);

		my_metric_info->OverrideIntegInfo(std::make_shared<NumAlg_AdaptiveInteg_Info>());

		const auto& integ = my_metric_info->IntegInfo();
		integ->SetMaxNbIterations(METRIC_CONFIG_INTEG_MAX_NB_ITERS);
		integ->SetTolerance(METRIC_CONFIG_INTEG_TOL);
		integ->SetNbInitIterations(METRIC_CONFIG_INTEG_INIT_ITERS);
	}

	auto get_curve_info()
	{
		return my_curve_info;
	}

	struct OverallLenCalcConfig
	{
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> config;
	};

	struct IntegConfig
	{
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> config;
	};

	struct IterConfig
	{
		std::shared_ptr<NumAlg_NewtonSolver_Info> config;
	};

	struct MetricConfig
	{
		std::shared_ptr<Aft_MetricPrcsrAnIso_Info> config;
	};

	struct CorrConfig
	{
		std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info> config;
	};

	struct MetricIntegConfig
	{
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> config;
	};

	auto get_metric_info()
	{
		return MetricConfig{ my_metric_info };
	}

	auto get_overall_len(const std::shared_ptr<Mesh_Curve_Info>& info)
	{
		return OverallLenCalcConfig{ info->OverallLengthIntgInfo() };
	}

	auto get_integ_config(const MetricConfig& config)
	{
		return MetricIntegConfig{ config.config->IntegInfo() };
	}

	void set_max_nb_iterations(const OverallLenCalcConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - OverallLenConfig.MAX_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetMaxNbIterations(n);
	}

	void set_nb_init_iters(const OverallLenCalcConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - OverallLenConfig.NB_INIT_ITERS is set to: " << n << "\n";
		}
		config.config->SetNbInitIterations(n);
	}

	void set_tol(const OverallLenCalcConfig& config, double tol)
	{
		if (verbose)
		{
			Info << " - OverallLenConfig.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_max_nb_iterations(const IntegConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - IntegConfig.MAX_NB_ITER is set to: " << n << "\n";
		}
		config.config->SetMaxNbIterations(n);
	}

	void set_nb_init_iterations(const IntegConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - IntegConfig.NB_INIT_ITER is set to: " << n << "\n";
		}
		config.config->SetNbInitIterations(n);
	}

	void set_tol(const IntegConfig& config, double tol)
	{
		if (verbose)
		{
			Info << " - IntegConfig.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_max_nb_iterations(const IterConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - IterConfig.MAX_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetMaxIterations(n);
	}

	void set_small(const IterConfig& config, double tol)
	{
		if (verbose)
		{
			Info << " - IterConfig.SMALL is set to: " << tol << "\n";
		}
		config.config->SetSmall(tol);
	}

	void set_zero(const IterConfig& config, double value)
	{
		if (verbose)
		{
			Info << " - IterConfig.ZERO is set to: " << value << "\n";
		}
		config.config->SetZero(value);
	}

	void set_tol(const IterConfig& config, double tol)
	{
		if (verbose)
		{
			Info << " - IterConfig.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_ur(const IterConfig& config, double value)
	{
		if (verbose)
		{
			Info << " - IterConfig.UR is set to: " << value << "\n";
		}
		config.config->SetUnderRelaxation(value);
	}

	void set_max_level(const CorrConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - CorrConfig.MAX_LEV is set to: " << n << "\n";
		}
		config.config->SetMaxLevel(n);
	}

	void set_tol(const CorrConfig& config, double tol)
	{
		if (verbose)
		{
			Info << " - CorrConfig.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_ur(const CorrConfig& config, double value)
	{
		if (verbose)
		{
			Info << " - CorrConfig.UR is set to: " << value << "\n";
		}
		config.config->SetUnderRelaxation(value);
	}

	void set_max_nb_iters(const MetricIntegConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - MetricConfig.Integ.MAX_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetMaxNbIterations(n);
	}

	void set_nb_init_iters(const MetricIntegConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - MetricConfig.Integ.NB_INIT_ITERS is set to: " << n << "\n";
		}
		config.config->SetNbInitIterations(n);
	}

	void set_tol(const MetricIntegConfig& config, double tol)
	{
		if (verbose)
		{
			Info << " - MetricConfig.Integ.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_tol(const MetricConfig& config, double tol)
	{
		if (verbose)
		{
			Info << " - MetricConfig.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_nb_iters(const MetricConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - MetricConfig.NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetNbIters(n);
	}

	void set_nb_sampels(const MetricConfig& config, int n)
	{
		if (verbose)
		{
			Info << " - MetricConfig.NB_SAMPLES is set to: " << n << "\n";
		}
		config.config->SetNbSamples(n);
	}

	auto get_integ_config(const std::shared_ptr<Mesh_Curve_Info>& info)
	{
		return IntegConfig{ info->NewtonIntgInfo() };
	}

	auto get_iter_config(const std::shared_ptr<Mesh_Curve_Info>& info)
	{
		return IterConfig{ info->NewtonIterInfo() };
	}

	auto get_corr_config(const std::shared_ptr<Mesh_Curve_Info>& info)
	{
		return CorrConfig{ info->CorrAlgInfo() };
	}



	RunTimeConfigs(Aft_MetricPrcsrAnIso_Info);
	SetRunTimeConfigs(Aft_MetricPrcsrAnIso_Info)
	{
		my_metric_info->SetNbIters(40);
		my_metric_info->SetNbIters(4);
		my_metric_info->SetTolerance(1.0e-4);
	}

	static std::shared_ptr<Aft3d_SolutionData_SurfVol> my_solution_data;


	void load_volume(const std::string& name)
	{
		file::CheckExtension(name);
		my_volume = file::LoadFile<std::shared_ptr<Cad_Volume>>(name + Cad_Volume::extension, verbose);
		if (NOT my_volume)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the file contains a null volume." << endl
				<< abort(FatalError);
		}
	}

	void load_size_fun(const std::string& name)
	{
		file::CheckExtension(name);
		my_size_fun = file::LoadFile<std::shared_ptr<Geo3d_SizeFunction>>(name + Geo3d_SizeFunction::extension, verbose);
		if (NOT my_size_fun)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the file contains a null size function." << endl
				<< abort(FatalError);
		}
	}

	void save_to(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(my_solution_data, name + Aft3d_SolutionData_SurfVol::extension, verbose);
	}

	void execute()
	{
		if (NOT my_size_fun)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "no size function has been loaded." << endl
				<< abort(FatalError);
		}
		if (NOT my_volume)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "no volume has been loaded." << endl
				<< abort(FatalError);
		}
		my_solution_data = std::make_shared<Aft3d_SolutionData_SurfVol>();
		my_solution_data->SetCurveInfo(my_curve_info);
		my_solution_data->SetGeometry(my_volume);
		my_solution_data->SetSizeFunction(my_size_fun);
		my_solution_data->SetMetricProcessorInfo(my_metric_info);

		exeTag = true;
	}

}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFunctions(const module_t& mod)
	{
		// io functions [12/5/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {save_to(name); }), "save_to");
		mod->add(chaiscript::fun([](const std::string& name)->void {load_volume(name); }), "load_volume");
		mod->add(chaiscript::fun([](const std::string& name)->void {load_size_fun(name); }), "load_size_func");

		// settings [12/5/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		mod->add(chaiscript::fun([](const OverallLenCalcConfig& config, int n)->void {set_max_nb_iterations(config, n); }), "set_max_nb_iters");
		mod->add(chaiscript::fun([](const OverallLenCalcConfig& config, int n)->void {set_nb_init_iters(config, n); }), "set_nb_init_iters");
		mod->add(chaiscript::fun([](const OverallLenCalcConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");

		mod->add(chaiscript::fun([](const IntegConfig& config, int n)->void {set_max_nb_iterations(config, n); }), "set_max_nb_iters");
		mod->add(chaiscript::fun([](const IntegConfig& config, int n)->void {set_nb_init_iterations(config, n); }), "set_nb_init_iters");
		mod->add(chaiscript::fun([](const IntegConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");

		mod->add(chaiscript::fun([](const IterConfig& config, int n)->void {set_max_nb_iterations(config, n); }), "set_max_nb_iters");
		mod->add(chaiscript::fun([](const IterConfig& config, double value)->void {set_small(config, value); }), "set_small");
		mod->add(chaiscript::fun([](const IterConfig& config, double value)->void {set_zero(config, value); }), "set_zero");
		mod->add(chaiscript::fun([](const IterConfig& config, double value)->void {set_tol(config, value); }), "set_tol");
		mod->add(chaiscript::fun([](const IterConfig& config, double ur)->void {set_ur(config, ur); }), "set_ur");

		mod->add(chaiscript::fun([](const CorrConfig& config, int n)->void {set_max_level(config, n); }), "set_max_level");
		mod->add(chaiscript::fun([](const CorrConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const CorrConfig& config, double ur)->void {set_ur(config, ur); }), "set_ur");

		//- metric configs
		mod->add(chaiscript::fun([](const MetricConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const MetricConfig& config, int n)->void {set_nb_iters(config, n); }), "set_nb_iters");
		mod->add(chaiscript::fun([](const MetricConfig& config, int n)->void {set_nb_sampels(config, n); }), "set_nb_samples");

		mod->add(chaiscript::fun([](const MetricIntegConfig& config, int n)->void {set_max_nb_iters(config, n); }), "set_max_nb_iters");
		mod->add(chaiscript::fun([](const MetricIntegConfig& config, int n)->void {set_nb_init_iters(config, n); }), "set_nb_init_iters");
		mod->add(chaiscript::fun([](const MetricIntegConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");

		// operators [12/5/2021 Amir]
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");

		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Curve_Info>& info)->auto {return get_overall_len(info); }), "get_overall_len_config");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Curve_Info>& info)->auto {return get_integ_config(info); }), "get_integ_config");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Curve_Info>& info)->auto {return get_iter_config(info); }), "get_iter_config");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Curve_Info>& info)->auto {return get_corr_config(info); }), "get_corr_config");

		mod->add(chaiscript::fun([]()->auto {return get_curve_info(); }), "get_curve_config");

		mod->add(chaiscript::fun([]()->auto {return get_metric_info(); }), "get_metric_config");
	}

	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument IS_EQUAL command;
	}
}

using namespace tnbLib;

int main(int argc, char* argv[])
{
	//FatalError.throwExceptions();

	if (argc <= 1)
	{
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a solution data of the surface mesh of a volume." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - save_to(file_name)" << endl
				<< " - load_volume(file_name)" << endl
				<< " - load_size_func(file_name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " - (CurveConfig.OverallLen).set_max_nb_iters(n); default = " << CURVE_CONFIG_OVERALL_LEN_MAX_NB_ITERS << endl
				<< " - (CurveConfig.OverallLen).set_nb_init_iters(n); default = " << CURVE_CONFIG_OVERALL_LEN_NB_INIT_ITERS << endl
				<< " - (CurveConfig.OverallLen).set_tol(x); default = " << CURVE_CONFIG_OVERALL_LEN_TOL << endl << endl

				<< " - (CurveConfig.Integ).set_max_nb_iters(n); default = " << CURVE_CONFIG_ITER_MAX_NB_ITERS << endl
				<< " - (CurveConfig.Integ).set_nb_init_iters(n); default = " << CURVE_CONFIG_INTEG_NB_INIT << endl
				<< " - (CurveConfig.Integ).set_tol(x); default = " << CURVE_CONFIG_INTEG_TOL << endl << endl

				<< " - (CurveConfig.Iter).set_max_nb_iters(n); default = " << CURVE_CONFIG_ITER_MAX_NB_ITERS << endl
				<< " - (CurveConfig.Iter).set_small(x); default = " << CURVE_CONFIG_ITER_SMALL << endl
				<< " - (CurveConfig.Iter).set_zero(x); default = " << CURVE_CONFIG_ITER_ZERO << endl
				<< " - (CurveConfig.Iter).set_tol(x); default = " << CURVE_CONFIG_ITER_TOL << endl
				<< " - (CurveConfig.Iter).set_ur(x); default = " << CURVE_CONFIG_ITER_UR << endl << endl

				<< " - (CurveConfig.Corr).set_max_level(n); default = " << CURVE_CONFIG_CORR_MAX_LEV << endl
				<< " - (CurveConfig.Corr).set_tol(x); default = " << CURVE_CONFIG_CORR_TOL << endl
				<< " - (CurveConfig.Corr).set_ur(x); default = " << CURVE_CONFIG_CORR_UR << endl << endl

				<< " - (MetricConfig).set_tol(x); default = " << METRIC_CONFIG_TOL << endl
				<< " - (MetricConfig).set_nb_iters(n); default = " << METRIC_CONFIG_NB_ITERS << endl
				<< " - (MetricConfig).set_nb_samples(n); default = " << METRIC_CONFIG_NB_SAMPLES << endl << endl

				<< " - (MetricConfig.Integ).set_max_nb_iters(n); default = " << METRIC_CONFIG_INTEG_MAX_NB_ITERS << endl
				<< " - (MetricConfig.Integ).set_nb_init_iters(n); default = " << METRIC_CONFIG_INTEG_INIT_ITERS << endl
				<< " - (MetricConfig.Integ).set_tol(x); default = " << METRIC_CONFIG_INTEG_TOL << endl << endl

				<< " # operators: " << endl << endl

				<< " - [CurveConfig] get_curve_config()" << endl
				<< " - [MetricConfig] get_metric_config()" << endl << endl

				<< " - [OverallLen] (CurveConfig).get_overall_len_config()" << endl
				<< " - [Integ] (CurveConfig).get_integ_config()" << endl
				<< " - [Iter] (CurveConfig).get_iter_config()" << endl
				<< " - [Corr] (CurveConfig).get_corr_config()" << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);


			try
			{
				fileName theFileName(file::GetSystemFile("tnbMeshVolumeBndSoluDataAft"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}