#pragma once
#ifndef _SectPx_PntTools_Header
#define _SectPx_PntTools_Header

#include <Standard_TypeDef.hxx>
#include <SectPx_PntsFwd.hxx>

#include <vector>
#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pnt;
	class SectPx_TPnt;
	class SectPx_Coord;
	class SectPx_MasterPnt;
	class SectPx_Edge;

	class SectPx_PntTools
	{

	public:

		/*static Standard_Integer
			NbParents
			(
				const std::shared_ptr<SectPx_Coord>& thePnt
			);

		static Standard_Boolean
			HasParent
			(
				const std::shared_ptr<SectPx_Coord>& thePnt
			);*/

		static Standard_Boolean
			IsRemovable
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static Standard_Boolean
			IsEmpty
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static Standard_Boolean
			IsComponent
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static Standard_Boolean
			IsGeoField
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static void deAttach
		(
			const std::shared_ptr<SectPx_TPnt>& thePnt,
			const std::shared_ptr<SectPx_Edge>& theEdge
		);

		static std::vector<std::shared_ptr<SectPx_Edge>>
			deAttach
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static void Replace
		(
			const std::shared_ptr<SectPx_Pnt>& thePrior,
			const std::shared_ptr<SectPx_Edge>& theEdge,
			const std::shared_ptr<SectPx_Pnt>& theNew
		);

		static void Replace
		(
			const std::shared_ptr<SectPx_Pnt>& thePrior,
			const std::shared_ptr<SectPx_Pnt>& theNew
		);
	};
}

#endif // !_SectPx_PntTools_Header
