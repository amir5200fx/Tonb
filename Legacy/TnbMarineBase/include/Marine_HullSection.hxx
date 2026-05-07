#pragma once
#ifndef _Marine_HullSection_Header
#define _Marine_HullSection_Header

#include <Marine_Section.hxx>

namespace tnbLib
{

	class Marine_HullSection
		: public Marine_Section
	{

		/*Private Data*/

		/*private functions and operators*/

		TNB_SERIALIZATION(TnbMarine_EXPORT);

	protected:

		template<class... _Types>
		Marine_HullSection(_Types&&... _Args)
			: Marine_Section(_Args...)
		{}

	public:

		Standard_Boolean IsHull() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsXsect() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsZsect() const
		{
			return Standard_False;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_HullSection);

#endif // !_Marine_HullSection_Header
