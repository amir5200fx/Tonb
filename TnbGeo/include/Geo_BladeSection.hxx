#pragma once
#ifndef _Geo_BladeSection_Header
#define _Geo_BladeSection_Header

#include <Geo_AirfoilSection.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class Geo_BladeSection
		: public Geo3d_AirfoilSection
	{

		/*Private Data*/



		// private functions and operators [4/29/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Geo3d_AirfoilSection>(*this);
		}

	protected:

		// default constructor [4/29/2022 Amir]

		Geo_BladeSection()
		{}


		// constructors [4/29/2022 Amir]

		Geo_BladeSection
		(
			const Geo3d_AirfoilBack& theBack,
			const Geo3d_AirfoilFace& theFace
		)
			: Geo3d_AirfoilSection(theBack, theFace)
		{}

		Geo_BladeSection
		(
			Geo3d_AirfoilBack&& theBack,
			Geo3d_AirfoilFace&& theFace
		)
			: Geo3d_AirfoilSection(std::move(theBack), std::move(theFace))
		{}

	public:

		// public functions and operators [4/29/2022 Amir]

		virtual ~Geo_BladeSection()
		{}


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo_BladeSection);

#endif // !_Geo_BladeSection_Header
