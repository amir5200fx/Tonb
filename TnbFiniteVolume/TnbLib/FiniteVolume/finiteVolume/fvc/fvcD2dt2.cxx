#include <fvcD2dt2.hxx>

#include <d2dt2Scheme.hxx>
#include <fvMesh.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			d2dt2
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().ddtScheme("d2dt2(" + vf.name() + ')')
			)().fvcD2dt2(vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			d2dt2
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().ddtScheme
				(
					"d2dt2(" + rho.name() + ',' + vf.name() + ')'
				)
			)().fvcD2dt2(rho, vf);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //