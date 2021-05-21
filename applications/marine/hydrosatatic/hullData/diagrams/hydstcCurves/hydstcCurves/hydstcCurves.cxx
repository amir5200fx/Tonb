#include <HydStatic_SolutionData_HydCurves.hxx>
#include <HydStatic_HydCurves.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	typedef std::shared_ptr<hydStcLib::SolutionData_HydCurves> soluData_t;

	static soluData_t mySolutionData;

	static unsigned short verbose(0);
	static auto hydCurves = std::make_shared<HydStatic_HydCurves>();

	void loadSolutionData(const std::string& name)
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
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
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

	void setRhoSW(double x)
	{
		hydCurves->SetRhoSW(x);
	}

	void setRhoFW(double x)
	{
		hydCurves->SetRhoFW(x);
	}

	void setRudder(double x)
	{
		hydCurves->SetRudderLocation(x);
	}

	void setDisplFactor(double x)
	{
		hydCurves->SetDisplFactor(x);
	}


}