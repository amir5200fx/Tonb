#pragma once
#ifndef _Marine_Body_Tank_Header
#define _Marine_Body_Tank_Header

#include <Marine_Body.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Body_Tank
			: public Marine_Body
		{

			/*Private Data*/

		protected:

			template<class... _Types>
			Body_Tank(_Types&&... _Args)
				: Marine_Body(_Args...)
			{}

		public:

			Standard_Boolean IsTank() const override
			{
				return Standard_True;
			}

			Marine_BodyType Type() const override
			{
				return Marine_BodyType::tank;
			}

			virtual Standard_Boolean ShapeType() const
			{
				return Standard_False;
			}

			std::shared_ptr<Marine_Body> Copy() const override;
		};
	}
}

#include <Marine_BodyConstructor.hxx>

#endif // !_Marine_Body_Tank_Header
