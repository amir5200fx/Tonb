#pragma once
#ifndef _Dir2d_Header
#define _Dir2d_Header

#include <gp_Dir2d.hxx>
#include <Vec2d.hxx>
#include <Geo_Module.hxx>
#include <Geo_Serialization.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Dir2d;

	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Dir2d&);
	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, Dir2d&);

	TnbGeo_EXPORT Ostream& operator<<(Ostream& os, const Dir2d&);
	TnbGeo_EXPORT Istream& operator>>(Istream& is, Dir2d&);

	class Dir2d
		: public gp_Dir2d
	{
		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<gp_Dir2d>(*this);
		}

		//TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		static TnbGeo_EXPORT const Dir2d null;

		// default constructor

		Dir2d() = default;
		Dir2d(const Dir2d&) = default;
		Dir2d& operator=(const Dir2d&) = default;

		// constructors

		Dir2d(const gp_Dir2d& d)
			: gp_Dir2d(d)
		{}

		Dir2d
		(
			const gp_XY& Coord
		)
			: gp_Dir2d(Coord)
		{}

		Dir2d
		(
			const Vec2d& V
		)
			: gp_Dir2d(V)
		{}

		Dir2d
		(
			const Standard_Real Xv,
			const Standard_Real Yv
		)
			: gp_Dir2d(Xv, Yv)
		{}

		Dir2d(Dir2d&& other) noexcept
			: gp_Dir2d(std::move(other))
		{}


		// Public functions and operators

		Dir2d& operator=(Dir2d&& other) noexcept
		{
			if (this != &other)
			{
				gp_Dir2d::operator=(other);
			}
			return *this;
		}

		TnbGeo_EXPORT Dir2d
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		);
	};
}

#include <Dir2dI.hxx>

#endif // !_Dir2d_Header