#include <GeoIntsct3d_PlnTris.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Geo_Serialization.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static const std::string extension = GeoIntsct3d_PlnTris::intsctEntity::extension;

	static std::vector<std::shared_ptr<GeoIntsct3d_PlnTris::intsctEntity>> myEntities;
	static std::shared_ptr<Entity3d_Triangulation> myTris;

	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myEntities = file::LoadFile<std::vector<std::shared_ptr<GeoIntsct3d_PlnTris::intsctEntity>>>(name + extension, verbose);
		if (NOT myEntities.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "the entity list is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
		loadFile(name);
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

		file::SaveTo(myTris, name + Entity3d_Triangulation::extension, verbose);
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

	auto getTri(const std::shared_ptr<GeoIntsct3d_PlnTris::pntIntsct>& ent)
	{
		Entity3d_Triangulation tri;
		tri.Points() = ent->RetrievePoints();
		connectivity::triple I;
		I.Value(0) = 1;
		I.Value(1) = 1;
		I.Value(2) = 1;
		std::vector<connectivity::triple> indices = { std::move(I) };
		tri.Connectivity() = std::move(indices);
		return std::move(tri);
	}

	auto getTri(const std::shared_ptr<GeoIntsct3d_PlnTris::segIntsct>& ent)
	{
		Entity3d_Triangulation tri;
		tri.Points() = ent->RetrievePoints();
		connectivity::triple I;
		I.Value(0) = 1;
		I.Value(1) = 2;
		I.Value(2) = 1;
		std::vector<connectivity::triple> indices = { std::move(I) };
		tri.Connectivity() = std::move(indices);
		return std::move(tri);
	}

	auto getTri(const std::shared_ptr<GeoIntsct3d_PlnTris::triIntsct>& ent)
	{
		Entity3d_Triangulation tri;
		tri.Points() = ent->RetrievePoints();
		connectivity::triple I;
		I.Value(0) = 1;
		I.Value(1) = 2;
		I.Value(2) = 3;
		std::vector<connectivity::triple> indices = { std::move(I) };
		tri.Connectivity() = std::move(indices);
		return std::move(tri);
	}

	void execute()
	{
		auto tri = std::make_shared<Entity3d_Triangulation>();
		for (const auto& x : myEntities)
		{
			if (x->IsPoint())
			{
				auto ent = std::dynamic_pointer_cast<GeoIntsct3d_PlnTris::pntIntsct>(x);
				auto t = getTri(ent);
				tri->Add(t);
			}
			else if (x->IsSegment())
			{
				auto ent = std::dynamic_pointer_cast<GeoIntsct3d_PlnTris::segIntsct>(x);
				auto t = getTri(ent);
				tri->Add(t);
			}
			else if (x->IsTriangle())
			{
				auto ent = std::dynamic_pointer_cast<GeoIntsct3d_PlnTris::triIntsct>(x);
				auto t = getTri(ent);
				tri->Add(t);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to identity the type of entity!" << endl
					<< abort(FatalError);
			}
		}
		myTris = std::move(tri);

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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
		// io functions [12/21/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/21/2021 Amir]
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
			Info << " This application is aimed to view the entities of the intersection of a plane and a mesh." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbMeshToolPlnIntsctViewer"));

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