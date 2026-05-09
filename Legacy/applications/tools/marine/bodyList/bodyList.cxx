#include <Marine_Bodies.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<Marine_Body> body_t;

	static std::vector<body_t> myBodies;

	static bool verbose = false;

	void loadBodies(const std::string& name)
	{
		int i = 0;
		while (true)
		{
			boost::filesystem::path dir(std::to_string(i));
			if (boost::filesystem::is_directory(dir))
			{
				std::string address = ".\\" + std::to_string(i) + "\\" + name;
				std::fstream file;
				file.open(address, ios::in);

				if (file.fail())
				{
					FatalErrorIn(FunctionSIG)
						<< "file was not found" << endl
						<< abort(FatalError);
				}

				boost::archive::polymorphic_text_iarchive ia(file);

				body_t body;
				ia >> body;

				if (verbose)
				{
					Info << "the file: " << address << " has been loaded, successfully." << endl;
				}

				if (NOT body)
				{
					FatalErrorIn(FunctionSIG)
						<< "the body is empty" << endl
						<< abort(FatalError);
				}
				myBodies.push_back(std::move(body));
				++i;
			}

			else
			{
				break;
			}
		}

		if (verbose)
		{
			Info << myBodies.size() << " The body(s) has(have) been loaded successfully." << endl;
		}

		auto type = myBodies[0]->Type();
		for (const auto& x : myBodies)
		{
			if (type NOT_EQUAL x->Type())
			{
				FatalErrorIn(FunctionSIG)
					<< " The bodies' types are not the same. " << endl
					<< abort(FatalError);
			}
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myBodies;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void bodyListMaker(const module_t& mod)
	{

		mod->add(chaiscript::fun([](const std::string& name)-> void { loadBodies(name); }), "loadBodies");
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

			bodyListMaker(mod);

			chai.add(mod);

			fileName myFileName("bodyList");

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