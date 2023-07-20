#include <LegModel_DispNo1.hxx>

#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <algorithm>

#define NORMALIZED_VALUE(x) std::max(std::min(x , 1.0), 0.0)

#include <TopoDS_Face.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<LegModel_DispNo1_HullPatch> ship_t;

	static const auto myShip = std::make_shared<LegModel_DispNo1_HullPatch>();
	static const auto minL = (double)1.0e-4;
	static unsigned short verbose = 0;
	static bool exeTag = false;

	static std::shared_ptr<Cad_Shape> myShape;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	const auto& getShip()
	{
		return myShip;
	}

	void setTransomHeight(const double x)
	{
		getShip()->TransomHeight()->Value() = std::max(x, minL);
		if (verbose)
		{
			Info << endl
				<< " - the transom height is set to: " << getShip()->TransomHeight()->Value() << endl;
		}
	}

	void setDepthAtBow(const double x)
	{
		getShip()->DepthAtBow()->Value() = std::max(x, minL);
		if (verbose)
		{
			Info << endl
				<< " - the depth at bow is set to: " << getShip()->DepthAtBow()->Value() << endl;
		}
	}

	void setDepthAtTransom(const double x)
	{
		getShip()->DepthAtTransom()->Value() = std::max(x, minL);
		if (verbose)
		{
			Info << endl
				<< " - the depth at transom is set to: " << getShip()->DepthAtTransom()->Value() << endl;
		}
	}

	void setBeamOnDeck(const double x)
	{
		getShip()->BeamOnDeck()->Value() = std::max(x, minL);
		if (verbose)
		{
			Info << endl
				<< " - the beam at deck is set to: " << getShip()->BeamOnDeck()->Value() << endl;
		}
	}

	void setLengthOnDeck(const double x)
	{
		getShip()->LengthOnDeck()->Value() = std::max(x, minL);
		if (verbose)
		{
			Info << endl
				<< " - the length on deck is set to: " << getShip()->LengthOnDeck()->Value() << endl;
		}
	}

	void setNbNetRows(const int n)
	{
		getShip()->SetNbNetRows(std::max(n, 5));
		if (verbose)
		{
			Info << endl
				<< " - the no. of net rows is set to: " << getShip()->NbNetRows() << endl;
		}
	}

	void setNbNetColumns(const int n)
	{
		getShip()->SetNbNetColumns(std::max(n, 5));
		if (verbose)
		{
			Info << endl
				<< " - the no. of net columns is set to: " << getShip()->NbNetColumns() << endl;
		}
	}


	typedef LegModel_DispNo1_AftSectionParams aftPars;
	typedef LegModel_DispNo1_MidSectionParams midPars;
	typedef LegModel_DispNo1_FwdSectionParams fwdPars;
	typedef LegModel_DispNo1_KeelParams keelPars;
	typedef LegModel_DispNo1_StemParams stemPars;
	typedef LegModel_DispNo1_TransomParams transomPars;
	typedef LegModel_DispNo1_HullParams hullPars;

	void setMaxAreaLoc(const hullPars& p, const double x)
	{
		p.MaxAreaLocation()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the max. area location is set to: " << p.MaxAreaLocation()->Value() << endl;
		}
	}

	void setFwdFullness(const hullPars& p, const double x)
	{
		p.FwdFullness()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the Fwd. fullness is set to: " << p.FwdFullness()->Value() << endl;
		}
	}

	void setAftFullness(const hullPars& p, const double x)
	{
		p.AftFullness()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the Aft. fullness is set to: " << p.AftFullness()->Value() << endl;
		}
	}

	void setRake(const transomPars& p, const double x)
	{
		p.Rake()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the rake is set to: " << p.Rake()->Value() << endl;
		}
	}

	void setWidth(const transomPars& p, const double x)
	{
		p.Width()->Value() = x;
		if (verbose)
		{
			Info << endl
				<< " - the width is set to: " << p.Width()->Value() << endl;
		}
	}

	void setBowRounding(const stemPars& p, const double x)
	{
		p.BowRounding()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the bow rounding is set to: " << p.BowRounding()->Value() << endl;
		}
	}

	void setStemRake(const stemPars& p, const double x)
	{
		p.StemRake()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the stem rake is set to: " << p.StemRake()->Value() << endl;
		}
	}

	void setForeFootShape(const stemPars& p, const double x)
	{
		p.ForeFootShape()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the fore foot shape is set to: " << p.ForeFootShape()->Value() << endl;
		}
	}

	void setLoc(const keelPars& p, const double x)
	{
		p.Position()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the keel position is set to: " << p.Position()->Value() << endl;
		}
	}

	void setRisePoint(const keelPars& p, const double x)
	{
		p.RisePoint()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the keel rise position is set to: " << p.RisePoint()->Value() << endl;
		}
	}

	void setRiseSlope(const keelPars& p, const double x)
	{
		p.RiseSlope()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the rise slope of the keel is set to: " << p.RiseSlope()->Value() << endl;
		}
	}

	void setTransomSlope(const keelPars& p, const double x)
	{
		p.TransomSlope()->Value() = x;
		if (verbose)
		{
			Info << endl
				<< " - the transom slope of the keel is set to: " << p.TransomSlope()->Value() << endl;
		}
	}

	void setTightness(const aftPars& p, const double x)
	{
		p.Tightness()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the tightness of the aft is set to: " << p.Tightness()->Value() << endl;
		}
	}

	void setDeadrise(const aftPars& p, const double x)
	{
		p.Deadrise()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the deadrise of the aft is set to: " << p.Deadrise()->Value() << endl;
		}
	}

	void setSideSlope(const aftPars& p, const double x)
	{
		p.SideSlope()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the side slope of the aft is set to: " << p.SideSlope()->Value() << endl;
		}
	}

	void setFlare(const aftPars& p, const double x)
	{
		p.Flare()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the flare of the aft is set to: " << p.Flare()->Value() << endl;
		}
	}

	void setTightness(const midPars& p, const double x)
	{
		p.Tightness()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the tightness of the mid is set to: " << p.Tightness()->Value() << endl;
		}
	}

	void setDeadrise(const midPars& p, const double x)
	{
		p.Deadrise()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the deadrise of the mid is set to: " << p.Deadrise()->Value() << endl;
		}
	}

	void setSideSlope(const midPars& p, const double x)
	{
		p.SideSlope()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the side slope of the mid is set to: " << p.SideSlope()->Value() << endl;
		}
	}

	void setFlare(const midPars& p, const double x)
	{
		p.Flare()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the flare of the mid is set to: " << p.Flare()->Value() << endl;
		}
	}

	void setTightness(const fwdPars& p, const double x)
	{
		p.Tightness()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the tightness of the fwd is set to: " << p.Tightness()->Value() << endl;
		}
	}

	void setDeadrise(const fwdPars& p, const double x)
	{
		p.Deadrise()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the deadrise of the fwd is set to: " << p.Deadrise()->Value() << endl;
		}
	}

	void setSideSlope(const fwdPars& p, const double x)
	{
		p.SideSlope()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the side slope of the fwd is set to: " << p.SideSlope()->Value() << endl;
		}
	}

	void setFlare(const fwdPars& p, const double x)
	{
		p.Flare()->Value() = NORMALIZED_VALUE(x);
		if (verbose)
		{
			Info << endl
				<< " - the flare of the fwd is set to: " << p.Flare()->Value() << endl;
		}
	}

	void exportIgesTo(const std::string& name)
	{
		const auto& patch = myShip->Entity();
		if (patch.IsNull())
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		Cad_Tools::ExportToIGES("SI", patch, name);
	}

	void exportStepTo(const std::string& name)
	{
		const auto& patch = myShip->Entity();
		if (patch.IsNull())
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		Cad_Tools::ExportToSTEP(patch, name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed." << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(myShape, name + Cad_Shape::extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed." << endl
				<< abort(FatalError);
		}
		saveTo(myShape->Name());
	}

	void execute(const std::string& name)
	{
		myShip->Perform();

		myShape = std::make_shared<Cad_Shape>(0, name, myShip->Entity());
		TNB_PERFORMED_TAG;
	}

	void execute()
	{
		execute("myShip");
	}
}


#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setParameters(const module_t& mod)
	{

		mod->add(chaiscript::fun([](const double x)->void {setTransomHeight(x); }), "setTransomHeight");
		mod->add(chaiscript::fun([](const double x)->void {setDepthAtBow(x); }), "setDepthAtBow");
		mod->add(chaiscript::fun([](const double x)->void {setDepthAtTransom(x); }), "setDepthAtTransom");
		mod->add(chaiscript::fun([](const double x)->void {setLengthOnDeck(x); }), "setLengthOnDeck");
		mod->add(chaiscript::fun([](const double x)->void {setBeamOnDeck(x); }), "setBeamOnDeck");

		mod->add(chaiscript::fun([](const int n)->void {setNbNetRows(n); }), "setNbNetRows");
		mod->add(chaiscript::fun([](const int n)->void {setNbNetColumns(n); }), "setNbNetColumns");


		mod->add(chaiscript::fun([](const hullPars& p, const double x)-> void {setMaxAreaLoc(p, x); }), "setMaxAreaLocation");
		mod->add(chaiscript::fun([](const hullPars& p, const double x)-> void {setFwdFullness(p, x); }), "setFwdFullness");
		mod->add(chaiscript::fun([](const hullPars& p, const double x)-> void {setAftFullness(p, x); }), "setAftFullness");

		mod->add(chaiscript::fun([](const hullPars& p)->const auto& {return p.AftSection(); }), "getAftSection");
		mod->add(chaiscript::fun([](const hullPars& p)->const auto& {return p.MidSection(); }), "getMidSection");
		mod->add(chaiscript::fun([](const hullPars& p)->const auto& {return p.FwdSection(); }), "getFwdSection");

		mod->add(chaiscript::fun([](const transomPars& p, const double x)-> void {setRake(p, x); }), "setRake");
		mod->add(chaiscript::fun([](const transomPars& p, const double x)-> void {setWidth(p, x); }), "setWidth");

		mod->add(chaiscript::fun([](const stemPars& p, const double x)->void {setBowRounding(p, x); }), "setBowRounding");
		mod->add(chaiscript::fun([](const stemPars& p, const double x)->void {setStemRake(p, x); }), "setStemRake");
		mod->add(chaiscript::fun([](const stemPars& p, const double x)->void {setForeFootShape(p, x); }), "setForeFootShape");

		mod->add(chaiscript::fun([](const keelPars& p, const double x)->void {setLoc(p, x); }), "setLocation");
		mod->add(chaiscript::fun([](const keelPars& p, const double x)->void {setRisePoint(p, x); }), "setRisePoint");
		mod->add(chaiscript::fun([](const keelPars& p, const double x)->void {setRiseSlope(p, x); }), "setRiseSlope");
		mod->add(chaiscript::fun([](const keelPars& p, const double x)->void {setTransomSlope(p, x); }), "setTransomSlope");

		mod->add(chaiscript::fun([](const aftPars& p, const double x)->void {setTightness(p, x); }), "setTightness");
		mod->add(chaiscript::fun([](const aftPars& p, const double x)->void {setDeadrise(p, x); }), "setDeadrise");
		mod->add(chaiscript::fun([](const aftPars& p, const double x)->void {setSideSlope(p, x); }), "setSideSlope");
		mod->add(chaiscript::fun([](const aftPars& p, const double x)->void {setFlare(p, x); }), "setFlare");

		mod->add(chaiscript::fun([](const midPars& p, const double x)->void {setTightness(p, x); }), "setTightness");
		mod->add(chaiscript::fun([](const midPars& p, const double x)->void {setDeadrise(p, x); }), "setDeadrise");
		mod->add(chaiscript::fun([](const midPars& p, const double x)->void {setSideSlope(p, x); }), "setSideSlope");
		mod->add(chaiscript::fun([](const midPars& p, const double x)->void {setFlare(p, x); }), "setFlare");

		mod->add(chaiscript::fun([](const fwdPars& p, const double x)->void {setTightness(p, x); }), "setTightness");
		mod->add(chaiscript::fun([](const fwdPars& p, const double x)->void {setDeadrise(p, x); }), "setDeadrise");
		mod->add(chaiscript::fun([](const fwdPars& p, const double x)->void {setSideSlope(p, x); }), "setSideSlope");
		mod->add(chaiscript::fun([](const fwdPars& p, const double x)->void {setFlare(p, x); }), "setFlare");
	}

	void setFunctions(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()-> const auto& {return myShip->AftSection(); }), "getAftPars");
		mod->add(chaiscript::fun([]()-> const auto& {return myShip->MidSection(); }), "getMidPars");
		mod->add(chaiscript::fun([]()-> const auto& {return myShip->FwdSection(); }), "getFwdPars");

		mod->add(chaiscript::fun([]()-> const hullPars& {return myShip->Parameters(); }), "getHullPars");
		mod->add(chaiscript::fun([]()-> const stemPars& {return myShip->Parameters(); }), "getStemPars");
		mod->add(chaiscript::fun([]()-> const keelPars& {return myShip->Parameters(); }), "getKeelPars");
		mod->add(chaiscript::fun([]()-> const transomPars& {return myShip->Parameters(); }), "getTransomPars");

		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		mod->add(chaiscript::fun([](const std::string& name)-> void {exportIgesTo(name); }), "exportIGES");
		mod->add(chaiscript::fun([](const std::string& name)-> void {exportStepTo(name); }), "exportSTEP");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
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
			Info << " This application is aimed to create a legacy displacement vessel." << endl << endl;
			
			Info << " # Function list: " << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name [optional])" << endl
				<< " - exportAsIGES(name [optional])" << endl
				<< " - exportAsSTEP(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setTransomHeight(x)" << endl
				<< " - setDepthAtBow(x)" << endl
				<< " - setDepthAtTransom(x)" << endl
				<< " - setLengthOnDeck(x)" << endl
				<< " - setBeamOnDeck(x)" << endl << endl

				<< " - setNbNetRows(n)" << endl
				<< " - setNbNetColumns(n)" << endl << endl

				<< " - [hullPars] getHullPars()" << endl
				<< " - [stemPars] getStemPars()" << endl
				<< " - [keelPars] getKeelPars()" << endl
				<< " - [transomPars] getTransomPars()" << endl << endl

				<< " - [aftPars] (hullPars).getAftSection()" << endl
				<< " - [midPars] (hullPars).getMidSection()" << endl
				<< " - [fwdPars] (hullPars).getFwdSection()" << endl << endl

				<< " - [Aft] getAftSection()" << endl
				<< " - [Mid] getMidSection()" << endl
				<< " - [Fwd] getFwdSection()" << endl << endl

				<< " - (hullPars).setMaxAreaLocation(x)" << endl
				<< " - (hullPars).setFwdFullness(x)" << endl
				<< " - (hullPars).setAftFullness(x)" << endl << endl

				<< " - (transomPars).setRake(x)" << endl
				<< " - (transomPars).setWidth(x)" << endl << endl

				<< " - (stemPars).setBowRounding(x)" << endl
				<< " - (stemPars).setStemRake(x)" << endl
				<< " - (stemPars).setForeFootShape(x)" << endl << endl

				<< " - (keelPars).setLocation(x)" << endl
				<< " - (keelPars).setRisePoint(x)" << endl
				<< " - (keelPars).setRiseSlope(x)" << endl
				<< " - (keelPars).setTransomSlope(x)" << endl << endl

				<< " - (aftPars).setTightness(x)" << endl
				<< " - (aftPars).setDeadrise(x)" << endl
				<< " - (aftPars).setSideSlope(x)" << endl
				<< " - (aftPars).setFlare(x)" << endl << endl

				<< " - (midPars).setTightness(x)" << endl
				<< " - (midPars).setDeadrise(x)" << endl
				<< " - (midPars).setSideSlope(x)" << endl
				<< " - (midPars).setFlare(x)" << endl << endl

				<< " - (fwdPars).setTightness(x)" << endl
				<< " - (fwdPars).setDeadrise(x)" << endl
				<< " - (fwdPars).setSideSlope(x)" << endl
				<< " - (fwdPars).setFlare(x)" << endl << endl

				<< " - setVerbose(n); n = 0, 1" << endl << endl

				<< " # Operators: " << endl << endl

				<< " - execute(name[optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setParameters(mod);
			setFunctions(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbCadModelDisplVesselLeg"));
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