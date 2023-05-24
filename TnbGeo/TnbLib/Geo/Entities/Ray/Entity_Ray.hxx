#pragma once
#ifndef _Entity_Ray_Header
#define _Entity_Ray_Header

#include <Global_Serialization.hxx>

namespace tnbLib
{

	template<class Point, class Dir>
	class Entity_Ray
	{

		/*Private Data*/

		Point thePoint_;
		Dir theDirection_;


		// Private functions and operators [4/30/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& thePoint_;
			ar& theDirection_;
		}

	public:

		// default constructor [4/30/2023 Payvand]

		Entity_Ray()
		{}


		// constructors [4/30/2023 Payvand]

		Entity_Ray(const Point& thePoint, const Dir& theDir)
			: thePoint_(thePoint)
			, theDirection_(theDir)
		{}

		Entity_Ray(Point&& thePoint, Dir2d&& theDir)
			: thePoint_(std::move(thePoint))
			, theDirection_(std::move(theDir))
		{}


		// Public functions and operators [4/30/2023 Payvand]

		const auto& Coord() const
		{
			return thePoint_;
		}

		auto& CoordRef() const
		{
			return thePoint_;
		}

		const auto& Direction() const
		{
			return theDirection_;
		}

		auto& DirectionRef()
		{
			return theDirection_;
		}

		void SetPoint(const Point& thePoint) { thePoint_ = thePoint; }
		void SetPoint(Point&& thePoint) { thePoint_ = std::move(thePoint); }
		void SetDirection(const Dir2d& theDir) { theDirection_ = theDir; }
		void SetDirection(Dir2d&& theDir) { theDirection_ = std::move(theDir); }

	};
}

#endif // !_Entity_Ray_Header
