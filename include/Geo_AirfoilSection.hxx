#pragma once
#ifndef _Geo_AirfoilSection_Header
#define _Geo_AirfoilSection_Header

#include <Geo_AirfoilSurface.hxx>

namespace tnbLib
{

	template<class Point>
	class Geo_AirfoilSection
	{

		/*Private Data*/

		Geo_AirfoilFace<Point> theFace_;
		Geo_AirfoilBack<Point> theBack_;


		// private functions and operators [4/29/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theFace_;
			ar & theBack_;
		}

	public:

		// default constructor [4/29/2022 Amir]

		Geo_AirfoilSection()
		{}


		// constructors [4/29/2022 Amir]

		Geo_AirfoilSection
		(
			const Geo_AirfoilBack<Point>& theBack,
			const Geo_AirfoilFace<Point>& theFace
		)
			: theBack_(theBack)
			, theFace_(theFace)
		{}

		Geo_AirfoilSection
		(
			Geo_AirfoilBack<Point>&& theBack,
			Geo_AirfoilFace<Point>&& theFace
		)
			: theBack_(std::move(theBack))
			, theFace_(std::move(theFace))
		{}


		// public functions and operators [4/29/2022 Amir]

		const auto& FaceOffsets() const
		{
			return theFace_;
		}

		auto& FaceOffsetsRef()
		{
			return theFace_;
		}

		const auto& BackOffsets() const
		{
			return theBack_;
		}

		auto& BackOffsetsRef()
		{
			return theBack_;
		}

		void SetFace(const Geo_AirfoilFace<Point>& theOffsets)
		{
			theFace_ = theOffsets;
		}

		void SetFace(Geo_AirfoilFace<Point>&& theOffsets)
		{
			theFace_ = std::move(theOffsets);
		}

		void SetBack(const Geo_AirfoilBack<Point>& theOffsets)
		{
			theBack_ = theOffsets;
		}

		void SetBack(Geo_AirfoilBack<Point>&& theOffsets)
		{
			theBack_ = std::move(theOffsets);
		}
	};
}

#include <Geo2d_AirfoilSection.hxx>
#include <Geo3d_AirfoilSection.hxx>

#endif // !_Geo_AirfoilSection_Header
