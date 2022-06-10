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
			Sum(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
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
			Sum(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
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
			Sum(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
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
			Sum(_Types&&... _Args)
				: SectPx_BinaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
		};


		typedef Sum<std::shared_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>> Sum_SF_SF;
		typedef Sum<std::shared_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>> Sum_SF_WF;
		typedef Sum<std::weak_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>> Sum_WF_SF;
		typedef Sum<std::weak_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>> Sum_WF_WF;

	}
}


BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Sum_SF_SF);
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Sum_WF_SF);
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Sum_SF_WF);
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Sum_WF_WF);

#endif // !_SectPx_BinaryOpFieldFun_Sum_Header
