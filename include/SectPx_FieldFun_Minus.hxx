#pragma once
#ifndef _SectPx_FieldFun_Minus_Header
#define _SectPx_FieldFun_Minus_Header

#include <SectPx_oneParFieldFun.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class FieldFun_Minus
			: public SectPx_oneParFieldFun
		{

			/*Private Data*/

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_oneParFieldFun>(*this);
			}

		public:

			static const char* typeName_;

			template<class... _Types>
			FieldFun_Minus(_Types&&... _Args)
				: SectPx_oneParFieldFun(_Args...)
			{}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::FieldFun_Minus);

#endif // !_SectPx_FieldFun_Minus_Header
