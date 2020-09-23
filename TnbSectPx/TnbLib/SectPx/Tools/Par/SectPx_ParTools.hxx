#pragma once
#ifndef _SectPx_ParTools_Header
#define _SectPx_ParTools_Header

#include <Standard_TypeDef.hxx>
#include <SectPx_ParsFwd.hxx>

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

		static Standard_Boolean
			HasParent
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static Standard_Boolean
			IsRemovable
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static Standard_Integer
			NbParents
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static std::map
			<
			Standard_Integer,
			std::weak_ptr<SectPx_Parent>
			>
			Parents
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static std::vector<std::shared_ptr<SectPx_Parent>>
			RetrieveParents
			(
				const std::shared_ptr<SectPx_Child>& theChild
			);

		static std::vector<std::shared_ptr<SectPx_Parent>> RetrievePntParents(const std::shared_ptr<SectPx_Child>& theChild);

		static std::vector<std::shared_ptr<SectPx_Parent>> RetrieveGeoMapParents(const std::shared_ptr<SectPx_Child>& theChild);

		static std::shared_ptr<SectPx_FreePar>
			FreeParameter
			(
				const std::shared_ptr<SectPx_RegObj>& theEntity
			);

		static std::shared_ptr<SectPx_FixedPar>
			FixedParameter
			(
				const std::shared_ptr<SectPx_RegObj>& theEntity
			);

		static std::shared_ptr<SectPx_ConstPar>
			ConstParameter
			(
				const std::shared_ptr<SectPx_RegObj>& theEntity
			);

		static Standard_Boolean IsParameter(const std::shared_ptr<SectPx_RegObj>& theObj);

		static void RemoveParentFromChild
		(
			const std::shared_ptr<SectPx_Parent>& theParent,
			const std::shared_ptr<SectPx_Child>& theChild
		);

		static void AddParentToChild
		(
			const std::shared_ptr<SectPx_Parent>& theParent,
			const std::shared_ptr<SectPx_Child>& theChild
		);
	};
}

#endif // !_SectPx_ParTools_Header
