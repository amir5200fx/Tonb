#include <Geo3d_BasicApprxCurveAdaptor.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Curve.hxx>

template<>
gp_Pnt tnbLib::Geo3d_BasicApprxCurveAdaptor::Value(const Standard_Real x) const
{
	Debug_Null_Pointer(this->Geometry());
	return this->Geometry()->Value(x);
}