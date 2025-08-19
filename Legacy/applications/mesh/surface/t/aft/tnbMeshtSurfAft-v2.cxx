#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Cad_TModel.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Entity3d_SurfTriangulation.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NelderMeadInfo.hxx>
#include <Global_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Cad_TModel> myModel;
	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;
	static std::shared_ptr<Mesh_Curve_Info> myGlobalCurveInfo;
	static std::map<int, std::shared_ptr<Mesh_Curve_Info>> myLocalCurveInfo;

	static std::shared_ptr<std::map<int, std::shared_ptr<Entity3d_SurfTriangulation>>> myMesh;

	static unsigned short verbose = 0;
	static auto loadTag = false;
	static auto exeTag = false;


	static auto myIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static auto mySizeCorrIterInfo = std::make_shared<Aft_SizeCorr_IterativeInfo>();

	RunTimeConfigs(IntegInfo);
	SetRunTimeConfigs(IntegInfo)
	{
		myIntegInfo->SetMaxNbIterations(200);
		myIntegInfo->SetNbInitIterations(4);
		myIntegInfo->SetTolerance(1.0E-4);
	}

	RunTimeConfigs(SizeCorrIterInfo);
	SetRunTimeConfigs(SizeCorrIterInfo)
	{
		mySizeCorrIterInfo->SetIgnoreNonConvergency(true);
		mySizeCorrIterInfo->SetMaxNbIters(100);
		mySizeCorrIterInfo->SetTolerance(1.0E-5);
		mySizeCorrIterInfo->SetUnderRelaxation(0.85);
	}

	static auto myNelderMeadInfo = std::make_shared<NumAlg_NelderMeadInfo>();

	RunTimeConfigs(NelderMeadInfo);
	SetRunTimeConfigs(NelderMeadInfo)
	{
		myNelderMeadInfo->SetMaxNbIterations(50);
		myNelderMeadInfo->SetTolerance(1.0E-3);
	}

	void setMaxNbIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo, int n)
	{
		theInfo->SetMaxNbIterations(n);
		if (verbose)
		{
			Info << endl
				<< " - the maximum no. of iterations is set to: " << theInfo->MaxNbIterations() << endl;
		}
	}

	void setNbInitIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo, int n)
	{
		theInfo->SetNbInitIterations(n);
		if (verbose)
		{
			Info << endl
				<< " - the no. of initial iterations is set to: " << theInfo->NbInitIterations() << endl;
		}
	}

	void setTolerance(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo, double x)
	{
		theInfo->SetTolerance(x);
		if (verbose)
		{
			Info << endl
				<< " - the tolerance of the adaptive integration is set to: " << theInfo->Tolerance() << endl;
		}
	}

	void setMaxNbIters(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo, int n)
	{
		theInfo->SetMaxNbIters(n);
		if (verbose)
		{
			Info << endl
				<< " - the max. no. of iterations of the size corr. is set to: " << theInfo->MaxNbIters() << endl;
		}
	}

	void setTolerance(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo, double x)
	{
		theInfo->SetTolerance(x);
		if (verbose)
		{
			Info << endl
				<< " - the tolerance of the size corr. is set to: " << theInfo->Tolerance() << endl;
		}
	}

	void setUr(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo, double x)
	{
		theInfo->SetUnderRelaxation(x);
		if (verbose)
		{
			Info << endl
				<< " - the under relaxation of the size corr. is set to: " << theInfo->UnderRelaxation() << endl;
		}
	}

	void setNbIters(const std::shared_ptr<NumAlg_NelderMeadInfo>& theInfo, int n)
	{
		theInfo->SetMaxNbIterations(n);
		if (verbose)
		{
			Info << endl
				<< " - the max. no. of iterations of the Nelder-Mead is set to: " << theInfo->MaxNbIterations() << endl;
		}
	}

	void setTolerance(const std::shared_ptr<NumAlg_NelderMeadInfo>& theInfo, double x)
	{
		theInfo->SetTolerance(x);
		if (verbose)
		{
			Info << endl
				<< " - the tolerance of the Nelder-Mead is set to: " << theInfo->Tolerance() << endl;
		}
	}

	void loadModel()
	{
		static const auto current_directory = "model";
		myModel = file::LoadSingleFile<std::shared_ptr<Cad_TModel>>(current_directory, Cad_TModel::extension, verbose);
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded." << endl
				<< abort(FatalError);
		}
	}

	void loadSizeFun()
	{
		static const auto current_directory = "sizeMap";
		mySizeFun = file::LoadSingleFile<std::shared_ptr<Geo3d_SizeFunction>>(current_directory, Geo3d_SizeFunction::extension, verbose);
		if (NOT mySizeFun)
		{
			FatalErrorIn(FunctionSIG)
				<< "no size function has been loaded." << endl
				<< abort(FatalError);
		}
	}

	void loadCurveInfo()
	{
		static const auto current_directory = "curveInfo";
		myGlobalCurveInfo = file::LoadSingleFile<std::shared_ptr<Mesh_Curve_Info>>(current_directory, Mesh_Curve_Info::extension, verbose);
		if (NOT myGlobalCurveInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve info. has been loaded." << endl
				<< abort(FatalError);
		}

		// get the current path [6/11/2023 Payvand]
		const auto current_path = boost::filesystem::current_path();

		// change the current path [6/11/2023 Payvand]
		boost::filesystem::current_path(current_path.string() + R"(\)" + current_directory);
		{
			const auto subCurrentPath = boost::filesystem::current_path();
			// load the subs [6/11/2023 Payvand]
			for
				(
					boost::filesystem::directory_iterator iter(subCurrentPath);
					iter != boost::filesystem::directory_iterator();
					iter++
					)
			{
				auto fname = iter->path().string();
				if (Global_Tools::IsNumber(fname))
				{
					auto curveNb = std::stoi(fname);
					// Change the current path [12/2/2021 Amir]
					boost::filesystem::current_path(subCurrentPath.string() + R"(\)" + fname);

					try
					{
						auto name = file::GetSingleFile(boost::filesystem::current_path(), Mesh_Curve_Info::extension).string();
						auto curveInfo = file::LoadFile<std::shared_ptr<Mesh_Curve_Info>>(name + Mesh_Curve_Info::extension, verbose);
						if (NOT curveInfo)
						{
							FatalErrorIn(FunctionSIG)
								<< " the info curve file is null!" << endl
								<< abort(FatalError);
						}

						auto paired = std::make_pair(curveNb, std::move(curveInfo));
						auto insert = myLocalCurveInfo.insert(std::move(paired));
						if (NOT insert.second)
						{
							FatalErrorIn(FunctionSIG)
								<< "unable to insert the curve info into the map!" << endl
								<< " Duplicate data maybe?!" << endl
								<< abort(FatalError);
						}

						if (verbose)
						{
							Info << " - the curve info, " << curveNb << ", has been loaded, successfully!" << endl;
						}
					}
					catch (const error& x)
					{
						Info << " - Couldn't load the curve info: " << endl;
						Info << x.message() << endl;
					}
				}
			}
		}

	}
}