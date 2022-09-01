#pragma once
#ifndef _Geo_ApprxCurve_Header
#define _Geo_ApprxCurve_Header

#include <Geo_ApprxCurve_Traits.hxx>
#include <Geo_Traits.hxx>
#include <Global_Done.hxx>
#include <Entity_Polygon.hxx>

#include <memory>

//#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	class Geo_ApprxCurveBase
	{

		/*Private Data*/

	protected:

		// default constructor [8/25/2022 Amir]

		Geo_ApprxCurveBase()
		{}


		// constructors [8/25/2022 Amir]

	public:

		struct Segment
		{
			Standard_Real theX0;
			Standard_Real theX1;

			Segment()
			{}

			Segment(const Standard_Real x0, const Standard_Real x1)
				: theX0(x0)
				, theX1(x1)
			{}

			Segment Left() const
			{
				return Segment(theX0, MEAN(theX0, theX1));
			}

			Segment Right() const
			{
				return Segment(MEAN(theX0, theX1), theX1);
			}

			Standard_Real Mean() const
			{
				return MEAN(theX0, theX1);
			}

			static Standard_Boolean IsLess(const Segment& theS1, const Segment& theS2)
			{
				return theS1.Mean() < theS2.Mean();
			}
		};

		typedef std::vector<Segment> segList;

	};

	template<class CurveType, bool RandSamples>
	class Geo_ApprxCurve
		: public Global_Done
		, public Geo_ApprxCurveBase
	{

	public:

		using Geo_ApprxCurveBase::Segment;
		using Geo_ApprxCurveBase::segList;

		typedef typename remove_pointer<CurveType>::type CurveTypeR;
		//typedef typename down_cast_point<typename CurveTypeR::ptType>::type Point;
		typedef typename cascadeLib::pt_type_from_curve<CurveTypeR>::ptType Point;
		//typedef typename Geo_ApprxCurve_Traits<CurveTypeR>::ptType Point;

		typedef Entity_Polygon<Point> chain;
		typedef std::shared_ptr<chain> chain_ptr;

		typedef typename Geo_ApprxCurveInfo_Traits<CurveTypeR>::infoType info;

	private:

		/*Private Data*/

		CurveType theCurve_;

		Standard_Real theFirst_;
		Standard_Real theLast_;

		std::shared_ptr<info> theInfo_;

		chain_ptr theChain_;


		// Private functions and operators [8/25/2022 Amir]

		void Subdivide(segList& theSegmments) const;

	public:


		// default constructor [8/25/2022 Amir]

		Geo_ApprxCurve()
		{}


		// constructors [8/25/2022 Amir]

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


		// public functions and operators [8/25/2022 Amir]

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
