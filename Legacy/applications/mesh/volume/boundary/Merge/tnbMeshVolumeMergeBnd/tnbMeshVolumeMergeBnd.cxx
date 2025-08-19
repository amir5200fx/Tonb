#include <Aft3d_SolutionData_SurfVol.hxx>
#include <Merge3d_Triangulation.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static unsigned short verbose = 0;
	static bool load_tag = false;
	static bool exe_tag = false;

	static double my_tol = 1.0e-6;

	static const auto extension = Aft3d_SolutionData_SurfVol::extension;

	static std::shared_ptr<Aft3d_SolutionData_SurfVol> my_solu_data;
	static std::string my_file_name;

	void set_verbose(unsigned int i)
	{
		Info << "\n"
			<< " - the verbosity level is set to: " << i << "\n";
		verbose = i;
	}

	void set_tol(double x)
	{
		if (verbose)
		{
			Info << " - TOL has been set to: " << my_tol << "\n";
		}
		my_tol = x;
	}

	void load_file(const std::string& name)
	{
		file::CheckExtension(name);
		my_solu_data = file::LoadFile<std::shared_ptr<Aft3d_SolutionData_SurfVol>>(name + extension, verbose);
		if (NOT my_solu_data)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the file contain null object." << endl
				<< abort(FatalError);
		}
		load_tag = true;
	}

	void load_file()
	{
		const auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		my_file_name = name;
		load_file(name);
	}

	void save_to(const std::string& name)
	{
		if (NOT exe_tag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " the application has not been performed." << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(my_solu_data, name + extension, verbose);
	}

	void save_to()
	{
		if (NOT exe_tag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " the application has not been performed." << endl
				<< abort(FatalError);
		}
		save_to(my_file_name);
	}

	void execute()
	{
		const auto unmerged = std::make_shared<Entity3d_Triangulation>();
		for (const auto& [id, surface] : my_solu_data->Tris())
		{
			unmerged->Add(*surface);
		}
		{
			const auto bnd_box = Geo_BoxTools::GetBox(unmerged->Points(), 0);
			const auto alg = std::make_shared<Merge3d_Triangulation>();
			alg->SetTriangulation(unmerged);
			alg->SetRadius(bnd_box.Diameter() * my_tol);
			alg->Perform();

			my_solu_data->MergedRef() = alg->Merged();
		}
		exe_tag = true;
		if (verbose)
		{
			Info << endl
				<< " The application has been successfully performed!" << endl;
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

	void setFuns(const module_t& mod)
	{
		// io functions 
		mod->add(chaiscript::fun([](const std::string& name)-> void {save_to(name); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {save_to(); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {load_file(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name)-> void {load_file(name); }), "load_file");

		// settings 
		mod->add(chaiscript::fun([](unsigned short i)-> void {set_verbose(i); }), "set_verbose");
		mod->add(chaiscript::fun([](double x)-> void {set_tol(x); }), "set_tol");

		// operators 
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
			Info << " This application is aimed to merge the boundary mesh volume." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_file(name [optional])" << endl
				<< " - save_to(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - set_verbose(unsigned int); Levels: 0, 1" << endl
				<< " - set_tol(x)" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
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
				fileName myFileName(file::GetSystemFile("tnbMeshVolumeMergeBnd"));

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