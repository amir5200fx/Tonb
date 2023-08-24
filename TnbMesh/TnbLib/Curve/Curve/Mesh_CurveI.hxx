#pragma once
#include <Geo_Tools.hxx>
#include <Mesh_CurveLength.hxx>
#include <Mesh_CurveOptmPoint_Correction.hxx>
#include <Mesh_CurveOptmPoint_BisectCorrection.hxx>
#include <Mesh_CurveOptmPoint_BisectCorrection_Initial.hxx>
#include <Mesh_CurveOptmPoint_Newton.hxx>
namespace tnbLib
{

	namespace meshLib
	{
		class LengthCurveError
		{
		public:
			Standard_Real length;

			LengthCurveError(const Standard_Real x)
				: length(x)
			{}
		};
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	void Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::MakeChain
	(
		const std::vector<Standard_Real>& theParameters
	)
	{
		theChain_ = std::make_shared<chain>();

		auto& Points = theChain_->Points();
		Points.reserve(theParameters.size());

		const auto& curve = *theCurve_;
		for (const auto x : theParameters)
		{
			Points.push_back(curve.Value(x));
		}
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	Standard_Real Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::CalcNextParameter
	(
		const Standard_Real theU0,
		const Standard_Real theGuess,
		const Standard_Real theStep,
		const Standard_Real theUmax,
		const Standard_Integer theLevel,
		const Standard_Integer theMaxLevel,
		const entity & theCurve,
		const info & theInfo
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
			//std::cout << "correction..." << std::endl;
			Mesh_CurveOptmPoint_Correction<gCurveType, MetricPrcsrType>
				correction(theU0, theGuess, theCurve, *theInfo.CorrAlgInfo(), theInfo.NewtonIntgInfo());

			correction.SetLen(theStep);
			correction.Perform();

			Debug_If_Condition_Message(NOT correction.IsDone(),
				"mesh_curveoptpoint_correction algorithm has not been performed!");
			corrected = correction.Corrected();
			//std::cout << "correction is finished." << std::endl;
		}
		catch (const ConvError&)
		{
			//std::cout << "initial..." << std::endl;
			Mesh_CurveOptmPoint_BisectCorrection_Initial<gCurveType, MetricPrcsrType>
				initial(theU0, theGuess, theCurve, theInfo.OverallLengthIntgInfo());

			//initial.SetMaxLevel(25);
			initial.SetLen(theStep);
			initial.Perform();

			Debug_If_Condition_Message(NOT initial.IsDone(),
				"the application algorithm has not been performed!");
			//std::cout << "initial is finished." << std::endl;
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
			//std::cout << "bisect..." << std::endl;
			Mesh_CurveOptmPoint_BisectCorrection<gCurveType, MetricPrcsrType>
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

			//correction.SetLen(theStep);
			/*FatalErrorIn(FunctionSIG)
				<< "Can not Calculate parameter of the curve" << endl
				<< " - U0: " << theU0 << endl
				<< " - Guess: " << theGuess << endl
				<< " - Corrected: " << corrected << endl
				<< abort(FatalError);*/
			corrected = correction.Corrected();
			//std::cout << "bisect is finished..." << std::endl;
			//std::cout << " - corrected: " << corrected << std::endl;
			goto iterationAlg;

			/*if (theLevel > theMaxLevel)
			{
				Mesh_CurveOptmPoint_BisectCorrection_Initial<gCurveType, MetricPrcsrType>
					initial(theU0, theGuess, theCurve);

				initial.SetLen(theStep);
				initial.Perform();

				Debug_If_Condition_Message(NOT initial.IsDone(),
					"the application algorithm has not been performed!");

				const auto[x0, x1] = initial.Bound();
				std::cout << "x0: " << x0 << ", x1: " << x1 << std::endl;
				if (x0 IS_EQUAL x1)
				{
					FatalErrorIn(FunctionSIG)
						<< "Can not Calculate parameter of the curve" << endl
						<< " - U0: " << theU0 << endl
						<< " - Guess: " << theGuess << endl
						<< " - Corrected: " << corrected << endl
						<< abort(FatalError);
				}

				Mesh_CurveOptmPoint_BisectCorrection<gCurveType, MetricPrcsrType>
					correction(theU0, x0, x1, theCurve, theInfo.BisectAlgInfo());

				correction.SetLen(theStep);
				correction.Perform();

				Debug_If_Condition_Message(NOT correction.IsDone(),
					"mesh_curveoptpoint_correction algorithm has not been performed!");

				correction.SetLen(theStep);
				corrected = correction.Corrected();

				goto iterationAlg;
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
				);*/
		}

	iterationAlg:
		//std::cout << "optimum..." << std::endl;
		Mesh_CurveOptmPoint_Newton<gCurveType, MetricPrcsrType>
			Iteration(theU0, theStep, theCurve);	
		try
		{
			Iteration.Perform(corrected, theInfo.NewtonIterInfo(),
				theInfo.NewtonIntgInfo());
			Debug_If_Condition_Message(NOT Iteration.IsDone(),
				"mesh_curveoptpoint_newton algorithm has not been performed!");
			//std::cout << "optimum is finished." << std::endl;
			return Iteration.Corrected();
		}
		catch (const ConvError&)
		{
			//std::cout << " subdivide span..." << std::endl;
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
			//std::cout << " calc um..." << std::endl;
			auto um =
				CalcNextParameter
				(
					theU0,
					du, ds2, theUmax,
					theLevel + 1, theMaxLevel,
					theCurve, theInfo);
			//std::cout << " calc um till next..." << std::endl;
			return
				CalcNextParameter
				(
					um, 2.0*um - theU0, ds2,
					theUmax, theLevel + 1,
					theMaxLevel, theCurve, theInfo
				);
		}
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	Standard_Real Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::CalcNextParameter
	(
		const Standard_Real theU0,
		const Standard_Real theGuess,
		const Standard_Real theStep,
		const Standard_Real theUmax,
		const entity & theCurve,
		const info & theInfo
	)
	{
		return
			CalcNextParameter
			(
				theU0, theGuess, theStep,
				theUmax, 0, theInfo.LengthCalcMaxLevel(),
				theCurve, theInfo);
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::Mesh_Curve
	(
		const Handle(gCurveType)& theCurve,
		const Standard_Real theU0,
		const Standard_Real theU1,
		const std::shared_ptr<MetricPrcsrType>& theMetricMap,
		const std::shared_ptr<info>& theInfo
	)
		: Mesh_Curve_Base(theU0, theU1, theInfo)
		, theCurve_(theCurve)
		, theMetricMap_(theMetricMap)
	{
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	void Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::LoadCurve
	(
		const Handle(gCurveType)& theCurve,
		const Standard_Real theU0,
		const Standard_Real theU1
	)
	{
		theCurve_ = theCurve;
		ChangeFirstParameter() = theU0;
		ChangeLastParameter() = theU1;
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	void tnbLib::Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::LoadMap
	(
		const std::shared_ptr<MetricPrcsrType>& theSizeMap
	)
	{
		theMetricMap_ = theSizeMap;
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	inline void tnbLib::Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::Discretize
	(
		const Standard_Real theLength
	)
	{
		Mesh_CurveEntity<gCurveType, MetricPrcsrType>
			Integrand(*Geometry(), *MetricMap(), FirstParameter(), LastParameter());

		// uniform nb. of segment under the current space function
		auto NbSegments =
			MAX
			(
				Geo_Tools::Round(theLength*(1.0 + EPS6)),
				Geo_Tools::Round(theLength*(1.0 - EPS6)));

		// There must be at least one segment
		if (NbSegments < 1) NbSegments = 1;
		Debug_If_Condition(NbSegments < 1);

		const auto Ds = theLength / (Standard_Real)NbSegments;
		const auto dt = 1.0 / theLength;
		Standard_Real U0, U1, Guess;

		std::vector<Standard_Real> Parameters(NbSegments + 1);

		Parameters.at(0) = FirstParameter();
		Parameters.at(Parameters.size() - 1) = LastParameter();

		U0 = Parameters.at(0);
		Guess = U0 + dt;  // Debug: 4/14/2018

		if (Guess < FirstParameter()) Guess = FirstParameter();
		if (Guess > LastParameter()) Guess = LastParameter();
		//std::cout << "Length = " << theLength << std::endl;
		Standard_Real approxLength = 0;
		forThose(Index, 1, NbSegments - 1)
		{
			try
			{
				U1 = CalcNextParameter
				(
					U0, Guess, Ds,
					LastParameter(), Integrand, *Info());
				//std::cout << "- iter: " << U1 << std::endl;
			}
			catch (const error&)
			{
				auto len = this->CalcCurveLength(U0, LastParameter());
				approxLength += len;
				throw meshLib::LengthCurveError(approxLength);
			}

			approxLength += Ds;
			if (NOT INSIDE(U1, U0, LastParameter()))
			{
				FatalErrorIn("void Mesh_Curve<gCurveType, MetricPrcsrType>::Perform()")
					<< "Invalid Parameter: " << U1 << endl
					<< " - First parameter: " << FirstParameter() << endl
					<< " - Last parameter: " << LastParameter() << endl
					<< abort(FatalError);
			}

			Parameters.at(Index) = U1;

			Guess = U1 + MIN(dt, Info()->UnderRelaxation()*(Parameters.at(Index) - Parameters.at(Index - 1)));
			if (Guess < FirstParameter()) Guess = FirstParameter();
			if (Guess > LastParameter()) Guess = LastParameter();
			Debug_If_Condition(Guess <= U1);

			U0 = U1;
		}

		MakeChain(Parameters);
		theParameters_ = std::move(Parameters);
		Change_IsDone() = Standard_True;
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	Standard_Real Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::Perform()
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
			try
			{
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

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	Standard_Real Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::CalcLength
	(
		const entity& theCurve,
		const Standard_Integer theLevel,
		const Standard_Integer theMaxLevel,
		intgInfo& theInfo
	)
	{
		try
		{
			return Mesh_CurveLength::Length(theCurve, theInfo);
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
					entity
					(
						theCurve.Curve(),
						theCurve.SizeMap(),
						theCurve.FirstParameter(),
						MEAN(theCurve.FirstParameter(), theCurve.LastParameter())),
					theLevel + 1, theMaxLevel, theInfo)
				+ CalcLength
				(
					entity
					(
						theCurve.Curve(),
						theCurve.SizeMap(),
						MEAN(theCurve.FirstParameter(), theCurve.LastParameter()),
						theCurve.LastParameter()),
					theLevel + 1, theMaxLevel, theInfo);
		}
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	Standard_Real Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::CalcLength
	(
		const entity& theCurve,
		const Standard_Integer theMaxLevel,
		intgInfo& theInfo
	)
	{
		return CalcLength(theCurve, 0, theMaxLevel, theInfo);
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	inline Standard_Real tnbLib::Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::CalcLengthWithChecking
	(
		const Standard_Integer theLev, 
		const Standard_Integer theMaxLev, 
		const Standard_Real theFirst,
		const Standard_Real theLast
	) const
	{
		if (theLev > theMaxLev)
		{
			return this->CalcCurveLength(theFirst, theLast);
			/*FatalErrorIn(FunctionSIG)
				<< "cannot calculate the curve length." << endl
				<< " - nb. of levels= " << theMaxLev << endl
				<< abort(FatalError);*/
		}
		auto totLength = this->CalcCurveLength(theFirst, theLast);
		auto len0 = this->CalcCurveLength(theFirst, MEAN(theFirst, theLast));
		auto len1 = this->CalcCurveLength(MEAN(theFirst, theLast), theLast);

		if (std::abs(totLength - (len0 + len1)) <= this->Info()->NewtonIntgInfo()->Tolerance()*totLength)
		{
			return totLength;
		}
		else
		{
			//std::cout << "DL = " << std::abs(totLength - (len0 + len1)) << ", tol = " << this->Info()->NewtonIntgInfo()->Tolerance() * totLength << std::endl;
			return CalcLengthWithChecking(theLev + 1, theMaxLev, theFirst, MEAN(theFirst, theLast))
				+ CalcLengthWithChecking(theLev + 1, theMaxLev, MEAN(theFirst, theLast), theLast);
		}
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	inline Standard_Real tnbLib::Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::CalcLengthWithChecking
	(
		const Standard_Integer theMaxLev
	) const
	{
		if (nbLevels_CheckingLength < 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid nb of levels for checking the length of the curve!" << endl
				<< " - nb of levels= " << nbLevels_CheckingLength << endl
				<< abort(FatalError);
		}
		return CalcLengthWithChecking(0, nbLevels_CheckingLength, FirstParameter(), LastParameter());
	}

	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	inline Standard_Real 
		tnbLib::Mesh_Curve<gCurveType, MetricPrcsrType, SavePars>::CalcCurveLength
		(
			const Standard_Real theU0,
			const Standard_Real theU1
		) const
	{
		Mesh_CurveEntity<gCurveType, MetricPrcsrType>
			Integrand(*Geometry(), *MetricMap(), theU0, theU1);
		return CalcLength
		(
			Integrand, Info()->LengthCalcMaxLevel(),
			*Info()->OverallLengthIntgInfo());
	}
}