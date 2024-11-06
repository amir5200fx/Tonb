#include <Mesh3d_ReferenceValues.hxx>
#include <Cad_Shape.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static std::string extension = Mesh3d_ReferenceValues::extension;

	static bool loadTag = false;
	static unsigned short verbose = 0;

	static double my_base_size = 0.01;
	static double my_dia = 0;
	static auto my_ref = std::make_shared<Mesh3d_ReferenceValues>(my_base_size, nullptr);

	static const double DEFAULT_MIN_SIZE = 1.0E-6;

	struct SurfConfig
	{
		std::shared_ptr<Mesh_SurfaceSizeValues> values;
		std::shared_ptr<Mesh_SurfaceCurvatureValues> curvature;
	};

	struct SurfConfig_Values
	{
		std::shared_ptr<Mesh_SurfaceSizeValues> config;
	};

	struct SurfConfig_Curvature
	{
		std::shared_ptr<Mesh_SurfaceCurvatureValues> config;
	};

	auto get_surf_config()
	{
		return SurfConfig{ my_ref->SurfaceSize(), my_ref->SurfaceCurvature() };
	}

	auto get_values(const SurfConfig& config)
	{
		return SurfConfig_Values{ config.values };
	}

	auto get_curvature(const SurfConfig& config)
	{
		return SurfConfig_Curvature{ config.curvature };
	}

	void check_folder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void set_verbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void load_shape(const std::string& name)
	{
		file::CheckExtension(name);
		auto shape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + Cad_Shape::extension, verbose);
		if (NOT shape)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the file contains a null shape." << endl
				<< abort(FatalError);
		}
		my_dia = shape->BoundingBox()->Diameter();
		my_ref->SetRegion(shape->BoundingBox());
		loadTag = true;
	}

	void save_to(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no region has been loaded!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);
		file::SaveTo(my_ref, name + extension, verbose);
	}

	void save_to()
	{
		save_to("meshReference");
	}

	void set_base_size(double x)
	{
		if (x < DEFAULT_MIN_SIZE) x = DEFAULT_MIN_SIZE;
		my_ref->SetBaseSize(x);
	}

	void set_growth_rate(const std::string& rate)
	{
		if (rate IS_EQUAL "verySlow")
		{
			my_ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::verySlow);
		}
		else if (rate IS_EQUAL "slow")
		{
			my_ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::slow);
		}
		else if (rate IS_EQUAL "moderate")
		{
			my_ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::moderate);
		}
		else if (rate IS_EQUAL "fast")
		{
			my_ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::fast);
		}
		else if (rate IS_EQUAL "custom")
		{
			my_ref->SetDefaultGrowthRate(Mesh_VariationRateInfo::custom);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified rate of the growth has been detected. valid growth rates are:" << endl
				<< " - verySlow" << endl
				<< " - slow" << endl
				<< " - moderate" << endl
				<< " - fast" << endl
				<< " - custom" << endl
				<< abort(FatalError);
		}
	}

	void set_boundary_growth_rate(const std::string& rate)
	{
		if (rate IS_EQUAL "verySlow")
		{
			my_ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::verySlow);
		}
		else if (rate IS_EQUAL "slow")
		{
			my_ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::slow);
		}
		else if (rate IS_EQUAL "moderate")
		{
			my_ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::moderate);
		}
		else if (rate IS_EQUAL "fast")
		{
			my_ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::fast);
		}
		else if (rate IS_EQUAL "custom")
		{
			my_ref->SetBoundaryGrowthRate(Mesh_VariationRateInfo::custom);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified rate of the growth has been detected. valid growth rates are:" << endl
				<< " - verySlow" << endl
				<< " - slow" << endl
				<< " - moderate" << endl
				<< " - fast" << endl
				<< " - custom" << endl
				<< abort(FatalError);
		}
	}

	void set_method(const SurfConfig_Values& v, const std::string& name)
	{
		if (name IS_EQUAL "minOnly")
		{
			v.config->SetSizeMethod(Mesh_SizeMethodInfo::minOnly);
		}
		else if (name IS_EQUAL "minAndTarget")
		{
			v.config->SetSizeMethod(Mesh_SizeMethodInfo::minAndTerget);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified the method of the surface size value has been detected!" << endl
				<< "The valid methods are:" << endl
				<< " - minOnly" << endl
				<< " - minAndTarget" << endl
				<< abort(FatalError);
		}
	}

	void set_value_method(const SurfConfig_Values& v, const std::string& name)
	{
		if (name IS_EQUAL "relativeToBase")
		{
			v.config->SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo::relativeToBase);
		}
		else if (name IS_EQUAL "absolute")
		{
			v.config->SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo::absolute);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified the method of the value has been detected!" << endl
				<< "The valid methods are:" << endl
				<< " - relativeToBase" << endl
				<< " - absolute" << endl
				<< abort(FatalError);
		}
	}

	void set_min_size(const SurfConfig_Values& v, double x)
	{
		if (x < DEFAULT_MIN_SIZE) x = DEFAULT_MIN_SIZE;
		v.config->SetMinSize(x);
	}

	void set_target_size(const SurfConfig_Values& v, double x)
	{
		if (x < DEFAULT_MIN_SIZE) x = DEFAULT_MIN_SIZE;
		v.config->SetTargetSize(x);
	}

	auto& get_curvature_values()
	{
		return *my_ref->SurfaceCurvature();
	}

	void set_curvature_info(const SurfConfig_Curvature& v, const std::string& name)
	{
		if (name IS_EQUAL "continum")
		{
			v.config->SetCurvatureInfo(Mesh_SurfaceCurvatureInfo::continum);
		}
		else if (name IS_EQUAL "custom")
		{
			v.config->SetCurvatureInfo(Mesh_SurfaceCurvatureInfo::custom);
		}
		else if (name IS_EQUAL "disable")
		{
			v.config->SetCurvatureInfo(Mesh_SurfaceCurvatureInfo::disable);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified the method of the curvature has been detected!" << endl
				<< "The valid methods are:" << endl
				<< " - continum" << endl
				<< " - custom" << endl
				<< " - disable" << endl
				<< abort(FatalError);
		}
	}

	void set_span_anlge(const SurfConfig_Curvature& v, double x)
	{
		x = Geo_Tools::DegToRadian(x);
		if (x < DEFAULT_MIN_SIZE) x = DEFAULT_MIN_SIZE;
		v.config->SetSpanAngle(x);
	}

	auto get_diameter()
	{
		if (!loadTag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " no file has been loaded." << endl
				<< abort(FatalError);
		}
		return my_dia;
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
		// io functions [12/12/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {save_to(name); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {save_to(); }), "save_to");
		mod->add(chaiscript::fun([](const std::string& name)-> void {load_shape(name); }), "load_file");

		// functions
		mod->add(chaiscript::fun([]()-> auto {return get_diameter(); }), "calc_dia");
		mod->add(chaiscript::fun([]()->auto {return get_surf_config(); }), "surf_config");
		mod->add(chaiscript::fun([](const SurfConfig& config)->auto {return get_values(config); }), "values");
		mod->add(chaiscript::fun([](const SurfConfig& config)->auto {return get_curvature(config); }), "curvature");

		// settings [12/12/2021 Amir]

		mod->add(chaiscript::fun([](double x)-> void {set_base_size(x); }), "set_base_size");
		mod->add(chaiscript::fun([](const std::string& name)-> void {set_growth_rate(name); }), "set_default_growth_rate");
		mod->add(chaiscript::fun([](const std::string& name)-> void {set_boundary_growth_rate(name); }), "set_boundary_growth_rate");


		mod->add(chaiscript::fun([](const SurfConfig_Values& config, const std::string& name)-> void {set_value_method(config, name); }), "set_type");
		mod->add(chaiscript::fun([](const SurfConfig_Values& config, const std::string& name)-> void {set_method(config, name); }), "set_method");
		mod->add(chaiscript::fun([](const SurfConfig_Values& config, double x)-> void {set_min_size(config, x); }), "set_min");
		mod->add(chaiscript::fun([](const SurfConfig_Values& config, double x)->void {set_target_size(config, x); }), "set_target");

		mod->add(chaiscript::fun([](const SurfConfig_Curvature& config, const std::string& name)-> void {set_curvature_info(config, name); }), "set_type");
		mod->add(chaiscript::fun([](const SurfConfig_Curvature& config, double x)-> void {set_span_anlge(config, x); }), "set_span_angle");

		mod->add(chaiscript::fun([](unsigned short i)-> void {set_verbose(i); }), "set_verbose");

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
			Info << " This application is aimed to create a reference values for mesh3d algorithm." << endl << endl;
			Info << " - Requirements: A *.shape file must be loaded to calculate the region of the geometry that is supposed to be meshed." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_file(name)" << endl
				<< " - save_to(name [optional])" << endl << endl

				<< " # General Settings: " << endl << endl
				<< " - set_base_size(double)" << endl
				<< " - set_default_growth_rate(string);                 - Types: verySlow, slow, moderate, fast, costum" << endl
				<< " - set_boundary_growth_rate(string);                - Types: verySlow, slow, moderate, fast, costum" << endl 
				<< " - [SurfConfig] surf_config();                      - Getting the surface configuration" << endl << endl

				<< " # Surface size configurations: " << endl << endl

				
				<< " - [SurfConfig.Value] (SurfConfig).values();        - Getting the values settings of surfaces" << endl
				<< " - (SurfConfig.Value).set_type(string);             - Types: relativeToBase, absolute" << endl
				<< " - (SurfConfig.Value).set_method(string);           - Types: minOnly, minAndTarget" << endl
				<< " - (SurfConfig.Value).set_min(double);              - The min. size value" << endl
				<< " - (SurfConfig.Value).set_target(double);           - The target size value" << endl << endl

				<< " # Surface curvature configurations: " << endl << endl

				<< " - [SurfConfig.Curvature] (SurfConfig).curvature(); - Getting the curvature settings of surfaces" << endl
				<< " - (SurfConfig.Curvature).set_type(string);         - Types: continum, custom, disable" << endl
				<< " - (SurfConfig.Curvature).set_span_angle(double);   " << endl

				<< " - set_verbose(unsigned int);                       - Levels: 0, 1" << endl

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
				fileName myFileName(file::GetSystemFile("tnbMeshReference3d"));

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