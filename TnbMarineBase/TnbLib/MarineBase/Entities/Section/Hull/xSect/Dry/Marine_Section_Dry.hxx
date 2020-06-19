#pragma once
#ifndef _Marine_Section_Dry_Header
#define _Marine_Section_Dry_Header

#include <Marine_xSection.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Section_Dry
			: public Marine_xSection
		{

			/*Private Data*/

		protected:

			template<class... _Types>
			Section_Dry(_Types&&... _Args)
				: Marine_xSection(_Args...)
			{}

		public:

			virtual Standard_Boolean IsInner() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsOuter() const
			{
				return Standard_False;
			}

			Standard_Boolean IsDry() const override
			{
				return Standard_True;
			}

			Marine_SectionType Type() const override
			{
				return Marine_SectionType::dry;
			}

		};
	}
}

#endif // !_Marine_Section_Dry_Header
