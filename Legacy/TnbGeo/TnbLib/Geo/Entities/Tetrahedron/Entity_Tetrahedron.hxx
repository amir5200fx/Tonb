#pragma once
#ifndef _Entity_Tetrahedron_Header
#define _Entity_Tetrahedron_Header

#include <Pnt3d.hxx>

namespace tnbLib
{

	template<class Point>
	class Entity_Tetrahedron
	{

		/*Private Data*/

		Point theP0_;
		Point theP1_;
		Point theP2_;
		Point theP3_;

		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theP0_;
			ar & theP1_;
			ar & theP2_;
			ar & theP3_;
		}

	public:

		// default constructor [10/28/2022 Amir]

		Entity_Tetrahedron()
			: theP0_(Point::null)
			, theP1_(Point::null)
			, theP2_(Point::null)
			, theP3_(Point::null)
		{}


		// constructors [10/28/2022 Amir]

		Entity_Tetrahedron
		(
			const Point& theP0,
			const Pnt3d& theP1,
			const Pnt3d& theP2,
			const Pnt3d& theP3
		)
			: theP0_(theP0)
			, theP1_(theP1)
			, theP2_(theP2)
			, theP3_(theP3)
		{}

		Entity_Tetrahedron
		(
			Point&& theP0,
			Pnt3d&& theP1,
			Pnt3d&& theP2,
			Pnt3d&& theP3
		)
			: theP0_(std::move(theP0))
			, theP1_(std::move(theP1))
			, theP2_(std::move(theP2))
			, theP3_(std::move(theP3))
		{}

		// public functions and operators [10/28/2022 Amir]

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

		const auto& P2() const
		{
			return theP2_;
		}

		auto& P2Ref()
		{
			return theP2_;
		}

		const auto& P3() const
		{
			return theP3_;
		}

		auto& P3Ref()
		{
			return theP3_;
		}

		const Point& Vertex
		(
			const Standard_Integer theIndex
		) const
		{
			return (&theP0_)[theIndex];
		}
	};

	// Forward Declarations [10/28/2022 Amir]

	class Pnt3d;

	template<>
	class Entity_Tetrahedron<const Pnt3d&>
	{

		/*Private Data*/

		const Pnt3d& theP0_;
		const Pnt3d& theP1_;
		const Pnt3d& theP2_;
		const Pnt3d& theP3_;

	public:

		// default constructor [10/28/2022 Amir]


		// constructors [10/28/2022 Amir]

		Entity_Tetrahedron
		(
			const Pnt3d& theP0, 
			const Pnt3d& theP1, 
			const Pnt3d& theP2,
			const Pnt3d& theP3
		)
			: theP0_(theP0)
			, theP1_(theP1)
			, theP2_(theP2)
			, theP3_(theP3)
		{}


		// public functions and operators [10/28/2022 Amir]

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

		const auto& P3() const
		{
			return theP3_;
		}

		const auto& Vertex(const Standard_Integer theIndex) const
		{
			if (theIndex == 0)
			{
				return theP0_;
			}
			else if (theIndex == 1)
			{
				return theP1_;
			}
			else if (theIndex == 2)
			{
				return theP2_;
			}
			else
			{
				return theP3_;
			}
		}
	};
}

#endif // !_Entity_Tetrahedron_Header
