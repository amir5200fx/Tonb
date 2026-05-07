#include <Mesh3d_gSurface.hxx>

#include <GModel_Surface.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Triangulation.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh3d_gSurface::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<Global_Indexed>(*this);
		ar& theParaTriangulation_;
		ar& theTriangulation_;
	}

	template<>
	template<>
	void Mesh3d_gSurface::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<Global_Indexed>(*this);
		ar& theParaTriangulation_;
		ar& theTriangulation_;
	}
}