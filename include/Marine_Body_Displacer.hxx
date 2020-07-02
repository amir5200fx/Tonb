#pragma once
#ifndef _Marine_Body_Displacer_Header
#define _Marine_Body_Displacer_Header

#include <Marine_HullBody.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Body_Displacer
			: public Marine_HullBody
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Body_Displacer(_Types&&... _Args)
				: Marine_HullBody(_Args...)
			{}

			Standard_Boolean IsDisplacer() const override
			{
				return Standard_True;
			}

			Marine_BodyType Type() const override
			{
				return Marine_BodyType::displacer;
			}

			std::shared_ptr<Marine_Body> Copy() const override;
		};
	}
}

#endif // !_Marine_Body_Displacer_Header
