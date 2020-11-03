#pragma once
#ifndef _Entity_Line_Header
#define _Entity_Line_Header

#include <Traits.hxx>
#include <Entity2d_LineRef.hxx>
#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	template<class Point, class Direct>
	class Entity_Line
	{

	public:

		//typedef typename remove_reference<PointRef>::type Point;
		//typedef typename remove_reference<DirectRef>::type Direct;

	private:

		/*Private Data*/

		Point theP_;
		Direct theDir_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);
		
	public:

		Entity_Line()
			: theP_(Point::null)
			, theDir_(Direct::null)
		{}

		Entity_Line
		(
			const Point& theP, 
			const Direct& theV
		)
			: theP_(theP)
			, theDir_(theV)
		{}

		Entity_Line
		(
			const Point& theP0,
			const Point& theP1
		)
			: theP_(theP0)
			, theDir_(theP0, theP1)
		{}

		Entity_Line
		(
			Point&& theP,
			Direct&& theV
		)
			: theP_(std::move(theP))
			, theDir_(std::move(theV))
		{}

		const Point& P() const
		{
			return theP_;
		}

		Point& P()
		{
			return theP_;
		}

		const Direct& Dir() const
		{
			return theDir_;
		}

		Direct& Dir()
		{
			return theDir_;
		}
	};

	template<>
	class Entity_Line<const Pnt2d&, const Dir2d&>
	{

		/*Private Data*/

		const Pnt2d& theP_;
		const Dir2d& theDir_;


		DECLARE_SAVE_LOAD_HEADER(TnbGeo_EXPORT);

	public:

		Entity_Line
		(
			const Pnt2d& theP,
			const Dir2d& theV
		)
			: theP_(theP)
			, theDir_(theV)
		{}

		Entity_Line
		(
			Pnt2d&& theP,
			Dir2d&& theV
		)
			: theP_(std::move(theP))
			, theDir_(std::move(theV))
		{}

		const auto& P() const
		{
			return theP_;
		}

		const auto& Dir() const
		{
			return theDir_;
		}
	};

	typedef Entity_Line<Pnt2d, Dir2d> Entity2d_Line;
}

#include <Entity_LineI.hxx>

#endif // !_Entity_Line_Header
