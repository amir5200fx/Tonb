#include <HydStatic_SolutionData_GzEff.hxx>
#include <HydStatic_GZ.hxx>
#include <HydStatic_GzEff.hxx>
#include <HydStatic_Shapes.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>
#include <HydStatic_CmptLib.hxx>
#include <HydStatic_Tools.hxx>
#include <HydStatic_rArmCurve_Cmpt.hxx>
#include <HydStatic_rArmCurve_Tanks.hxx>
#include <HydStatic_rArmCurve_FSLq.hxx>
#include <StbGMaker_Model.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>
#include <fstream>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_GzEff> soluData_t;

	static soluData_t mySolutionData;

	static unsigned short verbose = 0;

	void checkData()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been found!" << endl
				<< abort(FatalError);
		}
	}

	void loadSoluData(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the solution data from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		TNB_iARCH_FILE_TYPE ar(myFile);

		ar >> mySolutionData;
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< " the solution data is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the solution data is loaded, successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << mySolutionData;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the solution data is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto retrieveKG()
	{
		if (NOT mySolutionData->Model())
		{
			FatalErrorIn(FunctionSIG)
				<< " no model has been found for the solution data" << endl
				<< abort(FatalError);
		}

		const auto& model = mySolutionData->Model();

		auto vcg = model->LightWeight().Vcg();
		if (NOT vcg.IsSpecified())
		{
			FatalErrorIn(FunctionSIG)
				<< "no vcg has been specified!" << endl
				<< abort(FatalError);
		}

		marineLib::KG kg(vcg());
		return std::move(kg);
	}

	auto hullGZ()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& hull = mySolutionData->Hull();
		if (NOT hull->CrossCurves())
		{
			FatalErrorIn(FunctionSIG)
				<< " no cross-curves has been found for the hull!" << endl
				<< " please, make sure you have run the crossCurves application before running this application." << endl
				<< abort(FatalError);
		}

		const auto kg = retrieveKG();
		const auto& dispv = mySolutionData->DISPV();
		if (NOT dispv.IsSpecified())
		{
			FatalErrorIn(FunctionSIG)
				<< "no dispv has been specified!" << endl
				<< abort(FatalError);
		}

		const auto alg = std::make_shared<HydStatic_GZ>();

		alg->SetBodyType(HydStatic_GZ::bodyType::hull);
		alg->SetDispv(dispv);
		alg->SetKG(kg);
		alg->LoadCrossCurves(hull->CrossCurves());
		alg->Perform();

		auto bodyGz = std::dynamic_pointer_cast<hydStcLib::rArmCurve_Body>(alg->RightingArm());
		if (NOT bodyGz)
		{
			FatalErrorIn(FunctionSIG)
				<< "unexpected error has been occurred" << endl
				<< abort(FatalError);
		}

		return std::move(bodyGz);
	}

	auto tanksGZ()
	{
		marineLib::DISPV dispv;
		const auto& tanks = mySolutionData->Tanks();
		if (tanks.empty())
		{
			return std::shared_ptr<hydStcLib::rArmCurve_Tanks>();
		}
		std::vector<std::shared_ptr<hydStcLib::rArmCurve_FSLq>> curves;
		curves.reserve(tanks.size());
		for (const auto& iter : tanks)
		{
			const auto& x = iter.second;
			if (NOT x->CrossCurves())
			{
				FatalErrorIn(FunctionSIG)
					<< " no cross-curves has been found for the tank!" << endl
					<< " please, make sure you have run the crossCurves application before running this application." << endl
					<< abort(FatalError);
			}

			const auto& kg = x->KG();
			const auto vol = HydStatic_CmptLib::RetrieveDispv(*x);
			dispv() = vol;

			const auto alg = std::make_shared<HydStatic_GZ>();

			alg->SetBodyType(HydStatic_GZ::bodyType::tank);
			alg->SetDispv(dispv);
			alg->SetKG(kg);
			alg->LoadCrossCurves(x->CrossCurves());
			alg->Perform();

			auto flsq = std::dynamic_pointer_cast<hydStcLib::rArmCurve_FSLq>(alg->RightingArm());
			if (NOT flsq)
			{
				FatalErrorIn(FunctionSIG)
					<< "unexpected error has been occurred" << endl
					<< abort(FatalError);
			}
			curves.push_back(std::move(flsq));
		}

		auto cmpt = std::make_shared<hydStcLib::rArmCurve_Cmpt<hydStcLib::rArmCurve_FSLq>>(std::move(curves));
		auto gz = HydStatic_Tools::MakeTanksRightCurve(std::move(cmpt));
		return std::move(gz);
	}

	void execute()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		auto gzHull = hullGZ();

		auto gzTanks = tanksGZ();

		auto alg = std::make_shared<HydStatic_GzEff>(gzHull);
		alg->LoadTanksGz(gzTanks);

		alg->Perform();

		mySolutionData->SetGzEff(alg->GzEff());
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;


	std::string getstring(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getstring(argv);
		return argument IS_EQUAL command;
	}
}