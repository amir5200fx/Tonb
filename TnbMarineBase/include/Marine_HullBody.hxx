#pragma once
#ifndef _Marine_HullBody_Header
#define _Marine_HullBody_Header

#include <Marine_Body.hxx>

namespace tnbLib
{

	class Marine_HullBody
		: public Marine_Body
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		Marine_HullBody(_Types&&... _Args)
			: Marine_Body(_Args...)
		{}

	public:

		Standard_Boolean IsHull() const override
		{
			return Standard_True;
		}

		Standard_Boolean IsLaunched() const;

		virtual Standard_Boolean IsWetted() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsDry() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsDisplacer() const
		{
			return Standard_False;
		}
	};
}

#endif // !_Marine_HullBody_Header
