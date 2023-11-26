#include <Voyage_AdaptPath_Info.hxx>

#include <Geo_Tools.hxx>

const Standard_Real tnbLib::Voyage_AdaptPath_Info::DEFAULT_TARGET_ANGLE = tnbLib::Geo_Tools::DegToRadian(30.0);

const Standard_Integer tnbLib::Voyage_AdaptPath_Info::DEFAULT_NB_LEVELS(2);
const Standard_Integer tnbLib::Voyage_AdaptPath_Info::DEFAULT_NB_SAMPLES(1);

tnbLib::Voyage_AdaptPath_Info::Voyage_AdaptPath_Info()
	: theTargetAngle_(DEFAULT_TARGET_ANGLE)
	, theNbLevels_(DEFAULT_NB_LEVELS)
	, theNbSamples_(DEFAULT_NB_SAMPLES)
{}
