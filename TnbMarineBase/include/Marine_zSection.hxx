#pragma once
#ifndef _Marine_zSection_Header
#define _Marine_zSection_Header

#include <Marine_HullSection.hxx>

namespace tnbLib
{

	class Marine_zSection
		: public Marine_HullSection
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		Marine_zSection(_Types&&... _Args)
			: Marine_HullSection(_Args...)
		{}

	public:

		Standard_Boolean IsZsect() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsWaterLine() const
		{
			return Standard_False;
		}
	};
}

#endif // !_Marine_zSection_Header
