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
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <frameMaker.hxx>

namespace tnbLib
{

	static std::shared_ptr<SectPx_Registry> myRegistry;
	static std::shared_ptr<SectPx_Frame> myFrame;
	static std::shared_ptr<SectPx_ScatterRegistry> scatterReg;

	static appl::edge_t firstEdge;

	static appl::profileMaker_t myThickness;

	static size_t verbose = 0;
	static bool loaded = false;

	void checkFrame()
	{
		if (NOT loaded)
		{
			FatalErrorIn(FunctionSIG)
				<< "no frame has been loaded" << endl
				<< abort(FatalError);
		}
	}

	const auto& getScatterReg()
	{
		checkFrame();
		return myFrame->ParRegistry()->Scatter();
	}

	void loadFrame(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);

		boost::archive::polymorphic_text_iarchive oa(f);

		oa >> myRegistry;
		if (NOT myRegistry)
		{
			FatalErrorIn(FunctionSIG)
				<< " the registry is null" << endl
				<< abort(FatalError);
		}

		if (myRegistry->NbFrames() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< " it's not a valid registry" << endl
				<< abort(FatalError);
		}

		oa >> myFrame;
		if (NOT myFrame)
		{
			FatalErrorIn(FunctionSIG)
				<< " the frame registry is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the frame has been loaded successfully!" << endl;
			Info << endl;
		}

		if (NOT myFrame)
		{
			FatalErrorIn(FunctionSIG)
				<< "no frame has been detected" << endl
				<< abort(FatalError);
		}
		if (NOT myFrame->FrameRegistry())
		{
			FatalErrorIn(FunctionSIG)
				<< "no registry has been detected for the frame" << endl
				<< abort(FatalError);
		}

		loaded = true;

		scatterReg = myRegistry->Scatter();
	}

	auto commonEdge(const appl::pnt_t& p0, const appl::pnt_t& p1)
	{
		auto t = SectPx_PntTools::CommonEdge(p0, p1);
		return std::move(t);
	}

	//- makers

	const auto& getParameterMaker()
	{
		checkFrame();
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
		checkFrame();
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
		checkFrame();
		return appl::getPointMaker(myFrame);
	}

	const auto& getDatumMaker()
	{
		checkFrame();
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
		checkFrame();
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
		checkFrame();
		return appl::getCmpProfileMaker(myFrame);
	}

	auto createCustomProfile(const appl::pnt_t& p0, const appl::pnt_t& p1)
	{
		if (getProfileMaker()->NbProfiles() > 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "the thickness profile has been already created" << endl
				<< abort(FatalError);
		}

		auto f = appl::createCustomProfile(getProfileMaker(), p0, p1);
		f->SetName("thickness profile");
		firstEdge = commonEdge(p0, p1);
		myThickness = f;
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
		checkFrame();
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
		checkFrame();
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
		checkFrame();
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myRegistry;
		oa << myFrame;
	}

	void drawPlt(const std::string& name)
	{
		checkFrame();
		fileName fn(name);
		OFstream f(fn);

		const auto& profiles = scatterReg->ScatterMap(SectPx_RegObjType::profile);
		for (const auto& x : profiles)
		{
			auto profile = std::dynamic_pointer_cast<SectPx_TopoProfile>(x.second.lock());
			Debug_Null_Pointer(profile);

			if (profile IS_EQUAL myThickness->TopoProfile())
			{
				auto pnts = profile->RetrieveCoords();
				Io::ExportCurve(pnts, f);
			}		
		}
	}

	void printFixedParams()
	{
		checkFrame();
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
		checkFrame();
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

	auto degreeToRad(double x)
	{
		auto r = Geo_Tools::DegToRadian(x);
		return r;
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
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto{auto t = createUniformField(p); return std::move(t); }), "createUniformField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& p)-> auto{auto t = createUniformField(name, p); return std::move(t); }), "createUniformField");
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
		mod->add(chaiscript::fun([](const appl::par_t& x, const appl::par_t& y)-> auto{auto t = createOuterPoint(x, y); return std::move(t); }), "createOuterPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& x, const appl::par_t& y)-> auto{auto t = createOuterPoint(name, x, y); return std::move(t); }), "createOuterPoint");
		mod->add(chaiscript::fun([](const appl::dtm_t& d)-> auto{auto t = createOuterPoint(d); return std::move(t); }), "createOuterPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::dtm_t& d)-> auto{auto t = createOuterPoint(name, d); return std::move(t); }), "createOuterPoint");
		mod->add(chaiscript::fun([](const appl::par_t& x, const appl::par_t& y)-> auto{auto t = createInnerPoint(x, y); return std::move(t); }), "createInnerPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::dtm_t& d)-> auto{auto t = createInnerPoint(name, d); return std::move(t); }), "createInnerPoint");
		mod->add(chaiscript::fun([](const appl::dtm_t& d)-> auto{auto t = createInnerPoint(d); return std::move(t); }), "createInnerPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& x, const appl::par_t& y)-> auto{auto t = createInnerPoint(name, x, y); return std::move(t); }), "createInnerPoint");
		mod->add(chaiscript::fun([](const appl::geoMap_t& g)-> auto{auto t = createFieldPoint(g); return std::move(t); }), "createFieldPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::geoMap_t& g)-> auto{auto t = createFieldPoint(name, g); return std::move(t); }), "createFieldPoint");
		mod->add(chaiscript::fun([](const appl::mastPnt_t& m)-> auto{auto t = createSlavePoint(m); return std::move(t); }), "createSlavePoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::mastPnt_t& m)-> auto{auto t = createSlavePoint(name, m); return std::move(t); }), "createSlavePoint");
		mod->add(chaiscript::fun([](const appl::par_t& x, const appl::par_t& y)-> auto{auto t = createDatum(x, y); return std::move(t); }), "createDatum");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& x, const appl::par_t& y)-> auto{auto t = createDatum(name, x, y); return std::move(t); }), "createDatum");
		mod->add(chaiscript::fun([](const appl::geoMap_t& g)-> auto{auto t = createDatum(g); return std::move(t); }), "createDatum");
		mod->add(chaiscript::fun([](const std::string& name, const appl::geoMap_t& g)-> auto{auto t = createDatum(name, g); return std::move(t); }), "createDatum");

		mod->add(chaiscript::fun([](const appl::dtm_t& p)-> auto{auto t = appl::getCoord(p); return std::move(t); }), "getCoord");
		mod->add(chaiscript::fun([](const appl::pnt_t& p)-> auto{auto t = appl::getCoord(p); return std::move(t); }), "getCoord");
		mod->add(chaiscript::fun([](const appl::coord_t& p)-> auto{auto t = appl::getCoord(p); return std::move(t); }), "getCoord");

		mod->add(chaiscript::fun([](const appl::pnt_t& p)-> auto{auto t = appl::getMaster(p); return std::move(t); }), "getMaster");
	}

	void setGeometrics(const module_t& mod)
	{
		mod->add(chaiscript::fun([](double x, double y)-> auto {auto t = Dir2d(x, y); return std::move(t); }), "createDirection");

		mod->add(chaiscript::fun([](const appl::coord_t& q0, const appl::coord_t& q1, const appl::par_t& p)-> auto{auto t = createLinearInterpl(q0, q1, p); return std::move(t); }), "createLinearInterplGeoMap");
		mod->add(chaiscript::fun([](const std::string& name, const appl::coord_t& q0, const appl::coord_t& q1, const appl::par_t& p)-> auto{auto t = createLinearInterpl(name, q0, q1, p); return std::move(t); }), "createLinearInterplGeoMap");
		mod->add(chaiscript::fun([](const appl::coord_t& q0, const Dir2d& d0, const appl::par_t& ang0, const appl::coord_t& q1, const Dir2d& d1, const appl::par_t& ang1)-> auto{auto t = createIntersection(q0, d0, ang0, q1, d1, ang1); return std::move(t); }), "createIntersectGeoMap");
		mod->add(chaiscript::fun([](const std::string& name, const appl::coord_t& q0, const Dir2d& d0, const appl::par_t& ang0, const appl::coord_t& q1, const Dir2d& d1, const appl::par_t& ang1)-> auto{auto t = createIntersection(name, q0, d0, ang0, q1, d1, ang1); return std::move(t); }), "createIntersectGeoMap");
	}

	void setProfiles(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->const auto& {return firstEdge; }), "getFirstEdge");

		mod->add(chaiscript::fun([](const appl::pnt_t& p0, const appl::pnt_t& p1)-> auto {auto t = createCustomProfile(p0, p1); return std::move(t); }), "createCustomProfile");

		mod->add(chaiscript::fun([](const appl::profileMaker_t& m, int id)-> auto {auto t = appl::selectEdge(m, id); return std::move(t); }), "selectEdge");
		mod->add(chaiscript::fun([](const appl::profileMaker_t& m, const appl::pnt_t& p, const appl::edge_t& ed)-> auto{auto t = appl::importPnt(m, p, ed); return std::move(t); }), "importPoint");
		mod->add(chaiscript::fun([](const std::pair<appl::edge_t, appl::edge_t>& p)->auto {auto t = appl::retrieveLeftEdge(p); return std::move(t); }), "retrieveLeftEdge");
		mod->add(chaiscript::fun([](const std::pair<appl::edge_t, appl::edge_t>& p)->auto {auto t = appl::retrieveRightEdge(p); return std::move(t); }), "retrieveRightEdge");
	}

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()-> void {printReg(); }), "printRegistry");
		mod->add(chaiscript::fun([]()-> void {printFixedParams(); }), "printFixedParameters");
		mod->add(chaiscript::fun([]()-> void {printPoints(); }), "printPoints");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {drawPlt(name); }), "drawPlt");

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFrame(name); }), "loadCamber");

		mod->add(chaiscript::fun([](double x)->auto {return degreeToRad(x); }), "degToRad");

		mod->add(chaiscript::fun([](const unsigned int i)-> void {verbose = i; }), "setVerbose");
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
			setParMakers(mod);
			setFieldMakers(mod);
			setPointMakers(mod);
			setGeometrics(mod);
			setProfiles(mod);

			chai.add(mod);

			fileName myFileName("thicknessProfile");

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