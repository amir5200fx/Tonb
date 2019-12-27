#include <labelVector.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::labelVector::typeName = "labelVector";

template<>
const char* tnbLib::labelVector::componentNames[] = { "x", "y", "z" };

template<>
const tnbLib::labelVector tnbLib::labelVector::zero(0, 0, 0);

template<>
const tnbLib::labelVector tnbLib::labelVector::one(1, 1, 1);


// ************************************************************************* //