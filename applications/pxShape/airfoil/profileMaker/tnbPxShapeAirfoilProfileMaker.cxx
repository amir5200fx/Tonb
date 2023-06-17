#include <Geo_Tools.hxx>
#include <SectPx_ParRegistry.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_Registry.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_FieldFuns.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_GeoMap.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_Datums.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPxIO_Airfoil.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>

#include <frameMaker.hxx>

namespace tnbLib
{

	static const std::string saveExt = SectPx_Frame::extension;

	static const auto myRegistry = std::make_shared<SectPx_Registry>();

	static std::shared_ptr<SectPx_Frame> myFrame;
	static std::shared_ptr<SectPx_ScatterRegistry> scatterReg;

	static appl::edge_t firstEdge;

	static std::vector<appl::profileMaker_t> myThickness;
	static std::vector<appl::profileMaker_t> myCamber;

	static unsigned short verbose(0);

	auto commonEdge(const appl::pnt_t& p0, const appl::pnt_t& p1)
	{
		auto t = SectPx_PntTools::CommonEdge(p0, p1);
		return std::move(t);
	}

	auto degreeToRad(double x)
	{
		auto r = Geo_Tools::DegToRadian(x);
		return r;
	}

	//- makers

	const auto& getParameterMaker()
	{
		return appl::getParameterMaker(myFrame);
	}

	auto createFixed(double x, double xmin, double xmax)
	{
		auto par = appl::createFixed(getParameterMaker(), x, xmin, xmax);
		return std::move(par);
	}

	auto createFixed(const std::string& name, double x, double xmin, double xmax)
	{
		auto par = appl::createFixed(getParameterMaker(), name, x, xmin, xmax);
		return std::move(par);
	}

	auto createConstant(double x)
	{
		auto par = appl::createConstant(getParameterMaker(), x);
		return std::move(par);
	}

	auto createConstant(const std::string& name, double x)
	{
		auto par = appl::createConstant(getParameterMaker(), name, x);
		return std::move(par);
	}

	auto createFree(const appl::fieldFun_t& f)
	{
		auto par = appl::createFree(getParameterMaker(), f);
		return std::move(par);
	}

	auto createFree(const std::string& name, const appl::fieldFun_t& f)
	{
		auto par = appl::createFree(getParameterMaker(), name, f);
		return std::move(par);
	}

	//- field functions

	const auto& getFieldMaker()
	{
		return appl::getFieldMaker(myFrame);
	}

	auto createUniformField(const appl::par_t& p)
	{
		auto f = appl::createUniform(getFieldMaker(), p);
		return std::move(f);
	}

	auto createUniformField(const std::string& name, const appl::par_t& p)
	{
		auto f = appl::createUniform(getFieldMaker(), p);
		f->SetName(name);
		return std::move(f);
	}

	auto createMinusField(const appl::par_t& p)
	{
		auto f = appl::createMinus(getFieldMaker(), p);
		return std::move(f);
	}

	auto createMinusField(const std::string& name, const appl::par_t& p)
	{
		auto f = appl::createMinus(getFieldMaker(), p);
		f->SetName(name);
		return std::move(f);
	}

	auto createXReaderField(const appl::coord_t& pt)
	{
		auto f = appl::createRead_x(getFieldMaker(), pt);
		return std::move(f);
	}

	auto createXReaderField(const std::string& name, const appl::coord_t& pt)
	{
		auto f = appl::createRead_x(getFieldMaker(), pt);
		f->SetName(name);
		return std::move(f);
	}

	auto createYReaderField(const appl::coord_t& pt)
	{
		auto f = appl::createRead_y(getFieldMaker(), pt);
		return std::move(f);
	}

	auto createYReaderField(const std::string& name, const appl::coord_t& pt)
	{
		auto f = appl::createRead_y(getFieldMaker(), pt);
		f->SetName(name);
		return std::move(f);
	}

	auto createLinearFormField(const appl::fieldFun_t& f0, const appl::fieldFun_t& f1, const appl::par_t& p)
	{
		auto f = appl::createLinearForm(getFieldMaker(), f0, f1, p);
		return std::move(f);
	}

	auto createLinearFormField(const std::string& name, const appl::fieldFun_t& f0, const appl::fieldFun_t& f1, const appl::par_t& p)
	{
		auto f = appl::createLinearForm(getFieldMaker(), f0, f1, p);
		f->SetName(name);
		return std::move(f);
	}

	auto createExprField(const std::string& ex)
	{
		auto f = appl::createExpr(getFieldMaker(), ex);
		return std::move(f);
	}

	auto createExprField(const std::string& name, const std::string& ex)
	{
		auto f = appl::createExpr(getFieldMaker(), ex);
		f->SetName(name);
		return std::move(f);
	}

	void addVariable(const appl::exprField_t& f, const std::string& name, const appl::fieldFun_t& x)
	{
		appl::addVariable(f, name, x);
	}

	//- create points

	const auto& getPointMaker()
	{
		return appl::getPointMaker(myFrame);
	}

	const auto& getDatumMaker()
	{
		return appl::getDatumMaker(myFrame);
	}

	auto createOuterPoint(const appl::par_t& x, const appl::par_t& y)
	{
		auto pm = appl::createOuterComponent(getPointMaker(), x, y);
		return std::move(pm);
	}

	auto createOuterPoint(const std::string& name, const appl::par_t& x, const appl::par_t& y)
	{
		auto pm = appl::createOuterComponent(getPointMaker(), x, y);
		pm->SetName(name);
		return std::move(pm);
	}

	auto createOuterPoint(const std::string& name, const appl::dtm_t& d)
	{
		const auto& dtm_name = d->Name();
		auto f0 = createXReaderField(dtm_name + "_xReaderField", d);
		auto f1 = createYReaderField(dtm_name + "_yReaderField", d);

		auto par0 = createFree(f0->Name() + "_par", f0);
		auto par1 = createFree(f1->Name() + "_par", f1);

		auto pm = appl::createOuterComponent(getPointMaker(), par0, par1);
		pm->SetName(name);
		return std::move(pm);
	}

	auto createOuterPoint(const appl::dtm_t& d)
	{
		const auto& dtm_name = d->Name();
		auto f0 = createXReaderField(dtm_name + "_xReaderField", d);
		auto f1 = createYReaderField(dtm_name + "_yReaderField", d);

		auto par0 = createFree(f0->Name() + "_par", f0);
		auto par1 = createFree(f1->Name() + "_par", f1);

		auto pm = appl::createOuterComponent(getPointMaker(), par0, par1);
		return std::move(pm);
	}

	auto createInnerPoint(const appl::par_t& x, const appl::par_t& y)
	{
		auto pm = appl::createInnerComponent(getPointMaker(), x, y);
		return std::move(pm);
	}

	auto createInnerPoint(const std::string& name, const appl::par_t& x, const appl::par_t& y)
	{
		auto pm = appl::createInnerComponent(getPointMaker(), x, y);
		pm->SetName(name);
		return std::move(pm);
	}

	auto createInnerPoint(const std::string& name, const appl::dtm_t& d)
	{
		const auto& dtm_name = d->Name();
		auto f0 = createXReaderField(dtm_name + "_xReaderField", d);
		auto f1 = createYReaderField(dtm_name + "_yReaderField", d);

		auto par0 = createFree(f0->Name() + "_par", f0);
		auto par1 = createFree(f1->Name() + "_par", f1);

		auto pm = appl::createInnerComponent(getPointMaker(), par0, par1);
		pm->SetName(name);
		return std::move(pm);
	}

	auto createInnerPoint(const appl::dtm_t& d)
	{
		const auto& dtm_name = d->Name();
		auto f0 = createXReaderField(dtm_name + "_xReaderField", d);
		auto f1 = createYReaderField(dtm_name + "_yReaderField", d);

		auto par0 = createFree(f0->Name() + "_par", f0);
		auto par1 = createFree(f1->Name() + "_par", f1);

		auto pm = appl::createInnerComponent(getPointMaker(), par0, par1);
		return std::move(pm);
	}

	auto createFieldPoint(const appl::geoMap_t& g)
	{
		auto pm = appl::createField(getPointMaker(), g);
		return std::move(pm);
	}

	auto createFieldPoint(const std::string& name, const appl::geoMap_t& g)
	{
		auto pm = appl::createField(getPointMaker(), g);
		pm->SetName(name);
		return std::move(pm);
	}

	auto createSlavePoint(const appl::mastPnt_t& m)
	{
		auto pm = appl::createEmpty(getPointMaker(), m);
		return std::move(pm);
	}

	auto createSlavePoint(const std::string& name, const appl::mastPnt_t& m)
	{
		auto pm = appl::createEmpty(getPointMaker(), m);
		pm->SetName(name);
		return std::move(pm);
	}

	auto createDatum(const appl::par_t& x, const appl::par_t& y)
	{
		auto pm = appl::createComponent(getDatumMaker(), x, y);
		return std::move(pm);
	}

	auto createDatum(const std::string& name, const appl::par_t& x, const appl::par_t& y)
	{
		auto pm = appl::createComponent(getDatumMaker(), x, y);
		pm->SetName(name);
		return std::move(pm);
	}

	auto createDatum(const appl::geoMap_t& g)
	{
		auto pm = appl::createField(getDatumMaker(), g);
		return std::move(pm);
	}

	auto createDatum(const std::string& name, const appl::geoMap_t& g)
	{
		auto pm = appl::createField(getDatumMaker(), g);
		pm->SetName(name);
		return std::move(pm);
	}

	//- create geometric map

	const auto& getGeoMaker()
	{
		return appl::getGeometricMapMaker(myFrame);
	}

	auto createLinearInterpl(const appl::coord_t& q0, const appl::coord_t& q1, const appl::par_t& p)
	{
		auto gm = appl::createLinearIntrpl(getGeoMaker(), q0, q1, p);
		return std::move(gm);
	}

	auto createLinearInterpl(const std::string& name, const appl::coord_t& q0, const appl::coord_t& q1, const appl::par_t& p)
	{
		auto gm = appl::createLinearIntrpl(getGeoMaker(), q0, q1, p);
		gm->SetName(name);
		return std::move(gm);
	}

	auto createIntersection(const appl::coord_t& q0, const Dir2d& d0, const appl::par_t& ang0, const appl::coord_t& q1, const Dir2d& d1, const appl::par_t& ang1)
	{
		auto gm = appl::createIntersection(getGeoMaker(), q0, d0, ang0, q1, d1, ang1);
		return std::move(gm);
	}

	auto createIntersection(const std::string& name, const appl::coord_t& q0, const Dir2d& d0, const appl::par_t& ang0, const appl::coord_t& q1, const Dir2d& d1, const appl::par_t& ang1)
	{
		auto gm = appl::createIntersection(getGeoMaker(), q0, d0, ang0, q1, d1, ang1);
		gm->SetName(name);
		return std::move(gm);
	}

	//- profiles

	const auto& getProfileMaker()
	{
		return appl::getCmpProfileMaker(myFrame);
	}

	auto createCustomCamberProfile(const appl::pnt_t& p0, const appl::pnt_t& p1)
	{
		auto f = appl::createCustomProfile(getProfileMaker(), p0, p1);
		f->SetName("camber profile");
		firstEdge = commonEdge(p0, p1);

		myCamber.push_back(f);
		return std::move(f);
	}

	auto createCustomThicknessProfile(const appl::pnt_t& p0, const appl::pnt_t& p1)
	{
		auto f = appl::createCustomProfile(getProfileMaker(), p0, p1);
		f->SetName("thickness profile");
		firstEdge = commonEdge(p0, p1);

		myThickness.push_back(f);
		return std::move(f);
	}

	/*auto createCamberProfile(const std::string& name, const appl::pnt_t& p0, const appl::pnt_t& p1)
	{
		if (getProfileMaker()->NbProfiles())
		{
			FatalErrorIn(FunctionSIG)
				<< "the camber profile has been already created" << endl
				<< abort(FatalError);
		}

		auto f = appl::createCustomProfile(getProfileMaker(), p0, p1);
		f->SetName(name);
		firstEdge = commonEdge(p0, p1);
		return std::move(f);
	}*/

	//- globals

	int nbEdges()
	{
		return (int)scatterReg->ScatterMap(SectPx_RegObjType::edge).size();
	}

	auto getEdge(int i)
	{
		if (NOT nbEdges())
		{
			FatalErrorIn(FunctionSIG)
				<< "there is no edge!" << endl
				<< abort(FatalError);
		}
		if (NOT INSIDE(i, 0, nbEdges() - 1))
		{
			FatalErrorIn(FunctionSIG)
				<< "index has been exceeded the map" << endl
				<< abort(FatalError);
		}
		const auto& m = scatterReg->ScatterMap(SectPx_RegObjType::edge);
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

	void printObj(const std::shared_ptr<SectPx_RegObj>& item)
	{
		Info << "- index: " << item->Index()
			<< ", " << getRegObjTypeName(item->RegObjType())
			<< "'s name: "
			<< "["
			<< item->Name()
			<< "]"
			<< endl;
	}

	void printReg()
	{
		Info << " parameters: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::parameter))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " field functions: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::fieldFun))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " points: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::pnt))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " edges: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::edge))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " profiles: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::profile))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " nodes: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::node))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " datums: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::datum))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " geometric maps: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::geoMap))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " interfaces: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::Interface))
		{
			auto item = x.second.lock();
			printObj(item);
		}
	}

	void saveTo(const std::string& name)
	{
		auto saveObj = std::make_shared<SectPxIO_Airfoil>();
		saveObj->SetRegistry(myRegistry);
		saveObj->SetFrame(myFrame);
		saveObj->SetCamber(myCamber);
		saveObj->SetThickness(myThickness);

		file::CheckExtension(name);

		file::SaveTo(saveObj, name + SectPxIO_Airfoil::extension, verbose);
	}

	void printFixedParams()
	{
		const auto& params = scatterReg->ScatterMap(SectPx_RegObjType::parameter);
		Info << " fixed parameters: " << endl;
		for (const auto& x : params)
		{
			auto par = std::dynamic_pointer_cast<SectPx_FixedPar>(x.second.lock());
			if (par)
			{
				Info << " - " << "index: "
					<< par->Index() << ", "
					<< par->Name() << ", value: "
					<< par->Value()() << endl;
			}
		}
	}

	void printPoints()
	{
		const auto& points = scatterReg->ScatterMap(SectPx_RegObjType::pnt);
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

	void drawCamberPlt(const std::string& name)
	{
		if (myCamber.size())
		{
			fileName fn(name);
			OFstream f(fn);

			for (const auto& x : myCamber)
			{
				auto pnts = x->TopoProfile()->RetrieveCoords();
				Io::ExportCurve(pnts, f);
			}
		}
	}

	void drawThicknessPlt(const std::string& name)
	{
		if (myThickness.size())
		{
			fileName fn(name);
			OFstream f(fn);

			for (const auto& x : myThickness)
			{
				auto pnts = x->TopoProfile()->RetrieveCoords();
				Io::ExportCurve(pnts, f);
			}
		}
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setParMakers(const module_t& mod)
	{
		mod->add(chaiscript::fun([](double x, double xmin, double xmax)->auto {auto t = createFixed(x, xmin, xmax); return std::move(t); }), "createFixed");
		mod->add(chaiscript::fun([](const std::string& name, double x, double xmin, double xmax)->auto {auto t = createFixed(name, x, xmin, xmax); return std::move(t); }), "createFixed");
		mod->add(chaiscript::fun([](double x)->auto {auto t = createConstant(x); return std::move(t); }), "createConstant");
		mod->add(chaiscript::fun([](const std::string& name, double x)->auto {auto t = createConstant(name, x); return std::move(t); }), "createConstant");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {auto t = createFree(f); return std::move(t); }), "createFree");
		mod->add(chaiscript::fun([](const std::string& name, const appl::fieldFun_t& f)->auto {auto t = createFree(name, f); return std::move(t); }), "createFree");

		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto {auto t = appl::getFixedPar(p); return std::move(t); }), "getFixedPar");
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto {auto t = appl::getFreePar(p); return std::move(t); }), "getFreePar");
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto {auto t = appl::getConstPar(p); return std::move(t); }), "getConstPar");

		mod->add(chaiscript::fun([](const appl::fixed_t& p)-> auto {auto t = appl::getPar(p); return std::move(t); }), "getPar");
		mod->add(chaiscript::fun([](const appl::free_t& p)-> auto {auto t = appl::getPar(p); return std::move(t); }), "getPar");
		mod->add(chaiscript::fun([](const appl::const_t& p)-> auto {auto t = appl::getPar(p); return std::move(t); }), "getPar");
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto {auto t = appl::getPar(p); return std::move(t); }), "getPar");
	}

	void setFieldMakers(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto {auto t = createUniformField(p); return std::move(t); }), "createUniformField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& p)-> auto {auto t = createUniformField(name, p); return std::move(t); }), "createUniformField");
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto {auto t = createMinusField(p); return std::move(t); }), "createMinusField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& p)-> auto {auto t = createMinusField(name, p); return std::move(t); }), "createMinusField");
		mod->add(chaiscript::fun([](const appl::coord_t& pt)-> auto {auto t = createXReaderField(pt); return std::move(t); }), "createXReaderField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::coord_t& pt)-> auto {auto t = createXReaderField(name, pt); return std::move(t); }), "createXReaderField");
		mod->add(chaiscript::fun([](const appl::coord_t& pt)-> auto {auto t = createYReaderField(pt); return std::move(t); }), "createYReaderField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::coord_t& pt)-> auto {auto t = createYReaderField(name, pt); return std::move(t); }), "createYReaderField");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f0, const appl::fieldFun_t& f1, const appl::par_t& p)-> auto {auto t = createLinearFormField(f0, f1, p); return std::move(t); }), "createLinearFormField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::fieldFun_t& f0, const appl::fieldFun_t& f1, const appl::par_t& p)-> auto {auto t = createLinearFormField(name, f0, f1, p); return std::move(t); }), "createLinearFormField");
		mod->add(chaiscript::fun([](const std::string& ex)-> auto {auto t = createExprField(ex); return std::move(t); }), "createExprField");
		mod->add(chaiscript::fun([](const std::string& name, const std::string& ex)-> auto {auto t = createExprField(name, ex); return std::move(t); }), "createExprField");

		mod->add(chaiscript::fun([](const appl::exprField_t& f)->auto {auto t = appl::getFieldFun(f); return std::move(t); }), "getFieldFun");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {auto t = appl::getFieldFun(f); return std::move(t); }), "getFieldFun");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {auto t = appl::getExprField(f); return std::move(t); }), "getExprFieldFun");

		mod->add(chaiscript::fun([](const appl::exprField_t& f, const std::string& name, const appl::fieldFun_t& x)-> void {addVariable(f, name, x); }), "addVariable");
	}

	void setPointMakers(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const appl::par_t& x, const appl::par_t& y)-> auto {auto t = createOuterPoint(x, y); return std::move(t); }), "createOuterPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& x, const appl::par_t& y)-> auto {auto t = createOuterPoint(name, x, y); return std::move(t); }), "createOuterPoint");
		mod->add(chaiscript::fun([](const appl::dtm_t& d)-> auto {auto t = createOuterPoint(d); return std::move(t); }), "createOuterPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::dtm_t& d)-> auto {auto t = createOuterPoint(name, d); return std::move(t); }), "createOuterPoint");
		mod->add(chaiscript::fun([](const appl::par_t& x, const appl::par_t& y)-> auto {auto t = createInnerPoint(x, y); return std::move(t); }), "createInnerPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::dtm_t& d)-> auto {auto t = createInnerPoint(name, d); return std::move(t); }), "createInnerPoint");
		mod->add(chaiscript::fun([](const appl::dtm_t& d)-> auto {auto t = createInnerPoint(d); return std::move(t); }), "createInnerPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& x, const appl::par_t& y)-> auto {auto t = createInnerPoint(name, x, y); return std::move(t); }), "createInnerPoint");
		mod->add(chaiscript::fun([](const appl::geoMap_t& g)-> auto {auto t = createFieldPoint(g); return std::move(t); }), "createFieldPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::geoMap_t& g)-> auto {auto t = createFieldPoint(name, g); return std::move(t); }), "createFieldPoint");
		mod->add(chaiscript::fun([](const appl::mastPnt_t& m)-> auto {auto t = createSlavePoint(m); return std::move(t); }), "createSlavePoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::mastPnt_t& m)-> auto {auto t = createSlavePoint(name, m); return std::move(t); }), "createSlavePoint");
		mod->add(chaiscript::fun([](const appl::par_t& x, const appl::par_t& y)-> auto {auto t = createDatum(x, y); return std::move(t); }), "createDatum");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& x, const appl::par_t& y)-> auto {auto t = createDatum(name, x, y); return std::move(t); }), "createDatum");
		mod->add(chaiscript::fun([](const appl::geoMap_t& g)-> auto {auto t = createDatum(g); return std::move(t); }), "createDatum");
		mod->add(chaiscript::fun([](const std::string& name, const appl::geoMap_t& g)-> auto {auto t = createDatum(name, g); return std::move(t); }), "createDatum");

		mod->add(chaiscript::fun([](const appl::dtm_t& p)-> auto {auto t = appl::getCoord(p); return std::move(t); }), "getCoord");
		mod->add(chaiscript::fun([](const appl::pnt_t& p)-> auto {auto t = appl::getCoord(p); return std::move(t); }), "getCoord");
		mod->add(chaiscript::fun([](const appl::coord_t& p)-> auto {auto t = appl::getCoord(p); return std::move(t); }), "getCoord");

		mod->add(chaiscript::fun([](const appl::pnt_t& p)-> auto {auto t = appl::getMaster(p); return std::move(t); }), "getMaster");
	}

	void setGeometrics(const module_t& mod)
	{
		mod->add(chaiscript::fun([](double x, double y)-> auto {auto t = Dir2d(x, y); return std::move(t); }), "createDirection");

		mod->add(chaiscript::fun([](const appl::coord_t& q0, const appl::coord_t& q1, const appl::par_t& p)-> auto {auto t = createLinearInterpl(q0, q1, p); return std::move(t); }), "createLinearInterplGeoMap");
		mod->add(chaiscript::fun([](const std::string& name, const appl::coord_t& q0, const appl::coord_t& q1, const appl::par_t& p)-> auto {auto t = createLinearInterpl(name, q0, q1, p); return std::move(t); }), "createLinearInterplGeoMap");
		mod->add(chaiscript::fun([](const appl::coord_t& q0, const Dir2d& d0, const appl::par_t& ang0, const appl::coord_t& q1, const Dir2d& d1, const appl::par_t& ang1)-> auto {auto t = createIntersection(q0, d0, ang0, q1, d1, ang1); return std::move(t); }), "createIntersectGeoMap");
		mod->add(chaiscript::fun([](const std::string& name, const appl::coord_t& q0, const Dir2d& d0, const appl::par_t& ang0, const appl::coord_t& q1, const Dir2d& d1, const appl::par_t& ang1)-> auto {auto t = createIntersection(name, q0, d0, ang0, q1, d1, ang1); return std::move(t); }), "createIntersectGeoMap");
	}

	void setProfiles(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->const auto& {return firstEdge; }), "getFirstEdge");

		mod->add(chaiscript::fun([](const appl::pnt_t& p0, const appl::pnt_t& p1)-> auto {auto t = createCustomCamberProfile(p0, p1); return std::move(t); }), "createCustomCamberProfile");
		mod->add(chaiscript::fun([](const appl::pnt_t& p0, const appl::pnt_t& p1)-> auto {auto t = createCustomThicknessProfile(p0, p1); return std::move(t); }), "createCustomThicknessProfile");

		mod->add(chaiscript::fun([](const appl::profileMaker_t& m, int id)-> auto {auto t = appl::selectEdge(m, id); return std::move(t); }), "selectEdge");
		mod->add(chaiscript::fun([](const appl::profileMaker_t& m, const appl::pnt_t& p, const appl::edge_t& ed)-> auto {auto t = appl::importPnt(m, p, ed); return std::move(t); }), "importPoint");
		mod->add(chaiscript::fun([](const std::pair<appl::edge_t, appl::edge_t>& p)->auto {auto t = appl::retrieveLeftEdge(p); return std::move(t); }), "retrieveLeftEdge");
		mod->add(chaiscript::fun([](const std::pair<appl::edge_t, appl::edge_t>& p)->auto {auto t = appl::retrieveRightEdge(p); return std::move(t); }), "retrieveRightEdge");
	}

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()-> void {printReg(); }), "printRegistry");
		mod->add(chaiscript::fun([]()-> void {printFixedParams(); }), "printFixedParameters");
		mod->add(chaiscript::fun([]()-> void {printPoints(); }), "printPoints");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {drawCamberPlt(name); }), "drawCamberPlt");
		mod->add(chaiscript::fun([](const std::string& name)-> void {drawThicknessPlt(name); }), "drawThicknessPlt");

		mod->add(chaiscript::fun([](double x)->auto {return degreeToRad(x); }), "degToRad");
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

int main(int argc, char* argv[])
{
	//FatalError.throwExceptions();

	myFrame = std::make_shared<SectPx_Frame>(myRegistry->Parameter(), myRegistry->SelectFrame(myRegistry->CreateFrame()));
	scatterReg = myRegistry->Scatter();

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
			Info << endl;
			Info << " This application is aimed to create a parametric section." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - saveTo(string)" << endl
				<< " - drawPlt(string)" << endl << endl

				<< " # parameters: " << endl << endl
				<< " - [Par] createFixed(string [opt.], value, minValue, maxValue);    - 'string' is the name of the parameter" << endl
				<< " - [Par] createConstant(string [opt.], value);                     - 'string' is the name of the parameter" << endl
				<< " - [Par] createFree(string [opt.], Field);                 - 'string' is the name of the parameter" << endl << endl

				<< " - [Fixed-Par] getFixedPar(Par)" << endl
				<< " - [Free-Par] getFreePar(Par)" << endl
				<< " - [Const-Par] getConstPar(Par)" << endl << endl

				<< " - [Par] getPar(Fixed-Par)" << endl
				<< " - [Par] getPar(Free-Par)" << endl
				<< " - [Par] getPar(Const-Par)" << endl
				<< " - [Par] getPar(Par)" << endl << endl

				<< " # fields: " << endl << endl
				<< " - [Field] createUniformField(name [opt.], Par)" << endl
				<< " - [Field] createMinusField(name [opt.], Par)" << endl
				<< " - [Field] createXReaderField(name [opt.], Coord)" << endl
				<< " - [Field] createYReaderField(name [opt.], Coord)" << endl
				<< " - [Field] createLinearFormField(name [opt.], Field0, Field1, Par)" << endl
				<< " - [Field] createExprField(name [opt.], Expression)" << endl << endl

				<< " - [Field] getFieldFun(ExprField)" << endl
				<< " - [Field] getFieldFun(Field)" << endl
				<< " - [Field] getExprFieldFun(Field)" << endl << endl

				<< " - addVariable(ExprField, name, Field)" << endl
				<< " - addVariable(Field, name, Field)" << endl << endl

				<< " # Point makers: " << endl << endl

				<< " - [Point] createOuterPoint(name [opt.], x, y)" << endl
				<< " - [Point] createOuterPoint(name [opt.], datum)" << endl << endl

				<< " - [Point] createInnerPoint(name [opt.], x, y)" << endl
				<< " - [Point] createInnerPoint(name [opt.], Datum)" << endl << endl

				<< " - [Point] createFieldPoint(name [opt.], GeoMap)" << endl << endl

				<< " - [Point] createSlavePoint(name [opt.], Master)" << endl << endl

				<< " - [Datum] createDatum(name [opt.], x, y)" << endl
				<< " - [Datum] createDatum(name [opt.], geoMap)" << endl << endl

				<< " - [Coord] getCoord(datum)" << endl
				<< " - [Coord] getCoord(point)" << endl
				<< " - [Coord] getCoord(coord)" << endl << endl

				<< " - [Master] getMaster(point)" << endl << endl

				<< " # Geometric operators: " << endl << endl
				<< " - [Dir] createDirection(double x, double y)" << endl
				<< " - [GeoMap] createLinearInterplGeoMap(name [opt.], coord, coord, parameter)" << endl
				<< " - [GeoMap] createIntersectGeoMap(name [opt.], Coord0, Dir0, angle0 [Par], Coord1, Dir1, angle1 [Par])" << endl << endl

				<< " # Profile operators: " << endl << endl
				<< " - [Edge] getFirstEdge()" << endl << endl

				<< " - [Profile] createCustomProfile(name [opt.], Point0, Point1)" << endl << endl

				<< " - [Edge] selectEdge(profileMaker, id)" << endl
				<< " - [<Edge, Edge>] importPoint(Profile, point, Edge); - outputs: pair of the new left edge and the new right edge <edge, edge>;" << endl
				<< " - [Edge] retrieveLeftEdge(<Edge, Edge>)" << endl
				<< " - [Edge] retrieveRightEdge(<Edge, Edge>)" << endl << endl

				<< " # Global functions: " << endl << endl
				<< " - printRegistry()" << endl
				<< " - printFixedParameters()" << endl
				<< " - printPoints()" << endl << endl

				<< " - [double] degToRad(double)" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setParMakers(mod);
			setFieldMakers(mod);
			setPointMakers(mod);
			setGeometrics(mod);
			setProfiles(mod);

			chai.add(mod);

			try
			{
				auto address = file::GetSystemFile("tnbPxShapeAirfoilProfileMaker");
				fileName myFileName(address);

				chai.eval_file(myFileName);
				return 0;
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
	return 0;
}