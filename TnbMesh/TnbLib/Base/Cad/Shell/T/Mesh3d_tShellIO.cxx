#include <Mesh3d_tShell.hxx>

#include <Mesh3d_tSurface.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh3d_tShell::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<Global_Indexed>(*this);
		ar& boost::serialization::base_object<Global_Named>(*this);
		ar& theSurfaces_;
	}

	template<>
	template<>
	void Mesh3d_tShell::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<Global_Indexed>(*this);
		ar& boost::serialization::base_object<Global_Named>(*this);
		ar& theSurfaces_;
	}
}