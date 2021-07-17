#include <Mesh_ReferenceValues.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fstream>

namespace tnbLib
{

	static unsigned short verbose = 0;
	typedef std::shared_ptr<Mesh_ReferenceValues> ref_t;

	
	static double myBaseSize = 0.01;
	static auto myRef = std::make_shared<Mesh_ReferenceValues>(myBaseSize);

	static const double DEFAULT_MIN_SIZE = 1.0E-6;

	void saveTo(const std::string& name)
	{
		if (NOT myRef)
		{
			FatalErrorIn(FunctionSIG)
				<< "no ref. data has been created!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);

		oa << myRef;

		if (verbose)
		{
			Info << " the reference values are saved to: " << fn << ", successfully!" << endl;
			Info << endl;
		}
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
		return myRef->SurfaceSizeRef();
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
		return myRef->SurfaceCurvatureRef();
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

		mod->add(chaiscript::fun([](double x)-> void {setBaseSize(x); }), "setBaseSize");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setGrowthRate(name); }), "setDefaultGrowthRate");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setBoundaryGrowthRate(name); }), "setBoundaryGrowthRate");

		mod->add(chaiscript::fun([]()-> auto& {return getSurfaceSizeValues(); }), "getSurfaceSizeValues");
		mod->add(chaiscript::fun([](Mesh_SurfaceSizeValues& v, const std::string& name)-> void {setValueMethod(v, name); }), "setValueType");
		mod->add(chaiscript::fun([](Mesh_SurfaceSizeValues& v, const std::string& name)-> void {setMethod(v, name); }), "setMethod");
		mod->add(chaiscript::fun([](Mesh_SurfaceSizeValues& v, double x)-> void {setMinSize(v, x); }), "setMinSize");
		mod->add(chaiscript::fun([](Mesh_SurfaceSizeValues& v, double x)->void {setTargetSize(v, x); }), "setTargetSize");

		mod->add(chaiscript::fun([]()-> auto&{return getCurvatureValues(); }), "getCurvatureValues");
		mod->add(chaiscript::fun([](Mesh_SurfaceCurvatureValues& v, const std::string& name)-> void {setCurvatureInfo(v, name); }), "setType");
		mod->add(chaiscript::fun([](Mesh_SurfaceCurvatureValues& v, double x)-> void {setSpanAngle(v, x); }), "setSpanAngle");

		mod->add(chaiscript::fun([](unsigned short i)-> void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			fileName myFileName("refSizeMap");

			try
			{
				chai.eval_file(myFileName);
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
			FatalErrorIn(FunctionSIG)
				<< "Undefined command has been detected!" << endl
				<< abort(FatalError);
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}