#include <SectPx_PairedInterface.hxx>

const std::shared_ptr<tnbLib::SectPx_PairedInterface>
tnbLib::SectPx_PairedInterface::null = nullptr;

Standard_Boolean 
tnbLib::SectPx_PairedInterface::IsPaired() const
{
	return Standard_True;
}

void tnbLib::SectPx_PairedInterface::disJoint()
{
	SetPair(null);
}