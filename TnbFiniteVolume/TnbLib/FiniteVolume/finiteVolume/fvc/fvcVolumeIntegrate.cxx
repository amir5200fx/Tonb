#include <fvcVolumeIntegrate.hxx>

#include <fvMesh.hxx>
#include <Field.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<Field<Type> >
			volumeIntegrate
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return vf.mesh().V()*vf.internalField();
		}

		template<class Type>
		tmp<Field<Type> >
			volumeIntegrate
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf
			)
		{
			tmp<Field<Type> > tvivf = tvf().mesh().V()*tvf().internalField();
			tvf.clear();
			return tvivf;
		}


		template<class Type>
		dimensioned<Type>
			domainIntegrate
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return dimensioned<Type>
				(
					"domainIntegrate(" + vf.name() + ')',
					dimVol*vf.dimensions(),
					gSum(fvc::volumeIntegrate(vf))
					);
		}

		template<class Type>
		dimensioned<Type>
			domainIntegrate
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf
			)
		{
			dimensioned<Type> integral = domainIntegrate(tvf());
			tvf.clear();
			return integral;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
