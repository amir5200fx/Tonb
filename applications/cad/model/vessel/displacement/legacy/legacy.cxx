#include <LegModel_DispNo1.hxx>

#include <Cad_Tools.hxx>
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

	const auto& getShip()
	{
		return myShip;
	}

	void setTransomHeight(const double x)
	{
		getShip()->TransomHeight()->Value() = std::max(x, minL);
	}

	void setDepthAtBow(const double x)
	{
		getShip()->DepthAtBow()->Value() = std::max(x, minL);
	}

	void setDepthAtTransom(const double x)
	{
		getShip()->DepthAtTransom()->Value() = std::max(x, minL);
	}

	void setBeamOnDeck(const double x)
	{
		getShip()->BeamOnDeck()->Value() = std::max(x, minL);
	}

	void setLengthOnDeck(const double x)
	{
		getShip()->LengthOnDeck()->Value() = std::max(x, minL);
	}

	void setNbNetRows(const int n)
	{
		getShip()->SetNbNetRows(std::max(n, 5));
	}

	void setNbNetColumns(const int n)
	{
		getShip()->SetNbNetColumns(std::max(n, 5));
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
	}

	void setFwdFullness(const hullPars& p, const double x)
	{
		p.FwdFullness()->Value() = NORMALIZED_VALUE(x);
	}

	void setAftFullness(const hullPars& p, const double x)
	{
		p.AftFullness()->Value() = NORMALIZED_VALUE(x);
	}

	void setRake(const transomPars& p, const double x)
	{
		p.Rake()->Value() = NORMALIZED_VALUE(x);
	}

	void setWidth(const transomPars& p, const double x)
	{
		p.Width()->Value() = x;
	}

	void setBowRounding(const stemPars& p, const double x)
	{
		p.BowRounding()->Value() = NORMALIZED_VALUE(x);
	}

	void setStemRake(const stemPars& p, const double x)
	{
		p.StemRake()->Value() = NORMALIZED_VALUE(x);
	}

	void setForeFootShape(const stemPars& p, const double x)
	{
		p.ForeFootShape()->Value() = NORMALIZED_VALUE(x);
	}

	void setLoc(const keelPars& p, const double x)
	{
		p.Position()->Value() = NORMALIZED_VALUE(x);
	}

	void setRisePoint(const keelPars& p, const double x)
	{
		p.RisePoint()->Value() = NORMALIZED_VALUE(x);
	}

	void setRiseSlope(const keelPars& p, const double x)
	{
		p.RiseSlope()->Value() = NORMALIZED_VALUE(x);
	}

	void setTransomSlope(const keelPars& p, const double x)
	{
		p.TransomSlope()->Value() = x;
	}

	void setTightness(const aftPars& p, const double x)
	{
		p.Tightness()->Value() = NORMALIZED_VALUE(x);
	}

	void setDeadrise(const aftPars& p, const double x)
	{
		p.Deadrise()->Value() = NORMALIZED_VALUE(x);
	}

	void setSideSlope(const aftPars& p, const double x)
	{
		p.SideSlope()->Value() = NORMALIZED_VALUE(x);
	}

	void setFlare(const aftPars& p, const double x)
	{
		p.Flare()->Value() = NORMALIZED_VALUE(x);
	}

	void setTightness(const midPars& p, const double x)
	{
		p.Tightness()->Value() = NORMALIZED_VALUE(x);
	}

	void setDeadrise(const midPars& p, const double x)
	{
		p.Deadrise()->Value() = NORMALIZED_VALUE(x);
	}

	void setSideSlope(const midPars& p, const double x)
	{
		p.SideSlope()->Value() = NORMALIZED_VALUE(x);
	}

	void setFlare(const midPars& p, const double x)
	{
		p.Flare()->Value() = NORMALIZED_VALUE(x);
	}

	void setTightness(const fwdPars& p, const double x)
	{
		p.Tightness()->Value() = NORMALIZED_VALUE(x);
	}

	void setDeadrise(const fwdPars& p, const double x)
	{
		p.Deadrise()->Value() = NORMALIZED_VALUE(x);
	}

	void setSideSlope(const fwdPars& p, const double x)
	{
		p.SideSlope()->Value() = NORMALIZED_VALUE(x);
	}

	void setFlare(const fwdPars& p, const double x)
	{
		p.Flare()->Value() = NORMALIZED_VALUE(x);
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

		mod->add(chaiscript::fun([](const hullPars& p)->const auto&{return p.AftSection(); }), "getAftSection");
		mod->add(chaiscript::fun([](const hullPars& p)->const auto&{return p.MidSection(); }), "getMidSection");
		mod->add(chaiscript::fun([](const hullPars& p)->const auto&{return p.FwdSection(); }), "getFwdSection");

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

		mod->add(chaiscript::fun([]()-> void {myShip->Perform(); }), "execute");

		mod->add(chaiscript::fun([](const std::string& name)-> void {exportIgesTo(name); }), "exportIGES");
		mod->add(chaiscript::fun([](const std::string& name)-> void {exportStepTo(name); }), "exportSTEP");
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

			setParameters(mod);
			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("modelDisplNo1");

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
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}