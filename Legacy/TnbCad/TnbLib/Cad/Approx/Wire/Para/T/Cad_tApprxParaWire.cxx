#include <Cad_tApprxParaWire.hxx>

#include <TModel_ParaWire.hxx>
#include <TModel_ParaCurve.hxx>

template<>
std::vector<std::shared_ptr<tnbLib::TModel_ParaCurve>>
tnbLib::Cad_tApprxParaWire::RetrieveCurves
(
	const TModel_ParaWire& theWire
)
{
	auto curves = theWire.Curves();
	return std::move(curves);
}