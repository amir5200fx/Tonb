#pragma once
#ifndef _HsVessel_Body_Header
#define _HsVessel_Body_Header

#include <HsVessel_Entity.hxx>

#include <gp_Ax2.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HsVessel_CmpSection;

	class HsVessel_Body
		: public HsVessel_Entity
	{

		/*Private Data*/

		gp_Ax2 theSystem_;

		std::vector<std::shared_ptr<HsVessel_CmpSection>> theSections_;


		auto& ChangeSections()
		{
			return theSections_;
		}

	public:

		HsVessel_Body();

		HsVessel_Body(const Standard_Integer theIndex);

		HsVessel_Body(const Standard_Integer theIndex, const word& theName);


		auto NbSections() const
		{
			return (Standard_Integer)theSections_.size();
		}

		const auto& Sections() const
		{
			return theSections_;
		}
	};
}

#endif // !_HsVessel_Body_Header
