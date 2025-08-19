#pragma once
#ifndef _Geo_AirfoilFace_Header
#define _Geo_AirfoilFace_Header

#include <Geo_AirfoilSurface.hxx>

namespace tnbLib
{

	template<class Point>
	class Geo_AirfoilFace
		: public Geo_AirfoilSurface<Point>
	{

		/*Private functions*/


		// private functions and operators [4/28/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Geo_AirfoilSurface<Point>>(*this);
		}

	public:

		// default constructor [4/28/2022 Amir]

		Geo_AirfoilFace()
		{}


		// constructors [4/28/2022 Amir]

		explicit Geo_AirfoilFace(const std::vector<Point>& theOffsets)
			: Geo_AirfoilSurface(theOffsets)
		{}

		Geo_AirfoilFace(std::vector<Point>&& theOffsets)
			: Geo_AirfoilSurface(std::move(theOffsets))
		{}


		// public functions and operators [4/28/2022 Amir]


	};
}

#include <Geo2d_AirfoilFace.hxx>
#include <Geo3d_AirfoilFace.hxx>

#endif // !_Geo_AirfoilFace_Header
