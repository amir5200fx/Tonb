#pragma once
#ifndef _Marine_Section_Wetted_Header
#define _Marine_Section_Wetted_Header

#include <Marine_xSection.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	namespace marineLib
	{

		class Section_Wetted
			: public Marine_xSection
		{

			/*Private Data*/

			Standard_Boolean IsDeep_;


			/*private functions and operators*/

			DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);


			auto& Change_IsDeep()
			{
				return IsDeep_;
			}

		protected:

			template<class... _Types>
			Section_Wetted(_Types&&... _Args)
				: Marine_xSection(_Args...)
			{}

		public:

			auto DeepCondition() const
			{
				return IsDeep_;
			}

			Standard_Boolean IsWetted() const override
			{
				return Standard_True;
			}

			void SetDeep(const Standard_Boolean deep)
			{
				IsDeep_ = deep;
			}

			TnbMarine_EXPORT std::vector<std::shared_ptr<Pln_Curve>>
				RetrieveCurvesOnWater() const;

			TnbMarine_EXPORT void RetrieveCurvesOnWaterTo
			(
				std::vector<std::shared_ptr<Pln_Curve>>& theCurves
			) const;

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
				return Marine_SectionType::wetted;
			}
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Section_Wetted);

#include <Marine_Section_Constructor.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::InnerSection<tnbLib::marineLib::Section_Wetted>);
BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Wetted>);

#endif // !_Marine_Section_Wetted_Header
