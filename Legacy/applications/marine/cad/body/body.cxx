#include <Marine_PlnCurves.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_Section.hxx>
#include <Marine_SectionType.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Bodies.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Marine_TankModeler.hxx>
#include <Marine_SailModeler.hxx>
#include <Marine_DisplacerModeler.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>


#include <vector>
#include <algorithm>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<Marine_CmpSection> section_t;
	static std::vector<section_t> mySections;

	static Marine_SectionType bodyType;
	static std::shared_ptr<Marine_Body> myBody;

	static bool tag = false;
	static size_t verbose = 0;


	void loadSections(const std::string& name)
	{
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

		const auto& section = mySections[0];

		switch (section->Type())
		{
		case Marine_SectionType::displacer:
			bodyType = Marine_SectionType::displacer;
			break;

		case Marine_SectionType::sail:
			bodyType = Marine_SectionType::sail;
			break;

		case Marine_SectionType::tank:
			bodyType = Marine_SectionType::tank;
			break;

		default:
			FatalErrorIn(FunctionSIG)
				<< "the section type is not supported" << endl
				<< abort(FatalError);
			break;
		}

		for (const auto& x : mySections)
		{
			if (x->Type() NOT_EQUAL bodyType)
			{
				FatalErrorIn(FunctionSIG)
					<< "section types must be the same." << endl
					<< abort(FatalError);
			}
		}

		tag = true;

		if (verbose)
		{
			Info << " the section list is loaded, successfully!" << endl;
		}
	}

	void sortSections(std::vector<section_t>& sections)
	{
		std::sort
		(
			sections.begin(), 
			sections.end(), 
			[](const section_t& s0, const section_t& s1)->bool {return s0->X() < s1->X(); }
		);
	}

	void makeBody()
	{
		if (!tag)
		{
			FatalErrorIn(FunctionSIG)
				<< "sections have not been loaded." << endl
				<< abort(FatalError);
		}

		for (size_t i = 1; i < mySections.size() - 1; i++)
		{
			if (mySections[i]->X() <= mySections[i - 1]->X())
			{
				sortSections(mySections);
				break;
			}
		}

		switch (bodyType)
		{
		case tnbLib::Marine_SectionType::displacer:
		{
			myBody = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Displacer>>(std::move(mySections));
			break;
		}
		case tnbLib::Marine_SectionType::sail:
		{
			myBody = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Sail>>(std::move(mySections));
			break;
		}
		case tnbLib::Marine_SectionType::tank:
		{
			myBody = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Tank>>(std::move(mySections));
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "This body type is not allowed." << endl
				<< abort(FatalError);
		}
		if (verbose)
		{
			Info << " the body is created, successfully!" << endl;
			Info << " - body type: ";
			switch (bodyType)
			{
			case tnbLib::Marine_SectionType::displacer:
				Info << "displacer" << endl;
				break;
			case tnbLib::Marine_SectionType::sail:
				Info << "sail" << endl;
				break;
			case tnbLib::Marine_SectionType::tank:
				Info << "tank" << endl;
				break;
			default:
				FatalErrorIn(FunctionSIG)
					<< "unspecified type of body has been detected!" << endl
					<< abort(FatalError);
				break;
			}
		}
	}

	void saveTo(const std::string& name) 
	{
		if (NOT myBody)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myBody;

		if (verbose)
		{
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
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

		mod->add(chaiscript::fun([](const std::string& name)-> void { loadSections(name); }), "loadSections");
		mod->add(chaiscript::fun([]()-> void {makeBody(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](int i)-> void {verbose = i; }), "setVerbose");

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

			fileName myFileName("TnbBodyMaker");

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