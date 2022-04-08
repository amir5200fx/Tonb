#include <Cad_gLineSingularZone.hxx>

#include <Cad_gLineSingularCurve.hxx>
#include <GModel_Surface.hxx>
#include <GModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//template<>
//void tnbLib::Cad_gLineSingularZone::ProjectBoundariesToHorizons
//(
//	const GModel_Surface& theSurface
//)
//{
//	const auto& curves = this->Curves();
//	auto clist = curves;
//
//	std::vector<Pnt3d> offsets;
//	offsets.reserve(curves.size() + 1);
//	for (const auto& x : curves)
//	{
//		Debug_Null_Pointer(x);
//		auto pt = theSurface.Value(x->FirstCoord());
//		offsets.push_back(std::move(pt));
//	}
//	auto pt = theSurface.Value(curves.back()->LastCoord());
//	offsets.push_back(std::move(pt));
//
//	const auto horizons = this->Horizons();
//	Standard_Boolean projected = Standard_False;
//	for (const auto& x : horizons)
//	{
//		Debug_Null_Pointer(x);
//		auto lineHorizon = std::dynamic_pointer_cast<Cad_gLineSingularCurve>(x);
//		if (lineHorizon)
//		{
//			auto fp = lineHorizon->FirstParameter();
//			auto lp = lineHorizon->LastParameter();
//
//			Standard_Integer k = 0;
//			for (const auto& Q : offsets)
//			{
//				auto pj = lineHorizon->ProjectAt(Q, theSurface);
//
//			}
//		}
//	}
//	std::vector<std::shared_ptr<GModel_ParaCurve>> prjCurves;
//
//}