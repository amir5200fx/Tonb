#pragma once
#ifndef _HsVessel_Section_Header
#define _HsVessel_Section_Header

#include <HsVessel_Entity.hxx>

#include <vector>

class gp_Ax2;

namespace tnbLib
{

	// Forward Declarations
	class Marine_Section;
	class Marine_CmpSection;
	class HsSection_Dry;
	class HsSection_WaterLine;
	class HsSection_UnderWater;

	class HsVessel_Section
		: public HsVessel_Entity
	{

		/*Private Data*/

		std::shared_ptr<Marine_CmpSection> theSection_;

	protected:

		HsVessel_Section();

		HsVessel_Section(const Standard_Integer theIndex);

		HsVessel_Section(const Standard_Integer theIndex, const word& theName);

	public:

		const gp_Ax2& System() const;

		const auto& CmpSection() const
		{
			return theSection_;
		}

		virtual Standard_Boolean IsTank() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSail() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsHull() const
		{
			return Standard_False;
		}

	};
}

#endif // !_HsVessel_Section_Header
