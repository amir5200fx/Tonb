#include <Geo_Tools.hxx>
//#include <Marine_System.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_CmptLib2.hxx>
#include <HydStatic_CrossCurves.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>
#include <HydStatic_Spacing.hxx>
#include <HydStatic_CustomSpacing.hxx>
#include <HydStatic_UniformSpacing.hxx>
#include <HydStatic_HeelSpacing_Arbt.hxx>
#include <HydStatic_HeelSpacing_Asym.hxx>
#include <HydStatic_HeelSpacing_Stb.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <algorithm>
#include <vector>

namespace tnbLib
{
	static const unsigned int DEFAULT_NB_WATERS = 5;
	static const unsigned int DEFAULT_NB_HEELS = 5;
	static const auto crossCurves = std::make_shared<HydStatic_CrossCurves>();
	static int nbWaters = 10;
	static const std::vector<double> DEFAULT_HEELS = { 0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90 };
	static bool bodyLoad_flag = false;
	static bool execute_flag = false;

	typedef std::shared_ptr<Marine_Body> body_t;
	typedef std::shared_ptr<marineLib::Body_Tank> tank_t;
	typedef std::shared_ptr<marineLib::Body_Displacer> displacer_t;
	typedef std::shared_ptr<HydStatic_HeelSpacing> spacing_t;

	spacing_t myHeels;

	//- global functions

	const auto& getCrossCurves()
	{
		return crossCurves;
	}

	void setVolumeTol(double x)
	{
		crossCurves->SetVolumeCoeff(x);
	}

	void SetNbWaters(unsigned int n)
	{
		nbWaters = std::max(DEFAULT_NB_WATERS, n);
	}

	void setStbHeels(const std::vector<double>& h)
	{
		if (h.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the list is empty" << endl
				<< abort(FatalError);
		}
		auto iter = h.begin();
		auto x0 = *iter;
		iter++;
		while (iter NOT_EQUAL h.end())
		{
			auto x1 = *iter;
			if (x1 <= x0)
			{
				FatalErrorIn(FunctionSIG)
					<< "heel list is not sorted!" << endl
					<< abort(FatalError);
			}
			x0 = x1;
			iter++;
		}
		
		auto heels = std::make_shared<hydStcLib::HeelSpacing_Stb>();
		heels->Perform(h);
		myHeels = std::move(heels);
	}

	void setStbHeels(unsigned int n)
	{
		n = std::max(n, DEFAULT_NB_HEELS);

		auto heels = std::make_shared<hydStcLib::HeelSpacing_Stb>();
		heels->Perform(n);
		myHeels = std::move(heels);
	}

	void setAsymmHeels(const std::vector<double>& h)
	{
		if (h.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the list is empty" << endl
				<< abort(FatalError);
		}
		auto iter = h.begin();
		auto x0 = *iter;
		iter++;
		while (iter NOT_EQUAL h.end())
		{
			auto x1 = *iter;
			if (x1 <= x0)
			{
				FatalErrorIn(FunctionSIG)
					<< "heel list is not sorted!" << endl
					<< abort(FatalError);
			}
			x0 = x1;
			iter++;
		}
		auto heels = std::make_shared<hydStcLib::HeelSpacing_Asym>();
		heels->Perform(h);
		myHeels = std::move(heels);
	}

	void setAsymmHeels(unsigned int n)
	{
		n = std::max(n, DEFAULT_NB_HEELS);

		auto heels = std::make_shared<hydStcLib::HeelSpacing_Asym>();
		heels->Perform(n);
		myHeels = std::move(heels);
	}

	void setArbtHeels(const std::vector<double>& h)
	{
		if (h.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the list is empty" << endl
				<< abort(FatalError);
		}
		auto iter = h.begin();
		auto x0 = *iter;
		iter++;
		while (iter NOT_EQUAL h.end())
		{
			auto x1 = *iter;
			if (x1 <= x0)
			{
				FatalErrorIn(FunctionSIG)
					<< "heel list is not sorted!" << endl
					<< abort(FatalError);
			}
			x0 = x1;
			iter++;
		}
		auto spacing = std::make_shared<HydStatic_CustomSpacing>(std::move(h));
		auto heels = std::make_shared<hydStcLib::HeelSpacing_Arbt>(std::move(spacing));
		myHeels = std::move(heels);
	}

	void setHeels()
	{
		std::vector<double> heels;
		heels.reserve(DEFAULT_HEELS.size());
		for (auto h : DEFAULT_HEELS)
		{
			heels.push_back(Geo_Tools::DegToRadian(h));
		}
		setStbHeels(heels);
	}

	void setArbtHeels(double l, double u, unsigned int n)
	{
		if (u <= l)
		{
			std::swap(l, u);
		}

		auto h = std::make_shared<HydStatic_UniformSpacing>(n);
		h->SetLower(Geo_Tools::DegToRadian(l));
		h->SetUpper(Geo_Tools::DegToRadian(u));
		myHeels = std::make_shared<hydStcLib::HeelSpacing_Arbt>(std::move(h));
	}

	auto createDomain_tank(const tank_t& b)
	{
		auto domain = Marine_WaterLib::Domain(*b);
		return std::move(domain);
	}

	auto createDomain_displacer(const displacer_t& b)
	{
		auto domain = Marine_WaterLib::Domain(*b);
		return std::move(domain);
	}

	std::shared_ptr<Marine_Domain> createDomain(const body_t& b)
	{
		if (b->IsHull())
		{
			auto body = std::dynamic_pointer_cast<marineLib::Body_Displacer>(b);
			if (body)
			{
				auto t = createDomain_displacer(body);
				return std::move(t);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid body" << endl
					<< abort(FatalError);
				return nullptr;
			}
		}
		else if (b->IsTank())
		{
			auto body = std::dynamic_pointer_cast<marineLib::Body_Tank>(b);
			if (body)
			{
				auto t = createDomain_tank(body);
				return std::move(t);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid body" << endl
					<< abort(FatalError);
				return nullptr;
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid body" << endl
				<< abort(FatalError);
			return nullptr;
		}
	}

	void execute()
	{
		if (NOT bodyLoad_flag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been loaded!" << endl
				<< abort(FatalError);
		}
		if (NOT myHeels)
		{
			setHeels();
		}

		getCrossCurves()->LoadHeels(myHeels);
		getCrossCurves()->Perform();

		execute_flag = true;
	}

	//- io functions

	void saveGraphTo(const std::string& name)
	{
		if (NOT execute_flag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no cross-curves diagram has been created" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << getCrossCurves()->CrossCurves();
	}

	void saveTo(const std::string& name)
	{
		if (NOT execute_flag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no cross-curves diagram has been created" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << getCrossCurves();
	}

	void loadBody(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		body_t body;
		//ar >> body;
		Marine_Body::Load(ar, body);

		if (body->IsHull())
		{
			if (NOT std::dynamic_pointer_cast<marineLib::Body_Displacer>(body))
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid body type!" << endl
					<< abort(FatalError);
			}
		}
		else if (body->IsSail())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid body type!" << endl
				<< abort(FatalError);
		}

		if (body->NbSections() < 3)
		{
			FatalErrorIn(FunctionSIG)
				<< " the body has not enough sections" << endl
				<< abort(FatalError);
		}

		auto domain = createDomain(body);

		getCrossCurves()->LoadBody(body);
		getCrossCurves()->LoadDomain(domain);
		getCrossCurves()->SetNbWaters(nbWaters);

		gp_Ax1 ax(body->CoordinateSystem().Location(), body->CoordinateSystem().XDirection());

		getCrossCurves()->SetAx(ax);

		bodyLoad_flag = true;
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
		mod->add(chaiscript::fun([](double x)-> void {setVolumeTol(x); }), "setVolumeTol");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::vector<double>& h)-> void {setStbHeels(h); }), "setStbHeels");
		mod->add(chaiscript::fun([](int n)-> void {setStbHeels(n); }), "setStbHeels");
		mod->add(chaiscript::fun([](const std::vector<double>& h)-> void {setAsymmHeels(h); }), "setAsymHeels");
		mod->add(chaiscript::fun([](int n)-> void {setAsymmHeels(n); }), "setAsymHeels");
		mod->add(chaiscript::fun([](double l, double u, unsigned int n)-> void {setArbtHeels(l, u, n); }), "setHeels");
		mod->add(chaiscript::fun([](const unsigned int n)->void {SetNbWaters(n); }), "setNbWaters");
		mod->add(chaiscript::fun([](unsigned short i)->void {HydStatic_CrossCurves::verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](unsigned short i)-> void {Marine_CmptLib2::CrossCurve_Verbose = i; }), "setCrossCurveVerbose");
		mod->add(chaiscript::fun([](unsigned short i)-> void {Marine_CmptLib2::LeverArm_Verbose2 = i; }), "setLeverArmVerbose");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadBody(name); }), "loadBody");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveGraphTo(name); }), "saveGraphTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("crossCurves");

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