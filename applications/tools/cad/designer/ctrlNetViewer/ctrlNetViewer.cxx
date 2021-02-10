#include <Entity3d_Chain.hxx>
#include <Cad_PreviewTools.hxx>
#include <ShapePx_CtrlNet.hxx>
#include <TecPlot.hxx>
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

	typedef std::shared_ptr<ShapePx_CtrlNet> net_t;

	std::vector<net_t> myNets;
	static unsigned short verbose = 0;

	static bool loadTag = false;

	void loadNets(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);

		if (f.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(f);
		ia >> myNets;

		if (verbose)
		{
			Info << endl;
			Info << " the ctrl net list has been loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void exportToPlt(const net_t& net, OFstream& f)
	{
		std::vector<std::vector<Pnt3d>> rows;
		rows.reserve(net->NbRows());
		for (const auto& x : net->Rows())
		{
			std::vector<Pnt3d> row;
			row.reserve(x.NbPnts());
			auto z = x.X();
			for (const auto& p : x.Pnts())
			{
				const auto& pt2 = p.first;
				Pnt3d pt(pt2.X(), pt2.Y(), z);
				row.push_back(std::move(pt));
			}
			rows.push_back(std::move(row));
		}

		auto chain = Cad_PreviewTools::RetrieveChain(rows);
		chain->ExportToPlt(f);
	}

	void exportToPlt(const std::string& name)
	{
		fileName fn(name);
		OFstream f(fn);
		for (const auto& x : myNets)
		{
			if (x)
			{
				exportToPlt(x, f);
			}
		}

		if (verbose)
		{
			Info << endl;
			Info << " the ctrl-nets are exported to *.plt, successfully!" << endl;
			Info << endl;
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {exportToPlt(name); }), "exportToPlt");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("TnbCtrlNetViewer");

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