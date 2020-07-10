#pragma once
#ifndef _Marine_Model_Header
#define _Marine_Model_Header

#include <Marine_Entity.hxx>
#include <Marine_ModelType.hxx>

namespace tnbLib
{

	class Marine_Model
		: public Marine_Entity
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		Marine_Model(_Types&&... _Args)
			: Marine_Entity(_Args...)
		{}

	public:


		virtual Marine_ModelType Type() const = 0;

		virtual Standard_Boolean IsHull() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSail() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTank() const
		{
			return Standard_False;
		}
	};
}

#endif // !_Marine_Model_Header
