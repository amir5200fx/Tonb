#include <GModel_MetricAnalyzer.hxx>

#include <Cad_GModel.hxx>
#include <GModel_Surface.hxx>
#include <Cad_ApprxMetricInfo.hxx>
#include <Cad_ApprxMetric.hxx>
#include <Cad_GeomSurface.hxx>
#include <Entity2d_MetricMeshValue.hxx>
#include <Entity2d_Metric1.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Box.hxx>
#include <Cad_Tools.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::GModel_MetricAnalyzer::verbose(0);

const std::string tnbLib::GModel_MetricAnalyzer::extension = ".gmodelmanalzr";

const std::shared_ptr<tnbLib::Cad_ApprxMetricInfo> tnbLib::GModel_MetricAnalyzer::DEFAULT_INFO =
std::make_shared<Cad_ApprxMetricInfo>();

void tnbLib::GModel_MetricAnalyzer::Perform()
{
	if (verbose)
	{
		tnbLib::Info << endl
			<< "******* Calculating the surface metrics of a Meodel ********" << endl
			<< endl;
	}

	if (NOT Model())
	{
		FatalErrorIn(FunctionSIG)
			<< "no model has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& surfaces = Model()->Surfaces();
	if (surfaces.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no surface is found!" << endl
			<< abort(FatalError);
	}

	const auto& glInfo = GlobalInfo();
	if (NOT glInfo)
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found" << endl
			<< abort(FatalError);
	}

	const auto& infoMap = Infos();

	for (const auto& x : surfaces)
	{
		if (verbose)
		{
			Info << " - surface, nb " << x->Index() << endl;
		}

		auto iter = infoMap.find(x->Index());

		Standard_Boolean localInfo = Standard_False;
		std::shared_ptr<Cad_ApprxMetricInfo> currentInfo;
		if (iter IS_EQUAL infoMap.end())
		{
			currentInfo = glInfo;
		}
		else
		{
			currentInfo = iter->second;
			localInfo = Standard_True;
		}

		if (NOT currentInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< "info is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl
				<< " Using Local Info? " << (localInfo ? "YES" : "NO") << endl;
		}

		if (verbose)
		{
			Info << " Approximating the metric..." << endl;
		}

		const auto& geometry = x->GeomSurface();
		auto b = std::make_shared<Entity2d_Box>(geometry->ParametricBoundingBox());
		Debug_Null_Pointer(geometry);
		
		{// timer scope [12/31/2021 Amir]
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			auto alg = std::make_shared<Cad_ApprxMetric>();
			Debug_Null_Pointer(alg);

			alg->LoadGeoemtry(geometry->Geometry());
			alg->LoadDomain(std::move(b));
			alg->OverrideInfo(std::move(currentInfo));

			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

			auto tri = std::move(alg->TriangulationRef());
			Debug_Null_Pointer(tri);

			std::vector<Entity2d_Metric1> values;
			values.reserve(tri->NbPoints());

			const auto& g = geometry->Geometry();
			for (const auto& x : tri->Points())
			{
				auto m = Cad_Tools::CalcMetric(x, g);
				values.push_back(std::move(m));
			}

			auto valueMesh = std::make_shared<Entity2d_MetricMeshValue>(std::move(tri), std::move(values));
			Debug_Null_Pointer(valueMesh);

			auto paired = std::make_pair(x->Index(), std::move(valueMesh));
			auto insert = theMetrics_.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data has been detected!" << endl
					<< abort(FatalError);
			}
		}

		if (verbose)
		{
			Info << endl
				<< " - the metric of the surface is calculated in, " << global_time_duration << " ms." << endl
				<< endl;
		}
	}

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		tnbLib::Info << endl
			<< "******* End of the Calculating the surface metrics of a Meodel ********" << endl
			<< endl;
	}
}