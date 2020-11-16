#pragma once
#ifndef _Dir3d_Header
#define _Dir3d_Header

#include <gp_Dir.hxx>
#include <Vec3d.hxx>
#include <Geo_Module.hxx>
#include <Geo_Serialization.hxx>

namespace tnbLib
{

	class Pnt3d;

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

		//DECLARE_SAVE_LOAD_HEADER(TnbGeo_EXPORT);

	public:

		static TnbGeo_EXPORT const Dir3d null;

		Dir3d()
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

		TnbGeo_EXPORT Dir3d(const Pnt3d& theP0, const Pnt3d& theP1);

	};
}

#endif // !_Dir3d_Header
