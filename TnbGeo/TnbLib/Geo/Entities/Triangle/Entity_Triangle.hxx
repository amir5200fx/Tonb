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
		
		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theP0_;
			ar & theP1_;
			ar & theP2_;
		}

	public:

		//- default constructor

		Entity_Triangle()
			: theP0_(Point::null)
			, theP1_(Point::null)
			, theP2_(Point::null)
		{}


		//- constructors

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

		Entity_Triangle
		(
			Point&& theP0,
			Point&& theP1,
			Point&& theP2
		)
			: theP0_(std::move(theP0))
			, theP1_(std::move(theP1))
			, theP2_(std::move(theP2))
		{}


		//- public functions and operators

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

		auto Reverted() const
		{
			auto t = *this;
			t.Revert();
			return std::move(t);
		}

		void Revert()
		{
			std::swap(theP0_, theP1_);
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

		//- default constructor


		//- constructors

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


		//- public functions and operators

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


		//- default constructor


		//- constructors

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


		//- public functions and operators

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
