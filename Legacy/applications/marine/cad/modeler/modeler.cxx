#include <Marine_Bodies.hxx>
#include <Marine_Models.hxx>
#include <Marine_TankModeler.hxx>
#include <Marine_SailModeler.hxx>
#include <Marine_DisplacerModeler.hxx>
#include <StbGMaker_Model.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<Marine_Model> model_t;

	static const std::string hullFolder = "hull";
	static const std::string sailsFolder = "sails";
	static const std::string tanksFolder = "tanks";

	static bool hullTag = false;
	static bool sailTag = false;
	static bool tankTag = false;
	static bool verbose = false;

	static auto myModel = std::make_shared<StbGMaker_Model>();

	void loadHull(const std::string& name)
	{
		std::string address = ".\\" + hullFolder + "\\" + name;
		std::fstream file;
		file.open(address, ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(file);

		std::shared_ptr<marineLib::Model_Hull> myHull;
		ia >> myHull;

		if (!myHull)
		{
			FatalErrorIn(FunctionSIG)
				<< "no hull has been loaded" << endl
				<< abort(FatalError);
		}

		myModel->SetHull(std::move(myHull));

		hullTag = true;

		if (!myHull)
		{
			FatalErrorIn(FunctionSIG)
				<< "The hull is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " The Hull has been loaded successfully. " << endl
				<< " - hull's name: " << myHull->Name() << endl;
		}
	}

	void loadSails(const std::string& name)
	{
		std::string address = ".\\" + sailsFolder + "\\" + name;
		std::fstream file;
		file.open(address, ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(file);
		
		std::vector<std::shared_ptr<marineLib::Model_Sail>> mySails;

		ia >> mySails;

		myModel->SetSail(std::move(mySails));

		sailTag = true;

		if (verbose)
		{
			Info << " The list of Sails has been loaded successfully. " << endl
				<< " - no. of sails: " << mySails.size() << endl;
		}
	}

	void loadTanks(const std::string& name)
	{
		std::string address = ".\\" + tanksFolder + "\\" + name;
		std::fstream file;
		file.open(address, ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(file);

		std::vector<std::shared_ptr<marineLib::Model_Tank>> myTanks;

		ia >> myTanks;

		myModel->SetTanks(std::move(myTanks));

		tankTag = true;

		if (verbose)
		{
			Info << " The list of Tanks has been loaded successfully." << endl
				<< " - no. of tanks: " << myTanks.size() << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myModel;
	}
}


#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void modelMaker(const module_t& mod)
	{

		mod->add(chaiscript::fun([](const std::string& name)-> void { loadHull(name); }), "loadHull");
		mod->add(::chaiscript::fun([](const std::string& name)-> void {loadSails(name); }), "loadSails");
		mod->add(::chaiscript::fun([](const std::string& name)-> void {loadTanks(name); }), "loadTanks");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			modelMaker(mod);

			chai.add(mod);

			fileName myFileName("modeler");

			try
			{
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