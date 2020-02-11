#include <Pln_Curve.hxx>

#include <Entity2d_Box.hxx>
#include <Pln_Tools.hxx>
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
	const Handle(Geom2d_Curve)& theGeom
)
	: theGeometry_(theGeom)
{
	plnCurveLib::CheckBounded(theGeom, "Pln_Curve()");
}

tnbLib::Pln_Curve::Pln_Curve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theGeom
)
	: Pln_Entity(theIndex)
	, theGeometry_(theGeom)
{
	plnCurveLib::CheckBounded(theGeom, "Pln_Curve()");
}

tnbLib::Pln_Curve::Pln_Curve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theGeom
)
	: Pln_Entity(theIndex, theName)
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

std::tuple<std::shared_ptr<tnbLib::Pln_Curve>, std::shared_ptr<tnbLib::Pln_Curve>>
tnbLib::Pln_Curve::Split(const Standard_Real x) const
{
	if (NOT INSIDE(x, FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split()")
			<< "Invalid Parameter: " << x << endl
			<< " - First parameter: " << FirstParameter() << endl
			<< " - Last Parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) C0, C1;
	Pln_Tools::SplitCurve(Geometry(), x, C0, C1);

	return 
	{ 
		std::make_shared<Pln_Curve>(C0) , 
		std::make_shared<Pln_Curve>(C1) 
	};
}

void tnbLib::Pln_Curve::Split
(
	const Standard_Real x,
	std::shared_ptr<Pln_Curve>& theLeft, 
	std::shared_ptr<Pln_Curve>& theRight
) const
{
	if (NOT INSIDE(x, FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split()")
			<< "Invalid Parameter: " << x << endl
			<< " - First parameter: " << FirstParameter() << endl
			<< " - Last Parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) C0, C1;
	Pln_Tools::SplitCurve(Geometry(), x, C0, C1);

	theLeft = std::make_shared<Pln_Curve>(C0);
	theRight = std::make_shared<Pln_Curve>(C1);
}

void tnbLib::Pln_Curve::Split
(
	const Standard_Real x, 
	Pnt2d & theCoord,
	std::shared_ptr<Pln_Curve>& theLeft, 
	std::shared_ptr<Pln_Curve>& theRight
) const
{
	if (NOT INSIDE(x, FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split()")
			<< "Invalid Parameter: " << x << endl
			<< " - First parameter: " << FirstParameter() << endl
			<< " - Last Parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) C0, C1;
	Pln_Tools::SplitCurve(Geometry(), x, C0, C1);

	theCoord = Geometry()->Value(x);

	theLeft = std::make_shared<Pln_Curve>(C0);
	theRight = std::make_shared<Pln_Curve>(C1);
}

namespace tnbLib
{

	void CheckSort(const std::vector<Standard_Real>& theParameters, const char* theName)
	{
		auto x0 = RealFirst();
		for (const auto x : theParameters)
		{
			if (x <= x0)
			{
				FatalErrorIn(theName)
					<< "Invalid Parameters to subdivide the curve!" << endl
					<< abort(FatalError);
			}
			x0 = x;
		}
	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>>
tnbLib::Pln_Curve::Split
(
	const std::vector<Standard_Real>& theParameters
) const
{
	if (NOT theParameters.size())
	{
		FatalErrorIn("void Split(...)")
			<< "empty list: there is no parameter to split the curve" << endl
			<< abort(FatalError);
	}

	CheckSort(theParameters, "void Split(...)");

	if (NOT INSIDE(theParameters[0], FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split(...)")
			<< "Invalid parameters to split the curve: the first parameter is outside the boundary!" << endl
			<< abort(FatalError);
	}

	if (NOT INSIDE(theParameters[theParameters.size() - 1], FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split(...)")
			<< "Invalid parameters to split the curve: the last parameter is outside the boundary!" << endl
			<< abort(FatalError);
	}

	auto curve = std::dynamic_pointer_cast<Pln_Curve>(This());
	
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(theParameters.size() + 1);

	for (const auto x : theParameters)
	{
		Debug_Null_Pointer(curve);
		auto[left, right] = curve->Split(x);

		curves.push_back(std::move(left));

		curve = std::move(right);
	}
	curves.push_back(std::move(curve));

	return std::move(curves);
}

void tnbLib::Pln_Curve::Split
(
	const std::vector<Standard_Real>& theParameters, 
	std::vector<Pnt2d>& theCoords,
	std::vector<std::shared_ptr<Pln_Curve>>& theCurves
) const
{
	if (NOT theParameters.size())
	{
		return;
	}

	CheckSort(theParameters, "void Split(...)");

	if (NOT INSIDE(theParameters[0], FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split(...)")
			<< "Invalid parameters to split the curve: the first parameter is outside the boundary!" << endl
			<< abort(FatalError);
	}

	if (NOT INSIDE(theParameters[theParameters.size() - 1], FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split(...)")
			<< "Invalid parameters to split the curve: the last parameter is outside the boundary!" << endl
			<< abort(FatalError);
	}

	auto curve = std::dynamic_pointer_cast<Pln_Curve>(This());

	theCoords.reserve(theParameters.size());
	theCurves.reserve(theParameters.size() + 1);

	for (const auto x : theParameters)
	{
		Debug_Null_Pointer(curve);

		std::shared_ptr<Pln_Curve> left, right;
		Pnt2d coord;

		curve->Split(x, coord, left, right);

		theCoords.push_back(std::move(coord));
		theCurves.push_back(std::move(left));

		curve = std::move(right);
	}
	theCurves.push_back(std::move(curve));
}

#include <Cad2d_GeoSketch_Circle.hxx>
#include <Cad2d_GeoSketch_Ellipse.hxx>
#include <Cad2d_GeoSketch_LineSegment.hxx>

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::Pln_Curve::MakeLineSegment
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	auto sketch = 
		std::make_shared<Cad2d_GeoSketch_LineSegment>(theP0, theP1);
	Debug_Null_Pointer(sketch);

	auto curve = std::make_shared<Pln_Curve>(sketch->Geometry());
	return std::move(curve);
}

