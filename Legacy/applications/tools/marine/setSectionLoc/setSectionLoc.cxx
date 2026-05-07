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

	section_t mySection;

	static bool tag = false;
	static size_t verbose = 0;

	void loadSection(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
			Info << " loading the section..." << endl;
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
		ia >> mySection;

		if (NOT mySection)
		{
			FatalErrorIn(FunctionSIG)
				<< " the section is null" << endl
				<< abort(FatalError);
		}

		tag = true;

		if (verbose)
		{
			Info << endl;
			Info << " the section is loaded, from: " << fn << ",successfully!" << endl;
		}
	}

	void setLocation(double x)
	{
		Marine_SectTools::SetLocation(mySection, x);

		if (verbose)
		{
			Info << endl;
			Info << " the location of the section is changed!" << endl
				<< " - x: " << mySection->X() << endl;
		}

		tag = true;
	}

	void saveTo(const std::string & name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << mySection;

		if (verbose)
		{
			Info << endl;
			Info << " the section has been saved in: " << fn << endl;
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

	void SectionMaker(const module_t& mod)
	{

		mod->add(chaiscript::fun([](const std::string& name)-> void { loadSection(name); }), "loadSection");
		mod->add(chaiscript::fun([](double x)-> void {setLocation(x); }), "setLocation");
		mod->add(chaiscript::fun([](int i)-> void {verbose = i; }), "setVerbose");
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

			SectionMaker(mod);

			chai.add(mod);

			fileName myFileName("TnbSetSectionLoc");

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