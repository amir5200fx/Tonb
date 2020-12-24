#pragma once
#ifndef _Marine_BooleanOps_Header
#define _Marine_BooleanOps_Header

#include <Marine_CmpSectionType.hxx>
#include <Marine_SectionsFwd.hxx>
#include <Marine_Module.hxx>

#include <memory>
#include <vector>

class gp_Ax2;

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_Section;
	class Pln_Wire;

	class Marine_BooleanOps
	{

	public:

		static TnbMarine_EXPORT std::shared_ptr<Marine_Section> 
			Union
			(
				const std::shared_ptr<Marine_Section>& theSect0, 
				const std::shared_ptr<Marine_Section>& theSect1
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>> 
			Subtract
			(
				const std::shared_ptr<Marine_Section>& theSect0, 
				const std::shared_ptr<Marine_Section>& theSect1
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>> 
			Intersection
			(
				const std::shared_ptr<Marine_Section>& theSect0,
				const std::shared_ptr<Marine_Section>& theSect1
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			WettedSection
			(
				const std::shared_ptr<Pln_Wire>& theSection,
				const std::shared_ptr<Pln_Wire>& theWater
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			WettedSection
			(
				const std::shared_ptr<marineLib::Section_Displacer>& theSection,
				const std::shared_ptr<Marine_Section>& theWater
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			WettedSection
			(
				const std::shared_ptr<marineLib::Section_Tank>& theSection,
				const std::shared_ptr<Marine_Section>& theWater
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_CmpSection>
			WettedSection
			(
				const std::shared_ptr<Marine_CmpSection>& theSection,
				const std::shared_ptr<Marine_Section>& theWater
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			DrySection
			(
				const std::shared_ptr<Pln_Wire>& theSection,
				const std::shared_ptr<Pln_Wire>& theWater
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			DrySection
			(
				const std::shared_ptr<marineLib::Section_Displacer>& theSection,
				const std::shared_ptr<Marine_Section>& theWater
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			DrySection
			(
				const std::shared_ptr<marineLib::Section_Tank>& theSection,
				const std::shared_ptr<Marine_Section>& theWater
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_CmpSection>
			DrySection
			(
				const std::shared_ptr<Marine_CmpSection>& theSection,
				const std::shared_ptr<Marine_Section>& theWater
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_CmpSection>>
			WettedSections
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const std::vector<std::shared_ptr<Marine_Section>>& theWaterSections
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_CmpSection>>
			DrySections
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const std::vector<std::shared_ptr<Marine_Section>>& theWaterSections
			);


	};
}

#endif // !_Marine_BooleanOps_Header
