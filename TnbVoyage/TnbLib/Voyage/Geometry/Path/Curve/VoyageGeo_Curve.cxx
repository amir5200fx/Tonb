#include <VoyageGeo_Curve.hxx>

#include <Mesh2d_CurveAnIso.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Pln_Curve.hxx>
#include <Dir2d.hxx>
#include <Vec2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

tnbLib::Pnt2d 
tnbLib::VoyageGeo_Curve::Value(const Standard_Real x) const
{
	Debug_Null_Pointer(theGeometry_);
	auto pt = theGeometry_->Value(x);
	return std::move(pt);
}

tnbLib::Dir2d 
tnbLib::VoyageGeo_Curve::CalcNormal(const Standard_Real t) const
{
	Debug_Null_Pointer(theGeometry_);
	auto [pt, n] = theGeometry_->D1(t);
	n.Rotate(PI / 2.0);
	return std::move(n);
}

tnbLib::Pnt2d 
tnbLib::VoyageGeo_Curve::Start() const
{
	Debug_Null_Pointer(theGeometry_);
	auto pt = theGeometry_->Value(theGeometry_->FirstParameter());
	return std::move(pt);
}

tnbLib::Pnt2d
tnbLib::VoyageGeo_Curve::End() const
{
	Debug_Null_Pointer(theGeometry_);
	auto pt = theGeometry_->Value(theGeometry_->LastParameter());
	return std::move(pt);
}

std::vector<Standard_Real> 
tnbLib::VoyageGeo_Curve::Discrete
(
	const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& thePrcsr,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
) const
{

	Mesh2d_CurveAnIso alg
	(
		theGeometry_->Geometry(), 
		theGeometry_->FirstParameter(), 
		theGeometry_->LastParameter(), 
		thePrcsr, theInfo
	);
	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the application is not performed");
	auto mesh = alg.Parameters();
	return std::move(mesh);
}