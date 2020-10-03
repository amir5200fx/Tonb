#include <CadModel_Scripts.hxx>

#include <LegModel_DispNo1.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <messageStream.hxx>

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

	mod->add(chaiscript::user_type<std::shared_ptr<LegModel_DispNo1>>(), "model_disp_no1");
	mod->add(chaiscript::fun([]() {return std::make_shared<LegModel_DispNo1>(); }), "model_disp_no1");

	mod->add(chaiscript::fun(&cad_model_perform_p), "model_ptr_perform");
	//mod->add(chaiscript::fun(&cad_model_perform), "model_perform");
	//mod->add(chaiscript::fun([](LegModel_DispNo1& t) {cad_model_perform(t); }), "perform");
	mod->add(chaiscript::fun([](const std::shared_ptr<LegModel_DispNo1>& t)-> void {cad_model_perform_p(t); }), "perform");

	//mod->add(chaiscript::fun([](LegModel_DispNo1& m, const word& name) {m.SetName(name); }), "set_name");
	mod->add(chaiscript::fun([](const std::shared_ptr<LegModel_DispNo1>& t, const word& name)-> void {t->SetName(name); }), "set_name");

	//mod->add(chaiscript::fun([](LegModel_DispNo1& m, const Standard_Integer i) {m.SetIndex(i); }), "set_index");
	mod->add(chaiscript::fun([](const std::shared_ptr<LegModel_DispNo1>& t, const Standard_Integer i)-> void {t->SetIndex(i); }), "set_index");

	//mod->add(chaiscript::fun([](LegModel_DispNo1& m) {return m.Entity(); }), "get_shape");
	mod->add(chaiscript::fun([](const std::shared_ptr<LegModel_DispNo1>& t)-> const TopoDS_Shape& {return t->Entity(); }), "get_shape");

	mod->add(chaiscript::fun([](const std::shared_ptr<LegModel_DispNo1>& t)-> Standard_Boolean {return t->IsDone(); }), "is_done");

	mod->add(chaiscript::fun(&cad_model_set_print_info), "model_set_print_info");

	chai.add(mod);
}