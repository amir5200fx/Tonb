#pragma once
#ifndef _SectPx_UnaryOpFieldFun_Acos_Header
#define _SectPx_UnaryOpFieldFun_Acos_Header
#include <SectPx_UnaryOpFieldFun.hxx>
#include <cmath>

namespace tnbLib
{
    namespace unaryOpFieldFun
    {
        template<class Memory>
        class Acos
        {};

        template<>
        class Acos<std::shared_ptr<SectPx_FieldFun>>
            : public SectPx_UnaryOpFieldFun_Memory<std::shared_ptr<SectPx_FieldFun>>
        {
        public:
            typedef SectPx_UnaryOpFieldFun_Memory base;
        private:
            /*Private Data*/
            friend boost::serialization::access;
            template<class Archive>
            void serialize(Archive& ar, const unsigned int file_version)
            {
                ar& boost::serialization::base_object<base>(*this);
            }
        public:
            static const char* typeName_;
            // constructors
            template<class... _Types>
            Acos(_Types&&... _Args)
                : base(_Args...)
            {}
            // Public functions and operators
            word RegObjTypeName() const override;
            Standard_Real Value() const override;
        };

        template<>
        class Acos<std::weak_ptr<SectPx_FieldFun>>
            : public SectPx_UnaryOpFieldFun_Memory<std::weak_ptr<SectPx_FieldFun>>
        {
        public:
            typedef SectPx_UnaryOpFieldFun_Memory base;
        private:
            /*Private Data*/
            friend boost::serialization::access;
            template<class Archive>
            void serialize(Archive& ar, const unsigned int file_version)
            {
                ar& boost::serialization::base_object<base>(*this);
            }
        public:
            static const char* typeName_;
            // constructors
            template<class... _Types>
            Acos(_Types&&... _Args)
                : base(_Args...)
            {}
            // Public functions and operators
            word RegObjTypeName() const override;
            Standard_Real Value() const override;
        };
    }
}
BOOST_CLASS_EXPORT_KEY(tnbLib::unaryOpFieldFun::Acos<std::shared_ptr<tnbLib::SectPx_FieldFun>>);
BOOST_CLASS_EXPORT_KEY(tnbLib::unaryOpFieldFun::Acos<std::weak_ptr<tnbLib::SectPx_FieldFun>>);
#endif
