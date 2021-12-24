#include <Aft2d_RegionPlaneAnIso.hxx>

#include <Cad2d_Plane.hxx>
#include <Aft2d_PlnWireAnIso.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Aft2d_RegionPlaneAnIso::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);

		ar & thePlane_;

		ar & theOuter_;
		ar & theInner_;
	}

	template<>
	template<>
	void Aft2d_RegionPlaneAnIso::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);

		ar & thePlane_;

		ar & theOuter_;
		ar & theInner_;
	}
}