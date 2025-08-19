#include <ShapePx_ContinProfile_GeneratedCustom.hxx>

#include <Pnt2d.hxx>
#include <SectPx_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>
#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

const Standard_Integer tnbLib::shapePxLib::ContinProfile_GeneratedCustom::DEFAULT_MAX_DEGREE(3);
const Standard_Integer tnbLib::shapePxLib::ContinProfile_GeneratedCustom::DEFAULT_MIN_DEGREE(1);

tnbLib::shapePxLib::ContinProfile_GeneratedCustom::ContinProfile_GeneratedCustom
(
	const Standard_Integer theIndex,
	const word & theName
)
	: ContinProfile_Custom(theIndex, theName)
{
	// empty body
}

tnbLib::shapePxLib::ContinProfile_GeneratedCustom::ContinProfile_GeneratedCustom
(
	const std::shared_ptr<SectPx_CurveQ>& theCurve, 
	const Standard_Integer theDegree
)
	: theCurve_(theCurve)
	, theDegree_(theDegree)
{
	// empty body
}

tnbLib::shapePxLib::ContinProfile_GeneratedCustom::ContinProfile_GeneratedCustom
(
	std::shared_ptr<SectPx_CurveQ>&& theCurve,
	const Standard_Integer theDegree
)
	: theCurve_(std::move(theCurve))
	, theDegree_(theDegree)
{
	// empty body
}

tnbLib::shapePxLib::ContinProfile_GeneratedCustom::ContinProfile_GeneratedCustom
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<SectPx_CurveQ>& theCurve, 
	const Standard_Integer theDegree
)
	: ContinProfile_Custom(theIndex, theName)
	, theCurve_(theCurve)
	, theDegree_(theDegree)
{
	// empty body
}

tnbLib::shapePxLib::ContinProfile_GeneratedCustom::ContinProfile_GeneratedCustom
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<SectPx_CurveQ>&& theCurve, 
	const Standard_Integer theDegree
)
	: ContinProfile_Custom(theIndex, theName)
	, theCurve_(std::move(theCurve))
	, theDegree_(theDegree)
{
	// empty body
}

Standard_Boolean 
tnbLib::shapePxLib::ContinProfile_GeneratedCustom::IsIntersect
(
	const Standard_Real x
) const
{
	return INSIDE(x, Lower(), Upper());
}

void tnbLib::shapePxLib::ContinProfile_GeneratedCustom::Perform()
{
	if (NOT CurveQ())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve for the profile has been detected!" << endl
			<< abort(FatalError);
	}
	const auto polesQ = SectPx_Tools::RetrievePoles(CurveQ());
	const auto segments = SectPx_Tools::RetrieveInnerSegments(polesQ);

	const auto poles = SectPx_Tools::RetrieveControlPoints(segments);

	const auto knotsVect = SectPx_Tools::Knots(segments, std::min(DEFAULT_MAX_DEGREE, std::max(DEFAULT_MIN_DEGREE, Degree())));
	const auto knots = SectPx_Tools::Knots(knotsVect);

	const auto weights = SectPx_Tools::Weights(SectPx_Tools::RetrieveWeights(segments));

	const auto cpts = SectPx_Tools::CPts(poles);

	try
	{
		Handle(Geom2d_Curve) curve =
			new Geom2d_BSplineCurve(cpts, weights, knots.first, knots.second, Degree());

		theProfile_ = std::move(curve);
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}

	Change_IsDone() = Standard_True;
}

Standard_Boolean 
tnbLib::shapePxLib::ContinProfile_GeneratedCustom::IsGenerated() const
{
	return Standard_True;
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_GeneratedCustom::Lower() const
{
	Debug_Null_Pointer(theProfile_);
	auto pt = theProfile_->Value(theProfile_->FirstParameter());
	return pt.X();
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_GeneratedCustom::Upper() const
{
	Debug_Null_Pointer(theProfile_);
	auto pt = theProfile_->Value(theProfile_->LastParameter());
	return pt.X();
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_GeneratedCustom::MinLower() const
{
	return Lower();
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_GeneratedCustom::MaxUpper() const
{
	return Upper();
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_GeneratedCustom::Value
(
	const Standard_Real x
) const
{
	Debug_Null_Pointer(theProfile_);
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< " the algorithm is not performed!" << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Line) l = new Geom2d_Line(gp_Pnt2d(x, 0), gp_Dir2d(0, 1));
	Debug_Null_Pointer(l);

	Geom2dAPI_InterCurveCurve alg(l, Profile());
	if (alg.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid data for the profile has been detected!" << endl
			<< abort(FatalError);
	}
	auto value = alg.Point(1);
	return value.Y();
}

std::vector<tnbLib::ShapePx_Profile::offsetPoint> 
tnbLib::shapePxLib::ContinProfile_GeneratedCustom::RetrieveOffsets() const
{
	FatalErrorIn(FunctionSIG)
		<< "this functions is not supposed to called for this type of profile!" << endl
		<< abort(FatalError);
	return std::vector<offsetPoint>();
}

std::vector<Standard_Real> 
tnbLib::shapePxLib::ContinProfile_GeneratedCustom::X() const
{
	FatalErrorIn(FunctionSIG)
		<< "this functions is not supposed to called for this type of profile!" << endl
		<< abort(FatalError);
	return std::vector<Standard_Real>();
}

void tnbLib::shapePxLib::ContinProfile_GeneratedCustom::Update()
{
	Perform();
}
