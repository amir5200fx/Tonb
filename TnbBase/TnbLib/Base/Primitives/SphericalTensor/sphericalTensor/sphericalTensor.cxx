#include <sphericalTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::sphericalTensor::vsType::typeName = "sphericalTensor";

template<>
const char* const tnbLib::sphericalTensor::vsType::componentNames[] = { "ii" };

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::zero
(
	sphericalTensor::uniform(0)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::one
(
	sphericalTensor::uniform(1)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::max
(
	sphericalTensor::uniform(VGREAT)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::min
(
	sphericalTensor::uniform(-VGREAT)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::rootMax
(
	sphericalTensor::uniform(ROOTVGREAT)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::rootMin
(
	sphericalTensor::uniform(-ROOTVGREAT)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::I(1);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::oneThirdI(1.0 / 3.0);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::twoThirdsI(2.0 / 3.0);

// ************************************************************************* //
