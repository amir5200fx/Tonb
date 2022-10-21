#include <Mesh3d_ReferenceValues.hxx>
#include <Mesh_Values.hxx>
#include <Mesh_Conditions.hxx>
#include <Mesh3d_UniformBoundarySizeMapControl.hxx>
#include <Mesh3d_UniformFeatureSizeMapControl.hxx>
#include <Mesh3d_UnionSizeMap.hxx>
#include <MeshBase_Tools.hxx>
#include <GeoMesh_Background_Info.hxx>
#include <BoundarySizeMap3d_UniformFaceTool.hxx>
#include <BoundarySizeMap3d_UniformSegmentTool.hxx>
#include <BoundarySizeMap3d_UniformFaceTool_Info.hxx>
#include <GeoSizeFun3d_Background.hxx>
#include <Geo3d_ApprxSurfPatch_Info.hxx>
#include <Geo3d_PatchCloud_EdgeSamplesLev1.hxx>
#include <Geo3d_PatchCloud_TriSamplesLev1.hxx>
#include <Geo3d_PatchCloud_InternalSamples.hxx>
#include <Geo3d_SegmentCloud_InternalSamples.hxx>
#include <Geo3d_SegmentCloud_SamplesLev1.hxx>
#include <Cad_TModel.hxx>
#include <Cad_Tools.hxx>
#include <TModel_CornerManager.hxx>
#include <TModel_SegmentManager.hxx>
#include <TModel_FaceManager.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool exeTag = false;
	static bool loadTag = false;

	static std::vector<std::shared_ptr<Cad_TModel>> myModels;

	static std::shared_ptr<Mesh3d_UniformBoundarySizeMapControl> myBoundarySizeMaps;
	static std::shared_ptr<Mesh3d_UniformFeatureSizeMapControl> myFeatureSizeMaps;

	static std::shared_ptr<Mesh3d_ReferenceValues> myRef;
	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;

	static std::shared_ptr<Geo3d_PatchCloud_EdgeSamples> myEdgeSamples;
	static std::shared_ptr<Geo3d_PatchCloud_TriSamples> myTrisSamples;
	static std::shared_ptr<Geo3d_PatchCloud> myCloud;

	static std::shared_ptr<Geo3d_SegmentCloud> mySegmentCloud;
	static std::shared_ptr<Geo3d_SegmentCloud_SamplesLev1> mySegmentSamples;

	static double myTol = 1.0E-6;
	static unsigned int myMaxUnbalancing = 2;

	//static std::string currentPath;

	static auto myCorrInfo =
		std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
	static auto myFaceSizeMapInfo =
		std::make_shared<BoundarySizeMap3d_UniformFaceTool_Info>();

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void checkLoad()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been load." << endl
				<< abort(FatalError);
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;

		Mesh3d_UniformBoundarySizeMapControl::verbose = i;
		Mesh3d_UniformFeatureSizeMapControl::verbose = i;
	}

	void setMaxUnbalancing(unsigned int n)
	{
		myMaxUnbalancing = n;
		if (verbose)
		{
			Info << endl
				<< " - Max. Unbalancing is set to: " << myMaxUnbalancing << endl;
		}
	}

	auto retrieveBoundingBox()
	{
		auto reg = std::make_shared<Entity3d_Box>(myRef->Region()->Expanded(myRef->Region()->Diameter()*1.0E-5));
		return std::move(reg);
		//return myRef->Region();
	}

	void loadRefFile()
	{
		checkFolder("reference");

		const auto currentPath = boost::filesystem::current_path();

		boost::filesystem::current_path(currentPath.string() + R"(\reference)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Mesh3d_ReferenceValues::extension).string();

		file::CheckExtension(name);
		myRef = file::LoadFile<std::shared_ptr<Mesh3d_ReferenceValues>>(name + Mesh3d_ReferenceValues::extension, verbose);
		if (NOT myRef)
		{
			FatalErrorIn(FunctionSIG)
				<< "the loaded file is null!" << endl
				<< abort(FatalError);
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadModels()
	{
		checkFolder("models");

		const auto currentPath = boost::filesystem::current_path();

		boost::filesystem::current_path(currentPath.string() + R"(\models)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_TModel::extension + "list").string();

		file::CheckExtension(name);
		myModels = file::LoadFile<std::vector<std::shared_ptr<Cad_TModel>>>(name + Cad_TModel::extension + "list", verbose);
		if (myModels.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the model list is empty." << endl
				<< abort(FatalError);
		}

		for (const auto& x : myModels)
		{
			Cad_Tools::Connect(x);
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);		
	}

	void loadFiles()
	{
		if (verbose)
		{
			Info << " loading the files..." << endl
				<< endl;
		}

		{
			Global_Timer myTimer;
			myTimer.SetInfo(Global_TimerInfo_ms);

			loadRefFile();
			loadModels();
		}

		if (verbose)
		{
			Info << endl
				<< " - All models are loaded, in: " << global_time_duration << " ms." << endl;
		}

		auto domain = retrieveBoundingBox();

		if (NOT myCloud)
		{
			myEdgeSamples = std::make_shared<Geo3d_PatchCloud_EdgeSamplesLev1>();
			myTrisSamples = std::make_shared<Geo3d_PatchCloud_TriSamplesLev1>();

			myCloud = std::make_shared<Geo3d_PatchCloud_InternalSamples>(myEdgeSamples, myTrisSamples);
		}

		myBoundarySizeMaps = std::make_shared<Mesh3d_UniformBoundarySizeMapControl>(myRef, domain, myCloud);
		myFeatureSizeMaps = std::make_shared<Mesh3d_UniformFeatureSizeMapControl>(myRef, domain, myCloud);

		loadTag = true;

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

		file::SaveTo(mySizeFun, name + Geo3d_SizeFunction::extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(mySizeFun->Name());
	}

	void printNbCorners(const std::shared_ptr<Cad_TModel>& m)
	{
		Info << endl
			<< " - nb. of corners: " << m->NbCorners() << endl;
	}

	void printNbSegments(const std::shared_ptr<Cad_TModel>& m)
	{
		Info << endl
			<< " - nb. of corners: " << m->NbSegments() << endl;
	}

	void printNbFaces(const std::shared_ptr<Cad_TModel>& m)
	{
		Info << endl
			<< " - nb. of corners: " << m->NbFaces() << endl;
	}

	auto getCorners(const std::shared_ptr<Cad_TModel>& m)
	{
		return m->Corners();
	}

	auto getSegments(const std::shared_ptr<Cad_TModel>& m)
	{
		return m->Segments();
	}

	auto getFaces(const std::shared_ptr<Cad_TModel>& m)
	{
		return m->Faces();
	}

	void printBlocks(const std::shared_ptr<TModel_CornerManager>& manager)
	{
		Info << endl
			<< " - list of the corners:" << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	void printBlocks(const std::shared_ptr<TModel_SegmentManager>& manager)
	{
		Info << endl
			<< " - list of the segments:" << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	void printBlocks(const std::shared_ptr<TModel_FaceManager>& manager)
	{
		Info << endl
			<< " - list of the faces:" << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	std::shared_ptr<Mesh3d_BoundarySizeMapTool> createBoundarySizeMap(const std::string& name, const std::shared_ptr<Cad_TModel>& model)
	{
		checkLoad();
		if (NOT myCloud)
		{
			myEdgeSamples = std::make_shared<Geo3d_PatchCloud_EdgeSamplesLev1>();
			myTrisSamples = std::make_shared<Geo3d_PatchCloud_TriSamplesLev1>();

			myCloud = std::make_shared<Geo3d_PatchCloud_InternalSamples>(myEdgeSamples, myTrisSamples);
		}
		myBoundarySizeMaps->CreateSizeMap(name, model, myCloud, myFaceSizeMapInfo);
		return myBoundarySizeMaps->SelectMap(name);
	}

	std::shared_ptr<Mesh3d_BoundarySizeMapTool> createFeatureSizeMap(const std::string& name, const std::shared_ptr<Cad_TModel>& model)
	{
		checkLoad();
		if (NOT mySegmentCloud)
		{
			mySegmentSamples = std::make_shared<Geo3d_SegmentCloud_SamplesLev1>();

			mySegmentCloud = std::make_shared<Geo3d_SegmentCloud_InternalSamples>(mySegmentSamples);
		}
		myFeatureSizeMaps->CreateSizeMap(name, model, mySegmentCloud);
		return myFeatureSizeMaps->SelectMap(name);
	}

	void importEntityPatch(const std::shared_ptr<Mesh3d_BoundarySizeMapTool>& theSizeMap, const std::string& name)
	{
		theSizeMap->ImportPatch(name);
	}

	const auto& meshConditions(const std::shared_ptr<Mesh3d_BoundarySizeMapTool>& theSizeMap)
	{
		return theSizeMap->MeshConditions();
	}

	const auto& meshValues(const std::shared_ptr<Mesh3d_BoundarySizeMapTool>& theSizeMap)
	{
		return theSizeMap->MeshValues();
	}

	const auto& surfaceSize(const std::shared_ptr<Mesh_Values>& v)
	{
		return v->SurfaceSize();
	}

	void setCustomSurfaceSize(const std::shared_ptr<Mesh_Conditions>& cond, bool d)
	{
		cond->SetCustomSurfaceSize(d);
	}

	void setCustomBoundaryGrowthRate(const std::shared_ptr<Mesh_Conditions>& cond, bool d)
	{
		cond->SetCustomBoundaryGrowthRate(d);
	}

	auto switchToCurvatureInfo(const std::string& name)
	{
		if (name == "continuum")
		{
			return Mesh_SurfaceCurvatureInfo::continum;
		}
		else if (name == "custom")
		{
			return Mesh_SurfaceCurvatureInfo::custom;
		}
		else if (name == "disable")
		{
			return Mesh_SurfaceCurvatureInfo::disable;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of surface curvature has been detected." << endl
				<< " - valid types: 'continuum', 'custom', and 'disable'" << endl
				<< " - selected type: " << name << endl
				<< abort(FatalError);
			return Mesh_SurfaceCurvatureInfo::disable;
		}
	}

	void setCustomSurfaceCurvature(const std::shared_ptr<Mesh_Conditions>& cond, const std::string& d)
	{
		cond->SetCustomSurfaceCurvature(switchToCurvatureInfo(d));
	}

	auto switchToValueType(const std::string& name)
	{
		if (name == "relative")
		{
			return Mesh_RelativeAbsoluteInfo::relativeToBase;
		}
		else if (name == "absolute")
		{
			return Mesh_RelativeAbsoluteInfo::absolute;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of value has been detected." << endl
				<< " - valid types: 'relative', and 'absolute'" << endl
				<< " - selected type: " << name << endl
				<< abort(FatalError);
			return Mesh_RelativeAbsoluteInfo::relativeToBase;
		}
	}

	void setMeshValuesType(const std::shared_ptr<Mesh_SurfaceSizeValues>& v, const std::string& t)
	{
		v->SetRelativeAbsolute(switchToValueType(t));
	}

	void setTargetSize(const std::shared_ptr<Mesh_SurfaceSizeValues>& v, double x)
	{
		v->SetTargetSize(x);
	}

	auto switchToVariationRateType(const std::string& name)
	{
		if (name == "custom")
		{
			return Mesh_VariationRateInfo::custom;
		}
		else if (name == "verySlow")
		{
			return Mesh_VariationRateInfo::verySlow;
		}
		else if (name == "slow")
		{
			return Mesh_VariationRateInfo::slow;
		}
		else if (name == "moderate")
		{
			return Mesh_VariationRateInfo::moderate;
		}
		else if (name == "fast")
		{
			return Mesh_VariationRateInfo::fast;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of growth rate has been detected." << endl
				<< " - valid types: 'custom', 'verySlow', 'slow', 'moderate', and 'fast'" << endl
				<< " - selected type: " << name << endl
				<< abort(FatalError);
			return Mesh_VariationRateInfo::custom;
		}
	}

	void setBoundaryVariationRate(const std::shared_ptr<Mesh_Values>& v, const std::string& name)
	{
		v->SetBoundaryGrowthRate(switchToVariationRateType(name));
	}

	auto retrieveBackgrounds()
	{
		std::vector<std::shared_ptr<GeoMesh3d_Background>> backs;
		if (myBoundarySizeMaps->NbMaps())
		{
			backs.push_back(myBoundarySizeMaps->BackgroundMesh());
		}
		if (myFeatureSizeMaps->NbMaps())
		{
			backs.push_back(myFeatureSizeMaps->BackgroundMesh());
		}
		return std::move(backs);
	}


	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		const auto& approxInfo = myFaceSizeMapInfo->ApprxSurfInfo();
		approxInfo->SetMinSubdivide(2);
		approxInfo->SetMaxSubdivide(4);

		{
			// main scope [7/20/2022 Amir]
			Global_Timer myTimer;
			myTimer.SetInfo(Global_TimerInfo_ms);

			if (verbose > 1)
			{
				Mesh_SizeMapToolBaseNonTemplate::verbose = verbose;
				BoundarySizeMap3d_UniformSegmentTool::verbose = verbose;
				Mesh3d_UnionSizeMap::verbose = verbose;
			}

			auto domain = retrieveBoundingBox();

			if (myBoundarySizeMaps->NbMaps())
			{
				myBoundarySizeMaps->Perform();
			}
			//std::exit(1);
			//auto ss = myFeatureSizeMaps->SelectMap("edges");
			//std::cout << ss->MeshConditions()->CustomBoundaryGrowthRate() << std::endl;
			//ss->MeshConditions()->SetCustomBoundaryGrowthRate(Standard_True);
			//ss->MeshValues()->SetBoundaryGrowthRate(Mesh_VariationRateInfo::verySlow);

			if (myFeatureSizeMaps->NbMaps())
			{
				myFeatureSizeMaps->Perform();
			}
			//std::exit(1);
			auto models = myModels;
			auto backs = retrieveBackgrounds();			

			std::shared_ptr<GeoMesh3d_Background> myBackgound;
			if (backs.size())
			{
				Global_Timer unifyTimer;
				unifyTimer.SetInfo(Global_TimerInfo_ms);

				if (NOT myCloud)
				{
					myEdgeSamples = std::make_shared<Geo3d_PatchCloud_EdgeSamplesLev1>();
					myTrisSamples = std::make_shared<Geo3d_PatchCloud_TriSamplesLev1>();

					myCloud = std::make_shared<Geo3d_PatchCloud_InternalSamples>(myEdgeSamples, myTrisSamples);
				}

				auto alg = std::make_shared<Mesh3d_UnionSizeMap>();
				alg->SetTolerance(myTol);
				alg->SetMaxUnbalancing(myMaxUnbalancing);
				alg->SetDomain(domain);
				alg->SetSmoothingInfo(myCorrInfo);

				alg->SetModels(std::move(models));
				alg->SetBackgrounds(std::move(backs));

				alg->SetCloud(myCloud);

				alg->Perform();

				myBackgound = alg->UnifiedMap();
			}
			/*else if (backs.size() == 1)
			{
				myBackgound = backs.at(0);
			}*/
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "no size map has been created." << endl
					<< abort(FatalError);
			}

			if (verbose)
			{
				Info << endl
					<< " - All the maps are unified in, " << global_time_duration << " ms." << endl;
			}
			OFstream myFile("background.plt");
			myBackgound->ExportToPlt(myFile);

			/*auto facets = MeshBase_Tools::RetrieveFacets(myBackgound->Mesh()->Elements());
			for (const auto& x : facets)
			{
				std::cout << "- face: " << x->Index() << ",  ";
				if (auto e = x->LeftElement().lock())
				{
					std::cout << "left: " << e->Index() << ",  ";
				}
				else
				{
					std::cout << "left: " << 0 << ",  ";
				}

				if (auto e = x->RightElement().lock())
				{
					std::cout << "right: " << e->Index() << std::endl;
				}
				else
				{
					std::cout << "right: " << 0 << std::endl;
				}
			}*/

			auto d = *domain;
			mySizeFun =
				std::make_shared<GeoSizeFun3d_Background>
				(0, name, std::move(d), std::move(myBackgound));
		}

		

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, in " << global_time_duration << " ms." << endl;
		}

		exeTag = true;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void addUserTypes(const module_t& mod)
	{
		mod->add(chaiscript::user_type<Mesh_Conditions>(), "MeshConditions");
		mod->add(chaiscript::constructor<Mesh_Conditions()>(), "MeshConditions");

		mod->add(chaiscript::user_type<Mesh_SurfaceSizeValues>(), "SurfaceSizeValues");
		mod->add(chaiscript::constructor<Mesh_SurfaceSizeValues()>(), "SurfaceSizeValues");

		mod->add(chaiscript::user_type<Mesh_Values>(), "MeshValues");
		mod->add(chaiscript::constructor<Mesh_Values()>(), "MeshValues");
	}

	void setFunctions(const module_t& mod)
	{
		// io functions [7/31/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		// operators [7/31/2022 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name, const std::shared_ptr<Cad_TModel>& model)-> auto {return createBoundarySizeMap(name, model); }), "createBoundarySizeMap");
		mod->add(chaiscript::fun([](const std::string& name, const std::shared_ptr<Cad_TModel>& model)-> auto {return createFeatureSizeMap(name, model); }), "createFeatureSizeMap");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh3d_BoundarySizeMapTool>& sm, const std::string& name)-> void {importEntityPatch(sm, name); }), "importPatch");

		mod->add(chaiscript::fun([](int i)-> auto{return myModels.at(i); }), "getModel");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_TModel>& m)-> void {printNbCorners(m); }), "printNbCorners");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_TModel>& m)-> void {printNbSegments(m); }), "printNbSegments");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_TModel>& m)-> void {printNbFaces(m); }), "printNbFaces");

		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_CornerManager>& m)-> void {printBlocks(m); }), "printBlocks");
		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_SegmentManager>& m)-> void {printBlocks(m); }), "printBlocks");
		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_FaceManager>& m)-> void {printBlocks(m); }), "printBlocks");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_TModel>& m)-> auto{return getCorners(m); }), "getCorners");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_TModel>& m)-> auto{return getSegments(m); }), "getSegments");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_TModel>& m)-> auto{return getFaces(m); }), "getFaces");
		
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh3d_BoundarySizeMapTool>& sm)-> auto {return meshConditions(sm); }), "getMeshConditions");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh3d_BoundarySizeMapTool>& sm)-> auto {return meshValues(sm); }), "getMeshValues");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Values>& v)-> auto {return v->SurfaceSize(); }), "getSurfaceSize");

		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Conditions>& cond, bool d)-> void {setCustomSurfaceSize(cond, d); }), "setCustomSurfaceSize");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Conditions>& cond, bool d)-> void {setCustomBoundaryGrowthRate(cond, d); }), "setCustomBoundaryGrowthRate");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Conditions>& cond, const std::string& name)-> void {setCustomSurfaceCurvature(cond, name); }), "setCustomSurfaceCurvature");

		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_SurfaceSizeValues>& v, const std::string& name)-> void {setMeshValuesType(v, name); }), "setType");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_SurfaceSizeValues>& v, double x)-> void {setTargetSize(v, x); }), "setTargetSize");
		
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Values>& v, const std::string& name)-> void {setBoundaryVariationRate(v, name); }), "setVariationRate");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_Values>& v)-> auto& {return surfaceSize(v); }), "getSurfaceSize");

		// settings [7/31/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		
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

int main(int argc, char *argv[])
{
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
			Info << " This application is aimed to create an adaptive size function." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - printNbCorners(model)" << endl
				<< " - printNbSegments(model)" << endl
				<< " - printNbFaces(model)" << endl << endl

				<< " - printBlocks(manager)" << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl

				<< " # Operators:" << endl << endl

				<< " - [manager] getCorners(model);                     - it gives the corner manager." << endl
				<< " - [manager] getSegments(model);                    - it gives the segment manager." << endl
				<< " - [manager] getFaces(model);                       - it gives the face manager." << endl << endl

				<< " - [model] getModel(int);" << endl
				<< " - [sizeMap] createBoundarySizeMap(name, model);" << endl
				<< " - [sizeMap] createFeatureSizeMap(name, model);" << endl << endl

				<< " - importPatch(sizeMap, name);" << endl << endl

				<< " - [meshConds] (sizeMap).getMeshConditions();" << endl
				<< " - [meshValues] (sizeMap).getMeshValues();" << endl << endl

				<< " - [surfaceSize] (meshValues).getSurfaceSize();" << endl << endl

				<< " - (meshConds).setCustomBoundaryGrowthRate(bool);   - default value: false" << endl
				<< " - (meshConds).setCustomSurfaceSize(bool);          - default value: false" << endl
				<< " - (meshConds).setCustomSurfaceCurvature(bool);     - default value: false" << endl << endl

				<< " - (meshValues).setVariationRate(rate);             - rate: verySlow, slow, moderate, fast." << endl << endl
				
				<< " - (surfaceSize).setType(type);                     - type: ralative, absolute." << endl
				<< " - (surfaceSize).setTargetSize(size)" << endl << endl

				<< " - execute(name)" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			addUserTypes(mod);
			setFunctions(mod);

			chai.add(mod);

			try
			{
				auto address = file::GetSystemFile("tnbMeshSizeMap3dAdaptive");
				fileName myFileName(address);

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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}