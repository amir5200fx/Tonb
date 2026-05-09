#pragma once
#ifndef _StbGMaker_Scripts_Header
#define _StbGMaker_Scripts_Header

#include <Marine_ShapesFwd.hxx>

#include <memory>

class TopoDS_Shape;

namespace chaiscript
{
	class ChaiScript;
}

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_Creator;

	namespace script
	{

		struct StbModelMaker
		{

			std::shared_ptr<StbGMaker_Creator> newModelMaker() const;

			std::shared_ptr<marineLib::Shape_Sail> newSailShape(const TopoDS_Shape&);
			std::shared_ptr<marineLib::Shape_Hull> newHullShape(const TopoDS_Shape&);
			std::shared_ptr<marineLib::Shape_Tank> newTankShape(const TopoDS_Shape&);
		};

		void load_stb_gmaker(chaiscript::ChaiScript&);
	}
}

#endif // !_StbGMaker_Scripts_Header
