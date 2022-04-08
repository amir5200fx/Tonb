#include <Cad_gApprxParaWire.hxx>

#include <GModel_ParaWire.hxx>
#include <GModel_ParaCurve.hxx>

template<>
std::vector<std::shared_ptr<tnbLib::GModel_ParaCurve>> 
tnbLib::Cad_gApprxParaWire::RetrieveCurves
(
	const GModel_ParaWire& theWire
)
{
	auto curves = theWire.Curves();
	return std::move(curves);
}