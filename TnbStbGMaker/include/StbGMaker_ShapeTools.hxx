#pragma once
#ifndef _StbGMaker_ShapeTools_Header
#define _StbGMaker_ShapeTools_Header

#include <Marine_ShapesFwd.hxx>

#include <memory>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	class StbGMaker_ShapeTools
	{

	public:

		static std::shared_ptr<marineLib::Shape_Sail> Sail(const TopoDS_Shape& theShape);

		static std::shared_ptr<marineLib::Shape_Hull> Hull(const TopoDS_Shape& theShape);

		static std::shared_ptr<marineLib::Shape_Tank> Tank(const TopoDS_Shape& theShape);
	};
}

#endif // !_StbGMaker_ShapeTools_Header
