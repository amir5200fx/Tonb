#include <Aft2d_CoreBaseAnIso.hxx>

#include <Aft2d_OptNodeAnIso_Calculator.hxx>
#include <Aft2d_MetricPrcsrAnIso.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_Transient.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_CoreBaseAnIso::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & boost::serialization::base_object<globalData>(*this);
		ar & boost::serialization::base_object<frontInfo>(*this);
		ar & boost::serialization::base_object<frontData>(*this);
		ar & boost::serialization::base_object<Aft_Core_BaseInfo>(*this);

		ar & theNodeCalculator_;
		ar & theMetricMap_;
	}

	template<>
	template<>
	void Aft2d_CoreBaseAnIso::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & boost::serialization::base_object<globalData>(*this);
		ar & boost::serialization::base_object<frontInfo>(*this);
		ar & boost::serialization::base_object<frontData>(*this);
		ar & boost::serialization::base_object<Aft_Core_BaseInfo>(*this);

		ar & theNodeCalculator_;
		ar & theMetricMap_;
	}
}