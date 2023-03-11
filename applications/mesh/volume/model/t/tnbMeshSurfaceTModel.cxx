#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Cad_ApprxMetricInfo.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fstream>

namespace fs = boost::filesystem;

namespace tnbLib
{

	static std::shared_ptr<Cad_ApprxMetricInfo> myMetricApproxInfo;
	static std::shared_ptr<NumAlg_AdaptiveInteg_Info> myIntegInfo;
	static std::shared_ptr<Aft_SizeCorr_IterativeInfo> myIterInfo;

	static const std::string METRIC_APPROX_INFO_DIRECTORY = "metricInfo";
	static const std::string INTEG_INFO_DIRCETORY = "integInfo";
	static const std::string ITER_INFO_DIRECTORY = "iterInfo";

	static unsigned short verbose = 0;
 
	void checkFolder(const std::string& name)
	{
		if (NOT fs::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void loadMetricApproxInfo()
	{
		checkFolder(METRIC_APPROX_INFO_DIRECTORY);

		const auto currentPath = fs::current_path();

		// change the current path [3/10/2023 Payvand]
		fs::current_path(currentPath.string() + R"(\)" + METRIC_APPROX_INFO_DIRECTORY);
		if (file::IsFile(fs::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(fs::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [3/10/2023 Payvand]
				boost::filesystem::current_path(address);

				auto name = file::GetSingleFile(fs::current_path(), Cad_ApprxMetricInfo::extension).string();
				myMetricApproxInfo = file::LoadFile<std::shared_ptr<Cad_ApprxMetricInfo>>(name + Cad_ApprxMetricInfo::extension, verbose);
				if (NOT myMetricApproxInfo)
				{
					FatalErrorIn(FunctionSIG)
						<< "the metric approx. info is null!" << endl
						<< abort(FatalError);
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto name = file::GetSingleFile(fs::current_path(), Cad_ApprxMetricInfo::extension).string();
			myMetricApproxInfo = file::LoadFile<std::shared_ptr<Cad_ApprxMetricInfo>>(name + Cad_ApprxMetricInfo::extension, verbose);
			if (NOT myMetricApproxInfo)
			{
				FatalErrorIn(FunctionSIG)
					<< "the metric approx. info is null!" << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		fs::current_path(currentPath);
	}

	void loadIntegInfo()
	{
		checkFolder(INTEG_INFO_DIRCETORY);

		const auto currentPath = fs::current_path();

		// change the current path [3/10/2023 Payvand]
		fs::current_path(currentPath.string() + R"(\)" + INTEG_INFO_DIRCETORY);
		if (file::IsFile(fs::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(fs::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [3/10/2023 Payvand]
				boost::filesystem::current_path(address);

				auto name = file::GetSingleFile(fs::current_path(), NumAlg_AdaptiveInteg_Info::extension).string();
				myMetricApproxInfo = file::LoadFile<std::shared_ptr<NumAlg_AdaptiveInteg_Info>>(name + NumAlg_AdaptiveInteg_Info::extension, verbose);
				if (NOT myMetricApproxInfo)
				{
					FatalErrorIn(FunctionSIG)
						<< "the metric approx. info is null!" << endl
						<< abort(FatalError);
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto name = file::GetSingleFile(fs::current_path(), NumAlg_AdaptiveInteg_Info::extension).string();
			myMetricApproxInfo = file::LoadFile<std::shared_ptr<NumAlg_AdaptiveInteg_Info>>(name + NumAlg_AdaptiveInteg_Info::extension, verbose);
			if (NOT myMetricApproxInfo)
			{
				FatalErrorIn(FunctionSIG)
					<< "the metric approx. info is null!" << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		fs::current_path(currentPath);
	}
}