#include <GeoMesh3d_Data.hxx>

namespace tnbLib
{

	template<>
	template<>
	void GeoMesh3d_Data::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			)
	{
		ar & theElements_;
	}

	template<>
	template<>
	void GeoMesh3d_Data::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			)
	{
		ar & theElements_;
	}
}