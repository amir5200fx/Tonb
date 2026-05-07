#pragma once
#ifndef _ShapePx_Shape_Header
#define _ShapePx_Shape_Header

#include <ShapePx_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_Section;

	class ShapePx_Shape
		: public ShapePx_Entity
	{

		/*Private Data*/

		std::shared_ptr<ShapePx_Section> theSection_;
	};
}

#endif // !_ShapePx_Shape_Header
