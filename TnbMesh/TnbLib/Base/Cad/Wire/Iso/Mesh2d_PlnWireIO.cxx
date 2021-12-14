#include <Mesh2d_PlnWire.hxx>

#include <Mesh2d_PlnCurve.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh2d_PlnWire::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);

		ar & theCurves_;
	}

	template<>
	template<>
	void Mesh2d_PlnWire::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);

		ar & theCurves_;
	}
}