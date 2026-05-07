#include <VoyageGeo_PathGeneration.hxx>

#include <VoyageGeo_GreateCircleNav.hxx>
#include <Voyage_Tools.hxx>
#include <VoyageGeo_Earth.hxx>
#include <VoyageGeo_Path2.hxx>
#include <Mesh2d_CurveAnIso.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <Cad_Tools.hxx>
#include <Cad_CurveTools.hxx>
#include <Cad_GeomSurface.hxx>
#include <Cad_GeomCurve.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

Standard_Integer tnbLib::VoyageGeo_PathGeneration::DEFAULT_NB_SAMPLES = 30;

void tnbLib::VoyageGeo_PathGeneration::Perform()
{
	if (NOT Earth())
	{
		FatalErrorIn(FunctionSIG)
			<< "no earth has been found." << endl
			<< abort(FatalError);
	}
	if (Offsets().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no offset point has been detected." << endl
			<< abort(FatalError);
	}
	for (const auto& x:Offsets())
	{
		if (x->NbPoints() < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "no valid path has been found." << endl
				<< abort(FatalError);
		}
	}
	auto earth = Earth();
	const auto& surface = earth->Surface();
	auto domain = surface->ParametricBoundingBox();

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	Standard_Integer i = 0;
	for (const auto& path:Offsets())
	{
		const auto& coords = path->Points();
		const auto& p0 = FirstItem(coords);
		const auto& p1 = LastItem(coords);
		
		auto offsets =
			Voyage_Tools::ShortestStraightPath(p0, p1, surface);
		if (offsets.size() IS_EQUAL 3)
		{
			/*{
				auto geom = Pln_CurveTools::MakeSegment(offsets.at(0), offsets.at(1));
				Mesh2d_CurveAnIso
					alg
					(
						geom, geom->FirstParameter(),
						geom->LastParameter(),
						MetricPrcsr(), CurveInfo()
					);
				alg.Perform();
				const auto& poly = alg.Mesh();
				std::vector<Pnt3d> coords;
				for (const auto& x : poly->Points())
				{
					auto pt = surface->Value(x);
					coords.push_back(std::move(pt));
				}
				auto curve = std::make_shared<Cad_GeomCurve>(Cad_CurveTools::Interpolation(coords));
				thePaths_.push_back(std::move(curve));
			}
			{
				auto geom = Pln_CurveTools::MakeSegment(offsets.at(1), offsets.at(2));
				Mesh2d_CurveAnIso
					alg
					(
						geom, geom->FirstParameter(),
						geom->LastParameter(),
						MetricPrcsr(), CurveInfo()
					);
				alg.Perform();
				const auto& poly = alg.Mesh();
				std::vector<Pnt3d> coords;
				for (const auto& x : poly->Points())
				{
					auto pt = surface->Value(x);
					coords.push_back(std::move(pt));
				}
				auto curve = std::make_shared<Cad_GeomCurve>(Cad_CurveTools::Interpolation(coords));
				thePaths_.push_back(std::move(curve));
			}*/
			NotImplemented;
		}
		else
		{
			auto geom_2d = Pln_CurveTools::Interpolation(coords);
			auto curve_2d = std::make_shared<Pln_Curve>(++i, std::move(geom_2d));
			curves.push_back(std::move(curve_2d));
		}
		
	}
	auto edges = Pln_Tools::RetrieveEdges(curves);
	auto path = std::make_shared<VoyageGeo_Path2>(std::move(edges), std::move(earth));
	thePath_ = std::move(path);
	Change_IsDone() = Standard_True;
}