#pragma once
#ifndef _SectPx_UnaryOpFieldFun_Minus_Header
#define _SectPx_UnaryOpFieldFun_Minus_Header

#include <SectPx_UnaryOpFieldFun.hxx>

namespace tnbLib
{

	namespace unaryOpFieldFun
	{

		template<class Memory>
		class Minus
		{};

		template<>
		class Minus<std::shared_ptr<SectPx_FieldFun>>
			: public SectPx_UnaryOpFieldFun_Memory<std::shared_ptr<SectPx_FieldFun>>
		{

			/*Private Data*/

			typedef SectPx_UnaryOpFieldFun_Memory<std::shared_ptr<SectPx_FieldFun>>
				base;

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<base>(*this);
			}

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			template<class... _Types>
			Minus(_Types&&... _Args)
				: SectPx_UnaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
		};

		template<>
		class Minus<std::weak_ptr<SectPx_FieldFun>>
			: public SectPx_UnaryOpFieldFun_Memory<std::weak_ptr<SectPx_FieldFun>>
		{

			/*Private Data*/

			typedef SectPx_UnaryOpFieldFun_Memory<std::weak_ptr<SectPx_FieldFun>>
				base;

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<base>(*this);
			}

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			template<class... _Types>
			Minus(_Types&&... _Args)
				: SectPx_UnaryOpFieldFun_Memory(_Args...)
			{}

			word RegObjTypeName() const override
			{
				return typeName_;
			}

			TnbSectPx_EXPORT Standard_Real Value() const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::unaryOpFieldFun::Minus<std::shared_ptr<tnbLib::SectPx_FieldFun>>);
BOOST_CLASS_EXPORT_KEY(tnbLib::unaryOpFieldFun::Minus<std::weak_ptr<tnbLib::SectPx_FieldFun>>);

#endif // !_SectPx_UnaryOpFieldFun_Minus_Header
