#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::string loadExt = Pln_Edge::extension + "list";
	static std::string saveExt = Entity2d_Triangulation::extension + "list";

	static std::vector<std::shared_ptr<Pln_Edge>> myCurves;
	static std::vector<std::shared_ptr<Entity2d_Triangulation>> myTris;

	static bool verbose = false;
	static bool loadTag = false;

	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myFileName = name;
		myCurves = file::LoadFile<std::vector<std::shared_ptr<Pln_Edge>>>(name + loadExt, verbose);
		loadTag = true;
	}

	void loadFile()
	{
		myFileName = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
		loadFile(myFileName);
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		file::SaveTo()
	}
}