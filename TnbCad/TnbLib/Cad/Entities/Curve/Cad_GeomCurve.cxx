#include <Cad_GeomCurve.hxx>

#include <Entity3d_Box.hxx>
#include <Pnt3d.hxx>
#include <Cad_Tools.hxx>

#include <Geom_Curve.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BndLib_Add3dCurve.hxx>
#include <Adaptor3d_Curve.hxx>

void tnbLib::Cad_GeomCurve::CheckBounded(const Handle(Geom_Curve)& theCurve)
{
	if (NOT Cad_Tools::IsBounded(theCurve))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}
}

tnbLib::Cad_GeomCurve::Cad_GeomCurve(const Handle(Geom_Curve)& theGeometry)
	: theGeometry_(theGeometry)
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomCurve::Cad_GeomCurve(Handle(Geom_Curve) && theGeometry)
	: theGeometry_(std::move(theGeometry))
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomCurve::Cad_GeomCurve
(
	const Standard_Integer theIndex, 
	const Handle(Geom_Curve)& theGeometry
)
	: Global_Indexed(theIndex)
	, theGeometry_(theGeometry)
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomCurve::Cad_GeomCurve
(
	const Standard_Integer theIndex,
	Handle(Geom_Curve)&& theGeometry
)
	: Global_Indexed(theIndex)
	, theGeometry_(std::move(theGeometry))
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomCurve::Cad_GeomCurve
(
	const Standard_Integer theIndex,
	const word& theName,
	const Handle(Geom_Curve)& theGeometry
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theGeometry_(theGeometry)
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomCurve::Cad_GeomCurve
(
	const Standard_Integer theIndex,
	const word& theName,
	Handle(Geom_Curve) && theGeometry
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theGeometry_(std::move(theGeometry))
{
	CheckBounded(Geometry());
}

Standard_Real 
tnbLib::Cad_GeomCurve::FirstParameter() const
{
	return Geometry()->FirstParameter();
}

Standard_Real 
tnbLib::Cad_GeomCurve::LastParameter() const
{
	return Geometry()->LastParameter();
}

tnbLib::Pnt3d 
tnbLib::Cad_GeomCurve::Value(const Standard_Real x) const
{
	auto pt = Pnt3d(Geometry()->Value(x));
	return std::move(pt);
}

//tnbLib::Entity3d_Box 
//tnbLib::Cad_GeomCurve::CalcBoundingBox() const
//{
//	
//}