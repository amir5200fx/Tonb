#include <ShapePx_TopoCtrlNet.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

#include <frameMaker.hxx>
#include <frameTuner.hxx>

#include <vector>
#include <map>

namespace tnbLib
{

	typedef std::shared_ptr<ShapePx_TopoCtrlNet> net_t;

	std::vector<net_t> myNets;
	static unsigned short verbose = 0;

	static bool loadTag = false;

	void loadNets(const std::string& name)
	{
		if (verbose)
		{
			Info << " loading nets..." << endl;
		}

		size_t i = 0;
		while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			std::fstream file;
			file.open(address, std::ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			boost::archive::polymorphic_text_iarchive ia(file);

			net_t net;
			ia >> net;

			if (verbose)
			{
				Info << " net, " << i << ", is loaded from: " << address << ", successfully!" << endl;
			}

			myNets.push_back(std::move(net));

			i++;
		}

		loadTag = true;

		if (verbose)
		{
			Info << endl;
			Info << " " << myNets.size() << " nb. of nets have been loaded" << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (!loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no net has been loaded!" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myNets;
		if (verbose)
		{
			Info << " nets are saved in: " << fn << ", successfully!" << endl;
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadNets(name); }), "loadNets");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](int c)->void {verbose = c; }), "setVerbose");
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
			Info << " This application is aimed to create a list of control nets." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadNets(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl <<endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl

				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbPxModelCtrlNetList";
			fileName myFileName(address);

			try
			{
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