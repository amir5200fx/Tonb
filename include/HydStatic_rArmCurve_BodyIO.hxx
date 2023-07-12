#pragma once
#include <HydStatic_rArmCurve_Cmpt.hxx>

namespace tnbLib
{
	namespace hydStcLib
	{

		template<>
		template<>
		inline void rArmCurve_Cmpt<rArmCurve_Body>::serialize<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				const unsigned int file_version
				)
		{
			NotImplemented;
		}

		template<>
		template<>
		inline void rArmCurve_Cmpt<rArmCurve_Body>::serialize<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const unsigned int file_version
				)
		{
			NotImplemented;
		}
	}
}
