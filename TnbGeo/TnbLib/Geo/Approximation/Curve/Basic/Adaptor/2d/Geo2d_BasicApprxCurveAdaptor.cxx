#include <Geo2d_BasicApprxCurveAdaptor.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

template<>
gp_Pnt2d tnbLib::Geo2d_BasicApprxCurveAdaptor::Value(const Standard_Real x) const
{
	Debug_Null_Pointer(this->Geometry());
	return this->Geometry()->Value(x);
}