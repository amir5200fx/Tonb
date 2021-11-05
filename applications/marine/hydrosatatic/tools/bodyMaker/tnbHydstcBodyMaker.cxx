#include <Marine_CmpSection.hxx>
#include <Marine_Bodies.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static const std::string loadExt = ".hsslst";
	static const std::string saveExt = Marine_Body::extention;

	static std::string myFileName;

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose(0);

	typedef std::shared_ptr<Marine_CmpSection> section_t;

	static Marine_SectionType bodyType;
	static std::vector<section_t> mySections;

	static std::shared_ptr<Marine_Body> myBody;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel(const std::string& name)
	{
		file::CheckExtension(name);

		mySections = file::LoadFile<std::vector<std::shared_ptr<Marine_CmpSection>>>(name + loadExt, verbose);
		if (mySections.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
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

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void loadModel()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt);
		myFileName = name.string();
		loadModel(myFileName);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myBody, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed" << endl
				<< abort(FatalError);
		}

		saveTo(myFileName);
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

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
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

		exeTag = true;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFunctions(const module_t& mod)
	{
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([]()->void {loadModel(); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
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
			Info << endl;
			Info << " This application is aimed to create a body from a section list." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions:" << endl << endl
				<< " - loadModel(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl
				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);	

			try
			{
				//std::string address = ".\\system\\tnbHydstcBodyMaker";
				fileName myFileName(file::GetSystemFile("tnbHydstcBodyMaker"));

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