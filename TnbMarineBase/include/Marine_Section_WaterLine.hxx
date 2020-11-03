#pragma once
#ifndef _Marine_Section_WaterLine_Header
#define _Marine_Section_WaterLine_Header

#include <Marine_zSection.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Section_WaterLine
			: public Marine_zSection
		{

			/*Private Data*/


			/*private functions and operators*/

			DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);

		protected:

			template<class... _Types>
			Section_WaterLine(_Types&&... _Args)
				: Marine_zSection(_Args...)
			{}

		public:

			Standard_Boolean IsWaterLine() const override
			{
				return Standard_True;
			}

			virtual Standard_Boolean IsInner() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsOuter() const
			{
				return Standard_False;
			}

			//std::shared_ptr<Marine_Section> Copy() const override;

			Marine_SectionType Type() const override
			{
				return Marine_SectionType::waterLine;
			}
		};
	}
}

#endif // !_Marine_Section_WaterLine_Header
