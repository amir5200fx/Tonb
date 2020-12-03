#include <Entity2d_Polygon.hxx>
#include <Pln_CurveTools.hxx>
#include <LegModel_NozzleType1.hxx>
#include <TecPlot.hxx>

#include <algorithm>

namespace tnbLib
{

	typedef std::shared_ptr<LegModel_NozzleType1> nozzle_t;
	typedef std::shared_ptr<nozzle::NozzleType1_InletProfileParams> inletProfile_t;
	typedef std::shared_ptr<nozzle::NozzleType1_OutletProfileParams> outletProfile_t;

	//static const auto myNozzle = std::make_shared<LegModel_NozzleType1>();
	nozzle_t myNozzle;

	const auto& getNozzle()
	{
		return myNozzle;
	}

	const auto& getInlet()
	{
		return getNozzle()->InletProfile();
	}

	const auto& getOutlet()
	{
		return getNozzle()->OutletProfile();
	}

	const auto& getDimension()
	{
		return getNozzle();
	}

	/* Dimension parameters */

	void setOverallLength(const double x)
	{
		getDimension()->OverallLength()->Value() = x;
	}

	void setThroat(const double x)
	{
		getDimension()->Throat()->Value() = x;
	}

	void setRadiusAtInlet(const double x)
	{
		getDimension()->RadiusAtInlet()->Value() = x;
	}

	void setRadiusAtOutlet(const double x)
	{
		getDimension()->RadiusAtOutlet()->Value() = x;
	}

	void setRadiusAtThroat(const double x)
	{
		getDimension()->RadiusAtThroat()->Value() = x;
	}

	/*inlet parameters*/

	void setInflection(const inletProfile_t& t, const double x)
	{
		t->Inflection()->Value() = x;
	}

	void setRadiusAtInflection(const inletProfile_t& t, const double x)
	{
		t->RadiusAtInflection()->Value() = x;
	}

	void setOffsetAtThroat(const inletProfile_t& t, const double x)
	{
		t->OffsetAtThroat()->Value() = x;
	}

	void setOffsetAtInlet(const inletProfile_t& t, const double x)
	{
		t->OffsetAtInlet()->Value() = x;
	}

	void setRounding1(const inletProfile_t& t, const double x)
	{
		t->Rounding1()->Value() = x;
	}

	void setRounding2(const inletProfile_t& t, const double x)
	{
		t->Rounding2()->Value() = x;
	}

	void SetRoundingWeight1(const inletProfile_t& t, const double x)
	{
		t->RoundingWeight1()->Value() = x;
	}

	void setRoundingWeight2(const inletProfile_t& t, const double x)
	{
		t->RoundingWeight2()->Value() = x;
	}

	/*outlet parameters*/

	void setInflection(const outletProfile_t& t, const double x)
	{
		t->Inflection()->Value() = x;
	}

	void setRadiusAtInflection(const outletProfile_t& t, const double x)
	{
		t->RadiusAtInflection()->Value() = x;
	}

	void setOffsetAtThroat(const outletProfile_t& t, const double x)
	{
		t->OffsetAtThroat()->Value() = x;
	}

	void setOffsetAtOutlet(const outletProfile_t& t, const double x)
	{
		t->OffsetAtOutlet()->Value() = x;
	}

	void setTangentAtOutlet(const outletProfile_t& t, const double x)
	{
		t->TangentAtOutlet()->Value() = x;
	}

	void setRounding1(const outletProfile_t& t, const double x)
	{
		t->Rounding1()->Value() = x;
	}

	void setRounding2(const outletProfile_t& t, const double x)
	{
		t->Rounding2()->Value() = x;
	}

	void SetRoundingWeight1(const outletProfile_t& t, const double x)
	{
		t->RoundingWeight1()->Value() = x;
	}

	void setRoundingWeight2(const outletProfile_t& t, const double x)
	{
		t->RoundingWeight2()->Value() = x;
	}

	void exportToPlt(const fileName& name, int n)
	{
		OFstream f(name);
		n = std::max(n, 5);
		const auto& geom = getNozzle()->Profile();
		Pln_CurveTools::ExportToPlt(geom, f, n);
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
		mod->add(chaiscript::fun([](const double x)->void {setOverallLength(x); }), "setOverallLength");
		mod->add(chaiscript::fun([](const double x)->void {setThroat(x); }), "setThroat");
		mod->add(chaiscript::fun([](const double x)->void {setRadiusAtInlet(x); }), "setRadiusAtInlet");
		mod->add(chaiscript::fun([](const double x)->void {setRadiusAtOutlet(x); }), "setRadiusAtOutlet");
		mod->add(chaiscript::fun([](const double x)->void {setRadiusAtThroat(x); }), "setRadiusAtThroat");

		mod->add(chaiscript::fun([]()-> const auto& {return getInlet(); }), "getInlet");
		mod->add(chaiscript::fun([]()-> const auto& {return getOutlet(); }), "getOutlet");

		mod->add(chaiscript::fun([](const inletProfile_t& t, const double x)->void {setInflection(t, x); }), "setInflection");
		mod->add(chaiscript::fun([](const inletProfile_t& t, const double x)->void {setRadiusAtInflection(t, x); }), "setRadiusAtInflection");
		mod->add(chaiscript::fun([](const inletProfile_t& t, const double x)->void {setOffsetAtThroat(t, x); }), "setOffsetAtThroat");
		mod->add(chaiscript::fun([](const inletProfile_t& t, const double x)->void {setOffsetAtInlet(t, x); }), "setOffsetAtInlet");
		mod->add(chaiscript::fun([](const inletProfile_t& t, const double x)->void {setRounding1(t, x); }), "setRounding1");
		mod->add(chaiscript::fun([](const inletProfile_t& t, const double x)->void {setRounding2(t, x); }), "setRounding2");
		mod->add(chaiscript::fun([](const inletProfile_t& t, const double x)->void {SetRoundingWeight1(t, x); }), "SetRoundingWeight1");
		mod->add(chaiscript::fun([](const inletProfile_t& t, const double x)->void {setRoundingWeight2(t, x); }), "setRoundingWeight2");

		mod->add(chaiscript::fun([](const outletProfile_t& t, const double x)->void {setInflection(t, x); }), "setInflection");
		mod->add(chaiscript::fun([](const outletProfile_t& t, const double x)->void {setRadiusAtInflection(t, x); }), "setRadiusAtInflection");
		mod->add(chaiscript::fun([](const outletProfile_t& t, const double x)->void {setOffsetAtThroat(t, x); }), "setOffsetAtThroat");
		mod->add(chaiscript::fun([](const outletProfile_t& t, const double x)->void {setOffsetAtOutlet(t, x); }), "setOffsetAtOutlet");
		mod->add(chaiscript::fun([](const outletProfile_t& t, const double x)->void {setTangentAtOutlet(t, x); }), "setTangentAtOutlet");
		mod->add(chaiscript::fun([](const outletProfile_t& t, const double x)->void {setRounding1(t, x); }), "setRounding1");
		mod->add(chaiscript::fun([](const outletProfile_t& t, const double x)->void {setRounding2(t, x); }), "setRounding2");
		mod->add(chaiscript::fun([](const outletProfile_t& t, const double x)->void {SetRoundingWeight1(t, x); }), "SetRoundingWeight1");
		mod->add(chaiscript::fun([](const outletProfile_t& t, const double x)->void {setRoundingWeight2(t, x); }), "setRoundingWeight2");

		mod->add(chaiscript::fun([]()->void {getNozzle()->Perform(); }), "perform");
		mod->add(chaiscript::fun([](const std::string& name, const int n)->void {exportToPlt(name, n); }), "exportToPlt");
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
	myNozzle = std::make_shared<LegModel_NozzleType1>();
	/*myNozzle->Perform();
	exportToPlt("myNozzle", 50);
	return 0;*/

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