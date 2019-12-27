#include <labelTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::labelTensor::typeName = "labelTensor";

template<>
const char* tnbLib::labelTensor::componentNames[] =
{
	"xx", "xy", "xz",
	"yx", "yy", "yz",
	"zx", "zy", "zz"
};

template<>
const tnbLib::labelTensor tnbLib::labelTensor::zero
(
	0, 0, 0,
	0, 0, 0,
	0, 0, 0
);

template<>
const tnbLib::labelTensor tnbLib::labelTensor::one
(
	1, 1, 1,
	1, 1, 1,
	1, 1, 1
);


// ************************************************************************* //