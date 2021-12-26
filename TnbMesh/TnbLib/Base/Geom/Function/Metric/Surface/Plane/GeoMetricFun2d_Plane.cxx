#include <GeoMetricFun2d_Plane.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Plane.hxx>

void tnbLib::GeoMetricFun2d_Plane::CalcMetric()
{
	Debug_Null_Pointer(theSurface_);

	gp_Vec D1U, D1V;
	gp_Pnt Pt;

	auto p = BoundingBox().CalcCentre();
	theSurface_->D1(p.X(), p.Y(), Pt, D1U, D1V);

	Standard_Real A = D1U.Dot(D1U);
	Standard_Real B = D1U.Dot(D1V);
	Standard_Real C = D1V.Dot(D1V);

	Entity2d_Metric1 m(A, B, C);

	SetMetric(std::move(m));

	Change_IsDone() = Standard_True;
}