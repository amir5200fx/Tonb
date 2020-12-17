#pragma once
#ifndef _SectPx_FrameRegistry_Header
#define _SectPx_FrameRegistry_Header

#include <SectPx_ObjectRegistry.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoSegment;

	class SectPx_FrameRegistry
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

		SectPx_FrameRegistry()
		{}

	public:

		TnbSectPx_EXPORT SectPx_FrameRegistry
		(
			const std::shared_ptr<SectPx_CountRegistry>& theCounter,
			const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
		);

		TnbSectPx_EXPORT SectPx_FrameRegistry
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_CountRegistry>& theCounter,
			const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
		);

		TnbSectPx_EXPORT Standard_Integer NbTopoSegments() const;

		TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_TopoSegment>> 
			RetrieveTopoSegments() const;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_FrameRegistry);


#endif // !_SectPx_FrameRegistry_Header
