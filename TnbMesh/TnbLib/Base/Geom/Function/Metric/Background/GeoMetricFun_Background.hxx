#pragma once
#ifndef _GeoMetricFun_Background_Header
#define _GeoMetricFun_Background_Header

#include <GeoMetricFun_nonUniform.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

namespace tnbLib
{

	template<class BackMeshData>
	class GeoMetricFun_Background
		: public GeoMetricFun_nonUniform<typename BackMeshData::Point>
	{

		typedef typename BackMeshData::Point Point;

		/*Private Data*/

		std::shared_ptr<BackMeshData> theBackMesh_;


		//- private functions and operators

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << "this function is not supposed to be called" << endl;
			NotImplemented;
		}

	protected:

		//- default constructor for serialization purposes only!

		GeoMetricFun_Background()
		{}

	public:

		typedef Point ptType;
		typedef typename metric_type_from_point<Point>::metricType metricType;


		//- constructors

		GeoMetricFun_Background
		(
			const std::shared_ptr<BackMeshData>& theBackMesh
		)
			: theBackMesh_(theBackMesh)
		{}

		GeoMetricFun_Background
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<BackMeshData>& theBackMesh
		);



		//- public functions and operators

		const std::shared_ptr<BackMeshData>& BackMesh() const
		{
			return theBackMesh_;
		}


		//- override functions and operators

		metricType Value(const Point& theCoord) const override;
	};
}

#include <GeoMetricFun_BackgroundI.hxx>

#endif // !_GeoMetricFun_Background_Header