#include <diagTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::diagTensor::vsType::typeName = "diagTensor";

template<>
const char* const tnbLib::diagTensor::vsType::componentNames[] =
{
	"xx", "yy", "zz"
};

template<>
const tnbLib::diagTensor tnbLib::diagTensor::vsType::vsType::zero
(
	diagTensor::uniform(0)
);

template<>
const tnbLib::diagTensor tnbLib::diagTensor::vsType::one
(
	diagTensor::uniform(1)
);

template<>
const tnbLib::diagTensor tnbLib::diagTensor::vsType::max
(
	diagTensor::uniform(VGREAT)
);

template<>
const tnbLib::diagTensor tnbLib::diagTensor::vsType::min
(
	diagTensor::uniform(-VGREAT)
);

template<>
const tnbLib::diagTensor tnbLib::diagTensor::vsType::rootMax
(
	diagTensor::uniform(ROOTVGREAT)
);

template<>
const tnbLib::diagTensor tnbLib::diagTensor::vsType::rootMin
(
	diagTensor::uniform(-ROOTVGREAT)
);


// ************************************************************************* //