#include <Marine_Bodies.hxx>
#include <Marine_Models.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	

	std::vector<std::shared_ptr<marineLib::Model_Sail>> myBodies;

	static bool loadTag = false;
	static bool exeTag = false;

	static unsigned short verbose(0);

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadBodies()
	{
		if (verbose)
		{
			Info << "loading the bodies..." << endl;
			Info << endl;
		}

		size_t i = 0;
		while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
		{
			auto name = file::GetSingleFile()
			auto name = getSingleFile(boost::filesystem::path(std::to_string(i)));
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ia(file);

			std::shared_ptr<Marine_Body> body;
			ia >> body;

			if (NOT body)
			{
				FatalErrorIn(FunctionSIG)
					<< "the body is null!" << endl
					<< abort(FatalError);
			}

			if (verbose)
			{
				Info << " - body, " << i << ", is loaded from: " << address << ", successfully!" << endl;
			}

			auto model = std::make_shared<marineLib::Model_Sail>(i + 1, body->Name(), std::move(body));

			myBodies.push_back(std::move(body));
			i++;
		}
		if (verbose)
		{
			Info << endl
				<< " All files are loaded, successfully!" << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);

		oa << myBodies;
		if (verbose)
		{
			Info << endl;
			Info << " bodies are saved in: " << fn << ", successfully!" << endl;
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
		mod->add(chaiscript::fun([]()->void {loadBodies(); }), "loadBodies");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](unsigned short c)->void {verbose = c; }), "setVerbose");
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
