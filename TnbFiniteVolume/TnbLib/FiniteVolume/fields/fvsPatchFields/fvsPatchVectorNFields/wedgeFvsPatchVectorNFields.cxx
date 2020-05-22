#include <wedgeFvsPatchVectorNFields.hxx>

#include <fvsPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define doMakeFvsPatchTypeField(type, Type, args)                          \
    makeFvsPatchTypeField(fvsPatch##Type##Field, wedgeFvsPatch##Type##Field);

	forAllVectorNTypes(doMakeFvsPatchTypeField)

		forAllTensorNTypes(doMakeFvsPatchTypeField)

		forAllDiagTensorNTypes(doMakeFvsPatchTypeField)

		forAllSphericalTensorNTypes(doMakeFvsPatchTypeField)

#undef doMakeFvsPatchTypeField

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //