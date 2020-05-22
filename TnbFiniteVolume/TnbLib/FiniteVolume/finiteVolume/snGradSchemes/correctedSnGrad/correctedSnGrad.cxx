#include <correctedSnGrad.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <linear.hxx>
#include <surfaceInterpolate.hxx>
#include <fvcGrad.hxx>
#include <gaussGrad.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		correctedSnGrad<Type>::~correctedSnGrad()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class Type>
		tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh> >
			tnbLib::fv::correctedSnGrad<Type>::fullGradCorrection
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			const fvMesh& mesh = this->mesh();

			tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > tssf =
				mesh.correctionVectors() & fvc::interpolate(fvc::grad(vf));
			tssf().rename("snGradCorr(" + vf.name() + ')');

			return tssf;
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			correctedSnGrad<Type>::correction
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			const fvMesh& mesh = this->mesh();

			// construct GeometricField<Type, fvsPatchField, surfaceMesh>
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > tssf
			(
				new GeometricField<Type, fvsPatchField, surfaceMesh>
				(
					IOobject
					(
						"snGradCorr(" + vf.name() + ')',
						vf.instance(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					vf.dimensions()*mesh.deltaCoeffs().dimensions()
					)
			);
			GeometricField<Type, fvsPatchField, surfaceMesh>& ssf = tssf();

			for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
			{
				ssf.replace
				(
					cmpt,
					correctedSnGrad<typename pTraits<Type>::cmptType>(mesh)
					.fullGradCorrection(vf.component(cmpt))
				);
			}

			return tssf;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //