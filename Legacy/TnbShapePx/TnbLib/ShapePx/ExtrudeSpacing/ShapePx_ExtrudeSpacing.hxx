//#pragma once
//#ifndef _ShapePx_ExtrudeSpacing_Header
//#define _ShapePx_ExtrudeSpacing_Header
//
//#include <Standard_TypeDef.hxx>
//#include <Global_Done.hxx>
//#include <ShapePx_Module.hxx>
//
//#include <vector>
//
//namespace tnbLib
//{
//
//	// Forward Declarations
//	class ShapePx_CustomSpacing;
//
//	class ShapePx_ExtrudeSpacing
//		: public Global_Done
//	{
//
//	public:
//
//		class Dot
//		{
//
//		public:
//
//			Standard_Real x;
//
//			Dot(const Standard_Real r)
//				: x(r)
//			{}
//
//			virtual Standard_Boolean IsSpan() const
//			{
//				return Standard_False;
//			}
//
//			static bool IsLess(const std::shared_ptr<Dot>& d0, const std::shared_ptr<Dot>& d1)
//			{
//				return d0->x < d1->x;
//			}
//		};
//
//		class SpanDot
//			: public Dot
//		{
//
//		public:
//
//			SpanDot(const Standard_Real x)
//				: Dot(x)
//			{}
//
//			Standard_Boolean IsSpan() const override
//			{
//				return Standard_True;
//			}
//		};
//
//		typedef std::shared_ptr<Dot> dot_t;
//
//		struct Span
//		{
//			double x0;
//			double x1;
//		};
//
//	private:
//
//		/*Private Data*/
//
//		Standard_Integer theMinNbSections_;
//		Standard_Real theMinDelta_;
//
//
//		std::vector<Span> theSpans_;
//		std::vector<dot_t> theMerged_;
//
//
//		static TnbShapePx_EXPORT Standard_Real Dx(const Span& p, const Standard_Integer n);
//		static TnbShapePx_EXPORT std::vector<dot_t> Xs(const Span& p, const Standard_Integer n);
//
//
//		TnbShapePx_EXPORT void CalcMinDelta();
//
//	public:
//
//		static TnbShapePx_EXPORT const Standard_Integer DEFAULT_MIN_NB_SECTIONS;
//
//		ShapePx_ExtrudeSpacing()
//		{}
//
//		auto MinNbSections() const
//		{
//			return theMinNbSections_;
//		}
//
//		const auto& Spans() const
//		{
//			return theSpans_;
//		}
//
//		const auto& Merged() const
//		{
//			return theMerged_;
//		}
//
//		TnbShapePx_EXPORT std::shared_ptr<ShapePx_CustomSpacing> Spacing() const;
//
//		TnbShapePx_EXPORT void Perform();
//
//		TnbShapePx_EXPORT void SetMinNbSections(const Standard_Integer n);
//
//		TnbShapePx_EXPORT void ImportSpan(const Span& p);
//
//		TnbShapePx_EXPORT void ImportSpan(Span&& p);
//	};
//}
//
//#endif // !_ShapePx_ExtrudeSpacing_Header
