#pragma once
#ifndef _Dir3d_Header
#define _Dir3d_Header

#include <gp_Dir.hxx>
#include <Vec3d.hxx>
#include <Geo_Module.hxx>
#include <Geo_Serialization.hxx>

namespace tnbLib
{

	//- Forward Declarations
	class Pnt3d;
	class Dir3d;

	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Dir3d&);
	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, Dir3d&);

	TnbGeo_EXPORT Ostream& operator<<(Ostream& os, const Dir3d&);
	TnbGeo_EXPORT Istream& operator>>(Istream& is, Dir3d&);

	class Dir3d
		: public gp_Dir
	{

		/*Private Data*/
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<gp_Dir>(*this);
		}

		//TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		static TnbGeo_EXPORT const Dir3d null;

		// default constructor

		Dir3d() = default;
		Dir3d(const Dir3d&) = default;
		Dir3d& operator=(const Dir3d&) = default;

		// constructors

		Dir3d(const gp_Dir& d)
			: gp_Dir(d)
		{}

		Dir3d(const gp_XYZ& xyz)
			: gp_Dir(xyz)
		{}

		Dir3d(const Vec3d& v)
			: gp_Dir(v)
		{}

		Dir3d
		(
			const Standard_Real x, 
			const Standard_Real y, 
			const Standard_Real z
		)
			: gp_Dir(x, y, z)
		{}

		Dir3d(Dir3d&& other) noexcept
			: gp_Dir(std::move(other))
		{}

		// Public functions and operators

		Dir3d& operator=(Dir3d&& other) noexcept
		{
			if (this != &other)
			{
				gp_Dir::operator=(other);
			}
			return *this;
		}

		TnbGeo_EXPORT Dir3d(const Pnt3d& theP0, const Pnt3d& theP1);

	};
}

#include <Dir3dI.hxx>

#endif // !_Dir3d_Header
