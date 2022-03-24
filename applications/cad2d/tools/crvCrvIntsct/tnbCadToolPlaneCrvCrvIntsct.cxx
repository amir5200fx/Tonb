#include <Cad2d_CrvsIntsct.hxx>
#include <Cad2d_BruteForceSearchCrv.hxx>
#include <Cad2d_EntityEntityIntersection.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::string loadExt = Pln_Edge::extension + "list";
	static std::string saveExt = Cad2d_EntityEntityIntersection::extension + "list";

	static std::vector<std::shared_ptr<Pln_Edge>> myCurves;
	static std::vector<std::shared_ptr<Cad2d_EntityEntityIntersection>> myEntities;

	static bool loadTag = false;
	static bool exeTag = false;

	static double myTol = 1.0E-6;

	static std::string myFileName;

	static unsigned short verbose = 0;

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

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myCurves = file::LoadFile<std::vector<std::shared_ptr<Pln_Edge>>>(name + loadExt, verbose);

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
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}

		file::SaveTo(myEntities, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}
}