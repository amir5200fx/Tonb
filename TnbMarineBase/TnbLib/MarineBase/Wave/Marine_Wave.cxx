#include <Marine_Wave.hxx>

#include <Entity3d_Box.hxx>

#include <gp_Ax3.hxx>
#include <gp_Ax2.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>

tnbLib::Pnt3d
tnbLib::Marine_Wave::ProjectedCoordOnSurface() const
{
	Debug_Null_Pointer(SurfaceGeometry());

	GeomAPI_ProjectPointOnSurf proj;
	proj.Init(PointOnWater(), SurfaceGeometry());

	proj.Perform(PointOnWater());
	if (NOT proj.IsDone())
	{
		FatalErrorIn("Pnt3d Marine_Wave::ProjectedCoordOnSurface() const")
			<< "the projection is not performed!" << endl
			<< abort(FatalError);
	}

	return proj.NearestPoint();
}

tnbLib::Entity3d_Box 
tnbLib::Marine_Wave::BoundingBoxOfRotatedDomain
(
	const Entity3d_Box & theDomain
) const
{
	//auto loc = Origin().Location();
	
	auto p0 = theDomain.Corner(Box3d_PickAlgorithm::Box3d_PickAlgorithm_Aft_NE);
	auto p1 = theDomain.Corner(Box3d_PickAlgorithm::Box3d_PickAlgorithm_Aft_NW);
	auto p2 = theDomain.Corner(Box3d_PickAlgorithm::Box3d_PickAlgorithm_Aft_SE);
	auto p3 = theDomain.Corner(Box3d_PickAlgorithm::Box3d_PickAlgorithm_Aft_SW);

	auto p4 = theDomain.Corner(Box3d_PickAlgorithm::Box3d_PickAlgorithm_Fwd_NE);
	auto p5 = theDomain.Corner(Box3d_PickAlgorithm::Box3d_PickAlgorithm_Fwd_NW);
	auto p6 = theDomain.Corner(Box3d_PickAlgorithm::Box3d_PickAlgorithm_Fwd_SE);
	auto p7 = theDomain.Corner(Box3d_PickAlgorithm::Box3d_PickAlgorithm_Fwd_SW);

	std::vector<Pnt3d> pts;
	pts.reserve(8);

	auto t = originToCurrentTransform.Inverted();

	pts.push_back(p0.Transformed(t));
	pts.push_back(p1.Transformed(t));
	pts.push_back(p2.Transformed(t));
	pts.push_back(p3.Transformed(t));
														  
	pts.push_back(p4.Transformed(t));
	pts.push_back(p5.Transformed(t));
	pts.push_back(p6.Transformed(t));
	pts.push_back(p7.Transformed(t));

	auto box = Entity3d_Box::BoundingBoxOf(pts);
	return std::move(box);
}

void tnbLib::Marine_Wave::TransformOriginToCurrent() const
{
	gp_Trsf t;
	t.SetTransformation(Origin(), 
		gp_Ax2(Origin().Location(), 
			VerticalDirection(), SurfaceDirection()));
	originToCurrentTransform = std::move(t);
}


tnbLib::Marine_WaveDensity::Marine_WaveDensity()
	: theLightFluidDensity_("light fluid density", 1.225)
	, theHeavyFluidDensity_("heavy fluid density", 998.0)
{
}



void tnbLib::Marine_Wave::MakeGeometrySurface
(
	const Standard_Real y0,
	const Standard_Real y1
)
{
	Debug_Null_Pointer(CurveGeometry());

	auto profile = 
		Handle(Geom2d_BSplineCurve)::DownCast(CurveGeometry());
	Debug_Null_Pointer(profile);

	const auto& poles2 = profile->Poles();
	TColgp_Array1OfPnt poles(1, profile->Poles().Size());

	forThose(Index, 1, poles.Size())
	{
		poles.SetValue(Index, Pnt3d(poles2.Value(Index).X(), poles2.Value(Index).Y(), 0));
	}

	Handle(Geom_Curve) base = 
		new Geom_BSplineCurve(poles, profile->Knots(),
			profile->Multiplicities(), profile->Degree());
	Debug_Null_Pointer(base);
	
	Handle(Geom_Surface) extruded = new Geom_SurfaceOfLinearExtrusion(base, Dir3d(0, 1, 0));
	Handle(Geom_Surface) surface = 
		new Geom_RectangularTrimmedSurface
		(
			extruded,base->FirstParameter(), base->LastParameter(), y0, y1
		);
	Debug_Null_Pointer(surface);

	ChangeSurfaceGeometry() = surface;	
}

void tnbLib::Marine_Wave::TransportGeometrySurface()
{
	const auto& surface = SurfaceGeometry();
	Debug_Null_Pointer(surface);

	surface->Transform(originToCurrentTransform);
}

void tnbLib::Marine_Wave::TranslateSurfaceToPointOnWater
(
	const Pnt3d & theProj
)
{
	const auto& surface = SurfaceGeometry();
	Debug_Null_Pointer(surface);

	surface->Translate(theProj, PointOnWater());
}

gp_Ax2 
tnbLib::Marine_Wave::SurfaceCoordinateSystem() const
{
	return gp_Ax2(PointOnWater(), VerticalDirection(), Current());
}

void tnbLib::Marine_Wave::Perform()
{
	//theOrigin_ = gp_Ax2(MEAN(Domain().P0(), Domain().P1()), Dir3d(0, 0, 1.0), Dir3d(1, 0, 0));
	TransformOriginToCurrent();

	auto expanded = Entity3d_Box::Union(BoundingBoxOfRotatedDomain(*Domain()), *Domain());

	const auto& ep0 = expanded.P0();
	const auto& ep1 = expanded.P1();
	
	const auto& loc = Origin().Location();
	MakeProfileCurve(Pnt2d(ep0.X(), loc.Z()), Pnt2d(ep1.X(), loc.Z()));

	MakeGeometrySurface(ep0.Y(), ep1.Y());

	TransportGeometrySurface();

	TranslateSurfaceToPointOnWater(ProjectedCoordOnSurface());

	Change_IsDone() = Standard_True;
}