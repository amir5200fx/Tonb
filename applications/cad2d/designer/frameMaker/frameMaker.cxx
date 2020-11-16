#include <TecPlot.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_FieldFuns.hxx>
#include <SectPx_Coord.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_GeoMap.hxx>
#include <SectPx_UniKnots.hxx>
#include <SectPx_ProfileMaker.hxx>
#include <SectPx_TopoProfile.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <boost/graph/minimum_degree_ordering.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<SectPx_Frame> frame_t;

	typedef std::shared_ptr<maker::Parameter> parMaker_t;
	typedef std::shared_ptr<maker::FieldFun> fieldMaker_t;
	typedef std::shared_ptr<maker::Point> pntMaker_t;
	typedef std::shared_ptr<maker::GeometricMap> geoMaker_t;
	typedef std::shared_ptr<maker::CmptProfile> cmpPrfMaker_t;
	typedef std::shared_ptr<maker::Profile> profile_t;

	typedef std::shared_ptr<SectPx_Par> par_t;
	typedef std::shared_ptr<SectPx_FixedPar> fixed_t;
	typedef std::shared_ptr<SectPx_FreePar> free_t;
	typedef std::shared_ptr<SectPx_ConstPar> const_t;

	typedef std::shared_ptr<SectPx_FieldFun> fieldFun_t;
	typedef std::shared_ptr<sectPxLib::FieldFun_Expr> exprField_t;
	typedef std::shared_ptr<SectPx_GeoMap> geoMap_t;

	typedef std::shared_ptr<SectPx_Coord> coord_t;
	typedef std::shared_ptr<SectPx_Pnt> pnt_t;
	typedef std::shared_ptr<SectPx_MasterPnt> mastPnt_t;
	typedef std::shared_ptr<SectPx_Cloud> cloud_t;

	typedef std::shared_ptr<SectPx_Edge> edge_t;
	typedef std::shared_ptr<SectPx_RegObj> regObj_t;

	static auto uniKnotAlg_t = std::make_shared<SectPx_UniKnots>();
	static auto myFrame = std::make_shared<SectPx_Frame>();


	Pnt2d createGeoPoint(const double x, const double y)
	{
		Pnt2d p(x, y);
		return std::move(p);
	}

	par_t getPar(const fixed_t& p)
	{
		return p;
	}

	par_t getPar(const free_t& p)
	{
		return p;
	}

	par_t getPar(const const_t& p)
	{
		return p;
	}

	par_t getPar(const par_t& p)
	{
		return p;
	}

	coord_t getCoord(const pnt_t& p)
	{
		return p;
	}

	coord_t getCoord(const coord_t& p)
	{
		return p;
	}

	void printObj(const regObj_t& t)
	{
		Info << "object type: " << t->RegObjTypeName() << endl;
		Info << " - index: " << t->Index() << ", name: " << t->Name() << endl;
	}

	void printValue(const par_t& t)
	{
		Info << " - value: " << t->Value() << endl;
	}

	void printValue(const coord_t& t)
	{
		Info << " - coordinate: " << t->Coord() << endl;
	}

	void printValue(const fieldFun_t& t)
	{
		Info << " - value: " << t->Value() << endl;
	}

	void print(const par_t& t)
	{
		printObj(t);
		printValue(t);
	}

	void print(const fieldFun_t& t)
	{
		printObj(t);
		printValue(t);
	}

	void print(const pnt_t& pt)
	{
		printObj(pt);
		printValue(pt);
	}

	auto getMaster(const pnt_t& p)
	{
		if (NOT p->IsMaster())
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is not master!" << endl
				<< abort(FatalError);
		}
		auto master = std::dynamic_pointer_cast<SectPx_MasterPnt>(p);
		Debug_Null_Pointer(master);
		return std::move(master);
	}

	const auto& getFrame()
	{
		return myFrame;
	}

	const auto & getRegistry()
	{
		return getFrame()->Registry();
	}

	void printFrame()
	{
		getFrame()->PrintRegistry();
	}


	// - makers in the frame:

	const auto& getParameterMaker()
	{
		return getFrame()->ParameterMaker();
	}

	const auto& getPointMaker()
	{
		return getFrame()->PointMaker();
	}

	const auto& getGeometricMapMaker()
	{
		return getFrame()->GeometricMapMaker();
	}

	const auto& getCmpProfileMaker()
	{
		return getFrame()->CmptProfileMaker();
	}

	const auto& getFieldFunMaker()
	{
		return getFrame()->FieldFunMaker();
	}

	//- global functions

	auto nbProfiles()
	{
		return getCmpProfileMaker()->NbProfiles();
	}

	auto getProfile(const int i)
	{
		if (i < 0 OR i >= nbProfiles())
		{
			FatalErrorIn(FunctionSIG)
				<< "index has been exceeded the map" << endl
				<< abort(FatalError);
		}
		const auto& reg = getRegistry();
		const auto& m = reg->ScatterMap(SectPx_RegObjType::profile);
		
		if (m.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "there is no profile in the frame!" << endl
				<< abort(FatalError);
		}

		auto iter = m.begin();
		int k = 0;
		while ((k NOT_EQUAL i) AND (iter NOT_EQUAL m.end()))
		{
			++k;
			iter++;
		}
		auto profile = std::dynamic_pointer_cast<SectPx_TopoProfile>(iter->second.lock());
		Debug_Null_Pointer(profile);
		return std::move(profile);
	}

	const auto& getProfiles()
	{
		return getRegistry()->ScatterMap(SectPx_RegObjType::profile);
	}

	auto drawPlt(const word& name)
	{
		fileName myFileName(name);
		OFstream file(myFileName);

		const auto& profiles = getProfiles();
		for (const auto& x : profiles)
		{
			auto profile = std::dynamic_pointer_cast<SectPx_TopoProfile>(x.second.lock());
			Debug_Null_Pointer(profile);

			auto pnts = profile->RetrieveCoords();
			Io::ExportCurve(pnts, file);
		}
	}

	void saveTo(const word& name)
	{
		std::ofstream myFile(name);
		boost::archive::polymorphic_text_oarchive ar(myFile);
		ar & *getFrame();
	}

	void loadFrom(const word& name)
	{
		std::ifstream myFile(name);
		boost::archive::polymorphic_text_iarchive ar(myFile);
		ar & *getFrame();
	}

	// - default shapes

	void makeSegment(const Pnt2d& p0, const Pnt2d& p1)
	{
		getFrame()->MakeLineSegment(p0, p1);
	}

	void makeCorner(const Pnt2d& p0, const Pnt2d& p1)
	{
		getFrame()->MakeCorner(p0, p1);
	}

	void makeCorner
	(
		const Pnt2d& p0, 
		const Dir2d& d0, 
		const Standard_Real ang0, 
		const Pnt2d& p1, 
		const Dir2d& d1, 
		const Standard_Real ang1
	)
	{
		getFrame()->MakeCorner(p0, d0, ang0, p1, d1, ang1);
	}

	void makeUShape(const Pnt2d& p0, const Pnt2d& p1, const Standard_Real w)
	{
		getFrame()->MakeUShape(p0, p1, w);
	}

	// - create the profiles

	auto createCustomProfile(const cmpPrfMaker_t& m, const pnt_t& p0, const pnt_t& p1)
	{
		auto t = m->SelectProfile(m->CreateCustomProfile(p0, p1));
		return std::move(t);
	}

	auto createInterplProfile(const cmpPrfMaker_t& m, const cloud_t& c)
	{
		auto t = m->SelectProfile(m->CreateInterplProfile(c));
		return std::move(t);
	}


	// - modify a profile

	auto selectEdge(const profile_t& m, const Standard_Integer id)
	{
		auto t = m->SelectEdge(id);
		return std::move(t);
	}

	auto importPnt(const profile_t& m, const pnt_t& p, const edge_t& ed)
	{
		auto t = m->ImportPnt(p, ed);
		return std::move(t);
	}

	void removePnt(const profile_t& m, const pnt_t& p)
	{
		m->RemovePnt(p);
	}


	//- parameters: 

	auto createFree(const parMaker_t& m, const fieldFun_t& f)
	{
		auto t = std::dynamic_pointer_cast<SectPx_FreePar>(m->SelectParameter(m->CreateFree(f)));
		return std::move(t);
	}

	auto createFree(const parMaker_t& m, const word& name, const fieldFun_t& f)
	{
		auto t = std::dynamic_pointer_cast<SectPx_FreePar>(m->SelectParameter(m->CreateFree(name, f)));
		return std::move(t);
	}

	auto createFixed(const parMaker_t& m, const double x)
	{
		auto t = std::dynamic_pointer_cast<SectPx_FixedPar>(m->SelectParameter(m->CreateFixed(x)));
		return std::move(t);
	}

	auto createFixed(const parMaker_t& m, const word& name, const double x)
	{
		auto t = std::dynamic_pointer_cast<SectPx_FixedPar>(m->SelectParameter(m->CreateFixed(name, x)));
		return std::move(t);
	}

	auto createConstant(const parMaker_t& m, const double x)
	{
		auto t = std::dynamic_pointer_cast<SectPx_ConstPar>(m->SelectParameter(m->CreateConstant(x)));
		return std::move(t);
	}

	auto createConstant(const parMaker_t& m, const word& name, const double x)
	{
		auto t = std::dynamic_pointer_cast<SectPx_ConstPar>(m->SelectParameter(m->CreateConstant(name, x)));
		return std::move(t);
	}

	void removePar(const parMaker_t& m, const par_t& p)
	{
		auto t = m->RemoveParameter(p->Index());
		Debug_If_Condition(t NOT_EQUAL p);
	}

	/*par_t selectPar(const parMaker_t& m, const int id)
	{
		auto t = m->SelectParameter(id);
		return std::move(t);
	}*/

	auto createUniform(const fieldMaker_t& m, const par_t& p)
	{
		auto t = m->SelectFieldFun(m->CreateUniform(p));
		return std::move(t);
	}

	auto createMinus(const fieldMaker_t& m, const par_t& p)
	{
		auto t = m->SelectFieldFun(m->CreateInverse(p));
		return std::move(t);
	}

	auto createRead_x(const fieldMaker_t& m, const coord_t& pt)
	{
		auto t = m->SelectFieldFun(m->CreateReadingX(pt));
		return std::move(t);
	}

	auto createRead_y(const fieldMaker_t& m, const coord_t& pt)
	{
		auto t = m->SelectFieldFun(m->CreateReadingY(pt));
		return std::move(t);
	}

	auto createLinearForm(const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1, const par_t& t)
	{
		auto tt = m->SelectFieldFun(m->CreateLinearForm(f0, f1, t));
		return std::move(tt);
	}

	auto createExpr(const fieldMaker_t& m, const word& ex)
	{
		auto t = std::dynamic_pointer_cast<sectPxLib::FieldFun_Expr>(m->SelectFieldFun(m->CreateExpression(ex)));
		return std::move(t);
	}

	/* point maker methods*/

	auto createOuterComponent(const pntMaker_t& m, const par_t& x, const par_t& y)
	{
		auto t = m->SelectPnt(m->CreateOuterComponent(x, y));
		return std::move(t);
	}

	auto createInnerComponent(const pntMaker_t& m, const par_t& x, const par_t& y)
	{
		auto t = m->SelectPnt(m->CreateInnerComponent(x, y));
		return std::move(t);
	}

	auto createOuterOffset(const pntMaker_t& m, const Standard_Real x, const Standard_Real y)
	{
		auto t = m->SelectPnt(m->CreateOuterOffset(x, y));
		return std::move(t);
	}

	auto createOuterOffset(const pntMaker_t& m, const Pnt2d& p)
	{
		auto t = m->SelectPnt(m->CreateOuterOffset(p));
		return std::move(t);
	}

	auto createInnerOffset(const pntMaker_t& m, const Standard_Real x, const Standard_Real y)
	{
		auto t = m->SelectPnt(m->CreateInnerOffset(x, y));
		return std::move(t);
	}

	auto createInnerOffset(const pntMaker_t& m, const Pnt2d& p)
	{
		auto t = m->SelectPnt(m->CreateInnerOffset(p));
		return std::move(t);
	}

	auto createField(const pntMaker_t& m, const geoMap_t& g)
	{
		auto t = m->SelectPnt(m->CreateField(g));
		return std::move(t);
	}

	auto createEmpty(const pntMaker_t& m, const mastPnt_t& p)
	{
		auto t = m->SelectPnt(m->CreateEmpty(p));
		return std::move(t);
	}


	/*geometric map maker*/

	auto createLinearIntrpl(const geoMaker_t& m, const coord_t& q0, const coord_t& q1, const par_t& p)
	{
		auto t = m->SelectGeoMap(m->CreateLinearInterpolation(q0, q1, p));
		return std::move(t);
	}

	auto createIntersection(const geoMaker_t& m, const coord_t& q0, const Dir2d& d0, const par_t& ang0, const coord_t& q1, const Dir2d& d1, const par_t& ang1)
	{
		auto t = m->SelectGeoMap(m->CreateIntersection(q0, d0, ang0, q1, d1, ang1));
		return std::move(t);
	}

	/*fieldFun_t selectField(const fieldMaker_t& m, const int id)
	{
		auto f = m->SelectFieldFun(id);
		return std::move(f);
	}*/

	void removeField(const fieldMaker_t& m, const fieldFun_t& f)
	{
		auto item = m->RemoveFieldFun(f->Index());
		Debug_If_Condition(item NOT_EQUAL f);
	}

	void addVariable(const exprField_t& f, const word& name, double& x)
	{
		f->AddVariable(name, x);
	}

	void addVariable(const exprField_t& f, const word& name, const fieldFun_t& x)
	{
		f->AddVariable(name, *x);
	}

	void addVariable(const exprField_t& f, const word& name, const fixed_t& x)
	{
		f->AddVariable(name, *x);
	}

	void addConstant(const exprField_t& f, const word& name, const double& x)
	{
		f->AddConstant(name, x);
	}

	void addConstant(const exprField_t& f, const word& name, const const_t& x)
	{
		f->AddConstant(name, *x);
	}

	void removeVariable(const exprField_t& f, const word& name)
	{
		f->RemoveVariable(name);
	}

	void print(const frame_t& f)
	{
		f->PrintRegistry();
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setTypes(const module_t& mod)
	{
		mod->add(chaiscript::user_type<SectPx_Frame>(), "frame");
		mod->add(chaiscript::user_type<maker::Parameter>(), "paramMaker");
		mod->add(chaiscript::user_type<maker::FieldFun>(), "fieldFunMaker");

		mod->add(chaiscript::user_type<SectPx_FixedPar>(), "fixedPar");
		mod->add(chaiscript::user_type<SectPx_FreePar>(), "freePar");
		mod->add(chaiscript::user_type<SectPx_ConstPar>(), "constPar");
		mod->add(chaiscript::user_type<SectPx_Par>(), "par");

		mod->add(chaiscript::user_type<Pnt2d>(), "gPoint");
	}

	void setParameters(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const parMaker_t& m, const fieldFun_t& f)-> auto {auto t = createFree(m, f); return std::move(t); }), "createFree");
		mod->add(chaiscript::fun([](const parMaker_t& m, const std::string& name, const fieldFun_t& f)-> auto {auto t = createFree(m, name, f); return std::move(t); }), "createFree");
		mod->add(chaiscript::fun([](const parMaker_t& m, const double x)-> auto {auto t = createFixed(m, x); }), "createFixed");
		mod->add(chaiscript::fun([](const parMaker_t& m, const std::string& name, const double x)-> auto {auto t = createFixed(m, name, x); return std::move(t); }), "createFixed");
		mod->add(chaiscript::fun([](const parMaker_t& m, const double x)-> auto {auto t = createConstant(m, x); return std::move(t); }), "createConstant");
		mod->add(chaiscript::fun([](const parMaker_t& m, const std::string& name, const double x)-> auto {auto t = createConstant(m, name, x); return std::move(t); }), "createConstant");
		//mod->add(chaiscript::fun([](const parMaker_t& m, const par_t& p)-> void {removePar(m, p); }), "remove");
		mod->add(chaiscript::fun([](const parMaker_t& m, const fixed_t& p)-> void {removePar(m, p); }), "remove");
		mod->add(chaiscript::fun([](const parMaker_t& m, const free_t& p)-> void {removePar(m, p); }), "remove");
		mod->add(chaiscript::fun([](const parMaker_t& m, const const_t& p)-> void {removePar(m, p); }), "remove");
	}

	void setField(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const par_t& p)-> auto {auto t = createUniform(m, p); return std::move(t); }), "createUniform");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const par_t& p)-> auto {auto t = createMinus(m, p); return std::move(t); }), "createMinus");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const coord_t& pt)-> auto {auto t = createRead_x(m, pt); return std::move(t); }), "createReadX");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const coord_t& pt)-> auto {auto t = createRead_y(m, pt); return std::move(t); }), "createReadY");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1, const par_t& t)-> auto {auto tt = createLinearForm(m, f0, f1, t); return std::move(tt); }), "createLinearForm");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const std::string& ex)-> auto {auto t = createExpr(m, ex); return std::move(t); }), "createExpr");
	}

	void setPoints(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const pntMaker_t& m, const par_t& x, const par_t& y)-> auto {auto t = createOuterComponent(m, x, y); return std::move(t); }), "createOuterComponent");
		mod->add(chaiscript::fun([](const pntMaker_t& m, const par_t& x, const par_t& y)-> auto {auto t = createInnerComponent(m, x, y); return std::move(t); }), "createInnerComponent");
		mod->add(chaiscript::fun([](const pntMaker_t& m, const Standard_Real x, const Standard_Real y)-> auto {auto t = createOuterOffset(m, x, y); return std::move(t); }), "createOuterOffset");
		mod->add(chaiscript::fun([](const pntMaker_t& m, const Standard_Real x, const Standard_Real y)-> auto {auto t = createInnerOffset(m, x, y); return std::move(t); }), "createInnerOffset");
		mod->add(chaiscript::fun([](const pntMaker_t& m, const Pnt2d& p)-> auto {auto t = createOuterOffset(m, p); return std::move(t); }), "createOuterOffset");
		mod->add(chaiscript::fun([](const pntMaker_t& m, const Pnt2d& p)-> auto {auto t = createInnerOffset(m, p); return std::move(t); }), "createInnerOffset");

		mod->add(chaiscript::fun([](const pntMaker_t& m, const geoMap_t& t)-> auto {auto tt = createField(m, t); return std::move(tt); }), "createField");
		mod->add(chaiscript::fun([](const pntMaker_t& m, const mastPnt_t& p)-> auto {auto t = createEmpty(m, p); return std::move(t); }), "createEmpty");
	}

	void setGeometricMaps(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const geoMaker_t& m, const coord_t& p0, const coord_t& p1, const par_t& p)-> auto{auto t = m->SelectGeoMap(m->CreateLinearInterpolation(p0, p1, p)); return std::move(t); }), "createLinearInterpl");
		mod->add(chaiscript::fun([](const geoMaker_t& m, const coord_t& p0, const Dir2d& d0, const par_t& ang0, const coord_t& p1, const Dir2d& d1, const par_t& ang1)-> auto {auto t = m->SelectGeoMap(m->CreateIntersection(p0, d0, ang0, p1, d1, ang1)); return std::move(t); }), "createIntersection");
		mod->add(chaiscript::fun([](const geoMaker_t& m, const geoMap_t& g)-> void {m->RemoveGeoMap(g->Index()); }), "remove");
	}

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()-> const auto& {return getParameterMaker(); }), "getParameterMaker");
		mod->add(chaiscript::fun([]()-> const auto& {return getFieldFunMaker(); }), "getFieldFunMaker");
		mod->add(chaiscript::fun([]()-> const auto& {return getRegistry(); }), "getRegistry");

		mod->add(chaiscript::fun([](const fixed_t& p)-> auto {return getPar(p); }), "getParameter");
		mod->add(chaiscript::fun([](const pnt_t& p)-> auto {auto t = getMaster(p); return std::move(t); }), "getMaster");

		mod->add(chaiscript::fun([](const par_t& t)-> void {print(t); }), "print");
		mod->add(chaiscript::fun([](const fieldFun_t& t)-> void {print(t); }), "print");
		mod->add(chaiscript::fun([](const pnt_t& t)-> void {print(t); }), "print");

		mod->add(chaiscript::fun([]()-> void {printFrame(); }), "printFrame");

		mod->add(chaiscript::fun([]()-> auto {return nbProfiles(); }), "nbProfiles");

		//- drawing
		mod->add(chaiscript::fun([](const std::string& s)->void {drawPlt(s); }), "exportToPlt");

		//- predefined shapes
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> void {makeSegment(p0, p1); }), "makeSegment");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> void {makeCorner(p0, p1); }), "makeCorner");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Dir2d& d0, const double ang0, const Pnt2d& p1, const Dir2d& d1, const double ang1)-> void {makeCorner(p0, d0, ang0, p1, d1, ang1); }), "makeCorner");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const double w)-> void {makeUShape(p0, p1, w); }), "makeUShape");

		//- create geometric point
		mod->add(chaiscript::fun([](const double x, const double y)-> auto {return Pnt2d(x, y); }), "createGeoPoint");

		//- serialization
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFrom(name); }), "loadFrom");
	}

	/*void setFrame(const module_t& mod)
	{
		mod->add(chaiscript::fun([]() {auto t = std::make_shared<SectPx_Frame>(); return std::move(t); }), "newFrame");
		mod->add(chaiscript::fun([](const frame_t& f)-> void {print(f); }), "print");
		mod->add(chaiscript::fun([](const frame_t& f)-> auto {return f->ParameterMaker(); }), "getParamMaker");
		mod->add(chaiscript::fun([](const frame_t& f)-> auto {return f->FieldFunMaker(); }), "getFieldFunMaker");
	}*/

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

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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

			setTypes(mod);
			setGlobals(mod);
			setParameters(mod);
			setField(mod);

			chai.add(mod);

			fileName myFileName("frameMaker");

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

	return 0;
}