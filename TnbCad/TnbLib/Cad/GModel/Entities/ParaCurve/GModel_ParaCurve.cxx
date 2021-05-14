#include <GModel_ParaCurve.hxx>

#include <Global_Macros.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_BoundedCurve.hxx>

void tnbLib::GModel_ParaCurve::CheckBoundary
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

void tnbLib::GModel_ParaCurve::CheckBounded
(
	const Handle(Geom2d_Curve)& theCurve,
	const char * theName
)
{
	if (NOT Handle(Geom2d_BoundedCurve)::DownCast(theCurve))
	{
		FatalErrorIn(theName) << endl
			<< "the geometry curve is not bounded!" << endl
			<< abort(FatalError);
	}
}

tnbLib::GModel_ParaCurve::GModel_ParaCurve
(
	const Handle(Geom2d_Curve)& theGeometry
)
	: theGeometry_(theGeometry)
{
	CheckBounded(Geometry(), "GModel_ParaCurve::GModel_ParaCurve()");
}

tnbLib::GModel_ParaCurve::GModel_ParaCurve
(
	Handle(Geom2d_Curve)&& theGeometry
)
	: theGeometry_(std::move(theGeometry))
{
	CheckBounded(Geometry(), "GModel_ParaCurve::GModel_ParaCurve()");
}

Standard_Real 
tnbLib::GModel_ParaCurve::FirstParameter() const
{
	Debug_Null_Pointer(Geometry());
	return Geometry()->FirstParameter();
}

Standard_Real 
tnbLib::GModel_ParaCurve::LastParameter() const
{
	Debug_Null_Pointer(Geometry());
	return Geometry()->LastParameter();
}

tnbLib::Pnt2d 
tnbLib::GModel_ParaCurve::Value
(
	const Standard_Real x
) const
{
	Debug_Null_Pointer(Geometry());
#ifdef FULLDEBUG
	CheckBoundary(x, "Pnt2d Value(const Standard_Real x) const");
#endif
	auto value = Geometry()->Value(x);
	return std::move(value);
}

tnbLib::Pnt2d 
tnbLib::GModel_ParaCurve::Value_normParam
(
	const Standard_Real x
) const
{
	auto p = FirstParameter() + x * (LastParameter() - FirstParameter());
	auto value = Value(p);
	return std::move(value);
}

#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>

tnbLib::Entity2d_Box
tnbLib::GModel_ParaCurve::CalcBoundingBox() const
{
	Debug_Null_Pointer(Geometry());
	Bnd_Box2d BndBox;
	BndLib_Add2dCurve::Add(Geometry(), FirstParameter(), LastParameter(), 0, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax;
	BndBox.Get(Xmin, Ymin, Xmax, Ymax);

	Entity2d_Box box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
	return std::move(box);
}