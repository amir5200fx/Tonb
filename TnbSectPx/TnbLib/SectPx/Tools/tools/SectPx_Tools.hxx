#pragma once
#ifndef _SectPx_Tools_Header
#define _SectPx_Tools_Header

#include <Pnt2d.hxx>
#include <SectPx_Segment.hxx>
#include <SectPx_Module.hxx>
#include <SectPx_JoinPriority.hxx>

#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

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
	class SectPx_CurveQ;
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

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_Segment> 
			CommonSegment
			(
				const std::shared_ptr<SectPx_Pole>& thePole0,
				const std::shared_ptr<SectPx_Pole>& thePole1
			);

		//- the pole1 must be after the pole0
		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Pole>>
			TrackPoles
			(
				const std::shared_ptr<SectPx_Pole>& thePole0, 
				const std::shared_ptr<SectPx_Pole>& thePole1
			);

		//- if the pole is boundary, the second segment is null
		static TnbSectPx_EXPORT std::pair
			<
			std::shared_ptr<SectPx_Segment>, 
			std::shared_ptr<SectPx_Segment>
			>
			RetrieveSegments
			(
				const std::shared_ptr<SectPx_Pole>& thePole
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Segment>> 
			RetrieveSegments
			(
				const std::vector<std::shared_ptr<SectPx_Pole>>& thePoles
			);

		//- the poles need to be sorted
		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Segment>>
			RetrieveInnerSegments
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
				const std::shared_ptr<SectPx_TopoSegment>& theSeg
			);

		static TnbSectPx_EXPORT std::vector<Pnt2d>
			RetrieveControlPoints
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
			);

		static TnbSectPx_EXPORT std::vector<Pnt2d>
			RetrieveControlPoints
			(
				const std::shared_ptr<SectPx_CurveQ>& theSeg
			);

		static TnbSectPx_EXPORT std::vector<Standard_Real> 
			RetrieveWeights
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Pole>>
			RetrievePoles
			(
				const std::shared_ptr<SectPx_CurveQ>& theSeg
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_CurveQ>> 
			RetrieveSubCurveQ
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
			);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Pole>> 
			RetrievePoles
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
			);

		static TnbSectPx_EXPORT std::vector<std::pair<Standard_Real, Standard_Integer>> 
			KnotsNoInnerSlider
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments, 
				const Standard_Integer theDegree, 
				const Standard_Real theU0 = 0.0, 
				const Standard_Real theU1 = 1.0
			);

		static TnbSectPx_EXPORT std::vector<std::pair<Standard_Real, Standard_Integer>> 
			Knots
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments,
				const Standard_Integer theDegree
			);

		static TnbSectPx_EXPORT std::pair<TColStd_Array1OfReal, TColStd_Array1OfInteger> 
			Knots
			(
				const std::vector<std::pair<Standard_Real, Standard_Integer>>& theKnots
			);

		static TnbSectPx_EXPORT std::vector<std::pair<Standard_Real, Standard_Integer>> 
			Knots
			(
				const Standard_Integer theNbQ, 
				const Standard_Integer theDegree, 
				const Standard_Real theU0,
				const Standard_Real theU1
			);

		static TnbSectPx_EXPORT void RemoveParentFromChildren
		(
			const std::shared_ptr<SectPx_Parent>& theParent
		);

		static TnbSectPx_EXPORT void disJiont
		(
			const std::shared_ptr<SectPx_Interface>& theInterface
		);

		static TnbSectPx_EXPORT void Add
		(
			std::vector<std::pair<Standard_Real, Standard_Integer>>& theCurrent, 
			const std::vector<std::pair<Standard_Real, Standard_Integer>>& theKnot
		);

	};
}

#endif // !_SectPx_Tools_Header
