#pragma once
#ifndef _HsEntity_Section_Header
#define _HsEntity_Section_Header

#include <HsVessel_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Section;
	class HsSection_Dry;
	class HsSection_WaterLine;
	class HsSection_UnderWater;

	class HsEntity_Section
		: public HsVessel_Entity
	{

		/*Private Data*/

		std::shared_ptr<Marine_Section> theSection_;

		std::shared_ptr<HsSection_WaterLine> theWaterLineSection_;

		std::vector<std::shared_ptr<HsSection_Dry>> theDrySections_;
		std::vector<std::shared_ptr<HsSection_UnderWater>> theUnderWaterSections_;

	protected:

		HsEntity_Section();

		HsEntity_Section(const Standard_Integer theIndex);

		HsEntity_Section(const Standard_Integer theIndex, const word& theName);

	public:

		Standard_Boolean HasWettedArea() const;

		auto HasWaterLineSection() const
		{
			return (Standard_Boolean)theWaterLineSection_;
		}

		auto HasDrySection() const
		{
			return (Standard_Boolean)NbDrySections();
		}

		auto HasUnderWaterSection() const
		{
			return (Standard_Boolean)NbUnderWaterSections();
		}

		Standard_Integer NbDrySections() const
		{
			return (Standard_Integer)theDrySections_.size();
		}

		Standard_Integer NbUnderWaterSections() const
		{
			return (Standard_Integer)theUnderWaterSections_.size();
		}

		//- max beam on hull
		Standard_Real MaxBeam() const;

		Standard_Real BeamOnDeck() const;

		Standard_Real MaxWetBeam() const;

		Standard_Real Depth() const;

		Standard_Real Draft() const;

		Standard_Real WettedArea() const;

		Standard_Real X() const;

		const auto& Section() const
		{
			return theSection_;
		}
	};
}

#endif // !_HsEntity_Section_Header
