#pragma once
#ifndef _HydroStatic_Vessel_Header
#define _HydroStatic_Vessel_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>
#include <vector>
#include <map>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HsVessel_CmpSection;
	class HsVessel_Tank;
	class HsVessel_Body;
	class Marine_DryBody;
	class Marine_WettedBody;
	class Marine_SailBody;

	class HydroStatic_Vessel
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<HydroStatic_Vessel>
	{

		/*Private Data*/

		gp_Ax2 theSystem_;

		std::vector<std::shared_ptr<HsVessel_CmpSection>> theSections_;

		std::shared_ptr<HsVessel_CmpSection> theMidSection_;
		std::shared_ptr<HsVessel_CmpSection> theApSection_;
		std::shared_ptr<HsVessel_CmpSection> theFpSection_;

		std::shared_ptr<Marine_WettedBody> theWettedHull_;
		std::shared_ptr<Marine_DryBody> theDryHull_;

		std::shared_ptr<Marine_SailBody> theSail_;

		std::map<Standard_Integer, std::shared_ptr<HsVessel_Tank>>
			theTanks_;

	protected:

		HydroStatic_Vessel();

		HydroStatic_Vessel(const Standard_Integer theIndex);

		HydroStatic_Vessel(const Standard_Integer theIndex, const word& theName);

	public:

		virtual ~HydroStatic_Vessel()
		{}

		Standard_Integer CalcNbBodies() const;

		Standard_Boolean HasCompositeBody() const;

		Standard_Real FirstWaterLineSectionX() const;

		Standard_Real LastWaterLineSectionX() const;

		Standard_Real FirstUnderWaterSectionX() const;

		Standard_Real LastUnderWaterSectionX() const;

		Standard_Real FirstSectionX() const;

		Standard_Real LastSectionX() const;

		const auto& System() const
		{
			return theSystem_;
		}

		const auto& MidSection() const
		{
			return theMidSection_;
		}

		const auto& ApSection() const
		{
			return theApSection_;
		}

		const auto& FpSection() const
		{
			return theFpSection_;
		}

		const auto& Sections() const
		{
			return theSections_;
		}

		const std::shared_ptr<HsVessel_CmpSection>& FirstUnderWaterSection() const;

		const std::shared_ptr<HsVessel_CmpSection>& LastUnderWaterSection() const;

		const std::shared_ptr<HsVessel_CmpSection>& FirstMonoSection() const;

		const std::shared_ptr<HsVessel_CmpSection>& LastMonoSection() const;

		std::vector<std::shared_ptr<HsVessel_Body>> RetrieveWettedBodies() const;

	};
}

#endif // !_HydroStatic_Vessel_Header
