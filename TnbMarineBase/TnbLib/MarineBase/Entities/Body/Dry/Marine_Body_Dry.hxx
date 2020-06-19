#pragma once
#ifndef _Marine_Body_Dry_Header
#define _Marine_Body_Dry_Header

#include <Marine_HullBody.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Body_Dry
			: public Marine_HullBody
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Body_Dry(_Types&&... _Args)
				: Marine_HullBody(_Args...)
			{}

			Standard_Boolean IsDry() const override
			{
				return Standard_True;
			}

			Marine_BodyType Type() const override
			{
				return Marine_BodyType::dry;
			}

			std::shared_ptr<Marine_Body> Copy() const override;
		};
	}
}

#endif // !_Marine_Body_Dry_Header
