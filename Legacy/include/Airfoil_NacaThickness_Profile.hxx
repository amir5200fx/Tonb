#pragma once
#ifndef _Airfoil_NacaThickness_Profile_Header
#define _Airfoil_NacaThickness_Profile_Header

#include <Airfoil_NacaThickness.hxx>

namespace tnbLib
{

	// Forward Declarations [10/30/2022 Amir]
	class Airfoil_OffsetProfile;

	class Airfoil_NacaThickness_Profile
		: public Airfoil_NacaThickness
	{

		/*Private Data*/

	
		std::shared_ptr<Airfoil_OffsetProfile> theProfile_;

	public:

		// default constructor [10/30/2022 Amir]

		Airfoil_NacaThickness_Profile()
		{}

		// constructors [10/30/2022 Amir]

		Airfoil_NacaThickness_Profile(const Standard_Integer theIndex, const word& theName)
			: Airfoil_NacaThickness(theIndex, theName)
		{}

		// public functions and operators [10/30/2022 Amir]

		const auto& Profile() const
		{
			return theProfile_;
		}

		TnbAirfoil_EXPORT Standard_Real CalcYt(const Standard_Real xPerc) const override;

		void SetProfile(const std::shared_ptr<Airfoil_OffsetProfile>& theProfile)
		{
			theProfile_ = theProfile;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Airfoil_NacaThickness);

#endif // !_Airfoil_NacaThickness_Profile_Header
