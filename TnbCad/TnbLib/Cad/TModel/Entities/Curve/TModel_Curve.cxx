#include <TModel_Curve.hxx>

#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Curve.hxx>
#include <Geom_BoundedCurve.hxx>

void tnbLib::TModel_Curve::CheckBoundary
(
	const Standard_Real x, 
	const char * theName
) const
{
	Debug_Null_Pointer(Geometry());
	if (NOT INSIDE(x, Geometry()->FirstParameter(), Geometry()->LastParameter()))
	{
		FatalErrorIn(theName) << endl
			<< "the geometry curve is not bounded!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::TModel_Curve::CheckBounded
(
	const Handle(Geom_Curve)& theCurve, 
	const char * theName
)
{
	if (NOT Handle(Geom_BoundedCurve)::DownCast(theCurve))
	{
		FatalErrorIn(theName) << endl
			<< "the geometry curve is not bounded!" << endl
			<< abort(FatalError);
	}
}

tnbLib::TModel_Curve::TModel_Curve
(
	const Handle(Geom_Curve) theGeometry
)
	: theGeometry_(theGeometry)
{
	CheckBounded(Geometry(), "TModel_Curve::TModel_Curve()");
}

Standard_Real 
tnbLib::TModel_Curve::FirstParameter() const
{
	Debug_Null_Pointer(Geometry());
	return Geometry()->FirstParameter();
}

Standard_Real 
tnbLib::TModel_Curve::LastParameter() const
{
	Debug_Null_Pointer(Geometry());
	return Geometry()->LastParameter();
}

tnbLib::Pnt3d
tnbLib::TModel_Curve::Value
(
	const Standard_Real x
) const
{
	Debug_Null_Pointer(Geometry());
#ifdef FULLDEBUG
	CheckBoundary(x, "Pnt3d Value(const Standard_Real x) const");
#endif
	auto value = Geometry()->Value(x);
	return std::move(value);
}

tnbLib::Pnt3d 
tnbLib::TModel_Curve::Value_normParam
(
	const Standard_Real x
) const
{
	auto p = FirstParameter() + x * (LastParameter() - FirstParameter());
	auto value = Value(p);
	return std::move(value);
}

#include <Bnd_Box.hxx>
#include <BndLib_Add3dCurve.hxx>
#include <GeomAdaptor_Curve.hxx>

tnbLib::Entity3d_Box 
tnbLib::TModel_Curve::CalcBoundingBox() const
{
	Debug_Null_Pointer(Geometry());
	Bnd_Box BndBox;
	BndLib_Add3dCurve::AddOptimal
	(
		GeomAdaptor_Curve(Geometry()),
		FirstParameter(),
		LastParameter(),
		0,
		BndBox
	);

	Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	BndBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

	Entity3d_Box box(Pnt3d(Xmin, Ymin, Zmin), Pnt3d(Xmax, Ymax, Zmax));
	return std::move(box);
}