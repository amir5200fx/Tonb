#pragma once
#ifndef _Marine_Model_Tank_Header
#define _Marine_Model_Tank_Header

#include <Marine_Model.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Model_Tank
			: public Marine_Model
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Model_Tank(_Types&&... _Args)
				: Marine_Model(_Args...)
			{}

			Marine_ModelType Type() const override
			{
				return Marine_ModelType::tank;
			}

			Standard_Boolean IsTank() const override
			{
				return Standard_True;
			}
		};
	}
}

#endif // !_Marine_Model_Tank_Header
