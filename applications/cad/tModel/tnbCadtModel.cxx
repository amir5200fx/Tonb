#include <Cad_tModelMaker.hxx>
#include <Cad_tModelMakerInfo_Absolute.hxx>
#include <Cad_tEdgeMakerInfo_Absolute.hxx>
#include <Cad_tSurfaceMakerInfo_Absolute.hxx>
#include <Cad_tModelMaker_OnePtDistPairCrvCriterion.hxx>
#include <Cad_CurveLength_Info.hxx>
#include <Cad_CurveSplitter_Info.hxx>
#include <Cad_Shape.hxx>
#include <Cad_TModel.hxx>
#include <TModel_Surface.hxx>
#include <TModel_GeneratedEdge.hxx>
#include <TModel_Wire.hxx>
#include <TModel_ParaCurve.hxx>
#include <Pln_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <Entity2d_Chain.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include "../../../include/NumAlg_AdaptiveInteg_Info.hxx"
#include "../../../TnbNumAlg/include/NumAlg_NewtonSolver_Info.hxx"
#include "../../../TnbNumAlg/TnbLib/NumAlg/NonLinearSolver/Bisection/Info/NumAlg_BisectionSolver_Info.hxx"

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static int nbSegments = 40;

	static std::shared_ptr<Cad_TModel> myModel;
	static std::shared_ptr<Cad_Shape> myShape;
	static std::string myFileName;

	static auto my_curve_len_config = std::make_shared<Cad_CurveLength_Info>();
	static auto my_curve_splitter_config = std::make_shared<Cad_CurveSplitter_Info>();
	static auto my_edge_pair_config = std::make_shared<cadLib::tModelMaker_OnePtDistPairCrvCriterion>(my_curve_len_config, my_curve_splitter_config);
	static double my_tol = 1.0E-6;

	struct EdgeMatchConfig
	{
		std::shared_ptr<Cad_CurveLength_Info> curve_config;
		std::shared_ptr<Cad_CurveSplitter_Info> splitter_config;
		double tol = my_tol;
	};
	static const auto my_edge_match_maker_config = std::make_shared<EdgeMatchConfig>(EdgeMatchConfig{ my_curve_len_config, my_curve_splitter_config, my_tol });

	auto get_edge_match_maker_config()
	{
		return my_edge_match_maker_config;
	}

	void set_tol(const std::shared_ptr<EdgeMatchConfig>& config, double tol)
	{
		if (verbose)
		{
			Info  << "\n"
			<< " - EdgeMatchMaker.TOL has been set to: " << tol << "\n";
		}
		config->tol = tol;
	}

	struct EdgeMatchConfig_Compute
	{
		std::shared_ptr<Cad_CurveLength_Info> config;
	};

	auto get_edge_compute(const std::shared_ptr<EdgeMatchConfig>& config)
	{
		return EdgeMatchConfig_Compute{ config->curve_config };
	}

	void set_max_lev(const EdgeMatchConfig_Compute& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMatchMakerConfig.Compute.MAX_LEV has been set to: " << n << "\n";
		}
		config.config->SetMaxLevel(n);
	}

	struct ComputeEdge_Integ
	{
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> config;
	};

	auto get_compute_integ(const EdgeMatchConfig_Compute& config)
	{
		return ComputeEdge_Integ{ config.config->IntegInfo() };
	}

	void set_tol(const ComputeEdge_Integ& config, int tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMakerConfig.Compute.Integ.TOL has been set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_max_iters(const ComputeEdge_Integ& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMakerConfig.Compute.Integ.MAX_NB_ITERS has been set to: " << n << "\n";
		}
		config.config->SetMaxNbIterations(n);
	}

	void set_init_nb_iters(const ComputeEdge_Integ& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMakerConfig.Compute.Integ.NB_INIT has been set to: " << n << "\n";
		}
		config.config->SetNbInitIterations(n);
	}

	struct EdgeMatchConfig_Splitter
	{
		std::shared_ptr<Cad_CurveSplitter_Info> config;
	};

	auto get_splitter(const std::shared_ptr<EdgeMatchConfig>& config)
	{
		return EdgeMatchConfig_Splitter{ config->splitter_config };
	}

	static auto myEdgeMakerInfo = std::make_shared<Cad_tEdgeMakerInfo_Absolute>();
	static auto mySurfMakerInfo = std::make_shared<Cad_tSurfaceMakerInfo_Absolute>();
	static auto myModelMakerInfo = std::make_shared<Cad_tModelMakerInfo_Absolute>();

	TNB_SET_VERBOSE_FUN;


	void set_max_lev(const EdgeMatchConfig_Splitter& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMatchMakerConfig.Splitter.MAX_LEV has been set to: " << n << "\n";
		}
		config.config->SetMaxLevel(n);
	}

	void set_ur(const EdgeMatchConfig_Splitter& config, double ur)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMatchMakerConfig.Splitter.UR has been set to: " << ur << "\n";
		}
		config.config->SetUnderRelaxation(ur);
	}

	void set_conv_status(const EdgeMatchConfig_Splitter& config, bool status)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMatchMakerConfig.Splitter.STATUS has been set to: " << (status ? "TRUE" : "FALSE") << "\n";
		}
		config.config->SetUnderRelaxation(status);
	}

	auto get_edge_config()
	{
		return EdgeMatchConfig{ my_curve_len_config, my_curve_splitter_config };
	}

	/*auto get_len_config(const EdgeMatchConfig& config)
	{
		return EdgeMatchConfig_Edge{ config.curve_config };
	}

	auto get_splitter_config(const EdgeMatchConfig& config)
	{
		return EdgeMatchConfig_Splitter{ config.splitter };
	}*/

	struct SplitterConfig_Iter
	{
		std::shared_ptr<NumAlg_NewtonSolver_Info> config;
	};

	auto get_splitter_iter(const EdgeMatchConfig_Splitter& config)
	{
		return SplitterConfig_Iter{ config.config->NewtonIterInfo() };
	}

	void set_max_iters(const SplitterConfig_Iter& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Iter.MAX_ITERS has been set to: " << n << "\n";
		}
		config.config->SetMaxIterations(n);
	}

	void set_tol(const SplitterConfig_Iter& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Iter.TOL has been set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_small(const SplitterConfig_Iter& config, double samll)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Iter.SMALL has been set to: " << small << "\n";
		}
		config.config->SetSmall(small);
	}

	void set_zero(const SplitterConfig_Iter& config, double zero)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Iter.ZERO has been set to: " << zero << "\n";
		}
		config.config->SetZero(zero);
	}

	void set_ur(const SplitterConfig_Iter& config, double ur)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Iter.UR has been set to: " << ur << "\n";
		}
		config.config->SetUnderRelaxation(ur);
	}

	struct SplitterConfig_OverallLen
	{
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> config;
	};

	auto get_overall_len(const EdgeMatchConfig_Splitter& config)
	{
		return SplitterConfig_OverallLen{ config.config->OverallLengthIntgInfo() };
	}

	void set_tol(const SplitterConfig_OverallLen& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.OverallLen.TOL has been set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_max_nb_iters(const SplitterConfig_OverallLen& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.OverallLen.MAX_NB_ITERS has been set to: " << n << "\n";
		}
		config.config->SetMaxNbIterations(n);
	}

	void set_init_nb_iters(const SplitterConfig_OverallLen& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.OverallLen.INIT_NB_ITERS has been set to: " << n << "\n";
		}
		config.config->SetNbInitIterations(n);
	}

	struct SplitterConfig_Integ
	{
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> config;
	};

	auto get_integ(const EdgeMatchConfig_Splitter& config)
	{
		return SplitterConfig_Integ{ config.config->IterIntgInfo() };
	}

	void set_tol(const SplitterConfig_Integ& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Integ.TOL has been set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_max_nb_iters(const SplitterConfig_Integ& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Integ.MAX_NB_ITERS has been set to: " << n << "\n";
		}
		config.config->SetMaxNbIterations(n);
	}

	void set_init_nb_iters(const SplitterConfig_Integ& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Integ.INIT_NB_ITERS has been set to: " << n << "\n";
		}
		config.config->SetNbInitIterations(n);
	}

	void set_tol(double tol)
	{
		my_tol = tol;
		if (verbose)
		{
			Info << "\n"
				<< " - TOL is set to: " << tol << "\n";
		}
	}

	struct SplitterConfig_Bisection
	{
		std::shared_ptr<NumAlg_BisectionSolver_Info> config;
	};

	auto get_bisection(const EdgeMatchConfig_Splitter& config)
	{
		return SplitterConfig_Bisection{ config.config->BisectInfo() };
	}

	void set_max_iters(const SplitterConfig_Bisection& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Bisection.MAX_NB_ITERS has been set to: " << n << "\n";
		}
		config.config->SetMaxIterations(n);
	}

	void set_tol(const SplitterConfig_Bisection& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Bisection.TOL has been set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_delta(const SplitterConfig_Bisection& config, double d)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.Bisection.DELTA has been set to: " << d << "\n";
		}
		config.config->SetDelta(d);
	}

	struct SplitterConfig_Point
	{
		std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info> config;
	};

	auto get_point_gen(const EdgeMatchConfig_Splitter& config)
	{
		return SplitterConfig_Point{ config.config->CorrInfo() };
	}

	void set_tol(const SplitterConfig_Point& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.NodeGen.TOL has set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_ur(const SplitterConfig_Point& config, double ur)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.NodeGen.UR has been set to: " << ur << "\n";
		}
		config.config->SetUnderRelaxation(ur);
	}

	void set_max_lev(const SplitterConfig_Point& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeConfig.Splitter.NodeGen.MAX_LEV has set to: " << n << "\n";
		}
		config.config->SetMaxLevel(n);
	}

	void load_file(const std::string& name)
	{
		file::CheckExtension(name);

		myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + Cad_Shape::extension, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the shape file is null!" << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void load_file()
	{
		const auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_TModel::extension).string();
		myFileName = name;
		load_file(name);
	}

	void save_to(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myModel, name + Cad_TModel::extension, verbose);
	}

	void save_to()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		save_to(myFileName);
	}

	auto get_polygon(const TModel_Wire& wire)
	{
		auto chain = std::make_shared<Entity2d_Chain>();
		const auto curves = *TModel_Wire::RetrieveParaCurves(wire);
		for (const auto& x : curves)
		{
			auto pl = Pln_Tools::UniformDiscrete(x->Curve(), x->FirstParameter(), x->LastParameter(), nbSegments);
			auto iChain = Geo_Tools::RetrieveChain(*pl);
			chain->Add(*iChain);
		}
		return std::move(chain);
	}

	auto get_patch(const TModel_Surface& theSurface)
	{
		const auto& outer = theSurface.Outer();
		auto chain = get_polygon(*outer);
		if (theSurface.Inner())
		{
			for (const auto& x : *theSurface.Inner())
			{
				auto iChain = get_polygon(*x);
				chain->Add(*iChain);
			}
		}
		return std::move(chain);
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}
		if (verbose > 1)
		{
			Cad_tModelMaker::verbose = 1;
		}
		// Calculating the dimension of the model
		const auto d = myShape->BoundingBox()->Diameter();
		// Setting the tolerance relative to the dimension
		my_edge_pair_config->SetTolerance(my_edge_match_maker_config->tol*d);

		{// Calculating the run-time calculation
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			auto myModelInfo = std::make_shared<Cad_tModelMaker::MakerInfo>();
			myModelInfo->edgeInfo = myEdgeMakerInfo;
			myModelInfo->modelInfo = myModelMakerInfo;
			myModelInfo->surfInfo = mySurfMakerInfo;

			const auto myMaker =
				std::make_shared<Cad_tModelMaker>(myShape->Shape(), myModelInfo, my_edge_pair_config);
			myMaker->Perform();

			myModel = myMaker->Model();
		}

		/*std::vector<std::shared_ptr<Entity2d_Triangulation>> myTris;
		for (const auto& x : myModel->RetrieveFaces())
		{
			auto chain = GetPatch(*x);
			auto tri = Geo_Tools::Triangulation(*chain);
			myTris.push_back(std::move(tri));
		}

		OFstream myFile("paraCurves.plt");
		for (const auto& x : myTris)
		{
			x->ExportToPlt(myFile);
		}*/

		if (verbose)
		{
			Info << endl;
			Info << " - Number of corners: " << myModel->NbCorners() << endl
				<< " - Number of segments: " << myModel->NbSegments() << endl
				<< " - Number of faces: " << myModel->NbFaces() << endl << endl;
		}

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< "- the application is performed, successfully, in "<< global_time_duration << " ms." << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		execute(myShape->Name());
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
		// io functions [1/31/2022 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {load_file(name); }), "load_file");
		mod->add(chaiscript::fun([]()-> void {load_file(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name)-> void {save_to(name); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {save_to(); }), "save_to");

		//* The edge match maker
		mod->add(chaiscript::fun([]()->auto {get_edge_match_maker_config(); }), "get_edge_match_maker_config");
		//- Setting the tolerance
		mod->add(chaiscript::fun([](const std::shared_ptr<EdgeMatchConfig>& config, double tol)-> void {set_tol(config, tol); }), "set_tol");
		//- Getting the curve computations configs
		mod->add(chaiscript::fun([](const std::shared_ptr<EdgeMatchConfig>& config)->auto {return get_edge_compute(config); }), "computs");
		//*
		//- The computation settings
		mod->add(chaiscript::fun([](const EdgeMatchConfig_Compute& config, int n)->void {set_max_lev(config, n); }), "set_max_lev");
		//*
		//- Getting the integration settings of the computation part
		mod->add(chaiscript::fun([](const EdgeMatchConfig_Compute& config)->auto {return get_compute_integ(config); }), "integ");
		mod->add(chaiscript::fun([](const ComputeEdge_Integ& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const ComputeEdge_Integ& config, int n)->void {set_max_iters(config, n); }), "set_max");
		mod->add(chaiscript::fun([](const ComputeEdge_Integ& config, int n)->void {set_init_nb_iters(config, n); }), "set_init");
		//- Getting the curve splitter configs
		mod->add(chaiscript::fun([](const std::shared_ptr<EdgeMatchConfig>& config)->auto {return get_splitter(config); }), "splitter");
		//*
		//- The splitter configs
		mod->add(chaiscript::fun([](const EdgeMatchConfig_Splitter& config, int n)->void {set_max_lev(config, n); }), "set_max_lev");
		mod->add(chaiscript::fun([](const EdgeMatchConfig_Splitter& config, double ur)->void {set_ur(config, ur); }), "set_ur");
		mod->add(chaiscript::fun([](const EdgeMatchConfig_Splitter& config, bool status)->void {set_conv_status(config, status); }), "set_conv_status");
		//*
		//- The iteration settings of the splitter algorithm
		mod->add(chaiscript::fun([](const EdgeMatchConfig_Splitter& config)->auto {return get_splitter_iter(config); }), "iter");
		mod->add(chaiscript::fun([](const SplitterConfig_Iter& config, int n)->void {set_max_iters(config, n); }), "set_max");
		mod->add(chaiscript::fun([](const SplitterConfig_Iter& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const SplitterConfig_Iter& config, double small)->void {set_small(config, small); }), "set_small");
		mod->add(chaiscript::fun([](const SplitterConfig_Iter& config, double zero)->void {set_zero(config, zero); }), "set_zero");
		mod->add(chaiscript::fun([](const SplitterConfig_Iter& config, double ur)->void {set_ur(config, ur); }), "set_ur");
		//*
		//- The overall length calculation settings of the splitter algorithm
		//*
		//- Getting the overall length calculation part's settings
		mod->add(chaiscript::fun([](const EdgeMatchConfig_Splitter& config)->auto {return get_overall_len(config); }), "len");
		mod->add(chaiscript::fun([](const SplitterConfig_OverallLen& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const SplitterConfig_OverallLen& config, int n)->void {set_max_nb_iters(config, n); }), "set_max");
		mod->add(chaiscript::fun([](const SplitterConfig_OverallLen& config, int n)->void {set_init_nb_iters(config, n); }), "set_init");
		//*
		//- The integration settings of the splitter algorithm
		mod->add(chaiscript::fun([](const EdgeMatchConfig_Splitter& config)->auto {return get_integ(config); }), "integ");
		mod->add(chaiscript::fun([](const SplitterConfig_Integ& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const SplitterConfig_Integ& config, int n)->void {set_max_nb_iters(config, n); }), "set_max");
		mod->add(chaiscript::fun([](const SplitterConfig_Integ& config, int n)->void {set_init_nb_iters(config, n); }), "set_init");
		//*
		//- The Bisection's settings of the splitter algorithm
		mod->add(chaiscript::fun([](const EdgeMatchConfig_Splitter& config)->auto {return get_bisection(config); }), "bisection");
		mod->add(chaiscript::fun([](const SplitterConfig_Bisection& config, int n)->void {set_max_iters(config, n); }), "set_max");
		mod->add(chaiscript::fun([](const SplitterConfig_Bisection& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const SplitterConfig_Bisection& config, double d)->void {set_delta(config, d); }), "set_delta");
		//.
		//- The node gen's settings of the splitter algorithm
		mod->add(chaiscript::fun([](EdgeMatchConfig_Splitter& config)->auto {return get_point_gen(config); }), "node_gen");
		mod->add(chaiscript::fun([](const SplitterConfig_Point& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const SplitterConfig_Point& config, double ur)->void {set_ur(config, ur); }), "set_ur");
		mod->add(chaiscript::fun([](const SplitterConfig_Point& config, int n)->void {set_max_lev(config, n); }), "set_max_lev");
		// operators [1/31/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");

		// settings [1/31/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "set_verbose");
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

int main(int argc, char *argv[])
{
	//FatalError.throwExceptions();
	FatalConvError.throwExceptions();

	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << " This application is aimed to create a TModel from a shape." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_file(name [optional])" << endl
				<< " - save_to(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " # Edge match maker's settings:\n\n"

				<< " - (EdgeMatchMaker).set_tol(x);\n\n"

				<< " # The splitter's settings of the edge match maker:\n\n"

				<< " - (EdgeMatchMk.Split).set_tol(x); \n"
				<< " - (EdgeMatchMk.Split).set_ur(x) \n"
				<< " - (EdgeMatchMk.Split).set_conv_status(bool) \n\n"

				<< " # The iteration's settings of the splitter algorithm:\n\n"

				<< " - (EdgeMatchMk.Split.Iter).set_max(n) \n"
				<< " - (EdgeMatchMk.Split.Iter).set_tol(x) \n"
				<< " - (EdgeMatchMk.Split.Iter).set_small(x) \n"
				<< " - (EdgeMatchMk.Split.Iter).set_zero(x) \n"
				<< " - (EdgeMatchMk.Split.Iter).set_ur(x) \n\n"

				<< " # The overall length's settings of the splitter algorithm:\n\n"

				<< " - (EdgeMatchMk.Split.Len).set_tol(x) \n"
				<< " - (EdgeMatchMk.Split.Len).set_max(n) \n"
				<< " - (EdgeMatchMk.Split.Len).set_init(n) \n\n"

				<< " # The Bisection's settings of the splitter algorithm: \n\n"

				<< " - (EdgeMatchMk.Split.Bisect).set_max(n) \n"
				<< " - (EdgeMatchMk.Split.Bisect).set_tol(x) \n"
				<< " - (EdgeMatchMk.Split.Bisect).set_delta(x) \n\n"

				<< " # The node gen's settings of the splitter algorithm: \n\n"

				<< " - (EdgeMatchMk.Split.NodeGen).set_tol(x) \n"
				<< " - (EdgeMatchMk.Split.NodeGen).set_ur(x) \n"
				<< " - (EdgeMatchMk.Split.NodeGen).set_max_lev(n) \n"

				<< " - set_verbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute(name [optional])" << endl
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
				auto address = file::GetSystemFile("tnbCadtModel");
				fileName myFileName(address);

				chai.eval_file(myFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				Info << x.what() << endl;
			}
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}