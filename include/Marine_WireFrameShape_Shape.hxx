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


			/*private functions and operators*/

			TNB_SERIALIZATION(TnbMarine_EXPORT);

			auto& ChangeShape()
			{
				return theShape_;
			}

		public:


			//- constructors

			WireFrameShape_Shape()
			{}

			TnbMarine_EXPORT explicit WireFrameShape_Shape(const Standard_Integer theIndex);

			TnbMarine_EXPORT WireFrameShape_Shape
			(
				const Standard_Integer theIndex,
				const word& theName
			);


			//- public functions and operators

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

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::WireFrameShape_Shape);

#endif // !_Marine_WireFrameShape_Shape_Header
