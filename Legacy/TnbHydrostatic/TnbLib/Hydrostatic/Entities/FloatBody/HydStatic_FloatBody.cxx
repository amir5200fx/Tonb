#include <HydStatic_FloatBody.hxx>

tnbLib::HydStatic_FloatBody::HydStatic_FloatBody
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: HydStatic_Entity(theIndex, theName)
{
	// empty body
}

tnbLib::HydStatic_FloatBody::HydStatic_FloatBody
(
	const std::shared_ptr<marineLib::Body_Dry>& theDry, 
	const std::shared_ptr<marineLib::Body_Wetted>& theWetted
)
	: theDry_(theDry)
	, theWetted_(theWetted)
{
	// empty body
}

tnbLib::HydStatic_FloatBody::HydStatic_FloatBody
(
	std::shared_ptr<marineLib::Body_Dry>&& theDry, 
	std::shared_ptr<marineLib::Body_Wetted>&& theWetted
)
	: theDry_(std::move(theDry))
	, theWetted_(std::move(theWetted))
{
	// empty body
}

tnbLib::HydStatic_FloatBody::HydStatic_FloatBody
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<marineLib::Body_Dry>& theDry,
	const std::shared_ptr<marineLib::Body_Wetted>& theWetted
)
	: HydStatic_Entity(theIndex, theName)
	, theDry_(theDry)
	, theWetted_(theWetted)
{
	// empty body
}

tnbLib::HydStatic_FloatBody::HydStatic_FloatBody
(
	const Standard_Integer theIndex,
	const word & theName, 
	std::shared_ptr<marineLib::Body_Dry>&& theDry,
	std::shared_ptr<marineLib::Body_Wetted>&& theWetted
)
	: HydStatic_Entity(theIndex, theName)
	, theDry_(std::move(theDry))
	, theWetted_(std::move(theWetted))
{
	// empty body
}