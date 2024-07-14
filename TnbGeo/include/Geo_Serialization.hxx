#pragma once
#ifndef _Geo_Serialization_Header
#define _Geo_Serialization_Header

#include <Global_Serialization.hxx>
#include <Geo_Module.hxx>

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
#include <gp_Mat2d.hxx>
#include <gp_Mat.hxx>
#include <gp_Vec.hxx>
#include <gp_Vec2d.hxx>
#include <gp_Trsf2d.hxx>
#include <gp_Trsf.hxx>

#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TShort_Array1OfShortReal.hxx>
#include <Poly_Array1OfTriangle.hxx>

// Forward Declarations
class Geom2d_Curve;
class Geom_Curve;
class Geom_Surface;
class TopoDS_Shape;
class Poly_Triangulation;
class Poly_Triangle;
class gp_Pnt;
class gp_Pnt2d;
class gp_Pln;

namespace boost
{
	namespace serialization
	{

		template<class Archive>
		void save(Archive & ar, const gp_XY & g, const unsigned int /*version*/)
		{
			ar << g.X();
			ar << g.Y();
		}

		template<class Archive>
		void load(Archive & ar, gp_XY & g, const unsigned int /*version*/)
		{
			Standard_Real x, y;
			ar >> x;
			ar >> y;
			g = gp_XY(x, y);
		}

		template<class Archive>
		void save(Archive & ar, const gp_XYZ & g, const unsigned int /*version*/)
		{
			ar << g.X();
			ar << g.Y();
			ar << g.Z();
		}

		template<class Archive>
		void load(Archive & ar, gp_XYZ & g, const unsigned int /*version*/)
		{
			Standard_Real x, y, z;
			ar >> x;
			ar >> y;
			ar >> z;
			g = gp_XYZ(x, y, z);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Dir2d & g, const unsigned int /*version*/)
		{
			ar << g.X();
			ar << g.Y();
		}

		template<class Archive>
		void load(Archive & ar, gp_Dir2d & g, const unsigned int /*version*/)
		{
			Standard_Real x, y;
			ar >> x;
			ar >> y;
			g = gp_Dir2d(x, y);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Dir & g, const unsigned int /*version*/)
		{
			ar << g.X();
			ar << g.Y();
			ar << g.Z();
		}

		template<class Archive>
		void load(Archive & ar, gp_Dir & g, const unsigned int /*version*/)
		{
			Standard_Real x, y, z;
			ar >> x;
			ar >> y;
			ar >> z;
			g = gp_Dir(x, y, z);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Pnt2d & g, const unsigned int /*version*/)
		{
			ar << g.X();
			ar << g.Y();
		}

		template<class Archive>
		void load(Archive & ar, gp_Pnt2d & g, const unsigned int /*version*/)
		{
			Standard_Real x, y;
			ar >> x;
			ar >> y;
			g = gp_Pnt2d(x, y);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Pnt & g, const unsigned int /*version*/)
		{
			ar << g.X();
			ar << g.Y();
			ar << g.Z();
		}

		template<class Archive>
		void load(Archive & ar, gp_Pnt & g, const unsigned int /*version*/)
		{
			Standard_Real x, y, z;
			ar >> x;
			ar >> y;
			ar >> z;
			g = gp_Pnt(x, y, z);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Ax1 & g, const unsigned int /*version*/)
		{
			ar << g.Location();
			ar << g.Direction();
		}

		template<class Archive>
		void load(Archive & ar, gp_Ax1 & g, const unsigned int /*version*/)
		{
			gp_Pnt loc;
			gp_Dir dir;
			ar >> loc;
			ar >> dir;
			gp_Ax1 ax(loc, dir);
			g = std::move(ax);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Ax2 & g, const unsigned int /*version*/)
		{
			ar << g.Axis();
			ar << g.YDirection();
			ar << g.XDirection();
		}

		template<class Archive>
		void load(Archive & ar, gp_Ax2 & g, const unsigned int /*version*/)
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

		template<class Archive>
		void save(Archive& ar, const gp_Ax2d & g, const unsigned int /*version*/)
		{
			ar << g.Location();
			ar << g.Direction();
		}

		template<class Archive>
		void load(Archive& ar, gp_Ax2d & g, const unsigned int /*version*/)
		{
			auto& loc = const_cast<gp_Pnt2d&>(g.Location());
			auto& dir = const_cast<gp_Dir2d&>(g.Direction());

			ar >> loc;
			ar >> dir;
		}

		template<class Archive>
		void save(Archive & ar, const gp_Mat2d & g, const unsigned int /*version*/)
		{
			ar & g(1, 1);
			ar & g(1, 2);
			ar & g(2, 1);
			ar & g(2, 2);
		}

		template<class Archive>
		void load(Archive & ar, gp_Mat2d & g, const unsigned int /*version*/)
		{
			ar & g(1, 1);
			ar & g(1, 2);
			ar & g(2, 1);
			ar & g(2, 2);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Mat & g, const unsigned int /*version*/)
		{
			ar & g(1, 1);
			ar & g(1, 2);
			ar & g(1, 3);
			ar & g(2, 1);
			ar & g(2, 2);
			ar & g(2, 3);
			ar & g(3, 1);
			ar & g(3, 2);
			ar & g(3, 3);
		}

		template<class Archive>
		void load(Archive & ar, gp_Mat & g, const unsigned int /*version*/)
		{
			ar & g(1, 1);
			ar & g(1, 2);
			ar & g(1, 3);
			ar & g(2, 1);
			ar & g(2, 2);
			ar & g(2, 3);
			ar & g(3, 1);
			ar & g(3, 2);
			ar & g(3, 3);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Vec2d & g, const unsigned int /*version*/)
		{
			ar & g.XY();
		}

		template<class Archive>
		void load(Archive & ar, gp_Vec2d & g, const unsigned int /*version*/)
		{
			gp_XY xy;
			ar & xy;
			g = gp_Vec2d(xy);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Vec & g, const unsigned int /*version*/)
		{
			ar & g.XYZ();
		}

		template<class Archive>
		void load(Archive & ar, gp_Vec & g, const unsigned int /*version*/)
		{
			gp_XYZ xyz;
			ar & xyz;
			g = gp_Vec(xyz);
		}

		template<class Archive>
		void save(Archive & ar, const gp_Trsf2d & g, const unsigned int)
		{
			ar& g.ScaleFactor();
			ar& g.Form();
			ar& g.HVectorialPart();
			ar& g.TranslationPart();
		}

		template<class Archive>
		void load(Archive & ar, gp_Trsf2d & g, const unsigned int /*version*/)
		{
			Standard_Real scale;
			ar& scale;
			gp_TrsfForm shape;
			ar& shape;
			gp_Mat2d matrix;
			ar& matrix;
			gp_XY loc;
			ar& loc;

			g.ScaleRef() = scale;
			g.ShapeRef() = shape;
			g.MatrixRef() = matrix;
			g.LocRef() = loc;
		}

		template<class Archive>
		void save(Archive & /*ar*/, const Poly_Triangle&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & /*ar*/, Poly_Triangle&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGeo_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const Poly_Triangle& s,
				const unsigned int version
				);

		template<>
		TnbGeo_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				Poly_Triangle& s,
				const unsigned int version
				);


		template<class Archive>
		void save(Archive & /*ar*/, const Handle(Poly_Triangulation)&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & /*ar*/, Handle(Poly_Triangulation)&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGeo_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const Handle(Poly_Triangulation)& s,
				const unsigned int version
				);

		template<>
		TnbGeo_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				Handle(Poly_Triangulation)& s,
				const unsigned int version
				);

		template<class Archive>
		void save(Archive & /*ar*/, const TShort_Array1OfShortReal&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & /*ar*/, TShort_Array1OfShortReal&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGeo_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const TShort_Array1OfShortReal& s,
				const unsigned int version
				);

		template<>
		TnbGeo_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				TShort_Array1OfShortReal& s,
				const unsigned int version
				);

		template<class Archive>
		void save(Archive & /*ar*/, const Poly_Array1OfTriangle&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & /*ar*/, Poly_Array1OfTriangle&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGeo_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const Poly_Array1OfTriangle& s,
				const unsigned int version
				);

		template<>
		TnbGeo_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				Poly_Array1OfTriangle& s,
				const unsigned int version
				);

		template<class Archive>
		void save(Archive & /*ar*/, const TColgp_Array1OfPnt2d&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & /*ar*/, TColgp_Array1OfPnt2d&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGeo_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const TColgp_Array1OfPnt2d& s,
				const unsigned int version
				);

		template<>
		TnbGeo_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				TColgp_Array1OfPnt2d& s,
				const unsigned int version
				);

		template<class Archive>
		void save(Archive & /*ar*/, const TColgp_Array1OfPnt&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & /*ar*/, TColgp_Array1OfPnt&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGeo_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const TColgp_Array1OfPnt& s,
				const unsigned int version
				);

		template<>
		TnbGeo_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				TColgp_Array1OfPnt& s,
				const unsigned int version
				);

		template<class Archive>
		void save(Archive& ar, const gp_Pln&, const unsigned int)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive& ar, gp_Pln&, const unsigned int)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGeo_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const gp_Pln& s,
				const unsigned int version
				);

		template<>
		TnbGeo_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				gp_Pln& s,
				const unsigned int version
				);

		template<class Archive>
		void save(Archive& ar, const std::shared_ptr<gp_Pln>&, const unsigned int)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive& ar, std::shared_ptr<gp_Pln>&, const unsigned int)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGeo_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const std::shared_ptr<gp_Pln>& s,
				const unsigned int version
				);

		template<>
		TnbGeo_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				std::shared_ptr<gp_Pln>& s,
				const unsigned int version
				);
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
BOOST_SERIALIZATION_SPLIT_FREE(gp_Mat2d)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Mat)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Trsf2d)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Vec2d)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Vec)
BOOST_SERIALIZATION_SPLIT_FREE(Poly_Triangle)
BOOST_SERIALIZATION_SPLIT_FREE(Handle(Poly_Triangulation))
BOOST_SERIALIZATION_SPLIT_FREE(TShort_Array1OfShortReal)
BOOST_SERIALIZATION_SPLIT_FREE(Poly_Array1OfTriangle)
BOOST_SERIALIZATION_SPLIT_FREE(TColgp_Array1OfPnt2d)
BOOST_SERIALIZATION_SPLIT_FREE(TColgp_Array1OfPnt)
BOOST_SERIALIZATION_SPLIT_FREE(gp_Pln)
BOOST_SERIALIZATION_SPLIT_FREE(std::shared_ptr<gp_Pln>)

#endif // !_Geo_Serialization_Header
