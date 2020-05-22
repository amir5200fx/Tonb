#include <coupledFvsPatchVectorNFields.hxx>

#include <fvsPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define doMakeFvsPatchTypeField(type, Type, args)                          \
    makeFvsPatchTypeFieldTypeName(coupledFvsPatch##Type##Field);

	forAllVectorNTypes(doMakeFvsPatchTypeField)

		forAllTensorNTypes(doMakeFvsPatchTypeField)

		forAllDiagTensorNTypes(doMakeFvsPatchTypeField)

		forAllSphericalTensorNTypes(doMakeFvsPatchTypeField)

#undef doMakeFvsPatchTypeField

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //