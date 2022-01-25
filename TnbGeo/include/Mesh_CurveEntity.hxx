#pragma once
#ifndef _Mesh_CurveEntity_Header
#define _Mesh_CurveEntity_Header

#include <Standard_TypeDef.hxx>
#include <Geo_Traits.hxx>
#include <Global_AccessMethod.hxx>

namespace tnbLib
{

	template<class gCurveType, class MetricPrcsrType = void>
	class Mesh_CurveEntity
	{

		/*Private Data*/

		const gCurveType& theCurve_;

		const MetricPrcsrType& theSizeMap_;

		Standard_Real theFirstParameter_;
		Standard_Real theLastParameter_;

	public:

		typedef typename cascadeLib::pt_type_from_curve<gCurveType>::ptType Point;

		// default constructor [1/16/2022 Amir]


		// constructors [1/16/2022 Amir]

		Mesh_CurveEntity
		(
			const gCurveType& theCurve,
			const MetricPrcsrType& theSizeMap,
			const Standard_Real theFirst,
			const Standard_Real theLast
		);


		// public functions and operators [1/16/2022 Amir]

		Point Value(const Standard_Real x) const;


		//- static members

		static Standard_Real Integrand
		(
			const Standard_Real x,
			const Mesh_CurveEntity& theEntity
		);

		//- Macros

		GLOBAL_ACCESS_ONLY_SINGLE(gCurveType, Curve)
			GLOBAL_ACCESS_ONLY_SINGLE(MetricPrcsrType, SizeMap)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, FirstParameter)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, LastParameter)
	};


	// Forward Declarations [1/16/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	template<class gCurveType>
	class Mesh_CurveEntity<gCurveType, void>
	{

		/*Private Data*/

		const gCurveType& theCurve_;

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theIntegInfo_;

		Standard_Real theSize_;

		Standard_Real theFirstParameter_;
		Standard_Real theLastParameter_;

	public:

		typedef typename cascadeLib::pt_type_from_curve<gCurveType>::ptType Point;

		// default constructor [1/16/2022 Amir]

		// constructors [1/16/2022 Amir]

		Mesh_CurveEntity
		(
			const gCurveType& theCurve, 
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theIntegInfo,
			const Standard_Real theSize,
			const Standard_Real theFirst, 
			const Standard_Real theLast
		)
			: theCurve_(theCurve)
			, theIntegInfo_(theIntegInfo)
			, theSize_(theSize)
			, theFirstParameter_(theFirst)
			, theLastParameter_(theLast)
		{}


		// public functions and operators [1/16/2022 Amir]

		Point Value(const Standard_Real x) const;

		//- static members

		static Standard_Real Integrand
		(
			const Standard_Real x,
			const Mesh_CurveEntity& theEntity
		);

		//- Macros

		GLOBAL_ACCESS_ONLY_SINGLE(gCurveType, Curve)
			GLOBAL_ACCESS_PRIM_SINGLE(std::shared_ptr<NumAlg_AdaptiveInteg_Info>, IntegInfo)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Size)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, FirstParameter)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, LastParameter)
	};
}

#include <Mesh_CurveEntityI.hxx>

#endif // !_Mesh_CurveEntity_Header