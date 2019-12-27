#include <TimeState.hxx>

#include <tnbTime.hxx>
#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::TimeState::TimeState()
	: dimensionedScalar(Time::timeName(0), dimTime, 0)
	, timeIndex_(0)
	, deltaT_(0)
	, deltaTSave_(0)
	, deltaT0_(0)
	, deltaTchanged_(false)
	, outputTimeIndex_(0)
	, outputTime_(false)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::TimeState::~TimeState()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::TimeState::userTimeToTime(const scalar theta) const
{
	return theta;
}


tnbLib::scalar tnbLib::TimeState::timeToUserTime(const scalar t) const
{
	return t;
}


tnbLib::scalar tnbLib::TimeState::timeOutputValue() const
{
	return timeToUserTime(value());
}


tnbLib::label tnbLib::TimeState::timeIndex() const
{
	return timeIndex_;
}


tnbLib::dimensionedScalar tnbLib::TimeState::deltaT() const
{
	return dimensionedScalar("deltaT", dimTime, deltaT_);
}


tnbLib::dimensionedScalar tnbLib::TimeState::deltaT0() const
{
	return dimensionedScalar("deltaT0", dimTime, deltaT0_);
}


bool tnbLib::TimeState::outputTime() const
{
	return outputTime_;
}


// ************************************************************************* //