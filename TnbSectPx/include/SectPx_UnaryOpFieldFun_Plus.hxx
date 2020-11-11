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

			typedef SectPx_UnaryOpFieldFun_Memory<std::shared_ptr<SectPx_FieldFun>>
				base;

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<base>(*this);
			}

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

			typedef SectPx_UnaryOpFieldFun_Memory<std::weak_ptr<SectPx_FieldFun>>
				base;

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<base>(*this);
			}

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

BOOST_CLASS_EXPORT_KEY(tnbLib::unaryOpFieldFun::Plus<std::shared_ptr<tnbLib::SectPx_FieldFun>>);
BOOST_CLASS_EXPORT_KEY(tnbLib::unaryOpFieldFun::Plus<std::weak_ptr<tnbLib::SectPx_FieldFun>>);

#endif // !_SectPx_UnaryOpFieldFun_Plus_Header
