#include <GeoSlicer3d_PlnTris.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Geo_Serialization.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>

namespace tnbLib
{

	static std::shared_ptr<Entity3d_Triangulation> myModel;
	static std::shared_ptr<Entity3d_Triangulation> myClipped;

	static std::pair<std::shared_ptr<gp_Pln>, double> myPln0;
	static std::pair<std::shared_ptr<gp_Pln>, double> myPln1;

	static std::shared_ptr<gp_Ax1> myAxis;
 
	static unsigned short verbose = 0;
	static auto exeTag = false;
	static auto loadTag = false;


	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);
		file::SaveTo(myClipped, name + Entity3d_Triangulation::extension, verbose);
	}

	void loadModel()
	{
		checkFolder("model");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\model)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [2/6/2023 Payvand]
				boost::filesystem::current_path(address);

				auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();
				myModel = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
				if (NOT myModel)
				{
					FatalErrorIn(FunctionSIG)
						<< " the model is null." << endl
						<< abort(FatalError);
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();
			myModel = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
			if (NOT myModel)
			{
				FatalErrorIn(FunctionSIG)
					<< " the model is null." << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadPlanes()
	{
		checkFolder("planes");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\planes)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.is_open())
			{
				std::vector<std::shared_ptr<gp_Pln>> planes;
				std::vector<double> locs;
				std::string address;
				while (std::getline(myFile, address))
				{
					// change the current path [2/6/2023 Payvand]
					boost::filesystem::current_path(address);
					{
						auto name = file::GetSingleFile(boost::filesystem::current_path(), ".gpln").string();
						auto pl = file::LoadFile<std::shared_ptr<gp_Pln>>(name + ".gpln", verbose);
						if (NOT pl)
						{
							FatalErrorIn(FunctionSIG)
								<< " the plane is null." << endl
								<< abort(FatalError);
						}
						locs.push_back(pl->Location().Distance(myAxis->Location()));
						planes.push_back(std::move(pl));
					}
				}
				if (planes.size() NOT_EQUAL 2)
				{
					FatalErrorIn(FunctionSIG)
						<< "there must be two planes." << endl
						<< abort(FatalError);
				}
				myPln0 = std::make_pair(planes.at(0), locs.at(0));
				myPln1 = std::make_pair(planes.at(1), locs.at(1));
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			std::vector<std::shared_ptr<gp_Pln>> planes;
			std::vector<double> locs;
			size_t i = 0;
			while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
			{
				auto icurrentPath = boost::filesystem::current_path().string() + R"(\)" + std::to_string(i);
				auto name = file::GetSingleFile(icurrentPath, ".gpln").string();
				std::string address = ".\\" + std::to_string(i) + "\\" + name + ".gpln";
				auto pln = file::LoadFile<std::shared_ptr<gp_Pln>>(address, verbose);
				if (NOT pln)
				{
					FatalErrorIn(FunctionSIG)
						<< "the plane is null." << endl
						<< abort(FatalError);
				}
				locs.push_back(pln->Location().Distance(myAxis->Location()));
				planes.push_back(std::move(pln));
				i++;
			}
			if (planes.size() NOT_EQUAL 2)
			{
				FatalErrorIn(FunctionSIG)
					<< "there must be two planes." << endl
					<< abort(FatalError);
			}
			myPln0 = std::make_pair(planes.at(0), locs.at(0));
			myPln1 = std::make_pair(planes.at(1), locs.at(1));
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadAxis()
	{
		checkFolder("axis");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\axis)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [2/6/2023 Payvand]
				boost::filesystem::current_path(address);

				auto name = file::GetSingleFile(boost::filesystem::current_path(), ".axis3d").string();
				myAxis = file::LoadFile<std::shared_ptr<gp_Ax1>>(name + ".axis3d", verbose);
				if (NOT myAxis)
				{
					FatalErrorIn(FunctionSIG)
						<< " the axis is null." << endl
						<< abort(FatalError);
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".axis3d").string();
			myAxis = file::LoadFile<std::shared_ptr<gp_Ax1>>(name + ".axis3d", verbose);
			if (NOT myAxis)
			{
				FatalErrorIn(FunctionSIG)
					<< " the axis is null." << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadFiles()
	{
		if (boost::filesystem::is_directory("model"))
		{
			loadModel();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no 'model' directory has been found." << endl
				<< abort(FatalError);
		}
		if (boost::filesystem::is_directory("axis"))
		{
			loadAxis();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no 'axis' directory has been found." << endl
				<< abort(FatalError);
		}
		if (boost::filesystem::is_directory("planes"))
		{
			loadPlanes();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no 'planes' directory has been found." << endl
				<< abort(FatalError);
		}
		
		loadTag = true;
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		if (NOT myPln0.first)
		{
			FatalErrorIn(FunctionSIG)
				<< "the plane 0 is null" << endl
				<< abort(FatalError);
		}
		if (NOT myPln1.first)
		{
			FatalErrorIn(FunctionSIG)
				<< "the plane 1 is null" << endl
				<< abort(FatalError);
		}
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "the model is null" << endl
				<< abort(FatalError);
		}
		if(myPln1.second < myPln0.second)
		{
			std::swap(myPln0, myPln1);
		}
		auto norm0 = myPln0.first->Axis().Direction();
		auto norm1 = myPln1.first->Axis().Direction();
		if (norm0.Dot(norm1) >= 0)
		{
			const auto& ax = myPln0.first->Axis();
			myPln0.first->SetAxis(ax.Reversed());
		}
		if (norm0.Dot(myAxis->Direction()) <= 0)
		{
			{
				const auto& ax = myPln0.first->Axis();
				myPln0.first->SetAxis(ax.Reversed());
			}
			{
				const auto& ax = myPln1.first->Axis();
				myPln1.first->SetAxis(ax.Reversed());
			}
		}
		{
			GeoSlicer3d_PlnTris slicer;
			slicer.SetMesh(myModel);
			slicer.SetPlane(myPln1.first);
			slicer.Perform();

			myClipped = slicer.Clipped();
		}
		{
			GeoSlicer3d_PlnTris slicer;
			slicer.SetMesh(myClipped);
			slicer.SetPlane(myPln0.first);
			slicer.Perform();

			myClipped = slicer.Clipped();
		}
		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
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
		//- io functions
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

		// Operators [2/11/2023 Payvand]
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
			Info << " This application is aimed to clip a model." << endl
				<< " - subdirectories: axis, model, planes" << endl
				<< " - two planes are needed to define the span." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - execute()" << endl

				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbShapeFitToolClipModel"));
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