#pragma once
#ifndef _SectPx_Tools_Header
#define _SectPx_Tools_Header

#include <Pnt2d.hxx>
#include <SectPx_Segment.hxx>
#include <SectPx_Module.hxx>
#include <SectPx_JoinPriority.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Parent;
	class SectPx_TopoProfile;
	class SectPx_Pnt;
	class SectPx_FrameRegistry;
	class SectPx_Node;
	class SectPx_Edge;
	class SectPx_Interface;
	class SectPx_Pole;
	class SectPx_BndPole;
	class SectPx_TopoSegment;
	class SectPx_Segment;
	class SectPx_Child;

	class SectPx_Tools
	{

	public:

		static TnbSectPx_EXPORT Standard_Boolean
			IsValidToJoint
			(
				const std::shared_ptr<SectPx_Node>& theNode0,
				const std::shared_ptr<SectPx_Node>& theNode1,
				const SectPx_JoinPriority priority = SectPx_JoinPriority::left
			);

		static TnbSectPx_EXPORT Standard_Integer
			MakePair
			(
				const std::shared_ptr<SectPx_Pnt>& theP0,
				const std::shared_ptr<SectPx_Pnt>& theP1,
				const std::shared_ptr<SectPx_FrameRegistry>& theReg,
				const SectPx_JoinPriority priority = SectPx_JoinPriority::left
			);

		static TnbSectPx_EXPORT std::tuple<Standard_Integer, Standard_Integer>
			MakeJoint
			(
				const std::shared_ptr<SectPx_TopoProfile>& theLeft,
				const std::shared_ptr<SectPx_TopoProfile>& theRight,
				const std::shared_ptr<SectPx_FrameRegistry>& theReg,
				const SectPx_JoinPriority priority = SectPx_JoinPriority::left
			);

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_Edge>
			MakeEdge
			(
				const std::shared_ptr<SectPx_Pnt>& theP0,
				const std::shared_ptr<SectPx_Pnt>& theP1,
				const std::shared_ptr<SectPx_FrameRegistry>& theReg
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Pole>>
			TrackPoles
			(
				const std::shared_ptr<SectPx_BndPole>& thePole0, 
				const std::shared_ptr<SectPx_BndPole>& thePole1
			);

		//- if the pole is boundary, the second segment is null
		static TnbSectPx_EXPORT std::pair<std::shared_ptr<SectPx_Segment>, std::shared_ptr<SectPx_Segment>>
			RetrieveSegments
			(
				const std::shared_ptr<SectPx_Pole>& thePole
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Segment>> 
			RetrieveSegments
			(
				const std::vector<std::shared_ptr<SectPx_Pole>>& thePoles
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>> 
			RetrieveChildren
			(
				const std::shared_ptr<SectPx_TopoSegment>& theSeg
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>> 
			RetrieveChildren
			(
				const std::shared_ptr<SectPx_Parent>& theParent
			);

		static TnbSectPx_EXPORT std::vector<Pnt2d>
			RetrieveControlPoints
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
			);

		static TnbSectPx_EXPORT void RemoveParentFromChildren
		(
			const std::shared_ptr<SectPx_Parent>& theParent
		);

		static void disJiont(const std::shared_ptr<SectPx_Interface>& theInterface);

	};
}

#endif // !_SectPx_Tools_Header
