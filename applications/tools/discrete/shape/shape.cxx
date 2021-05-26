#include <Global_Timer.hxx>
#include <Entity3d_Box.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>
#include <Cad_Shape.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<Cad_Shape> shape_t;
	typedef std::shared_ptr<FastDiscrete_Params> param_t;

	static unsigned short verbose(0);
	static bool loadTag = false;

	static shape_t myShape;
	
	double myAngle = 5.0;
	double myDeflection = 1.0E-3;
	double myMinSize = 1.0E-6;
	auto inParallel = false;
	auto inRalative = true;
	auto adaptiveMin = false;
	auto internalVerticesMode = true;
	auto controlSurfaceDeflection = true;

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

		TNB_iARCH_FILE_TYPE ar(myFile);

		ar >> myShape;
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded body is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the shape is loaded, from: " << name << ", successfully!" << endl;
			Info << " - shape's name: " << myShape->Name() << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myShape;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the shape is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute()
	{
		const auto& b = myShape->BoundingBox();
		if (NOT b)
		{
			FatalErrorIn(FunctionSIG)
				<< "no bounding box has been found!" << endl
				<< abort(FatalError);
		}

		const auto d = b->Diameter();
		auto params = FastDiscrete_Params();
		params.Angle = Geo_Tools::DegToRadian(myAngle);
		params.Deflection = myDeflection * d;
		params.MinSize = myMinSize * d;
		params.InParallel = inParallel;
		params.Relative = inRalative;
		params.AdaptiveMin = adaptiveMin;
		params.InternalVerticesMode = internalVerticesMode;
		params.ControlSurfaceDeflection = controlSurfaceDeflection;

		{// timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_s);
			Cad_FastDiscrete::Triangulation(myShape->Shape(), params);
		}
		if (verbose)
		{
			Info << endl;
			Info << " Discretization of the model has been completed, in " << global_time_duration << ", seconds.";
			Info << endl;

		}
	}


}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFunctions(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		//- io functions

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([](double x)-> void {myAngle = x; }), "setAngle");
		mod->add(chaiscript::fun([](double x)-> void {myDeflection = x; }), "setDeflection");
		mod->add(chaiscript::fun([](double x)-> void {myMinSize = x; }), "setMinSize");
		mod->add(chaiscript::fun([](bool c)-> void {inParallel = c; }), "parallelMode");
		mod->add(chaiscript::fun([](bool c)-> void {inRalative = c; }), "relativeMode");
		mod->add(chaiscript::fun([](bool c)-> void {adaptiveMin = c; }), "adaptiveMinMode");
		mod->add(chaiscript::fun([](bool c)-> void {internalVerticesMode = c; }), "internalVerticesMode");
		mod->add(chaiscript::fun([](bool c)-> void {controlSurfaceDeflection = c; }), "controlSurfaceDeflectionMode");
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
	//sysLib::init_gl_marine_integration_info();
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

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("discreteShape");

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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}