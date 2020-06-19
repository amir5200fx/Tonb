#pragma once
#ifndef _Marine_Body_Sail_Header
#define _Marine_Body_Sail_Header

#include <Marine_Body.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Body_Sail
			: public Marine_Body
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Body_Sail(_Types&&... _Args)
				: Marine_Body(_Args...)
			{}

			Standard_Boolean IsSail() const override
			{
				return Standard_True;
			}

			Marine_BodyType Type() const override
			{
				return Marine_BodyType::sail;
			}

			std::shared_ptr<Marine_Body> Copy() const override;
		};
	}
}

#endif // !_Marine_Body_Sail_Header
