#include <TModel_ParaWire.hxx>

tnbLib::TModel_ParaWire::TModel_ParaWire
(
	const std::shared_ptr<TModel_CmpParaCurve>& theCurve
)
	: theCurve_(theCurve)
{
}

tnbLib::TModel_ParaWire::TModel_ParaWire
(
	const Standard_Integer theIndex,
	const std::shared_ptr<TModel_CmpParaCurve>& theCurve
)
	: theCurve_(theCurve)
	, TModel_Entity(theIndex)
{
}

tnbLib::TModel_ParaWire::TModel_ParaWire
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<TModel_CmpParaCurve>& theCurve
)
	: theCurve_(theCurve)
	, TModel_Entity(theIndex, theName)
{
}