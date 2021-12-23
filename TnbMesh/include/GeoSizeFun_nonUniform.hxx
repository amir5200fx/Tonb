#pragma once
#ifndef _GeoSizeFun_nonUniform_Header
#define _GeoSizeFun_nonUniform_Header

#include <Geo_SizeFunction.hxx>

namespace tnbLib
{

	template<class Point>
	class GeoSizeFun_nonUniform
		: public Geo_SizeFunction<Point>
	{

		/*Private Data*/


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Geo_SizeFunction<Point>>(*this);
		}


	protected:

		// default constructor [7/17/2021 Amir]

		GeoSizeFun_nonUniform()
		{}


		// constructors [7/17/2021 Amir]

		GeoSizeFun_nonUniform
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Geo_SizeFunction<Point>(theIndex, theName)
		{}

		GeoSizeFun_nonUniform
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Entity_Box<Point>& theBoundingBox
		)
			: Geo_SizeFunction<Point>(theIndex, theName, theBoundingBox)
		{}

	public:

		//- public functions and operators

	};
}

#include <GeoSizeFun2d_nonUniform.hxx>
#include <GeoSizeFun3d_nonUniform.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoSizeFun2d_nonUniform);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoSizeFun3d_nonUniform);

#endif // !_GeoSizeFun_nonUniform_Header
