#include <labelDiagTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::labelDiagTensor::vsType::typeName
(
	"labelDiagTensor"
);

template<>
const char* const tnbLib::labelDiagTensor::vsType::componentNames[] =
{
	"ii"
};

template<>
const tnbLib::labelDiagTensor
tnbLib::labelDiagTensor::vsType::vsType::zero
(
	labelDiagTensor::uniform(0)
);

template<>
const tnbLib::labelDiagTensor tnbLib::labelDiagTensor::vsType::one
(
	labelDiagTensor::uniform(1)
);

template<>
const tnbLib::labelDiagTensor tnbLib::labelDiagTensor::vsType::max
(
	labelDiagTensor::uniform(labelMax)
);

template<>
const tnbLib::labelDiagTensor tnbLib::labelDiagTensor::vsType::min
(
	labelDiagTensor::uniform(-labelMax)
);

template<>
const tnbLib::labelDiagTensor tnbLib::labelDiagTensor::vsType::rootMax
(
	labelDiagTensor::uniform(sqrt(scalar(labelMax)))
);

template<>
const tnbLib::labelDiagTensor tnbLib::labelDiagTensor::vsType::rootMin
(
	labelDiagTensor::uniform(-sqrt(scalar(labelMax)))
);

