#pragma once
inline tnbLib::PtdModel_FixedPar::PtdModel_FixedPar
(
	const PtdModel_BndValue & theValue
)
	: theValue_(theValue)
{
	// empty body [6/3/2021 Amir]
}

inline tnbLib::PtdModel_FixedPar::PtdModel_FixedPar
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const PtdModel_BndValue & theValue
)
	: PtdModel_Par(theIndex, theName)
	, theValue_(theValue)
{
	// empty body [6/3/2021 Amir]
}

inline tnbLib::PtdModel_FixedPar::PtdModel_FixedPar
(
	PtdModel_BndValue && theValue
)
	: theValue_(std::move(theValue))
{
	// empty body [6/3/2021 Amir]
}

inline tnbLib::PtdModel_FixedPar::PtdModel_FixedPar
(
	const Standard_Integer theIndex,
	const word & theName,
	PtdModel_BndValue && theValue
)
	: PtdModel_Par(theIndex, theName)
	, theValue_(std::move(theValue))
{
	// empty body [6/3/2021 Amir]
}