#include <Pln_Curve.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_CmptLib.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<Cad2d_Plane> plane_t;
	typedef std::shared_ptr<NumAlg_AdaptiveInteg_Info> info_t;

	static size_t verbose = 0;
	static plane_t myPlane;
	static auto myInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();

	void setDefaults()
	{
		myInfo->SetNbInitIterations(4);
		myInfo->SetTolerance(1.0e-4);
	}

	class SetDefaultInfo
	{
	public:
		SetDefaultInfo()
		{
			setDefaults();
		}
	};

	static const SetDefaultInfo myDefaultInfo;

	void loadPlane(const std::string& name)
	{
		if (verbose)
		{
			Info << " loading the plane..." << endl;
		}

		fileName fn(name);
		std::fstream file;
		file.open(fn, std::ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(file);

		ia >> myPlane;

		if (NOT myPlane)
		{
			FatalErrorIn(FunctionSIG)
				<< "null pointer has been detected!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " the plane is loaded from: " << fn << ", successfully!" << endl;
			Info << " plane's name: " << myPlane->Name() << endl;

			if (myPlane->InnerWires())
			{
				Info << endl;
				Info << " the plane has(have) " << myPlane->InnerWires()->size() << " inner wire(s)" << endl;
			}
		}
	}

	void checkPlane(const char* name)
	{
		if (NOT myPlane)
		{
			FatalErrorIn(name) << endl
				<< "no plane has been loaded!" << endl
				<< abort(FatalError);
		}
	}

	auto calcArea()
	{
		checkPlane(FunctionSIG);
		const auto& outer = myPlane->OuterWire();

		auto Area = Cad2d_CmptLib::Area(*outer, myInfo);
		if (myPlane->InnerWires())
		{
			const auto& inners = myPlane->InnerWires();
			auto iArea = 0;
			for (const auto& x : *inners)
			{
				iArea += Cad2d_CmptLib::Area(*x, myInfo);
			}
			Debug_If_Condition_Message(iArea > 0, "the inner area must be <0");

			if (verbose)
			{
				Info << " - the outer area: " << Area << endl;
				Info << " - the inner area: " << iArea << endl;
			}
			Area += iArea;
		}

		if (verbose)
		{
			Info << " - the area of the plane: " << Area << endl;
		}
		return Area;
	}

	auto calcMx(double y0)
	{
		checkPlane(FunctionSIG);
		const auto& outer = myPlane->OuterWire();

		auto Mx = Cad2d_CmptLib::Mx(*outer, y0, myInfo);
		if (myPlane->InnerWires())
		{
			const auto& inners = myPlane->InnerWires();
			auto iMx = 0;
			for (const auto& x : *inners)
			{
				iMx += Cad2d_CmptLib::Mx(*x, y0, myInfo);
			}
			Debug_If_Condition_Message(iMx > 0, "the inner area must be <0");

			if (verbose)
			{
				Info << " - the outer Mx: " << Mx << endl;
				Info << " - the inner Mx: " << iMx << endl;
			}
			Mx += iMx;
		}

		if (verbose)
		{
			Info << " - the Mx of the plane: " << Mx << endl;
		}
		return Mx;
	}

	auto calcMy(double x0)
	{
		checkPlane(FunctionSIG);
		const auto& outer = myPlane->OuterWire();

		auto My = Cad2d_CmptLib::My(*outer, x0, myInfo);
		if (myPlane->InnerWires())
		{
			const auto& inners = myPlane->InnerWires();
			auto iMy = 0;
			for (const auto& x : *inners)
			{
				iMy += Cad2d_CmptLib::My(*x, x0, myInfo);
			}
			Debug_If_Condition_Message(iMy > 0, "the inner area must be <0");

			if (verbose)
			{
				Info << " - the outer My: " << My << endl;
				Info << " - the inner My: " << iMy << endl;
			}
			My += iMy;
		}

		if (verbose)
		{
			Info << " - the My of the plane: " << My << endl;
		}
		return My;
	}

	auto calcIx(double y0)
	{
		checkPlane(FunctionSIG);
		const auto& outer = myPlane->OuterWire();

		auto Ix = Cad2d_CmptLib::Ix(*outer, y0, myInfo);
		if (myPlane->InnerWires())
		{
			const auto& inners = myPlane->InnerWires();
			auto iIx = 0;
			for (const auto& x : *inners)
			{
				iIx += Cad2d_CmptLib::Ix(*x, y0, myInfo);
			}
			Debug_If_Condition_Message(iIx > 0, "the inner area must be <0");

			if (verbose)
			{
				Info << " - the outer Ix: " << Ix << endl;
				Info << " - the inner Ix: " << iIx << endl;
			}
			Ix += iIx;
		}

		if (verbose)
		{
			Info << " - the Ix of the plane: " << Ix << endl;
		}
		return Ix;
	}

	auto calcIy(double x0)
	{
		checkPlane(FunctionSIG);
		const auto& outer = myPlane->OuterWire();

		auto Iy = Cad2d_CmptLib::Iy(*outer, x0, myInfo);
		if (myPlane->InnerWires())
		{
			const auto& inners = myPlane->InnerWires();
			auto iIy = 0;
			for (const auto& x : *inners)
			{
				iIy += Cad2d_CmptLib::Iy(*x, x0, myInfo);
			}
			Debug_If_Condition_Message(iIy > 0, "the inner area must be <0");

			if (verbose)
			{
				Info << " - the outer Iy: " << Iy << endl;
				Info << " - the inner Iy: " << iIy << endl;
			}
			Iy += iIy;
		}

		if (verbose)
		{
			Info << " - the Iy of the plane: " << Iy << endl;
		}
		return Iy;
	}

	Pnt2d calcCentre()
	{
		const auto area = calcArea();
		Pnt2d c(calcMy(0) / area, calcMx(0) / area);
		if (verbose)
		{
			Info << " centre of the plane: " << c << endl;
		}
		return std::move(c);
	}

}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const std::string& name)->void {loadPlane(name); }), "loadPlane");
		mod->add(chaiscript::fun([](int c)->void {verbose = c; }), "setVerbose");

		mod->add(chaiscript::fun([]()->auto {return calcArea(); }), "calcArea");
		mod->add(chaiscript::fun([](double x0)->auto {return calcMy(x0); }), "calcMy");
		mod->add(chaiscript::fun([](double y0)->auto {return calcMx(y0); }), "calcMx");
		mod->add(chaiscript::fun([](double x0)->auto {return calcIy(x0); }), "calcIy");
		mod->add(chaiscript::fun([](double y0)->auto {return calcIx(y0); }), "calcIx");

		mod->add(chaiscript::fun([]()->auto {return calcCentre(); }), "calcCentre");
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

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("TnbAreaTools");

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