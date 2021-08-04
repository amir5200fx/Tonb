#include <Global_Timer.hxx>
#include <Entity3d_Box.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>
#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Poly_Triangulation.hxx>

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

	void setAngle(double x)
	{
		myAngle = x;
		if (verbose)
		{
			Info << endl
				<< " - Angle deflection is set to: " << myAngle << endl;
		}
	}

	void setDeflection(double x)
	{
		myDeflection = x;
		if (verbose)
		{
			Info << endl
				<< " - Deflection is set to: " << myDeflection << endl;
		}
	}

	void setMinSize(double x)
	{
		myMinSize = x;
		if (verbose)
		{
			Info << endl
				<< " - Min. size is set to: " << myMinSize << endl;
		}
	}

	void setRelativeMode(bool x)
	{
		inRalative = x;
		if (verbose)
		{
			Info << endl
				<< " - Relative mode is set to: " << inRalative << endl;
		}
	}

	void setParallelMode(bool x)
	{
		inParallel = x;
		if (verbose)
		{
			Info << endl
				<< " - Parallel mode is set to: " << (inParallel ? "TRUE" : "FALSE") << endl;
		}
	}

	void setAdaptiveMin(bool x)
	{
		adaptiveMin = x;
		if (verbose)
		{
			Info << endl
				<< " - AdaptiveMin is set to:" << (adaptiveMin ? "TRUE" : "FALSE") << endl;
		}
	}

	void setInternalVertices(bool x)
	{
		internalVerticesMode = x;
		if (verbose)
		{
			Info << endl
				<< " - Internal vertices mode is set to: " << (internalVerticesMode ? "TRUE" : "FALSE") << endl;
		}
	}

	void setControlSurfaceDeflection(bool x)
	{
		controlSurfaceDeflection = x;
		if (verbose)
		{
			Info << endl
				<< " - Control surface deflection is set to: " << (controlSurfaceDeflection ? "TRUE" : "FALSE") << endl;
		}
	}

	void printDefaults()
	{
		Info << " Default values of the FastDiscrete algorithm are:" << endl
			<< " - angle: " << myAngle << endl
			<< " - deflection: " << myDeflection << endl
			<< " - min. size: " << myMinSize << endl
			<< " - parallel mode? " << (inParallel ? "yes" : "no") << endl
			<< " - relative mode? " << (inRalative ? "yes" : "no") << endl
			<< " - adaptive min.? " << (adaptiveMin ? "yes" : "no") << endl
			<< " - internal vertices mode? " << (internalVerticesMode ? "yes" : "no") << endl
			<< " - control surface deflection? " << (controlSurfaceDeflection ? "yes" : "no") << endl;
	}

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
		if (verbose > 1)
		{
			const auto surfaces = Cad_Tools::RetrieveTriangulation(myShape->Shape());
			Info << " - nb. of surfaces: " << surfaces.size() << endl;
			size_t k = 0;
			size_t nbNodes = 0;
			size_t nbTris = 0;
			for (const auto& x : surfaces)
			{
				if (x)
				{
					Info << " - surface nb. " << k++ << ": "
						<< "nb. of nodes: " << x->NbNodes() << ", nb. of triangles: " << x->NbTriangles()
						<< ", Deflection: " << x->Deflection() << endl;

					nbNodes += x->NbNodes();
					nbTris += x->NbTriangles();
				}
			}
			Info << endl;
			Info << " - Total nb. of nodes: " << nbNodes << endl;
			Info << " - Total nb. of triangles: " << nbTris << endl;
			Info << endl;

			/*double yMin = RealLast();
			for (const auto& x : surfaces)
			{
				const auto& nodes = x->Nodes();
				for (const auto& n : nodes)
				{
					if (n.Coord().Y() < yMin) yMin = n.Coord().Y();
				}
			}
			std::cout << "yMin = " << yMin << std::endl;*/
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
		mod->add(chaiscript::fun([]()-> void {printDefaults(); }), "printDefaults");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([](double x)-> void {setAngle(x); }), "setAngle");
		mod->add(chaiscript::fun([](double x)-> void {setDeflection(x); }), "setDeflection");
		mod->add(chaiscript::fun([](double x)-> void {setMinSize(x); }), "setMinSize");
		mod->add(chaiscript::fun([](bool c)-> void {setParallelMode(c); }), "setParallelMode");
		mod->add(chaiscript::fun([](bool c)-> void {setRelativeMode(c); }), "setRelativeMode");
		mod->add(chaiscript::fun([](bool c)-> void {setAdaptiveMin(c); }), "setAdaptiveMinMode");
		mod->add(chaiscript::fun([](bool c)-> void {setInternalVertices(c); }), "setInternalVerticesMode");
		mod->add(chaiscript::fun([](bool c)-> void {setControlSurfaceDeflection(c); }), "setControlSurfaceDeflectionMode");
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
			Info << endl;
			Info << "This application is aimed to discrete surfaces of the shape." << endl;
			Info << endl;
			Info << " Function list:" << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl
				<< " - printDefaults()" << endl << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl
				<< " - setAngle(double)" << endl
				<< " - setDeflection(double)" << endl
				<< " - setMinSize(double)" << endl
				<< " - setParallelMode(bool)" << endl
				<< " - setAdaptiveMinMode(bool)" << endl
				<< " - setInternalVerticesMode(bool)" << endl
				<< " - setControlSurfaceDeflectionMode(bool)" << endl << endl
				<< " - execute()" << endl;
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

}