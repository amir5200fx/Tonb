#include <Cad_gSingularity.hxx>

#include <Aft2d_gRegionPlaneSurface.hxx>
#include <Mesh2d_Element.hxx>
#include <Cad_LineSingularZone_Loop.hxx>
#include <Cad_PoleSingularZone_Loop.hxx>
#include <Cad_PoleSingularZone_PartialSide.hxx>
#include <Cad_PoleSingularZone_WholeSide.hxx>
#include <Cad_PoleSingularZone_Corner.hxx>
#include <Cad_LineSingularZone_Dangle.hxx>
#include <Cad_LineSingularZone_Corner.hxx>
#include <Cad_LineSingularZone_Loop.hxx>
#include <Cad_LineSingularZone_TwoSide.hxx>
#include <Cad_LineSingularZone_WholeSide.hxx>
#include <Cad_SingularityTools.hxx>
#include <Cad_gPoleSingularCurve.hxx>
#include <Cad_gLineSingularCurve.hxx>
#ifdef _DEBUG
#include <Cad_SingularityHorizons.hxx>
#include <Cad_ColorApprxMetric.hxx>
#include <Cad_SingularityTools.hxx>
#include <Geo2d_PolygonGraph.hxx>
#include <Geo2d_LinTessellatePolygon.hxx>
#include <Geo2d_InscConxPoly.hxx>
#include <Geo_BoxTools.hxx>
#endif // _DEBUG
#include <GModel_ParaCurve.hxx>
#include <Cad_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Geo_Tools.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo2d_NormalizePolygon.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo2d_LinTessellatePolygon.hxx>
#include <Geo2d_InscConxPoly.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom_Surface.hxx>
#include <opencascade/Geom2dAPI_ProjectPointOnCurve.hxx>

unsigned short tnbLib::Cad_gSingularity::verbose(0);
const Standard_Real tnbLib::Cad_gSingularity::DEFAULT_WEIGHT = 1.25;

template<>
std::shared_ptr<tnbLib::Cad_gSingularZone> 
tnbLib::Cad_gSingularity::TypeDetection
(
	const std::shared_ptr<Entity2d_Polygon>& thePoly,
	const GeoMesh2d_Data& theBMesh, 
	const std::vector<std::shared_ptr<Pln_Curve>>& theSides, 
	const Geom_Surface& theSurface,
	const Standard_Real theDim
) const
{
	if (NOT this->SizeFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size function has been found!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(thePoly);
	const auto& polyRef = *thePoly;

	//std::cout << "run...." << std::endl;
	//OFstream myFile("metric.plt");
	// checking the polygon [3/29/2022 Amir]
	Entity2d_Polygon::Check(polyRef);
	//{
	//	theBMesh.StaticData()->ExportToPlt(myFile);
	//	polyRef.ExportToPlt(myFile);

	//	auto pp = std::make_shared<Entity2d_Polygon>(polyRef);
	//	Geo2d_NormalizePolygon aa(pp);
	//	aa.Perform();

	//	auto bb = Geo_BoxTools::GetBox(pp->Points(), 1.0E-12);
	//	//PAUSE;
	//	{
	//		Geo2d_InscConxPoly convx(aa.Normalized(), 1.0E-6);
	//		convx.Perform();

	//		auto retrieved = Geo_Tools::DistributeInDomain(convx.ConvexHull()->Points(), bb);

	//		auto retPoly = std::make_shared<Entity2d_Polygon>(std::move(retrieved), 0);
	//		Geo2d_LinTessellatePolygon tess(retPoly);
	//		tess.Tessellate(2);


	//		//convx.ConvexHull()->ExportToPlt(myFile);
	//		tess.Tessellated()->ExportToPlt(myFile);
	//	}

	//	//std::exit(1);
	//}
	const auto& pts = polyRef.Points();
	const auto& p0 = FirstItem(pts);
	const auto& p1 = LastItem(pts);
	const auto& pm = pts.at(pts.size() / 2);

	Standard_Integer nbZones = 0;
	if (polyRef.IsClosed())
	{
		const auto length = Cad_Tools::CalcLength(polyRef, theSurface);
		const auto elmSize = std::min(this->SizeFun()->Value(pm), theDim);

		const auto b = Entity2d_Box::BoundingBoxOf(pts);
		auto curves = base::LineHorizonCurves_Loop(b);
		if (length <= Weight()*elmSize)
		{
			if (verbose)
			{
				Info << endl
					<< " - a Pole-Loop singularity has been detected..." << endl;
			}

			auto singularity = 
				std::make_shared<cadLib::PoleSingularZone_Loop<Aft2d_gRegionPlaneSurface>>
				(
					++nbZones,
					ParaPlane(),
					curves.at(0), curves.at(1), curves.at(2), curves.at(3)
					);
			return std::move(singularity);
		}
		else
		{
			if (verbose)
			{
				Info << endl
					<< " - a Line-Loop singularity has been detected..." << endl;
			}

			auto singularity = 
				std::make_shared<cadLib::LineSingularZone_Loop<Aft2d_gRegionPlaneSurface>>
				(
					++nbZones, 
					ParaPlane(), 
					curves.at(0), curves.at(1), curves.at(2), curves.at(3)
					);
			return std::move(singularity);
		}
	}
	else
	{
		const auto e0 = theBMesh.TriangleLocation(theBMesh.FirstElement(), p0);
		const auto e1 = theBMesh.TriangleLocation(theBMesh.FirstElement(), p1);
		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);

		const auto s0 = e0->Index();
		const auto s1 = e1->Index();

		/*const auto smax = std::max(s0, s1)%4;
		const auto smin = std::min(s0, s1);*/

		const auto& c0 = *theSides.at(Index_Of(s0));
		const auto& c1 = *theSides.at(Index_Of(s1));

		Geom2dAPI_ProjectPointOnCurve Projector;
		Projector.Init(p0, c0.Geometry(), c0.FirstParameter(), c0.LastParameter());
		const auto d0 = Projector.LowerDistance();

		Projector.Init(p1, c1.Geometry(), c1.FirstParameter(), c1.LastParameter());
		const auto d1 = Projector.LowerDistance();

		if (d0 > EPS6)
		{
			FatalErrorIn(FunctionSIG)
				<< "unexpected error has been occurred!" << endl
				<< " - d0: "<< d0 << endl
				<< abort(FatalError);
		}

		if (d1 > EPS6)
		{
			FatalErrorIn(FunctionSIG)
				<< "unexpected error has been occurred!" << endl
				<< " - d1: " << d1 << endl
				<< abort(FatalError);
		}

		const auto size0 = SizeFun()->Value(p0);
		const auto size1 = SizeFun()->Value(p1);
		const auto size = std::min(size0, size1);

		const auto length = Cad_Tools::CalcLength(polyRef, theSurface);

		if (length <= Weight()*size AND length < 0.025*theDim)
		{
			if (s0 IS_EQUAL s1)
			{
				if (ReversePolygon(Dir2d(thePoly->FirstPoint(), thePoly->LastPoint()), s0))
				{
					thePoly->Reverse();
				}
				auto normAlg = std::make_shared<Geo2d_NormalizePolygon>(thePoly);
				Debug_Null_Pointer(normAlg);

				normAlg->Perform();
				Debug_If_Condition_Message(NOT normAlg->IsDone(), "the application is not performed.");

				auto b = Geo_BoxTools::GetBox(thePoly->Points(), 1.0E-12);

				auto revPolyAlg = std::make_shared<Geo2d_InscConxPoly>(normAlg->Normalized(), 1.0E-6);
				Debug_Null_Pointer(revPolyAlg);

				revPolyAlg->Perform();
				Debug_If_Condition_Message(NOT revPolyAlg->IsDone(), "the application is not performed");

				auto tessAlg = std::make_shared<Geo2d_LinTessellatePolygon>(revPolyAlg->ConvexHull());
				Debug_Null_Pointer(tessAlg);

				tessAlg->Tessellate(2);
				Debug_If_Condition_Message(NOT tessAlg->IsDone(), "the application is not performed");

				const auto& tessellated = tessAlg->Tessellated();
				Debug_Null_Pointer(tessellated);

				auto retrieved = Geo_Tools::DistributeInDomain(tessellated->Points(), b);
				auto retPoly = std::make_shared<Entity2d_Polygon>(std::move(retrieved), 0);

				auto curve = Cad_SingularityTools::ParametricPoleCurve<Aft2d_gPlnCurveSurface>(*retPoly);
				Debug_Null_Pointer(curve);

				auto Pm = Cad_SingularityTools::FindParametricCoord(*retPoly, theSurface, 0.5*length);
				curve->SetMidCoord(std::move(Pm));

				auto singularity = 
					std::make_shared<cadLib::PoleSingularZone_PartialSide<Aft2d_gRegionPlaneSurface>>
					(++nbZones, ParaPlane(), curve);
				return std::move(singularity);

			}
			else if (std::abs(s0 - s1) IS_EQUAL 1 OR std::abs(s0 - s1) IS_EQUAL 3)
			{
				Standard_Integer Id = 1;
				if (std::abs(s0 - s1) IS_EQUAL 1) Id = std::max(s0, s1);
				const auto corner = GetCorner(Id);
				if (ReverseCrossZonesPolygon(thePoly->FirstPoint(), thePoly->LastPoint(), corner))
				{
					thePoly->Reverse();
				}
				auto normAlg = std::make_shared<Geo2d_NormalizePolygon>(thePoly);
				Debug_Null_Pointer(normAlg);

				normAlg->Perform();
				Debug_If_Condition_Message(NOT normAlg->IsDone(), "the application is not performed.");

				auto b = Geo_BoxTools::GetBox(thePoly->Points(), 1.0E-12);

				auto revPolyAlg = std::make_shared<Geo2d_InscConxPoly>(normAlg->Normalized(), 1.0E-6);
				Debug_Null_Pointer(revPolyAlg);

				revPolyAlg->Perform();
				Debug_If_Condition_Message(NOT revPolyAlg->IsDone(), "the application is not performed");

				auto tessAlg = std::make_shared<Geo2d_LinTessellatePolygon>(revPolyAlg->ConvexHull());
				Debug_Null_Pointer(tessAlg);

				tessAlg->Tessellate(2);
				Debug_If_Condition_Message(NOT tessAlg->IsDone(), "the application is not performed");

				const auto& tessellated = tessAlg->Tessellated();
				Debug_Null_Pointer(tessellated);

				auto retrieved = Geo_Tools::DistributeInDomain(tessellated->Points(), b);
				auto retPoly = std::make_shared<Entity2d_Polygon>(std::move(retrieved), 0);

				auto curve = Cad_SingularityTools::ParametricPoleCurve<Aft2d_gPlnCurveSurface>(*retPoly);
				Debug_Null_Pointer(curve);

				auto Pm = Cad_SingularityTools::FindParametricCoord(*retPoly, theSurface, 0.5*length);
				curve->SetMidCoord(std::move(Pm));

				auto singularity =
					std::make_shared<cadLib::PoleSingularZone_Corner<Aft2d_gRegionPlaneSurface>>
					(++nbZones, ParaPlane(), curve);
				return std::move(singularity);
			}
			else if (std::abs(s0 - s1) IS_EQUAL 2)
			{
				auto geom = Cad_SingularityTools::GetParaCurve(p0, p1);
				Debug_Null_Pointer(geom);

				auto pcurve = std::make_shared<GModel_ParaCurve>(std::move(geom));
				Debug_Null_Pointer(pcurve);

				const auto Pm = MEAN(p0, p1);
				auto curve = std::make_shared<Cad_gPoleSingularCurve>(std::move(pcurve), std::move(Pm));

				auto singularity =
					std::make_shared<cadLib::PoleSingularZone_Corner<Aft2d_gRegionPlaneSurface>>
					(++nbZones, ParaPlane(), curve);
				return std::move(singularity);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unspecified condition has been detected." << endl
					<< abort(FatalError);
			}
		}
		else
		{
			const auto b = Entity2d_Box::BoundingBoxOf(pts);

			if (s0 IS_EQUAL s1)
			{
				auto curves = base::LineHorizonCurves_Dangle(b, s0);

				auto singularity = 
					std::make_shared<cadLib::LineSingularZone_Dangle<Aft2d_gRegionPlaneSurface>>
					(++nbZones, ParaPlane(), curves.at(0), curves.at(1), curves.at(2));
				return std::move(singularity);
			}
			else if (std::abs(s0 - s1) IS_EQUAL 1 OR std::abs(s0 - s1) IS_EQUAL 3)
			{
				auto curves = 
					base::LineHorizonCurves_Corner
					(b, s0, theSurface, Weight()*size);

				auto singularity = 
					std::make_shared<cadLib::LineSingularZone_Corner<Aft2d_gRegionPlaneSurface>>
					(++nbZones, ParaPlane(), curves.at(0), curves.at(1));
				return std::move(singularity);
			}
			else if (std::abs(s0 - s1) IS_EQUAL 2)
			{
				auto curves = base::LineHorizonCurves_WholeSide(b, s0);

				auto singularity =
					std::make_shared<cadLib::LineSingularZone_WholeSide<Aft2d_gRegionPlaneSurface>>
					(++nbZones, ParaPlane(), curves.at(0));
				return std::move(singularity);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unspecified condition has been detected." << endl
					<< abort(FatalError);
			}
		}
		
	}

	FatalErrorIn(FunctionSIG)
		<< "unexpected situation has been detected!" << endl
		<< abort(FatalError);
	return std::shared_ptr<tnbLib::Cad_gSingularZone>();
}

template<>
std::shared_ptr<tnbLib::Cad_gSingularZone>
tnbLib::Cad_gSingularity::TypeDetection
(
	const std::shared_ptr<Entity2d_Polygon>& thePoly0,
	const std::shared_ptr<Entity2d_Polygon>& thePoly1,
	const GeoMesh2d_Data& bMesh,
	const std::vector<std::shared_ptr<Pln_Curve>>& theSides,
	const Geom_Surface& theSurface,
	const Standard_Real theDim
) const
{
	if (NOT this->SizeFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size function has been found!" << endl
			<< abort(FatalError);
	}

	const auto& polyRef0 = *thePoly0;
	const auto& polyRef1 = *thePoly1;
#ifdef _DEBUG
	Entity2d_Polygon::Check(polyRef0);
	Entity2d_Polygon::Check(polyRef1);
#endif // _DEBUG

	const auto& pts0 = polyRef0.Points();
	const auto& pts1 = polyRef1.Points();

	const auto& P00 = FirstItem(pts0);
	const auto& P01 = LastItem(pts0);

	const auto& P10 = FirstItem(pts1);
	const auto& P11 = LastItem(pts1);

	const auto& e00 = bMesh.TriangleLocation(bMesh.FirstElement(), P00);
	const auto& e01 = bMesh.TriangleLocation(bMesh.FirstElement(), P01);

	const auto s00 = e00->Index();
	const auto s01 = e01->Index();

	const auto& c00 = *theSides[Index_Of(s00)];
	const auto& c01 = *theSides[Index_Of(s01)];

	Geom2dAPI_ProjectPointOnCurve Projector;

	Projector.Init(P00, c00.Geometry(), c00.FirstParameter(), c00.LastParameter());
	const auto d00 = Projector.LowerDistance();

	Projector.Init(P01, c01.Geometry(), c01.FirstParameter(), c01.LastParameter());
	const auto d01 = Projector.LowerDistance();

	if (d00 > EPS12)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	if (d01 > EPS12)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	const auto& e10 = bMesh.TriangleLocation(bMesh.FirstElement(), P10);
	const auto& e11 = bMesh.TriangleLocation(bMesh.FirstElement(), P11);

	const auto s10 = e10->Index();
	const auto s11 = e11->Index();

	const auto& c10 = *theSides[Index_Of(s10)];
	const auto& c11 = *theSides[Index_Of(s11)];

	Projector.Init(P10, c10.Geometry(), c10.FirstParameter(), c10.LastParameter());
	const auto d10 = Projector.LowerDistance();

	Projector.Init(P11, c11.Geometry(), c11.FirstParameter(), c11.LastParameter());
	const auto d11 = Projector.LowerDistance();

	if (d10 > EPS12)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	if (d11 > EPS12)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	const auto size00 = SizeFun()->Value(P00);
	const auto size01 = SizeFun()->Value(P01);
	const auto size0 = std::min(size00, size01);

	const auto size10 = SizeFun()->Value(P10);
	const auto size11 = SizeFun()->Value(P11);
	const auto size1 = std::min(size10, size11);

	const auto box0 = Entity2d_Box::BoundingBoxOf(pts0);
	const auto box1 = Entity2d_Box::BoundingBoxOf(pts1);

	const auto box = Entity2d_Box::Union(box0, box1);

	const auto curves = base::LineHorizonCurves_TwoSided(box, s00);

	auto singularity = 
		std::make_shared<cadLib::LineSingularZone_TwoSide<Aft2d_gRegionPlaneSurface>>
		(++NbZonesRef(), ParaPlane(), curves.at(0), curves.at(1));
	return std::move(singularity);
}

#ifdef _DEBUG
template<>
void tnbLib::Cad_gSingularity::Perform()
{
	if (NOT SizeFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size fun has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT ParaPlane())
	{
		FatalErrorIn(FunctionSIG)
			<< "no plane has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Horizons())
	{
		FatalErrorIn(FunctionSIG)
			<< "no Horizon analysis has been found" << endl
			<< abort(FatalError);
	}

	if (NOT Horizons()->MetricCalculator())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric calculator has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT Colors())
	{
		FatalErrorIn(FunctionSIG)
			<< "no coloring has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT Horizons()->Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT Horizons()->HasHorizon())
	{
		Change_IsDone() = Standard_True;
	}
	else
	{
		auto d = Cad_SingularityHorizons::RetrieveDomain(*Horizons());
		//d.Expand(0.1*d.Diameter());
		const auto& gsurf = Horizons()->Geometry();

		const auto& colors = *Colors();

		std::map
			<
			Standard_Integer,
			std::shared_ptr<std::vector<std::shared_ptr<Entity2d_Polygon>>>
			>
			horizonMap;

		const auto& edges = Horizons()->Horizons()->Edges();

		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x.second);
			const auto& e = x.second;

			const auto& poly = e->Polygon();
			Debug_Null_Pointer(poly);

			const auto& horizon = *poly;
#ifdef _DEBUG
			//Cad_ColorApprxMetric::Check(horizon, colors);
#endif // _DEBUG
			const auto icolor = colors.Value(GetSamplePoint(horizon));

			auto iter = horizonMap.find(icolor);
			if (iter IS_EQUAL horizonMap.end())
			{
				auto polyList = std::make_shared<std::vector<std::shared_ptr<Entity2d_Polygon>>>();
				Debug_Null_Pointer(polyList);

				polyList->reserve(2);
				auto paired = std::make_pair(icolor, std::move(polyList));
				horizonMap.insert(std::move(paired));
			}
			horizonMap.at(icolor)->push_back(poly);
		}

		const auto tris = Cad_SingularityTools::GetTriangulation(d);
		const auto sides = Cad_SingularityTools::RetrieveSides(d);

		GeoMesh2d_Data bmesh;
		bmesh.Construct(*tris);

		auto& zones = ZonesRef();
		zones.reserve(horizonMap.size());

		const auto dim = EstimateDim();

		for (const auto& x : horizonMap)
		{
			Debug_Null_Pointer(x.second);
			const auto& l = *x.second;
			if (l.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "empty list has been detected!" << endl
					<< abort(FatalError);
			}
			if (l.size() IS_EQUAL 1)
			{
				Debug_Null_Pointer(l.front());
				auto t = TypeDetection(l.front(), bmesh, sides, *gsurf, dim);
				Debug_Null_Pointer(t);

				t->SetIndex(x.first);
				zones.push_back(std::move(t));
			}
			else if (l.size() IS_EQUAL 2)
			{
				const auto[pl0, pl1] = Cad_SingularityNonTempBase::RetrievePair(l);
				Debug_Null_Pointer(pl0);
				Debug_Null_Pointer(pl1);

				auto t = TypeDetection(pl0, pl1, bmesh, sides, *gsurf, dim);
				Debug_Null_Pointer(t);

				t->SetIndex(x.first);
				zones.push_back(std::move(t));
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unexpected situation has been detected!" << endl
					<< abort(FatalError);
			}
		}
	}

	Change_IsDone() = Standard_True;
}
#endif // _DEBUG
