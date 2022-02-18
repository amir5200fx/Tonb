#include <Cad2d_CurveLength_UniDiscret.hxx>

#include <Pln_Curve.hxx>
#include <Pln_CurveTools.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::cad2dLib::CurveLength_UniDiscret::DEFAULT_NB_SEGMENTS(20);

Standard_Real 
tnbLib::cad2dLib::CurveLength_UniDiscret::CalcLength
(
	const std::shared_ptr<Pln_Curve>& theCurve
) const
{
	if (NOT theCurve)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is a null pointer." << endl
			<< abort(FatalError);
	}

	if (NbSegments() < 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "An invalid number of segments has been set." << endl
			<< "The minimum number of segments is 1." << endl
			<< " - nb. of segments: " << theNbSegments_ << endl
			<< abort(FatalError);
	}

	auto poly = Pln_Curve::Discretize(*theCurve, NbSegments());
	Debug_Null_Pointer(poly);

	return Geo_Tools::CalcLength(*poly);
}

Standard_Real 
tnbLib::cad2dLib::CurveLength_UniDiscret::CalcLength
(
	const std::shared_ptr<Pln_Curve>& theCurve,
	const Standard_Real theLower,
	const Standard_Real theUpper
) const
{
	if (NOT theCurve)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is a null pointer." << endl
			<< abort(FatalError);
	}

	auto curve = 
		std::make_shared<Pln_Curve>
		(
			Pln_CurveTools::Trim(theCurve->Geometry(), theLower, theUpper)
			);
	Debug_Null_Pointer(curve);

	if (NbSegments() < 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "An invalid number of segments has been set." << endl
			<< "The minimum number of segments is 1." << endl
			<< " - nb. of segments: " << theNbSegments_ << endl
			<< abort(FatalError);
	}

	auto poly = Pln_Curve::Discretize(*curve, NbSegments());
	Debug_Null_Pointer(poly);

	return Geo_Tools::CalcLength(*poly);
}