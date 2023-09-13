#include <Aft2d_SolutionData.hxx>
#include <Aft2d_SolutionDataAnIso.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <MeshBLayer2d_Offset.hxx>
#include <Entity2d_QuadMesh.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Aft2d_SolutionDataBase> mySoluData;

	static std::shared_ptr<Entity2d_Polygon> myWall;
	static std::shared_ptr<Entity2d_Polygon> myOuterLayer;

	static std::shared_ptr<Entity2d_QuadMesh> myMesh;

	static double myRate = 1.003;
	static int myClusterSize = 5;

	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_GLOBAL_PATH;
	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;

	TNB_SET_VERBOSE_FUN;

	static const std::string wall_directory = "wall";
	static const std::string outer_directory = "outer";

	void setClusterSize(int n)
	{
		myClusterSize = n;
		if(verbose)
		{
			Info << endl
				<< " - the cluster size is set to: " << myClusterSize << endl;
		}
	}

	void setRate(double x)
	{
		myRate = x;
		if(verbose)
		{
			Info << endl
				<< " - the rate is set to: " << myRate << endl;
		}
	}

	void loadFiles()
	{
		{// load the wall file
			myWall = 
				file::LoadSingleFile<std::shared_ptr<Entity2d_Polygon>>
			(wall_directory, Entity2d_Polygon::extension, verbose);
			TNB_CHECK_LOADED_FILE(myWall);
		}
		{// load the outer layer
			myOuterLayer = 
				file::LoadSingleFile<std::shared_ptr<Entity2d_Polygon>>
			(outer_directory, Entity2d_Polygon::extension, verbose);
		}
		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		TNB_CHECK_EXE_TAG;
		file::SaveTo(myMesh, name + Entity2d_QuadMesh::extension, verbose);
	}

	template<class EdgeType>
	struct EdgeSet
	{
		std::vector<std::shared_ptr<EdgeType>> edges;
	};

	
	
	std::vector<std::shared_ptr<EdgeSet<Aft2d_Edge>>> retrieveBndLayarEdges(const Aft2d_SolutionData& theSolu)
	{
		std::map<int, std::shared_ptr<EdgeSet<Aft2d_Edge>>> all_edge_sets;
		for (const auto& x : theSolu.BoundaryEdges())
		{
			const auto curve = x->Curve().lock();
			if (!curve)
			{
				FatalErrorIn(FunctionSIG)
					<< "No curve has been assigned to the edge." << endl
					<< abort(FatalError);
			}
			const auto curve_id = curve->Index();
			auto iter = all_edge_sets.find(curve_id);
			if (iter IS_EQUAL all_edge_sets.end())
			{
				auto new_set = std::make_shared<EdgeSet<Aft2d_Edge>>();
				all_edge_sets.insert({ curve_id,std::move(new_set) });
			}
			all_edge_sets.at(curve_id)->edges.emplace_back(x);
		}
		const auto& bnd_list = theSolu.BndLayerList();

	}

	void execute()
	{
		TNB_CHECK_LOADED;

		if (mySoluData->IsIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionData>(mySoluData);
			Debug_Null_Pointer(soluData);

			const auto& boundaries = soluData->BoundaryEdges();
			if (boundaries.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "no boundary edge has been detected!" << endl
					<< abort(FatalError);
			}

		}
		else
		{
			NotImplemented;
		}

		auto alg = std::make_shared<MeshBLayer2d_Offset>();
		alg->SetClusterSize(myClusterSize);
		alg->SetRate(myRate);
		alg->SetPolygon(myWall);
		alg->SetOffset(myOuterLayer);
		alg->Perform();
		myMesh = alg->Mesh();
		TNB_EXECUTE_TAG;
	}
	
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFuns(const module_t& mod)
	{
		// io functions [12/9/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [12/9/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		mod->add(chaiscript::fun([](int n)-> void {setClusterSize(n); }), "setClusterSize");
		mod->add(chaiscript::fun([](double x)-> void {setRate(x); }), "setRate");

		// operators [12/9/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
	}

	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument IS_EQUAL command;
	}
}

using namespace tnbLib;

int main(int argc, char* argv[])
{
	//FatalError.throwExceptions();

	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << " This application is aimed to create a boundary layer mesh." << endl << endl;
			Info << " - subdirectories: {wall}, {outer}" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl
				<< " - setClusterSize(n)" << endl
				<< " - setRate(x)" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshBndLayer2d"));

				chai.eval_file(myFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				Info << x.what() << endl;
			}
		}
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}