#pragma once
#ifndef _SectPx_PairedInterface_Joint_Header
#define _SectPx_PairedInterface_Joint_Header

#include <SectPx_PairedInterface.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class PairedInterface_Joint
			: public SectPx_PairedInterface
		{

			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_PairedInterface>(*this);
			}

		public:

			static const char* typeName_;

			template<class... _Types>
			PairedInterface_Joint(_Types&&... _Args)
				: SectPx_PairedInterface(_Args...)
			{}

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT sectPxLib::interfaceType InterfaceType() const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::PairedInterface_Joint);

#endif // !_SectPx_PairedInterface_Joint_Header

