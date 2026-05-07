#pragma once
#ifndef _Mesh_CurveOptmPoint_Correction_Header
#define _Mesh_CurveOptmPoint_Correction_Header

#include <Mesh_CurveOptmPoint_Correction_Base.hxx>

#include <memory>

namespace tnbLib
{

	template<class gCurveType, class MetricPrcsrType = void>
	class Mesh_CurveOptmPoint_Correction
		: public Global_Done
		, public Mesh_CurveOptmPoint_Correction_Base
	{

		typedef Mesh_CurveEntity<gCurveType, MetricPrcsrType> entity;
		typedef Mesh_CurveOptmPoint_Correction_Info info;

		/*Private Data*/

		const entity& theCurve_;

	public:


		// default constructor [1/16/2022 Amir]


		// constructors [1/16/2022 Amir]

		Mesh_CurveOptmPoint_Correction
		(
			const Standard_Real theU0,
			const Standard_Real theGuess,
			const entity& theCurve,
			const info& theInfo,
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theIntegInfo
		)
			: Mesh_CurveOptmPoint_Correction_Base(theU0, theGuess, theInfo, theIntegInfo)
			, theCurve_(theCurve)
		{}


		// public functions and operators [1/16/2022 Amir]

		const auto& Entity() const
		{
			return theCurve_;
		}

		void Perform();
	};

	//template<class gCurveType>
	//class Mesh_CurveOptmPoint_Correction<gCurveType, void>
	//	: public Global_Done
	//	, public Mesh_CurveOptmPoint_Correction_Base
	//{

	//	typedef Mesh_CurveEntity<gCurveType> entity;
	//	typedef Mesh_CurveOptmPoint_Correction_Info info;

	//	/*Private Data*/

	//	const entity& theCurve_;

	//public:

	//	// default constructor [1/16/2022 Amir]


	//	// constructors [1/16/2022 Amir]

	//	Mesh_CurveOptmPoint_Correction
	//	(
	//		const Standard_Real theU0,
	//		const Standard_Real theGuess,
	//		const entity& theCurve,
	//		const info& theInfo,
	//		const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theIntegInfo
	//	)
	//		: Mesh_CurveOptmPoint_Correction_Base(theU0, theGuess, theInfo, theIntegInfo)
	//		, theCurve_(theCurve)
	//	{}


	//	// public functions and operators [1/16/2022 Amir]

	//	const auto& Entity() const
	//	{
	//		return theCurve_;
	//	}

	//	void Perform();
	//};
}

#include <Mesh_CurveOptmPoint_CorrectionI.hxx>

#endif // !_Mesh_CurveOptmPoint_Correction_Header