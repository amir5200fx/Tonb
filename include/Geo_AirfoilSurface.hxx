#pragma once
#ifndef _Geo_AirfoilSurface_Header
#define _Geo_AirfoilSurface_Header

#include <Global_Serialization.hxx>

#include <vector>

namespace tnbLib
{

	template<class Point>
	class Geo_AirfoilSurface
	{

		/*Private Data*/

		std::vector<Point> theOffsets_;


		// private functions and operators [4/28/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theOffsets_;
		}

	protected:

		// default constructor [4/28/2022 Amir]

		Geo_AirfoilSurface()
		{}


		// constructors [4/28/2022 Amir]

		explicit Geo_AirfoilSurface(const std::vector<Point>& theOffsets)
			: theOffsets_(theOffsets)
		{}

		Geo_AirfoilSurface(std::vector<Point>&& theOffsets)
			: theOffsets_(std::move(theOffsets))
		{}

	public:


		// public functions and operators [4/28/2022 Amir]

		const auto& Offsets() const
		{
			return theOffsets_;
		}

		auto& OffsetsRef()
		{
			return theOffsets_;
		}

		void SetOffsets(const std::vector<Point>& theOffsets)
		{
			theOffsets_ = theOffsets;
		}

		void SetOffsets(std::vector<Point>&& theOffsets)
		{
			theOffsets_ = std::move(theOffsets);
		}
	};
}

#include <Geo_AirfoilBack.hxx>
#include <Geo_AirfoilFace.hxx>

#endif // !_Geo_AirfoilSurface_Header
