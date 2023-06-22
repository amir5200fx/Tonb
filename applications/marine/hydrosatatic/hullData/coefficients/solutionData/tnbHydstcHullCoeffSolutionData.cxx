#include <HydStatic_SolutionData_Coeffs.hxx>
#include <HydStatic_ModelShape.hxx>
#include <HydStatic_Shapes.hxx>
#include <Marine_Models.hxx>
#include <Marine_Body_Displacer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_Coeffs> soluData_t;
	typedef std::shared_ptr<HydStatic_ModelShape> model_t;

	model_t myBody;
	soluData_t mySolutionData;

	TNB_STANDARD_LOAD_SAVE_OBJECTS("model");
	TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(myBody, model_directory, mySolutionData);

	void execute()
	{
		if (NOT myBody)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been loaded!" << endl
				<< abort(FatalError);
		}
		const auto& shape = myBody->Hull();
		if (NOT shape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been found!" << endl
				<< abort(FatalError);
		}

		const auto& model = shape->Hull();
		if (NOT model)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been found!" << endl
				<< abort(FatalError);
		}

		const auto& domain = myBody->Domain();
		if (NOT domain)
		{
			FatalErrorIn(FunctionSIG)
				<< "no domain has been found!" << endl
				<< abort(FatalError);
		}
		mySolutionData = std::make_shared<hydStcLib::SolutionData_Coeffs>(model->Body());
		mySolutionData->LoadDomain(domain);
		mySolutionData->SetCurrentSolution(hydStcLib::SolutionData_Coeffs::solutionOrder::model);

		if (verbose)
		{
			Info << endl;
			Info << " - symmetric body? " << (shape->IsSymmetric() ? "yes" : "no") << endl;
			Info << endl;
		}
		mySolutionData->SetSymmetric(shape->IsSymmetric());
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

	void setFunctions(const module_t& mod)
	{
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadFile");

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

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
	//sysLib::init_gl_marine_integration_info();
	//FatalError.throwExceptions();

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
			Info << " This application is aimed to provide a solution data for the hydrostatic coefficients of hull" << endl;

			Info << " - You can upload the file form a subdirectory named '" << model_directory << "'." << endl
				<< " - inputs: *" << std::remove_reference<decltype(*myBody)>::type::extension << endl
				<< " - outputs: *" << std::remove_reference<decltype(*mySolutionData)>::type::extension << endl << endl;
			
			Info << endl
				<< " Function list:" << endl << endl

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

			setFunctions(mod);

			chai.add(mod);


			//std::string address = ".\\system\\tnbHydstcHullSolutionData";
			//fileName myFileName(address);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbHydstcHullModelMaker"));
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