#include <Cad_Tools.hxx>
#include <LegModel_DispNo1.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <Ostream.hxx>
#include <OFstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	static const Standard_Real lowCriterion = 0.01;
	static const Standard_Real topCriterion = 1.0;
	static const Standard_Real minLength = 1.0;
	static const Standard_Real maxLength = 500.0;

	static const Standard_Integer minNbSections = 3;
	static const Standard_Integer maxNbSections = 100;

	static Standard_Boolean verbose = Standard_False;

	static word unit = "m";

	template<class T>
	inline Standard_Boolean isInside(T& x, const T low, const T up)
	{
		if (x < low)
		{
			x = low;
			return Standard_False;
		}
		if (x > up)
		{
			x = up;
			return Standard_False;
		}
		return Standard_True;
	}

	template<class T>
	void checkCriterion(T& x, const T low, const T up, const word& name)
	{
		auto x0 = x;
		if (NOT isInside(x, low, up))
		{
			Info << endl;
			Info << " Warning: the parameter's value is exceeded of the allowed span" << endl
				<< " - lower: " << low << endl
				<< " - upper: " << up << endl
				<< " - " << name << ": " << x0 << endl
				<< " - the parameter is set to: " << x << endl;
		}
	}

	typedef std::shared_ptr<LegModel_DispNo1> shipModel_t;
	typedef std::shared_ptr<LegModel_Parameter> param_t;
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void modelType(module_t& mod)
	{
		mod->add(chaiscript::user_type<shipModel_t>(), "shipModel");
	}

	void newModel(module_t& mod)
	{
		mod->add(chaiscript::fun([]() { auto t = std::make_shared<LegModel_DispNo1>(); return std::move(t); }), "newShip");
	}

	void setVerbose(const Standard_Boolean x)
	{
		verbose = x;
	}

	void setVerbose(module_t& mod)
	{
		mod->add(chaiscript::fun(static_cast<void(*)(const Standard_Boolean)>(&setVerbose)), "setVerbose");
	}

	void setUnit(const word& x)
	{
		unit = x;
	}

	void setUnit(module_t& mod)
	{
		mod->add(chaiscript::fun(static_cast<void(*)(const word&)>(&setUnit)), "setUnit");
	}

	void setLength(param_t& t, Standard_Real x)
	{
		checkCriterion(x, minLength, maxLength, t->Name());
		t->Value() = x;

		if (verbose)
		{
			Info << " '" << t->Name() << "' is set to: " << x << endl;
		}
	}

	void setParameter(param_t& t, Standard_Real x)
	{
		checkCriterion(x, lowCriterion, topCriterion, t->Name());
		t->Value() = x;

		if (verbose)
		{
			Info << " '" << t->Name() << "' is set to: " << x << endl;
		}
	}

	void setNbNetRows(Standard_Integer& t, Standard_Integer x)
	{
		static const word name = "nb. of rows";
		checkCriterion(x, minNbSections, maxNbSections, name);
		t = x;

		if (verbose)
		{
			Info << " '" << name << "' is set to: " << x << endl;
		}
	}

	void setNbNetColumns(Standard_Integer& t, Standard_Integer x)
	{
		static const word name = "nb. of columns";
		checkCriterion(x, minNbSections, maxNbSections, name);
		t = x;

		if (verbose)
		{
			Info << " '" << name << "' is set to: " << x << endl;
		}
	}

	void printParameter(const word& id, const param_t& t, Ostream& os)
	{
		os << id << t->Name() << ", value = " << t->Value() << endl;
	}

	void printParameterList(const shipModel_t& t, Ostream& os)
	{
		os << " parameter's List: " << endl;
		os << endl;
		os << " dimension's parameters: " << endl;
		printParameter(" 1. ", t->LengthOnDeck(), os);
		printParameter(" 2. ", t->BeamOnDeck(), os);
		printParameter(" 3. ", t->DepthAtBow(), os);
		printParameter(" 4. ", t->DepthAtTransom(), os);
		printParameter(" 5. ", t->TransomHeight(), os);

		os << " hull's parameters: " << endl;
		printParameter(" 6. ", t->MaxAreaLocation(), os);
		printParameter(" 7. ", t->FwdFullness(), os);
		printParameter(" 8. ", t->AftFullness(), os);

		os << endl;
		printParameter(" 9. ", t->AftSection().SideSlope(), os);
		printParameter(" 10. ", t->AftSection().Deadrise(), os);
		printParameter(" 11. ", t->AftSection().Tightness(), os);
		printParameter(" 12. ", t->AftSection().Flare(), os);

		os << endl;
		printParameter(" 13. ", t->MidSection().SideSlope(), os);
		printParameter(" 14. ", t->MidSection().Deadrise(), os);
		printParameter(" 15. ", t->MidSection().Tightness(), os);
		printParameter(" 16. ", t->MidSection().Flare(), os);

		os << endl;
		printParameter(" 17. ", t->FwdSection().SideSlope(), os);
		printParameter(" 18. ", t->FwdSection().Deadrise(), os);
		printParameter(" 19. ", t->FwdSection().Tightness(), os);
		printParameter(" 20. ", t->FwdSection().Flare(), os);

		os << endl;
		os << " transom's parameters: " << endl;
		printParameter(" 21. ", t->Rake(), os);
		printParameter(" 22. ", t->Width(), os);

		os << endl;
		os << " stem's parameters: " << endl;
		printParameter(" 23. ", t->BowRounding(), os);
		printParameter(" 24. ", t->StemRake(), os);
		printParameter(" 25. ", t->ForeFootShape(), os);

		os << endl;
		os << " keel's parameters: " << endl;
		printParameter(" 26. ", t->Position(), os);
		printParameter(" 27. ", t->RisePoint(), os);
		printParameter(" 28. ", t->RiseSlope(), os);
		printParameter(" 29. ", t->TransomSlope(), os);
	}


}

#define MODEL_t const shipModel_t& t
#define PARAM_v Standard_Real x
#define setLength_MODEL_t(par) [](MODEL_t, PARAM_v) -> void {Debug_Null_Pointer(t); setLength(t->par(),x);}
#define setParameter_MODEL_t(par) [](MODEL_t, PARAM_v) -> void {Debug_Null_Pointer(t); setParameter(t->par(),x);}
#define addFun_Length(par, name) mod->add(chaiscript::fun(setLength_MODEL_t(par)), name)

namespace tnbLib
{

	void setParameters(const module_t& mod)
	{
		addFun_Length(LengthOnDeck, "setLengthOnDeck");
		addFun_Length(BeamOnDeck, "setBeamOnDeck");
		addFun_Length(DepthAtBow, "setDepthAtBow");
		addFun_Length(DepthAtTransom, "setDepthAtTransom");
		addFun_Length(TransomHeight, "setTransomHeight");

		addFun_Length(MaxAreaLocation, "setMaxAreaLocation");
		addFun_Length(FwdFullness, "setFwdFullness");
		addFun_Length(AftFullness, "setAftFullness");

		addFun_Length(AftSection().SideSlope, "setAftSideSlope");
		addFun_Length(AftSection().Deadrise, "setAftDeadrise");
		addFun_Length(AftSection().Tightness, "setAftTightness");
		addFun_Length(AftSection().Flare, "setAftFlare");

		addFun_Length(MidSection().SideSlope, "setMidSideSlope");
		addFun_Length(MidSection().Deadrise, "setMidDeadrise");
		addFun_Length(MidSection().Tightness, "setMidTightness");
		addFun_Length(MidSection().Flare, "setMidFlare");

		addFun_Length(FwdSection().SideSlope, "setFwdSideSlope");
		addFun_Length(FwdSection().Deadrise, "setFwdDeadrise");
		addFun_Length(FwdSection().Tightness, "setFwdTightness");
		addFun_Length(FwdSection().Flare, "setFwdFlare");

		addFun_Length(Position, "setKeelPosition");
		addFun_Length(RisePoint, "setKeelRisePoint");
		addFun_Length(RiseSlope, "setKeelRiseSlope");
		addFun_Length(TransomSlope, "setKeelTransomSlope");

		addFun_Length(BowRounding, "setBowRounding");
		addFun_Length(StemRake, "setStemRake");
		addFun_Length(ForeFootShape, "setForeFootShape");

		addFun_Length(Rake, "setRake");
		addFun_Length(Width, "setWidth");

		mod->add(chaiscript::fun([](MODEL_t, Standard_Integer x)-> void {Debug_Null_Pointer(t); setNbNetRows(t->NbNetRows(), x); }), "setNbNetRows");
		mod->add(chaiscript::fun([](MODEL_t, Standard_Integer x)-> void {Debug_Null_Pointer(t); setNbNetColumns(t->NbNetColumns(), x); }), "setNbNetColumns");
	}

	void setPerform(const shipModel_t& t)
	{
		Debug_Null_Pointer(t);
		t->Perform();

		if (verbose)
		{
			Info << " the ship has been created, successfully!" << endl;
		}
	}
	void setPerform(module_t& mod)
	{
		mod->add(chaiscript::fun([](const shipModel_t& t)-> void {Debug_Null_Pointer(t); setPerform(t); }), "perform");
	}

	void checkPerform(const shipModel_t& t, const word& name)
	{
		if (NOT t->IsDone())
		{
			FatalErrorIn(name)
				<< "the algorithm is not performed yet!" << endl
				<< " - please, considering to call 'perform' method before this function" << endl
				<< abort(FatalError);
		}
	}

	void exportToIGES(const shipModel_t& t, const word& name)
	{
		checkPerform(t, "void exportToIGES(const shipModel_t& t, const word& name)");

		fileName myFileName(name);

		const auto& shape = t->Entity();
		Debug_If_Condition(shape.IsNull());

		Cad_Tools::ExportToIGES(unit, shape, myFileName);
	}

	void exportToSTEP(const shipModel_t& t, const word& name)
	{
		checkPerform(t, "void exportToSTEP(const shipModel_t& t, const word& name)");

		fileName myFileName(name);

		const auto& shape = t->Entity();
		Debug_If_Condition(shape.IsNull());

		Cad_Tools::ExportToSTEP(shape, myFileName);
	}

	void setIO(module_t& mod)
	{
		mod->add(chaiscript::fun([](const shipModel_t& t, const std::string& name)-> void {Debug_Null_Pointer(t); exportToIGES(t, name); }), "exportToIGES");
		mod->add(chaiscript::fun([](const shipModel_t& t, const std::string& name)-> void {Debug_Null_Pointer(t); exportToSTEP(t, name); }), "exportToSTEP");
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

#include <argList.hxx>
#include <Time.hxx>

using namespace tnbLib;

int main(int argc, char *argv[])
{
	FatalError.throwExceptions();

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

			modelType(mod);
			newModel(mod);

			setParameters(mod);
			setPerform(mod);
			setIO(mod);
			setVerbose(mod);
			setUnit(mod);

			chai.add(mod);

			fileName myFileName("legacy");

			try
			{
				chai.eval_file(myFileName);
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				std::cout << x.pretty_print();
				std::cout << '\n';
			}
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	return 0;
}