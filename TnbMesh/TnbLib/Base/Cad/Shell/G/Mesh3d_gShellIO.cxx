#include <Mesh3d_gShell.hxx>

#include <Mesh3d_gSurface.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh3d_gShell::serialize<TNB_iARCH_TYPE>
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
	void Mesh3d_gShell::serialize<TNB_oARCH_TYPE>
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