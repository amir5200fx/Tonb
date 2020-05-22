#include <fvcDdt.hxx>

#include <fvMesh.hxx>
#include <ddtScheme.hxx>
#include <GeometricFields.hxx>
#include <volMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			ddt
			(
				const dimensioned<Type> dt,
				const fvMesh& mesh
			)
		{
			return fv::ddtScheme<Type>::New
			(
				mesh,
				mesh.schemesDict().ddtScheme("ddt(" + dt.name() + ')')
			)().fvcDdt(dt);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			ddt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().ddtScheme("ddt(" + vf.name() + ')')
			)().fvcDdt(vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			ddt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().ddtScheme
				(
					"ddt(" + rho.name() + ',' + vf.name() + ')'
				)
			)().fvcDdt(rho, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			ddt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().ddtScheme
				(
					"ddt(" + rho.name() + ',' + vf.name() + ')'
				)
			)().fvcDdt(rho, vf);
		}


		template<class Type>
		tmp<GeometricField<typename flux<Type>::type, fvsPatchField, surfaceMesh> >
			ddtPhiCorr
			(
				const volScalarField& rA,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField
				<
				typename flux<Type>::type,
				fvsPatchField,
				surfaceMesh
				>& phi
			)
		{
			return fv::ddtScheme<Type>::New
			(
				U.mesh(),
				U.mesh().schemesDict().ddtScheme("ddt(" + U.name() + ')')
			)().fvcDdtPhiCorr(rA, U, phi);
		}


		template<class Type>
		tmp<GeometricField<typename flux<Type>::type, fvsPatchField, surfaceMesh> >
			ddtPhiCorr
			(
				const volScalarField& rA,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField
				<
				typename flux<Type>::type,
				fvsPatchField,
				surfaceMesh
				>& phi
			)
		{
			return fv::ddtScheme<Type>::New
			(
				U.mesh(),
				U.mesh().schemesDict().ddtScheme
				(
					"ddt(" + rho.name() + ',' + U.name() + ')'
				)
			)().fvcDdtPhiCorr(rA, rho, U, phi);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //