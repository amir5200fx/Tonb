#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>

#include <Mesh_Curve_Info.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_BoundaryOfPlaneAnIso_Info::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Aft_BoundaryOfPlane_Info_Base>(*this);

		ar & theMergeTolerance_;

		ar & theGlobalCurve_;
		ar & theGlobalMetricPrcsr_;

		ar & OverrideInfo_;
	}

	template<>
	template<>
	void Aft2d_BoundaryOfPlaneAnIso_Info::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Aft_BoundaryOfPlane_Info_Base>(*this);

		ar & theMergeTolerance_;

		ar & theGlobalCurve_;
		ar & theGlobalMetricPrcsr_;

		ar & OverrideInfo_;
	}
}