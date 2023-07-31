#include <VoyageGeo_PathGeneration.hxx>

#include <VoyageGeo_GreateCircleNav.hxx>
#include <Voyage_Tools.hxx>
#include <Mesh2d_CurveAnIso.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <Cad_Tools.hxx>
#include <Cad_CurveTools.hxx>
#include <Cad_GeomSurface.hxx>
#include <Cad_GeomCurve.hxx>
#include <Pln_CurveTools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

void tnbLib::VoyageGeo_PathGeneration::Perform()
{
	if (NOT Surface())
	{
		FatalErrorIn(FunctionSIG)
			<< "no surface has been found." << endl
			<< abort(FatalError);
	}
	if (NOT CurveInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve info. has been found." << endl
			<< abort(FatalError);
	}
	if (NOT MetricPrcsr())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric processor has been found." << endl
			<< abort(FatalError);
	}
	if (theCoords_.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "no valid path has been found." << endl
			<< abort(FatalError);
	}
	const auto& surface = Surface();
	auto domain = surface->ParametricBoundingBox();

	for (size_t i = 1; i < Coords().size(); i++)
	{
		const auto& p0 = Coords().at(i - 1);
		const auto& p1 = Coords().at(i);

		auto offsets = Voyage_Tools::ShortestStraightPath(p0, p1, surface);

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
			/*auto geom = Pln_CurveTools::MakeSegment(p0, p1);
			std::cout << "the curve is created" << std::endl;
			std::cout << geom->FirstParameter() << std::endl;
			std::cout << geom->LastParameter() << std::endl;
			Debug_Null_Pointer(geom);
			Mesh2d_CurveAnIso
				alg
				(
					geom, geom->FirstParameter(),
					geom->LastParameter(),
					MetricPrcsr(), CurveInfo()
				);
			alg.Perform();
			const auto& poly = alg.Mesh();
			std::cout << "size = " << poly->NbPoints() << std::endl;*/
			//std::vector<Pnt2d> pts2d;

			auto waypoints = std::make_shared<VoyageGeo_GreateCircleNav>(p0, p1);
			
			Standard_Integer n = 100;
			const auto du = (waypoints->Sigma2() - waypoints->Sigma1()) / (Standard_Real)(n);
			//const auto du = 1.0 / (Standard_Real)(n);

			std::vector<Standard_Real> us;
			us.reserve(n + 1);
			for (size_t k = 0; k <= n; k++)
			{
				us.push_back(waypoints->Sigma1() + (Standard_Real)k * du);
			}
			auto pts2 = waypoints->CalcWayPoints(us);

			//auto du = (p1 - p0) / (Standard_Real)n;
			//for (size_t k = 0; k <= n; k++)
			//{
			//	auto p2 = p0 + k * du;
			//	pts2d.push_back(std::move(p2));
			//}
			
			std::vector<Pnt3d> coords;
			for (const auto& x : /*poly->Points()*/pts2)
			{
				auto pt = surface->Value({x.Y() + PI, x.X()});
				//std::cout <<"pt = " << pt << std::endl;
				coords.push_back(std::move(pt));
			}

			auto curve = std::make_shared<Cad_GeomCurve>(Cad_CurveTools::Interpolation(coords));
			thePaths_.push_back(std::move(curve));
		}
	}
	Change_IsDone() = Standard_True;
}