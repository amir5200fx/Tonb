#pragma once
#ifndef _Vec3d_Header
#define _Vec3d_Header

#include <gp_Vec.hxx>
#include <Pnt3d.hxx>
#include <Geo_Serialization.hxx>

namespace tnbLib
{

	//- Forward Declarations
	class Dir3d;
	class Vec3d;

	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Vec3d&);
	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, Vec3d&);

	TnbGeo_EXPORT Ostream& operator<<(Ostream& os, const Vec3d&);
	TnbGeo_EXPORT Istream& operator>>(Istream& is, Vec3d&);

	class Vec3d
		: public gp_Vec
	{

		/*Private Data*/

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<gp_Vec>(*this);
		}

	public:

		static TnbGeo_EXPORT const Vec3d null;

		//- default constructor

		Vec3d()
		{}

		//- constructors

		TnbGeo_EXPORT Vec3d(const Dir3d& V);

		Vec3d(const gp_XYZ& xyz)
			: gp_Vec(xyz)
		{}

		Vec3d(const gp_Vec& v)
			: gp_Vec(v)
		{}

		Vec3d(const Standard_Real x, const Standard_Real y, const Standard_Real z)
			: gp_Vec(x, y, z)
		{}

		Vec3d(const Pnt3d& theP0, const Pnt3d& theP1)
			: gp_Vec(theP0, theP1)
		{}


		//- public functions and operators

	};
}

#endif // !_Vec3d_Header
