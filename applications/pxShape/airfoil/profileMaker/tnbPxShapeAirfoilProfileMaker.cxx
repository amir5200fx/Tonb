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

	struct CP
	{
		appl::pnt_t pnt;
	};

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

	auto createSum(const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createAdd(getFieldMaker(), f0, f1);
		return std::move(f);
	}

	auto createSum(const std::string& name, const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createAdd(getFieldMaker(), f0, f1);
		f->SetName(name);
		return std::move(f);
	}

	auto createSubtract(const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createSubtract(getFieldMaker(), f0, f1);
		return std::move(f);
	}

	auto createSubtract(const std::string& name, const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createSubtract(getFieldMaker(), f0, f1);
		f->SetName(name);
		return std::move(f);
	}

	auto createCross(const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createCross(getFieldMaker(), f0, f1);
		return std::move(f);
	}

	auto createCross(const std::string& name, const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createCross(getFieldMaker(), f0, f1);
		f->SetName(name);
		return std::move(f);
	}

	auto createSubdivide(const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createSubdivide(getFieldMaker(), f0, f1);
		return std::move(f);
	}

	auto createSubdivide(const std::string& name, const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createSubdivide(getFieldMaker(), f0, f1);
		f->SetName(name);
		return std::move(f);
	}

	auto createMin(const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createMin(getFieldMaker(), f0, f1);
		return std::move(f);
	}

	auto createMin(const std::string& name, const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createMin(getFieldMaker(), f0, f1);
		f->SetName(name);
		return std::move(f);
	}

	auto createMax(const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createMax(getFieldMaker(), f0, f1);
		return std::move(f);
	}

	auto createMax(const std::string& name, const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)
	{
		auto f = appl::createMax(getFieldMaker(), f0, f1);
		f->SetName(name);
		return std::move(f);
	}

	auto createAbs(const appl::fieldFun_t& f)
	{
		auto field = appl::createAbs(getFieldMaker(), f);
		return std::move(field);
	}

	auto createAbs(const std::string& name, const appl::fieldFun_t& f)
	{
		auto field = appl::createAbs(getFieldMaker(), f);
		field->SetName(name);
		return std::move(field);
	}

	auto createSqrt(const appl::fieldFun_t& f)
	{
		auto field = appl::createSqrt(getFieldMaker(), f);
		return std::move(field);
	}

	auto createSqrt(const std::string& name, const appl::fieldFun_t& f)
	{
		auto field = appl::createSqrt(getFieldMaker(), f);
		field->SetName(name);
		return std::move(field);
	}

	auto createSin(const appl::fieldFun_t& f)
	{
		auto field = appl::createSin(getFieldMaker(), f);
		return std::move(field);
	}

	auto createSin(const std::string& name, const appl::fieldFun_t& f)
	{
		auto field = appl::createSin(getFieldMaker(), f);
		field->SetName(name);
		return std::move(field);
	}

	auto createCos(const appl::fieldFun_t& f)
	{
		auto field = appl::createCos(getFieldMaker(), f);
		return std::move(field);
	}

	auto createCos(const std::string& name, const appl::fieldFun_t& f)
	{
		auto field = appl::createCos(getFieldMaker(), f);
		field->SetName(name);
		return std::move(field);
	}

	auto createTan(const appl::fieldFun_t& f)
	{
		auto field = appl::createTan(getFieldMaker(), f);
		return std::move(field);
	}

	auto createTan(const std::string& name, const appl::fieldFun_t& f)
	{
		auto field = appl::createTan(getFieldMaker(), f);
		field->SetName(name);
		return std::move(field);
	}

	auto createAsin(const appl::fieldFun_t& f)
	{
		auto field = appl::createAsin(getFieldMaker(), f);
		return std::move(field);
	}

	auto createAsin(const std::string& name, const appl::fieldFun_t& f)
	{
		auto field = appl::createAsin(getFieldMaker(), f);
		return std::move(field);
	}

	auto createACos(const appl::fieldFun_t& f)
	{
		auto field = appl::createAcos(getFieldMaker(), f);
		return std::move(field);
	}

	auto createACos(const std::string& name, const appl::fieldFun_t& f)
	{
		auto field = appl::createAcos(getFieldMaker(), f);
		field->SetName(name);
		return std::move(field);
	}

	auto createAtan(const appl::fieldFun_t& f)
	{
		auto field = appl::createAtan(getFieldMaker(), f);
		return std::move(field);
	}

	auto createAtan(const std::string& name, const appl::fieldFun_t& f)
	{
		auto field = appl::createAtan(getFieldMaker(), f);
		field->SetName(name);
		return std::move(field);
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
		CP pm = { appl::createOuterComponent(getPointMaker(), x, y) };
		return std::move(pm);
	}

	auto createOuterPoint(const std::string& name, const appl::par_t& x, const appl::par_t& y)
	{
		CP pm { appl::createOuterComponent(getPointMaker(), x, y) };
		pm.pnt->SetName(name);
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
		return CP{pm};
	}

	auto createOuterPoint(const appl::dtm_t& d)
	{
		const auto& dtm_name = d->Name();
		auto f0 = createXReaderField(dtm_name + "_xReaderField", d);
		auto f1 = createYReaderField(dtm_name + "_yReaderField", d);

		auto par0 = createFree(f0->Name() + "_par", f0);
		auto par1 = createFree(f1->Name() + "_par", f1);

		auto pm = appl::createOuterComponent(getPointMaker(), par0, par1);
		return CP{ pm };
	}

	auto createInnerPoint(const appl::par_t& x, const appl::par_t& y)
	{
		auto pm = appl::createInnerComponent(getPointMaker(), x, y);
		return CP{ pm };
	}

	auto createInnerPoint(const std::string& name, const appl::par_t& x, const appl::par_t& y)
	{
		auto pm = appl::createInnerComponent(getPointMaker(), x, y);
		pm->SetName(name);
		return CP{ pm };
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
		return CP{ pm };
	}

	auto createInnerPoint(const appl::dtm_t& d)
	{
		const auto& dtm_name = d->Name();
		auto f0 = createXReaderField(dtm_name + "_xReaderField", d);
		auto f1 = createYReaderField(dtm_name + "_yReaderField", d);

		auto par0 = createFree(f0->Name() + "_par", f0);
		auto par1 = createFree(f1->Name() + "_par", f1);

		auto pm = appl::createInnerComponent(getPointMaker(), par0, par1);
		return CP{ pm };
	}

	auto createFieldPoint(const appl::geoMap_t& g)
	{
		auto pm = appl::createField(getPointMaker(), g);
		return CP{ pm };
	}

	auto createFieldPoint(const std::string& name, const appl::geoMap_t& g)
	{
		auto pm = appl::createField(getPointMaker(), g);
		pm->SetName(name);
		return CP{ pm };
	}

	auto createSlavePoint(const appl::mastPnt_t& m)
	{
		auto pm = appl::createEmpty(getPointMaker(), m);
		return CP{ pm };
	}

	auto createSlavePoint(const std::string& name, const appl::mastPnt_t& m)
	{
		auto pm = appl::createEmpty(getPointMaker(), m);
		pm->SetName(name);
		return CP{ pm };
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

	auto createCustomThicknessProfile(const std::vector<appl::pnt_t>& pnts)
	{
		if (pnts.size() < 2)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "not enough points has been detected." << endl
				<< abort(FatalError);
		}
		auto pt0 = pnts.at(0);
		auto ptn = pnts.at(pnts.size() - 1);
		auto f = appl::createCustomProfile(getProfileMaker(), pt0, ptn);
		f->SetName("thickness profile");
		firstEdge = commonEdge(pt0, ptn);

		myThickness.push_back(f);
		auto current = firstEdge;
		for (size_t i = 1; i < pnts.size() - 1; i++)
		{
			auto [left, right] = appl::importPnt(f, pnts.at(i), current);
			current = right;
		}
		return f;
	}

	auto createCustomThicknessProfile(const std::vector<CP>& pnts)
	{
		if (pnts.size() < 2)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "not enough points has been detected." << endl
				<< abort(FatalError);
		}
		auto pt0 = pnts.at(0);
		auto ptn = pnts.at(pnts.size() - 1);
		auto f = appl::createCustomProfile(getProfileMaker(), pt0.pnt, ptn.pnt);
		f->SetName("thickness profile");
		firstEdge = commonEdge(pt0.pnt, ptn.pnt);

		myThickness.push_back(f);
		auto current = firstEdge;
		for (size_t i = 1; i < pnts.size() - 1; i++)
		{
			auto [left, right] = appl::importPnt(f, pnts.at(i).pnt, current);
			current = right;
		}
		return f;
	}

	auto createCustomCamberProfile(const std::vector<CP>& pnts)
	{
		if (pnts.size() < 2)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "not enough points has been detected." << endl
				<< abort(FatalError);
		}
		auto pt0 = pnts.at(0);
		auto ptn = pnts.at(pnts.size() - 1);
		auto f = appl::createCustomProfile(getProfileMaker(), pt0.pnt, ptn.pnt);
		f->SetName("camber profile");
		firstEdge = commonEdge(pt0.pnt, ptn.pnt);

		myCamber.push_back(f);
		auto current = firstEdge;
		for (size_t i = 1; i < pnts.size() - 1; i++)
		{
			auto [left, right] = appl::importPnt(f, pnts.at(i).pnt, current);
			current = right;
		}
		return f;
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

	void printCoord(const appl::coord_t& c)
	{
		Info << c->Coord();
	}

	auto getString(const appl::coord_t& c)
	{
		std::stringstream st;
		st << c->Coord();
		return st.str();
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
		size_t k = 0;
		Info << " fixed parameters: " << endl;
		for (const auto& x : params)
		{
			auto par = std::dynamic_pointer_cast<SectPx_FixedPar>(x.second.lock());
			if (par)
			{
				Info << " - " << "index: "
					<< par->Index() << ", par. no. "
					<< ++k << ", "
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

	void message(const std::string& msg)
	{
		std::cout << msg;
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
		mod->add(chaiscript::fun([](double x, double xmin, double xmax)-> auto
		{
			auto t = createFixed(x, xmin, xmax);
			return std::move(t);
		}), "createFixed");
		mod->add(chaiscript::fun([](const std::string& name, double x, double xmin, double xmax)-> auto
		{
			auto t = createFixed(name, x, xmin, xmax);
			return std::move(t);
		}), "createFixed");
		mod->add(chaiscript::fun([](double x)->auto {auto t = createConstant(x); return std::move(t); }), "createConstant");
		mod->add(chaiscript::fun([](const std::string& name, double x)-> auto
		{
			auto t = createConstant(name, x);
			return std::move(t);
		}), "createConstant");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)-> auto
		{
			auto t = createFree(f);
			return std::move(t);
		}), "createFree");
		mod->add(chaiscript::fun([](const std::string& name, const appl::fieldFun_t& f)-> auto
		{
			auto t = createFree(name, f);
			return std::move(t);
		}), "createFree");

		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto
		{
			auto t = appl::getFixedPar(p);
			return std::move(t);
		}), "getFixedPar");
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto
		{
			auto t = appl::getFreePar(p);
			return std::move(t);
		}), "getFreePar");
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto
		{
			auto t = appl::getConstPar(p);
			return std::move(t);
		}), "getConstPar");

		mod->add(chaiscript::fun([](const appl::fixed_t& p)-> auto
		{
			auto t = appl::getPar(p);
			return std::move(t);
		}), "getPar");
		mod->add(chaiscript::fun([](const appl::free_t& p)-> auto
		{
			auto t = appl::getPar(p);
			return std::move(t);
		}), "getPar");
		mod->add(chaiscript::fun([](const appl::const_t& p)-> auto
		{
			auto t = appl::getPar(p);
			return std::move(t);
		}), "getPar");
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto
		{
			auto t = appl::getPar(p);
			return std::move(t);
		}), "getPar");
	}

	void setFieldMakers(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto
		{
			auto t = createUniformField(p);
			return std::move(t);
		}), "createUniformField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& p)-> auto
		{
			auto t = createUniformField(name, p);
			return std::move(t);
		}), "createUniformField");
		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto
		{
			auto t = createMinusField(p);
			return std::move(t);
		}), "createMinusField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& p)-> auto
		{
			auto t = createMinusField(name, p);
			return std::move(t);
		}), "createMinusField");
		mod->add(chaiscript::fun([](const appl::coord_t& pt)-> auto
		{
			auto t = createXReaderField(pt);
			return std::move(t);
		}), "createXReaderField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::coord_t& pt)-> auto
		{
			auto t = createXReaderField(name, pt);
			return std::move(t);
		}), "createXReaderField");
		mod->add(chaiscript::fun([](const appl::coord_t& pt)-> auto
		{
			auto t = createYReaderField(pt);
			return std::move(t);
		}), "createYReaderField");
		mod->add(chaiscript::fun([](const std::string& name, const appl::coord_t& pt)-> auto
		{
			auto t = createYReaderField(name, pt);
			return std::move(t);
		}), "createYReaderField");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f0, const appl::fieldFun_t& f1, const appl::par_t& p)-> auto
		{
			auto t = createLinearFormField(f0, f1, p);
			return std::move(t);
		}), "createLinearFormField");
		mod->add(chaiscript::fun(
			         [](const std::string& name, const appl::fieldFun_t& f0, const appl::fieldFun_t& f1,
			            const appl::par_t& p)-> auto
			         {
				         auto t = createLinearFormField(name, f0, f1, p);
				         return std::move(t);
			         }), "createLinearFormField");
		mod->add(chaiscript::fun([](const std::string& ex)-> auto
		{
			auto t = createExprField(ex);
			return std::move(t);
		}), "createExprField");
		mod->add(chaiscript::fun([](const std::string& name, const std::string& ex)-> auto
		{
			auto t = createExprField(name, ex);
			return std::move(t);
		}), "createExprField");

		mod->add(chaiscript::fun([](const appl::par_t& p)-> auto {return createMinusField(p); }), "-");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)->auto {return createSum(f0, f1); }), "+");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)->auto {return createSubtract(f0, f1); }), "-");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)->auto {return createCross(f0, f1); }), "*");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)-> auto {return createSubdivide(f0, f1); }), "/");

		mod->add(chaiscript::fun([](const appl::par_t& p)->auto {return createUniformField(p); }), "%");
		mod->add(chaiscript::fun([](const appl::fixed_t& p)->auto {return createUniformField(p); }), "%");
		mod->add(chaiscript::fun([](const appl::const_t& p)->auto {return createUniformField(p); }), "%");
		mod->add(chaiscript::fun([](const appl::free_t& p)->auto {return createUniformField(p); }), "%");

		/*mod->add(chaiscript::fun([](const appl::par_t& par, const appl::fieldFun_t& f)->auto {return createSum(createUniformField(par), f); }), "+");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f, const appl::par_t& par)->auto {return createSum(f, createUniformField(par)); }), "+");
		mod->add(chaiscript::fun([](const appl::par_t& par, const appl::fieldFun_t& f)->auto {return createSubtract(createUniformField(par), f); }), "-");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f, const appl::par_t& p)->auto {return createSubtract(f, createUniformField(p)); }), "-");
		mod->add(chaiscript::fun([](const appl::par_t& p, const appl::fieldFun_t& f)->auto {return createCross(createUniformField(p), f); }), "*");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f, const appl::par_t& p)->auto {return createCross(f, createUniformField(p)); }), "*");
		mod->add(chaiscript::fun([](const appl::par_t& p, const appl::fieldFun_t& f)->auto {return createSubdivide(createUniformField(p), f); }), "/");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f, const appl::par_t& p)->auto {return createSubdivide(f, createUniformField(p)); }), "/");
		mod->add(chaiscript::fun([](const appl::par_t& p)->auto {return createAbs(createUniformField(p)); }), "abs");
		mod->add(chaiscript::fun([](const appl::par_t& p)->auto {return createSqrt(createUniformField(p)); }), "sqrt");
		mod->add(chaiscript::fun([](const appl::par_t& p)->auto {return createSin(createUniformField(p)); }), "sin");
		mod->add(chaiscript::fun([](const appl::par_t& p)->auto {return createCos(createUniformField(p)); }), "cos");
		mod->add(chaiscript::fun([](const appl::par_t& p)->auto {return createTan(createUniformField(p)); }), "tan");
		mod->add(chaiscript::fun([](const appl::par_t& p)->auto {return createAsin(createUniformField(p)); }), "asin");
		mod->add(chaiscript::fun([](const appl::par_t& p)->auto {return createACos(createUniformField(p)); }), "acos");
		mod->add(chaiscript::fun([](const appl::par_t& p)->auto {return createAtan(createUniformField(p)); }), "atan");
		mod->add(chaiscript::fun([](const appl::par_t& )))*/

		mod->add(chaiscript::fun([](const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)-> auto
		{
			return createMin(f0, f1);
		}), "min");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f0, const appl::fieldFun_t& f1)-> auto
		{
			return createMax(f0, f1);
		}), "max");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return createAbs(f); }), "abs");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return createSqrt(f); }), "sqrt");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return createSin(f); }), "sin");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return createCos(f); }), "cos");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return createTan(f); }), "tan");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return createAsin(f); }), "asin");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return createACos(f); }), "acos");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return createAtan(f); }), "atan");

		mod->add(chaiscript::fun([](const appl::exprField_t& f)-> auto
		{
			auto t = appl::getFieldFun(f);
			return std::move(t);
		}), "getFieldFun");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)-> auto
		{
			auto t = appl::getFieldFun(f);
			return std::move(t);
		}), "getFieldFun");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)-> auto
		{
			auto t = appl::getExprField(f);
			return std::move(t);
		}), "getExprFieldFun");

		mod->add(chaiscript::fun(
			         [](const appl::exprField_t& f, const std::string& name, const appl::fieldFun_t& x)-> void
			         {
				         addVariable(f, name, x);
			         }), "addVariable");

		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return f->Value(); }), "getValue");
	}

	void setPointMakers(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const appl::par_t& x, const appl::par_t& y)-> auto
		{
			auto t = createOuterPoint(x, y);
			return std::move(t);
		}), "createOuterPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& x, const appl::par_t& y)-> auto
		{
			auto t = createOuterPoint(name, x, y);
			return std::move(t);
		}), "createOuterPoint");
		mod->add(chaiscript::fun([](const appl::dtm_t& d)-> auto
		{
			auto t = createOuterPoint(d);
			return std::move(t);
		}), "createOuterPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::dtm_t& d)-> auto
		{
			auto t = createOuterPoint(name, d);
			return std::move(t);
		}), "createOuterPoint");
		mod->add(chaiscript::fun([](const appl::par_t& x, const appl::par_t& y)-> auto
		{
			auto t = createInnerPoint(x, y);
			return std::move(t);
		}), "createInnerPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::dtm_t& d)-> auto
		{
			auto t = createInnerPoint(name, d);
			return std::move(t);
		}), "createInnerPoint");
		mod->add(chaiscript::fun([](const appl::dtm_t& d)-> auto
		{
			auto t = createInnerPoint(d);
			return std::move(t);
		}), "createInnerPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& x, const appl::par_t& y)-> auto
		{
			auto t = createInnerPoint(name, x, y);
			return std::move(t);
		}), "createInnerPoint");
		mod->add(chaiscript::fun([](const appl::geoMap_t& g)-> auto
		{
			auto t = createFieldPoint(g);
			return std::move(t);
		}), "createFieldPoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::geoMap_t& g)-> auto
		{
			auto t = createFieldPoint(name, g);
			return std::move(t);
		}), "createFieldPoint");
		mod->add(chaiscript::fun([](const appl::mastPnt_t& m)-> auto
		{
			auto t = createSlavePoint(m);
			return std::move(t);
		}), "createSlavePoint");
		mod->add(chaiscript::fun([](const std::string& name, const appl::mastPnt_t& m)-> auto
		{
			auto t = createSlavePoint(name, m);
			return std::move(t);
		}), "createSlavePoint");
		mod->add(chaiscript::fun([](const appl::par_t& x, const appl::par_t& y)-> auto
		{
			auto t = createDatum(x, y);
			return std::move(t);
		}), "createDatum");
		mod->add(chaiscript::fun([](const std::string& name, const appl::par_t& x, const appl::par_t& y)-> auto
		{
			auto t = createDatum(name, x, y);
			return std::move(t);
		}), "createDatum");
		mod->add(chaiscript::fun([](const appl::geoMap_t& g)-> auto
		{
			auto t = createDatum(g);
			return std::move(t);
		}), "createDatum");
		mod->add(chaiscript::fun([](const std::string& name, const appl::geoMap_t& g)-> auto
		{
			auto t = createDatum(name, g);
			return std::move(t);
		}), "createDatum");

		mod->add(chaiscript::fun([](const appl::dtm_t& p)-> auto
		{
			auto t = appl::getCoord(p);
			return std::move(t);
		}), "getCoord");
		mod->add(chaiscript::fun([](const appl::pnt_t& p)-> auto
		{
			auto t = appl::getCoord(p);
			return std::move(t);
		}), "getCoord");
		mod->add(chaiscript::fun([](const CP& p)-> auto
			{
				auto t = appl::getCoord(p.pnt);
				return std::move(t);
			}), "getCoord");
		mod->add(chaiscript::fun([](const appl::coord_t& p)-> auto
		{
			auto t = appl::getCoord(p);
			return std::move(t);
		}), "getCoord");

		mod->add(chaiscript::fun([](const appl::pnt_t& p)-> auto
		{
			auto t = appl::getMaster(p);
			return std::move(t);
		}), "getMaster");
	}

	void setGeometrics(const module_t& mod)
	{
		mod->add(chaiscript::fun([](double x, double y)-> auto
		{
			auto t = Dir2d(x, y);
			return std::move(t);
		}), "createDirection");

		mod->add(chaiscript::fun([](const appl::coord_t& q0, const appl::coord_t& q1, const appl::par_t& p)-> auto
		{
			auto t = createLinearInterpl(q0, q1, p);
			return std::move(t);
		}), "createLinearInterplGeoMap");
		mod->add(chaiscript::fun(
			         [](const std::string& name, const appl::coord_t& q0, const appl::coord_t& q1,
			            const appl::par_t& p)-> auto
			         {
				         auto t = createLinearInterpl(name, q0, q1, p);
				         return std::move(t);
			         }), "createLinearInterplGeoMap");
		mod->add(chaiscript::fun(
			         [](const appl::coord_t& q0, const Dir2d& d0, const appl::par_t& ang0, const appl::coord_t& q1,
			            const Dir2d& d1, const appl::par_t& ang1)-> auto
			         {
				         auto t = createIntersection(q0, d0, ang0, q1, d1, ang1);
				         return std::move(t);
			         }), "createIntersectGeoMap");
		mod->add(chaiscript::fun(
			         [](const std::string& name, const appl::coord_t& q0, const Dir2d& d0, const appl::par_t& ang0,
			            const appl::coord_t& q1, const Dir2d& d1, const appl::par_t& ang1)-> auto
			         {
				         auto t = createIntersection(name, q0, d0, ang0, q1, d1, ang1);
				         return std::move(t);
			         }), "createIntersectGeoMap");
	}

	void setProfiles(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->const auto& {return firstEdge; }), "getFirstEdge");

		mod->add(chaiscript::fun([](const appl::pnt_t& p0, const appl::pnt_t& p1)-> auto
		{
			auto t = createCustomCamberProfile(p0, p1);
			return std::move(t);
		}), "createCustomCamberProfile");
		mod->add(chaiscript::fun([](const appl::pnt_t& p0, const appl::pnt_t& p1)-> auto
		{
			auto t = createCustomThicknessProfile(p0, p1);
			return std::move(t);
		}), "createCustomThicknessProfile");
		mod->add(chaiscript::fun([](const std::vector<CP>& pnts)-> auto
		{
			return createCustomCamberProfile(pnts);
		}), "createCustomCamberProfile");
		mod->add(chaiscript::fun([](const std::vector<CP>& pnts)-> auto
		{
			return createCustomThicknessProfile(pnts);
		}), "createCustomThicknessProfile");

		mod->add(chaiscript::fun([](const appl::profileMaker_t& m, int id)-> auto
		{
			auto t = appl::selectEdge(m, id);
			return std::move(t);
		}), "selectEdge");
		mod->add(chaiscript::fun([](const appl::profileMaker_t& m, const appl::pnt_t& p, const appl::edge_t& ed)-> auto
		{
			auto t = appl::importPnt(m, p, ed);
			return std::move(t);
		}), "importPoint");
		//mod->add(chaiscript::fun([](const std::vector<appl::par_t>& pnts)))
		mod->add(chaiscript::fun([](const std::pair<appl::edge_t, appl::edge_t>& p)-> auto
		{
			auto t = appl::retrieveLeftEdge(p);
			return std::move(t);
		}), "retrieveLeftEdge");
		mod->add(chaiscript::fun([](const std::pair<appl::edge_t, appl::edge_t>& p)-> auto
		{
			auto t = appl::retrieveRightEdge(p);
			return std::move(t);
		}), "retrieveRightEdge");
	}

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()-> void {printReg(); }), "printRegistry");
		mod->add(chaiscript::fun([]()-> void {printFixedParams(); }), "printFixedParameters");
		mod->add(chaiscript::fun([]()-> void {printPoints(); }), "printPoints");
		mod->add(chaiscript::fun([](const appl::coord_t& c)->void {printCoord(c); }), "printCoords");
		mod->add(chaiscript::fun([](const appl::coord_t& c)->auto {return getString(c); }), "getString");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return std::to_string(f->Value()); }), "getString");
		mod->add(chaiscript::fun([](double x)->auto {return std::to_string(x); }), "getString");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->auto {return f->Value(); }), "getValue");
		mod->add(chaiscript::fun([](const appl::fieldFun_t& f)->std::string {return f->Name(); }), "getName");
		mod->add(chaiscript::fun([](const CP& pt)->std::string {return pt.pnt->Name(); }), "getName");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {drawCamberPlt(name); }), "drawCamberPlt");
		mod->add(chaiscript::fun([](const std::string& name)-> void {drawThicknessPlt(name); }), "drawThicknessPlt");

		mod->add(chaiscript::fun([](double x)->auto {return degreeToRad(x); }), "degToRad");
		mod->add(chaiscript::fun([](double x)->auto {return Geo_Tools::RadianToDegree(x); }), "radToDeg");
		mod->add(chaiscript::fun([](const std::string& st)->void {message(st); }), "message");
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

				<< " - [Field] getValue()" << endl << endl

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

				<< " - [Profile] createCustomCamberProfile(name [opt.], Point0, Point1)" << endl
				<< " - [Profile] createCustomThicknessProfile(name [opt.], Point0, Point1)" << endl << endl

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

			// Point
			chai.add(chaiscript::user_type<CP>(), "cp");
			chai.add(chaiscript::constructor<CP()>(), "cp");
			chai.add(chaiscript::constructor<CP(const CP&)>(), "cp");
			chai.add(chaiscript::constructor<CP(CP&&)>(), "cp");

			chai.add(chaiscript::user_type<SectPx_Pnt>(), "cpoint");
			chai.add(chaiscript::user_type<sectPxLib::InnerPnt<sectPxLib::Pnt_Compnt>>(), "pnt_inner_compnt");
			chai.add(chaiscript::user_type<sectPxLib::OuterPnt<sectPxLib::Pnt_Compnt>>(), "pnt_outer_compnt");
			chai.add(chaiscript::user_type<sectPxLib::InnerPnt<sectPxLib::Pnt_GeoField>>(), "pnt_inner_geofield");
			chai.add(chaiscript::user_type<sectPxLib::OuterPnt<sectPxLib::Pnt_GeoField>>(), "pnt_outer_geofield");
			chai.add(chaiscript::user_type<sectPxLib::InnerPnt<sectPxLib::Pnt_Empty>>(), "pnt_inner_empty");
			chai.add(chaiscript::user_type<sectPxLib::OuterPnt<sectPxLib::Pnt_Empty>>(), "pnt_outer_empty");
			chai.add(chaiscript::user_type<sectPxLib::InnerPnt<sectPxLib::Pnt_Offset>>(), "pnt_inner_offset");
			chai.add(chaiscript::user_type<sectPxLib::OuterPnt<sectPxLib::Pnt_Offset>>(), "pnt_outer_offset");

			chai.add(chaiscript::constructor<sectPxLib::InnerPnt<sectPxLib::Pnt_Compnt>()>(), "pnt_inner_compnt");
			chai.add(chaiscript::constructor<sectPxLib::OuterPnt<sectPxLib::Pnt_Compnt>()>(), "pnt_outer_compnt");
			chai.add(chaiscript::constructor<sectPxLib::InnerPnt<sectPxLib::Pnt_Compnt>(const sectPxLib::InnerPnt<sectPxLib::Pnt_Compnt>&)>(), "pnt_inner_compnt");
			chai.add(chaiscript::constructor<sectPxLib::OuterPnt<sectPxLib::Pnt_Compnt>(const sectPxLib::OuterPnt<sectPxLib::Pnt_Compnt>&)>(), "pnt_outer_compnt");

			chai.add(chaiscript::constructor<sectPxLib::InnerPnt<sectPxLib::Pnt_GeoField>()>(), "pnt_inner_geofield");
			chai.add(chaiscript::constructor<sectPxLib::OuterPnt<sectPxLib::Pnt_GeoField>()>(), "pnt_inner_geofield");
			chai.add(chaiscript::constructor<sectPxLib::InnerPnt<sectPxLib::Pnt_GeoField>(const sectPxLib::InnerPnt<sectPxLib::Pnt_GeoField>&)>(), "pnt_inner_geofield");
			chai.add(chaiscript::constructor<sectPxLib::OuterPnt<sectPxLib::Pnt_GeoField>(const sectPxLib::OuterPnt<sectPxLib::Pnt_GeoField>&)>(), "pnt_outer_geofield");

			chai.add(chaiscript::constructor<sectPxLib::InnerPnt<sectPxLib::Pnt_Empty>()>(), "pnt_inner_empty");
			chai.add(chaiscript::constructor<sectPxLib::OuterPnt<sectPxLib::Pnt_Empty>()>(), "pnt_outer_empty");
			chai.add(chaiscript::constructor<sectPxLib::InnerPnt<sectPxLib::Pnt_Empty>(const sectPxLib::InnerPnt<sectPxLib::Pnt_Empty>&)>(), "pnt_inner_empty");
			chai.add(chaiscript::constructor<sectPxLib::OuterPnt<sectPxLib::Pnt_Empty>(const sectPxLib::OuterPnt<sectPxLib::Pnt_Empty>&)>(), "pnt_outer_empty");

			chai.add(chaiscript::constructor<sectPxLib::InnerPnt<sectPxLib::Pnt_Offset>()>(), "pnt_inner_offset");
			chai.add(chaiscript::constructor<sectPxLib::OuterPnt<sectPxLib::Pnt_Offset>()>(), "pnt_outer_offset");
			chai.add(chaiscript::constructor<sectPxLib::InnerPnt<sectPxLib::Pnt_Offset>(const sectPxLib::InnerPnt<sectPxLib::Pnt_Offset>&)>(), "pnt_inner_offset");
			chai.add(chaiscript::constructor<sectPxLib::OuterPnt<sectPxLib::Pnt_Offset>(const sectPxLib::OuterPnt<sectPxLib::Pnt_Offset>&)>(), "pnt_outer_offset");
			//chai.add(chaiscript::user_type<appl::pnt_t>(), "cpoint");

			chai.add(chaiscript::type_conversion<std::shared_ptr<sectPxLib::InnerPnt<sectPxLib::Pnt_Compnt>>, std::shared_ptr<SectPx_Pnt>>());
			chai.add(chaiscript::type_conversion<std::shared_ptr<sectPxLib::OuterPnt<sectPxLib::Pnt_Compnt>>, std::shared_ptr<SectPx_Pnt>>());
			chai.add(chaiscript::type_conversion<std::shared_ptr<sectPxLib::InnerPnt<sectPxLib::Pnt_GeoField>>, std::shared_ptr<SectPx_Pnt>>());
			chai.add(chaiscript::type_conversion<std::shared_ptr<sectPxLib::OuterPnt<sectPxLib::Pnt_GeoField>>, std::shared_ptr<SectPx_Pnt>>());
			chai.add(chaiscript::type_conversion<std::shared_ptr<sectPxLib::InnerPnt<sectPxLib::Pnt_Empty>>, std::shared_ptr<SectPx_Pnt>>());
			chai.add(chaiscript::type_conversion<std::shared_ptr<sectPxLib::OuterPnt<sectPxLib::Pnt_Empty>>, std::shared_ptr<SectPx_Pnt>>());
			chai.add(chaiscript::type_conversion<std::shared_ptr<sectPxLib::InnerPnt<sectPxLib::Pnt_Offset>>, std::shared_ptr<SectPx_Pnt>>());
			chai.add(chaiscript::type_conversion<std::shared_ptr<sectPxLib::OuterPnt<sectPxLib::Pnt_Offset>>, std::shared_ptr<SectPx_Pnt>>());

			//chai.add(chaiscript::constructor<appl::pnt_t(const appl::pnt_t&)>(), "cpoint");
			//chai.add(chaiscript::constructor<appl::pnt_t(appl::pnt_t&&)>(), "cpoint");
			chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<appl::pnt_t>>("std_vector_cpoint"));
			chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<CP>>("std_cp_vector"));
			chai.add(chaiscript::vector_conversion<std::vector<CP>>());

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