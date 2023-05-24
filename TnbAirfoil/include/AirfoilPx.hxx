#pragma once
#ifndef _AirfoilPx_Header
#define _AirfoilPx_Header

#include <Airfoil_Module.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [4/26/2023 Payvand]

	class AirfoilPx_CamberProfile;
	class AirfoilPx_ThickProfile;
	class Pln_Curve;
	class Geo_xDistb;

	class AirfoilPx
		: public Global_Done
	{

		friend class AirfoilPx_CamberProfile;
		friend class AirfoilPx_ThickProfile;

		/*Private Data*/

		std::shared_ptr<AirfoilPx_CamberProfile> theCamber_;
		std::shared_ptr<AirfoilPx_ThickProfile> theThick_;

		std::shared_ptr<Geo_xDistb> theXs_;

		Standard_Real theLeadRadius_;

		// result profiles [4/26/2023 Payvand]

		std::shared_ptr<Pln_Curve> theUpperSurface_;
		std::shared_ptr<Pln_Curve> theLowerSurface_;


		void SmoothLeading(const Standard_Real theRadius);

	public:

		// default constructor [4/26/2023 Payvand]

		AirfoilPx()
			: theLeadRadius_(0.005)
		{}


		// Public functions and operators [4/26/2023 Payvand]

		const auto& CamberProfile() const
		{
			return theCamber_;
		}

		const auto& ThickProfile() const
		{
			return theThick_;
		}

		const auto& Xs() const
		{
			return theXs_;
		}

		const auto& UpperSurface() const
		{
			return theUpperSurface_;
		}

		const auto& LowerSurface() const
		{
			return theLowerSurface_;
		}

		const auto& LeadRadius() const
		{
			return theLeadRadius_;
		}

		TnbAirfoil_EXPORT void Perform();

		void SetCamberProfile(const std::shared_ptr<AirfoilPx_CamberProfile>& theProfile)
		{
			theCamber_ = theProfile;
		}

		void SetThickProfile(const std::shared_ptr<AirfoilPx_ThickProfile>& theProfile)
		{
			theThick_ = theProfile;
		}

		void SetXs(const std::shared_ptr<Geo_xDistb>& theXs)
		{
			theXs_ = theXs;
		}

		void SetLeadRadius(const Standard_Real theRadius)
		{
			theLeadRadius_ = theRadius;
		}

	};
}

#endif // !_AirfoilPx_Header
