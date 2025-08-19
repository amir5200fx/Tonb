#include <HydStatic_SolutionData_HydCurves.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fstream>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_HydCurves> soluData_t;

	static soluData_t mySolutionData;

	static bool loadTag = false;
	static unsigned short verbose(0);

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

		loadTag = true;

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{

	}
}