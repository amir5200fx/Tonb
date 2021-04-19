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
#include <SectPx_TopoSegment.hxx>
#include <SectPx_FrameTuner.hxx>
#include <SectPx_Tools.hxx>
#include <SectPx_RegObjType.hxx>
#include <SectPx_Poles.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <frameMaker.hxx>
#include <frameTuner.hxx>

#include <map>

namespace tnbLib
{

	static std::shared_ptr<SectPx_Registry> myRegistry;
	static appl::frame_t myFrame;
	static appl::tuner_t myTuner;

	static size_t verbose = 0;
	static bool loaded = false;


	//static std::map<std::string, appl::profile_t> myProfiles;

	static std::vector<appl::profileMaker_t> myThickness;
	static std::vector<appl::profileMaker_t> myCamber;

	enum class matter
	{
		camber,
		thickness
	};

	static std::map<appl::profile_t, matter> profileMatter;

	//- globals

	void registerMatters(const std::vector<appl::profileMaker_t>& profiles, matter m)
	{
		for (const auto& x : profiles)
		{
			const auto& t = x->TopoProfile();
			auto paired = std::make_pair(t, m);
			auto insert = profileMatter.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}
		}
	}

	/*void insertToMap(const appl::profile_t& p)
	{
		auto paired = std::make_pair(p->Name(), p);
		auto insert = myProfiles.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been detected!" << endl
				<< " - unable to register the profiles" << endl
				<< abort(FatalError);
		}
	}*/

	/*auto selectProfile(const word& name)
	{
		auto iter = myProfiles.find(name);
		if (iter IS_EQUAL myProfiles.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "Wrong profile's name: " << name << endl
				<< abort(FatalError);
		}
		return iter->second;
	}*/

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

	const auto& getProfileMaker()
	{
		checkFrame();
		return appl::getCmpProfileMaker(myFrame);
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

		oa >> myCamber;
		oa >> myThickness;

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

		if (NOT myCamber.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "no camber profile has been detected!" << endl
				<< abort(FatalError);
		}

		if (NOT myThickness.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "no thickness profile has been detected!" << endl
				<< abort(FatalError);
		}
		
		//const auto& profiles = appl::getCmpProfileMaker(myFrame);
		/*if (profiles->NbProfiles() NOT_EQUAL 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid data has been detected!" << endl
				<< abort(FatalError);
		}*/
		/*for (const auto& x : profiles->Profiles())
		{
			insertToMap(x.second->TopoProfile());
		}*/

		registerMatters(myCamber, matter::camber);
		registerMatters(myThickness, matter::thickness);

		myTuner = std::make_shared<SectPx_FrameTuner>(myFrame->ParRegistry(), myFrame->FrameRegistry());

		appl::importFrame(myTuner, myFrame);

		loaded = true;

		if (verbose)
		{
			Info << endl;
			Info << " the frame is imported to the tuner, successfully!" << endl;
			Info << endl;
		}
	}

	/*void loadTuner(const std::string& name)
	{

		fileName fn(name);
		std::ifstream f(fn);

		boost::archive::polymorphic_text_iarchive ia(f);

		ia >> myTuner;

		if (verbose)
		{
			Info << " the tuner has been loaded successfully!" << endl;
		}

		if (NOT myTuner)
		{
			FatalErrorIn(FunctionSIG)
				<< "no tuner has been detected" << endl
				<< abort(FatalError);
		}
		if (NOT myTuner->FrameRegistry())
		{
			FatalErrorIn(FunctionSIG)
				<< "no registry has been detected for the frame" << endl
				<< abort(FatalError);
		}
		if (NOT myTuner->IsFrameLoaded())
		{
			FatalErrorIn(FunctionSIG)
				<< "no frame has been loaded into the tuner!" << endl
				<< abort(FatalError);
		}
	}*/

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
		const auto& scatterReg = getScatterReg();
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
	}

	void printFixedParams()
	{
		const auto& params = getScatterReg()->ScatterMap(SectPx_RegObjType::parameter);
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
		const auto& points = getScatterReg()->ScatterMap(SectPx_RegObjType::pnt);
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

	void saveTo(const std::string& name)
	{
		checkFrame();
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myRegistry;
		oa << myTuner;
		oa << myCamber;
		oa << myThickness;

		if (verbose)
		{
			Info << endl;
			Info << " the tuner is saved to: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	/*void drawPlt(const std::string& name)
	{
		fileName fn(name);
		OFstream f(fn);

		const auto& profiles = getScatterReg()->ScatterMap(SectPx_RegObjType::profile);
		for (const auto& x : profiles)
		{
			auto profile = std::dynamic_pointer_cast<SectPx_TopoProfile>(x.second.lock());
			Debug_Null_Pointer(profile);

			auto pnts = profile->RetrieveCoords();
			Io::ExportCurve(pnts, f);
		}
	}*/

	void drawCamberPolesPlt(const std::string& name)
	{
		fileName fn(name);
		OFstream f(fn);

		const auto& topoSegments = getScatterReg()->ScatterMap(SectPx_RegObjType::topoSegment);
		for (const auto& x : topoSegments)
		{
			auto seg = std::dynamic_pointer_cast<SectPx_TopoSegment>(x.second.lock());
			Debug_Null_Pointer(seg);

			const auto& p0 = seg->Pole0();
			auto topoPrf = p0->TopoProfile().lock();
			auto iter = profileMatter.find(topoPrf);
			if (iter IS_EQUAL profileMatter.end())
			{
				FatalErrorIn(FunctionSIG)
					<< "unidentified profile has been detected!" << endl
					<< abort(FatalError);
			}
			if (iter->second IS_EQUAL matter::camber)
			{
				auto pnts = SectPx_Tools::RetrieveControlPoints(seg);
				Io::ExportCurve(pnts, f);
			}		
		}
	}

	void drawThicknessPolesPlt(const std::string& name)
	{
		fileName fn(name);
		OFstream f(fn);

		const auto& topoSegments = getScatterReg()->ScatterMap(SectPx_RegObjType::topoSegment);
		for (const auto& x : topoSegments)
		{
			auto seg = std::dynamic_pointer_cast<SectPx_TopoSegment>(x.second.lock());
			Debug_Null_Pointer(seg);

			const auto& p0 = seg->Pole0();
			auto topoPrf = p0->TopoProfile().lock();
			auto iter = profileMatter.find(topoPrf);
			if (iter IS_EQUAL profileMatter.end())
			{
				FatalErrorIn(FunctionSIG)
					<< "unidentified profile has been detected!" << endl
					<< abort(FatalError);
			}
			if (iter->second IS_EQUAL matter::thickness)
			{
				auto pnts = SectPx_Tools::RetrieveControlPoints(seg);
				Io::ExportCurve(pnts, f);
			}
		}
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


	//- tuner makers

	void createWeight(int pole, const appl::par_t& p)
	{
		checkFrame();
		appl::createWeight(myTuner, pole, p);
	}

	void createSymmTightness(int pole, const appl::par_t& p)
	{
		checkFrame();
		appl::createSymmTightness(myTuner, pole, p);
	}

	void createSlider(int seg, const appl::par_t& p)
	{
		checkFrame();
		appl::createSlider(myTuner, seg, p);
	}

	void createSlider(int seg, const appl::coord_t& c)
	{
		checkFrame();
		appl::createSlider(myTuner, seg, c);
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
		mod->add(chaiscript::fun([]()-> void {printReg(); }), "printRegistry");
		mod->add(chaiscript::fun([]()-> void {printFixedParams(); }), "printFixedParameters");
		mod->add(chaiscript::fun([]()-> void {printPoints(); }), "printPoints");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {drawPlt(name); }), "drawPntsPlt");
		mod->add(chaiscript::fun([](const std::string& name)-> void {drawCamberPolesPlt(name); }), "drawCamberPolesPlt");
		mod->add(chaiscript::fun([](const std::string& name)-> void {drawThicknessPolesPlt(name); }), "drawThicknessPolesPlt");
		mod->add(chaiscript::fun([](const std::string& name)->void {loadFrame(name); }), "loadFrame");
		//mod->add(chaiscript::fun([](const std::string& name)->void {loadTuner(name); }), "loadTuner");

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
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

	void setTuners(const module_t& mod)
	{
		mod->add(chaiscript::fun([](int pole, const appl::par_t& p)->void {createWeight(pole, p); }), "createWeight");
		mod->add(chaiscript::fun([](int pole, const appl::par_t& p)->void {createSymmTightness(pole, p); }), "createSymmTightness");
		mod->add(chaiscript::fun([](int seg, const appl::par_t& p)-> void {createSlider(seg, p); }), "createSlider");
		mod->add(chaiscript::fun([](int seg, const appl::coord_t& c)-> void {createSlider(seg, c); }), "createSlider");
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

			setGlobals(mod);
			setParMakers(mod);
			setFieldMakers(mod);
			setTuners(mod);

			chai.add(mod);

			fileName myFileName("profileTuner");

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