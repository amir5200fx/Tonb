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

			TNB_SERIALIZATION(TnbMarine_EXPORT);


		protected:

			template<class... _Types>
			Section_WaterLine(_Types&&... _Args)
				: Marine_zSection(_Args...)
			{
				CheckCurves();
			}

			template<>
			Section_WaterLine()
			{}

			TnbMarine_EXPORT void CheckCurves() const;

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

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Section_WaterLine);

#include <Marine_Section_Constructor.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::InnerSection<tnbLib::marineLib::Section_WaterLine>);
BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_WaterLine>);

#endif // !_Marine_Section_WaterLine_Header
