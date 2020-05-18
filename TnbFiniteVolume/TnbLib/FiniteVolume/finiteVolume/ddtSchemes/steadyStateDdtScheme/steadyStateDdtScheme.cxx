#include <steadyStateDdtScheme.hxx>

#include <fvcDiv.hxx>
#include <fvMatrices.hxx>
#include <GeometricFields.hxx>
#include <surfaceFields.hxx>
#include <tnbTime.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			steadyStateDdtScheme<Type>::fvcDdt
			(
				const dimensioned<Type>& dt
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh> >
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"ddt(" + dt.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<Type>
						(
							"0",
							dt.dimensions() / dimTime,
							pTraits<Type>::zero
							)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			steadyStateDdtScheme<Type>::fvcDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh> >
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"ddt(" + vf.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<Type>
						(
							"0",
							vf.dimensions() / dimTime,
							pTraits<Type>::zero
							)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			steadyStateDdtScheme<Type>::fvcDdt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh> >
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"ddt(" + rho.name() + ',' + vf.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<Type>
						(
							"0",
							rho.dimensions()*vf.dimensions() / dimTime,
							pTraits<Type>::zero
							)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			steadyStateDdtScheme<Type>::fvcDdt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh> >
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"ddt(" + rho.name() + ',' + vf.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<Type>
						(
							"0",
							rho.dimensions()*vf.dimensions() / dimTime,
							pTraits<Type>::zero
							)
						)
					);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			steadyStateDdtScheme<Type>::fvmDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type> > tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					vf.dimensions()*dimVol / dimTime
					)
			);

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			steadyStateDdtScheme<Type>::fvmDdt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type> > tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					rho.dimensions()*vf.dimensions()*dimVol / dimTime
					)
			);

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			steadyStateDdtScheme<Type>::fvmDdt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type> > tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					rho.dimensions()*vf.dimensions()*dimVol / dimTime
					)
			);

			return tfvm;
		}


		template<class Type>
		tmp<typename steadyStateDdtScheme<Type>::fluxFieldType>
			steadyStateDdtScheme<Type>::fvcDdtPhiCorr
			(
				const volScalarField& rA,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			)
		{
			return tmp<fluxFieldType>
				(
					new fluxFieldType
					(
						IOobject
						(
							"ddtPhiCorr("
							+ rA.name() + ',' + U.name() + ',' + phi.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<typename flux<Type>::type>
						(
							"zero",
							rA.dimensions()*phi.dimensions() / dimTime,
							pTraits<typename flux<Type>::type>::zero
							)
					)
					);
		}


		template<class Type>
		tmp<typename steadyStateDdtScheme<Type>::fluxFieldType>
			steadyStateDdtScheme<Type>::fvcDdtPhiCorr
			(
				const volScalarField& rA,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			)
		{
			if
				(
					U.dimensions() == dimVelocity
					&& phi.dimensions() == dimVelocity * dimArea
					)
			{
				return tmp<fluxFieldType>
					(
						new fluxFieldType
						(
							IOobject
							(
								"ddtPhiCorr("
								+ rA.name() + ',' + rho.name()
								+ ',' + U.name() + ',' + phi.name() + ')',
								mesh().time().timeName(),
								mesh()
							),
							mesh(),
							dimensioned<typename flux<Type>::type>
							(
								"zero",
								rA.dimensions()*rho.dimensions()*phi.dimensions() / dimTime,
								pTraits<typename flux<Type>::type>::zero
								)
						)
						);
			}
			else if
				(
					U.dimensions() == dimVelocity
					&& phi.dimensions() == rho.dimensions()*dimVelocity*dimArea
					)
			{
				return tmp<fluxFieldType>
					(
						new fluxFieldType
						(
							IOobject
							(
								"ddtPhiCorr("
								+ rA.name() + ',' + rho.name()
								+ ',' + U.name() + ',' + phi.name() + ')',
								mesh().time().timeName(),
								mesh()
							),
							mesh(),
							dimensioned<typename flux<Type>::type>
							(
								"zero",
								rA.dimensions()*phi.dimensions() / dimTime,
								pTraits<typename flux<Type>::type>::zero
								)
						)
						);
			}
			else
			{
				FatalErrorIn
				(
					"steadyStateDdtScheme<Type>::fvcDdtPhiCorr"
				) << "dimensions of phi are not correct"
					<< abort(FatalError);

				return fluxFieldType::null();
			}
		}


		template<class Type>
		tmp<surfaceScalarField> steadyStateDdtScheme<Type>::meshPhi
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		)
		{
			return tmp<surfaceScalarField>
				(
					new surfaceScalarField
					(
						IOobject
						(
							"meshPhi",
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensionedScalar("0", dimVolume / dimTime, 0.0)
					)
					);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //