#pragma once
#ifndef _Marine_WireFrameShape_Shape_Header
#define _Marine_WireFrameShape_Shape_Header

#include <Marine_WireFrameShape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Shape;
	class Marine_DisctLib;

	namespace marineLib
	{

		class WireFrameShape_Shape
			: public Marine_WireFrameShape
		{

			friend class Marine_DisctLib;

			/*Private Data*/

			std::shared_ptr<Marine_Shape> theShape_;


			auto& ChangeShape()
			{
				return theShape_;
			}

		public:

			template<class... _Types>
			WireFrameShape_Shape(_Types&&... _Args)
				: Marine_WireFrameShape(_Args...)
			{}


			const auto& Shape() const
			{
				return theShape_;
			}

			Standard_Boolean HasShape() const override
			{
				return Standard_True;
			}
		};
	}
}

#endif // !_Marine_WireFrameShape_Shape_Header
