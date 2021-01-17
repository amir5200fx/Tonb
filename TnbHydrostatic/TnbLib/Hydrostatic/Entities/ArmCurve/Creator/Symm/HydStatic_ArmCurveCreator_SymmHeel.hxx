//#pragma once
//#ifndef _HydStatic_ArmCurveCreator_SymmHeel_Header
//#define _HydStatic_ArmCurveCreator_SymmHeel_Header
//
//#include <memory>
//
//namespace tnbLib
//{
//
//	namespace hydStcLib
//	{
//
//		template<class ArmCurve>
//		class ArmCurveCreator_SymmHeel
//			: public ArmCurve
//		{
//
//			/*Private Data*/
//
//		public:
//
//			template<class... _Types>
//			ArmCurveCreator_SymmHeel(_Types&&... _Args)
//				: ArmCurve(_Args...)
//			{}
//
//		};
//
//		template<class ArmCurve>
//		bool IsSymmHeel(const std::shared_ptr<ArmCurve>& theCurve)
//		{
//			return (bool)std::dynamic_pointer_cast<ArmCurveCreator_SymmHeel<ArmCurve>>(theCurve);
//		}
//	}
//}
//
//#endif // !_HydStatic_ArmCurveCreator_SymmHeel_Header
