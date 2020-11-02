#pragma once
#ifndef _Geo_Serialization_Header
#define _Geo_Serialization_Header

#include <Global_Serialization.hxx>

#include <gp_XY.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax2d.hxx>

namespace boost
{
	namespace serialization
	{

		template<class Archive>
		void save(Archive & ar, const gp_XY & g, const unsigned int version)
		{
			ar << g.X();
			ar << g.Y();
		}

		template<class Archive>
		void load(Archive & ar, gp_XY & g, const unsigned int version)
		{
			Standard_Real x, y;
			ar >> x;
			ar >> y;
			g = gp_XY(x, y);
		}

		template<class Archive>
		void save(Archive & ar, const gp_XYZ & g, const unsigned int version)
		{
			ar << g.X();
			ar << g.Y();
			ar << g.Z();
		}

		template<class Archive>
		void load(Archive & ar, gp_XYZ & g, const unsigned int version)
		{
			Standard_Real x, y, z;
			ar >> x;
			ar >> y;
			ar >> z;
			g = gp_XYZ(x, y, z);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Dir2d & g, const unsigned int version)
		{
			ar << g.X();
			ar << g.Y();
		}

		template<class Archive>
		void load(Archive & ar, gp_Dir2d & g, const unsigned int version)
		{
			Standard_Real x, y;
			ar >> x;
			ar >> y;
			g = gp_Dir2d(x, y);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Dir & g, const unsigned int version)
		{
			ar << g.X();
			ar << g.Y();
			ar << g.Z();
		}

		template<class Archive>
		void load(Archive & ar, gp_Dir & g, const unsigned int version)
		{
			Standard_Real x, y, z;
			ar >> x;
			ar >> y;
			ar >> z;
			g = gp_Dir(x, y, z);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Pnt2d & g, const unsigned int version)
		{
			ar << g.X();
			ar << g.Y();
		}

		template<class Archive>
		void load(Archive & ar, gp_Pnt2d & g, const unsigned int version)
		{
			Standard_Real x, y;
			ar >> x;
			ar >> y;
			g = gp_Pnt2d(x, y);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Pnt & g, const unsigned int version)
		{
			ar << g.X();
			ar << g.Y();
			ar << g.Z();
		}

		template<class Archive>
		void load(Archive & ar, gp_Pnt & g, const unsigned int version)
		{
			Standard_Real x, y, z;
			ar >> x;
			ar >> y;
			ar >> z;
			g = gp_Pnt(x, y, z);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Ax1 & g, const unsigned int version)
		{
			ar << g.Location();
			ar << g.Direction();
		}

		template<class Archive>
		void load(Archive & ar, gp_Ax1 & g, const unsigned int version)
		{
			gp_Pnt loc;
			gp_Dir dir;
			ar >> loc;
			ar >> dir;
			gp_Ax1 ax(loc, dir);
			g = std::move(ax);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Ax2 & g, const unsigned int version)
		{
			ar << g.Axis();
			ar << g.YDirection();
			ar << g.XDirection();
		}

		template<class Archive>
		void load(Archive & ar, gp_Ax2 & g, const unsigned int version)
		{
			gp_Ax1 ax;
			gp_Dir ydir, xdir;

			auto& ax0 = const_cast<gp_Ax1&>(g.Axis());
			auto& ydir0 = const_cast<gp_Dir&>(g.YDirection());
			auto& xdir0 = const_cast<gp_Dir&>(g.XDirection());

			ar >> ax;
			ar >> ydir;
			ar >> xdir;
			
			ax0 = std::move(ax);
			ydir0 = std::move(ydir);
			xdir0 = std::move(xdir);
		}
	}
}

BOOST_SERIALIZATION_SPLIT_FREE(gp_XY)
BOOST_SERIALIZATION_SPLIT_FREE(gp_XYZ)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Dir2d)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Dir)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Pnt2d)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Pnt)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Ax1)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Ax2)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Ax2d)

#endif // !_Geo_Serialization_Header
