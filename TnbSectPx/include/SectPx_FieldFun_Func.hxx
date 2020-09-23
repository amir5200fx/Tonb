#pragma once
#ifndef _SectPx_FieldFun_Func_Header
#define _SectPx_FieldFun_Func_Header

#include <SectPx_oneParFieldFun.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class FieldFun_Func
			: public SectPx_oneParFieldFun
		{

			/*Private Data*/

			double(*theFun_)(double);

			Standard_Real xValue(const Standard_Real x) const
			{
				Debug_Null_Pointer(theFun_);
				return (Standard_Real)theFun_((double)x);
			}

		public:

			static const char* typeName_;

			template<class... _Types>
			FieldFun_Func(_Types&&... _Args)
				: SectPx_oneParFieldFun(_Args...)
			{}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;

			void SetFunc(double(*theFun)(double))
			{
				theFun_ = theFun;
			}
		};
	}
}

#endif // !_SectPx_FieldFun_Func_Header
