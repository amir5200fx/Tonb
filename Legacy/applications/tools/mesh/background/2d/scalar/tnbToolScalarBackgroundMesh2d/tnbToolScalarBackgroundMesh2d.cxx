#include <MeshBase_Tools.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Global_File.hxx>
#include <token.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	static std::vector<Pnt2d> myCoords;
	static std::vector<double> myValues;

	static std::shared_ptr<GeoMesh2d_Background> myBackmesh;

	static double myTol = 1.0E-4;

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;

	TNB_SET_VERBOSE_FUN;

	void loadFile(const std::string& name)
	{
		IFstream myfile(name);
		while (myfile.peek() NOT_EQUAL EOF)
		{
			double x, y, value;
			myfile >> x >> y >> value;

			auto pt = Pnt2d(x, y);
			myCoords.push_back(std::move(pt));
			myValues.push_back(value);
		}
		if (verbose)
		{
			Info << " - The list has successfully been loaded." << endl
				<< " - No. of points = " << myCoords.size() << endl << endl;

			Info << token::BEGIN_LIST << endl;
			for (const auto& x : myCoords)
			{
				Info << " - " << x << endl;
			}
			Info << token::END_LIST << endl;
		}
		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		TNB_CHECK_EXE_TAG;
		file::CheckExtension(name);
		file::SaveTo(myBackmesh, name + GeoMesh2d_Background::extension, verbose);
	}

	void execute()
	{
		TNB_CHECK_LOAD_TAG;
		myBackmesh = MeshBase_Tools::MakeBackground(myCoords, myValues, myTol);
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
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {return loadFile(name); }), "loadFile");

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
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
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a two-dimensional scalar background mesh." << endl
				<< " - INPUTS: the list of the coordinates and their values. The extension of the file" << endl
				<< "   must be provided (or you can provide one without an extension)." << endl;

			/*Info << endl
				<< " - Alternatively, you can provide the list of the coordinates by " << endl
				<< "   creating a list of the points in system file." << endl;*/

			Info << endl
				<< " - OUTPUTS: a *.edge2d file format" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - [PointList] loadXYs(file name)" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [Point] createPoint(double, double)" << endl
				<< " - make(point list, name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			chai.add(chaiscript::user_type<Pnt2d>(), "pnt2d");
			chai.add(chaiscript::constructor<Pnt2d()>(), "pnt2d");
			chai.add(chaiscript::constructor<Pnt2d(const Pnt2d&)>(), "pnt2d");
			chai.add(chaiscript::constructor<Pnt2d(Pnt2d&&)>(), "pnt2d");
			chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<Pnt2d>>("std_vector_pnt2d"));
			chai.add(chaiscript::vector_conversion<std::vector<Pnt2d>>());

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);


			try
			{
				fileName theFileName(file::GetSystemFile("tnbToolScalarBackgroundMesh2d"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}