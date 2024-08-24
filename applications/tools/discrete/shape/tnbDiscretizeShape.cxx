#include <Global_Timer.hxx>
#include <Entity3d_Box.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>
#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo


#include <Poly_Triangulation.hxx>
#include <BRepTools.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	static const std::string extension = Cad_Shape::extension;

	typedef std::shared_ptr<Cad_Shape> shape_t;
	typedef std::shared_ptr<FastDiscrete_Params> param_t;

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static shape_t myShape;
	static std::string myFileName;
	
	double myAngle = 5.0;
	double myDeflection = 1.0E-3;
	double myMinSize = 1.0E-6;
	auto inParallel = false;
	auto inRalative = true;
	auto adaptiveMin = false;
	auto internalVerticesMode = true;
	auto controlSurfaceDeflection = true;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

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

	void loadModel(const std::string& name)
	{
		file::CheckExtension(name);

		myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + extension, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}
		if (verbose)
		{
			Info << " - shape's name: " << myShape->Name() << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void loadModel()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension);
		myFileName = name.string();
		loadModel(myFileName);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the algorithm has not been performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myShape, name + extension, verbose);
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
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		
		if (Cad_Tools::HasTriangulation(myShape->Shape()))
		{
			FatalErrorIn(FunctionSIG)
				<< "the shape has already been discretized!" << endl
				<< abort(FatalError);
		}

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

	void setFunctions(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "load_file");
		mod->add(chaiscript::fun([]()-> void {loadModel(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "save_to");

		mod->add(chaiscript::fun([]()-> void {printDefaults(); }), "print_defaults");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "set_verbose");

		mod->add(chaiscript::fun([](double x)-> void {setAngle(x); }), "set_angle");
		mod->add(chaiscript::fun([](double x)-> void {setDeflection(x); }), "set_deflection");
		mod->add(chaiscript::fun([](double x)-> void {setMinSize(x); }), "set_min_size");
		mod->add(chaiscript::fun([](bool c)-> void {setParallelMode(c); }), "set_parallel_mode");
		mod->add(chaiscript::fun([](bool c)-> void {setRelativeMode(c); }), "set_relative_mode");
		mod->add(chaiscript::fun([](bool c)-> void {setAdaptiveMin(c); }), "set_adaptive_min_mode");
		mod->add(chaiscript::fun([](bool c)-> void {setInternalVertices(c); }), "set_internal_vertices_mode");
		mod->add(chaiscript::fun([](bool c)-> void {setControlSurfaceDeflection(c); }), "set_control_surface_deflection_mode");
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
			Info << " Function list:" << endl << endl
				
				<< " # IO functions: " << endl << endl

				<< " - print_defaults()" << endl
				<< " - load_model(name [optional])" << endl
				<< " - save_to(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - set_verbose(unsigned int); Levels: 0, 1, 2" << endl
				<< " - set_angle(double)" << endl
				<< " - set_deflection(double)" << endl
				<< " - set_min_size(double)" << endl
				<< " - set_parallel_mode(bool)" << endl
				<< " - set_adaptive_min_mode(bool)" << endl
				<< " - set_internal_vertices_mode(bool)" << endl
				<< " - set_control_surface_deflection_mode(bool)" << endl << endl

				<< " - execute()" << endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			//std::string address = ".\\system\\tnbDiscretizeShape";	

			try
			{
				fileName theFileName(file::GetSystemFile("tnbDiscretizeShape"));
				chai.eval_file(theFileName);
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