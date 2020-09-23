#pragma once
#ifndef _SectPx_FieldFun_Minus_Header
#define _SectPx_FieldFun_Minus_Header

#include <SectPx_oneParFieldFun.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class FieldFun_Minus
			: public SectPx_oneParFieldFun
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			FieldFun_Minus(_Types&&... _Args)
				: SectPx_oneParFieldFun(_Args...)
			{}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;
		};
	}
}

#endif // !_SectPx_FieldFun_Minus_Header
