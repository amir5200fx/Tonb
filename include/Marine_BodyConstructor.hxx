#pragma once
#ifndef _Marine_BodyConstructor_Header
#define _Marine_BodyConstructor_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Shape;

	namespace marineLib
	{

		template<class BodyType>
		class BodyConstructor_Shape
			: public BodyType
		{

			/*Private Data*/

			std::shared_ptr<Marine_Shape> theShape_;

		public:

			template<class... _Types>
			BodyConstructor_Shape(_Types&&... _Args)
				: BodyType(_Args...)
			{}

			Standard_Boolean ShapeType() const override
			{
				return Standard_True;
			}

			const auto& Shape() const
			{
				return theShape_;
			}

			void SetShape(const std::shared_ptr<Marine_Shape>& theShape)
			{
				theShape_ = theShape;
			}
		};

	}


	namespace marineLib
	{

		template<class BodyType>
		class BodyConstructor_noShape
			: public BodyType
		{

			/*Private Data*/

		public:

			template<class... _Types>
			BodyConstructor_noShape(_Types&&... _Args)
				: BodyType(_Args...)
			{}

		};
	}


}

#endif // !_Marine_BodyConstructor_Header
