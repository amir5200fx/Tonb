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
	const auto& p0 = theDomain.P0();
	const auto& p1 = theDomain.P1();

	auto pp0 = p0.Transformed(originToCurrentTransform);
	auto pp1 = p1.Transformed(originToCurrentTransform);

	auto x0 = MIN(pp0.X(), pp1.X());
	auto x1 = MAX(pp0.X(), pp1.X());

	auto y0 = MIN(pp0.Y(), pp1.Y());
	auto y1 = MAX(pp0.Y(), pp1.Y());

	auto z0 = MIN(pp0.Z(), pp1.Z());
	auto z1 = MAX(pp0.Z(), pp1.Z());

	Entity3d_Box box(Pnt3d(x0, y0, z0), Pnt3d(x1, y1, z1));
	return std::move(box);
}

void tnbLib::Marine_Wave::TransformOriginToCurrent() const
{
	gp_Trsf t;
	t.SetTransformation(Origin(), 
		gp_Ax2(Origin().Location(), 
			VerticalDirection(), Current()));
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

	Standard_Integer K = 0;
	for (auto& x : poles)
	{
		++K;
		x = Pnt3d(poles2.Value(K).X(), poles2.Value(K).Y(), 0);
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
	
	TransformOriginToCurrent();
	
	auto expanded = Entity3d_Box::Union(BoundingBoxOfRotatedDomain(Domain()), Domain());
	
	const auto& ep0 = expanded.P0();
	const auto& ep1 = expanded.P1();
	
	const auto& loc = Origin().Location();
	MakeProfileCurve(Pnt2d(ep0.X(), loc.Z()), Pnt2d(ep1.X(), loc.Z()));

	MakeGeometrySurface(ep0.Y(), ep1.Y());

	TransportGeometrySurface();

	TranslateSurfaceToPointOnWater(ProjectedCoordOnSurface());
}