#include <Aft3d_SolutionData_SurfVol.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Cad_Volume.hxx>
#include <GModel_Tools.hxx>
#include <GModel_ParaWire.hxx>
#include <GModel_Surface.hxx>
#include <GModel_Plane.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static unsigned short verbose = 0;
	static bool exeTag = false;
	static bool loadTag = false;

	static double myTol = 1.0E-6;

	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;
	static std::shared_ptr<Mesh_Curve_Info> myCurveInfo;
	static std::shared_ptr<Cad_Volume> myModel;

	static std::shared_ptr<Aft3d_SolutionData_SurfVol> mySolutionData;

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTolerance(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the tolerance is set to: " << myTol << endl;
		}
	}

	bool isNumber(const std::string s)
	{
		if (s.size() IS_EQUAL 0) return false;
		for (int i = 0; i < s.size(); i++)
		{
			if ((s[i] >= '0' && s[i] <= '9') IS_EQUAL false)
			{
				return false;
			}
		}
		return true;
	}

	void loadModelFile()
	{
		checkFolder("model");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/4/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\model)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_Volume::extension).string();

		myModel = file::LoadFile<std::shared_ptr<Cad_Volume>>(name + Cad_Volume::extension, verbose);
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< " the model file is null!" << endl
				<< abort(FatalError);
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadModelFile(const std::string& name)
	{
		file::CheckExtension(name);
		myModel = file::LoadFile<std::shared_ptr<Cad_Volume>>(name + Cad_Volume::extension, verbose);
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< " the model file is null!" << endl
				<< abort(FatalError);
		}
	}

	auto loadCurveInfo()
	{
		checkFolder("curve");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/4/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\curve)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Mesh_Curve_Info::extension).string();

		auto glCurveInfo = file::LoadFile<std::shared_ptr<Mesh_Curve_Info>>(name + Mesh_Curve_Info::extension, verbose);
		if (NOT glCurveInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< " the global curve info file is null" << endl
				<< abort(FatalError);
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);

		//auto t = std::make_tuple(std::move(glCurveInfo), std::move(curveInfoMap));
		return std::move(glCurveInfo);
	}

	void loadCurveInfo(const std::string& name)
	{
		file::CheckExtension(name);

		myCurveInfo = file::LoadFile<std::shared_ptr<Mesh_Curve_Info>>(name + Mesh_Curve_Info::extension, verbose);
		if (NOT myCurveInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< " the global curve info file is null" << endl
				<< abort(FatalError);
		}
	}

	void loadSizeFunction()
	{
		checkFolder("sizeMap");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/4/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\sizeMap)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Geo3d_SizeFunction::extension).string();

		mySizeFun = file::LoadFile<std::shared_ptr<Geo3d_SizeFunction>>(name + Geo3d_SizeFunction::extension, verbose);
		if (NOT mySizeFun)
		{
			FatalErrorIn(FunctionSIG)
				<< " the size function file is null" << endl
				<< abort(FatalError);
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadSizeFunction(const std::string& name)
	{
		file::CheckExtension(name);

		mySizeFun = file::LoadFile<std::shared_ptr<Geo3d_SizeFunction>>(name + Geo3d_SizeFunction::extension, verbose);
		if (NOT mySizeFun)
		{
			FatalErrorIn(FunctionSIG)
				<< " the size function file is null" << endl
				<< abort(FatalError);
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(mySolutionData, name + Aft3d_SolutionData_SurfVol::extension, verbose);
	}

	void loadFiles()
	{
		loadModelFile();
		loadCurveInfo();
		loadSizeFunction();
	}

	void execute()
	{
		//loadModelFile();
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the geometrical model is not loaded." << endl
				<< abort(FatalError);
		}
		if (NOT mySizeFun)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " the size function is not loaded." << endl
				<< abort(FatalError);
		}
		if (NOT myCurveInfo)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " the curve info. is not loaded." << endl
				<< abort(FatalError);
		}

		//loadSizeFunction();
		//loadCurveInfo();

		auto soluData = std::make_shared<Aft3d_SolutionData_SurfVol>();

		soluData->SetGeometry(myModel);
		soluData->SetSizeFunction(mySizeFun);
		soluData->SetCurveInfo(myCurveInfo);

		mySolutionData = std::move(soluData);

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " the application is performed successfully!" << endl;
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

	void setFunctions(const module_t& mod)
	{
		// io functions [2/23/2022 Amir]
		//mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModelFile(name); }), "loadModel");
		mod->add(chaiscript::fun([]()->void {loadModelFile(); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadCurveInfo(name); }), "loadCurveInfo");
		mod->add(chaiscript::fun([]()-> void {loadCurveInfo(); }), "loadCurveInfo");
		mod->add(chaiscript::fun([](const std::string& name)->void {loadSizeFunction(name); }), "loadSizeFunction");
		mod->add(chaiscript::fun([]()->void {loadSizeFunction(); }), "loadSizeFunction");
		mod->add(chaiscript::fun([]()->void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [2/23/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [2/23/2022 Amir]
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

int main(int argc, char* argv[])
{
	//FatalError.throwExceptions();

	if (argc <= 1)
	{
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a solution data of the surface mesh of a volume." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				/*<< " - loadFile()" << endl*/
				<< " - loadModel(name [optional])" << endl
				<< " - loadCurveInfo(name [optional])" << endl
				<< " - loadSizeFunction(name [optional])" << endl
				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

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
				fileName theFileName(file::GetSystemFile("tnbMeshVolumeBndSoluDataAft"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}