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

		public:

			template<class... _Types>
			Body_Tank(_Types&&... _Args)
				: Marine_Body(_Args...)
			{}

			Standard_Boolean IsTank() const override
			{
				return Standard_True;
			}

			Marine_BodyType Type() const override
			{
				return Marine_BodyType::tank;
			}

			std::shared_ptr<Marine_Body> Copy() const override;
		};
	}
}

#endif // !_Marine_Body_Tank_Header
