#include <Aft2d_SolutionData.hxx>
#include <Aft2d_SolutionDataAnIso.hxx>
#include <Aft2d_BoundaryOfPlane_Info.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_Element.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Vertex.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

//BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoSizeFun2d_Uniform);

namespace tnbLib
{

	static const std::string extension = Aft2d_SolutionData::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static double minTol = 1.0E-6;

	static std::shared_ptr<Aft2d_SolutionDataBase> mySoluData;
	static std::string myFileName;

	static bool overrideInfo = true;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setMinTol(double x)
	{
		minTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the min. of tolerance is set to: " << minTol << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_SolutionDataBase>>(name + extension, verbose);
		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "the data solution file is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
		loadFile(name);
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

		file::SaveTo(mySoluData, name + extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	auto retrieveMaxTol(const std::shared_ptr<Cad2d_Plane>& plane)
	{
		std::vector<std::shared_ptr<Pln_Entity>> vertices;
		plane->RetrieveCornersTo(vertices);

		auto maxTol = minTol;
		for (const auto& x : vertices)
		{
			auto vtx = std::dynamic_pointer_cast<Pln_Vertex>(x);
			if (vtx)
			{
				if (vtx->Precision() > maxTol)
				{
					maxTol = vtx->Precision();
				}
			}
		}
		return maxTol;
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& plane = mySoluData->Plane();
		if (NOT plane)
		{
			FatalErrorIn(FunctionSIG)
				<< "no plane has been detected!" << endl
				<< abort(FatalError);
		}

		const auto maxTol = retrieveMaxTol(plane);

		if (mySoluData->IsIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionData>(mySoluData);
			Debug_Null_Pointer(soluData);

			auto myInfo = std::make_shared<Aft2d_BoundaryOfPlane_Info>();

			myInfo->SetMergeTolerance(maxTol*1.05);
			myInfo->SetOverrideInfo(overrideInfo);

			myInfo->OverrideGlobalCurve(soluData->GlobalCurveInfo());
			myInfo->OverrideGlobalMetricPrcsr(soluData->GlobalMetricInfo());
			myInfo->Curve() = soluData->CurveInfo();

			soluData->SetBoundaryInfo(std::move(myInfo));
		}
		else if (mySoluData->IsAnIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionDataAnIso>(mySoluData);
			Debug_Null_Pointer(soluData);

			auto myInfo = std::make_shared<Aft2d_BoundaryOfPlaneAnIso_Info>();

			myInfo->SetMergeTolerance(maxTol*1.05);
			myInfo->SetOverrideInfo(overrideInfo);

			myInfo->OverrideGlobalCurve(soluData->GlobalCurveInfo());
			myInfo->OverrideGlobalMetricPrcsr(soluData->GlobalMetricInfo());
			myInfo->Curve() = soluData->CurveInfo();

			soluData->SetBoundaryInfo(std::move(myInfo));
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified type of data has been detected!" << endl
				<< abort(FatalError);
		}

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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

	void setFuns(const module_t& mod)
	{
		// io functions [12/12/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/12/2021 Amir]

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setMinTol(x); }), "setMinTol");

		// operators [12/12/2021 Amir]

		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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
			Info << " This application is aimed to create plane boundary info." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setMinTol(x)" << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshPlaneBndInfo"));

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