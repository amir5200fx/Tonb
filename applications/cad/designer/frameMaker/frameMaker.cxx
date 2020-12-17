#include "frameMaker.hxx"

#include <TecPlot.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_FieldFuns.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_GeoMap.hxx>
#include <SectPx_Cloud.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_Registry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#define TypeName_APPL typename tnbLib::appl::

//std::shared_ptr<tnbLib::SectPx_Registry> 
//tnbLib::appl::myRegistry = std::make_shared<tnbLib::SectPx_Registry>();

//const TypeName_APPL registry_t &
//tnbLib::appl::getRegistry()
//{
//	return myRegistry;
//}

tnbLib::Pnt2d 
tnbLib::appl::createGeoPoint(double x, double y)
{
	Pnt2d p(x, y);
	return std::move(p);
}

TypeName_APPL par_t
tnbLib::appl::getPar(const fixed_t& p)
{
	return p;
}

TypeName_APPL par_t
tnbLib::appl::getPar(const free_t& p)
{
	return p;
}

TypeName_APPL par_t
tnbLib::appl::getPar(const const_t& p)
{
	return p;
}

TypeName_APPL par_t
tnbLib::appl::getPar(const par_t& p)
{
	return p;
}

TypeName_APPL fixed_t 
tnbLib::appl::getFixedPar(const par_t & p)
{
	auto fixed = std::dynamic_pointer_cast<SectPx_FixedPar>(p);
	if (NOT fixed)
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter's type is not 'fixed'" << endl
			<< "- type: " << p->RegObjTypeName() << endl
			<< abort(FatalError);
	}
	return std::move(fixed);
}

TypeName_APPL free_t 
tnbLib::appl::getFreePar(const par_t & p)
{
	auto free = std::dynamic_pointer_cast<SectPx_FreePar>(p);
	if (NOT free)
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter's type is not 'free'" << endl
			<< "- type: " << p->RegObjTypeName() << endl
			<< abort(FatalError);
	}
	return std::move(free);
}

TypeName_APPL const_t 
tnbLib::appl::getConstPar(const par_t & p)
{
	auto item = std::dynamic_pointer_cast<SectPx_ConstPar>(p);
	if (NOT item)
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter's type is not 'constant'" << endl
			<< "- type: " << p->RegObjTypeName() << endl
			<< abort(FatalError);
	}
	return std::move(item);
}

TypeName_APPL coord_t 
tnbLib::appl::getCoord(const pnt_t & p)
{
	return p;
}

TypeName_APPL coord_t 
tnbLib::appl::getCoord(const coord_t & p)
{
	return p;
}

TypeName_APPL fieldFun_t 
tnbLib::appl::getFieldFun(const exprField_t & f)
{
	return f;
}

TypeName_APPL fieldFun_t 
tnbLib::appl::getFieldFun(const fieldFun_t & f)
{
	return f;
}

TypeName_APPL exprField_t 
tnbLib::appl::getExprField(const fieldFun_t & f)
{
	auto expr = std::dynamic_pointer_cast<sectPxLib::FieldFun_Expr>(f);
	if (NOT expr)
	{
		FatalErrorIn(FunctionSIG)
			<< "the field's type is not 'expression'" << endl
			<< " - type: " << f->RegObjTypeName() << endl
			<< abort(FatalError);
	}
	return std::move(expr);
}

TypeName_APPL mastPnt_t 
tnbLib::appl::getMaster(const pnt_t & p)
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

void tnbLib::appl::printObj(const regObj_t & t)
{
	Info << "object type: " << t->RegObjTypeName() << endl;
	Info << " - index: " << t->Index() << ", name: " << t->Name() << endl;
}

void tnbLib::appl::printValue(const par_t & t)
{
	Info << " - value: " << t->Value() << endl;
}

void tnbLib::appl::printValue(const coord_t & t)
{
	Info << " - coordinate: " << t->Coord() << endl;
}

void tnbLib::appl::printValue(const fieldFun_t & t)
{
	Info << " - value: " << t->Value() << endl;
}

void tnbLib::appl::print(const par_t & t)
{
	printObj(t);
	printValue(t);
}

void tnbLib::appl::print(const fieldFun_t & t)
{
	printObj(t);
	printValue(t);
}

void tnbLib::appl::print(const pnt_t & pt)
{
	printObj(pt);
	printValue(pt);
}

void tnbLib::appl::printFrame(const frame_t& f)
{
	f->PrintRegistry();
}

const TypeName_APPL parMaker_t & 
tnbLib::appl::getParameterMaker(const frame_t& f)
{
	return f->ParameterMaker();
}

const TypeName_APPL pntMaker_t & 
tnbLib::appl::getPointMaker(const frame_t& f)
{
	return f->PointMaker();
}

const TypeName_APPL geoMaker_t & 
tnbLib::appl::getGeometricMapMaker(const frame_t& f)
{
	return f->GeometricMapMaker();
}

const TypeName_APPL cmpPrfMaker_t & 
tnbLib::appl::getCmpProfileMaker(const frame_t& f)
{
	return f->CmptProfileMaker();
}

const TypeName_APPL fieldMaker_t &
tnbLib::appl::getFieldMaker(const frame_t& f)
{
	return f->FieldFunMaker();
}

int tnbLib::appl::nbProfiles(const frame_t& f)
{
	return getCmpProfileMaker(f)->NbProfiles();
}

int tnbLib::appl::nbEdges(const registry_t& reg)
{
	return (int)reg->Scatter()->ScatterMap(SectPx_RegObjType::edge).size();
}

TypeName_APPL profile_t 
tnbLib::appl::getProfile(const registry_t& r, const frame_t& f, int i)
{
	if (i < 0 OR i >= nbProfiles(f))
	{
		FatalErrorIn(FunctionSIG)
			<< "index has been exceeded the map" << endl
			<< abort(FatalError);
	}
	const auto& reg = r;
	const auto& m = reg->Scatter()->ScatterMap(SectPx_RegObjType::profile);

	if (m.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no profile in the frame!" << endl
			<< abort(FatalError);
	}

	auto iter = m.begin();
	int k = 0;
	while ((k NOT_EQUAL i) AND(iter NOT_EQUAL m.end()))
	{
		++k;
		iter++;
	}
	auto profile = std::dynamic_pointer_cast<SectPx_TopoProfile>(iter->second.lock());
	Debug_Null_Pointer(profile);
	return std::move(profile);
}

TypeName_APPL edge_t 
tnbLib::appl::getEdge(const registry_t& r, int i)
{
	if (i < 0 OR i >= nbEdges(r))
	{
		FatalErrorIn(FunctionSIG)
			<< "index has been exceeded the map" << endl
			<< abort(FatalError);
	}
	const auto& reg = r;
	const auto& m = reg->Scatter()->ScatterMap(SectPx_RegObjType::edge);

	if (m.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no edge in the frame!" << endl
			<< abort(FatalError);
	}

	auto iter = m.begin();
	int k = 0;
	while ((k NOT_EQUAL i) AND(iter NOT_EQUAL m.end()))
	{
		++k;
		iter++;
	}

	auto edge = std::dynamic_pointer_cast<SectPx_Edge>(iter->second.lock());
	Debug_Null_Pointer(edge);
	return std::move(edge);
}

const std::map<Standard_Integer, std::weak_ptr<tnbLib::SectPx_RegObj>> &
tnbLib::appl::getProfiles(const registry_t& r)
{
	return r->Scatter()->ScatterMap(SectPx_RegObjType::profile);
}

void tnbLib::appl::drawPlt(const registry_t& r,const std::string& name)
{
	fileName myFileName(name);
	OFstream file(myFileName);

	const auto& profiles = getProfiles(r);
	for (const auto& x : profiles)
	{
		auto profile = std::dynamic_pointer_cast<SectPx_TopoProfile>(x.second.lock());
		Debug_Null_Pointer(profile);

		auto pnts = profile->RetrieveCoords();
		Io::ExportCurve(pnts, file);
	}
}

void tnbLib::appl::saveTo(const std::string& name, const frame_t& f)
{
	std::ofstream myFile(name);
	boost::archive::polymorphic_text_oarchive ar(myFile);
	ar & f;
}

void tnbLib::appl::loadFrom(const std::string& name, frame_t& f)
{
	std::ifstream myFile(name);
	boost::archive::polymorphic_text_iarchive ar(myFile);
	ar & f;
}

void tnbLib::appl::makeSegment(const frame_t& f, const Pnt2d & p0, const Pnt2d & p1)
{
	f->MakeLineSegment(p0, p1);
}

void tnbLib::appl::makeCorner(const frame_t& f, const Pnt2d & p0, const Pnt2d & p1)
{
	f->MakeCorner(p0, p1);
}

void tnbLib::appl::makeCorner
(
	const frame_t& f,
	const Pnt2d & p0, 
	const Dir2d & d0, 
	double ang0,
	const Pnt2d & p1,
	const Dir2d & d1, 
	double ang1
)
{
	f->MakeCorner(p0, d0, ang0, p1, d1, ang1);
}

void tnbLib::appl::makeUShape(const frame_t& f, const Pnt2d & p0, const Pnt2d & p1, double w)
{
	f->MakeUShape(p0, p1, w);
}

TypeName_APPL profileMaker_t
tnbLib::appl::createCustomProfile
(
	const cmpPrfMaker_t & m,
	const pnt_t & p0,
	const pnt_t & p1
)
{
	auto t = m->SelectProfile(m->CreateCustomProfile(p0, p1));
	return std::move(t);
}

TypeName_APPL profileMaker_t 
tnbLib::appl::createInterplProfile
(
	const cmpPrfMaker_t & m, 
	const cloud_t & c
)
{
	auto t = m->SelectProfile(m->CreateInterplProfile(c));
	return std::move(t);
}

TypeName_APPL edge_t 
tnbLib::appl::selectEdge(const profileMaker_t & m, int id)
{
	auto t = m->SelectEdge(id);
	return std::move(t);
}

std::pair<TypeName_APPL edge_t, TypeName_APPL edge_t> 
tnbLib::appl::importPnt(const profileMaker_t & m, const pnt_t & p, const edge_t & ed)
{
	const auto[i0, i1] = m->ImportPnt(p, ed);
	auto e0 = selectEdge(m, i0);
	auto e1 = selectEdge(m, i1);
	auto t = std::make_pair(std::move(e0), std::move(e1));
	return std::move(t);
}

TypeName_APPL edge_t 
tnbLib::appl::retrieveLeftEdge(const std::pair<edge_t, edge_t>& p)
{
	auto t = p.first;
	return std::move(t);
}

TypeName_APPL edge_t 
tnbLib::appl::retrieveRightEdge(const std::pair<edge_t, edge_t>& p)
{
	auto t = p.second;
	return std::move(t);
}

void tnbLib::appl::removePnt(const profileMaker_t & m, const pnt_t & p)
{
	m->RemovePnt(p);
}

TypeName_APPL par_t 
tnbLib::appl::createFree(const parMaker_t & m, const fieldFun_t & f)
{
	auto t = m->SelectParameter(m->CreateFree(f));
	return std::move(t);
}

TypeName_APPL par_t 
tnbLib::appl::createFree(const parMaker_t & m, const word & name, const fieldFun_t & f)
{
	auto t = m->SelectParameter(m->CreateFree(name, f));
	return std::move(t);
}

TypeName_APPL par_t 
tnbLib::appl::createFixed(const parMaker_t & m, double x)
{
	auto t = m->SelectParameter(m->CreateFixed(x));
	return std::move(t);
}

TypeName_APPL par_t 
tnbLib::appl::createFixed(const parMaker_t & m, const word & name, double x)
{
	auto t = m->SelectParameter(m->CreateFixed(name, x));
	return std::move(t);
}

TypeName_APPL par_t 
tnbLib::appl::createConstant(const parMaker_t & m, double x)
{
	auto t = m->SelectParameter(m->CreateConstant(x));
	return std::move(t);
}

TypeName_APPL par_t 
tnbLib::appl::createConstant(const parMaker_t & m, const word & name, double x)
{
	auto t = m->SelectParameter(m->CreateConstant(name, x));
	return std::move(t);
}

void tnbLib::appl::removePar(const parMaker_t & m, const par_t & p)
{
	auto t = m->RemoveParameter(p->Index());
	Debug_If_Condition(t NOT_EQUAL p);
}

TypeName_APPL fieldFun_t 
tnbLib::appl::createUniform(const fieldMaker_t & m, const par_t & p)
{
	auto t = m->SelectFieldFun(m->CreateUniform(p));
	return std::move(t);
}

TypeName_APPL fieldFun_t 
tnbLib::appl::createMinus(const fieldMaker_t & m, const par_t & p)
{
	auto t = m->SelectFieldFun(m->CreateInverse(p));
	return std::move(t);
}

TypeName_APPL fieldFun_t 
tnbLib::appl::createRead_x(const fieldMaker_t & m, const coord_t & pt)
{
	auto t = m->SelectFieldFun(m->CreateReadingX(pt));
	return std::move(t);
}

TypeName_APPL fieldFun_t 
tnbLib::appl::createRead_y(const fieldMaker_t & m, const coord_t & pt)
{
	auto t = m->SelectFieldFun(m->CreateReadingY(pt));
	return std::move(t);
}

TypeName_APPL fieldFun_t 
tnbLib::appl::createLinearForm(const fieldMaker_t & m, const fieldFun_t & f0, const fieldFun_t & f1, const par_t & t)
{
	auto tt = m->SelectFieldFun(m->CreateLinearForm(f0, f1, t));
	return std::move(tt);
}

TypeName_APPL fieldFun_t tnbLib::appl::createExpr(const fieldMaker_t & m, const word & ex)
{
	auto t = m->SelectFieldFun(m->CreateExpression(ex));
	return std::move(t);
}

TypeName_APPL pnt_t 
tnbLib::appl::createOuterComponent(const pntMaker_t & m, const par_t & x, const par_t & y)
{
	auto t = m->SelectPnt(m->CreateOuterComponent(x, y));
	return std::move(t);
}

TypeName_APPL pnt_t 
tnbLib::appl::createInnerComponent(const pntMaker_t & m, const par_t & x, const par_t & y)
{
	auto t = m->SelectPnt(m->CreateInnerComponent(x, y));
	return std::move(t);
}

TypeName_APPL pnt_t 
tnbLib::appl::createOuterOffset(const pntMaker_t & m, double x, double y)
{
	auto t = m->SelectPnt(m->CreateOuterOffset(x, y));
	return std::move(t);
}

TypeName_APPL pnt_t 
tnbLib::appl::createOuterOffset(const pntMaker_t & m, const Pnt2d & p)
{
	auto t = m->SelectPnt(m->CreateOuterOffset(p));
	return std::move(t);
}

TypeName_APPL pnt_t 
tnbLib::appl::createInnerOffset(const pntMaker_t & m, double x, double y)
{
	auto t = m->SelectPnt(m->CreateInnerOffset(x, y));
	return std::move(t);
}

TypeName_APPL pnt_t 
tnbLib::appl::createInnerOffset(const pntMaker_t & m, const Pnt2d & p)
{
	auto t = m->SelectPnt(m->CreateInnerOffset(p));
	return std::move(t);
}

TypeName_APPL pnt_t 
tnbLib::appl::createField(const pntMaker_t & m, const geoMap_t & g)
{
	auto t = m->SelectPnt(m->CreateField(g));
	return std::move(t);
}

TypeName_APPL pnt_t 
tnbLib::appl::createEmpty(const pntMaker_t & m, const mastPnt_t & p)
{
	auto t = m->SelectPnt(m->CreateEmpty(p));
	return std::move(t);
}

TypeName_APPL geoMap_t 
tnbLib::appl::createLinearIntrpl(const geoMaker_t & m, const coord_t & q0, const coord_t & q1, const par_t & p)
{
	auto t = m->SelectGeoMap(m->CreateLinearInterpolation(q0, q1, p));
	return std::move(t);
}

TypeName_APPL geoMap_t 
tnbLib::appl::createIntersection(const geoMaker_t & m, const coord_t & q0, const Dir2d & d0, const par_t & ang0, const coord_t & q1, const Dir2d & d1, const par_t & ang1)
{
	auto t = m->SelectGeoMap(m->CreateIntersection(q0, d0, ang0, q1, d1, ang1));
	return std::move(t);
}

void tnbLib::appl::removeField(const fieldMaker_t & m, const fieldFun_t & f)
{
	auto item = m->RemoveFieldFun(f->Index());
	Debug_If_Condition(item NOT_EQUAL f);
}

void tnbLib::appl::addVariable(const exprField_t & f, const word & name, const fieldFun_t & x)
{
	f->AddVariable(name, x);
}

void tnbLib::appl::removeVariable(const exprField_t & f, const word & name)
{
	f->RemoveVariable(name);
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::appl::frameMaker::setParameters(const module_t & mod)
{
	mod->add(chaiscript::fun([](const parMaker_t& m, const fieldFun_t& f)-> auto {auto t = createFree(m, f); return std::move(t); }), "createFree");
	mod->add(chaiscript::fun([](const parMaker_t& m, const std::string& name, const fieldFun_t& f)-> auto {auto t = createFree(m, name, f); return std::move(t); }), "createFree");
	mod->add(chaiscript::fun([](const parMaker_t& m, const double x)-> auto {auto t = createFixed(m, x); return std::move(t); }), "createFixed");
	mod->add(chaiscript::fun([](const parMaker_t& m, const std::string& name, const double x)-> auto {auto t = createFixed(m, name, x); return std::move(t); }), "createFixed");
	mod->add(chaiscript::fun([](const parMaker_t& m, const double x)-> auto {auto t = createConstant(m, x); return std::move(t); }), "createConstant");
	mod->add(chaiscript::fun([](const parMaker_t& m, const std::string& name, const double x)-> auto {auto t = createConstant(m, name, x); return std::move(t); }), "createConstant");
	mod->add(chaiscript::fun([](const parMaker_t& m, const par_t& p)-> void {removePar(m, p); }), "remove");

	mod->add(chaiscript::fun([](const par_t& p, const std::string& name)-> void {p->SetName(name); }), "setName");

	mod->add(chaiscript::fun([](const double x, const double y)-> auto{auto t = Dir2d(x, y); return std::move(t); }), "makeDir");
}

void tnbLib::appl::frameMaker::setField(const module_t & mod)
{
	mod->add(chaiscript::fun([](const fieldMaker_t& m, const par_t& p)-> auto {auto t = createUniform(m, p); return std::move(t); }), "createUniform");
	mod->add(chaiscript::fun([](const fieldMaker_t& m, const par_t& p)-> auto {auto t = createMinus(m, p); return std::move(t); }), "createMinus");
	mod->add(chaiscript::fun([](const fieldMaker_t& m, const coord_t& pt)-> auto {auto t = createRead_x(m, pt); return std::move(t); }), "createReadX");
	mod->add(chaiscript::fun([](const fieldMaker_t& m, const coord_t& pt)-> auto {auto t = createRead_y(m, pt); return std::move(t); }), "createReadY");
	mod->add(chaiscript::fun([](const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1, const par_t& t)-> auto {auto tt = createLinearForm(m, f0, f1, t); return std::move(tt); }), "createLinearForm");
	mod->add(chaiscript::fun([](const fieldMaker_t& m, const std::string& ex)-> auto {auto t = createExpr(m, ex); return std::move(t); }), "createExpr");

	mod->add(chaiscript::fun([](const fieldFun_t& f, const std::string& name)-> void {f->SetName(name); }), "setName");

	//mod->add(chaiscript::fun([](const exprField_t& f)-> auto {auto t = getFieldFun(f); return std::move(t); }), "getFieldFun");
	//mod->add(chaiscript::fun([](const fieldFun_t& f)-> auto {auto t = getFieldFun(f); return std::move(t); }), "getFieldFun");

	mod->add(chaiscript::fun([](const fieldFun_t& f, const fieldFun_t& x)-> void {addVariable(getExprField(f), x->Name(), x); }), "addVariable");
}

void tnbLib::appl::frameMaker::setPoints(const module_t & mod)
{
	mod->add(chaiscript::fun([](const pntMaker_t& m, const par_t& x, const par_t& y)-> auto {auto t = createOuterComponent(m, x, y); return std::move(t); }), "createOuterComponent");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const par_t& x, const par_t& y)-> auto {auto t = createInnerComponent(m, x, y); return std::move(t); }), "createInnerComponent");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const Standard_Real x, const Standard_Real y)-> auto {auto t = createOuterOffset(m, x, y); return std::move(t); }), "createOuterOffset");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const Standard_Real x, const Standard_Real y)-> auto {auto t = createInnerOffset(m, x, y); return std::move(t); }), "createInnerOffset");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const Pnt2d& p)-> auto {auto t = createOuterOffset(m, p); return std::move(t); }), "createOuterOffset");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const Pnt2d& p)-> auto {auto t = createInnerOffset(m, p); return std::move(t); }), "createInnerOffset");

	mod->add(chaiscript::fun([](const pntMaker_t& m, const geoMap_t& t)-> auto {auto tt = createField(m, t); return std::move(tt); }), "createField");
	mod->add(chaiscript::fun([](const pntMaker_t& m, const mastPnt_t& p)-> auto {auto t = createEmpty(m, p); return std::move(t); }), "createEmpty");

	mod->add(chaiscript::fun([](const pnt_t& p, const std::string& name)-> void {p->SetName(name); }), "setName");
}

void tnbLib::appl::frameMaker::setGeometricMaps(const module_t & mod)
{
	mod->add(chaiscript::fun([](const geoMaker_t& m, const coord_t& p0, const coord_t& p1, const par_t& p)-> auto{auto t = m->SelectGeoMap(m->CreateLinearInterpolation(p0, p1, p)); return std::move(t); }), "createLinearInterpl");
	mod->add(chaiscript::fun([](const geoMaker_t& m, const coord_t& p0, const Dir2d& d0, const par_t& ang0, const coord_t& p1, const Dir2d& d1, const par_t& ang1)-> auto {auto t = m->SelectGeoMap(m->CreateIntersection(p0, d0, ang0, p1, d1, ang1)); return std::move(t); }), "createIntersection");
	mod->add(chaiscript::fun([](const geoMaker_t& m, const geoMap_t& g)-> void {m->RemoveGeoMap(g->Index()); }), "remove");
}

void tnbLib::appl::frameMaker::setProfileMakers(const module_t & mod)
{
	mod->add(chaiscript::fun([](const profileMaker_t& m, const pnt_t& p, const edge_t& e)-> auto {auto t = importPnt(m, p, e); return std::move(t); }), "importPoint");
	mod->add(chaiscript::fun([](const std::pair<edge_t, edge_t>& p)-> auto {auto t = retrieveLeftEdge(p); return std::move(t); }), "retrieveLeftEdge");
	mod->add(chaiscript::fun([](const std::pair<edge_t, edge_t>& p)-> auto {auto t = retrieveRightEdge(p); return std::move(t); }), "retrieveRightEdge");
}

void tnbLib::appl::frameMaker::setGlobals(const module_t & mod)
{
	mod->add(chaiscript::fun([](const frame_t& f)-> const auto& {return getParameterMaker(f); }), "getParameterMaker");
	mod->add(chaiscript::fun([](const frame_t& f)-> const auto& {return getFieldMaker(f); }), "getFieldFunMaker");
	//mod->add(chaiscript::fun([]()-> const auto& {return getRegistry(); }), "getRegistry");
	mod->add(chaiscript::fun([](const frame_t& f)-> const auto& {return getPointMaker(f); }), "getPointMaker");
	mod->add(chaiscript::fun([](const frame_t& f)-> const auto& {return getCmpProfileMaker(f); }), "getCmpProfileMaker");
	mod->add(chaiscript::fun([](const frame_t& f)-> const auto& {return getGeometricMapMaker(f); }), "getGeoMapMaker");

	mod->add(chaiscript::fun([](const par_t& t)-> void {print(t); }), "print");
	mod->add(chaiscript::fun([](const fieldFun_t& t)-> void {print(t); }), "print");
	mod->add(chaiscript::fun([](const pnt_t& t)-> void {print(t); }), "print");

	mod->add(chaiscript::fun([](const frame_t& f)-> void {printFrame(f); }), "printFrame");

	mod->add(chaiscript::fun([](const frame_t& f)-> auto {return nbProfiles(f); }), "nbProfiles");

	mod->add(chaiscript::fun([](const registry_t& r, const int i)-> auto {auto t = getEdge(r, i); return std::move(t); }), "getSeqEdge");

	mod->add(chaiscript::fun([](const pnt_t& p)-> auto {auto t = getCoord(p); return std::move(t); }), "getCoord");
	mod->add(chaiscript::fun([](const coord_t& p)-> auto {auto t = getCoord(p); return std::move(t); }), "getCoord");

	//- profile makers 

	mod->add(chaiscript::fun([](const cmpPrfMaker_t& m, const pnt_t& p0, const pnt_t& p1)-> auto {auto t = createCustomProfile(m, p0, p1); return std::move(t); }), "createCustom");
	mod->add(chaiscript::fun([](const cmpPrfMaker_t& m, const cloud_t& c)-> auto {auto t = createInterplProfile(m, c); return std::move(t); }), "createInterpl");

	//- drawing
	mod->add(chaiscript::fun([](const registry_t& r, const std::string& s)->void {drawPlt(r, s); }), "exportToPlt");

	//- predefined shapes
	mod->add(chaiscript::fun([](const frame_t& f, const Pnt2d& p0, const Pnt2d& p1)-> void {makeSegment(f, p0, p1); }), "makeSegment");
	mod->add(chaiscript::fun([](const frame_t& f, const Pnt2d& p0, const Pnt2d& p1)-> void {makeCorner(f, p0, p1); }), "makeCorner");
	mod->add(chaiscript::fun([](const frame_t& f, const Pnt2d& p0, const Dir2d& d0, const double ang0, const Pnt2d& p1, const Dir2d& d1, const double ang1)-> void {makeCorner(f, p0, d0, ang0, p1, d1, ang1); }), "makeCorner");
	mod->add(chaiscript::fun([](const frame_t& f, const Pnt2d& p0, const Pnt2d& p1, const double w)-> void {makeUShape(f, p0, p1, w); }), "makeUShape");

	//- create geometric point
	mod->add(chaiscript::fun([](const double x, const double y)-> auto {return Pnt2d(x, y); }), "createGeoPoint");

	//- serialization
	mod->add(chaiscript::fun([](const std::string& name, const frame_t& f)-> void {saveTo(name, f); }), "saveTo");
	mod->add(chaiscript::fun([](const std::string& name, frame_t& f)-> void {loadFrom(name, f); }), "loadFrom");
}

std::string 
tnbLib::appl::getString(char * argv)
{
	std::string argument(argv);
	return std::move(argument);
}

bool 
tnbLib::appl::IsEqualCommand(char * argv, const std::string & command)
{
	auto argument = getString(argv);
	return argument IS_EQUAL command;
}