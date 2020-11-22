#pragma once
#ifndef _SectPx_FieldFun_Uni_Header
#define _SectPx_FieldFun_Uni_Header

#include <SectPx_oneParFieldFun.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class FieldFun_Uni
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

			FieldFun_Uni()
			{}

			FieldFun_Uni
			(
				const Standard_Integer theIndex
			)
				: SectPx_oneParFieldFun(theIndex)
			{}

			FieldFun_Uni
			(
				const Standard_Integer theIndex,
				const word& theName
			)
				: SectPx_oneParFieldFun(theIndex, theName)
			{}


			TnbSectPx_EXPORT Standard_Real Value() const override;

			TnbSectPx_EXPORT word RegObjTypeName() const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::FieldFun_Uni);

#endif // !_SectPx_FieldFun_Uni_Header
