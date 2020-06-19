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

			std::vector<std::shared_ptr<Pln_Curve>>
				RetrieveCurvesOnWater() const;

			void RetrieveCurvesOnWaterTo
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

#endif // !_Marine_Section_Wetted_Header
