#include <Marine_DisctSectionsIO.hxx>
#include <Marine_SectionsIO.hxx>
#include <Pln_Edge.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity3d_Chain.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fstream>

namespace tnbLib
{

	static bool loadTag = false;
	static bool exeTag = false;

	static bool unionMesh = true;

	static unsigned short verbose(0);

	static std::shared_ptr<marineLib::io::DisctSections> mySections;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> mySections;
		}

		if (NOT mySections)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& sections = mySections->GetSections();
		if (NOT sections)
		{
			FatalErrorIn(FunctionSIG)
				<< "no sections object is provided!" << endl
				<< abort(FatalError);
		}

		for (const auto& x : sections->GetSections())
		{
			const auto& edges = x->Edges();

			for (const auto& ed : edges)
			{
				Debug_Null_Pointer(ed);

				const auto& ply2d = ed->Mesh();
				if (NOT ply2d)
				{
					FatalErrorIn(FunctionSIG)
						<< "the edge has no mesh" << endl
						<< abort(FatalError);
				}
			}
		}
	}
}