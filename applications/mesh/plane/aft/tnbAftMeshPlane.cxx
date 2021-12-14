#include <Aft2d_RegionPlane.hxx>
#include <Aft2d_Model.hxx>
#include <Aft2d_MetricPrcsr.hxx>
#include <Aft2d_SolutionData.hxx>
#include <Aft2d_SolutionDataAnIso.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static const std::string saveExt = Aft2d_SolutionDataBase::extension;
	static const std::string loadExt = Aft2d_SolutionDataBase::extension;

	static std::shared_ptr<Aft2d_SolutionDataBase> mySoluData;

	static std::shared_ptr<Aft2d_Model> myAlg;
	static std::string myFileName;

	static bool loadTag = false;
	static unsigned short verbose = 0;
	static bool exeTag = false;

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_SolutionDataBase>>(name + loadExt, verbose);
		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been found!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), Aft2d_SolutionDataBase::extension).string();
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

		file::SaveTo(mySoluData, name + saveExt, verbose);
	}

	void saveTo()
	{
		saveTo(myFileName);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		if (mySoluData->IsIso())
		{
			auto solutionData = std::dynamic_pointer_cast<Aft2d_SolutionData>(mySoluData);
			Debug_Null_Pointer(solutionData);

			if (const auto& bndPoly = solutionData->BoundaryMesh())
			{

			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "no boundary mesh has been detected!" << endl
					<< abort(FatalError);
			}
		}
		else if (mySoluData->IsAnIso())
		{

		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of solution file has been detected!" << endl
				<< abort(FatalError);
		}
	}
}