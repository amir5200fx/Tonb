#include <Aft_Tools.hxx>
#include <Aft2d_gSolutionDataSurface.hxx>
#include <Aft2d_gSegmentEdge.hxx>
#include <Entity3d_TriVolume.hxx>
#include <Entity3d_TriShell.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static const std::string loadExt = Aft2d_gSolutionDataSurface::extension;

	static std::shared_ptr<Aft2d_gSolutionDataSurface> mySoluData;
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

		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_gSolutionDataSurface>>(name + loadExt, verbose);
		myFileName = name;
		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "the data solution file is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
		loadFile(name);
	}

	void execute()
	{
		
	}

}