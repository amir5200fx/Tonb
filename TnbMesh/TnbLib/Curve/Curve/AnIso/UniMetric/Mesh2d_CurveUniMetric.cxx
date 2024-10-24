#ifdef MeshCurveAnIso_Debug
#include <Mesh2d_CurveUniMetric.hxx>

#include <Mesh2d_CurveOptmPointUniMetric_Correction.hxx>
#include <Mesh2d_CurveOptmPointUniMetric_BisectCorrection_Initial.hxx>
#include <Mesh_CurveOptmPoint_BisectCorrection.hxx>
#include <Mesh_CurveOptmPoint_Newton.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
Standard_Real
tnbLib::Mesh2d_CurveUniMetric::CalcNextParameter
(
	const Standard_Real theU0,
	const Standard_Real theGuess,
	const Standard_Real theStep,
	const Standard_Real theUmax,
	const Standard_Integer theLevel,
	const Standard_Integer theMaxLevel,
	const Mesh2d_CurveEntityUniMetric & theCurve,
	const Mesh_Curve_Info & theInfo
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

	Standard_Real corrected = theGuess;
	try
	{
		Mesh2d_CurveOptmPointUniMetric_Correction
			correction(theU0, theGuess, theCurve, *theInfo.CorrAlgInfo(), theInfo.NewtonIntgInfo());

		correction.SetLen(theStep);
		correction.Perform();

		Debug_If_Condition_Message(NOT correction.IsDone(),
			"mesh_curveoptpoint_correction algorithm has not been performed!");
		corrected = correction.Corrected();
	}
	catch (const ConvError&)
	{
		Mesh2d_CurveOptmPointUniMetric_BisectCorrection_Initial
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
		Mesh_CurveOptmPoint_BisectCorrection<Geom2d_Curve, Geo2d_MetricPrcsrUniMetric>
			correction(theU0, x0, x1, theCurve, theInfo.BisectAlgInfo(), theInfo.OverallLengthIntgInfo());
		/*std::cout << "bisection..." << std::endl;
		std::cout << " - U0: " << theU0 << std::endl;
		std::cout << " - guess: " << theGuess << std::endl;
		std::cout << " - x0: " << x0 << std::endl;
		std::cout << " - x1: " << x1 << std::endl;*/
		correction.SetLen(theStep);
		correction.Perform();
		//std::cout << "bisection is performed" << std::endl;
		Debug_If_Condition_Message(NOT correction.IsDone(),
			"mesh_curveoptpoint_correction algorithm has not been performed!");

		correction.SetLen(theStep);
		/*FatalErrorIn(FunctionSIG)
			<< "Can not Calculate parameter of the curve" << endl
			<< " - U0: " << theU0 << endl
			<< " - Guess: " << theGuess << endl
			<< " - Corrected: " << corrected << endl
			<< abort(FatalError);*/
		corrected = correction.Corrected();
		//std::cout << " - corrected: " << corrected << std::endl;
		goto iterationAlg;
	}

iterationAlg:

	Mesh_CurveOptmPoint_Newton<Geom2d_Curve, Geo2d_MetricPrcsrUniMetric>
		Iteration(theU0, theStep, theCurve);
	try
	{
		Iteration.Perform(corrected, theInfo.NewtonIterInfo(),
			theInfo.NewtonIntgInfo());
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
			return Iteration.Corrected();
		}
		const auto ds2 = 0.5*theStep;
		const auto du = theU0 + 0.5*(corrected - theU0);
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

template<>
Standard_Real tnbLib::Mesh2d_CurveUniMetric::Perform()
{
	if (NOT Geometry())
	{
		FatalErrorIn("void Mesh_Curve<CurveType, SizeMap>::Perform()")
			<< "No curve has been loaded" << endl
			<< abort(FatalError);
	}

	if (NOT MetricMap())
	{
		FatalErrorIn("void Mesh_Curve<CurveType, SizeMap>::Perform()")
			<< "No sizeMap has been loaded" << endl
			<< abort(FatalError);
	}

	if (NOT Info())
	{
		FatalErrorIn("void Mesh_Curve<CurveType, SizeMap>::Perform()")
			<< "No sizeMap has been loaded" << endl
			<< abort(FatalError);
	}

	// Determine the Length of the curve under the current space function
	/*auto curveLength =
		CalcLength
		(
			Integrand, Info()->LengthCalcMaxLevel(),
			*Info()->OverallLengthIntgInfo());*/
	auto curveLength = CalcLengthWithChecking(nbLevels_CheckingLength);

	try
	{
		Discretize(curveLength);
	}
	catch (const meshLib::LengthCurveError& x)
	{
		std::cout << "Length = " << curveLength << std::endl;
		try
		{
			std::cout << " recalculation, Length= " << x.length << std::endl;
			Discretize(x.length);
			return x.length;
		}
		catch (const meshLib::LengthCurveError&)
		{
			FatalErrorIn(FunctionSIG)
				<< "Cannot calculate the actual curve length: unexpected results have been came up!" << endl
				<< abort(FatalError);
			return 0.;
		}
	}
	return curveLength;
}
#endif // MeshCurveAnIso_Debug