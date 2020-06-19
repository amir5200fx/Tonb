#pragma once
#ifndef _Marine_Model_Hull_Header
#define _Marine_Model_Hull_Header

#include <Marine_Model.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Model_Hull
			: public Marine_Model
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Model_Hull(_Types&&... _Args)
				: Marine_Model(_Args...)
			{}


			Marine_ModelType Type() const override
			{
				return Marine_ModelType::hull;
			}

			Standard_Boolean IsHull() const override
			{
				return Standard_True;
			}
		};
	}
}

#endif // !_Marine_Model_Hull_Header
