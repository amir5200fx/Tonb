#include <PtdModel_WingGlobalPars.hxx>

tnbLib::PtdModel_WingGlobalPars::PtdModel_WingGlobalPars
(
	const std::shared_ptr<PtdModel_Par>& par
)
	: theSpan_(par)
{
	// empty body [6/10/2021 Amir]
}

tnbLib::PtdModel_WingGlobalPars::PtdModel_WingGlobalPars
(
	std::shared_ptr<PtdModel_Par>&& par
)
	: theSpan_(std::move(par))
{
	// empty body [6/10/2021 Amir]
}