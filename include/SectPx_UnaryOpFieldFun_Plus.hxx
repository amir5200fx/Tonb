#pragma once
#ifndef _SectPx_UnaryOpFieldFun_Plus_Header
#define _SectPx_UnaryOpFieldFun_Plus_Header

#include <SectPx_UnaryOpFieldFun.hxx>

namespace tnbLib
{

	namespace unaryOpFieldFun
	{

		template<class Memory>
		class Plus
		{};

		template<>
		class Plus<std::shared_ptr<SectPx_FieldFun>>
			: public SectPx_UnaryOpFieldFun_Memory<std::shared_ptr<SectPx_FieldFun>>
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			Plus(_Types&&... _Args)
				: SectPx_UnaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			Standard_Real Value() const override;
		};

		template<>
		class Plus<std::weak_ptr<SectPx_FieldFun>>
			: public SectPx_UnaryOpFieldFun_Memory<std::weak_ptr<SectPx_FieldFun>>
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			Plus(_Types&&... _Args)
				: SectPx_UnaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			Standard_Real Value() const override;
		};
	}
}

#endif // !_SectPx_UnaryOpFieldFun_Plus_Header
