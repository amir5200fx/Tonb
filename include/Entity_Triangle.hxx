#pragma once
#ifndef _Entity_Triangle_Header
#define _Entity_Triangle_Header

#include <Traits.hxx>
#include <Entity_Segment.hxx>

namespace tnbLib
{

	template<class Point>
	class Entity_Triangle
	{

		//typedef typename remove_reference<PointRef>::type Point;
		typedef Entity_Segment<Point> segment;

		/*Private Data*/

		Point theP0_;
		Point theP1_;
		Point theP2_;


		/*private functions and operators*/

		friend class boost::serialization::access;
		void save(TNB_oARCH_TYPE& ar, const unsigned int version) const;
		void load(TNB_iARCH_TYPE& ar, const unsigned int version);

		void serialize(TNB_oARCH_TYPE& ar, const unsigned int file_version)
		{
			boost::serialization::split_member(ar, *this, file_version);
		}

		void serialize(TNB_iARCH_TYPE& ar, const unsigned int file_version)
		{
			boost::serialization::split_member(ar, *this, file_version);
		};

	public:

		Entity_Triangle()
			: theP0_(Point::null)
			, theP1_(Point::null)
			, theP2_(Point::null)
		{}

		Entity_Triangle
		(
			const Point& theP0,
			const Point& theP1,
			const Point& theP2
		)
			: theP0_(theP0)
			, theP1_(theP1)
			, theP2_(theP2)
		{}

		const Point& P0() const
		{
			return theP0_;
		}

		Point& P0Ref()
		{
			return theP0_;
		}

		const Point& P1() const
		{
			return theP1_;
		}

		Point& P1Ref()
		{
			return theP1_;
		}

		const Point& P2() const
		{
			return theP2_;
		}

		Point& P2Ref()
		{
			return theP2_;
		}

		const Point& Vertex
		(
			const Standard_Integer theIndex
		) const
		{
			return (&theP0_)[theIndex];
		}

		segment Segment0() const
		{
			segment s(P1(), P2());
			return std::move(s);
		}

		segment Segment1() const
		{
			segment s(P2(), P0());
			return std::move(s);
		}

		segment Segment2() const
		{
			segment s(P0(), P1());
			return std::move(s);
		}

		segment Segment
		(
			const Standard_Integer theIndex
		) const
		{
			if (theIndex == 0)
			{
				segment s(theP1_, theP2_);
				return std::move(s);
			}
			else if (theIndex == 1)
			{
				segment s(theP2_, theP0_);
				return std::move(s);
			}
			else
			{
				segment s(theP0_, theP1_);
				return std::move(s);
			}
			
		}
	};

	template<>
	class Entity_Triangle<const Pnt2d&>
	{

		/*Private Data*/

		const Pnt2d& theP0_;
		const Pnt2d& theP1_;
		const Pnt2d& theP2_;

	public:

		Entity_Triangle
		(
			const Pnt2d& p0, 
			const Pnt2d& p1, 
			const Pnt2d& p2
		)
			: theP0_(p0)
			, theP1_(p1)
			, theP2_(p2)
		{}

		const auto& P0() const
		{
			return theP0_;
		}

		const auto& P1() const
		{
			return theP1_;
		}

		const auto& P2() const
		{
			return theP2_;
		}

		const auto& Vertex(const Standard_Integer theIndex)
		{
			if (theIndex == 0)
			{
				return theP0_;
			}
			else if (theIndex == 1)
			{
				return theP1_;
			}
			else
			{
				return theP2_;
			}
		}

		auto Segment0() const
		{
			Entity2d_SegmentRef s(P1(), P2());
			return std::move(s);
		}

		auto Segment1() const
		{
			Entity2d_SegmentRef s(P2(), P0());
			return std::move(s);
		}

		auto Segment2() const
		{
			Entity2d_SegmentRef s(P0(), P1());
			return std::move(s);
		}

		auto Segment
		(
			const Standard_Integer theIndex
		) const
		{
			if (theIndex == 0)
			{
				Entity2d_SegmentRef s(theP1_, theP2_);
				return std::move(s);
			}
			else if (theIndex == 1)
			{
				Entity2d_SegmentRef s(theP2_, theP0_);
				return std::move(s);
			}
			else
			{
				Entity2d_SegmentRef s(theP0_, theP1_);
				return std::move(s);
			}

		}
	};


	template<>
	class Entity_Triangle<const Pnt3d&>
	{

		/*Private Data*/

		const Pnt3d& theP0_;
		const Pnt3d& theP1_;
		const Pnt3d& theP2_;

	public:

		Entity_Triangle
		(
			const Pnt3d& p0,
			const Pnt3d& p1,
			const Pnt3d& p2
		)
			: theP0_(p0)
			, theP1_(p1)
			, theP2_(p2)
		{}

		const auto& P0() const
		{
			return theP0_;
		}

		const auto& P1() const
		{
			return theP1_;
		}

		const auto& P2() const
		{
			return theP2_;
		}

		const auto& Vertex(const Standard_Integer theIndex)
		{
			if (theIndex == 0)
			{
				return theP0_;
			}
			else if (theIndex == 1)
			{
				return theP1_;
			}
			else
			{
				return theP2_;
			}
		}

		auto Segment0() const
		{
			Entity3d_SegmentRef s(P1(), P2());
			return std::move(s);
		}

		auto Segment1() const
		{
			Entity3d_SegmentRef s(P2(), P0());
			return std::move(s);
		}

		auto Segment2() const
		{
			Entity3d_SegmentRef s(P0(), P1());
			return std::move(s);
		}

		auto Segment
		(
			const Standard_Integer theIndex
		) const
		{
			if (theIndex == 0)
			{
				Entity3d_SegmentRef s(theP1_, theP2_);
				return std::move(s);
			}
			else if (theIndex == 1)
			{
				Entity3d_SegmentRef s(theP2_, theP0_);
				return std::move(s);
			}
			else
			{
				Entity3d_SegmentRef s(theP0_, theP1_);
				return std::move(s);
			}

		}
	};
}

#include <Entity_TriangleI.hxx>

#endif // !_Entity_Triangle_Header
