#include <NModel_ParaWire.hxx>

tnbLib::NModel_ParaWire::NModel_ParaWire
(
	const std::shared_ptr<NModel_CmpParaCurve>& theCurve
)
	: theCurve_(theCurve)
{
}

tnbLib::NModel_ParaWire::NModel_ParaWire
(
	const Standard_Integer theIndex,
	const std::shared_ptr<NModel_CmpParaCurve>& theCurve
)
	: theCurve_(theCurve)
	, NModel_Entity(theIndex)
{
}

tnbLib::NModel_ParaWire::NModel_ParaWire
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<NModel_CmpParaCurve>& theCurve
)
	: theCurve_(theCurve)
	, NModel_Entity(theIndex, theName)
{
}