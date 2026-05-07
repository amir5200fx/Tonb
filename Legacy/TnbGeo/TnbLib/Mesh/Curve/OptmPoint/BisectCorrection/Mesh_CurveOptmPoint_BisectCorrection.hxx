#pragma once
#ifndef _Mesh_CurveOptmPoint_BisectCorrection_Header
#define _Mesh_CurveOptmPoint_BisectCorrection_Header

#include <Mesh_CurveOptmPoint_BisectCorrection_Base.hxx>
#include <NumAlg_BisectionSolver.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [6/19/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	template<class gCurveType, class MetricPrcsrType = void>
	class Mesh_CurveOptmPoint_BisectCorrection
		: public Global_Done
		, public Mesh_CurveOptmPoint_BisectCorrection_Base
	{

	public:

		typedef Mesh_CurveEntity<gCurveType, MetricPrcsrType> entity;
		typedef NumAlg_BisectionSolver_Info info;
		typedef NumAlg_AdaptiveInteg_Info integInfo;
	

	private:

		/*Private Data*/

		const entity& theCurve_;

		struct Mesh_CurveOptmPoint_BisectCorrection_Function
			: public NumAlg_Bisection_Function
		{

			const entity& theCurve_;

			Standard_Real theU0_;
			Standard_Real theLen_;

			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo_;

			Mesh_CurveOptmPoint_BisectCorrection_Function
			(
				const entity& theCurve, 
				const Standard_Real theU0, 
				const Standard_Real theLen,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			)
				: theCurve_(theCurve)
				, theU0_(theU0)
				, theLen_(theLen)
				, theInfo_(theInfo)
			{}

			Standard_Real Value(const Standard_Real x) const override;
		};

	public:

		// default constructor [6/8/2022 Amir]
	

		// constructor [6/8/2022 Amir]

		Mesh_CurveOptmPoint_BisectCorrection
		(
			const Standard_Real theU0,
			const Standard_Real theGuess0,
			const Standard_Real theGuess1,
			const entity& theCurve,
			const std::shared_ptr<info>& theInfo,
			const std::shared_ptr<integInfo>& theIntegInfo
		)
			: Mesh_CurveOptmPoint_BisectCorrection_Base
			(
				theU0, theGuess0, 
				theGuess1,
				theInfo, theIntegInfo
			)
			, theCurve_(theCurve)
		{}


		// public functions and operators [6/8/2022 Amir]

		const auto& Entity() const
		{
			return theCurve_;
		}

		void Perform();
	};
}

#include <Mesh_CurveOptmPoint_BisectCorrectionI.hxx>

#endif // !_Mesh_CurveOptmPoint_BisectCorrection_Header
