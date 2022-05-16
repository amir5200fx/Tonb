#include <GModel_ParaCurve.hxx>

#include <Global_Macros.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_BoundedCurve.hxx>

#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <Pln_Tools.hxx>
#include <GModel_Tools.hxx>

std::pair
<
	std::shared_ptr<tnbLib::GModel_ParaCurve>,
	std::shared_ptr<tnbLib::GModel_ParaCurve>
> 
tnbLib::GModel_ParaCurve::Split
(
	const Standard_Real thePar,
	const std::shared_ptr<GModel_ParaCurve>& theCurve
)
{
	auto t = GModel_Tools::Split(thePar, theCurve);
	return std::move(t);
}
