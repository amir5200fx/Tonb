#pragma once
#ifndef _SectPx_ScatterRegistry_Header
#define _SectPx_ScatterRegistry_Header

#include <Global_Serialization.hxx>
#include <Standard_TypeDef.hxx>
#include <SectPx_ParsFwd.hxx>
#include <SectPx_RegObjType.hxx>
#include <SectPx_Module.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_RegObj;

	class SectPx_ScatterRegistry
	{

	public:

		static const size_t nbEntities = (size_t)SectPx_RegObjType::other;

		typedef std::map<Standard_Integer, std::weak_ptr<SectPx_RegObj>> scatterMap;

	private:

		/*Private Data*/

		scatterMap theMaps[nbEntities];


		//- private functions and operators

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

		static TnbSectPx_EXPORT void Import(const std::shared_ptr<SectPx_RegObj>& ent, scatterMap& theMap);
		static TnbSectPx_EXPORT void Remove(const Standard_Integer id, scatterMap& theMap);

	protected:

		TnbSectPx_EXPORT void ImportToScatterMap(const std::shared_ptr<SectPx_RegObj>& ent);

		TnbSectPx_EXPORT void RemoveFromScatterMap(const std::shared_ptr<SectPx_RegObj>& ent);

	public:

		SectPx_ScatterRegistry()
		{}

		TnbSectPx_EXPORT Standard_Integer LastId(SectPx_RegObjType t) const;

		TnbSectPx_EXPORT const scatterMap& ScatterMap(SectPx_RegObjType t) const;
	};
}

#endif // !_SectPx_ScatterRegistry_Header
