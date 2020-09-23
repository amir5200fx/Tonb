#pragma once
#ifndef _SectPx_FieldFun_Uni_Header
#define _SectPx_FieldFun_Uni_Header

#include <SectPx_oneParFieldFun.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class FieldFun_Uni
			: public SectPx_oneParFieldFun
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			FieldFun_Uni(_Types&&... _Args)
				: SectPx_oneParFieldFun(_Args...)
			{}


			Standard_Real Value() const override;

			word RegObjTypeName() const override;
		};
	}
}

#endif // !_SectPx_FieldFun_Uni_Header
