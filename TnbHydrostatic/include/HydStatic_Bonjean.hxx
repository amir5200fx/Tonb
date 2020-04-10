#pragma once
#ifndef _HydStatic_Bonjean_Header
#define _HydStatic_Bonjean_Header

#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_BnjCurve;
	class Marine_CmpSection;
	class Marine_GraphCurve;
	class Marine_Graph;
	class Marine_Body;
	class Marine_Domain;
	class Geo_xDistb;

	struct HydStatic_Bonjean_Entity
	{

		/*Private Data*/

		std::shared_ptr<Marine_CmpSection> Section;
		std::shared_ptr<HydStatic_BnjCurve> Curve;

		HydStatic_Bonjean_Entity
		(
			const std::shared_ptr<Marine_CmpSection>& theSection,
			const std::shared_ptr<HydStatic_BnjCurve>& theCurve
		)
			: Section(theSection)
			, Curve(theCurve)
		{}
	};

	class HydStatic_Bonjean
		: public Global_Done
	{

		typedef HydStatic_Bonjean_Entity entity;
		typedef std::vector<std::vector<Standard_Real>>
			tableOffset;

		/*Private Data*/

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<Marine_Body> theBody_;
		std::shared_ptr<Geo_xDistb> theWaters_;

		std::vector<std::shared_ptr<entity>> theBonjean_;

		std::shared_ptr<Marine_Graph> theGraph_;

		auto& ChangeBonjean()
		{
			return theBonjean_;
		}

		auto& ChangeGraph()
		{
			return theGraph_;
		}

	public:

		HydStatic_Bonjean();

		HydStatic_Bonjean
		(
			const std::shared_ptr<Marine_Domain>& theDomain, 
			const std::shared_ptr<Marine_Body>& theBody,
			const std::shared_ptr<Geo_xDistb>& theWaters
		);

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Body() const
		{
			return theBody_;
		}

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

		void Perform();

		void LoadDomain
		(
			const std::shared_ptr<Marine_Domain>& theDomain
		)
		{
			theDomain_ = theDomain;
		}

		void LoadBody
		(
			const std::shared_ptr<Marine_Body>& theBody
		)
		{
			theBody_ = theBody;
		}

		void LoadWaters
		(
			const std::shared_ptr<Geo_xDistb>& theWaters
		)
		{
			theWaters_ = theWaters;
		}
	};
}

#endif // !_HydStatic_Bonjean_Header
