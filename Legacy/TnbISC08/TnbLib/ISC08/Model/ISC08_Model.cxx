#include <ISC08_Model.hxx>

tnbLib::ISC08_Model::ISC08_Model
(
	VesselParams && theParameters,
	Props && theProperties, 
	const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theGz
)
	: theVesselParameters_(std::move(theParameters))
	, theProperties_(std::move(theProperties))
	, theEff_(theGz)
{
	// empty body
}

tnbLib::ISC08_Model::ISC08_Model
(
	VesselParams && theParameters, 
	Props && theProperties,
	std::shared_ptr<hydStcLib::rArmCurve_Eff>&& theGz
)
	: theVesselParameters_(std::move(theParameters))
	, theProperties_(std::move(theProperties))
	, theEff_(std::move(theGz))
{
	// empty body
}

void tnbLib::ISC08_Model::SetParameters(const VesselParams & theParameters)
{
	theVesselParameters_ = theParameters;
}

void tnbLib::ISC08_Model::SetParameters(VesselParams && theParameters)
{
	theVesselParameters_ = std::move(theParameters);
}

void tnbLib::ISC08_Model::SetProperties(const Props & theProps)
{
	theProperties_ = theProps;
}

void tnbLib::ISC08_Model::SetProperties(Props && theProps)
{
	theProperties_ = std::move(theProps);
}

void tnbLib::ISC08_Model::SetGZeff(const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theGz)
{
	theEff_ = theGz;
}

void tnbLib::ISC08_Model::SetGZeff(std::shared_ptr<hydStcLib::rArmCurve_Eff>&& theGz)
{
	theEff_ = std::move(theGz);
}