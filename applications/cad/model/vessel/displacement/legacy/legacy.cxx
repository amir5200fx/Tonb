#include <LegModel_DispNo1.hxx>

#include <algorithm>

#define NORMALIZED_VALUE(x) std::max(std::min(x , 1.0), 0.0)

namespace tnbLib
{

	typedef std::shared_ptr<LegModel_DispNo1> ship_t;

	static const auto myShip = std::make_shared<LegModel_DispNo1>();
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


	typedef std::shared_ptr<LegModel_DispNo1_AftSectionParams> aftPars_t;
	typedef std::shared_ptr<LegModel_DispNo1_MidSectionParams> midPars_t;
	typedef std::shared_ptr<LegModel_DispNo1_FwdSectionParams> fwdPars_t;
	typedef std::shared_ptr<LegModel_DispNo1_KeelParams> keelPars_t;
	typedef std::shared_ptr<LegModel_DispNo1_StemParams> stemPars_t;
	typedef std::shared_ptr<LegModel_DispNo1_TransomParams> transomPars_t;
	typedef std::shared_ptr<LegModel_DispNo1_HullParams> hullPars_t;

	void setMaxAreaLoc(const hullPars_t& p, const double x)
	{
		p->MaxAreaLocation()->Value() = NORMALIZED_VALUE(x);
	}

	void setFwdFullness(const hullPars_t& p, const double x)
	{
		p->FwdFullness()->Value() = NORMALIZED_VALUE(x);
	}

	void setAftFullness(const hullPars_t& p, const double x)
	{
		p->AftFullness()->Value() = NORMALIZED_VALUE(x);
	}

	void setRake(const transomPars_t& p, const double x)
	{
		p->Rake()->Value() = NORMALIZED_VALUE(x);
	}

	void setWidth(const transomPars_t& p, const double x)
	{
		p->Width()->Value() = x;
	}

	void setBowRounding(const stemPars_t& p, const double x)
	{
		p->BowRounding()->Value() = NORMALIZED_VALUE(x);
	}

	void setStemRake(const stemPars_t& p, const double x)
	{
		p->StemRake()->Value() = NORMALIZED_VALUE(x);
	}

	void setForeFootShape(const stemPars_t& p, const double x)
	{
		p->ForeFootShape()->Value() = NORMALIZED_VALUE(x);
	}

	void setLoc(const keelPars_t& p, const double x)
	{
		p->Position()->Value() = NORMALIZED_VALUE(x);
	}

	void setRisePoint(const keelPars_t& p, const double x)
	{
		p->RisePoint()->Value() = NORMALIZED_VALUE(x);
	}

	void setRiseSlope(const keelPars_t& p, const double x)
	{
		p->RiseSlope()->Value() = NORMALIZED_VALUE(x);
	}

	void setTransomSlope(const keelPars_t& p, const double x)
	{
		p->TransomSlope()->Value() = x;
	}

	void setTightness(const aftPars_t& p, const double x)
	{
		p->Tightness()->Value() = NORMALIZED_VALUE(x);
	}

	void setDeadrise(const aftPars_t& p, const double x)
	{
		p->Deadrise()->Value() = NORMALIZED_VALUE(x);
	}

	void setSideSlope(const aftPars_t& p, const double x)
	{
		p->SideSlope()->Value() = NORMALIZED_VALUE(x);
	}

	void setFlare(const aftPars_t& p, const double x)
	{
		p->Flare()->Value() = NORMALIZED_VALUE(x);
	}

	void setTightness(const midPars_t& p, const double x)
	{
		p->Tightness()->Value() = NORMALIZED_VALUE(x);
	}

	void setDeadrise(const midPars_t& p, const double x)
	{
		p->Deadrise()->Value() = NORMALIZED_VALUE(x);
	}

	void setSideSlope(const midPars_t& p, const double x)
	{
		p->SideSlope()->Value() = NORMALIZED_VALUE(x);
	}

	void setFlare(const midPars_t& p, const double x)
	{
		p->Flare()->Value() = NORMALIZED_VALUE(x);
	}

	void setTightness(const fwdPars_t& p, const double x)
	{
		p->Tightness()->Value() = NORMALIZED_VALUE(x);
	}

	void setDeadrise(const fwdPars_t& p, const double x)
	{
		p->Deadrise()->Value() = NORMALIZED_VALUE(x);
	}

	void setSideSlope(const fwdPars_t& p, const double x)
	{
		p->SideSlope()->Value() = NORMALIZED_VALUE(x);
	}

	void setFlare(const fwdPars_t& p, const double x)
	{
		p->Flare()->Value() = NORMALIZED_VALUE(x);
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


		mod->add(chaiscript::fun([](const hullPars_t& p, const double x)-> void {setMaxAreaLoc(p, x); }), "setMaxAreaLocation");
		mod->add(chaiscript::fun([](const hullPars_t& p, const double x)-> void {setFwdFullness(p, x); }), "setFwdFullness");
		mod->add(chaiscript::fun([](const hullPars_t& p, const double x)-> void {setAftFullness(p, x); }), "setAftFullness");

		mod->add(chaiscript::fun([](const hullPars_t& p)->const auto&{return p->AftSection(); }), "getAftSection");
		mod->add(chaiscript::fun([](const hullPars_t& p)->const auto&{return p->MidSection(); }), "getMidSection");
		mod->add(chaiscript::fun([](const hullPars_t& p)->const auto&{return p->FwdSection(); }), "getFwdSection");

		mod->add(chaiscript::fun([](const transomPars_t& p, const double x)-> void {setRake(p, x); }), "setRake");
		mod->add(chaiscript::fun([](const transomPars_t& p, const double x)-> void {setWidth(p, x); }), "setWidth");

		mod->add(chaiscript::fun([](const stemPars_t& p, const double x)->void {setBowRounding(p, x); }), "setBowRounding");
		mod->add(chaiscript::fun([](const stemPars_t& p, const double x)->void {setStemRake(p, x); }), "setStemRake");
		mod->add(chaiscript::fun([](const stemPars_t& p, const double x)->void {setForeFootShape(p, x); }), "setForeFootShape");

		mod->add(chaiscript::fun([](const keelPars_t& p, const double x)->void {setLoc(p, x); }), "setLocation");
		mod->add(chaiscript::fun([](const keelPars_t& p, const double x)->void {setRisePoint(p, x); }), "setRisePoint");
		mod->add(chaiscript::fun([](const keelPars_t& p, const double x)->void {setRiseSlope(p, x); }), "setRiseSlope");
		mod->add(chaiscript::fun([](const keelPars_t& p, const double x)->void {setTransomSlope(p, x); }), "setTransomSlope");

		mod->add(chaiscript::fun([](const aftPars_t& p, const double x)->void {setTightness(p, x); }), "setTightness");
		mod->add(chaiscript::fun([](const aftPars_t& p, const double x)->void {setDeadrise(p, x); }), "setDeadrise");
		mod->add(chaiscript::fun([](const aftPars_t& p, const double x)->void {setSideSlope(p, x); }), "setSideSlope");
		mod->add(chaiscript::fun([](const aftPars_t& p, const double x)->void {setFlare(p, x); }), "setFlare");

		mod->add(chaiscript::fun([](const midPars_t& p, const double x)->void {setTightness(p, x); }), "setTightness");
		mod->add(chaiscript::fun([](const midPars_t& p, const double x)->void {setDeadrise(p, x); }), "setDeadrise");
		mod->add(chaiscript::fun([](const midPars_t& p, const double x)->void {setSideSlope(p, x); }), "setSideSlope");
		mod->add(chaiscript::fun([](const midPars_t& p, const double x)->void {setFlare(p, x); }), "setFlare");

		mod->add(chaiscript::fun([](const fwdPars_t& p, const double x)->void {setTightness(p, x); }), "setTightness");
		mod->add(chaiscript::fun([](const fwdPars_t& p, const double x)->void {setDeadrise(p, x); }), "setDeadrise");
		mod->add(chaiscript::fun([](const fwdPars_t& p, const double x)->void {setSideSlope(p, x); }), "setSideSlope");
		mod->add(chaiscript::fun([](const fwdPars_t& p, const double x)->void {setFlare(p, x); }), "setFlare");
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

			chai.add(mod);

			fileName myFileName("nozzleMaker");

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