#include <CadModel_Scripts.hxx>

#include <LegModel_DispNo1.hxx>
#include <LegModel_NozzleType1.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <messageStream.hxx>

std::shared_ptr<tnbLib::LegModel_DispNo1> 
tnbLib::script::CadModel::newLegModelDispNo1() const
{
	auto t = std::make_shared<LegModel_DispNo1>();
	return std::move(t);
}

std::shared_ptr<tnbLib::LegModel_NozzleType1>
tnbLib::script::CadModel::newLegModelNozzelType1() const
{
	auto t = std::make_shared<LegModel_NozzleType1>();
	return std::move(t);
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

namespace tnbLib
{

	static bool print_cad_model_info = false;

	static void cad_model_perform_p(const std::shared_ptr<LegModel_DispNo1>& p)
	{
		Debug_Null_Pointer(p);
		p->Perform();

		if (print_cad_model_info)
		{
			tnbLib::Info << " the 'LegModel_DispNo1' has been created successfully" << endl
				<< " - model's name = " << p->Name() << endl
				<< "- model's index = " << p->Index() << endl;
		}
	}

	static void cad_model_perform(LegModel_DispNo1& p)
	{
		p.Perform();

		if (print_cad_model_info)
		{
			tnbLib::Info << " the 'LegModel_DispNo1' has been created successfully" << endl
				<< " - model's name = " << p.Name() << endl
				<< "- model's index = " << p.Index() << endl;
		}
	}

	static void cad_model_set_print_info(const bool print)
	{
		print_cad_model_info = print;
	}
}

#include <chaiscript/chaiscript.hpp>


void tnbLib::script::load_cad_model(chaiscript::ChaiScript& chai)
{
	auto mod = std::make_shared<chaiscript::Module>();

	//mod->add(chaiscript::user_type<LegModel_DispNo1>(), "model_disp_no1");
	//mod->add(chaiscript::constructor<LegModel_DispNo1()>(), "model_disp_no1");

	typedef std::shared_ptr<CadModel> cadModel_t;
	typedef std::shared_ptr<LegModel_DispNo1> legModelDispNo1_t;
	typedef std::shared_ptr<LegModel_NozzleType1> legModelNozzle_t;
	typedef std::shared_ptr<LegModel_Parameter> param_t;

	mod->add(chaiscript::user_type<cadModel_t>(), "CadModelModule");
	mod->add(chaiscript::fun([]() {auto t = std::make_shared<CadModel>(); return std::move(t); }), "newCadModelModule");

	mod->add(chaiscript::user_type<legModelNozzle_t>(), "LegModelNozzleNo1");
	mod->add(chaiscript::fun([](const cadModel_t& t)->legModelNozzle_t {auto m = t->newLegModelNozzelType1(); return std::move(m); }), "newLegModelNozzleNo1");

	mod->add(chaiscript::fun([](const legModelNozzle_t& t)-> void {Debug_Null_Pointer(t); t->Perform(); }), "perform");
	mod->add(chaiscript::fun([](const legModelNozzle_t& t)-> const Handle(Geom2d_Curve)& { Debug_Null_Pointer(t); return t->Profile(); }), "getProfile");


	mod->add(chaiscript::user_type<legModelDispNo1_t>(), "LegModelDispNo1");
	mod->add(chaiscript::fun([](const cadModel_t& t)-> legModelDispNo1_t {auto m = t->newLegModelDispNo1(); return std::move(m); }), "newLegModelDispNo1");

	mod->add(chaiscript::fun([](const legModelDispNo1_t& f)-> void {Debug_Null_Pointer(f); f->Perform(); }), "perform");
	mod->add(chaiscript::fun([](const legModelDispNo1_t& f)-> const TopoDS_Shape& {Debug_Null_Pointer(f); return f->Entity(); }), "getShape");

	//mod->add(chaiscript::fun(&cad_model_perform), "model_perform");
	//mod->add(chaiscript::fun([](LegModel_DispNo1& t) {cad_model_perform(t); }), "perform");
	//mod->add(chaiscript::fun([](const std::shared_ptr<LegModel_DispNo1>& t)-> void {cad_model_perform_p(t); }), "perform");

	//mod->add(chaiscript::fun([](LegModel_DispNo1& m, const word& name) {m.SetName(name); }), "set_name");
	mod->add(chaiscript::fun([](const std::shared_ptr<LegModel_DispNo1>& t, const word& name)-> void {t->SetName(name); }), "setName");

	//mod->add(chaiscript::fun([](LegModel_DispNo1& m, const Standard_Integer i) {m.SetIndex(i); }), "set_index");
	mod->add(chaiscript::fun([](const std::shared_ptr<LegModel_DispNo1>& t, const Standard_Integer i)-> void {t->SetIndex(i); }), "setIndex");

	//mod->add(chaiscript::fun([](LegModel_DispNo1& m) {return m.Entity(); }), "get_shape");

	mod->add(chaiscript::fun([](const std::shared_ptr<LegModel_DispNo1>& t)-> Standard_Boolean {return t->IsDone(); }), "isDone");

	mod->add(chaiscript::fun(&cad_model_set_print_info), "model_set_print_info");

	chai.add(mod);
}