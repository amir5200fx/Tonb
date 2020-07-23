#pragma once
#ifndef _Marine_DisctTools_Header
#define _Marine_DisctTools_Header

#include <memory>
#include <vector>

class TopoDS_Shape;
class gp_Ax2;

namespace tnbLib
{

	// Forward Declarations
	class Marine_Distrb;
	class Marine_CmpSection;
	class Marine_Section;

	class Marine_DisctTools
	{

	public:

		static TopoDS_Shape
			Section
			(
				const TopoDS_Shape& theShape,
				const gp_Ax2& theSys
			);

		static std::vector<std::shared_ptr<Marine_CmpSection>>
			WettedSections
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::vector<std::shared_ptr<Marine_Section>>& theWaters
			);
	};
}

#endif // !_Marine_DisctTools_Header
