#include <Aft2d_SolutionData.hxx>
#include <Aft2d_SolutionDataAnIso.hxx>
#include <Aft2d_MetricPrcsr.hxx>
#include <Aft2d_Element.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Aft2d_PlnWire.hxx>
#include <MeshBLayer2d_Offset.hxx>
#include <Mesh_BndLayer_Info.hxx>
#include <Merge2d_QuadMesh.hxx>
#include <Entity2d_QuadMesh.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include "tools.hxx"

namespace tnbLib
{
	static const std::string extension = Aft2d_SolutionData::extension;
	static std::shared_ptr<Aft2d_SolutionDataBase> mySoluData;
	static std::string myFileName;

	static std::shared_ptr<Entity2d_Polygon> myWall;
	static std::shared_ptr<Entity2d_Polygon> myOuterLayer;

	static std::shared_ptr<Entity2d_QuadMesh> myMesh;

	static std::set<int> myBndList;

	static double myRate = 1.003;
	static double myThick = 0.05;
	static int myClusterSize = 5;

	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_GLOBAL_PATH;
	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;

	TNB_SET_VERBOSE_FUN;

	//static const std::string wall_directory = "wall";
	//static const std::string outer_directory = "outer";

	//void loadFiles()
	//{
	//	{// load the wall file
	//		myWall =
	//			file::LoadSingleFile<std::shared_ptr<Entity2d_Polygon>>
	//			(wall_directory, Entity2d_Polygon::extension, verbose);
	//		TNB_CHECK_LOADED_FILE(myWall);
	//	}
	//	{// load the outer layer
	//		myOuterLayer =
	//			file::LoadSingleFile<std::shared_ptr<Entity2d_Polygon>>
	//			(outer_directory, Entity2d_Polygon::extension, verbose);
	//	}
	//	loadTag = true;
	//}

	void setClusterSize(int n)
	{
		myClusterSize = n;
		if (verbose)
		{
			Info << endl
				<< " - the cluster size is set to: " << myClusterSize << endl;
		}
	}

	void setRate(double x)
	{
		myRate = x;
		if (verbose)
		{
			Info << endl
				<< " - the rate is set to: " << myRate << endl;
		}
	}

	void setCurve(int i)
	{
		myBndList.insert(i);
		if (verbose)
		{
			Info << endl
				<< " - the curve is add to the list: " << i << endl;
		}
	}

	void setThick(double x)
	{
		myThick = x;
		if (verbose)
		{
			Info << endl
				<< " - the Thick. is set to: " << myThick << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_SolutionDataBase>>(name + extension, verbose);
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
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);
		file::SaveTo(mySoluData, name + extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	void execute()
	{
		TNB_CHECK_LOADED;

		if (mySoluData->IsIso())
		{
			const auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionData>(mySoluData);
			Debug_Null_Pointer(soluData);
			auto boundaries = soluData->BoundaryEdges();
			const auto& metrics = soluData->Metric();
			if (NOT metrics)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "No metric processor has been found." << endl
					<< abort(FatalError);
			}
			const auto& bnd_info = soluData->GlobalBndLayerInfo();
			const auto myInfo = std::make_shared<Mesh_BndLayer_Info>();
			//myInfo->SetFirstLayerThick(myThick);
			myInfo->SetGrowthRate(myRate);
			myInfo->SetNbLayers(myClusterSize);
			myInfo->SetOuterLayerThick(myThick);
			if (boundaries.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "no boundary edge has been detected!" << endl
					<< abort(FatalError);
			}
			//const auto& bnd_layer_list = soluData->BndLayerList();
			if (!myBndList.empty())
			{
				std::vector<std::shared_ptr<Entity2d_QuadMesh>> meshes;
				/*
				 * Retrieving the boundary map
				 */
				const auto bnd_sets = tools::RetrieveBoundaries(boundaries);
				/*
				 * Getting the inner wires
				 */
				const auto wires = tools::RetrieveWires(bnd_sets, myBndList);
				for (const auto& x:wires)
				{// for every wire on the list we need to create a bounady layer mesh.
					/*
					 * Check the wire if it's closed
					 * The new offset edges will be saved on the super edges.
					 */
					tools::CheckWire(x->edges);
					auto [outer_layer, mesh] = 
						bndLayer::CalcBndLayer(x->edges, *myInfo);
					const auto merge_alg = std::make_shared<Merge2d_QuadMesh>();
					merge_alg->Import(*mesh);
					merge_alg->Perform();
					mesh = merge_alg->Merged();
					meshes.emplace_back(std::move(mesh));
					/*
					 * The new offset edges has been saved on the super edges.
					 * We just need to replace the boundary layer edges with the offset ones.
					 * Both of them have been saved on the super edge.
					 */
					{// replacing the boundary layer edges
						std::map<int, std::shared_ptr<SupEdge>> sup_map;
						for (const auto& e:x->edges)
						{
							Global_Tools::InsertIgnoreDup(e->Index(), e, sup_map);
						}
						for (auto& bnd:boundaries)
						{
							if (auto iter=sup_map.find(bnd->Index()); iter NOT_EQUAL sup_map.end())
							{
								//bnd = iter->second->Edge();
								const auto& n0 = bnd->Node0();
								const auto& n1 = bnd->Node1();
								bnd->SetCharLength(metrics->CalcDistance(n0->Coord(), n1->Coord()));
								bnd->SetCentre(MEAN(n0->Coord(), n1->Coord()));
							}
						}
					}
				}
				soluData->SetBndlayerMeshes(meshes);
				soluData->SetBoundaryEdges(std::move(boundaries));
			}
		}
		else
		{
			NotImplemented;
		}

		/*auto alg = std::make_shared<MeshBLayer2d_Offset>();
		alg->SetClusterSize(myClusterSize);
		alg->SetRate(myRate);
		alg->SetPolygon(myWall);
		alg->SetOffset(myOuterLayer);
		alg->Perform();
		myMesh = alg->Mesh();*/
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/9/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		mod->add(chaiscript::fun([](int n)-> void {setClusterSize(n); }), "setClusterSize");
		mod->add(chaiscript::fun([](double x)-> void {setRate(x); }), "setRate");
		mod->add(chaiscript::fun([](double x)-> void {setThick(x); }), "setThick");
		mod->add(chaiscript::fun([](int i)-> void {setCurve(i); }), "addCurve");

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
				<< " - setRate(x)" << endl
				<< " - setThick(x)" << endl
				<< " - addCurve(i)" << endl << endl

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