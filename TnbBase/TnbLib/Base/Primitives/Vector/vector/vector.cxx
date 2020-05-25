#include <vector.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::vector::vsType::typeName = "vector";

template<>
const char* const tnbLib::vector::vsType::componentNames[] = { "x", "y", "z" };

template<>
const tnbLib::vector tnbLib::vector::vsType::vsType::zero(vector::uniform(0));

template<>
const tnbLib::vector tnbLib::vector::vsType::one(vector::uniform(1));

template<>
const tnbLib::vector tnbLib::vector::vsType::max(vector::uniform(VGREAT));

template<>
const tnbLib::vector tnbLib::vector::vsType::min(vector::uniform(-VGREAT));

template<>
const tnbLib::vector tnbLib::vector::vsType::rootMax(vector::uniform(ROOTVGREAT));

template<>
const tnbLib::vector tnbLib::vector::vsType::rootMin(vector::uniform(-ROOTVGREAT));


// ************************************************************************* //