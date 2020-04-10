#pragma once
#ifndef _HsVessel_CmpSection_Header
#define _HsVessel_CmpSection_Header

#include <HsVessel_Entity.hxx>
#include <Standard_Handle.hxx>

#include <memory>
#include <vector>

class gp_Ax2;
class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class HsVessel_Section;
	class HsVessel_MonoSection;
	class Marine_CmpSection;
	class Marine_Body;

	class HsVessel_CmpSection
		: public HsVessel_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<HsVessel_Section>> theSections_;

	public:

		HsVessel_CmpSection();

		HsVessel_CmpSection(const Standard_Integer theIndex);

		HsVessel_CmpSection(const Standard_Integer theIndex, const word& theName);

		const gp_Ax2& System() const;

		std::vector<std::shared_ptr<HsVessel_Section>> 
			RetrieveWLineSections() const;

		auto NbSections() const
		{
			return (Standard_Integer)theSections_.size();
		}

		const auto& Sections() const
		{
			return theSections_;
		}

		//- max beam on hull
		Standard_Real MaxBeam() const;

		Standard_Real BeamOnDeck() const;

		Standard_Real MaxWetBeam() const;

		Standard_Real Depth() const;

		Standard_Real Draft() const;

		Standard_Real WettedArea() const;

		Standard_Real X() const;

		virtual Standard_Boolean IsMono() const
		{
			return Standard_False;
		}

	};
}

#endif // !_HsVessel_CmpSection_Header
