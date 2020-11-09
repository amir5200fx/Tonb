//#include <SectPx_Script.hxx>
//
//#include <SectPx_Pars.hxx>
//#include <SectPx_Node.hxx>
//#include <SectPx_Edge.hxx>
//#include <SectPx_Frame.hxx>
//#include <SectPx_FrameAPI.hxx>
//#include <SectPx_FieldFun.hxx>
//#include <SectPx_GeoMap.hxx>
//#include <SectPx_ParameterMaker.hxx>
//#include <SectPx_PointMaker.hxx>
//#include <SectPx_GeometricMapMaker.hxx>
//#include <SectPx_CmptProfileMaker.hxx>
//#include <SectPx_FieldFunMaker.hxx>
//#include <SectPx_ProfileMaker.hxx>
//#include <SectPx_ProfileQ.hxx>
//#include <SectPx_TopoProfile.hxx>
//#include <SectPx_PntTools.hxx>
//#include <SectPx_Pnts.hxx>
//#include <SectPx_Registry.hxx>
//#include <SectPx_Cloud.hxx>
//
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//std::shared_ptr<tnbLib::SectPx_Frame> 
//tnbLib::script::SectPx::newFrame() const
//{
//	auto t = std::make_shared<SectPx_Frame>();
//	return std::move(t);
//}
//
//namespace tnbLib
//{
//	static Standard_Integer
//		sectpx_point_maker_create_empty
//		(
//			const std::shared_ptr<maker::Point>& m,
//			const std::shared_ptr<SectPx_Pnt>& pt
//		)
//	{
//		if (NOT pt->IsMaster())
//		{
//			FatalErrorIn(FunctionSIG)
//				<< " the point is not master!" << endl
//				<< abort(FatalError);
//		}
//		auto master = std::dynamic_pointer_cast<SectPx_MasterPnt>(pt);
//		Debug_Null_Pointer(master);
//
//		Debug_Null_Pointer(m);
//		return m->CreateEmpty(master);
//	}
//}
//
//#ifdef DebugInfo
//#undef DebugInfo
//#endif // DebugInfo
//
//#include <chaiscript/chaiscript.hpp>
//
//#include <vector>
//
//void tnbLib::script::load_sectpx(chaiscript::ChaiScript& chai)
//{
//	typedef std::shared_ptr<SectPx_Par> par_t;
//	typedef std::shared_ptr<SectPx_FieldFun> field_t;
//	typedef std::shared_ptr<SectPx_Pnt> pnt_t;
//	typedef std::shared_ptr<SectPx_Frame> frame_t;
//	typedef std::shared_ptr<SectPx_GeoMap> geoMap_t;
//	typedef std::shared_ptr<SectPx_Coord> coord_t;
//	typedef std::shared_ptr<SectPx_TopoProfile> tProf_t;
//	typedef std::shared_ptr<SectPx_Node> node_t;
//	typedef std::shared_ptr<SectPx_Edge> edge_t;
//	typedef std::shared_ptr<SectPx_ProfileQ> prfQ_t;
//	typedef std::shared_ptr<SectPx_FixedPar> fxPar_t;
//
//	auto mod = std::make_shared<chaiscript::Module>();
//
//	mod->add(chaiscript::user_type<par_t>(), "px_par");
//	mod->add(chaiscript::user_type<field_t>(), "px_field");
//	mod->add(chaiscript::user_type<pnt_t>(), "px_pnt");
//	mod->add(chaiscript::user_type<frame_t>(), "px_frame");
//	mod->add(chaiscript::user_type<geoMap_t>(), "px_geoMap");
//	mod->add(chaiscript::user_type<coord_t>(), "px_coord");
//	mod->add(chaiscript::user_type<tProf_t>(), "px_topoProfile");
//	mod->add(chaiscript::user_type<node_t>(), "px_node");
//	mod->add(chaiscript::user_type<edge_t>(), "px_edge");
//	mod->add(chaiscript::user_type<prfQ_t>(), "px_prfQ");
//
//	/*mod->add(chaiscript::constructor<SectPx_Frame()>(), "px_frame");
//	mod->add(chaiscript::constructor<SectPx_Frame(const Standard_Integer)>(), "px_frame");
//	mod->add(chaiscript::constructor<SectPx_Frame(const Standard_Integer, const word&)>(), "px_frame");*/
//	mod->add(chaiscript::fun([]() {return std::make_shared<SectPx_Frame>(); }), "px_newFrame");
//	mod->add(chaiscript::fun([](const Standard_Integer i) {return std::make_shared<SectPx_Frame>(i); }), "px_newFrame");
//	mod->add(chaiscript::fun([](const Standard_Integer i, const word& n) {return std::make_shared<SectPx_Frame>(i, n); }), "px_newFrame");
//
//	/*mod->add(chaiscript::user_type<SectPx_Par>(), "px_par");*/
//	mod->add(chaiscript::user_type<std::shared_ptr<SectPx_Par>>(), "px_par");
//	mod->add(chaiscript::user_type<std::vector<std::shared_ptr<SectPx_Par>>>(), "px_parVector");
//	mod->add(chaiscript::user_type<fxPar_t>(), "px_fxPar");
//	mod->add(chaiscript::fun([](const fxPar_t& f, const Standard_Real x)->void {Debug_Null_Pointer(f); f->SetValue(x); }), "setValue");
//	mod->add(chaiscript::user_type<std::map<std::string, fxPar_t>>(), "px_stringToFxParMap");
//	mod->add(chaiscript::fun([](const std::vector<std::shared_ptr<SectPx_Par>>& v) {return (Standard_Integer)v.size(); }), "getSize");
//	mod->add(chaiscript::fun([](const std::map<std::string, fxPar_t>& m) {return m.size(); }), "size");
//	mod->add(chaiscript::user_type<std::vector<prfQ_t>>(), "px_prfQVector");
//	mod->add(chaiscript::fun([](const std::vector<prfQ_t>& v) {return (Standard_Integer)v.size(); }), "size");
//	//mod->add(chaiscript::fun(&std::vector<std::shared_ptr<SectPx_Par>>::size), "size");
//
//	mod->add
//	(
//		chaiscript::fun
//		(
//			static_cast
//			<
//			const std::shared_ptr<SectPx_Par>&
//			(
//				std::vector<std::shared_ptr<SectPx_Par>>::*
//				)(const size_t) const
//			>
//			(&std::vector<std::shared_ptr<SectPx_Par>>::at)
//		),
//		"at"
//	);
//
//	mod->add
//	(
//		chaiscript::fun
//		(
//			static_cast
//			<
//			const std::shared_ptr<SectPx_Par>&
//			(
//				std::vector<std::shared_ptr<SectPx_Par>>::*
//				)(const size_t) const
//			>
//			(&std::vector<std::shared_ptr<SectPx_Par>>::operator[])
//		),
//		"[]"
//	);
//
//	mod->add(chaiscript::fun(static_cast<const prfQ_t&(std::vector<prfQ_t>::*)(const size_t)const>(&std::vector<prfQ_t>::at)), "at");
//	mod->add(chaiscript::fun(static_cast<const prfQ_t&(std::vector<prfQ_t>::*)(const size_t)const>(&std::vector<prfQ_t>::operator[])), "[]");
//	mod->add(chaiscript::fun(static_cast<const fxPar_t&(std::map<std::string, fxPar_t>::*)(const std::string&)const>(&std::map<std::string, fxPar_t>::at)), "at");
//	mod->add(chaiscript::fun(static_cast<const fxPar_t&(std::map<std::string, fxPar_t>::*)(const std::string&)const>(&std::map<std::string, fxPar_t>::at)), "at");
//	mod->add(chaiscript::fun(static_cast<fxPar_t&(std::map<std::string, fxPar_t>::*)(const std::string&)>(&std::map<std::string, fxPar_t>::operator[])), "[]");
//	//mod->add(chaiscript::fun(&SectPx_FrameAPI::CreateFrame), "px_newFrame");
//
//
//	typedef std::shared_ptr<maker::Parameter> parMaker_t;
//	mod->add(chaiscript::user_type<parMaker_t>(), "px_parameterMaker");
//
//	mod->add(chaiscript::fun([](const parMaker_t& m, const Standard_Real x)-> Standard_Integer { Debug_Null_Pointer(m); return m->CreateConstant(x); }), "makeConstant");
//	mod->add(chaiscript::fun([](const parMaker_t& m, const Standard_Real x)-> Standard_Integer {Debug_Null_Pointer(m); return m->CreateFixed(x); }), "makeFixed");
//	mod->add(chaiscript::fun([](const parMaker_t& m, const field_t& f)-> Standard_Integer {Debug_Null_Pointer(m); return m->CreateFree(f); }), "makeFree");
//
//	mod->add(chaiscript::fun([](const parMaker_t& m, const Standard_Integer i) -> par_t {Debug_Null_Pointer(m); return m->SelectParameter(i); }), "select");
//	mod->add(chaiscript::fun([](const parMaker_t& m, const Standard_Integer i) -> par_t {Debug_Null_Pointer(m); return m->RemoveParameter(i); }), "remove");
//
//	mod->add(chaiscript::fun([](const parMaker_t& m) -> std::vector<par_t> {Debug_Null_Pointer(m); auto v = m->RetrieveParameters(); return std::move(v); }), "retrieveParameters");
//	mod->add(chaiscript::fun([](const parMaker_t& m) -> std::vector<par_t> {Debug_Null_Pointer(m); auto v = m->RetrieveConstParameters(); return std::move(v); }), "retrieveConstantParameters");
//	mod->add(chaiscript::fun([](const parMaker_t& m) -> std::vector<par_t> {Debug_Null_Pointer(m); auto v = m->RetrieveFixedParameters(); return std::move(v); }), "retrieveFixedParameters");
//	mod->add(chaiscript::fun([](const parMaker_t& m) -> std::vector<par_t> {Debug_Null_Pointer(m); auto v = m->RetrieveFreeParameters(); return std::move(v); }), "retrieveFreeParameters");
//
//	typedef std::shared_ptr<maker::Point> pntMaker_t;
//	mod->add(chaiscript::user_type<pntMaker_t>(), "px_pointMaker");
//
//	mod->add(chaiscript::fun([](const pntMaker_t& m, const par_t& x, const par_t& y) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateOuterComponent(x, y); }), "makeOuterComponent");
//	mod->add(chaiscript::fun([](const pntMaker_t& m, const par_t& x, const par_t& y) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateInnerComponent(x, y); }), "makeInnerComponent");
//	mod->add(chaiscript::fun([](const pntMaker_t& m, const geoMap_t& g) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateField(g); }), "makeField");
//	mod->add(chaiscript::fun([](const pntMaker_t& m, const pnt_t& p) -> Standard_Integer {return sectpx_point_maker_create_empty(m, p); }), "makeEmpty");
//
//	mod->add(chaiscript::fun([](const pntMaker_t& m, const Standard_Integer i) -> pnt_t {Debug_Null_Pointer(m); auto t = m->SelectPnt(i); return std::move(t); }), "select");
//	mod->add(chaiscript::fun([](const pntMaker_t& m, const Standard_Integer i) -> pnt_t {Debug_Null_Pointer(m); auto t = m->RemovePnt(i); return std::move(t); }), "remove");
//
//	typedef std::shared_ptr<maker::GeometricMap> geoMapMaker_t;
//	mod->add(chaiscript::user_type<geoMapMaker_t>(), "px_geometricMapMaker");
//
//	mod->add(chaiscript::fun([](const geoMapMaker_t& m, const coord_t& p0, const coord_t& p1, const par_t& t) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateLinearInterpolation(p0, p1, t); }), "makeLinearInterpolation");
//	mod->add(chaiscript::fun([](const geoMapMaker_t& m) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateLinearInterpolation(); }), "makeLinearInterpolation");
//	mod->add(chaiscript::fun([](const geoMapMaker_t& m, const coord_t& q0, const Dir2d& d0, const par_t& a0, const coord_t& q1, const Dir2d& d1, const par_t& a1) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateIntersection(q0, d0, a0, q1, d1, a1); }), "makeIntersection");
//	mod->add(chaiscript::fun([](const geoMapMaker_t& m) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateIntersection(); }), "makeIntersection");
//
//	typedef std::shared_ptr<maker::CmptProfile> cmptProfMaker_t;
//	typedef std::shared_ptr<maker::Profile> profMaker_t;
//	mod->add(chaiscript::user_type<cmptProfMaker_t>(), "px_cmptProfileMaker");
//	mod->add(chaiscript::user_type<profMaker_t>(), "px_profileMaker");
//	mod->add(chaiscript::user_type<std::map<Standard_Integer, profMaker_t>>(), "px_profileMakerMap");
//
//	mod->add(chaiscript::fun([](const cmptProfMaker_t& m) -> Standard_Integer {Debug_Null_Pointer(m); return m->NbProfiles(); }), "nbProfiles");
//	mod->add(chaiscript::fun([](const cmptProfMaker_t& m) -> const std::map<Standard_Integer, profMaker_t>& {Debug_Null_Pointer(m); return m->Profiles(); }), "profiles");
//	mod->add(chaiscript::fun([](const cmptProfMaker_t& m, const Standard_Integer i) -> profMaker_t {Debug_Null_Pointer(m); auto p = m->SelectProfile(i); return std::move(p); }), "select");
//	mod->add(chaiscript::fun([](const cmptProfMaker_t& m, const pnt_t& p0, const pnt_t& p1) -> Standard_Integer {Debug_Null_Pointer(m); return m->CreateCustomProfile(p0, p1); }), "makeCustomProfile");
//	mod->add(chaiscript::fun([](const cmptProfMaker_t& m, const std::shared_ptr<SectPx_Cloud>& c) {Debug_Null_Pointer(m); auto p = m->CreateInterplProfile(c); return std::move(p); }), "makeInterplProfile");
//
//	mod->add(chaiscript::fun([](const profMaker_t& m) -> const tProf_t& {Debug_Null_Pointer(m); return m->TopoProfile(); }), "topoProfile");
//	mod->add(chaiscript::fun([](const profMaker_t& m) -> const node_t& {Debug_Null_Pointer(m); return m->Node0(); }), "node0");
//	mod->add(chaiscript::fun([](const profMaker_t& m) -> const node_t& {Debug_Null_Pointer(m); return m->Node1(); }), "node1");
//	mod->add(chaiscript::fun([](const profMaker_t& m) -> void {Debug_Null_Pointer(m); m->Init(); }), "init");
//	mod->add(chaiscript::fun([](const profMaker_t& m, const Standard_Integer i) -> edge_t {Debug_Null_Pointer(m); auto p = m->SelectEdge(i); return std::move(p); }), "selectEdge");
//	mod->add(chaiscript::fun([](const profMaker_t& m, const pnt_t& p, const edge_t& e) -> std::tuple<Standard_Integer, Standard_Integer> {Debug_Null_Pointer(m); auto t = m->ImportPnt(p, e); return std::move(t); }), "importEdge");
//	mod->add(chaiscript::fun([](const profMaker_t& m) -> prfQ_t {Debug_Null_Pointer(m); auto v = m->RetrieveProfileQ(); return std::move(v); }), "retrieveProfileQ");
//	mod->add(chaiscript::fun([](const profMaker_t& m, const Standard_Integer deg)->Handle(Geom2d_Curve) { Debug_Null_Pointer(m); auto c = m->RetrieveGeomCurve(deg); return std::move(c); }), "retrieveGeometryCurve");
//
//	mod->add(chaiscript::fun([](const prfQ_t& p) -> std::vector<Pnt2d> {Debug_Null_Pointer(p); auto v = p->RetrievePnts(); return std::move(v); }), "retrievePoints");
//	
//	mod->add(chaiscript::user_type<std::shared_ptr<script::SectPx>>(), "SectPxModule");
//	mod->add(chaiscript::fun([]() { return std::make_shared<script::SectPx>(); }), "newSectPxModule");
//	
//	typedef std::shared_ptr<script::SectPx> sectPx_t;
//
//	mod->add(chaiscript::user_type<std::shared_ptr<SectPx_Frame>>(), "SectPxFrame");
//	mod->add(chaiscript::fun([](const sectPx_t& t)-> std::shared_ptr<SectPx_Frame> {auto f = t->newFrame(); return std::move(f); }), "newFrame");
//
//	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<SectPx_Registry>& {Debug_Null_Pointer(f); return f->Registry(); }), "getRegistry");
//	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<SectPx_Frame::EntityMaker>& {Debug_Null_Pointer(f); return f->Makers(); }), "getMakers");
//	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::Parameter>& {Debug_Null_Pointer(f); return f->ParameterMaker(); }), "getParameterMaker");
//	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::Point>& {Debug_Null_Pointer(f); return f->PointMaker(); }), "getPointMaker");
//	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::GeometricMap>& {Debug_Null_Pointer(f); return f->GeometricMapMaker(); }), "getGeometricMapMaker");
//	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::FieldFun>& {Debug_Null_Pointer(f); return f->FieldFunMaker(); }), "getFieldMaker");
//	mod->add(chaiscript::fun([](const frame_t& f)-> const std::shared_ptr<maker::CmptProfile>& {Debug_Null_Pointer(f); return f->CmptProfileMaker(); }), "getCmptProfileMaker");
//
//	mod->add(chaiscript::fun([](const frame_t& f)-> void {Debug_Null_Pointer(f); f->MakeLineSegment(); }), "makeSegment");
//	mod->add(chaiscript::fun([](const frame_t& f, const Pnt2d& p0, const Pnt2d& p1)-> void {Debug_Null_Pointer(f); f->MakeLineSegment(p0, p1); }), "makeSegment");
//	mod->add(chaiscript::fun([](const frame_t& f)-> void {Debug_Null_Pointer(f); f->MakeCorner(); }), "makeCorner");
//	mod->add(chaiscript::fun([](const frame_t& f, const Pnt2d& p0, const Pnt2d& p1)-> void {Debug_Null_Pointer(f); f->MakeCorner(p0, p1); }), "makeCorner");
//	mod->add(chaiscript::fun([](const frame_t& f, const Pnt2d& p0, const Dir2d& d0, const Standard_Real a0, const Pnt2d& p1, const Dir2d& d1, const Standard_Real a1)-> void {Debug_Null_Pointer(f); f->MakeCorner(p0, d0, a0, p1, d1, a1); }), "makeCorner");
//	mod->add(chaiscript::fun([](const frame_t& f)-> void {Debug_Null_Pointer(f); f->MakeUShape(); }), "makeUShape");
//	mod->add(chaiscript::fun([](const frame_t& f, const Pnt2d& p0, const Pnt2d& p1, const Standard_Real w)-> void {Debug_Null_Pointer(f); f->MakeUShape(p0, p1, w); }), "makeUShape");
//	mod->add(chaiscript::fun([](const frame_t& f)-> Standard_Integer {Debug_Null_Pointer(f); return f->NbProfiles(); }), "nbProfiles");
//	mod->add(chaiscript::fun([](const frame_t& f)-> std::vector<prfQ_t> {Debug_Null_Pointer(f); auto v = f->RetrieveProfilesQ(); return std::move(v); }), "retrieveProfilesQ");
//	mod->add(chaiscript::fun([](const frame_t& f)-> std::map<std::string, fxPar_t> {Debug_Null_Pointer(f); auto v = f->RetrieveFixedParameters(); return std::move(v); }), "retrieveFixedParameters");
//
//	mod->add(chaiscript::fun([](const frame_t& f)-> void {Debug_Null_Pointer(f); f->PrintRegistry(); }), "printRegistry");
//
//	chai.add(mod);
//}