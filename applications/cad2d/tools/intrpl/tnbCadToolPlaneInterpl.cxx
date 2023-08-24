#include <Pln_CurveTools.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <IFstream.hxx>
#include <OSstream.hxx>
#include <token.hxx>
#include <word.hxx>

namespace tnbLib
{

	static Standard_Real myTol = 1.0E-6;
	
	static std::string saveExt = Pln_Edge::extension;
	static std::shared_ptr<Pln_Edge> myEdge;

	static unsigned short verbose(0);
	static bool exeTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	auto loadXYs(const std::string& name)
	{
		IFstream myfile(name);
		std::vector<Pnt2d> pnts;
		while (myfile.peek() NOT_EQUAL EOF)
		{
			double x, y;
			myfile >> x >> y;
			
			auto pt = Pnt2d(x, y);
			pnts.push_back(std::move(pt));
		}
		if (verbose)
		{
			Info << " - The list has successfully been loaded." << endl
				<< " - No. of points = " << pnts.size() << endl << endl;

			Info << token::BEGIN_LIST << endl;
			for (const auto& x : pnts)
			{
				Info << " - " << x << endl;
			}
			Info << token::END_LIST << endl;
		}
		return std::move(pnts);
	}

	void saveTo(const std::string& name)
	{
		if (NOT myEdge)
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been created!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myEdge, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT myEdge)
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been created!" << endl
				<< abort(FatalError);
		}

		if (NOT myEdge->Name().empty())
		{
			saveTo(myEdge->Name());
		}
		else
		{
			saveTo("curve");
		}
	}

	void makeEdge(const std::vector<Pnt2d>& qs, const std::string& name)
	{
		auto geom = Pln_CurveTools::Interpolation(qs, false, myTol);
		myEdge = Pln_Tools::MakeEdge(geom);

		myEdge->SetName(name);
		myEdge->Curve()->SetName(name);
	}

	void makeEdge(const std::vector<Pnt2d>& qs)
	{
		auto geom = Pln_CurveTools::Interpolation(qs, false, myTol);
		myEdge = Pln_Tools::MakeEdge(geom);
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
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
		mod->add(chaiscript::fun([](const std::string& name)-> auto {return loadXYs(name); }), "loadXYs");
		mod->add(chaiscript::fun([](const std::vector<Pnt2d>& qs)-> void {makeEdge(qs); }), "make");
		mod->add(chaiscript::fun([](const std::vector<Pnt2d>& qs, const std::string& name)-> void {makeEdge(qs, name); }), "make");
		mod->add(chaiscript::fun([](double x, double y)-> auto {return Pnt2d(x, y); }), "createPoint");
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
			Info << " This application is aimed to create a curve by interpolation." << endl
				<< " - INPUTS: the list of the coordinates. The extension of the file" << endl
				<< "   must be provided (or you can provide one without an extension)." << endl;

			Info << endl
				<< " - Alternatively, you can provide the list of the coordinates by " << endl
				<< "   creating a list of the points in system file." << endl;

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
				fileName theFileName(file::GetSystemFile("tnbCadToolPlaneInterpl"));

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