#include <interpolationCellPointWallModified.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::interpolationCellPointWallModified<Type>::
interpolationCellPointWallModified
(
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
	:
	interpolationCellPoint<Type>(psi)
{}


// ************************************************************************* //