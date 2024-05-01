#include <Mesh3d_ReferenceValues.hxx>
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

	static double myBaseSize = 0.01;
	static double myDia = 0;
	static auto myRef = std::make_shared<Mesh3d_ReferenceValues>(myBaseSize, nullptr);

	static const double DEFAULT_MIN_SIZE = 1.0E-6;

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadRegion()
	{
		checkFolder("region");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/7/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\region)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			std::string address;
			std::getline(myFile, address);

			// change the current path [2/6/2023 Payvand]
			boost::filesystem::current_path(address);

			{
				auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Box::extension).string();
				auto myRegion = file::LoadFile<std::shared_ptr<Entity3d_Box>>(name + Entity3d_Box::extension, verbose);
				if (NOT myRegion)
				{
					FatalErrorIn(FunctionSIG)
						<< " the region file is null!" << endl
						<< abort(FatalError);
				}
				myDia = myRegion->Diameter();
				myRef->SetRegion(myRegion);
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Box::extension).string();
			auto myRegion = file::LoadFile<std::shared_ptr<Entity3d_Box>>(name + Entity3d_Box::extension, verbose);
			if (NOT myRegion)
			{
				FatalErrorIn(FunctionSIG)
					<< " the region file is null!" << endl
					<< abort(FatalError);
			}
			myDia = myRegion->Diameter();
			myRef->SetRegion(myRegion);
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadRegion(const std::string& name)
	{
		file::CheckExtension(name);
		auto myRegion = file::LoadFile<std::shared_ptr<Entity3d_Box>>(name + Entity3d_Box::extension, verbose);
		if (NOT myRegion)
		{
			FatalErrorIn(FunctionSIG)
				<< "the region file is null." << endl
				<< abort(FatalError);
		}
		myDia = myRegion->Diameter();
		myRef->SetRegion(myRegion);
		loadTag = true;
	}

	void loadFile()
	{
		if (boost::filesystem::is_directory("region"))
		{
			loadRegion();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Box::extension).string();
			loadRegion(name);
		}

		loadTag = true;
	}


	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no region has been loaded!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);
		file::SaveTo(myRef, name + extension, verbose);
	}

	void saveTo()
	{
		saveTo("meshReference");
	}

	void setBaseSize(double x)
	{
		if (x < DEFAULT_MIN_SIZE) x = DEFAULT_MIN_SIZE;
		myRef->SetBaseSize(x);
	}

	void setGrowthRate(const std::string& rate)
	{
		if (rate IS_EQUAL "verySlow")
		{
			myRef->SetDefaultGrowthRate(Mesh_VariationRateInfo::verySlow);
		}
		else if (rate IS_EQUAL "slow")
		{
			myRef->SetDefaultGrowthRate(Mesh_VariationRateInfo::slow);
		}
		else if (rate IS_EQUAL "moderate")
		{
			myRef->SetDefaultGrowthRate(Mesh_VariationRateInfo::moderate);
		}
		else if (rate IS_EQUAL "fast")
		{
			myRef->SetDefaultGrowthRate(Mesh_VariationRateInfo::fast);
		}
		else if (rate IS_EQUAL "custom")
		{
			myRef->SetDefaultGrowthRate(Mesh_VariationRateInfo::custom);
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

	void setBoundaryGrowthRate(const std::string& rate)
	{
		if (rate IS_EQUAL "verySlow")
		{
			myRef->SetBoundaryGrowthRate(Mesh_VariationRateInfo::verySlow);
		}
		else if (rate IS_EQUAL "slow")
		{
			myRef->SetBoundaryGrowthRate(Mesh_VariationRateInfo::slow);
		}
		else if (rate IS_EQUAL "moderate")
		{
			myRef->SetBoundaryGrowthRate(Mesh_VariationRateInfo::moderate);
		}
		else if (rate IS_EQUAL "fast")
		{
			myRef->SetBoundaryGrowthRate(Mesh_VariationRateInfo::fast);
		}
		else if (rate IS_EQUAL "custom")
		{
			myRef->SetBoundaryGrowthRate(Mesh_VariationRateInfo::custom);
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

	auto& getSurfaceSizeValues()
	{
		return *myRef->SurfaceSize();
	}

	void setMethod(Mesh_SurfaceSizeValues& v, const std::string& name)
	{
		if (name IS_EQUAL "minOnly")
		{
			v.SetSizeMethod(Mesh_SizeMethodInfo::minOnly);
		}
		else if (name IS_EQUAL "minAndTarget")
		{
			v.SetSizeMethod(Mesh_SizeMethodInfo::minAndTerget);
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

	void setValueMethod(Mesh_SurfaceSizeValues& v, const std::string& name)
	{
		if (name IS_EQUAL "relativeToBase")
		{
			v.SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo::relativeToBase);
		}
		else if (name IS_EQUAL "absolute")
		{
			v.SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo::absolute);
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

	void setMinSize(Mesh_SurfaceSizeValues& v, double x)
	{
		if (x < DEFAULT_MIN_SIZE) x = DEFAULT_MIN_SIZE;
		v.SetMinSize(x);
	}

	void setTargetSize(Mesh_SurfaceSizeValues& v, double x)
	{
		if (x < DEFAULT_MIN_SIZE) x = DEFAULT_MIN_SIZE;
		v.SetTargetSize(x);
	}

	auto& getCurvatureValues()
	{
		return *myRef->SurfaceCurvature();
	}

	void setCurvatureInfo(Mesh_SurfaceCurvatureValues& v, const std::string& name)
	{
		if (name IS_EQUAL "continum")
		{
			v.SetCurvatureInfo(Mesh_SurfaceCurvatureInfo::continum);
		}
		else if (name IS_EQUAL "custom")
		{
			v.SetCurvatureInfo(Mesh_SurfaceCurvatureInfo::custom);
		}
		else if (name IS_EQUAL "disable")
		{
			v.SetCurvatureInfo(Mesh_SurfaceCurvatureInfo::disable);
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

	void setSpanAngle(Mesh_SurfaceCurvatureValues& v, double x)
	{
		x = Geo_Tools::DegToRadian(x);
		if (x < DEFAULT_MIN_SIZE) x = DEFAULT_MIN_SIZE;
		v.SetSpanAngle(x);
	}

	auto get_diameter()
	{
		if (!loadTag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " no file has been loaded." << endl
				<< abort(FatalError);
		}
		return myDia;
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& file)->void {loadRegion(file); }), "loadFile");

		// functions
		mod->add(chaiscript::fun([]()-> auto {return get_diameter(); }), "Diameter");


		// settings [12/12/2021 Amir]

		mod->add(chaiscript::fun([](double x)-> void {setBaseSize(x); }), "setBaseSize");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setGrowthRate(name); }), "setDefaultGrowthRate");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setBoundaryGrowthRate(name); }), "setBoundaryGrowthRate");


		mod->add(chaiscript::fun([](const std::string& name)-> void {setValueMethod(getSurfaceSizeValues(), name); }), "setSurfSizeValueType");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setMethod(getSurfaceSizeValues(), name); }), "setSurfSizeMethod");
		mod->add(chaiscript::fun([](double x)-> void {setMinSize(getSurfaceSizeValues(), x); }), "setSurfMinSize");
		mod->add(chaiscript::fun([](double x)->void {setTargetSize(getSurfaceSizeValues(), x); }), "setSurfTargetSize");

		mod->add(chaiscript::fun([](const std::string& name)-> void {setCurvatureInfo(getCurvatureValues(), name); }), "setCurvatureType");
		mod->add(chaiscript::fun([](double x)-> void {setSpanAngle(getCurvatureValues(), x); }), "setCurvatureSpanAngle");

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
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setBaseSize(double)" << endl
				<< " - setDefaultGrowthRate(string);         Types: verySlow, slow, moderate, fast, costum" << endl
				<< " - setBoundaryGrowthRate(string);        Types: verySlow, slow, moderate, fast, costum" << endl << endl

				<< " - setSurfSizeValueType(string);  Types: relativeToBase, absolute" << endl
				<< " - setSurfSizeMethod(string);     Types: minOnly, minAndTarget" << endl
				<< " - setSurfMinSize(double)" << endl
				<< " - setSurfTargetSize(double)" << endl << endl

				<< " - setCurvatureType(string);  Types: continum, custom, disable" << endl
				<< " - setCurvatureSpanAngle(double)" << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - Diameter()" << endl
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