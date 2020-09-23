#pragma once
#ifndef _SectPx_UnaryOpFieldFun_Plus_Header
#define _SectPx_UnaryOpFieldFun_Plus_Header

#include <SectPx_UnaryOpFieldFun.hxx>

namespace tnbLib
{

	namespace unaryOpFieldFun
	{

		class Plus
			: public SectPx_UnaryOpFieldFun
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			Plus(_Types&&... _Args)
				: SectPx_UnaryOpFieldFun(_Args...)
			{}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;
		};
	}
}

#endif // !_SectPx_UnaryOpFieldFun_Plus_Header
