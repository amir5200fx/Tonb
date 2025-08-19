#include <BoundarySizeMap2d_CornerTool.hxx>
#include <Mesh2d_SolutionData.hxx>
#include <Cad2d_Plane.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Mesh2d_SolutionData> mySoluData;
	static std::shared_ptr<BoundarySizeMap2d_CornerTool> mySizeMapTool;

	// settings [8/13/2021 Amir]
	static unsigned int myUnbalancing = 2;
	static unsigned int myMinSubdivision = 3;
	static unsigned int myMaxSubdivision = 8;

	void setUnbalancing(int i)
	{
		myUnbalancing = i;
		if (verbose)
		{
			Info << endl
				<< " - the unbalancing is set to: " << myUnbalancing << endl;
		}
	}

	void setMinSub(int i)
	{
		myMinSubdivision = i;
		if (verbose)
		{
			Info << endl
				<< " - the min. nb. of subdivisions is set to: " << myMinSubdivision << endl;
		}
	}

	void setMaxSub(int i)
	{
		myMaxSubdivision = i;
		if (verbose)
		{
			Info << endl
				<< " - the max. nb. of subdivisions is set to: " << myMaxSubdivision << endl;
		}
	}

	void loadSoluData(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> mySoluData;
		}

		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< " the solution data is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the algorithm has not been performed" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << mySoluData;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveBackMeshTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the algorithm has not been performed" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << mySizeMapTool->BackgroundMesh();

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& refValues = mySoluData->References();
		const auto& geom = mySoluData->Geometry();

		mySizeMapTool = std::make_shared<BoundarySizeMap2d_CornerTool>(refValues, geom);
		mySizeMapTool->SetMaxSubdivision(myMaxSubdivision);
		mySizeMapTool->SetMinSubdivision(myMinSubdivision);
		mySizeMapTool->SetUnbalancing(myUnbalancing);

		mySizeMapTool->Perform();

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
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadSoluData(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveBackMeshTo(name); }), "saveBackMeshTo");
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");


		// settings [8/13/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](unsigned short i)-> void {BoundarySizeMap2d_CornerTool::verbose = i; }), "setToolVerbose");
		mod->add(chaiscript::fun([](int i)-> void {setUnbalancing(i); }), "setUnbalancing");
		mod->add(chaiscript::fun([](int i)-> void {setMinSub(i); }), "setMinSubdivision");
		mod->add(chaiscript::fun([](int i)-> void {setMaxSub(i); }), "setMaxSubdivision");
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

			setFuns(mod);

			chai.add(mod);

			fileName myFileName("cornerSizeMap2d");

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
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Undefined command has been detected!" << endl
				<< abort(FatalError);
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}