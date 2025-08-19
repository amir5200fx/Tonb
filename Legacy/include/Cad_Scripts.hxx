#pragma once
#ifndef _Cad_Scripts_Header
#define _Cad_Scripts_Header

#include <Standard_TypeDef.hxx>
#include <Entity3d_BoxFwd.hxx>

#include <memory>

class TopoDS_Shape;
class gp_Ax2;

namespace chaiscript
{
	class ChaiScript;
}

namespace tnbLib
{

	namespace script
	{

		struct Cad
		{

			Standard_Real getDiameter(const TopoDS_Shape&);
			Entity3d_Box getBoundingBox(const TopoDS_Shape&);

			TopoDS_Shape newBox(const Pnt3d&, const Pnt3d&);
			TopoDS_Shape newBox(const gp_Ax2&, const Standard_Real dx, const Standard_Real dy, const Standard_Real dz);
			TopoDS_Shape newCylinder(const gp_Ax2&, const Standard_Real r, const Standard_Real h);
			TopoDS_Shape newSphere(const gp_Ax2&, const Standard_Real r);
			TopoDS_Shape newSphere(const Pnt3d&, const Standard_Real r);
		};

		void load_cad(chaiscript::ChaiScript&);
	}
}

#endif // !_Cad_Scripts_Header
