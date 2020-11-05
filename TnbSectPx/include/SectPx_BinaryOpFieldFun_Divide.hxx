#pragma once
#ifndef _SectPx_BinaryOpFieldFun_Divide_Header
#define _SectPx_BinaryOpFieldFun_Divide_Header

#include <SectPx_BinaryOpFieldFun.hxx>

namespace tnbLib
{

	namespace binaryOpsFieldFun
	{

		template<class Memory1, class Memory2>
		class Divide
		{};

		template<>
		class Divide<std::shared_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
		{

			/*Private Data*/

			typedef SectPx_BinaryOpFieldFun_Memory
				<
				std::shared_ptr<SectPx_FieldFun>,
				std::shared_ptr<SectPx_FieldFun>
				> base;

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<base>(*this);
			}

		public:

			static const char* typeName_;

			template<class... _Types>
			Divide(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			Standard_Real Value() const override;
		};

		template<>
		class Divide<std::shared_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
		{

			/*Private Data*/


			typedef SectPx_BinaryOpFieldFun_Memory
				<
				std::shared_ptr<SectPx_FieldFun>,
				std::weak_ptr<SectPx_FieldFun>
				> base;

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<base>(*this);
			}

		public:

			static const char* typeName_;

			template<class... _Types>
			Divide(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			Standard_Real Value() const override;
		};

		template<>
		class Divide<std::weak_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
		{

			/*Private Data*/


			typedef SectPx_BinaryOpFieldFun_Memory
				<
				std::weak_ptr<SectPx_FieldFun>,
				std::shared_ptr<SectPx_FieldFun>
				> base;

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<base>(*this);
			}

		public:

			static const char* typeName_;

			template<class... _Types>
			Divide(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			Standard_Real Value() const override;
		};

		template<>
		class Divide<std::weak_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
		{

			/*Private Data*/


			typedef SectPx_BinaryOpFieldFun_Memory
				<
				std::weak_ptr<SectPx_FieldFun>,
				std::weak_ptr<SectPx_FieldFun>
				> base;

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<base>(*this);
			}

		public:

			static const char* typeName_;

			template<class... _Types>
			Divide(_Types&&... _Args)
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

#endif // !_SectPx_BinaryOpFieldFun_Divide_Header
