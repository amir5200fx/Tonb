#include <StbGMaker_Model.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_Models.hxx>
#include <Marine_Domain.hxx>
#include <Marine_WaterLib.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<Marine_Body> body_t;
	typedef std::shared_ptr<StbGMaker_Model> model_t;
	typedef std::shared_ptr<Marine_Domain> domain_t;

	static model_t myModel;
	static domain_t myDomain;

	typedef std::shared_ptr<marineLib::Model_Hull> displacer_t;
	typedef std::shared_ptr<marineLib::Model_Tank> tank_t;
	typedef std::shared_ptr<marineLib::Model_Sail> sail_t;

	static displacer_t myDisplacer;
	static std::vector<tank_t> myTanks;
	static std::vector<sail_t> mySails;

	static unsigned short verbose(0);

	auto createDomain()
	{
		auto domain = Marine_WaterLib::Domain(*myDisplacer->Body());
		return std::move(domain);
	}

	void loadModel()
	{
		const auto currentPath = boost::filesystem::current_path().string();

		{ //- loading displacer part
			if (NOT boost::filesystem::is_directory("displacer"))
			{
				FatalErrorIn(FunctionSIG)
					<< "no 'displacer' directory has been found!" << endl
					<< abort(FatalError);
			}

			//- change the current path
			boost::filesystem::current_path(currentPath + R"(\displacer)");

			auto name = file::GetSingleFile(boost::filesystem::current_path(), Marine_Model::extension).string();

			auto theModel = file::LoadFile<std::shared_ptr<Marine_Model>>(name + Marine_Model::extension, verbose);
			myDisplacer = std::dynamic_pointer_cast<marineLib::Model_Hull>(theModel);
			if (NOT myDisplacer)
			{
				FatalErrorIn(FunctionSIG)
					<< "the displacer model is null!" << endl
					<< abort(FatalError);
			}

			if (verbose)
			{
				Info << " - model's name: " << myDisplacer->Name() << endl;
			}

			//- change the current path
			boost::filesystem::current_path(currentPath);
		}

		
		if (boost::filesystem::is_directory("tanks"))
		{//- loading the tanks
			
			//- change the current path
			boost::filesystem::current_path(currentPath + R"(\tanks)");

			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".hsmodellist").string();

			auto myModels = file::LoadFile<std::vector<std::shared_ptr<Marine_Model>>>(name + ".hsmodellist", verbose);
			if (myModels.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "the list of the tanks is empty!" << endl
					<< abort(FatalError);
			}

			myTanks.reserve(myModels.size());
			for (const auto& x : myModels)
			{
				auto t = std::dynamic_pointer_cast<marineLib::Model_Tank>(x);
				if (NOT t)
				{
					FatalErrorIn(FunctionSIG)
						<< "the model is not a tank!" << endl
						<< abort(FatalError);
				}
				myTanks.push_back(std::move(t));
			}

			//- change the current path
			boost::filesystem::current_path(currentPath);
		}
		else
		{
			if (verbose)
			{
				Info << endl
					<< " - no tank has been detected!" << endl;
			}
		}

		if (boost::filesystem::is_directory("sails"))
		{//- loading the tanks

			//- change the current path
			boost::filesystem::current_path(currentPath + R"(\sails)");

			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".hsmodellist").string();

			auto myModels = file::LoadFile<std::vector<std::shared_ptr<Marine_Model>>>(name + ".hsmodellist", verbose);
			if (myModels.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "the list of the tanks is empty!" << endl
					<< abort(FatalError);
			}

			mySails.reserve(myModels.size());
			for (const auto& x : myModels)
			{
				auto t = std::dynamic_pointer_cast<marineLib::Model_Sail>(x);
				if (NOT t)
				{
					FatalErrorIn(FunctionSIG)
						<< "the model is not a tank!" << endl
						<< abort(FatalError);
				}
				mySails.push_back(std::move(t));
			}

			//- change the current path
			boost::filesystem::current_path(currentPath);
		}
		else
		{
			if (verbose)
			{
				Info << endl
					<< " - no sail has been detected!" << endl;
			}
		}

		myDomain = createDomain();

		if (verbose)
		{
			const auto& b = *myDomain->Dim();
			Info << " - domain's dimension: " << b << endl;
		}
	}

	void makeModel()
	{
		if (NOT myDisplacer)
		{
			FatalErrorIn(FunctionSIG)
				<< "no displacer has been loaded!" << endl
				<< abort(FatalError);
		}
		myModel = std::make_shared<StbGMaker_Model>();
		myModel->SetDomain(myDomain);
		myModel->SetHull(myDisplacer);

		if (myTanks.size())
		{
			myModel->SetTanks(myTanks);
		}

		if (mySails.size())
		{
			myModel->SetSail(mySails);
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name + StbGMaker_Model::extension);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);
		oa << myModel;

		if (verbose)
		{
			Info << endl;
			Info << " the model is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
		saveTo("stbModel");
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
		mod->add(chaiscript::fun([]()->void {loadModel(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		mod->add(chaiscript::fun([]()->void {makeModel(); }), "execute");
		
		mod->add(chaiscript::fun([](int i)->void {verbose = i; }), "setVerbose");
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
	FatalError.throwExceptions();

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
			Info << endl;
			Info << " This application is aimed to create a stability model." << endl;

			Info << " - To create s stability model, there must be one displacement hull which is defined " << endl
				<< "   at 'displacer' subdirectory." << endl
				<< " - The tank list (if existed) should be defined at 'tanks' subdirectory." << endl
				<< " - The sail list (if existed) should be defined at 'sails' subdirectory." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # functions: " << endl << endl

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
				//std::string address = ".\\system\\tnbHydstcStabilityModelMaker";
				fileName myFileName(file::GetSystemFile("tnbHydstcStabilityModelMaker"));

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