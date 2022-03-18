#include <Aft2d_gModelSurfaceUniMetric.hxx>

#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <Entity2d_Triangulation.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_gModelSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & boost::serialization::base_object<cache>(*this);
		ar & boost::serialization::base_object<Aft_Model_Constants>(*this);

		ar & theBoundaryMap_;
		ar & theBoundaryEntity_;
		ar & theTriangulation_;
	}

	template<>
	template<>
	void Aft2d_gModelSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & boost::serialization::base_object<cache>(*this);
		ar & boost::serialization::base_object<Aft_Model_Constants>(*this);

		ar & theBoundaryMap_;
		ar & theBoundaryEntity_;
		ar & theTriangulation_;
	}
}