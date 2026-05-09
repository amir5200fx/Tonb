#include <Pln_Edge.hxx>
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

	typedef std::shared_ptr<Pln_Edge> edge_t;

	static std::vector<edge_t> myEdges;

	static bool tag = false;
	static bool verbose = false;

	void loadEdges(const std::string& name)
	{
		if (verbose)
		{
			Info << " loading the edges..." << endl;
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

			TNB_iARCH_FILE_TYPE ia(file);

			edge_t curve;
			ia >> curve;

			if (verbose)
			{
				Info << " curve, " << i << ", is loaded from: " << address << ", successfully!" << endl;
			}

			myEdges.push_back(std::move(curve));

			i++;
		}
		if (verbose)
		{
			if (myEdges.size() > 1)
			{
				Info << endl;
				Info << " " << myEdges.size() << " nb. of edges have been loaded" << endl;
			}
			else
			{
				Info << endl;
				Info << " " << myEdges.size() << " nb. of edge has been loaded" << endl;
			}
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);

		oa << myEdges;
		if (verbose)
		{
			Info << " curves are saved in: " << fn << ", successfully!" << endl;
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadEdges(name); }), "loadEdges");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](bool c)->void {verbose = c; }), "setVerbose");
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

			fileName myFileName("TnbEdgeList2d");

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