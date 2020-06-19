#pragma once
#ifndef _Marine_Model_Sail_Header
#define _Marine_Model_Sail_Header

#include <Marine_Model.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Model_Sail
			: public Marine_Model
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Model_Sail(_Types&&... _Args)
				: Marine_Model(_Args...)
			{}

			Marine_ModelType Type() const override
			{
				return Marine_ModelType::sail;
			}

			Standard_Boolean IsSail() const override
			{
				return Standard_True;
			}
		};
	}
}

#endif // !_Marine_Model_Sail_Header
