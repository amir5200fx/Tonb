#include <Cad_tModelMaker.hxx>
#include <Cad_tModelMakerInfo_Absolute.hxx>
#include <Cad_tEdgeMakerInfo_Absolute.hxx>
#include <Cad_tSurfaceMakerInfo_Absolute.hxx>
#include <Cad_tModelMaker_OnePtDistPairCrvCriterion.hxx>
#include <Cad_CurveLength_Info.hxx>
#include <Cad_CurveSplitter_Info.hxx>
#include <Cad_MultiVolume.hxx>
#include <Cad_SingleVolume.hxx>
#include <Cad_Solid.hxx>
#include <Cad_Shape.hxx>
#include <Cad_TModel.hxx>
#include <Cad_Tools.hxx>
#include <TModel_Surface.hxx>
#include <TModel_GeneratedEdge.hxx>
#include <TModel_Wire.hxx>
#include <TModel_ParaCurve.hxx>
#include <Pln_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <Entity2d_Chain.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static double myTol = 1.0E-6;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static const auto model_directory = "shape";

	static std::shared_ptr<Cad_Volume> myModel;
	static std::shared_ptr<Cad_Shape> myShape;
	static std::string myFileName;

	static auto myCrvLenInfo = std::make_shared<Cad_CurveLength_Info>();
	static auto myCrvSplitInfo = std::make_shared<Cad_CurveSplitter_Info>();

	static auto myEdgeMakerInfo = std::make_shared<Cad_tEdgeMakerInfo_Absolute>();
	static auto mySurfMakerInfo = std::make_shared<Cad_tSurfaceMakerInfo_Absolute>();
	static auto myModelMakerInfo = std::make_shared<Cad_tModelMakerInfo_Absolute>();
	static auto myPairCriterion = std::make_shared<cadLib::tModelMaker_OnePtDistPairCrvCriterion>(myCrvLenInfo, myCrvSplitInfo);

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTol(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the tolerance is set to: " << myTol << endl;
		}
	}

	void loadShape()
	{
		myShape = file::LoadSingleFile<std::shared_ptr<Cad_Shape>>
			(
				model_directory,
				Cad_Shape::extension,
				verbose, 
				myFileName
				);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded." << endl
				<< abort(FatalError);
		}
	}

	void loadShapeFile(const std::string& name)
	{
		file::CheckExtension(name);
		myShape =
			file::LoadFile<std::shared_ptr<Cad_Shape>>
			(name + Cad_Shape::extension, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded." << endl
				<< abort(FatalError);
		}
		myFileName = name;
		loadTag = true;
	}

	void loadFile()
	{
		if (file::IsDirectory(model_directory))
		{
			loadShape();
		}
		else
		{
			auto name =
				file::GetSingleFile

				(boost::filesystem::current_path(),
					Cad_Shape::extension
				).string();
			loadShapeFile(name);
		}
		loadTag = true;
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
		file::SaveTo(myModel, name + Cad_Volume::extension, verbose);
	}

	void saveTo()
	{
		saveTo(myFileName);
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		const auto d = myShape->BoundingBox()->Diameter();
		myPairCriterion->SetTolerance(myTol * d);
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			auto myModelInfo = std::make_shared<Cad_tModelMaker::MakerInfo>();
			myModelInfo->edgeInfo = myEdgeMakerInfo;
			myModelInfo->modelInfo = myModelMakerInfo;
			myModelInfo->surfInfo = mySurfMakerInfo;

			auto shapes = Cad_Tools::RetrieveSolids(myShape->Shape());
			if (NOT shapes.size())
			{
				FatalErrorIn(FunctionSIG)
					<< "no solid has been detected." << endl
					<< abort(FatalError);
			}
			if (shapes.size() == 1)
			{
				auto solid = Cad_Solid::MakeSolid(shapes.at(0), {
					                                  myModelMakerInfo, myEdgeMakerInfo, mySurfMakerInfo,
					                                  myPairCriterion
				                                  });
				if (verbose)
				{
					Info << endl;
					Info << " - Number of corners: " << solid->NbCorners() << endl
						<< " - Number of segments: " << solid->NbSegments() << endl
						<< " - Number of faces: " << solid->NbFaces() << endl << endl;
				}
				myModel = std::make_shared<Cad_SingleVolume>(std::move(solid));
			}
			else if (shapes.size() > 1)
			{
				size_t k = 0;
				Info << endl;
				std::vector<std::shared_ptr<Cad_Solid>> solids;
				for (const auto& x: shapes)
				{
					auto solid = Cad_Solid::MakeSolid(x, {
													  myModelMakerInfo, myEdgeMakerInfo, mySurfMakerInfo,
													  myPairCriterion
						});
					if (verbose)
					{
						
						Info << " * Shape number " << ++k << ":" << endl;
						Info << " - Number of corners: " << solid->NbCorners() << endl
							<< " - Number of segments: " << solid->NbSegments() << endl
							<< " - Number of faces: " << solid->NbFaces() << endl << endl;
					}
					solids.emplace_back(std::move(solid));
				}
				const auto model = std::make_shared<Cad_MultiVolume>(std::move(solids));
				Cad_Tools::RenumberSurfaces(model);
				myModel = model;
			}
			if (verbose > 1)
			{
				Cad_tModelMaker::verbose = 1;
			}
		}
		
		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< "- the application is performed, successfully, in " << global_time_duration << " ms." << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}
		execute(myShape->Name());
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
		// io functions [1/31/2022 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadShapeFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		// operators [1/31/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");

		// settings [1/31/2022 Amir]
		mod->add(chaiscript::fun([](double x)-> void {setTol(x); }), "setTolerance");
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
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
	FatalConvError.throwExceptions();

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
			Info << " This application is aimed to create a solid from a shape." << endl << endl;

			Info << " You can load the shape from 'shape' directory." << endl;
			Info << " WARNING! Make sure there is only one volume in the shape." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setTolerance(double)" << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute(name [optional])" << endl
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
				auto address = file::GetSystemFile("tnbCadSolid");
				fileName myFileName(address);

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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}