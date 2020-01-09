#include <coeffFields.hxx>

#include <blockVectorNMatrices.hxx>
#include <BlockLduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeNamedTemplateTypeNameAndDebug(type, Type, args)      \
    defineNamedTemplateTypeNameAndDebug(block##Type##Matrix, 0);

	forAllVectorNTypes(makeNamedTemplateTypeNameAndDebug);

#undef makeNamedTemplateTypeNameAndDebug

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //