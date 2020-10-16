#pragma once
#ifndef _Entity_Segment_Header
#define _Entity_Segment_Header

#include <Traits.hxx>

namespace tnbLib
{

	template<class Point>
	class Entity_Segment
	{

		//typedef typename remove_reference<Point>::type Point;

		/*Private Data*/

		Point theP0_;
		Point theP1_;

	public:

		Entity_Segment()
			: theP0_(Point::null)
			, theP1_(Point::null)
		{}

		Entity_Segment
		(
			const Point& theP0,
			const Point& theP1
		)
			: theP0_(theP0)
			, theP1_(theP1)
		{}

		Entity_Segment
		(
			Point&& theP0,
			Point&& theP1
		)
			: theP0_(std::move(theP0))
			, theP1_(std::move(theP1))
		{}

		const auto& P0() const
		{
			return theP0_;
		}

		auto& P0Ref()
		{
			return theP0_;
		}

		const auto& P1() const
		{
			return theP1_;
		}

		auto& P1Ref()
		{
			return theP1_;
		}
	};

	// Forward Declarations
	class Pnt2d;
	class Pnt3d;

	template<>
	class Entity_Segment<const Pnt2d&>
	{

		/*Private Data*/

		const Pnt2d& theP0_;
		const Pnt2d& theP1_;

	public:

		Entity_Segment
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		)
			: theP0_(theP0)
			, theP1_(theP1)
		{}

		const auto& P0() const
		{
			return theP0_;
		}

		const auto& P1() const
		{
			return theP1_;
		}
	};

	template<>
	class Entity_Segment<const Pnt3d&>
	{

		/*Private Data*/

		const Pnt3d& theP0_;
		const Pnt3d& theP1_;

	public:

		Entity_Segment
		(
			const Pnt3d& theP0,
			const Pnt3d& theP1
		)
			: theP0_(theP0)
			, theP1_(theP1)
		{}

		const auto& P0() const
		{
			return theP0_;
		}

		const auto& P1() const
		{
			return theP1_;
		}
	};

	typedef Entity_Segment<Pnt2d> Entity2d_Segment;
	typedef Entity_Segment<Pnt3d> Entity3d_Segment;
}

#endif // !_Entity_Segment_Header
