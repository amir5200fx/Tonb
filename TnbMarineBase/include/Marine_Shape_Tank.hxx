#pragma once
#ifndef _Marine_Shape_Tank_Header
#define _Marine_Shape_Tank_Header

#include <Marine_Shape.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Shape_Tank
			: public Marine_Shape
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Shape_Tank(_Types&&... _Args)
				: Marine_Shape(_Args...)
			{}

			Marine_ShapeType Type() const override
			{
				return Marine_ShapeType::tank;
			}

			Standard_Boolean IsTank() const override
			{
				return Standard_True;
			}
		};
	}
}

#endif // !_Marine_Shape_Tank_Header
