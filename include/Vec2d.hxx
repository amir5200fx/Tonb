#pragma once
#ifndef _Vec2d_Header
#define _Vec2d_Header

#include <gp_Vec2d.hxx>
#include <Pnt2d.hxx>
#include <Geo_Serialization.hxx>

namespace tnbLib
{

	//- Forward Declarations
	class Dir2d;
	class Vec2d;

	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Vec2d&);
	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, Vec2d&);

	TnbGeo_EXPORT Ostream& operator<<(Ostream& os, const Vec2d&);
	TnbGeo_EXPORT Istream& operator>>(Istream& is, Vec2d&);

	class Vec2d
		: public gp_Vec2d
	{

		/*Private Data*/

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<gp_Vec2d>(*this);
		}

	public:

		static TnbGeo_EXPORT const Vec2d null;

		//- default constructor

		Vec2d() = default;
		Vec2d(const Vec2d&) = default;


		//- constructors

		TnbGeo_EXPORT Vec2d
		(
			const Dir2d& V
		);

		Vec2d(const gp_Vec2d& v)
			: gp_Vec2d(v)
		{}

		Vec2d
		(
			const gp_XY& Coord
		)
			: gp_Vec2d(Coord)
		{}

		Vec2d
		(
			const Standard_Real Xv,
			const Standard_Real Yv
		)
			: gp_Vec2d(Xv, Yv)
		{}

		Vec2d
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		)
			: gp_Vec2d(theP0, theP1)
		{}

		Vec2d(Vec2d&& other) noexcept
			: gp_Vec2d(std::move(other))
		{}

		//- public functions and operators

		Vec2d& operator=(Vec2d&& other) noexcept
		{
			if (this != &other)
			{
				gp_Vec2d::operator=(other);
			}
			return *this;
		}
		Vec2d& operator=(const Vec2d&) = default;

	};
}

#include <Vec2dI.hxx>

#endif // !_Vec2d_Header