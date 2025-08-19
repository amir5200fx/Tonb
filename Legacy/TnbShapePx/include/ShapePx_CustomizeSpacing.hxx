//#pragma once
//#ifndef _ShapePx_CustomizeSpacing_Header
//#define _ShapePx_CustomizeSpacing_Header
//
//#include <Geo_PriorityList.hxx>
//#include <ShapePx_Module.hxx>
//
//#include <vector>
//#include <memory>
//
//namespace tnbLib
//{
//
//	// Forward Declarations
//	class ShapePx_CustomSpacing;
//
//	class ShapePx_CustomizeSpacing
//	{
//
//		/*Private Data*/
//
//		mutable Geo_PriorityList<Standard_Real> theXs_;
//
//
//		TnbShapePx_EXPORT void AllocateMemory();
//
//	public:
//
//		ShapePx_CustomizeSpacing()
//		{
//			AllocateMemory();
//		}
//
//
//		TnbShapePx_EXPORT std::vector<Standard_Real> Xs() const;
//
//		TnbShapePx_EXPORT std::shared_ptr<ShapePx_CustomSpacing> Spacing() const;
//
//		TnbShapePx_EXPORT void Insert(const Standard_Real x) const;
//
//		TnbShapePx_EXPORT void Insert(const std::vector<Standard_Real>& x) const;
//
//	};
//}
//
//#endif // !_ShapePx_CustomizeSpacing_Header
