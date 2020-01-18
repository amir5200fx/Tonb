#include <Pln_Curve.hxx>

#include <Entity2d_Box.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <StdFail_NotDone.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>

void tnbLib::Pln_Curve::CheckBoundary(const Standard_Real x, const char* theName) const
{
	Debug_Null_Pointer(Geometry());
	if (NOT INSIDE(x, Geometry()->FirstParameter(), Geometry()->LastParameter()))
	{
		FatalErrorIn(theName) << endl
			<< "the geometry curve is not bounded!" << endl
			<< abort(FatalError);
	}
}

namespace tnbLib
{

	namespace plnCurveLib
	{

		static void CheckBounded(const Handle(Geom2d_Curve)& theCurve, const char* theName)
		{
			if (NOT Handle(Geom2d_BoundedCurve)::DownCast(theCurve))
			{
				FatalErrorIn(theName) << endl
					<< "the geometry curve is not bounded!" << endl
					<< abort(FatalError);
			}
		}
	}
}

tnbLib::Pln_Curve::Pln_Curve
(
	const Handle(Geom2d_Curve)& theGeom, 
	const std::shared_ptr<info>& theInfo
)
	: theInfo_(theInfo)
	, theGeometry_(theGeom)
{
	plnCurveLib::CheckBounded(theGeom, "Pln_Curve()");
}

tnbLib::Pln_Curve::Pln_Curve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theGeom, 
	const std::shared_ptr<info>& theInfo
)
	: Pln_Entity(theIndex, theName)
	, theInfo_(theInfo)
	, theGeometry_(theGeom)
{
	plnCurveLib::CheckBounded(theGeom, "Pln_Curve()");
}

Standard_Real 
tnbLib::Pln_Curve::FirstParameter() const
{
	Debug_Null_Pointer(Geometry());
	return Geometry()->FirstParameter();
}

Standard_Real 
tnbLib::Pln_Curve::LastParameter() const
{
	Debug_Null_Pointer(Geometry());
	return Geometry()->LastParameter();
}

tnbLib::Pnt2d 
tnbLib::Pln_Curve::Value
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
tnbLib::Pln_Curve::Value_normParam
(
	const Standard_Real x
) const
{
	auto p = FirstParameter() + x * (LastParameter() - FirstParameter());
	auto value = Value(p);
	return std::move(value);
}

tnbLib::Entity2d_Box 
tnbLib::Pln_Curve::CalcBoundingBox() const
{
	Debug_Null_Pointer(Geometry());
	Bnd_Box2d BndBox;
	BndLib_Add2dCurve::Add(Geometry(), FirstParameter(), LastParameter(), 0, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax;
	BndBox.Get(Xmin, Ymin, Xmax, Ymax);

	Entity2d_Box box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
	return std::move(box);
}

void tnbLib::Pln_Curve::Interpolation
(
	const std::vector<Pnt2d>& theQ, 
	const Standard_Integer theDeg,
	const Standard_Real theTol
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn("void Pln_Curve::Interpolation(const pointList & theQ, const Standard_Integer theDeg, const Standard_Real theTolerance)")
			<< "Not enough points"
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) PtsPtr = new TColgp_HArray1OfPnt2d(1, (Standard_Integer)theQ.size());
	auto& Pts = *PtsPtr;
	forThose(Index, 0, theQ.size() - 1)
		Pts.SetValue(Index + 1, theQ[Index]);

	Geom2dAPI_Interpolate Interpolation(PtsPtr, Standard_False, theTol);
	Interpolation.Perform();

	if (!Interpolation.IsDone())
	{
		FatalErrorIn("void Pln_Curve::Interpolation(const pointList & theQ, const Standard_Integer theDeg, const Standard_Real theTolerance)")
			<< "Failed to interpolation!"
			<< abort(FatalError);
	}

	try
	{
		ChangeGeometry() = Interpolation.Curve();
	}
	catch (StdFail_NotDone&)
	{
		FatalErrorIn("void Pln_Curve::Interpolation(const pointList & theQ, const Standard_Integer theDeg, const Standard_Real theTolerance)")
			<< "Failed to interpolation!"
			<< abort(FatalError);
	}
}