#include <SectPx_ParRegistry.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_FieldFuns.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_GeoMap.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_Datums.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_FrameTuner.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <frameMaker.hxx>
#include <frameTuner.hxx>

namespace tnbLib
{

	static appl::tuner_t myTuner;

	std::map<word, appl::par_t> parMap;

	static bool verbose = false;

	const auto& getScatterReg()
	{
		return myTuner->ParRegistry()->Scatter();
	}

	appl::par_t findPar(const std::string& name)
	{
		auto iter = parMap.find(name);
		if (iter IS_EQUAL parMap.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "can't find the parameter: " << name << endl
				<< abort(FatalError);
			return nullptr;
		}
		return iter->second;
	}

	void setParameter(const std::string& name, double x)
	{
		auto par = findPar(name);
		if (par->IsFixed())
		{
			auto fixed = std::dynamic_pointer_cast<SectPx_FixedPar>(par);
			Debug_Null_Pointer(fixed);
			fixed->SetValue(x);
			return;
		}
		if (par->IsConstant())
		{
			auto c = std::dynamic_pointer_cast<SectPx_ConstPar>(par);
			Debug_Null_Pointer(c);
			c->SetValue(x);
			return;
		}
		FatalErrorIn(FunctionSIG)
			<< "unrecognized parameter" << endl
			<< abort(FatalError);
	}

	void setParameter(int i, double x)
	{
		auto parMaker = std::make_shared<maker::Parameter>(myTuner->ParRegistry());
		auto par = parMaker->SelectParameter(i);

		if (par->IsFixed())
		{
			auto fixed = std::dynamic_pointer_cast<SectPx_FixedPar>(par);
			Debug_Null_Pointer(fixed);
			fixed->SetValue(x);
			return;
		}
		if (par->IsConstant())
		{
			auto c = std::dynamic_pointer_cast<SectPx_ConstPar>(par);
			Debug_Null_Pointer(c);
			c->SetValue(x);
			return;
		}
		FatalErrorIn(FunctionSIG)
			<< "unrecognized parameter" << endl
			<< abort(FatalError);
	}

	void loadFrame(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);

		boost::archive::polymorphic_text_iarchive oa(f);

		oa >> myTuner;

		if (verbose)
		{
			Info << " the frame has been loaded successfully!" << endl;
		}

		const auto& scatter = getScatterReg();
		const auto& parameters = scatter->ScatterMap(sectPxLib::regObjType::parameter);

		if (verbose)
		{
			Info << " - nb. of parameters: " << parameters.size() << endl;
			Info << endl;
		}
		for (const auto& x : parameters)
		{
			auto par = std::dynamic_pointer_cast<SectPx_Par>(x.second.lock());
			if (NOT par)
			{
				FatalErrorIn(FunctionSIG)
					<< "parameter is null" << endl
					<< abort(FatalError);
			}
			if (par->IsFixed() OR par->IsConstant())
			{
				auto paired = std::make_pair(par->Name(), std::move(par));
				auto insert = parMap.insert(std::move(paired));
				if (NOT insert.second)
				{
					Info << " Warning! parameters with the same name has been detected!" << endl;
				}
			}
		}

		if (verbose)
		{
			Info << " - constant parameters: " << endl;
			for (const auto& x : parMap)
			{
				const auto& par = x.second;
				if (par->IsConstant())
				{
					Info << " - index: " << par->Index() << ", " << par->Name() << ": " << par->Value() << endl;
				}
			}
			Info << endl;
			Info << " - fixed parameters: " << endl;
			for (const auto& x : parMap)
			{
				const auto& par = x.second;
				if (par->IsFixed())
				{
					Info << " - index: " << par->Index() << ", " << par->Name() << ": " << par->Value() << endl;
				}
			}
		}
	}

	void drawPlt(const std::string& name)
	{
		fileName fn(name);
		OFstream f(fn);

		const auto& profiles = getScatterReg()->ScatterMap(SectPx_RegObjType::profile);
		for (const auto& x : profiles)
		{
			auto profile = std::dynamic_pointer_cast<SectPx_TopoProfile>(x.second.lock());
			Debug_Null_Pointer(profile);

			auto pnts = profile->RetrieveCoords();
			Io::ExportCurve(pnts, f);
		}
	}

	void printFixedParams()
	{
		const auto& params = getScatterReg()->ScatterMap(SectPx_RegObjType::parameter);
		Info << " fixed parameters: " << endl;
		for (const auto& x : params)
		{
			auto par = std::dynamic_pointer_cast<SectPx_FixedPar>(x.second.lock());
			if (par)
			{
				Info << " - " << "index: "
					<< par->Index() << ", "
					<< par->Name() << ", value: "
					<< par->Value() << endl;
			}
		}
	}

	void printPoints()
	{
		const auto& points = getScatterReg()->ScatterMap(SectPx_RegObjType::pnt);
		Info << " Points: " << endl;
		for (const auto& x : points)
		{
			auto pnt = std::dynamic_pointer_cast<SectPx_Pnt>(x.second.lock());
			if (pnt)
			{
				Info << " - " << "index: "
					<< pnt->Index() << ", "
					<< pnt->Name() << ", value: "
					<< pnt->Coord() << endl;
			}
		}
	}

	void printReg()
	{
		myTuner->PrintRegistry();
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myTuner;
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
		mod->add(chaiscript::fun([](const std::string& name, double x)-> void {setParameter(name, x); }), "setParameter");
		mod->add(chaiscript::fun([](int i, double x)-> void {setParameter(i, x); }), "setParameter");

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFrame(name); }), "loadFrame");

		mod->add(chaiscript::fun([](bool v)->void {verbose = v; }), "setVerbose");

		mod->add(chaiscript::fun([]()-> void {printReg(); }), "printRegistry");
		mod->add(chaiscript::fun([]()-> void {printFixedParams(); }), "printFixedParameters");
		mod->add(chaiscript::fun([]()-> void {printPoints(); }), "printPoints");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {drawPlt(name); }), "drawPlt");
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

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("frameReader");

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