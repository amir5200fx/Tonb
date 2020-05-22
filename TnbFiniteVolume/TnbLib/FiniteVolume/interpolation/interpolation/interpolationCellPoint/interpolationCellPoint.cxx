#include <interpolationCellPoint.hxx>

#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::interpolationCellPoint<Type>::interpolationCellPoint
(
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
	:
	interpolation<Type>(psi),
	psip_(volPointInterpolation::New(psi.mesh()).interpolate(psi))
{}


// ************************************************************************* //