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
	SetNode(nullptr);
}

Standard_Boolean 
tnbLib::SectPx_PairedInterface::IsRemovable() const
{
	if (Node()) return Standard_False;

	{ // check pairing connection
		const auto pair = Pair().lock();
		if (pair IS_EQUAL null) return Standard_True;
		if (NOT pair) return Standard_True;
	}

	return Standard_False;
}