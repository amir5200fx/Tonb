#include <Mesh2d_UniformBoundarySizeMapControl.hxx>
#include <Mesh2d_BoundarySizeMapTool.hxx>
#include <Mesh2d_ReferenceValues.hxx>
#include <Geo2d_SegmentCloud.hxx>
#include <Geo2d_SegmentCloud_Samples.hxx>
#include <Geo2d_SegmentCloud_SamplesLev2.hxx>
#include <Geo2d_SegmentCloud_SamplesLev1.hxx>
#include <Geo2d_SegmentCloud_SamplesLev0.hxx>
#include <GeoSizeFun2d_Background.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad_EntityManager.hxx>
#include <Pln_Tools.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_GLOBAL_PATH;

	TNB_SET_VERBOSE_FUN;

	static double myTol = 1.0E-6;

	static std::vector<std::shared_ptr<Cad2d_Plane>> myModels;

	static std::shared_ptr<Mesh2d_UniformBoundarySizeMapControl> myBoundarySizeMaps;

	static std::shared_ptr<Mesh2d_ReferenceValues> myRef;
	static std::shared_ptr<Geo2d_SizeFunction> mySizeFun;


	static std::shared_ptr<Geo2d_SegmentCloud> myEdgeSamples;

	void loadRefFile()
	{
		static const auto current_directory = "reference";
		file::CheckDirectory(current_directory);

		file::SetCurrentPath(global_path.string() + current_directory);
		myRef = file::LoadSingleFile<std::shared_ptr<Mesh2d_ReferenceValues>>(current_directory, verbose);
		TNB_CHECK_LOADED_FILE(myRef);
		file::SetCurrentPath(global_path.string());
	}

	void loadModels()
	{
		static const auto current_directory = "models";
		file::CheckDirectory(current_directory);

		file::SetCurrentPath(global_path.string() + current_directory);
		myModels = file::LoadSingleFile<std::vector<std::shared_ptr<Cad2d_Plane>>>(current_directory, verbose);
		for (const auto& x : myModels)
		{
			TNB_CHECK_LOADED(x);
			Pln_Tools::Connect(x);
		}
		file::SetCurrentPath(global_path.string());
	}

	auto calcBoundingBox()
	{
		const auto& b = myRef->Region();
		auto reg = std::make_shared<Entity2d_Box>(b->Expanded(b->Diameter() * 0.25));
		return std::move(reg);
	}

	void loadFiles()
	{
		loadRefFile();
		loadModels();

		if (verbose)
		{
			Info << endl
				<< " - All files has been successfully loaded." << endl;
		}
		auto domain = calcBoundingBox();
		if (NOT myEdgeSamples)
		{
			//myEdgeSamples = std::make_shared<Geo2d_SegmentCloud_SamplesLev0>();
		}
		myBoundarySizeMaps = 
			std::make_shared<Mesh2d_UniformBoundarySizeMapControl>
			(myRef, domain, myEdgeSamples);
		loadTag = true;
	}

	TNB_SAVE_FILE(mySizeFun);

	void saveTo()
	{
		TNB_CHECK_EXE_TAG;
		saveTo(mySizeFun->Name());
	}

	void printNbCorners(const std::shared_ptr<Cad2d_Plane>& m)
	{
		Info << endl
			<< " - no. of corners: " << m->NbCorners() << endl;
	}

	void printNbSegments(const std::shared_ptr<Cad2d_Plane>& m)
	{
		Info << endl
			<< " - no. of segments: " << m->NbSegments() << endl;
	}

	auto getCorners(const std::shared_ptr<Cad2d_Plane>& m)
	{
		return m->Corners();
	}

	auto getSegments(const std::shared_ptr<Cad2d_Plane>& m)
	{
		return m->Segments();
	}

	void printBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager)
	{
		Info << endl
			<< " - list of the corners: " << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	void printBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager)
	{
		Info << endl
			<< " - list of the segments: " << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	auto createBoundarySizeMap(const std::string& name, const std::shared_ptr<Cad2d_Plane>& model)
	{
		TNB_CHECK_LOADED;
		if (NOT myEdgeSamples)
		{
			//myEdgeSamples = std::make_shared<Geo2d_SegmentCloud_SamplesLev0>();
		}
		myBoundarySizeMaps->CreateSizeMap(name, model, myEdgeSamples);
		return myBoundarySizeMaps->SelectMap(name);
	}

	void importEntityPatch(const std::shared_ptr<Mesh2d_BoundarySizeMapTool>& theSizeMap, const std::string& name)
	{
		theSizeMap->ImportPatch(name);
	}

	const auto& meshConditions(const std::shared_ptr<Mesh2d_BoundarySizeMapTool>& theSizeMap)
	{
		return theSizeMap->MeshConditions();
	}

	const auto& meshValues(const std::shared_ptr<Mesh2d_BoundarySizeMapTool>& theSizeMap)
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
		std::vector<std::shared_ptr<GeoMesh2d_Background>> backs;
		if (myBoundarySizeMaps->NbMaps())
		{
			backs.push_back(myBoundarySizeMaps->BackgroundMesh());
		}
		/*if (myFeatureSizeMaps->NbMaps())
		{
			backs.push_back(myFeatureSizeMaps->BackgroundMesh());
		}*/
		return std::move(backs);
	}

	void execute(const std::string& name)
	{
		TNB_CHECK_LOADED;

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
		mod->add(chaiscript::fun([](const std::string& name, const std::shared_ptr<Cad2d_Plane>& model)-> auto {return createBoundarySizeMap(name, model); }), "createBoundarySizeMap");
		//mod->add(chaiscript::fun([](const std::string& name, const std::shared_ptr<Cad2d_Plane>& model)-> auto {return createFeatureSizeMap(name, model); }), "createFeatureSizeMap");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh2d_BoundarySizeMapTool>& sm, const std::string& name)-> void {importEntityPatch(sm, name); }), "importPatch");

		mod->add(chaiscript::fun([](int i)-> auto {return myModels.at(i); }), "getModel");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad2d_Plane>& m)-> void {printNbCorners(m); }), "printNbCorners");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad2d_Plane>& m)-> void {printNbSegments(m); }), "printNbSegments");
		//mod->add(chaiscript::fun([](const std::shared_ptr<Cad2d_Plane>& m)-> void {printNbFaces(m); }), "printNbFaces");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& m)-> void {printBlocks(m); }), "printBlocks");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& m)-> void {printBlocks(m); }), "printBlocks");
		//mod->add(chaiscript::fun([](const std::shared_ptr<TModel_FaceManager>& m)-> void {printBlocks(m); }), "printBlocks");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad2d_Plane>& m)-> auto {return getCorners(m); }), "getCorners");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad2d_Plane>& m)-> auto {return getSegments(m); }), "getSegments");
		//mod->add(chaiscript::fun([](const std::shared_ptr<Cad2d_Plane>& m)-> auto {return getFaces(m); }), "getFaces");

		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh2d_BoundarySizeMapTool>& sm)-> auto {return meshConditions(sm); }), "getMeshConditions");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh2d_BoundarySizeMapTool>& sm)-> auto {return meshValues(sm); }), "getMeshValues");
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

int main(int argc, char* argv[])
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
				<< " - printNbSegments(model)" << endl << endl

				<< " - printBlocks(manager)" << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl

				<< " # Operators:" << endl << endl

				<< " - [manager] getCorners(model);                     - it gives the corner manager." << endl
				<< " - [manager] getSegments(model);                    - it gives the segment manager." << endl << endl

				<< " - [model] getModel(int);" << endl
				<< " - [sizeMap] createBoundarySizeMap(name, model);" << endl << endl

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
				auto address = file::GetSystemFile("tnbMeshSizeMap2dAdaptive");
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