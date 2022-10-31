#include <Airfoil_Naca.hxx>
#include <Airfoil_NacaMidline.hxx>
#include <Airfoil_NacaThickness.hxx>
#include <Geo_CosineDistb.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static auto airfoil = std::make_shared<Airfoil_Naca>();
	static std::shared_ptr<Geo_xDistb> myDistb;

	static std::shared_ptr<Airfoil_NacaMidline> myCamber;
	static std::shared_ptr<Airfoil_NacaThickness> myThick;

	static auto myChord = 0.;
	static auto nbSegments = 10;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		airfoil->SetChord(myChord);
		airfoil->SetMidLine(myCamber);
		airfoil->SetThickness(myThick);
		airfoil->SetXc(myDistb);

		airfoil->Perform();
		if (NOT airfoil->IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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

	void setFuns(const module_t& mod)
	{
		// io functions [12/28/2021 Amir]
		//mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		//mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		//mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/28/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/28/2021 Amir]
		//mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
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