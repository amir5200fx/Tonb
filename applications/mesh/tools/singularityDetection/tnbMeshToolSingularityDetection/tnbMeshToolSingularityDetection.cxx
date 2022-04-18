#include <Cad_gSingularity.hxx>
#include <Cad_ColorApprxMetric.hxx>
#include <Cad_SingularityHorizons.hxx>
#include <Cad_MetricCalculator_SizeFun.hxx>
#include <Cad_MetricCalculator_Std.hxx>
#include <Cad_ApprxMetricIO.hxx>
#include <Cad_Tools.hxx>
#include <Cad_Shape.hxx>
#include <GModel_Tools.hxx>
#include <GModel_Surface.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Geo2d_PolygonGraph.hxx>
#include <Geo2d_PolygonGraphEdge.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static const auto loadExt = Cad_ApprxMetricIO::extension;

	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;

	static std::shared_ptr<Cad_ApprxMetricIO> myApproxMetrics;
	static std::vector<std::shared_ptr<Entity3d_Triangulation>> myHorizons;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static double myDegenCrit = Cad_SingularityHorizons::DEFAULT_DEGEN_CRITERION;

	auto checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			return true;
		}
		return false;
	}

	void loadSizeFun()
	{
		if (checkFolder("sizeMap"))
		{
			return;
		}
		else
		{
			const auto currentPath = boost::filesystem::current_path();

			// change the current path [12/4/2021 Amir]
			boost::filesystem::current_path(currentPath.string() + R"(\sizeMap)");

			auto name = file::GetSingleFile(boost::filesystem::current_path(), Geo3d_SizeFunction::extension).string();

			auto sizeFun = file::LoadFile<std::shared_ptr<Geo3d_SizeFunction>>(name + Geo3d_SizeFunction::extension, verbose);
			if (NOT sizeFun)
			{
				FatalErrorIn(FunctionSIG)
					<< " the size function file is null" << endl
					<< abort(FatalError);
			}

			//- change back the current path
			boost::filesystem::current_path(currentPath);

			mySizeFun = std::move(sizeFun);
		}
	}

	auto calcSize(const Pnt3d& pt)
	{
		return mySizeFun->Value(pt);
	}

	auto createMetricCalculator()
	{
		if (mySizeFun)
		{
			std::shared_ptr<Cad_MetricCalculator> alg =
				std::make_shared<cadLib::MetricCalculator_SizeFun>(&calcSize);
			return std::move(alg);
		}
		else
		{
			std::shared_ptr<Cad_MetricCalculator> alg =
				std::make_shared<cadLib::MetricCalculator_Std>();
			return std::move(alg);
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		loadSizeFun();

		auto metricCalculator = createMetricCalculator();

		const auto& myShape = myApproxMetrics->Model();
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded!" << endl
				<< abort(FatalError);
		}
		const auto surfaces = GModel_Tools::GetSurfaces(myShape->Shape());
		if (surfaces.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no surface is found!" << endl
				<< abort(FatalError);
		}

		const auto& myApproxMap = myApproxMetrics->Approx();
		for (const auto& x : surfaces)
		{
			Debug_Null_Pointer(x);
			auto iter = myApproxMap.find(x->Index());
			if (iter IS_EQUAL myApproxMap.end())
			{
				FatalErrorIn(FunctionSIG)
					<< "the item is not in the tree!" << endl
					<< abort(FatalError);
			}
			const auto& metricApprox = iter->second;
			if (NOT metricApprox)
			{
				FatalErrorIn(FunctionSIG)
					<< "no approximation has been found for the surface!" << endl
					<< abort(FatalError);
			}
			auto geom = GModel_Tools::RetrieveGeometry(*x);
			if (NOT geom)
			{
				FatalErrorIn(FunctionSIG)
					<< "no geometry has been found!" << endl
					<< abort(FatalError);
			}
			auto[maxDet, minDet] = Cad_Tools::CalcMaxMinMetrics(geom, *metricApprox);
			auto criterion = Cad_ColorApprxMetric::CalcCriterion(maxDet);
			auto colors = std::make_shared<Cad_ColorApprxMetric>();

			colors->SetCriterion(criterion);

			colors->LoadGeoemtry(geom);
			colors->LoadApproximation(metricApprox);
			colors->LoadMetricCalculator(metricCalculator);

			colors->Perform();
			if (NOT colors->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}

			auto horizonAlg = std::make_shared<Cad_SingularityHorizons>();
			
			horizonAlg->SetDegeneracyCriterion(myDegenCrit);
			
			horizonAlg->LoadGeometry(geom);
			horizonAlg->LoadApproximation(metricApprox);
			horizonAlg->LoadMetricCalculato(metricCalculator);

			horizonAlg->Perform();
			if (NOT horizonAlg->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}

			if (horizonAlg->HasHorizon())
			{
				const auto& horizons = horizonAlg->Horizons();
				Debug_Null_Pointer(horizons);

				for (const auto& pedge : horizons->Edges())
				{
					Debug_Null_Pointer(pedge.second);
					const auto& poly = pedge.second->Polygon();
					Debug_Null_Pointer(poly);

					auto tri2d = Geo_Tools::Triangulation(*Geo_Tools::RetrieveChain(*poly));
					auto tri = Cad_Tools::Triangulation(*geom, *tri2d);

					myHorizons.push_back(std::move(tri));
				}
			}
		}
	}
}