#include <Entity3d_Polygon.hxx>
#include <Entity3d_Chain.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Wire.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Sections.hxx>
#include <Marine_SectTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<Marine_CmpSection> section_t;
	static std::vector<section_t> mySections;

	static bool tag = false;
	static size_t verbose = 0;

	void loadSections(const std::string& name)
	{
		if (verbose)
		{
			Info << " loading the sections..." << endl;
		}
		
		fileName fn(name);
		std::fstream file;
		file.open(fn, std::ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(file);
		ia >> mySections;

		if (mySections.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no section has been loaded" << endl
				<< abort(FatalError);
		}

		for (const auto& x : mySections)
		{
			if (!x)
			{
				FatalErrorIn(FunctionSIG)
					<< "null section has been detected!" << endl
					<< abort(FatalError);
			}
		}

		tag = true;

		if (verbose)
		{
			Info << " sections are loaded, successfully!" << endl;
			Info << " - nb. of sections: " << mySections.size() << endl;
		}
	}

	enum class sectType
	{
		x,
		z
	};

	auto retrieveChain(const std::shared_ptr<Entity2d_Polygon>& poly, const Standard_Real coord, sectType t)
	{
		auto chain = std::make_shared<Entity3d_Chain>();
		std::vector<Pnt3d> pnts;
		pnts.reserve(poly->NbPoints());
		if (t IS_EQUAL sectType::x)
		{
			for (const auto& x : poly->Points())
			{
				Pnt3d pt(coord, x.X(), x.Y());
				pnts.push_back(std::move(pt));
			}
		}
		else
		{
			for (const auto& x : poly->Points())
			{
				Pnt3d pt(x.X(), x.Y(), coord);
				pnts.push_back(std::move(pt));
			}
		}
		chain->Points() = std::move(pnts);
		auto indices = dualConnectivityList_Chain(poly->NbPoints() - 1);
		chain->Connectivity() = std::move(indices);
		return std::move(chain);
	}

	auto retrieveChain_outer(const std::shared_ptr<Marine_Section>& s, const Standard_Real coord, sectType t)
	{
		auto total = std::make_shared<Entity3d_Chain>();
		const auto& wire = s->Wire();
		for (const auto& x : wire->Edges())
		{
			const auto& mesh = x->Mesh();
			if (NOT mesh)
			{
				FatalErrorIn(FunctionSIG)
					<< "null mesh is detected!" << endl
					<< abort(FatalError);
			}
			auto chain = retrieveChain(mesh, coord, t);
			total->Add(*chain);
		}
		return std::move(total);
	}

	auto retrieveChain_Inners(const std::shared_ptr<Marine_Section>& s, const Standard_Real coord, sectType t)
	{
		auto total = std::make_shared<Entity3d_Chain>();
		auto inners = Marine_SectTools::RetrieveInners(s);
		for (const auto& x : inners)
		{
			auto chain = retrieveChain_outer(x, coord, t);
			if (chain)
			{
				total->Add(*chain);
			}
		}
		return std::move(total);
	}

	auto retrieveChain(const section_t& s, const Standard_Real coord, sectType t)
	{
		auto total = std::make_shared<Entity3d_Chain>();
		for (const auto& x : s->Sections())
		{
			auto chain = retrieveChain_outer(x, coord, t);
			if (chain)
			{
				total->Add(*chain);
			}

			if (Marine_SectTools::HasInnerSection(x))
			{
				auto chain_inner = retrieveChain_Inners(x, coord, t);
				if (chain_inner)
				{
					total->Add(*chain_inner);
				}
			}
		}
		return std::move(total);
	}

	void exportToPlt(const std::string& name)
	{
		if (!tag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no section list has been loaded!" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		OFstream f(fn);

		for (const auto& x : mySections)
		{
			if (x)
			{
				if (x->IsXsection())
				{
					auto chain = retrieveChain(x, x->X(), sectType::x);
					if (chain)
					{
						chain->ExportToPlt(f);
					}
				}
				else
				{
					auto chain = retrieveChain(x, x->X(), sectType::z);
					if (chain)
					{
						chain->ExportToPlt(f);
					}
				}
			}
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadSections(name); }), "loadSections");
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

			fileName myFileName("TnbMarineSectionViewer");

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