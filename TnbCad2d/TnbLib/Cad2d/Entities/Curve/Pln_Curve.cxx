#include <Pln_Curve.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <Pln_Tools.hxx>
#include <Pln_TangCurve.hxx>
#include <Cad2d_IntsctEntity_TangSegment.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_Line.hxx>
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
			<< "the parameter exceeds the bounds of the curve!" << endl
			<< " - parameter: " << x << endl
			<< " - U0: " << Geometry()->FirstParameter() << endl
			<< " - U1: " << Geometry()->LastParameter() << endl
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
	Handle(Geom2d_Curve) && theGeom
)
	: theGeometry_(std::move(theGeom))
{
	plnCurveLib::CheckBounded(Geometry(), "Pln_Curve()");
}

tnbLib::Pln_Curve::Pln_Curve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theGeom
)
	: Global_Indexed(theIndex)
	, theGeometry_(theGeom)
{
	plnCurveLib::CheckBounded(theGeom, "Pln_Curve()");
}

tnbLib::Pln_Curve::Pln_Curve
(
	const Standard_Integer theIndex,
	Handle(Geom2d_Curve) && theGeom
)
	: Global_Indexed(theIndex)
	, theGeometry_(std::move(theGeom))
{
	plnCurveLib::CheckBounded(Geometry(), "Pln_Curve()");
}

tnbLib::Pln_Curve::Pln_Curve
(
	const Standard_Integer theIndex,
	const word & theName,
	const Handle(Geom2d_Curve)& theGeom
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theGeometry_(theGeom)
{
	plnCurveLib::CheckBounded(theGeom, "Pln_Curve()");
}

tnbLib::Pln_Curve::Pln_Curve
(
	const Standard_Integer theIndex,
	const word & theName,
	Handle(Geom2d_Curve) && theGeom
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theGeometry_(std::move(theGeom))
{
	plnCurveLib::CheckBounded(Geometry(), "Pln_Curve()");
}

Standard_Boolean 
tnbLib::Pln_Curve::IsRing
(
	const Standard_Real tol
) const
{
	if (FirstCoord().Distance(LastCoord()) <= tol)
	{
		return Standard_True;
	}
	else
		return Standard_False;
}

Standard_Boolean 
tnbLib::Pln_Curve::IsLinear() const
{
	if (auto g = Handle(Geom2d_BSplineCurve)::DownCast(Geometry()))
	{
		if (g->Degree() IS_EQUAL 1)
		{
			return Standard_True;
		}
		else
		{
			return Standard_False;
		}
	}

	if (auto g = Handle(Geom2d_Line)::DownCast(Geometry()))
	{
		return Standard_True;
	}
	else
	{
		return Standard_False;
	}
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
tnbLib::Pln_Curve::BoundingBox(const Standard_Real Tol) const
{
	Debug_Null_Pointer(Geometry());
	Bnd_Box2d BndBox;
	BndLib_Add2dCurve::Add(Geometry(), FirstParameter(), LastParameter(), 0, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax;
	BndBox.Get(Xmin, Ymin, Xmax, Ymax);

	Entity2d_Box box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
	if (Tol > 0)
	{
		box.Expand(Tol);
	}
	return std::move(box);
}

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::Pln_Curve::operator()
(
	const Handle(Geom2d_Curve)& theCurve
	) const
{
	auto curve = std::make_shared<Pln_Curve>(theCurve);
	return std::move(curve);
}

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::Pln_Curve::operator()
(
	Handle(Geom2d_Curve) && theCurve
	) const
{
	auto curve = std::make_shared<Pln_Curve>(std::move(theCurve));
	return std::move(curve);
}

//Standard_Boolean 
//tnbLib::Pln_Curve::IsOrphan() const
//{
//	return Standard_True;
//}

std::shared_ptr<tnbLib::Pln_Curve>
tnbLib::Pln_Curve::Copy() const
{
	auto c = Handle(Geom2d_Curve)::DownCast(Geometry()->Copy());
	Debug_Null_Pointer(c);

	auto copy = std::make_shared<Pln_Curve>(Index(), Name(), c);
	return std::move(copy);
}

//tnbLib::Pln_EntityType 
//tnbLib::Pln_Curve::Type() const
//{
//	return Pln_EntityType::CURVE;
//}

void tnbLib::Pln_Curve::Transform
(
	const gp_Trsf2d & t
)
{
	Geometry()->Transform(t);
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

std::tuple
<
	std::shared_ptr<tnbLib::Pln_Curve>,
	std::shared_ptr<tnbLib::Pln_Curve>
>
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

std::tuple
<
	std::shared_ptr<tnbLib::Pln_Curve>,
	std::shared_ptr<tnbLib::Pln_Curve>,
	std::shared_ptr<tnbLib::Pln_Curve>
>
tnbLib::Pln_Curve::Split
(
	const Cad2d_IntsctEntity_TangSegment & x
) const
{
	const auto x0 = x.Parameter0();
	const auto x1 = x.Parameter1();

	std::shared_ptr<Pln_Curve> c0, c1;
	
	if (std::abs(x0 - FirstParameter()) <= gp::Resolution())
	{
		c0 = nullptr;
		c1 = std::dynamic_pointer_cast<Pln_Curve>(This());
	}
	else
	{
		auto[c0x, c1x] = this->Split(x0);

		c0 = std::move(c0x);
		c1 = std::move(c1x);
	}

	std::shared_ptr<Pln_Curve> c2, c3;
	if (std::abs(x1 - LastParameter()) <= gp::Resolution())
	{
		c3 = nullptr;
		c2 = std::dynamic_pointer_cast<Pln_Curve>(This());
	}
	else
	{
		auto[c2x, c3x] = c1->Split(x1);

		c2 = std::move(c2x);
		c3 = std::move(c3x);
	}

	auto c2t = std::make_shared<Pln_TangCurve<Pln_Curve>>(c2->Geometry());

	auto c = std::make_tuple(c0, c2t, c3);
	return std::move(c);
}

//#include <Cad2d_GeoSketch_Circle.hxx>
//#include <Cad2d_GeoSketch_Ellipse.hxx>
//#include <Cad2d_GeoSketch_LineSegment.hxx>
//
//std::shared_ptr<tnbLib::Pln_Curve> 
//tnbLib::Pln_Curve::MakeLineSegment
//(
//	const Pnt2d & theP0, 
//	const Pnt2d & theP1
//)
//{
//	auto sketch = 
//		std::make_shared<Cad2d_GeoSketch_LineSegment>(theP0, theP1);
//	Debug_Null_Pointer(sketch);
//
//	auto curve = std::make_shared<Pln_Curve>(sketch->Geometry());
//	return std::move(curve);
//}

#include <NumAlg_AdaptiveInteg_Info.hxx>

Standard_Boolean
tnbLib::Pln_Curve::IsValid
(
	const std::shared_ptr<Pln_Curve>& theCurve,
	const Standard_Real theTol
)
{
	auto info = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	Debug_Null_Pointer(info);

	info->SetTolerance(1.0E-6);
	info->SetNbInitIterations(4);

	Debug_Null_Pointer(theCurve->Geometry());
	const auto l = Pln_Tools::Length(*theCurve->Geometry(), info);

	if (l <= theTol)
	{
		return Standard_False;
	}
	return Standard_True;
}

Standard_Boolean 
tnbLib::Pln_Curve::IsDegenerate
(
	const std::shared_ptr<Pln_Curve>& theCurve, 
	const Standard_Real theTol
)
{
	return std::abs(theCurve->FirstParameter() - theCurve->LastParameter()) <= theTol;
}

std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::Pln_Curve::Discretize
(
	const Pln_Curve & theCurve,
	const Standard_Integer theNbSegments
)
{
	auto nbSegments = std::max(1, theNbSegments);

	auto poly = std::make_shared<Entity2d_Polygon>();
	Debug_Null_Pointer(poly);

	auto& points = poly->Points();
	points.reserve(theNbSegments + 1);

	const auto u0 = theCurve.FirstParameter();
	const auto u1 = theCurve.LastParameter();
	const auto du = (theCurve.LastParameter() - u0)/(Standard_Real)nbSegments;

	for (size_t i = 0; i <= nbSegments; i++)
	{
		auto u = u0 + i * du;
		if (u > u1) u = u1;
		auto pt = theCurve.Value(u);
		points.push_back(std::move(pt));
	}
	return std::move(poly);
}