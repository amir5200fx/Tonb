#include <fvPatch.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class GeometricField, class Type>
const typename GeometricField::PatchFieldType& tnbLib::fvPatch::lookupPatchField
(
	const word& name,
	const GeometricField*,
	const Type*
) const
{
	return patchField<GeometricField, Type>
		(
			boundaryMesh().mesh().objectRegistry::lookupObject<GeometricField>(name)
			);
}


// ************************************************************************* //