#pragma once
#ifndef _SectPx_BinaryOpFieldFun_Max_Header
#define _SectPx_BinaryOpFieldFun_Max_Header
#include <SectPx_BinaryOpFieldFun.hxx>
namespace tnbLib
{
	namespace binaryOpsFieldFun
	{
		template<class Memory1, class Memory2>
		class Max
		{};

		template<>
		class Max<std::shared_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory<std::shared_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>
		{
			/*Private Data*/
			typedef SectPx_BinaryOpFieldFun_Memory base;

			friend boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<base>(*this);
			}
		public:
			static TnbSectPx_EXPORT const char* typeName_;
			// constructors
			template<class... _Types>
			Max(_Types&&... _Args)
				: base(_Args...)
			{}
			// Public functions and operators
			TnbSectPx_EXPORT word RegObjTypeName() const override;
			TnbSectPx_EXPORT Standard_Real Value() const override;
		};

		template<>
		class Max<std::shared_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory<std::shared_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>
		{
			/*Private Data*/
			typedef SectPx_BinaryOpFieldFun_Memory base;

			friend boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<base>(*this);
			}
		public:
			static TnbSectPx_EXPORT const char* typeName_;
			// constructors
			template<class... _Types>
			Max(_Types&&... _Args)
				: base(_Args...)
			{}
			// Public functions and operators
			TnbSectPx_EXPORT word RegObjTypeName() const override;
			TnbSectPx_EXPORT Standard_Real Value() const override;
		};

		template<>
		class Max<std::weak_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory<std::weak_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>
		{
			/*Private Data*/
			typedef SectPx_BinaryOpFieldFun_Memory base;

			friend boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<base>(*this);
			}
		public:
			static TnbSectPx_EXPORT const char* typeName_;
			// constructors
			template<class... _Types>
			Max(_Types&&... _Args)
				: base(_Args...)
			{}
			// Public functions and operators
			TnbSectPx_EXPORT word RegObjTypeName() const override;
			TnbSectPx_EXPORT Standard_Real Value() const override;
		};

		template<>
		class Max<std::weak_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>
			: public SectPx_BinaryOpFieldFun_Memory<std::weak_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>
		{
			/*Private Data*/
			typedef SectPx_BinaryOpFieldFun_Memory base;

			friend boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<base>(*this);
			}
		public:
			static TnbSectPx_EXPORT const char* typeName_;
			// constructors
			template<class... _Types>
			Max(_Types&&... _Args)
				: base(_Args...)
			{}
			// Public functions and operators
			TnbSectPx_EXPORT word RegObjTypeName() const override;
			TnbSectPx_EXPORT Standard_Real Value() const override;
		};

		typedef Max<std::shared_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>> Max_SF_SF;
		typedef Max<std::shared_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>> Max_SF_WF;
		typedef Max<std::weak_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>> Max_WF_SF;
		typedef Max<std::weak_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>> Max_WF_WF;
	}
}
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Max_SF_SF);
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Max_WF_SF);
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Max_SF_WF);
BOOST_CLASS_EXPORT_KEY(tnbLib::binaryOpsFieldFun::Max_WF_WF);
#endif