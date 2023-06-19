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

	static unsigned short verbose(0);

	model_t myBody;
	soluData_t mySolutionData;

	void loadModel(const std::string& name)
	{
		file::CheckExtension(name);

		myBody=file::LoadFile<std::shared_ptr<HydStatic_ModelShape>>(name + HydStatic_ModelShape)

		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		TNB_iARCH_FILE_TYPE ar(myFile);

		ar >> myBody;
		if (NOT myBody)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded body is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the body is loaded, from: " << name << ", successfully!" << endl;
			Info << " - body's name: " << myBody->Name() << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << mySolutionData;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the solution data is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

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
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		//- io functions

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
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

}