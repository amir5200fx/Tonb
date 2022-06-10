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

			static TnbSectPx_EXPORT const char* typeName_;

			template<class... _Types>
			Divide(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
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

			static TnbSectPx_EXPORT const char* typeName_;

			template<class... _Types>
			Divide(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
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

			static TnbSectPx_EXPORT const char* typeName_;

			template<class... _Types>
			Divide(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
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

			static TnbSectPx_EXPORT const char* typeName_;

			template<class... _Types>
			Divide(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
		};

		typedef Divide<std::shared_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>> Divide_SF_SF;
		typedef Divide<std::shared_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>> Divide_SF_WF;
		typedef Divide<std::weak_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>> Divide_WF_SF;
		typedef Divide<std::weak_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>> Divide_WF_WF;
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Divide_SF_SF);
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Divide_WF_SF);
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Divide_SF_WF);
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Divide_WF_WF);

#endif // !_SectPx_BinaryOpFieldFun_Divide_Header
