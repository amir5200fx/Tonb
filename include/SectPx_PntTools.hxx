#pragma once
#ifndef _SectPx_PntTools_Header
#define _SectPx_PntTools_Header

#include <Standard_TypeDef.hxx>
#include <SectPx_PntsFwd.hxx>
#include <SectPx_Module.hxx>

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
	class SectPx_FrameRegistry;
	class SectPx_Node;
	class Pnt2d;

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

		static TnbSectPx_EXPORT Standard_Boolean
			IsRemovable
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static TnbSectPx_EXPORT Standard_Boolean
			IsEmpty
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static TnbSectPx_EXPORT Standard_Boolean
			IsComponent
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static TnbSectPx_EXPORT Standard_Boolean
			IsGeoField
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Pnt>>
			MakeOffsetPnts
			(
				const std::vector<Pnt2d>& theCoords,
				const std::shared_ptr<SectPx_FrameRegistry>& theRegistry
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Pnt>>
			TrackPnts
			(
				const std::shared_ptr<SectPx_Node>& theNode0, 
				const std::shared_ptr<SectPx_Node>& theNode1
			);

		static TnbSectPx_EXPORT void deAttach
		(
			const std::shared_ptr<SectPx_TPnt>& thePnt,
			const std::shared_ptr<SectPx_Edge>& theEdge
		);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Edge>>
			deAttach
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_Edge> 
			CommonEdge
			(
				const std::shared_ptr<SectPx_Pnt>& theP0,
				const std::shared_ptr<SectPx_Pnt>& theP1
			);

		static TnbSectPx_EXPORT void Replace
		(
			const std::shared_ptr<SectPx_Pnt>& thePrior,
			const std::shared_ptr<SectPx_Edge>& theEdge,
			const std::shared_ptr<SectPx_Pnt>& theNew
		);

		static TnbSectPx_EXPORT void Replace
		(
			const std::shared_ptr<SectPx_Pnt>& thePrior,
			const std::shared_ptr<SectPx_Pnt>& theNew
		);
	};
}

#endif // !_SectPx_PntTools_Header
