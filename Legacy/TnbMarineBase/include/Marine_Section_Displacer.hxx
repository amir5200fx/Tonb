#pragma once
#ifndef _Marine_Section_Displacer_Header
#define _Marine_Section_Displacer_Header

#include <Marine_xSection.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Section_Displacer
			: public Marine_xSection
		{

			/*Private Data*/


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<Marine_xSection>(*this);
			}


		protected:

			template<class... _Types>
			Section_Displacer(_Types&&... _Args)
				: Marine_xSection(_Args...)
			{
				CheckCurves();
			}

			template<>
			Section_Displacer()
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

			Standard_Boolean IsDisplacer() const override
			{
				return Standard_True;
			}

			Marine_SectionType Type() const override
			{
				return Marine_SectionType::displacer;
			}
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Section_Displacer);

#include <Marine_Section_Constructor.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::InnerSection<tnbLib::marineLib::Section_Displacer>);
BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Displacer>);

#endif // !_Marine_Section_Displacer_Header
