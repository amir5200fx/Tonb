#pragma once
#ifndef _Geo_ApprxCurve_Header
#define _Geo_ApprxCurve_Header

#include <Geo_Traits.hxx>
#include <Global_Done.hxx>
#include <Entity_Polygon.hxx>
#include <Geo_ApprxCurve_Info.hxx>

#include <memory>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	template<class CurveType, bool RandSamples>
	class Geo_ApprxCurve
		: public Global_Done
	{

	public:

		typedef typename remove_pointer<CurveType>::type CurveTypeR;
		//typedef typename down_cast_point<typename CurveTypeR::ptType>::type Point;
		typedef typename cascadeLib::pt_type_from_curve<CurveTypeR>::ptType Point;

		typedef Entity_Polygon<Point> chain;
		typedef std::shared_ptr<chain> chain_ptr;

		typedef Geo_ApprxCurve_Info info;

	private:

		/*Private Data*/

		CurveType theCurve_;

		Standard_Real theFirst_;
		Standard_Real theLast_;

		std::shared_ptr<info> theInfo_;

		chain_ptr theChain_;

	public:

		Geo_ApprxCurve()
		{}

		Geo_ApprxCurve
		(
			const CurveType& theCurve,
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const std::shared_ptr<info>& theInfo
		)
			: theCurve_(theCurve)
			, theFirst_(theFirst)
			, theLast_(theLast)
			, theInfo_(theInfo)
		{}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		const CurveType& Curve() const
		{
			return theCurve_;
		}

		auto FirstParameter() const
		{
			return theFirst_;
		}

		auto LastParameter() const
		{
			return theLast_;
		}

		auto IsLoaded() const
		{
			return (Standard_Boolean)theCurve_;
		}

		const chain_ptr& Chain() const
		{
			return theChain_;
		}

		void LoadCurve
		(
			const CurveType& theCurve,
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const std::shared_ptr<info>& theInfo
		)
		{
			theCurve_ = theCurve;

			theFirst_ = theFirst;
			theLast_ = theLast;

			theInfo_ = theInfo;

			Change_IsDone() = Standard_False;
		}

		void Perform();

		void Reset();
	};
}

#include <Geo_ApprxCurveI.hxx>

#endif // !_Geo_ApprxCurve_Header
