#include <SectPx_Registry.hxx>
#include <SectPx_ParRegistry.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_FieldFuns.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_GeoMap.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_Datums.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_TopoSegment.hxx>
#include <SectPx_FrameTuner.hxx>
#include <SectPx_Tools.hxx>
#include <SectPx_RegObjType.hxx>
#include <SectPx_ExtrProfiles.hxx>
#include <SectPx_Limits.hxx>
#include <SectPx_CurveQ.hxx>
#include <ShapePx_ExtrudedPatch.hxx>
#include <ShapePx_Profile.hxx>
#include <ShapePx_Section.hxx>
#include <ShapePx_ContinProfile_OffsetCustom.hxx>
#include <ShapePx_ContinProfile_GeneratedCustom.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

#include <frameMaker.hxx>
#include <frameTuner.hxx>

#include <vector>

namespace tnbLib
{

	typedef std::shared_ptr<SectPx_CurveQ> curveQ_t;
	typedef std::shared_ptr<ShapePx_Profile> extrProfile_t;
	typedef std::shared_ptr<ShapePx_Section> section_t;
	typedef std::shared_ptr<ShapePx_ExtrudedPatch> patch_t;
	typedef std::shared_ptr<SectPx_Limits> limits_t;
	typedef std::shared_ptr<maker::Limits> limitsMaker_t;
	typedef std::shared_ptr<maker::Extrude> extrProfileMaker_t;
	typedef std::shared_ptr<maker::CurveQ> curveQMaker_t;

	static patch_t myPatch;
	static section_t mySection;
	static std::vector<extrProfile_t> myProfiles;
	static appl::registry_t myRegistry;
	static appl::fieldMaker_t myFieldMaker;

	static limitsMaker_t myLimitMaker;
	static extrProfileMaker_t myExtrProfileMaker;
	static curveQMaker_t myCurveQMaker;

	static appl::parMaker_t myParMaker;

	static std::map<int, appl::par_t> sectionPars;

	static unsigned short verbose = 0;
	static bool loaded = false;


	typedef std::tuple<appl::par_t, appl::par_t, appl::par_t, appl::par_t>
		profileBnd;

	//- globals

	void checkFrame()
	{
		if (NOT loaded)
		{
			FatalErrorIn(FunctionSIG)
				<< "no frame has been loaded" << endl
				<< abort(FatalError);
		}
	}

	bool hasPar(const appl::par_t& p)
	{
		auto iter = sectionPars.find(p->Index());
		if (iter IS_EQUAL sectionPars.end())
		{
			return false;
		}
		if (iter->second NOT_EQUAL p)
		{
			return false;
		}
		return true;
	}

	//- makers

	const auto& getLimitsMaker()
	{
		checkFrame();
		Debug_Null_Pointer(myLimitMaker);
		return myLimitMaker;
	}

	const auto& getExtrProfileMaker()
	{
		checkFrame();
		Debug_Null_Pointer(myExtrProfileMaker);
		return myExtrProfileMaker;
	}

	const auto& getParameterMaker()
	{
		checkFrame();
		Debug_Null_Pointer(myParMaker);
		return myParMaker;
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
		Debug_Null_Pointer(myFieldMaker);
		return myFieldMaker;
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

	void loadPatch(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);

		boost::archive::polymorphic_text_iarchive ia(f);

		std::shared_ptr<ShapePx_Patch> patch;
		ia >> patch;
		//ia >> sectionPars;

		if (verbose)
		{
			Info << endl;
			Info << " the patch is loaded form: " << fn << ", successfully!" << endl;
			Info << endl;
		}

		if (NOT patch)
		{
			FatalErrorIn(FunctionSIG)
				<< " the patch is null" << endl
				<< abort(FatalError);
		}

		if (NOT patch->IsExtruded())
		{
			FatalErrorIn(FunctionSIG)
				<< " the patch is not extruded!" << endl
				<< abort(FatalError);
		}

		myPatch = std::dynamic_pointer_cast<ShapePx_ExtrudedPatch>(patch);
		Debug_Null_Pointer(myPatch);

		mySection = myPatch->Section();
		if (NOT mySection)
		{
			FatalErrorIn(FunctionSIG)
				<< " the section is null" << endl
				<< abort(FatalError);
		}

		const auto& reg = mySection->Registry();
		const auto& pars = reg->Scatter()->ScatterMap(SectPx_RegObjType::parameter);

		//auto pars = mySection->RetrieveParameters();
		for (const auto& p : pars)
		{
			auto x = std::dynamic_pointer_cast<SectPx_Par>(p.second.lock());
			auto paired = std::make_pair(x->Index(), x);
			auto insert = sectionPars.insert(std::move(paired));

			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}
		}

		myParMaker = std::make_shared<maker::Parameter>(myPatch->Registry()->Parameter());
		myFieldMaker = std::make_shared<maker::FieldFun>(myPatch->Registry()->Parameter());
		myLimitMaker = std::make_shared<maker::Limits>(myPatch->Registry()->Shape());
		myExtrProfileMaker = std::make_shared<maker::Extrude>(myPatch->Registry()->Shape());
		myCurveQMaker = std::make_shared<maker::CurveQ>(myPatch->Section()->Registry());

		if (verbose)
		{
			Info << endl;
			Info << " the parameter maker is created, successfully!" << endl;
			Info << " the field maker is created, successfully!" << endl;
			Info << " the limits maker is created, successfully!" << endl;
			Info << " the extrusion profile maker is created, successfully!" << endl;
			Info << endl;
		}

		loaded = true;
	}

	/*profileBnd createProfileBound
	(
		const appl::par_t& minLow,
		const appl::par_t& maxUpper,
		const appl::par_t& x0,
		const appl::par_t& x1
	)
	{
		auto t = std::make_tuple(minLow, maxUpper, x0, x1);
		return std::move(t);
	}

	profileBnd createProfileBound
	(
		const appl::par_t& minLow,
		const appl::par_t& maxUpper
	)
	{
		auto t = createProfileBound(minLow, maxUpper, minLow, maxUpper);
		return std::move(t);
	}*/

	auto selectParameter(int i)
	{
		checkFrame();
		auto t = myParMaker->SelectParameter(i);
		return std::move(t);
	}

	auto selectCurve(int id)
	{
		checkFrame();
		auto c = myCurveQMaker->SelectCurve(id);
		return std::move(c);
	}

	limits_t createLimits(const appl::par_t& x0, const appl::par_t& x1)
	{
		auto t = myLimitMaker->SelectLimits(myLimitMaker->CreateLimits(x0, x1));
		return std::move(t);
	}

	void addProfile(extrProfile_t&& profile)
	{
		myProfiles.push_back(std::move(profile));
	}

	extrProfile_t createUniformProfile(const appl::par_t& x0, const appl::par_t& x1, const appl::par_t& v)
	{
		auto prf = myExtrProfileMaker->SelectProfile(myExtrProfileMaker->CreateUniform(x0, x1, v));
		auto t = std::make_shared<shapePxLib::ContinProfile_OffsetCustom>(std::move(prf));
		t->Perform();
		return std::move(t);
	}

	extrProfile_t createLinearProfile(const appl::par_t& x0, const appl::par_t& x1, const appl::par_t& v0, const appl::par_t& v1)
	{
		auto prf = myExtrProfileMaker->SelectProfile(myExtrProfileMaker->CreateLinear(x0, x1, v0, v1));
		auto t = std::make_shared<shapePxLib::ContinProfile_OffsetCustom>(std::move(prf));
		t->Perform();
		return std::move(t);
	}

	extrProfile_t createGeneratedProfile(const curveQ_t& c, int degree)
	{
		auto t = std::make_shared<shapePxLib::ContinProfile_GeneratedCustom>(c, degree);
		t->Perform();
		return std::move(t);
	}

	void importProfile(const appl::par_t& par, const extrProfile_t& prf)
	{
		if (NOT hasPar(par))
		{
			FatalErrorIn(FunctionSIG)
				<< " the parameter is not on the section!" << endl
				<< abort(FatalError);
		}

		myPatch->ImportProfileForParameter(par->Index(), prf);
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		std::shared_ptr<ShapePx_Patch> patch = myPatch;
		oa << patch;

		if (verbose)
		{
			Info << endl;
			Info << " the patch is saved at: " << fn << ", successfully!" << endl;
			Info << endl;
		}
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
		const auto& scatterReg = myPatch->Registry()->Scatter();
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
		Info << endl;
		Info << " poles: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::pole))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " segments: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::segment))
		{
			auto item = x.second.lock();
			printObj(item);
		}

		const auto curves = scatterReg->ScatterMap(SectPx_RegObjType::curveQ);
		if (curves.size())
		{
			Info << endl;
			Info << " curves: " << endl;
			Info << endl;
			for (const auto& x : curves)
			{
				auto item = x.second.lock();
				printObj(item);
			}
		}

		const auto limits = scatterReg->ScatterMap(SectPx_RegObjType::limits);
		if (limits.size())
		{
			Info << endl;
			Info << " limits: " << endl;
			Info << endl;
			for (const auto& x : limits)
			{
				auto item = x.second.lock();
				printObj(item);
			}
		}

		const auto extrProfiles = scatterReg->ScatterMap(SectPx_RegObjType::extrProfile);
		if (extrProfiles.size())
		{
			Info << endl;
			Info << " extrProfiles: " << endl;
			Info << endl;
			for (const auto& x : extrProfiles)
			{
				auto item = x.second.lock();
				printObj(item);
			}
		}

		const auto spacings = scatterReg->ScatterMap(SectPx_RegObjType::spacing);
		if (spacings.size())
		{
			Info << endl;
			Info << " spacings: " << endl;
			Info << endl;
			for (const auto& x : spacings)
			{
				auto item = x.second.lock();
				printObj(item);
			}
		}
	}

	void printSectionParameters()
	{
		checkFrame();
		const auto& section = myPatch->Section();
		if (NOT section)
		{
			FatalErrorIn(FunctionSIG)
				<< "no section is found for the patch!" << endl
				<< abort(FatalError);
		}
		const auto parameters = section->RetrieveParameters();
		Info << endl;
		Info << " parameters: " << endl;
		Info << endl;
		for (const auto& x : parameters)
		{
			printObj(x);
		}
	}

	void printFixedSectionParameters()
	{
		checkFrame();
		const auto& section = myPatch->Section();
		if (NOT section)
		{
			FatalErrorIn(FunctionSIG)
				<< "no section is found for the patch!" << endl
				<< abort(FatalError);
		}
		const auto& reg = section->Registry();
		const auto& parameters = reg->Scatter()->ScatterMap(SectPx_RegObjType::parameter);
		Info << endl;
		Info << " parameters: " << endl;
		Info << endl;
		for (const auto& x : parameters)
		{
			auto p = std::dynamic_pointer_cast<SectPx_FixedPar>(x.second.lock());
			if (p)
			{
				printObj(p);
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

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadPatch(name); }), "loadPatch");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](int i)-> auto {auto t = selectParameter(i); return std::move(t); }), "selectParameter");
		mod->add(chaiscript::fun([](int i)-> auto {auto t = selectCurve(i); return std::move(t); }), "selectCurve");
		mod->add(chaiscript::fun([]()->void {printSectionParameters(); }), "printSectionPars");
		mod->add(chaiscript::fun([]()->void {printFixedSectionParameters(); }), "printFixedSectionPars");
		mod->add(chaiscript::fun([]()->void {printReg(); }), "printRegistry");

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
	}

	void setProfiles(const module_t& mod)
	{
		//mod->add(chaiscript::fun([](const appl::par_t& minLow, const appl::par_t& maxUp, const appl::par_t& x0, const appl::par_t& x1)->auto {auto t = createProfileBound(minLow, maxUp, x0, x1); return std::move(t); }), "createProfileSpan");
		//mod->add(chaiscript::fun([](const appl::par_t& minLow, const appl::par_t& maxUp)->auto {auto t = createProfileBound(minLow, maxUp); return std::move(t); }), "createProfileSpan");

		mod->add(chaiscript::fun([](const appl::par_t& x0, const appl::par_t& x1, const appl::par_t& v)-> auto {auto t = createUniformProfile(x0, x1, v); return std::move(t); }), "createUniformProfile");
		mod->add(chaiscript::fun([](const appl::par_t& x0, const appl::par_t& x1, const appl::par_t& v0, const appl::par_t& v1)-> auto {auto t = createLinearProfile(x0, x1, v0, v1); return std::move(t); }), "createLinearProfile");
		mod->add(chaiscript::fun([](const curveQ_t& c, int deg)-> auto {auto t = createGeneratedProfile(c, deg); return std::move(t); }), "createGeneratedProfile");

		mod->add(chaiscript::fun([](const extrProfile_t& prf, const appl::par_t& p)-> void {importProfile(p, prf); }), "setProfileTo");
	}

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
			setProfiles(mod);
			setParMakers(mod);
			setFieldMakers(mod);

			chai.add(mod);

			fileName myFileName("TnbExtrudeProfile");

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
	return 0;
}