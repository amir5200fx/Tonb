#include <HydStatic_SolutionData_Coeffs.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_Wave.hxx>
#include <Marine_BooleanOps.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>
#include <HydStatic_FloatBody.hxx>
#include <HydStatic_ModelShape.hxx>
#include <HydStatic_Shapes.hxx>
#include <StbGMaker_Model.hxx>
#include <Pln_Wire.hxx>
#include <Pln_CmpEdge.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <OFstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_Coeffs> soluData_t;
	typedef std::shared_ptr<Marine_WaterDomain> waterDomain_t;

	static soluData_t mySolutionData;
	static waterDomain_t myWaterDomain;

	static const double DEFAULT_MIN_TOL = 1.0E-6;
	static const double DEFAULT_MAX_TOL = 1.0E-4;

	static auto minTol = DEFAULT_MIN_TOL;
	static auto maxTol = DEFAULT_MAX_TOL;

	TNB_STANDARD_LOAD_SAVE_OBJECTS("solution");
	TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(mySolutionData, model_directory, mySolutionData);

	void calcWater()
	{
		const auto& body = mySolutionData->Hull();
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}

		const auto& wave = mySolutionData->Wave();
		if (NOT wave)
		{
			FatalErrorIn(FunctionSIG)
				<< "no wave has been found!" << endl
				<< abort(FatalError);
		}

		if (NOT wave->Domain())
		{
			FatalErrorIn(FunctionSIG)
				<< "no domain has been found!" << endl
				<< abort(FatalError);
		}

		myWaterDomain = Marine_WaterLib::WaterDomain(*body, wave, wave->Domain(), minTol, maxTol);
		mySolutionData->SetWater(myWaterDomain->Water());
	}

	void calcFloatBody()
	{
		const auto& displacer = mySolutionData->Hull();
		if (NOT displacer)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}

		/*fileName nn("wire.plt");
		OFstream ff(nn);
		for (const auto& x : displacer->Sections())
		{
			std::cout << "nb. of sections: " << x->Sections().size() << std::endl << std::endl;
			for (const auto& s : x->Sections())
			{
				const auto& wire = s->Wire();
				std::cout << "nb of edges: " << wire->Edges().size() << std::endl;

				if (wire->Edges().size() == 1)
				{
					wire->ExportToPlt(ff);
				}
			}
		}*/

		if (verbose)
		{
			Info << endl;
			Info << " calculating the wetted body..." << endl;
			Info << endl;
		}
		auto wetted = Marine_BodyTools::WettedBody(displacer, myWaterDomain);
		if (NOT wetted)
		{
			FatalErrorIn(FunctionSIG)
				<< "no wetted body has been created!" << endl
				<< abort(FatalError);
		}
		auto wettedBody =
			Marine_BodyTools::WettedBody
			(
				wetted
			);

		if (verbose)
		{
			Info << endl;
			Info << " calculating the dry body..." << endl;
			Info << endl;
		}

		auto dryBody =
			Marine_BodyTools::DryBody
			(
				Marine_BodyTools::DryBody(displacer, myWaterDomain)
			);

		if (verbose)
		{
			Info << endl;
			Info << " creating float body..." << endl;
			Info << endl;
		}

		auto floatBody =
			std::make_shared<HydStatic_FloatBody>
			(
				0, "float body",
				std::move(dryBody),
				std::move(wettedBody)
				);

		mySolutionData->SetFloatBody(floatBody);
	}

	void execute()
	{
		TNB_CHECK_LOAD_TAG;
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT mySolutionData->IsUpdated(hydStcLib::SolutionData_Coeffs::solutionOrder::wave))
		{
			FatalErrorIn(FunctionSIG)
				<< " the solution data is not updated" << endl
				<< abort(FatalError);
		}

		calcWater();
		calcFloatBody();

		mySolutionData->SetCurrentSolution(hydStcLib::SolutionData_Coeffs::solutionOrder::floatBody);
		TNB_PERFORMED_TAG;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setGlobals(const module_t& mod)
	{
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadFile");

		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
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
	//Marine_BooleanOps::verbose = 1;
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
			Info << " This application is aimed to calculate the float body." << endl << endl;

			Info << " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbHydstcFloatBody"));

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
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
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