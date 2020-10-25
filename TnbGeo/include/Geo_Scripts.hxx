#pragma once
#ifndef _Geo_Scripts_Header
#define _Geo_Scripts_Header

#include <Standard_TypeDef.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>

class gp_Ax1;
class gp_Ax2;

namespace chaiscript
{
	class ChaiScript;
}

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Pnt3d;
	class Dir2d;
	class Dir3d;

	class Geo_UniDistb;
	class Geo_CosineDistb;

	namespace script
	{

		struct Geo
		{

			Standard_Real getConfusion() const;

			Pnt3d createPnt3d() const;
			Pnt3d createPnt3d(const Standard_Real x, const Standard_Real y, const Standard_Real z) const;
			Pnt2d createPnt2d() const;
			Pnt2d createPnt2d(const Standard_Real x, const Standard_Real y) const;

			Dir2d createDir2d() const;
			Dir2d createDir2d(const Standard_Real x, const Standard_Real y) const;
			Dir3d createDir3d() const;
			Dir3d createDir3d(const Standard_Real x, const Standard_Real y, const Standard_Real z) const;

			gp_Ax1 create_gpAx1() const;
			gp_Ax1 create_gpAx1(const Pnt3d&, const Dir3d&) const;

			Entity2d_Box createBox2d(const Pnt2d&, const Pnt2d&) const;
			Entity3d_Box createBox3d(const Pnt3d&, const Pnt3d&) const;

			std::shared_ptr<Geo_UniDistb> newUniformDistb(const Standard_Real x0, const Standard_Real x1, const Standard_Integer n) const;
			std::shared_ptr<Geo_CosineDistb> newCosineDistb(const Standard_Real x0, const Standard_Real x1, const Standard_Integer n) const;
		};

		void load_geo(chaiscript::ChaiScript&);
	}
}

#endif // !_Geo_Scripts_Header
