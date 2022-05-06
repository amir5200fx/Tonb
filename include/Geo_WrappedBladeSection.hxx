#pragma once
#ifndef _Geo_WrappedBladeSection_Header
#define _Geo_WrappedBladeSection_Header

#include <Geo_BladeSection.hxx>

namespace tnbLib
{

	class Geo_WrappedBladeSection
		: public Geo_BladeSection
	{

		/*Private Data*/


		// private functions and operators [4/29/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Geo_BladeSection>(*this);
		}

	public:

		// default constructor [4/29/2022 Amir]

		Geo_WrappedBladeSection()
		{}


		// constructors [4/29/2022 Amir]

		Geo_WrappedBladeSection
		(
			const Geo3d_AirfoilBack& theBack,
			const Geo3d_AirfoilFace& theFace
		)
			: Geo_BladeSection(theBack, theFace)
		{}

		Geo_WrappedBladeSection
		(
			Geo3d_AirfoilBack&& theBack,
			Geo3d_AirfoilFace&& theFace
		)
			: Geo_BladeSection(std::move(theBack), std::move(theFace))
		{}


		// public functions and operators [4/29/2022 Amir]

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_WrappedBladeSection);

#endif // !_Geo_WrappedBladeSection_Header
