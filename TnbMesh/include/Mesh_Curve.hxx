#pragma once
#ifndef _Mesh_Curve_Header
#define _Mesh_Curve_Header

#include <Mesh_Curve_Info.hxx>
#include <Mesh_CurveEntity.hxx>
#include <Mesh_Module.hxx>
#include <Mesh_CurveTraits.hxx>
#include <Global_Done.hxx>
#include <Global_Handle.hxx>
#include <Entity_Polygon.hxx>
#include <Geo_Traits.hxx>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;

	class Mesh_Curve_Base
	{
	public:
		typedef Mesh_Curve_Info info;
	private:
		/*Private Data*/

		Standard_Real theFirstParameter_;
		Standard_Real theLastParameter_;

		std::shared_ptr<info> theInfo_;


	protected:

		TnbMesh_EXPORT Mesh_Curve_Base();

		TnbMesh_EXPORT Mesh_Curve_Base
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const std::shared_ptr<info>& theInfo
		);

		auto& ChangeFirstParameter()
		{
			return theFirstParameter_;
		}

		auto& ChangeLastParameter()
		{
			return theLastParameter_;
		}

	public:

		static TnbMesh_EXPORT Standard_Integer nbLevels_CheckingLength;

		auto FirstParameter() const
		{
			return theFirstParameter_;
		}

		auto LastParameter() const
		{
			return theLastParameter_;
		}

		const auto& Info() const
		{
			return theInfo_;
		}

		void LoadInfo(const std::shared_ptr<info>& theInfo)
		{
			theInfo_ = theInfo;
		}

	};


	template<class gCurveType, class MetricPrcsrType, bool SavePars = false>
	class Mesh_Curve
		: public Global_Done
		, public Mesh_Curve_Base
	{
	public:
		typedef typename meshCurveTraits::point_type<gCurveType, SavePars>::Point Point;
		//typedef typename cascadeLib::pt_type_from_curve<gCurveType>::ptType Point;

		typedef Mesh_Curve_Info info;
		typedef NumAlg_AdaptiveInteg_Info intgInfo;
		typedef Entity_Polygon<Point> chain;
		typedef Mesh_CurveEntity<gCurveType, MetricPrcsrType> entity;

	private:
		/*Private Data*/

		Handle(gCurveType) theCurve_;

		std::shared_ptr<MetricPrcsrType> theMetricMap_;

		std::shared_ptr<chain> theChain_;
		std::vector<Standard_Real> theParameters_;


		//- private functions and operators

		void MakeChain(const std::vector<Standard_Real>& theParameters);
		void Discretize(const Standard_Real theLength);

		Standard_Real CalcNextParameter(const Standard_Real theLength, const Standard_Real U0) const;

		static Standard_Real
			CalcNextParameter
			(
				const Standard_Real theU0,
				const Standard_Real theGuess,
				const Standard_Real theStep,
				const Standard_Real theUmax,
				const Standard_Integer theLevel,
				const Standard_Integer theMaxLevel,
				const entity& theCurve,
				const info& theInfo
			);

		static Standard_Real
			CalcNextParameter
			(
				const Standard_Real theU0,
				const Standard_Real theGuess,
				const Standard_Real theStep,
				const Standard_Real theUmax,
				const entity& theCurve,
				const info& theInfo
			);


	public:


		// default constructor [7/14/2021 Amir]

		Mesh_Curve()
		{}


		// constructors [7/14/2021 Amir]

		Mesh_Curve
		(
			const Handle(gCurveType)& theCurve,
			const Standard_Real theU0,
			const Standard_Real theU1,
			const std::shared_ptr<MetricPrcsrType>& theMetricMap,
			const std::shared_ptr<info>& theInfo
		);


		// public functions and operators [7/14/2021 Amir]

		const Handle(gCurveType)& Geometry() const
		{
			return theCurve_;
		}

		const auto& MetricMap() const
		{
			return theMetricMap_;
		}

		const auto& Mesh() const
		{
			return theChain_;
		}

		const auto& Parameters() const { return theParameters_; }

		void LoadCurve
		(
			const Handle(gCurveType)& theCurve,
			const Standard_Real theU0,
			const Standard_Real theU1
		);

		void LoadMap
		(
			const std::shared_ptr<MetricPrcsrType>& theSizeMap
		);

		// return the curve length [7/14/2021 Amir]
		Standard_Real Perform();
		Standard_Real NextParameter(const Standard_Real u0);


		Standard_Real 
			CalcLengthWithChecking
			(
				const Standard_Integer theLev, 
				const Standard_Integer theMaxLev, 
				const Standard_Real theFirst,
				const Standard_Real theLast
			) const;

		Standard_Real 
			CalcLengthWithChecking(const Standard_Integer theMaxLev) const;

		Standard_Real 
			CalcCurveLength
			(
				const Standard_Real theU0, 
				const Standard_Real theU1
			) const;

		//- static functions and operators

		static Standard_Real
			CalcLength
			(
				const entity& theEntity,
				const Standard_Integer theMaxLevel,
				intgInfo& theInfo
			);

		static Standard_Real
			CalcLength
			(
				const entity& theEntity,
				const Standard_Integer theLevel,
				const Standard_Integer theMaxLevel,
				intgInfo& theInfo
			);

		
	};
}

#include <Mesh_CurveI.hxx>

#endif // !_Mesh_Curve_Header