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

		//DECLARE_SAVE_LOAD_HEADER(TnbGeo_EXPORT);

	public:

		static TnbGeo_EXPORT const Dir2d null;

		Dir2d()
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

		TnbGeo_EXPORT Dir2d
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		);
	};
}

#endif // !_Dir2d_Header