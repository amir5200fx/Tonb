#include <SectPx_Script.hxx>

#include <SectPx_Pars.hxx>
#include <SectPx_Node.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_FrameAPI.hxx>
#include <SectPx_FieldFun.hxx>
#include <SectPx_GeoMap.hxx>
#include <SectPx_ParameterMaker.hxx>
#include <SectPx_PointMaker.hxx>
#include <SectPx_GeometricMapMaker.hxx>
#include <SectPx_CmptProfileMaker.hxx>
#include <SectPx_FieldFunMaker.hxx>
#include <SectPx_ProfileMaker.hxx>
#include <SectPx_ProfileQ.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_Pnts.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static Standard_Integer
		sectpx_point_maker_create_empty
		(
			const std::shared_ptr<maker::Point>& m,
			const std::shared_ptr<SectPx_Pnt>& pt
		)
	{
		if (NOT pt->IsMaster())
		{
			FatalErrorIn(FunctionSIG)
				<< " the point is not master!" << endl
				<< abort(FatalError);
		}
		auto master = std::dynamic_pointer_cast<SectPx_MasterPnt>(pt);
		Debug_Null_Pointer(master);

		Debug_Null_Pointer(m);
		return m->CreateEmpty(master);
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

#include <vector>

void tnbLib::script::load_sectpx(chaiscript::ChaiScript& chai)
{
	typedef std::shared_ptr<SectPx_Par> par_t;
	typedef std::shared_ptr<SectPx_FieldFun> field_t;
	typedef std::shared_ptr<SectPx_Pnt> pnt_t;
	typedef std::shared_ptr<SectPx_Frame> frame_t;
	typedef std::shared_ptr<SectPx_GeoMap> geoMap_t;
	typedef std::shared_ptr<SectPx_Coord> coord_t;
	typedef std::shared_ptr<SectPx_TopoProfile> tProf_t;
	typedef std::shared_ptr<SectPx_Node> node_t;
	typedef std::shared_ptr<SectPx_Edge> edge_t;
	typedef std::shared_ptr<SectPx_ProfileQ> prfQ_t;

	auto mod = std::make_shared<chaiscript::Module>();

	mod->add(chaiscript::user_type<par_t>(), "px_par");
	mod->add(chaiscript::user_type<field_t>(), "px_field");
	mod->add(chaiscript::user_type<pnt_t>(), "px_pnt");
	mod->add(chaiscript::user_type<frame_t>(), "px_frame");
	mod->add(chaiscript::user_type<geoMap_t>(), "px_geoMap");
	mod->add(chaiscript::user_type<coord_t>(), "px_coord");
	mod->add(chaiscript::user_type<tProf_t>(), "px_topoProfile");
	mod->add(chaiscript::user_type<node_t>(), "px_node");
	mod->add(chaiscript::user_type<edge_t>(), "px_edge");
	mod->add(chaiscript::user_type<prfQ_t>(), "px_prileQ");

	/*mod->add(chaiscript::constructor<SectPx_Frame()>(), "px_frame");
	mod->add(chaiscript::constructor<SectPx_Frame(const Standard_Integer)>(), "px_frame");
	mod->add(chaiscript::constructor<SectPx_Frame(const Standard_Integer, const word&)>(), "px_frame");*/
	mod->add(chaiscript::fun([]() {return std::make_shared<SectPx_Frame>(); }), "px_newFrame");
	mod->add(chaiscript::fun([](const Standard_Integer i) {return std::make_shared<SectPx_Frame>(i); }), "px_newFrame");
	mod->add(chaiscript::fun([](const Standard_Integer i, const word& n) {return std::make_shared<SectPx_Frame>(i, n); }), "px_newFrame");

	/*mod->add(chaiscript::user_type<SectPx_Par>(), "px_par");*/
	mod->add(chaiscript::user_type<std::shared_ptr<SectPx_Par>>(), "px_par");
	mod->add(chaiscript::user_type<std::vector<std::shared_ptr<SectPx_Par>>>(), "px_parVector");
	mod->add(chaiscript::fun([](const std::vector<std::shared_ptr<SectPx_Par>>& v) {return (Standard_Integer)v.size(); }), "getSize");
	//mod->add(chaiscript::fun(&std::vector<std::shared_ptr<SectPx_Par>>::size), "size");

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

	//mod->add(chaiscript::fun(&SectPx_FrameAPI::CreateFrame), "px_newFrame");

	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<SectPx_Frame::EntityMaker>& {Debug_Null_Pointer(f); return f->Makers(); }), "getMakers");
	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::Parameter>& {Debug_Null_Pointer(f); return f->ParameterMaker(); }), "getParameterMaker");
	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::Point>& {Debug_Null_Pointer(f); return f->PointMaker(); }), "getPointMaker");
	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::GeometricMap>& {Debug_Null_Pointer(f); return f->GeometricMapMaker(); }), "getGeometricMap");
	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::FieldFun>& {Debug_Null_Pointer(f); return f->FieldFunMaker(); }), "getFieldMaker");
	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::CmptProfile>& {Debug_Null_Pointer(f); return f->CmptProfileMaker(); }), "getCmptProfileMaker");

	typedef std::shared_ptr<maker::Parameter> parMaker_t;
	mod->add(chaiscript::user_type<parMaker_t>(), "px_parameterMaker");

	mod->add(chaiscript::fun([](const parMaker_t& m, const Standard_Real x)-> Standard_Integer { Debug_Null_Pointer(m); return m->CreateConstant(x); }), "makeConstant");
	mod->add(chaiscript::fun([](const parMaker_t& m, const Standard_Real x)-> Standard_Integer {Debug_Null_Pointer(m); return m->CreateFixed(x); }), "makeFixed");
	mod->add(chaiscript::fun([](const parMaker_t& m, const field_t& f)-> Standard_Integer {Debug_Null_Pointer(m); return m->CreateFree(f); }), "makeFree");

	mod->add(chaiscript::fun([](const parMaker_t& m, const Standard_Integer i) -> par_t {Debug_Null_Pointer(m); return m->SelectParameter(i); }), "select");
	mod->add(chaiscript::fun([](const parMaker_t& m, const Standard_Integer i) -> par_t {Debug_Null_Pointer(m); return m->RemoveParameter(i); }), "remove");

	mod->add(chaiscript::fun([](const parMaker_t& m) -> std::vector<par_t> {Debug_Null_Pointer(m); auto v = m->RetrieveParameters(); return std::move(v); }), "retrieveParameters");
	mod->add(chaiscript::fun([](const parMaker_t& m) -> std::vector<par_t> {Debug_Null_Pointer(m); auto v = m->RetrieveConstParameters(); return std::move(v); }), "retrieveConstantParameters");
	mod->add(chaiscript::fun([](const parMaker_t& m) -> std::vector<par_t> {Debug_Null_Pointer(m); auto v = m->RetrieveFixedParameters(); return std::move(v); }), "retrieveFixedParameters");
	mod->add(chaiscript::fun([](const parMaker_t& m) -> std::vector<par_t> {Debug_Null_Pointer(m); auto v = m->RetrieveFreeParameters(); return std::move(v); }), "retrieveFreeParameters");

	typedef std::shared_ptr<maker::Point> pntMaker_t;
	mod->add(chaiscript::user_type<pntMaker_t>(), "px_pointMaker");

	mod->add(chaiscript::fun([](const pntMaker_t& m, const par_t& x, const par_t& y) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateOuterComponent(x, y); }), "makeOuterComponent");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const par_t& x, const par_t& y) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateInnerComponent(x, y); }), "makeInnerComponent");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const geoMap_t& g) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateField(g); }), "makeField");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const pnt_t& p) -> Standard_Integer {return sectpx_point_maker_create_empty(m, p); }), "makeEmpty");

	mod->add(chaiscript::fun([](const pntMaker_t& m, const Standard_Integer i) -> pnt_t {Debug_Null_Pointer(m); auto t = m->SelectPnt(i); return std::move(t); }), "select");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const Standard_Integer i) -> pnt_t {Debug_Null_Pointer(m); auto t = m->RemovePnt(i); return std::move(t); }), "remove");

	typedef std::shared_ptr<maker::GeometricMap> geoMapMaker_t;
	mod->add(chaiscript::user_type<geoMapMaker_t>(), "px_geometricMapMaker");

	mod->add(chaiscript::fun([](const geoMapMaker_t& m, const coord_t& p0, const coord_t& p1, const par_t& t) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateLinearInterpolation(p0, p1, t); }), "makeLinearInterpolation");
	mod->add(chaiscript::fun([](const geoMapMaker_t& m) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateLinearInterpolation(); }), "makeLinearInterpolation");
	mod->add(chaiscript::fun([](const geoMapMaker_t& m, const coord_t& q0, const Dir2d& d0, const par_t& a0, const coord_t& q1, const Dir2d& d1, const par_t& a1) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateIntersection(q0, d0, a0, q1, d1, a1); }), "makeIntersection");
	mod->add(chaiscript::fun([](const geoMapMaker_t& m) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateIntersection(); }), "makeIntersection");

	typedef std::shared_ptr<maker::CmptProfile> cmptProfMaker_t;
	typedef std::shared_ptr<maker::Profile> profMaker_t;
	mod->add(chaiscript::user_type<cmptProfMaker_t>(), "px_cmptProfileMaker");
	mod->add(chaiscript::user_type<profMaker_t>(), "px_profileMaker");
	mod->add(chaiscript::user_type<std::map<Standard_Integer, profMaker_t>>(), "px_profileMakerMap");

	mod->add(chaiscript::fun([](const cmptProfMaker_t& m) -> Standard_Integer {Debug_Null_Pointer(m); return m->NbProfiles(); }), "nbProfiles");
	mod->add(chaiscript::fun([](const cmptProfMaker_t& m) -> const std::map<Standard_Integer, profMaker_t>& {Debug_Null_Pointer(m); return m->Profiles(); }), "profiles");
	mod->add(chaiscript::fun([](const cmptProfMaker_t& m, const Standard_Integer i) -> profMaker_t {Debug_Null_Pointer(m); auto p = m->SelectProfile(i); return std::move(p); }), "select");
	mod->add(chaiscript::fun([](const cmptProfMaker_t& m, const pnt_t& p0, const pnt_t& p1) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateProfile(p0, p1); }), "makeProfile");

	mod->add(chaiscript::fun([](const profMaker_t& m) -> const tProf_t& {Debug_Null_Pointer(m); return m->TopoProfile(); }), "topoProfile");
	mod->add(chaiscript::fun([](const profMaker_t& m) -> const node_t& {Debug_Null_Pointer(m); return m->Node0(); }), "node0");
	mod->add(chaiscript::fun([](const profMaker_t& m) -> const node_t& {Debug_Null_Pointer(m); return m->Node1(); }), "node1");
	mod->add(chaiscript::fun([](const profMaker_t& m) -> void {Debug_Null_Pointer(m); m->Init(); }), "init");
	mod->add(chaiscript::fun([](const profMaker_t& m, const Standard_Integer i) -> edge_t {Debug_Null_Pointer(m); auto p = m->SelectEdge(i); return std::move(p); }), "selectEdge");
	mod->add(chaiscript::fun([](const profMaker_t& m, const pnt_t& p, const edge_t& e) -> std::tuple<Standard_Integer, Standard_Integer> {Debug_Null_Pointer(m); auto t = m->ImportPnt(p, e); return std::move(t); }), "importEdge");
	mod->add(chaiscript::fun([](const profMaker_t& m) -> prfQ_t {Debug_Null_Pointer(m); auto v = m->RetrieveProfileQ(); return std::move(v); }), "retrieveProfileQ");

	mod->add(chaiscript::fun([](const prfQ_t& p) -> std::vector<Pnt2d> {Debug_Null_Pointer(p); auto v = p->RetrievePnts(); return std::move(v); }), "retrievePoints");
	/*mod->add(chaiscript::fun(&SectPx_FrameAPI::SelectParameter), "px_select_par");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::RemoveParameter), "px_remove_par");

	mod->add(chaiscript::fun(&SectPx_FrameAPI::CreateConstantParameter), "px_create_const_par");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::CreateFixedParameter), "px_create_fixed_par");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::CreateFreeParameter), "px_create_free_par");

	mod->add(chaiscript::fun(&SectPx_FrameAPI::RetrieveFreeParameters), "px_retrieve_free_pars");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::RetrieveFixedParameters), "px_retrieve_fixed_pars");
	mod->add(chaiscript::fun(&SectPx_FrameAPI::RetrieveConstantParameters), "px_retrieve_const_pars");

	mod->add(chaiscript::fun(&SectPx_FrameAPI::RetrieveParameters), "px_retrieve_pars");

	mod->add(chaiscript::fun(&SectPx_FrameAPI::Print), "px_print");*/


	chai.add(mod);
}