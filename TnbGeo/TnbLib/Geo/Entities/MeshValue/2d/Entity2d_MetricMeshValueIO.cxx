#include <Entity2d_MetricMeshValue.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Metric1.hxx>
#include <Entity2d_Triangulation.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Entity2d_MetricMeshValue::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			)
	{
		ar & theMesh_;
		ar & theValues_;
	}

	template<>
	template<>
	void Entity2d_MetricMeshValue::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & theMesh_;
		ar & theValues_;
	}
}