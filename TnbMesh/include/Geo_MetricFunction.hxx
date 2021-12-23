#pragma once
#ifndef _Geo_MetricFunction_Header
#define _Geo_MetricFunction_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Done.hxx>
#include <Global_Serialization.hxx>
#include <Entity_Box.hxx>
#include <Geo_MetricFunctionTraits.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<class Point>
	class Geo_MetricFunction
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
	{

		/*Private Data*/

		Entity_Box<Point> theBoundingBox_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
			ar & boost::serialization::base_object<Global_Done>(*this);
			ar & theBoundingBox_;
		}

	protected:


		// default constructor [11/24/2021 Amir]

		Geo_MetricFunction()
		{}


		// constructors [11/24/2021 Amir]

		Geo_MetricFunction
		(
			const Entity_Box<Point>& theBox
		)
			: theBoundingBox_(theBox)
		{}

		Geo_MetricFunction
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Entity_Box<Point>& theBox
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theBoundingBox_(theBox)
		{}

		// Protected functions and operators [11/24/2021 Amir]

		Entity_Box<Point>& ChangeBoundingBox()
		{
			return theBoundingBox_;
		}

	public:

		typedef Point ptType;
		typedef typename metric_type_from_point<Point>::metricType metricType;

		static TnbMesh_EXPORT const std::string extension;


		// Public functions and operators [11/24/2021 Amir]

		const Entity_Box<Point>& BoundingBox() const
		{
			return theBoundingBox_;
		}

		virtual metricType Value(const Point& theCoord) const = 0;

		virtual void Perform()
		{
			Change_IsDone() = Standard_True;
		}
	};
}

#include <Geo2d_MetricFunction.hxx>
#include <Geo3d_MetricFunction.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo2d_MetricFunction);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo3d_MetricFunction);

#endif // !_Geo_MetricFunction_Header