#include <Geo_AirfoilOffsets_MH102.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_File.hxx>
#include <OFstream.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Trsf2d.hxx>

namespace tnbLib
{

	static unsigned short verbose = 0;

	static std::string surface = "both";
	static double chordlen = 1.0;
	static Pnt2d origin(0.,0.);
	static double angle = 0;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setChordLen(double x)
	{
		chordlen = x;
		if (verbose)
		{
			Info << endl
				<< " - the chord length is set to: " << chordlen << endl;
		}
	}

	void setOrigin(const Pnt2d& pt)
	{
		origin = pt;
		if (verbose)
		{
			Info << endl
				<< " - the Origin is set to: " << origin << endl;
		}
	}

	void setAngle(double x)
	{
		angle = x;
		if (verbose)
		{
			Info << endl
				<< " - the Angle is set to: " << angle << endl;
		}
	}

	void setSurface(const std::string& name)
	{
		surface = name;
		if (verbose)
		{
			Info << endl
				<< " - the surface is set to: " << surface << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		file::CheckExtension(name);
		if (surface IS_EQUAL "upper")
		{
			auto pts = geoLib::airfoilOffsetsLib::upper::coords;
			for (auto& x : pts)
			{
				x.X() *= chordlen;
				x.Y() *= chordlen;
			}
			{
				gp_Trsf2d t;
				t.SetTranslation(Pnt2d(0, 0), origin);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}
			{
				gp_Trsf2d t;
				t.SetRotation(origin, angle);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}

			Entity2d_Polygon poly(std::move(pts), 0);
			file::SaveTo(poly, name + Entity2d_Polygon::extension, verbose);		
		}
		else if (surface IS_EQUAL "lower")
		{
			auto pts = geoLib::airfoilOffsetsLib::lower::coords;
			for (auto& x : pts)
			{
				x.X() *= chordlen;
				x.Y() *= chordlen;
			}
			{
				gp_Trsf2d t;
				t.SetTranslation(Pnt2d(0, 0), origin);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}
			{
				gp_Trsf2d t;
				t.SetRotation(origin, angle);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}

			Entity2d_Polygon poly(std::move(pts), 0);
			file::SaveTo(poly, name + Entity2d_Polygon::extension, verbose);
		}
		else if (surface IS_EQUAL "both")
		{
			auto pts = geoLib::airfoilOffsetsLib::coords;
			for (auto& x : pts)
			{
				x.X() *= chordlen;
				x.Y() *= chordlen;
			}
			{
				gp_Trsf2d t;
				t.SetTranslation(Pnt2d(0, 0), origin);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}
			{
				gp_Trsf2d t;
				t.SetRotation(origin, angle);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}

			Entity2d_Polygon poly(std::move(pts), 0);
			file::SaveTo(poly, name + Entity2d_Polygon::extension, verbose);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no surface has been selected." << endl
				<< abort(FatalError);
		}
	}

	void exportToPlt(const std::string& name)
	{
		OFstream myFile(name + ".plt");
		if (surface IS_EQUAL "upper")
		{
			auto pts = geoLib::airfoilOffsetsLib::upper::coords;
			for (auto& x : pts)
			{
				x.X() *= chordlen;
				x.Y() *= chordlen;
			}
			{
				gp_Trsf2d t;
				t.SetTranslation(Pnt2d(0, 0), origin);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}
			{
				gp_Trsf2d t;
				t.SetRotation(origin, angle);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}
			Entity2d_Polygon poly(std::move(pts), 0);
			poly.ExportToPlt(myFile);
		}
		else if (surface IS_EQUAL "lower")
		{
			auto pts = geoLib::airfoilOffsetsLib::lower::coords;
			for (auto& x : pts)
			{
				x.X() *= chordlen;
				x.Y() *= chordlen;
			}
			{
				gp_Trsf2d t;
				t.SetTranslation(Pnt2d(0, 0), origin);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}
			{
				gp_Trsf2d t;
				t.SetRotation(origin, angle);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}
			Entity2d_Polygon poly(std::move(pts), 0);
			poly.ExportToPlt(myFile);
		}
		else if (surface IS_EQUAL "both")
		{
			auto pts = geoLib::airfoilOffsetsLib::coords;
			for (auto& x : pts)
			{
				x.X() *= chordlen;
				x.Y() *= chordlen;
			}
			{
				gp_Trsf2d t;
				t.SetTranslation(Pnt2d(0, 0), origin);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}
			{
				gp_Trsf2d t;
				t.SetRotation(origin, angle);
				for (auto& x : pts)
				{
					x.Transform(t);
				}
			}
			Entity2d_Polygon poly(std::move(pts), 0);
			poly.ExportToPlt(myFile);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no surface has been selected." << endl
				<< abort(FatalError);
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {exportToPlt(name); }), "exportToPlt");

		//- settings
		mod->add(chaiscript::fun([](double x)->void {setChordLen(x); }), "setChord");
		mod->add(chaiscript::fun([](const Pnt2d& o)->void {setOrigin(o); }), "setOrigin");
		mod->add(chaiscript::fun([](double a)->void {setAngle(a); }), "SetAngle");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setSurface(name); }), "setSurface");
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

		// operators [2/10/2023 Payvand]
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
			Info << " This application is aimed to create a MH102 airfoil." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - exportToPlt(name) " << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setChord(x)" << endl
				<< " - setOrigin(Point)" << endl
				<< " - setAngle(x)" << endl
				<< " - setSurface(name);            - surface: upper, lower, both" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [Point] createPoint(x, y)" << endl

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
				fileName myFileName(file::GetSystemFile("tnbGeoAirfoilMH102"));
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