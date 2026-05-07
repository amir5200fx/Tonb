#pragma once
#ifndef _ShapePx_Tools_Header
#define _ShapePx_Tools_Header

#include <Standard_Handle.hxx>
#include <ShapePx_Module.hxx>

#include <memory>
#include <vector>

#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array2OfReal.hxx>

class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_CtrlNet;
	class ShapePx_CtrlRow;
	class Pnt2d;
	class ShapePx_TopoSection;
	class ShapePx_TopoSectSegment;
	class ShapePx_TopoSectPole;
	class ShapePx_TopoCtrlNet;
	class SectPx_Segment;

	class ShapePx_Tools
	{

	public:

		static TnbShapePx_EXPORT TColgp_Array2OfPnt 
			ControlNet
			(
				const ShapePx_CtrlNet& theNet
			);

		static TnbShapePx_EXPORT TColStd_Array2OfReal
			Weights
			(
				const ShapePx_CtrlNet& theNet
			);

		static TnbShapePx_EXPORT std::shared_ptr<ShapePx_CtrlNet> 
			CreateControlNet
			(
				const ShapePx_TopoCtrlNet&
			);

		static TnbShapePx_EXPORT std::vector<std::pair<Pnt2d, Standard_Real>>
			CtrlRow
			(
				const std::vector<Pnt2d>& theQ, 
				const std::vector<Standard_Real>& theWeights
			);

		static TnbShapePx_EXPORT std::shared_ptr<ShapePx_TopoSection> 
			MakeTopoSection
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments, 
				const Standard_Real x
			);

		static TnbShapePx_EXPORT std::shared_ptr<ShapePx_TopoSection> 
			MakeTopoSection
			(
				const std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>& theSegments,
				const Standard_Real x
			);

		static TnbShapePx_EXPORT std::shared_ptr<ShapePx_TopoSection>
			MakeTopoSection
			(
				std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>&& theSegments,
				const Standard_Real x
			);

		static TnbShapePx_EXPORT std::vector<std::shared_ptr<ShapePx_TopoSectPole>> 
			CreateTopoControlPoints
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
			);

		static TnbShapePx_EXPORT std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>
			CreateTopoSegments
			(
				const std::vector<std::shared_ptr<ShapePx_TopoSectPole>>& thePoles
			);

		static TnbShapePx_EXPORT std::vector<std::shared_ptr<ShapePx_TopoSectPole>> 
			RetrievePoles
			(
				const std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>& theSegments
			);

		static TnbShapePx_EXPORT std::pair<std::vector<Pnt2d>, std::vector<Standard_Real>>
			RetrievePoles
			(
				const std::vector<std::shared_ptr<ShapePx_TopoSectPole>>& thePoles
			);

		static TnbShapePx_EXPORT Handle(Geom_Surface) Surface
		(
			const ShapePx_CtrlNet& theNet, 
			const Standard_Integer vDegree = 3
		);
	};
}

#endif // !_ShapePx_Tools_Header
