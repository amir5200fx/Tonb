#include <HydStatic_rArmCurve_Hlds.hxx>

#include <HydStatic_ArmCurve.hxx>

namespace tnbLib
{
	namespace hydStcLib
	{

		template<>
		template<>
		void rArmCurve_Cmpt<rArmCurve_Hlds>::serialize<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				const unsigned int /*file_version*/
				)
		{
			ar & boost::serialization::base_object<HydStatic_Entity>(*this);
			ar & theCurves_;
		}

		template<>
		template<>
		void rArmCurve_Cmpt<rArmCurve_Hlds>::serialize<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const unsigned int /*file_version*/
				)
		{
			ar & boost::serialization::base_object<HydStatic_Entity>(*this);
			ar & theCurves_;
		}
	}
}