#include <StbGMaker_Model.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_Models.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

#include <fstream>

namespace tnbLib
{

	typedef std::shared_ptr<Marine_Body> body_t;
	typedef std::shared_ptr<StbGMaker_Model> model_t;

	static model_t myModel;

	typedef std::shared_ptr<marineLib::Model_Hull> displacer_t;
	typedef std::shared_ptr<marineLib::Model_Tank> tank_t;
	typedef std::shared_ptr<marineLib::Model_Sail> sail_t;

	static displacer_t myDisplacer;
	static std::map<size_t, tank_t> myTanks;
	static std::map<size_t, sail_t> mySails;

	static size_t verbose;

	void loadDisplacer(const std::string& name)
	{
		boost::filesystem::path dir("displacer");
		if (NOT boost::filesystem::is_directory(dir))
		{
			FatalErrorIn(FunctionSIG)
				<< "no 'displacer' directory has been found!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::string address = ".\\displacer\\" + name;
	
		std::fstream file;

		file.open(address, std::ios::in);
		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to open the file: " << address << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ar(file);

		body_t body;
		ar >> body;

		auto displacer = std::dynamic_pointer_cast<marineLib::Body_Displacer>(body);
		if (NOT displacer)
		{
			FatalErrorIn(FunctionSIG)
				<< "the body is not displacer!" << endl
				<< abort(FatalError);
		}

		myDisplacer = std::make_shared<marineLib::Model_Hull>(std::move(displacer));

		if (verbose)
		{
			Info << " displacer has been loaded from: " << address << ", successfully!" << endl;
			Info << " - body's name: " << body->Name() << endl;
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
		myModel->SetHull(myDisplacer);

		if (myTanks.size())
		{
			std::vector<tank_t> tanks;
			for (const auto& x : myTanks)
			{
				tanks.push_back(x.second);
			}
			myModel->SetTanks(std::move(tanks));
		}

		if (mySails.size())
		{
			std::vector<sail_t> sails;
			for (const auto& x : mySails)
			{
				sails.push_back(x.second);
			}
			myModel->SetSail(std::move(sails));
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);
		oa << myModel;

		if (verbose)
		{
			Info << " the model is saved in: " << fn << ", successfully!" << endl;
		}
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadDisplacer(name); }), "loadDisplacer");
		mod->add(chaiscript::fun([]()->void {makeModel(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("TnbStbModelMaker");

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