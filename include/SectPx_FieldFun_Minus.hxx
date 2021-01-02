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

			static TnbSectPx_EXPORT const char* typeName_;

			FieldFun_Minus()
			{}

			FieldFun_Minus
			(
				const Standard_Integer theIndex
			)
				: SectPx_oneParFieldFun(theIndex)
			{}

			FieldFun_Minus
			(
				const Standard_Integer theIndex,
				const word& theName
			)
				: SectPx_oneParFieldFun(theIndex, theName)
			{}

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Standard_Real Value() const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::FieldFun_Minus);

#endif // !_SectPx_FieldFun_Minus_Header
