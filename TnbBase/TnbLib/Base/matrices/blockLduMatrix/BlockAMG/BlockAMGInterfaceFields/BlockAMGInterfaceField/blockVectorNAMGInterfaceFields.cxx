#include <BlockAMGInterfaceField.hxx>
#include <ProcessorBlockAMGInterfaceField.hxx>
#include <GGIBlockAMGInterfaceField.hxx>
#include <VectorNFieldTypes.hxx>S
#include <ExpandTensorNField.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeTemplateTypeNameAndDebug(type, Type, args)                     \
                                                                              \
typedef BlockAMGInterfaceField<type > block##Type##AMGInterfaceField;         \
defineNamedTemplateTypeNameAndDebug(block##Type##AMGInterfaceField, 0);       \
defineTemplateRunTimeSelectionTable(block##Type##AMGInterfaceField, lduInterface); \
                                                                              \
typedef ProcessorBlockAMGInterfaceField<type > block##Type##ProcessorAMGInterfaceField;  \
makeBlockAMGInterfaceField(block##Type##AMGInterfaceField, block##Type##ProcessorAMGInterfaceField); \
typedef GGIBlockAMGInterfaceField<type > block##Type##GGIAMGInterfaceField;  \
makeBlockAMGInterfaceField(block##Type##AMGInterfaceField, block##Type##GGIAMGInterfaceField); \

	forAllVectorNTypes(makeTemplateTypeNameAndDebug);

#undef makeTemplateTypeNameAndDebug

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //