#include <Marine_Models.hxx>

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
	typedef std::shared_ptr<Marine_Model> model_t;

	static std::vector<model_t> myModels;

	static bool verbose = false;

	void loadModels(const std::string& name)
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

				model_t model;
				ia >> model;

				if (verbose)
				{
					Info << "the file: " << address << " has been loaded, successfully." << endl;
				}

				if (NOT model)
				{
					FatalErrorIn(FunctionSIG)
						<< "the model is empty" << endl
						<< abort(FatalError);
				}
				myModels.push_back(std::move(model));
				++i;
			}

			else
			{
				break;
			}
		}

		if (verbose)
		{
			Info << myModels.size() << " The model(s) has(have) been loaded successfully." << endl;
		}

		auto type = myModels[0]->Type();
		for (const auto& x : myModels)
		{
			if (type NOT_EQUAL x->Type())
			{
				FatalErrorIn(FunctionSIG)
					<< " The models' types are not the same. " << endl
					<< abort(FatalError);
			}
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myModels;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void modelListMaker(const module_t& mod)
	{

		mod->add(chaiscript::fun([](const std::string& name)-> void { loadModels(name); }), "loadModels");
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

			modelListMaker(mod);

			chai.add(mod);

			fileName myFileName("modelList");

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