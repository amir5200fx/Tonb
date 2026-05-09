#pragma once
#ifndef _Marine_Section_Tank_Header
#define _Marine_Section_Tank_Header

#include <Marine_Section.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Section_Tank
			: public Marine_Section
		{

			/*Private Data*/


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<Marine_Section>(*this);
			}
	

		protected:

			template<class... _Types>
			Section_Tank(_Types&&... _Args)
				: Marine_Section(_Args...)
			{
				CheckCurves();
			}


			template<>
			Section_Tank()
			{}

			TnbMarine_EXPORT void CheckCurves() const;

		public:

			virtual Standard_Boolean IsInner() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsOuter() const
			{
				return Standard_False;
			}

			Standard_Boolean IsTank() const override
			{
				return Standard_True;
			}

			Marine_SectionType Type() const override
			{
				return Marine_SectionType::tank;
			}
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Section_Tank);

#include <Marine_Section_Constructor.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::InnerSection<tnbLib::marineLib::Section_Tank>);
BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Tank>);

#endif // !_Marine_Section_Tank_Header
