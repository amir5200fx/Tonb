#pragma once
#ifndef _Mesh_CurveOptmPoint_BisectCorrection_Initial_Header
#define _Mesh_CurveOptmPoint_BisectCorrection_Initial_Header

#include <Geo_Module.hxx>
#include <Mesh_CurveEntity.hxx>
#include <Global_Done.hxx>

namespace tnbLib
{

	class Mesh_CurveOptmPoint_BisectCorrection_InitialBase
	{

	protected:

		Mesh_CurveOptmPoint_BisectCorrection_InitialBase()
		{}

	public:

		static TnbGeo_EXPORT const Standard_Integer DEFAULT_MAX_LEVEL;
	};

	template<class gCurveType, class MetricPrcsrType = void>
	class Mesh_CurveOptmPoint_BisectCorrection_Initial
		: public Global_Done
		, public Mesh_CurveOptmPoint_BisectCorrection_InitialBase
	{

		typedef Mesh_CurveEntity<gCurveType, MetricPrcsrType> entity;

		/*Private Data*/

		Standard_Real theU0_;
		Standard_Real theGuess_;
		Standard_Real theLen_;

		const entity& theCurve_;

		Standard_Integer theMaxLevel_;

		// results [6/8/2022 Amir]

		std::pair<Standard_Real, Standard_Real> theBound_;
		Standard_Boolean IsConverged_;


		auto& BoundRef()
		{
			return theBound_;
		}

	public:

		

		// default constructor [6/8/2022 Amir]


		// constructors [6/8/2022 Amir]

		Mesh_CurveOptmPoint_BisectCorrection_Initial
		(
			const Standard_Real theU0,
			const Standard_Real theGuess,
			const entity& theCurve
		)
			: theU0_(theU0)
			, theGuess_(theGuess)
			, theCurve_(theCurve)
			, theLen_(1.0)
			, theMaxLevel_(DEFAULT_MAX_LEVEL)
			, IsConverged_(Standard_False)
		{}


		// public functions and operators [6/8/2022 Amir]

		auto U0() const
		{
			return theU0_;
		}

		auto Guess() const
		{
			return theGuess_;
		}

		auto Len() const
		{
			return theLen_;
		}

		auto MaxLevel() const
		{
			return theMaxLevel_;
		}

		const auto& Entity() const
		{
			return theCurve_;
		}

		const auto& Bound() const
		{
			return theBound_;
		}

		auto IsConverged() const
		{
			return IsConverged_;
		}

		void Perform();

		void SetLen(const Standard_Real x)
		{
			theLen_ = x;
		}

		void SetMaxLevel(const Standard_Integer n)
		{
			theMaxLevel_ = n;
		}
	};
}

#include <Mesh_CurveOptmPoint_BisectCorrection_InitialI.hxx>

#endif // !_Mesh_CurveOptmPoint_BisectCorrection_Initial_Header
