#include <Mesh3d_gRegionVolume.hxx>

#include <Mesh3d_gShell.hxx>
#include <Cad_GModel.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh3d_gRegionVolume::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<Global_Indexed>(*this);
		ar& boost::serialization::base_object<Global_Named>(*this);

		ar& theSolid_;
		ar& theOuter_;
		ar& theInners_;
	}

	template<>
	template<>
	void Mesh3d_gRegionVolume::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<Global_Indexed>(*this);
		ar& boost::serialization::base_object<Global_Named>(*this);

		ar& theSolid_;
		ar& theOuter_;
		ar& theInners_;
	}
}