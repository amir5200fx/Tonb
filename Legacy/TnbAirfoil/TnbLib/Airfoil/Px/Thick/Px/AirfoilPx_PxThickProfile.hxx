#pragma once
#ifndef _AirfoilPx_PxThickProfile_Header
#define _AirfoilPx_PxThickProfile_Header

#include <AirfoilPx_ThickProfile.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [4/25/2023 Payvand]

	class Pln_Curve;

	class AirfoilPx_PxThickProfile
		: public AirfoilPx_ThickProfile
		, public Global_Done
	{

		/*Private Data*/

		
		// Private functions and operators [4/26/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<AirfoilPx_ThickProfile>(*this);
			ar& boost::serialization::base_object<Global_Done>(*this);
		}

	protected:

		// default constructor [4/25/2023 Payvand]

		AirfoilPx_PxThickProfile()
		{}


		// constructors [4/25/2023 Payvand]


	public:

		// Public functions and operators [4/25/2023 Payvand]


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::AirfoilPx_PxThickProfile);

#endif // !_AirfoilPx_PxThickProfile_Header
