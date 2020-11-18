#pragma once
#ifndef _Marine_xSection_Header
#define _Marine_xSection_Header

#include <Marine_HullSection.hxx>

namespace tnbLib
{

	class Marine_xSection
		: public Marine_HullSection
	{

		/*Private Data*/


		/*private functions and operators*/

		DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);

	protected:

		template<class... _Types>
		Marine_xSection(_Types&&... _Args)
			: Marine_HullSection(_Args...)
		{}

	public:

		Standard_Boolean IsXsect() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsDry() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsWetted() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsDisplacer() const
		{
			return Standard_False;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_xSection);

#endif // !_Marine_xSection_Header
