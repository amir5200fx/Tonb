#include <Cad_CurveLength.hxx>

#include <Cad_Tools.hxx>
#include <Geo_CurveLength.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Curve.hxx>

#include <Pnt3d.hxx>
#include <Dir3d.hxx>

const std::shared_ptr<tnbLib::Cad_CurveLength_Info> tnbLib::Cad_CurveLength::DEFAULT_INFO =
std::make_shared<tnbLib::Cad_CurveLength_Info>();

Standard_Real tnbLib::Cad_CurveLength::Result() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application has not been performed, yet!" << endl
			<< abort(FatalError);
	}
	return theLength_;
}

#include <Mesh_CurveEntity.hxx>
#include <Mesh_CurveLength.hxx>

namespace tnbLib
{

	namespace crvLen
	{

		static Standard_Real 
			CalcLength
			(
				const Mesh_CurveEntity<Geom_Curve>& theCurve, 
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
						Mesh_CurveEntity<Geom_Curve>
						(
							theCurve.Curve(), 
							theCurve.IntegInfo(), 
							theCurve.Size(), 
							theCurve.FirstParameter(), 
							MEAN(theCurve.FirstParameter(), theCurve.LastParameter())), 
						theLevel + 1, theMaxLevel) 
					+ CalcLength
					(
						Mesh_CurveEntity<Geom_Curve>
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
				const Handle(Geom_Curve)& theCurve
				, const Standard_Real theFirst,
				const Standard_Real theLast,
				const Standard_Integer theMaxLevel,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			)
		{
			Mesh_CurveEntity<Geom_Curve> ent(*theCurve, theInfo, 1.0, theFirst, theLast);
			return CalcLength(ent, 0, theMaxLevel);
		}
	}
}

void tnbLib::Cad_CurveLength::Perform()
{
	if (NOT Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry has been loaded, yet!" << endl
			<< abort(FatalError);
	}

	const auto lower = Geometry()->FirstParameter();
	const auto upper = Geometry()->LastParameter();

	Perform(lower, upper);
}

void tnbLib::Cad_CurveLength::Perform
(
	const Standard_Real theLower, 
	const Standard_Real theUpper
)
{
	if (NOT Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry has been loaded, yet!" << endl
			<< abort(FatalError);
	}

	if (NOT CurveLengthInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no integ info has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT Cad_Tools::IsBounded(Geometry()))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}

	const auto lower = Geometry()->FirstParameter();
	const auto upper = Geometry()->LastParameter();

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

	theLength_ = 
		crvLen::CalcLength
		(
			Geometry(), 
			lower, upper, 
			CurveLengthInfo()->MaxLevel(), 
			CurveLengthInfo()->IntegInfo()
		);

	Change_IsDone() = Standard_True;
}