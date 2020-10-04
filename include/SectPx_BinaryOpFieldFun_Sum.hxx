#pragma once
#ifndef _SectPx_BinaryOpFieldFun_Sum_Header
#define _SectPx_BinaryOpFieldFun_Sum_Header

#include <SectPx_BinaryOpFieldFun.hxx>

namespace tnbLib
{

	namespace binaryOpsFieldFun
	{

		template<class Memory1, class Memory2>
		class Sum
		{};

		template<>
		class Sum<std::shared_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory
			<
			std::shared_ptr<SectPx_FieldFun>, 
			std::shared_ptr<SectPx_FieldFun>
			>
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			Sum(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			Standard_Real Value() const override;
		};

		template<>
		class Sum<std::shared_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory
			<
			std::shared_ptr<SectPx_FieldFun>, 
			std::weak_ptr<SectPx_FieldFun>
			>
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			Sum(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			Standard_Real Value() const override;
		};

		template<>
		class Sum<std::weak_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			Sum(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			Standard_Real Value() const override;
		};

		template<>
		class Sum<std::weak_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			Sum(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			Standard_Real Value() const override;
		};
	}
}

#endif // !_SectPx_BinaryOpFieldFun_Sum_Header
