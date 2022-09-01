#include <Cad_CurveSplitter.hxx>

#include <Mesh_CurveEntity.hxx>
#include <Mesh_CurveOptmPoint_Correction.hxx>
#include <Mesh_CurveOptmPoint_Newton.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <Mesh_CurveOptmPoint_BisectCorrection_Initial.hxx>
#include <Mesh_CurveOptmPoint_BisectCorrection.hxx>
#include <Cad_CurveSplitter_Info.hxx>
#include <Cad_CurveLength.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Curve.hxx>

const Standard_Integer tnbLib::Cad_CurveSplitter::DEFAULT_NB_SEGMENTS(15);
const std::shared_ptr<tnbLib::Cad_CurveSplitter_Info> tnbLib::Cad_CurveSplitter::DEFAULT_INFO =
std::make_shared<tnbLib::Cad_CurveSplitter_Info>();

namespace tnbLib
{

	class CurveSplitterRunTimeInfo
	{

		/*Private Data*/

	public:

		// default constructor [1/20/2022 Amir]

		CurveSplitterRunTimeInfo()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

void tnbLib::CurveSplitterRunTimeInfo::SetInfo()
{
	auto& myInfo = *Cad_CurveSplitter::DEFAULT_INFO;


}

static const tnbLib::CurveSplitterRunTimeInfo myCurveSplitterRunTimeInfoObj;

namespace tnbLib
{

	namespace crvSplitter
	{

		static Standard_Real 
			CalcNextParameter
			(
				const Standard_Real theU0, 
				const Standard_Real theGuess, 
				const Standard_Real theStep, 
				const Standard_Real theUmax, 
				const Standard_Integer theLevel, 
				const Standard_Real theMaxLevel, 
				const Mesh_CurveEntity<Geom_Curve>& theCurve, 
				const Cad_CurveSplitter_Info& theInfo
			)
		{
			if (theGuess <= theU0)
			{
				FatalErrorIn(FunctionSIG)
					<< " invalid initial guess for optimum point has been detected!" << endl
					<< " - u0: " << theU0 << endl
					<< " - guess: " << theGuess << endl
					<< " - step: " << theStep << endl
					<< " - uMax: " << theUmax << endl
					<< abort(FatalError);
			}
			Debug_Null_Pointer(theInfo.CorrInfo());

			Standard_Real corrected = theGuess;
			try
			{
				Mesh_CurveOptmPoint_Correction<Geom_Curve>
					correction(theU0, theGuess, theCurve, *theInfo.CorrInfo(), theInfo.IterIntgInfo());

				correction.SetLen(theStep);
				correction.Perform();

				Debug_If_Condition_Message(NOT correction.IsDone(),
					"mesh_curveoptpoint_correction algorithm has not been performed!");
				corrected = correction.Corrected();
			}
			catch (const ConvError&)
			{
				Mesh_CurveOptmPoint_BisectCorrection_Initial<Geom_Curve>
					initial(theU0, theGuess, theCurve, theInfo.OverallLengthIntgInfo());

				//initial.SetMaxLevel(25);
				initial.SetLen(theStep);
				initial.Perform();

				Debug_If_Condition_Message(NOT initial.IsDone(),
					"the application algorithm has not been performed!");

				const auto[x0, x1] = initial.Bound();
				if (x0 IS_EQUAL x1 AND initial.IsConverged())
				{
					corrected = x0;
					goto iterationAlg;
				}

				if (NOT initial.IsConverged())
				{
					FatalErrorIn(FunctionSIG)
						<< "Can not Calculate parameter of the curve" << endl
						<< " - U0: " << theU0 << endl
						<< " - Guess: " << theGuess << endl
						<< " - Corrected: " << corrected << endl
						<< abort(FatalError);
				}
				Mesh_CurveOptmPoint_BisectCorrection<Geom_Curve>
					correction(theU0, x0, x1, theCurve, theInfo.BisectInfo(), theInfo.OverallLengthIntgInfo());
				correction.SetLen(theStep);
				correction.Perform();

				Debug_If_Condition_Message(NOT correction.IsDone(),
					"mesh_curveoptpoint_correction algorithm has not been performed!");

				corrected = correction.Corrected();
				goto iterationAlg;
			}
			
		iterationAlg:

			/*Mesh_CurveOptmPoint_Correction<Geom_Curve> 
				correction(theU0, theGuess, theCurve, *theInfo.CorrInfo(), theInfo.IterIntgInfo());
			correction.Perform();

			Debug_If_Condition_Message(NOT correction.IsDone(),
				"mesh_curveoptpoint_correction algorithm has not been performed!");
			auto corrected = correction.Corrected();*/

			Mesh_CurveOptmPoint_Newton<Geom_Curve>
				Iteration(theU0, theStep, theCurve);

			try
			{
				Iteration.Perform(corrected, theInfo.NewtonIterInfo(),
					theInfo.IterIntgInfo());
				Debug_If_Condition_Message(NOT Iteration.IsDone(),
					"mesh_curveoptpoint_newton algorithm has not been performed!");

				return Iteration.Corrected();
			}
			catch (const ConvError&)
			{
				if (theLevel > theMaxLevel)
				{
					if (theInfo.IgnoreNonConvergency())
					{
						return Iteration.Corrected();
					}

					FatalErrorIn(FunctionSIG)
						<< "Can not Calculate parameter of the curve" << endl
						<< abort(FatalError);
				}

				const auto ds2 = theStep / 2;
				const auto du = theU0 + (corrected - theU0) / 2;

				auto um =
					CalcNextParameter
					(
						theU0,
						du, ds2, theUmax,
						theLevel + 1, theMaxLevel,
						theCurve, theInfo);
				return
					CalcNextParameter
					(
						um, 2.0*um - theU0, ds2,
						theUmax, theLevel,
						theMaxLevel, theCurve, theInfo
					);
			}
		}

		static Standard_Real
			CalcNextParameter
			(
				const Standard_Real theU0,
				const Standard_Real theGuess,
				const Standard_Real theStep,
				const Standard_Real theUmax,
				const Mesh_CurveEntity<Geom_Curve>& theCurve,
				const Cad_CurveSplitter_Info& theInfo
			)
		{
			return
				CalcNextParameter
				(
					theU0, theGuess, theStep,
					theUmax, 0, theInfo.MaxLevel(),
					theCurve, theInfo);
		}
	}
}

void tnbLib::Cad_CurveSplitter::Perform
(
	const Standard_Real theU0, 
	const Standard_Real theU1
)
{
	if (NOT Curve())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve is loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT GetInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found!" << endl
			<< abort(FatalError);
	}

	if (NbSegments() <= 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid nb. of segments has been detected!" << endl
			<< " - nb. of segments: " << NbSegments() << endl
			<< abort(FatalError);
	}

	if (NbSegments() IS_EQUAL 1)
	{
		auto& params = theParameters_;
		params.reserve(2);

		params.push_back(theU0);
		params.push_back(theU1);

		Change_IsDone() = Standard_True;
		return;
	}
	Debug_Null_Pointer(Curve());
	Debug_Null_Pointer(GetInfo());
	Debug_Null_Pointer(GetInfo()->IterIntgInfo());
	Mesh_CurveEntity<Geom_Curve> 
		Integrand(*Curve(), GetInfo()->IterIntgInfo(), 1.0, theU0, theU1);

	auto curveLengthInfo = 
		std::make_shared<Cad_CurveLength_Info>(GetInfo()->OverallLengthIntgInfo(), GetInfo()->MaxLevel());
	Debug_Null_Pointer(curveLengthInfo);

	auto curveLengthAlg = std::make_shared<Cad_CurveLength>(Curve(), curveLengthInfo);
	Debug_Null_Pointer(curveLengthAlg);

	curveLengthAlg->Perform(theU0, theU1);
	Debug_If_Condition_Message(NOT curveLengthAlg->IsDone(), "the application is not performed!");

	// calculate the length of the curve [1/20/2022 Amir]
	const auto curveLength = curveLengthAlg->Result();

	Debug_If_Condition(NbSegments() <= 1);
	const auto Ds = curveLength / (Standard_Real)NbSegments();
	const auto dt = Ds / curveLength;

	Standard_Real U0, U1, Guess;

	std::vector<Standard_Real> Parameters(NbSegments() + 1);
	Parameters[0] = theU0;
	Parameters[Parameters.size() - 1] = theU1;

	U0 = Parameters[0];
	Guess = U0 + dt;

	if (Guess < theU0) Guess = theU0;
	if (Guess > theU1) Guess = theU1;

	forThose(Index, 1, NbSegments() - 1)
	{
		U1 = crvSplitter::CalcNextParameter
		(
			U0, Guess, Ds,
			theU1, Integrand, *GetInfo());

		if (NOT INSIDE(U1, U0, theU1))
		{
			FatalErrorIn("void Mesh_Curve<gCurveType, MetricPrcsrType>::Perform()")
				<< "Invalid Parameter: " << U1 << endl
				<< " - First parameter: " << theU0 << endl
				<< " - Last parameter: " << theU1 << endl
				<< abort(FatalError);
		}

		Parameters[Index] = U1;

		Guess = U1 + MIN(dt, GetInfo()->UnderRelaxation()*(Parameters[Index] - Parameters[Index - 1]));

		Debug_If_Condition(Guess <= U1);

		U0 = U1;
	}

	theParameters_ = std::move(Parameters);
	Change_IsDone() = Standard_True;
}

void tnbLib::Cad_CurveSplitter::Perform()
{
	if (NOT Curve())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve is loaded!" << endl
			<< abort(FatalError);
	}

	Perform(Curve()->FirstParameter(), Curve()->LastParameter());
}