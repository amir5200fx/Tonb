#include <Aft3d_CoreBase.hxx>

#include <Geo3d_SizeFunction.hxx>
#include <Aft3d_OptNode_Calculator.hxx>
#include <Aft3d_MetricPrcsr.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft3d_CoreBase::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int file_version)
	{
		ar& boost::serialization::base_object<globalData>(*this);
		ar& boost::serialization::base_object<frontInfo>(*this);
		ar& boost::serialization::base_object<frontData>(*this);
		ar& boost::serialization::base_object<Aft_Core_BaseInfo>(*this);

		ar& theNodeCalculator_;
		ar& theMetricMap_;
	}

	template<>
	template<>
	void Aft3d_CoreBase::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int file_version)
	{
		ar& boost::serialization::base_object<globalData>(*this);
		ar& boost::serialization::base_object<frontInfo>(*this);
		ar& boost::serialization::base_object<frontData>(*this);
		ar& boost::serialization::base_object<Aft_Core_BaseInfo>(*this);

		ar& theNodeCalculator_;
		ar& theMetricMap_;
	}
}