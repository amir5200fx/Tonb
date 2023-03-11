#include <Mesh3d_tRegionVolume.hxx>

#include <Mesh3d_tShell.hxx>
#include <Cad_TModel.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh3d_tRegionVolume::serialize<TNB_iARCH_TYPE>
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
	void Mesh3d_tRegionVolume::serialize<TNB_oARCH_TYPE>
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