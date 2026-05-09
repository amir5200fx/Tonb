#include <PtdModel3d_Curve.hxx>

#include <OpenCascade_Serialization.hxx>

#include <Geom_Curve.hxx>

namespace tnbLib
{

	template<>
	template<>
	void tnbLib::PtdModel3d_Curve::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar & theGeometry_;
	}

	template<>
	template<>
	void tnbLib::PtdModel3d_Curve::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar & theGeometry_;
	}
}