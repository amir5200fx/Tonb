#pragma once
#ifndef _SectPx_ParTools_Header
#define _SectPx_ParTools_Header

#include <Standard_TypeDef.hxx>
#include <SectPx_ParsFwd.hxx>
#include <SectPx_Module.hxx>

#include <memory>
#include <map>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Parent;
	class SectPx_Child;
	class SectPx_RegObj;

	class SectPx_ParTools
	{

	public:

		static TnbSectPx_EXPORT Standard_Boolean
			HasParent
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static TnbSectPx_EXPORT Standard_Boolean
			IsRemovable
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static TnbSectPx_EXPORT Standard_Integer
			NbParents
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static TnbSectPx_EXPORT std::map
			<
			Standard_Integer,
			std::weak_ptr<SectPx_Parent>
			>
			Parents
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Parent>>
			RetrieveParents
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Parent>> RetrievePntParents(const std::shared_ptr<SectPx_Child>& theChild);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Parent>> RetrieveGeoMapParents(const std::shared_ptr<SectPx_Child>& theChild);

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_FreePar>
			FreeParameter
			(
				const std::shared_ptr<SectPx_RegObj>& theEntity
			);

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_FixedPar>
			FixedParameter
			(
				const std::shared_ptr<SectPx_RegObj>& theEntity
			);

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_ConstPar>
			ConstParameter
			(
				const std::shared_ptr<SectPx_RegObj>& theEntity
			);

		static TnbSectPx_EXPORT Standard_Boolean IsParameter(const std::shared_ptr<SectPx_RegObj>& theObj);

		static TnbSectPx_EXPORT void RemoveParentFromChild
		(
			const std::shared_ptr<SectPx_Parent>& theParent,
			const std::shared_ptr<SectPx_Child>& theChild
		);

		static TnbSectPx_EXPORT void AddParentToChild
		(
			const std::shared_ptr<SectPx_Parent>& theParent,
			const std::shared_ptr<SectPx_Child>& theChild
		);
	};
}

#endif // !_SectPx_ParTools_Header
