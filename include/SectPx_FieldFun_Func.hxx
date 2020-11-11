//#pragma once
//#ifndef _SectPx_FieldFun_Func_Header
//#define _SectPx_FieldFun_Func_Header
//
//#include <SectPx_oneParFieldFun.hxx>
//
//namespace tnbLib
//{
//
//	namespace sectPxLib
//	{
//
//		class FieldFun_Func
//			: public SectPx_oneParFieldFun
//		{
//
//			/*Private Data*/
//
//			double(*theFun_)(double);
//
//			Standard_Real xValue(const Standard_Real x) const
//			{
//				Debug_Null_Pointer(theFun_);
//				return (Standard_Real)theFun_((double)x);
//			}
//
//
//			friend boost::serialization::access;
//
//			template<class Archive>
//			void serialize(Archive &ar, const unsigned int file_version)
//			{
//				ar & boost::serialization::base_object<SectPx_oneParFieldFun>(*this);
//				ar & theFun_;
//			}
//
//		public:
//
//			static const char* typeName_;
//
//			template<class... _Types>
//			FieldFun_Func(_Types&&... _Args)
//				: SectPx_oneParFieldFun(_Args...)
//			{}
//
//			word RegObjTypeName() const override;
//
//			Standard_Real Value() const override;
//
//			void SetFunc(double(*theFun)(double))
//			{
//				theFun_ = theFun;
//			}
//		};
//	}
//}
//
//BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::FieldFun_Func);
//
//#endif // !_SectPx_FieldFun_Func_Header
