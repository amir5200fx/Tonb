#include <Cad2d_CurveLength_Adaptive.hxx>

#include <Cad2d_CurveLength_Adaptive_Info.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <Geo_CurveLength.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>

#include <Mesh_CurveEntity.hxx>
#include <Mesh_CurveLength.hxx>

namespace tnbLib
{

	namespace crvLen
	{

		static Standard_Real
			CalcLength
			(
				const Mesh_CurveEntity<Geom2d_Curve>& theCurve,
				const Standard_Integer theLevel,
				const Standard_Integer theMaxLevel
			)
		{
			try
			{
				return Mesh_CurveLength::Length(theCurve, *theCurve.IntegInfo());
			}
			catch (const ConvError&)
			{
				if (theLevel > theMaxLevel)
				{
					FatalErrorIn(FunctionSIG)
						<< "Can not Calculate length of the curve" << endl
						<< " - Level of the calculation: " << theLevel << endl
						<< " - Max. nb of the levels: " << theMaxLevel << endl
						<< abort(FatalError);
				}

				return
					CalcLength
					(
						Mesh_CurveEntity<Geom2d_Curve>
						(
							theCurve.Curve(),
							theCurve.IntegInfo(),
							theCurve.Size(),
							theCurve.FirstParameter(),
							MEAN(theCurve.FirstParameter(), theCurve.LastParameter())),
						theLevel + 1, theMaxLevel)
					+ CalcLength
					(
						Mesh_CurveEntity<Geom2d_Curve>
						(
							theCurve.Curve(),
							theCurve.IntegInfo(),
							theCurve.Size(),
							MEAN(theCurve.FirstParameter(), theCurve.LastParameter()),
							theCurve.LastParameter()),
						theLevel + 1, theMaxLevel);
			}
		}

		static Standard_Real
			CalcLength
			(
				const Handle(Geom2d_Curve)& theCurve
				, const Standard_Real theFirst,
				const Standard_Real theLast,
				const Standard_Integer theMaxLevel,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			)
		{
			Mesh_CurveEntity<Geom2d_Curve> ent(*theCurve, theInfo, 1.0, theFirst, theLast);
			return CalcLength(ent, 0, theMaxLevel);
		}
	}
}

Standard_Real 
tnbLib::cad2dLib::CurveLength_Adaptive::CalcLength
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

	return CalcLength(theCurve, theCurve->FirstParameter(), theCurve->LastParameter());
}

Standard_Real 
tnbLib::cad2dLib::CurveLength_Adaptive::CalcLength
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

	const auto& g = theCurve->Geometry();
	if (NOT g)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve has no geometry." << endl
			<< abort(FatalError);
	}

	if (NOT CurveLengthInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no integ info has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT Pln_Tools::IsBounded(g))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}

	const auto lower = g->FirstParameter();
	const auto upper = g->LastParameter();

	if (NOT INSIDE(theLower, lower, upper))
	{
		FatalErrorIn(FunctionSIG)
			<< "the lower parameter exceeds the knot vector." << endl
			<< " - x: " << theLower << endl
			<< " - lower: " << lower << endl
			<< " - upper: " << upper << endl
			<< abort(FatalError);
	}

	if (NOT INSIDE(theUpper, lower, upper))
	{
		FatalErrorIn(FunctionSIG)
			<< "the upper parameter exceeds the knot vector." << endl
			<< " - x: " << theUpper << endl
			<< " - lower: " << lower << endl
			<< " - upper: " << upper << endl
			<< abort(FatalError);
	}

	return
		crvLen::CalcLength
		(
			g,
			lower, upper,
			CurveLengthInfo()->MaxLevel(),
			CurveLengthInfo()->IntegInfo()
		);
}