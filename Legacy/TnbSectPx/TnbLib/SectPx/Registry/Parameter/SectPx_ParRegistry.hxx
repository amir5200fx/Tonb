#pragma once
#ifndef _SectPx_ParRegistry_Header
#define _SectPx_ParRegistry_Header

#include <SectPx_ObjectRegistry.hxx>

#include <map>

namespace tnbLib
{

	class SectPx_ParRegistry
		: public SectPx_ObjectRegistry
	{

		/*Private Data*/


		//- private functions and operators


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_ObjectRegistry>(*this);
		}


		TnbSectPx_EXPORT void CheckObjType
		(
			const std::shared_ptr<SectPx_RegObj>& theObj,
			const char* funcName
		) const override;

	protected:

		SectPx_ParRegistry()
		{}

	public:

		TnbSectPx_EXPORT SectPx_ParRegistry
		(
			const std::shared_ptr<SectPx_CountRegistry>& theCounter,
			const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
		);

		TnbSectPx_EXPORT SectPx_ParRegistry
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_CountRegistry>& theCounter,
			const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
		);


	};

}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_ParRegistry);

#endif // !_SectPx_ParRegistry_Header
