#include <Aft2d_tPlnWireSurface.hxx>

#include <Aft2d_tPlnCurveSurface.hxx>
#include <TModel_ParaCurve.hxx>
#include <TModel_ParaWire.hxx>
#include <TModel_CmpParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//template<>
//template<>
//std::shared_ptr<tnbLib::TModel_ParaWire>
//tnbLib::Aft2d_tPlnWireSurface::MakeOrignWire<tnbLib::TModel_ParaWire>
//(
//	const std::shared_ptr<Aft2d_tPlnWireSurface>& thePlnWire
//	)
//{
//	Debug_Null_Pointer(thePlnWire);
//	const auto& plnCurves = thePlnWire->Curves();
//
//	std::vector<std::shared_ptr<TModel_ParaCurve>> curves;
//	curves.reserve(plnCurves.size());
//	for (const auto& x : plnCurves)
//	{
//		Debug_Null_Pointer(x);
//		curves.push_back(x->Curve());
//	}
//	auto wire = std::make_shared<TModel_ParaWire>
//		(
//			std::make_shared
//			<
//			std::vector<std::shared_ptr<TModel_ParaCurve>>
//			>(std::move(curves))
//			);
//	return std::move(wire);
//}

template<>
tnbLib::Entity2d_Box
tnbLib::Aft2d_tPlnWireSurface::CalcBoundingBox
(
	const Aft2d_tPlnCurveSurface& theCurve
)
{
	const auto& c = theCurve.Curve();
	Debug_Null_Pointer(c);
	auto b = c->CalcBoundingBox();
	return std::move(b);
}