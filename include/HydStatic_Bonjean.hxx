#pragma once
#ifndef _HydStatic_Bonjean_Header
#define _HydStatic_Bonjean_Header

#include <Global_Done.hxx>
#include <HydStatic_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_Spacing;
	class HydStatic_BnjCurve;
	class Marine_CmpSection;
	class Marine_GraphCurve;
	class Marine_Graph;
	class Marine_Body;
	class Marine_Domain;
	class Marine_MultLevWaterDomain;

	struct HydStatic_Bonjean_Entity
	{

		/*Private Data*/

		std::shared_ptr<Marine_CmpSection> Section;
		std::shared_ptr<HydStatic_BnjCurve> Curve;


		//- default constructor for serializing

		HydStatic_Bonjean_Entity()
		{}

		//- constructor

		HydStatic_Bonjean_Entity
		(
			const std::shared_ptr<Marine_CmpSection>& theSection,
			const std::shared_ptr<HydStatic_BnjCurve>& theCurve
		)
			: Section(theSection)
			, Curve(theCurve)
		{}


		TNB_SERIALIZATION(TnbHydStatic_EXPORT);
	};

	class HydStatic_Bonjean
		: public Global_Done
	{

		typedef HydStatic_Bonjean_Entity entity;
		typedef std::vector<std::vector<Standard_Real>>
			tableOffset;

		/*Private Data*/

		std::shared_ptr<Marine_MultLevWaterDomain> theWaters_;

		std::vector<std::shared_ptr<entity>> theBonjean_;

		std::shared_ptr<Marine_Graph> theGraph_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);


		auto& ChangeBonjean()
		{
			return theBonjean_;
		}

		auto& ChangeGraph()
		{
			return theGraph_;
		}

	public:


		static TnbHydStatic_EXPORT unsigned short verbose;


		//- default constructor

		HydStatic_Bonjean()
		{}


		//- constructor

		TnbHydStatic_EXPORT HydStatic_Bonjean
		(
			const std::shared_ptr<Marine_MultLevWaterDomain>& theWaters
		);


		//- public functions and operators

		const auto& Waters() const
		{
			return theWaters_;
		}

		const auto& Bonjean() const
		{
			return theBonjean_;
		}

		const auto& Graph() const
		{
			return theGraph_;
		}

		TnbHydStatic_EXPORT void Perform();

		void LoadWaters
		(
			const std::shared_ptr<Marine_MultLevWaterDomain>& theWaters
		)
		{
			theWaters_ = theWaters;
		}
	};
}

#endif // !_HydStatic_Bonjean_Header
