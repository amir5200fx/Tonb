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

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{
	static std::vector<std::shared_ptr<Marine_CmpSection>> sections;
	static size_t nbSections = 0;

	static Marine_SectionType bodyType;
	static std::shared_ptr<Marine_Body> myBody;

	static bool tag = false;


	void loadSections(const std::string& name)
	{
		sections.reserve(nbSections);
		for (size_t i = 0; i < nbSections; i++)
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

			boost::archive::polymorphic_text_iarchive oa(file);

			std::shared_ptr<Marine_CmpSection> section;

			oa >> section;
			auto mSection = std::dynamic_pointer_cast<Marine_CmpSection>(section);
			if (!mSection)
			{
				FatalErrorIn(FunctionSIG)
					<< "the section is not marine type" << endl
					<< abort(FatalError);
			}

			sections.push_back(section);
		}

		if (sections.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no section has been loaded" << endl
				<< abort(FatalError);
		}

		const auto section = sections[0];

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

		for (const auto x : sections)
		{
			if (x->Type() NOT_EQUAL bodyType)
			{
				FatalErrorIn(FunctionSIG)
					<< "section types must be the same." << endl
					<< abort(FatalError);
			}
		}

		tag = true;
	}

	void makeBody()
	{
		if (!tag)
		{
			FatalErrorIn(FunctionSIG)
				<< "sections have not been loaded." << endl
				<< abort(FatalError);
		}

		switch (bodyType)
		{
		case tnbLib::Marine_SectionType::displacer:
		{
			myBody = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Displacer>>(std::move(sections));
			break;
		}
		case tnbLib::Marine_SectionType::sail:
		{
			myBody = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Sail>>(std::move(sections));
			break;
		}
		case tnbLib::Marine_SectionType::tank:
		{
			myBody = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Tank>>(std::move(sections));
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "This body type is not allowed." << endl
				<< abort(FatalError);
		}
	}

	void saveTo(const std::string& name) 
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myBody;
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

			fileName myFileName("body");

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