#pragma once
#ifndef _SectPx_BinaryOpFieldFun_Sum_Header
#define _SectPx_BinaryOpFieldFun_Sum_Header

#include <SectPx_BinaryOpFieldFun.hxx>

namespace tnbLib
{

	namespace binaryOpsFieldFun
	{

		class Sum
			: public SectPx_BinaryOpFieldFun
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			Sum(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun(_Args...)
			{}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;
		};
	}
}

#endif // !_SectPx_BinaryOpFieldFun_Sum_Header
