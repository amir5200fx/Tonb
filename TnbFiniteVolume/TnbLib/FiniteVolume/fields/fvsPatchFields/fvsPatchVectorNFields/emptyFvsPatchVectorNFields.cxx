#include <emptyFvsPatchVectorNFields.hxx>

#include <fvsPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define doMakeFvsPatchTypeField(type, Type, args)                          \
    makeFvsPatchTypeField(fvsPatch##Type##Field, emptyFvsPatch##Type##Field);

	forAllVectorNTypes(doMakeFvsPatchTypeField)

		forAllTensorNTypes(doMakeFvsPatchTypeField)

		forAllDiagTensorNTypes(doMakeFvsPatchTypeField)

		forAllSphericalTensorNTypes(doMakeFvsPatchTypeField)

#undef doMakeFvsPatchTypeField

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //