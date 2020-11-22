#pragma once
#ifndef _SectPx_EmptyInterface_Header
#define _SectPx_EmptyInterface_Header

#include <SectPx_Interface.hxx>

namespace tnbLib
{

	class SectPx_EmptyInterface
		: public SectPx_Interface
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Interface>(*this);
		}


	protected:


		TnbSectPx_EXPORT void disJoint() override;

		TnbSectPx_EXPORT Standard_Boolean IsRemovable() const override;

	public:

		static TnbSectPx_EXPORT const char* typeName_;

		template<class... _Types>
		SectPx_EmptyInterface(_Types&&... _Args)
			: SectPx_Interface(_Args...)
		{}

		TnbSectPx_EXPORT Standard_Boolean IsEmpty() const override;

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::interfaceType InterfaceType() const override;

		
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_EmptyInterface);

#endif // !_SectPx_EmptyInterface_Header
