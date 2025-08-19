#include <SectPx_SegmentAdaptor.hxx>

//#include <SectPx_SegmentController.hxx>
//#include <SectPx_CPtsMap.hxx>
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//std::vector<tnbLib::Pnt2d>
//tnbLib::SectPx_SegmentAdaptor::RetrieveControlPoints() const
//{
//	std::vector<Pnt2d> pts;
//	if (HasController())
//	{
//		auto ctrler = Controller().lock();
//		Debug_Null_Pointer(ctrler);
//
//		if (ctrler->CPts())
//		{
//			auto qs = ctrler->CPts()->Pts();
//			pts.reserve(qs.size());
//			for (const auto& x : qs)
//			{
//				pts.push_back(std::move(x));
//			}
//		}
//	}
//	return std::move(pts);
//}