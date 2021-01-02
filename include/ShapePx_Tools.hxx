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

		static TnbShapePx_EXPORT std::vector<std::pair<Pnt2d, Standard_Real>>
			CtrlRow
			(
				const std::vector<Pnt2d>& theQ, 
				const std::vector<Standard_Real>& theWeights
			);
	};
}

#endif // !_ShapePx_Tools_Header
