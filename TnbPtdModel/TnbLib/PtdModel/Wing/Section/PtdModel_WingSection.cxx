#include <PtdModel_WingSection.hxx>

#include <PtdModel_Wing.hxx>

const std::shared_ptr<tnbLib::PtdModel_WingInfo>& 
tnbLib::PtdModel_WingSection::WingInfo(const PtdModel_Wing & wing)
{
	return wing.WingInfo();
}

const std::shared_ptr<tnbLib::PtdModel_xPars>& 
tnbLib::PtdModel_WingSection::xParameters(const PtdModel_Wing & wing)
{
	return wing.xParameters();
}