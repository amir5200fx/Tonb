#pragma once
#ifndef _Cad2d_Scripts_Header
#define _Cad2d_Scripts_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Entity2d_Polygon.hxx>

#include <memory>

class Geom2d_Curve;

namespace chaiscript
{
	class ChaiScript;
}

namespace tnbLib
{

	// Forward Declarations

	namespace script
	{

		struct Cad2d
		{

			std::shared_ptr<Entity2d_Polygon> uniformDiscretize(const Handle(Geom2d_Curve)& theCurve, const Standard_Integer nSeg) const;

			void exportToPlt(const Handle(Geom2d_Curve)& theCurve, const Standard_Integer n, OFstream& f);
			void exportToPlt(const Handle(Geom2d_Curve)& theCurve, const Standard_Integer n, const word& name);
			void exportToPlt(const Handle(Geom2d_Curve)& theCurve, const Standard_Integer n, const std::string& name);
		};

		void load_cad2d(chaiscript::ChaiScript&);
	}
}

#endif // !_Cad2d_Scripts_Header
