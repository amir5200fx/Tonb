#include <blockAMGLevels.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineNamedTemplateTypeNameAndDebug(blockAmgScalarLevel, 0);
	defineNamedTemplateTypeNameAndDebug(blockAmgVectorLevel, 0);
	defineNamedTemplateTypeNameAndDebug(blockAmgTensorLevel, 0);
#define makeNamedTemplateTypeNameAndDebug(type, Type, args)      \
    defineNamedTemplateTypeNameAndDebug(blockAmg##Type##Level, 0);

	forAllVectorNTypes(makeNamedTemplateTypeNameAndDebug);

#undef makeNamedTemplateTypeNameAndDebug

	defineNamedTemplateTypeNameAndDebug(coarseblockAmgScalarLevel, 0);
	defineNamedTemplateTypeNameAndDebug(coarseblockAmgVectorLevel, 0);
	defineNamedTemplateTypeNameAndDebug(coarseblockAmgTensorLevel, 0);
#define makeNamedTemplateTypeNameAndDebug(type, Type, args)      \
    defineNamedTemplateTypeNameAndDebug(coarseblockAmg##Type##Level, 0);

	forAllVectorNTypes(makeNamedTemplateTypeNameAndDebug);

#undef makeNamedTemplateTypeNameAndDebug

	defineNamedTemplateTypeNameAndDebug(fineblockAmgScalarLevel, 0);
	defineNamedTemplateTypeNameAndDebug(fineblockAmgVectorLevel, 0);
	defineNamedTemplateTypeNameAndDebug(fineblockAmgTensorLevel, 0);
#define makeNamedTemplateTypeNameAndDebug(type, Type, args)      \
    defineNamedTemplateTypeNameAndDebug(fineblockAmg##Type##Level, 0);

	forAllVectorNTypes(makeNamedTemplateTypeNameAndDebug);

#undef makeNamedTemplateTypeNameAndDebug

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //