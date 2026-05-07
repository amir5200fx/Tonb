#include <PtdModel_PropSection.hxx>

#include <PtdModel_PropBlade.hxx>

unsigned short tnbLib::PtdModel_PropSection::verbose(0);

const std::shared_ptr<tnbLib::PtdModel_BladeInfo>& 
tnbLib::PtdModel_PropSection::BladeInfo(const PtdModel_PropBlade & blade)
{
	return blade.BladeInfo();
}

const std::shared_ptr<tnbLib::PtdModel_xPars>& 
tnbLib::PtdModel_PropSection::xParameters(const PtdModel_PropBlade & blade)
{
	return blade.xParameters();
}