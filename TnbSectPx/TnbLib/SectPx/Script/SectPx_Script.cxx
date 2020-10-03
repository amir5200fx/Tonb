#include <SectPx_Script.hxx>

#include <SectPx_Pars.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_FrameAPI.hxx>
#include <SectPx_FieldFun.hxx>

#include <chaiscript/chaiscript.hpp>

#include <vector>

void tnbLib::script::sectPx(chaiscript::ChaiScript& chai)
{

	auto mod = std::make_shared<chaiscript::Module>();


	mod->add(chaiscript::user_type<SectPx_Frame>(), "px_frame");
	mod->add(chaiscript::constructor<SectPx_Frame()>(), "px_frame");
	mod->add(chaiscript::constructor<SectPx_Frame(const Standard_Integer)>(), "px_frame");
	mod->add(chaiscript::constructor<SectPx_Frame(const Standard_Integer, const word&)>(), "px_frame");
	mod->add(chaiscript::fun([]() {return std::make_shared<SectPx_Frame>(); }), "px_new_frame");
	mod->add(chaiscript::fun([](const Standard_Integer i) {return std::make_shared<SectPx_Frame>(i); }), "px_new_frame");
	mod->add(chaiscript::fun([](const Standard_Integer i, const word& n) {return std::make_shared<SectPx_Frame>(i, n); }), "px_new_frame");

	mod->add(chaiscript::user_type<SectPx_Par>(), "px_par");
	mod->add(chaiscript::user_type<std::shared_ptr<SectPx_Par>>(), "px_par_ptr");
	mod->add(chaiscript::user_type<std::vector<std::shared_ptr<SectPx_Par>>>(), "px_par_vector");
	mod->add(chaiscript::fun([](const std::vector<std::shared_ptr<SectPx_Par>>& v) {return (Standard_Integer)v.size(); }), "px_get_size");
	mod->add(chaiscript::fun(&std::vector<std::shared_ptr<SectPx_Par>>::size), "size");

	mod->add
	(
		chaiscript::fun
		(
			static_cast
			<
			const std::shared_ptr<SectPx_Par>&
			(
				std::vector<std::shared_ptr<SectPx_Par>>::*
				)(const size_t) const
			>
			(&std::vector<std::shared_ptr<SectPx_Par>>::at)
		),
		"at"
	);

	mod->add
	(
		chaiscript::fun
		(
			static_cast
			<
			const std::shared_ptr<SectPx_Par>&
			(
				std::vector<std::shared_ptr<SectPx_Par>>::*
				)(const size_t) const
			>
			(&std::vector<std::shared_ptr<SectPx_Par>>::operator[])
		),
		"[]"
	);

	mod->add(chaiscript::fun(&SectPx_FrameAPI::CreateFrame), "px_create_frame");

	mod->add(chaiscript::fun(&SectPx_FrameAPI::SelectParameter), "px_select_par");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::RemoveParameter), "px_remove_par");

	mod->add(chaiscript::fun(&SectPx_FrameAPI::CreateConstantParameter), "px_create_const_par");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::CreateFixedParameter), "px_create_fixed_par");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::CreateFreeParameter), "px_create_free_par");

	mod->add(chaiscript::fun(&SectPx_FrameAPI::RetrieveFreeParameters), "px_retrieve_free_pars");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::RetrieveFixedParameters), "px_retrieve_fixed_pars");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::RetrieveConstantParameters), "px_retrieve_const_pars");

	mod->add(chaiscript::fun(&SectPx_FrameAPI::RetrieveParameters), "px_retrieve_pars");

	mod->add(chaiscript::fun(&SectPx_FrameAPI::Print), "px_print");

	
	chai.add(mod);
}