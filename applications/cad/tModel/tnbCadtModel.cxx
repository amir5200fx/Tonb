#include <Cad_tModelMaker.hxx>
#include <Cad_tModelMakerInfo_Absolute.hxx>
#include <Cad_tEdgeMakerInfo_Absolute.hxx>
#include <Cad_tSurfaceMakerInfo_Absolute.hxx>
#include <Cad_tModelMaker_OnePtDistPairCrvCriterion.hxx>
#include <Cad_CurveLength_Info.hxx>
#include <Cad_CurveSplitter_Info.hxx>
#include <Cad_Shape.hxx>
#include <Cad_TModel.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static const std::string loadExt = Cad_Shape::extension;
	static const std::string saveExt = Cad_TModel::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Cad_TModel> myModel;
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

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + loadExt, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the shape file is null!" << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
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

		file::SaveTo(myModel, name + saveExt, verbose);
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

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			auto myModelInfo = std::make_shared<Cad_tModelMaker::MakerInfo>();
			myModelInfo->edgeInfo = myEdgeMakerInfo;
			myModelInfo->modelInfo = myModelMakerInfo;
			myModelInfo->surfInfo = mySurfMakerInfo;

			auto myMaker =
				std::make_shared<Cad_tModelMaker>(myShape->Shape(), myModelInfo, myPairCriterion);
			myMaker->Perform();

			myModel = myMaker->Model();
		}

		if (verbose)
		{
			Info << endl
				<< "- the application is performed, successfully, in "<< global_time_duration << " ms." << endl;
		}
	}
}