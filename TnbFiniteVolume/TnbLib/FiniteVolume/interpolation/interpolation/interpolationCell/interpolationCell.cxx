#include <interpolationCell.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

	template<class Type>
	interpolationCell<Type>::interpolationCell
	(
		const GeometricField<Type, fvPatchField, volMesh>& psi
	)
		:
		interpolation<Type>(psi)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	Type interpolationCell<Type>::interpolate
	(
		const vector&,
		const label celli,
		const label
	) const
	{
		return this->psi_[celli];
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //