#include <uncorrectedSnGrad.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		uncorrectedSnGrad<Type>::~uncorrectedSnGrad()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			uncorrectedSnGrad<Type>::correction
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) const
		{
			notImplemented
			(
				"uncorrectedSnGrad<Type>::correction"
				"(const GeometricField<Type, fvPatchField, volMesh>&)"
			);
			return tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >(NULL);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //