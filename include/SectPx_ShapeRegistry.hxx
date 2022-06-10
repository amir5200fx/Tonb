#pragma once
#ifndef _SectPx_ShapeRegistry_Header
#define _SectPx_ShapeRegistry_Header

#include <SectPx_ObjectRegistry.hxx>

#include <map>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;

	class SectPx_ShapeRegistry
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

		SectPx_ShapeRegistry()
		{}

	public:

		TnbSectPx_EXPORT SectPx_ShapeRegistry
		(
			const std::shared_ptr<SectPx_CountRegistry>& theCounter,
			const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
		);

		TnbSectPx_EXPORT SectPx_ShapeRegistry
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_CountRegistry>& theCounter,
			const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
		);


		TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Par>> 
			RetrieveGlobalParameters() const;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_ShapeRegistry);

#endif // !_SectPx_ShapeRegistry_Header
