#include <Cad_gSingularZone.hxx>

#include <Cad_gSingularCurve.hxx>
#include <GModel_Surface.hxx>
#include <GModel_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Cad_gSingularZone::CreatePaired3d
(
	const GModel_Surface& theSurface
) const
{
	const auto& horizons = Horizons();
	for (const auto& x : horizons)
	{
		Debug_Null_Pointer(x);
		auto horizon = std::dynamic_pointer_cast<Cad_gSingularCurve>(x);
		Debug_Null_Pointer(horizon);

		auto c3d = 
			Cad_SingularCurveBase::CalcCurve3d
			(
				x->Geometry(), 
				GModel_Tools::RetrieveGeometry(theSurface),
				Cad_SingularCurveBase::ApproxInfo
			);
		Debug_Null_Pointer(c3d);
		horizon->SetPaired3d(std::move(c3d));
	}
}