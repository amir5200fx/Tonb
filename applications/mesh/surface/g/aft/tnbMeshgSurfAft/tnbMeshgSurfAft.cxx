#include <Aft2d_gModelSurface.hxx>
#include <Aft2d_gModelSurfaceUniMetric.hxx>
#include <Aft2d_gSolutionDataSurface.hxx>
#include <Aft2d_gPlnCurveSurfaceUniMetric.hxx>
#include <Aft2d_gPlnCurveSurface.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <Aft2d_gBoundaryOfPlaneSurfaceUniMetric.hxx>
#include <Aft2d_gBoundaryOfPlaneSurface.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_gRegionPlaneSurfaceUniMetric.hxx>
#include <Aft2d_gRegionPlaneSurface.hxx>
#include <Aft2d_OptNodeSurface_Algs.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_OptNodeAnIso_nonIterAdaptiveInfo.hxx>
#include <Aft_Tools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft_SizeCorr_FractionInfo.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Cad_Tools.hxx>
#include <GModel_Tools.hxx>
#include <GModel_Surface.hxx>
#include <GModel_Plane.hxx>
#include <GModel_ParaCurve.hxx>
#include <GModel_ParaWire.hxx>
#include <Cad_GeomSurface.hxx>
#include <GeoSizeFun2d_Surface.hxx>
#include <GeoMetricFun2d_ExactSurface.hxx>
#include <GeoMetricFun2d_Plane.hxx>
#include <Cad_GModel.hxx>

#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>

namespace tnbLib
{

	static const std::string extension = Aft2d_gSolutionDataSurface::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Aft2d_gSolutionDataSurface> mySoluData;
	static std::string myFileName;

	static double myTol = 1.0E-6;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTolerance(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the tolerance is set to: " << myTol << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_gSolutionDataSurface>>(name + extension, verbose);
		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "the data solution file is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(mySoluData, name + extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	auto mesh
	(
		const std::shared_ptr<Aft2d_MetricPrcsrSurface>& theMetricPrcsr, 
		const std::shared_ptr<Aft2d_OptNodeSurface_Calculator>& theCalculator, 
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundaries
	)
	{
		auto alg = std::make_shared<Aft2d_gModelSurface>();
		alg->LoadMetricMap(theMetricPrcsr);
		alg->LoadBoundaryMetricMap(theMetricPrcsr);

		alg->LoadBoundaryEdges(theBoundaries);
		alg->LoadNodeCalculator(theCalculator);

		{// timer scope [3/12/2022 Amir]
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_s);

			alg->Perform();
		}

		const auto& elemMap = alg->RetrieveElements();
		std::vector<std::shared_ptr<Aft2d_ElementSurface>> elements;
		elements.reserve(elemMap.size());
		for (const auto& x : elemMap)
		{
			elements.push_back(x.second);
		}
		return std::move(elements);
	}

	auto mesh
	(
		const std::shared_ptr<Aft2d_MetricPrcsrSurfaceUniMetric>& theMetricPrcsr,
		const std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator>& theCalculator,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundaries
	)
	{
		auto alg = std::make_shared<Aft2d_gModelSurfaceUniMetric>();
		alg->LoadMetricMap(theMetricPrcsr);
		alg->LoadBoundaryMetricMap(theMetricPrcsr);

		alg->LoadBoundaryEdges(theBoundaries);
		alg->LoadNodeCalculator(theCalculator);

		{// timer scope [3/12/2022 Amir]
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_s);

			alg->Perform();
		}

		const auto& elemMap = alg->RetrieveElements();
		std::vector<std::shared_ptr<Aft2d_ElementSurface>> elements;
		elements.reserve(elemMap.size());
		for (const auto& x : elemMap)
		{
			elements.push_back(x.second);
		}
		return std::move(elements);
	}

	auto mesh
	(
		const std::shared_ptr<GModel_Surface>& theSurface, 
		const std::shared_ptr<Geo3d_SizeFunction>& theSizeFun, 
		const std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator>& theUniMetricCalculator, 
		const std::shared_ptr<Aft2d_OptNodeSurface_Calculator>& theCalculator,
		const std::shared_ptr<Aft2d_BoundaryOfPlaneAnIso_Info>& theBndInfo,
		const std::shared_ptr<Aft_MetricPrcsrAnIso_Info>& theInfo
	)
	{
		if (NOT theSurface->GeomSurface())
		{
			FatalErrorIn(FunctionSIG)
				<< "no geometry has been found!" << endl
				<< abort(FatalError);
		}

		if (NOT theSurface->GeomSurface()->Geometry())
		{
			FatalErrorIn(FunctionSIG)
				<< "no geometry has been found!" << endl
				<< abort(FatalError);
		}
		const auto& geometry = theSurface->GeomSurface()->Geometry();

		auto wire = GModel_Tools::GetOuterParaWire(theSurface);
		auto box = GModel_Tools::CalcBoundingBox(*wire);

		auto d = box.Diameter();
		auto tol = myTol * d;

		auto pln = GModel_Tools::GetParaPlane(theSurface, tol);
		auto sizeFun = std::make_shared<GeoSizeFun2d_Surface>(geometry, theSizeFun, box);

		if (GModel_Tools::IsPlane(theSurface))
		{
			auto gPlane = Handle(Geom_Plane)::DownCast(geometry);
			if (NOT gPlane)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "the geometry is not plane!" << endl
					<< abort(FatalError);
			}
			auto metricFun = std::make_shared<GeoMetricFun2d_Plane>(gPlane, box);
			auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrSurfaceUniMetric>(sizeFun, metricFun, theInfo);
			metricPrcsr->SetDimSize(box.Diameter());

			auto plnRegion = Aft2d_gRegionPlaneSurfaceUniMetric::MakePlane(pln);

			auto bnd = std::make_shared<Aft2d_gBoundaryOfPlaneSurfaceUniMetric>(theBndInfo);
			bnd->LoadMetricProcessor(metricPrcsr);
			bnd->LoadPlane(plnRegion);

			bnd->Perform();
			if (NOT bnd->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}

			const auto& boundaries = bnd->Boundaries();

			Aft_Tools::Connect(boundaries);

			auto elements = mesh(metricPrcsr, theUniMetricCalculator, Aft_Tools::UpCast(boundaries));
			return std::move(elements);
		}
		else
		{
			auto metricFun = std::make_shared<GeoMetricFun2d_ExactSurface>(geometry, box);
			auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrSurface>(sizeFun, metricFun, theInfo);
			metricPrcsr->SetDimSize(box.Diameter());

			auto plnRegion = Aft2d_gRegionPlaneSurface::MakePlane(pln);

			auto bnd = std::make_shared<Aft2d_gBoundaryOfPlaneSurface>(theBndInfo);
			bnd->LoadMetricProcessor(metricPrcsr);
			bnd->LoadPlane(plnRegion);

			bnd->Perform();
			if (NOT bnd->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}

			const auto& boundaries = bnd->Boundaries();

			Aft_Tools::Connect(boundaries);

			auto elements = mesh(metricPrcsr, theCalculator, Aft_Tools::UpCast(boundaries));
			return std::move(elements);
		}
	}

	auto retrieveTris3d(const std::shared_ptr<GModel_Surface>& surface, const Entity2d_Triangulation& theTris)
	{
		auto tris3d = Cad_Tools::Triangulation(*surface->GeomSurface()->Geometry(), theTris);
		return std::move(tris3d);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& model = mySoluData->Geometry();
		if (NOT model)
		{
			FatalErrorIn(FunctionSIG)
				<< "th model is null!" << endl
				<< abort(FatalError);
		}

		const auto& sizeFun3d = mySoluData->SizeFun();

		auto iterInfo = std::make_shared<Aft_SizeCorr_IterativeInfo>();
		iterInfo->SetIgnoreNonConvergency(Standard_True);
		iterInfo->SetMaxNbIters(5);
		iterInfo->SetTolerance(0.025);
		iterInfo->SetUnderRelaxation(0.85);

		auto fracInfo = std::make_shared<Aft_SizeCorr_FractionInfo>();

		auto anIsoOptNodeInfo = std::make_shared<Aft2d_OptNodeAnIso_nonIterAdaptiveInfo>(iterInfo, fracInfo);
		auto anIsoOptNodeUniMetric = std::make_shared<Aft2d_OptNodeSurfaceUniMetric_nonIterAdaptive>(anIsoOptNodeInfo);
		auto anIsoOptNode = std::make_shared<Aft2d_OptNodeSurface_nonIterAdaptive>(anIsoOptNodeInfo);

		auto bndInfo = std::make_shared<Aft2d_BoundaryOfPlaneAnIso_Info>();
		bndInfo->SetOverrideInfo(Standard_False);
		bndInfo->SetMergeTolerance(1.0E-6);

		auto metricPrcsrInfo = std::make_shared<Aft_MetricPrcsrAnIso_Info>();
		metricPrcsrInfo->SetNbIters(5);
		metricPrcsrInfo->SetNbSamples(3);
		metricPrcsrInfo->SetTolerance(0.02);

		for (const auto& x : model->Surfaces())
		{
			Debug_Null_Pointer(x);
			auto plnMesh = mesh(x, sizeFun3d, anIsoOptNodeUniMetric, anIsoOptNode, bndInfo, metricPrcsrInfo);
			auto tris = Aft_Tools::RetrieveTriangleMesh(plnMesh);
			auto tris3d = retrieveTris3d(x, *tris);

			Global_Tools::Insert(x->Index(), tris3d, mySoluData->TrisRef());
		}
		exeTag = true;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFuns(const module_t& mod)
	{
		// io functions 
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings 
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators 
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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
			Info << " This application is aimed to create plane boundary info." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshgSurfAft"));

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
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}