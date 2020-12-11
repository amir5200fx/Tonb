#pragma once
#ifndef _HydStatic_ArmCurveCreator_ArbtHeel_Header
#define _HydStatic_ArmCurveCreator_ArbtHeel_Header

#include <memory>

namespace tnbLib
{

	namespace hydStcLib
	{

		template<class ArmCurve>
		class ArmCurveCreator_ArbtHeel
			: public ArmCurve
		{

			/*Private Data*/

		public:

			template<class... _Types>
			ArmCurveCreator_ArbtHeel(_Types&&... _Args)
				: ArmCurve(_Args...)
			{}

		};

		template<class ArmCurve>
		bool IsArbtHeel(const std::shared_ptr<ArmCurve>& theCurve)
		{
			return (bool)std::dynamic_pointer_cast<ArmCurveCreator_ArbtHeel<ArmCurve>>(theCurve);
		}
	}
}

#endif // !_HydStatic_ArmCurveCreator_ArbtHeel_Header
