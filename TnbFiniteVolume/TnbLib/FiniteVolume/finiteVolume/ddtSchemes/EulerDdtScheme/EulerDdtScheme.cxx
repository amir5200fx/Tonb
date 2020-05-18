#include <EulerDdtScheme.hxx>

#include <surfaceInterpolate.hxx>
#include <fvcDiv.hxx>
#include <fvMatrices.hxx>
#include <IOobject.hxx>
#include <dimensionSet.hxx>
#include <dimensionedTypes.hxx>
#include <GeometricFields.hxx>
#include <tnbTime.hxx>
#include <FieldFields.hxx>
#include <FieldFieldFunctions.hxx>
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
			EulerDdtScheme<Type>::fvcDdt
			(
				const dimensioned<Type>& dt
			)
		{
			dimensionedScalar rDeltaT = 1.0 / mesh().time().deltaT();

			IOobject ddtIOobject
			(
				"ddt(" + dt.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			if (mesh().moving())
			{
				tmp<GeometricField<Type, fvPatchField, volMesh> > tdtdt
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						ddtIOobject,
						mesh(),
						dimensioned<Type>
						(
							"0",
							dt.dimensions() / dimTime,
							pTraits<Type>::zero
							)
						)
				);

				tdtdt().internalField() =
					rDeltaT.value()*dt.value()*(1.0 - mesh().V0() / mesh().V());

				return tdtdt;
			}
			else
			{
				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							ddtIOobject,
							mesh(),
							dimensioned<Type>
							(
								"0",
								dt.dimensions() / dimTime,
								pTraits<Type>::zero
								),
							calculatedFvPatchField<Type>::typeName
							)
						);
			}
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			EulerDdtScheme<Type>::fvcDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			dimensionedScalar rDeltaT = 1.0 / mesh().time().deltaT();

			IOobject ddtIOobject
			(
				"ddt(" + vf.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			if (mesh().moving())
			{
				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							ddtIOobject,
							mesh(),
							rDeltaT.dimensions()*vf.dimensions(),
							rDeltaT.value()*
							(
								vf.internalField()
								- vf.oldTime().internalField()*mesh().V0() / mesh().V()
								),
							rDeltaT.value()*
							(
								vf.boundaryField() - vf.oldTime().boundaryField()
								)
							)
						);
			}
			else
			{
				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							ddtIOobject,
							rDeltaT*(vf - vf.oldTime())
							)
						);
			}
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			EulerDdtScheme<Type>::fvcDdt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			dimensionedScalar rDeltaT = 1.0 / mesh().time().deltaT();

			IOobject ddtIOobject
			(
				"ddt(" + rho.name() + ',' + vf.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			if (mesh().moving())
			{
				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							ddtIOobject,
							mesh(),
							rDeltaT.dimensions()*rho.dimensions()*vf.dimensions(),
							rDeltaT.value()*rho.value()*
							(
								vf.internalField()
								- vf.oldTime().internalField()*mesh().V0() / mesh().V()
								),
							rDeltaT.value()*rho.value()*
							(
								vf.boundaryField() - vf.oldTime().boundaryField()
								)
							)
						);
			}
			else
			{
				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							ddtIOobject,
							rDeltaT*rho*(vf - vf.oldTime())
							)
						);
			}
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			EulerDdtScheme<Type>::fvcDdt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			dimensionedScalar rDeltaT = 1.0 / mesh().time().deltaT();

			IOobject ddtIOobject
			(
				"ddt(" + rho.name() + ',' + vf.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			if (mesh().moving())
			{
				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							ddtIOobject,
							mesh(),
							rDeltaT.dimensions()*rho.dimensions()*vf.dimensions(),
							rDeltaT.value()*
							(
								rho.internalField()*vf.internalField()
								- rho.oldTime().internalField()
								*vf.oldTime().internalField()*mesh().V0() / mesh().V()
								),
							rDeltaT.value()*
							(
								rho.boundaryField()*vf.boundaryField()
								- rho.oldTime().boundaryField()
								*vf.oldTime().boundaryField()
								)
							)
						);
			}
			else
			{
				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							ddtIOobject,
							rDeltaT*(rho*vf - rho.oldTime()*vf.oldTime())
							)
						);
			}
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			EulerDdtScheme<Type>::fvmDdt
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

			fvMatrix<Type>& fvm = tfvm();

			scalar rDeltaT = 1.0 / mesh().time().deltaT().value();

			fvm.diag() = rDeltaT * mesh().V();

			if (mesh().moving())
			{
				fvm.source() = rDeltaT * vf.oldTime().internalField()*mesh().V0();
			}
			else
			{
				fvm.source() = rDeltaT * vf.oldTime().internalField()*mesh().V();
			}

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			EulerDdtScheme<Type>::fvmDdt
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
			fvMatrix<Type>& fvm = tfvm();

			scalar rDeltaT = 1.0 / mesh().time().deltaT().value();

			fvm.diag() = rDeltaT * rho.value()*mesh().V();

			if (mesh().moving())
			{
				fvm.source() = rDeltaT
					* rho.value()*vf.oldTime().internalField()*mesh().V0();
			}
			else
			{
				fvm.source() = rDeltaT
					* rho.value()*vf.oldTime().internalField()*mesh().V();
			}

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			EulerDdtScheme<Type>::fvmDdt
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
			fvMatrix<Type>& fvm = tfvm();

			scalar rDeltaT = 1.0 / mesh().time().deltaT().value();

			fvm.diag() = rDeltaT * rho.internalField()*mesh().V();

			if (mesh().moving())
			{
				fvm.source() = rDeltaT
					* rho.oldTime().internalField()
					*vf.oldTime().internalField()*mesh().V0();
			}
			else
			{
				fvm.source() = rDeltaT
					* rho.oldTime().internalField()
					*vf.oldTime().internalField()*mesh().V();
			}

			return tfvm;
		}


		template<class Type>
		tmp<typename EulerDdtScheme<Type>::fluxFieldType>
			EulerDdtScheme<Type>::fvcDdtPhiCorr
			(
				const volScalarField& rA,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phiAbs
			)
		{
			dimensionedScalar rDeltaT = 1.0 / mesh().time().deltaT();

			IOobject ddtIOobject
			(
				"ddtPhiCorr(" + rA.name() + ',' + U.name() + ',' + phiAbs.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			tmp<fluxFieldType> phiCorr =
				phiAbs.oldTime() - (fvc::interpolate(U.oldTime()) & mesh().Sf());

			return tmp<fluxFieldType>
				(
					new fluxFieldType
					(
						ddtIOobject,
						this->fvcDdtPhiCoeff(U.oldTime(), phiAbs.oldTime(), phiCorr())
						*fvc::interpolate(rDeltaT*rA)*phiCorr
					)
					);
		}


		template<class Type>
		tmp<typename EulerDdtScheme<Type>::fluxFieldType>
			EulerDdtScheme<Type>::fvcDdtPhiCorr
			(
				const volScalarField& rA,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phiAbs
			)
		{
			dimensionedScalar rDeltaT = 1.0 / mesh().time().deltaT();

			IOobject ddtIOobject
			(
				"ddtPhiCorr("
				+ rA.name() + ','
				+ rho.name() + ','
				+ U.name() + ','
				+ phiAbs.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			if
				(
					U.dimensions() == dimVelocity
					&& phiAbs.dimensions() == dimVelocity * dimArea
					)
			{
				return tmp<fluxFieldType>
					(
						new fluxFieldType
						(
							ddtIOobject,
							rDeltaT
							*this->fvcDdtPhiCoeff(U.oldTime(), phiAbs.oldTime())
							*(
								fvc::interpolate(rA*rho.oldTime())*phiAbs.oldTime()
								- (fvc::interpolate(rA*rho.oldTime()*U.oldTime())
									& mesh().Sf())
								)
						)
						);
			}
			else if
				(
					U.dimensions() == dimVelocity
					&& phiAbs.dimensions() == rho.dimensions()*dimVelocity*dimArea
					)
			{
				return tmp<fluxFieldType>
					(
						new fluxFieldType
						(
							ddtIOobject,
							rDeltaT
							*this->fvcDdtPhiCoeff
							(
								U.oldTime(),
								phiAbs.oldTime() / fvc::interpolate(rho.oldTime())
							)
							*(
								fvc::interpolate(rA*rho.oldTime())
								*phiAbs.oldTime() / fvc::interpolate(rho.oldTime())
								- (
									fvc::interpolate
									(
										rA*rho.oldTime()*U.oldTime()
									) & mesh().Sf()
									)
								)
						)
						);
			}
			else if
				(
					U.dimensions() == rho.dimensions()*dimVelocity
					&& phiAbs.dimensions() == rho.dimensions()*dimVelocity*dimArea
					)
			{
				return tmp<fluxFieldType>
					(
						new fluxFieldType
						(
							ddtIOobject,
							rDeltaT
							*this->fvcDdtPhiCoeff
							(
								rho.oldTime(),
								U.oldTime(),
								phiAbs.oldTime()
							)
							*(
								fvc::interpolate(rA)*phiAbs.oldTime()
								- (fvc::interpolate(rA*U.oldTime()) & mesh().Sf())
								)
						)
						);
			}
			else
			{
				FatalErrorIn
				(
					"EulerDdtScheme<Type>::fvcDdtPhiCorr"
				) << "dimensions of phiAbs are not correct"
					<< abort(FatalError);

				return fluxFieldType::null();
			}
		}


		template<class Type>
		tmp<surfaceScalarField> EulerDdtScheme<Type>::meshPhi
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		)
		{
			return mesh().phi();
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //