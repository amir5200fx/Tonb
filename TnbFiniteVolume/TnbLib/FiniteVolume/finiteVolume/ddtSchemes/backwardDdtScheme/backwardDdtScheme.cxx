#include <backwardDdtScheme.hxx>

#include <surfaceInterpolate.hxx>
#include <fvcDiv.hxx>
#include <fvMatrices.hxx>
#include <IOobject.hxx>
#include <fvPatchFields.hxx>
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
		scalar backwardDdtScheme<Type>::deltaT_() const
		{
			return mesh().time().deltaT().value();
		}


		template<class Type>
		scalar backwardDdtScheme<Type>::deltaT0_() const
		{
			return mesh().time().deltaT0().value();
		}


		template<class Type>
		template<class GeoField>
		scalar backwardDdtScheme<Type>::deltaT0_(const GeoField& vf) const
		{
			// Bug fix, Zeljko Tukovic: solver with outer iterations over a time-step
			// HJ, 12/Feb/2010
			if (vf.oldTime().timeIndex() == vf.oldTime().oldTime().timeIndex())
			{
				return GREAT;
			}
			else
			{
				return deltaT0_();
			}
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			backwardDdtScheme<Type>::fvcDdt
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

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_();

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

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

				tdtdt().internalField() = rDeltaT.value()*dt.value()*
					(
						coefft - (coefft0*mesh().V0() - coefft00 * mesh().V00()) / mesh().V()
						);

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
			backwardDdtScheme<Type>::fvcDdt
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

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(vf);

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

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
								coefft*vf.internalField() -
								(
									coefft0*vf.oldTime().internalField()*mesh().V0()
									- coefft00 * vf.oldTime().oldTime().internalField()
									*mesh().V00()
									) / mesh().V()
								),
							rDeltaT.value()*
							(
								coefft*vf.boundaryField() -
								(
									coefft0*vf.oldTime().boundaryField()
									- coefft00 * vf.oldTime().oldTime().boundaryField()
									)
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
							rDeltaT*
							(
								coefft*vf
								- coefft0 * vf.oldTime()
								+ coefft00 * vf.oldTime().oldTime()
								)
							)
						);
			}
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			backwardDdtScheme<Type>::fvcDdt
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

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(vf);

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

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
								coefft*vf.internalField() -
								(
									coefft0*vf.oldTime().internalField()*mesh().V0()
									- coefft00 * vf.oldTime().oldTime().internalField()
									*mesh().V00()
									) / mesh().V()
								),
							rDeltaT.value()*rho.value()*
							(
								coefft*vf.boundaryField() -
								(
									coefft0*vf.oldTime().boundaryField()
									- coefft00 * vf.oldTime().oldTime().boundaryField()
									)
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
							rDeltaT*rho*
							(
								coefft*vf
								- coefft0 * vf.oldTime()
								+ coefft00 * vf.oldTime().oldTime()
								)
							)
						);
			}
		}

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			backwardDdtScheme<Type>::fvcDdt
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

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(vf);

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

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
								coefft*rho.internalField()*vf.internalField() -
								(
									coefft0*rho.oldTime().internalField()
									*vf.oldTime().internalField()*mesh().V0()
									- coefft00 * rho.oldTime().oldTime().internalField()
									*vf.oldTime().oldTime().internalField()*mesh().V00()
									) / mesh().V()
								),
							rDeltaT.value()*
							(
								coefft*rho.boundaryField()*vf.boundaryField() -
								(
									coefft0*rho.oldTime().boundaryField()
									*vf.oldTime().boundaryField()
									- coefft00 * rho.oldTime().oldTime().boundaryField()
									*vf.oldTime().oldTime().boundaryField()
									)
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
							rDeltaT*
							(
								coefft*rho*vf
								- coefft0 * rho.oldTime()*vf.oldTime()
								+ coefft00 * rho.oldTime().oldTime()*vf.oldTime().oldTime()
								)
							)
						);
			}
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			backwardDdtScheme<Type>::fvmDdt
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

			scalar rDeltaT = 1.0 / deltaT_();

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(vf);

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

			fvm.diag() = (coefft*rDeltaT)*mesh().V();

			if (mesh().moving())
			{
				fvm.source() = rDeltaT *
					(
						coefft0*vf.oldTime().internalField()*mesh().V0()
						- coefft00 * vf.oldTime().oldTime().internalField()
						*mesh().V00()
						);
			}
			else
			{
				fvm.source() = rDeltaT * mesh().V()*
					(
						coefft0*vf.oldTime().internalField()
						- coefft00 * vf.oldTime().oldTime().internalField()
						);
			}

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			backwardDdtScheme<Type>::fvmDdt
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

			scalar rDeltaT = 1.0 / deltaT_();

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(vf);

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

			fvm.diag() = (coefft*rDeltaT*rho.value())*mesh().V();

			if (mesh().moving())
			{
				fvm.source() = rDeltaT * rho.value()*
					(
						coefft0*vf.oldTime().internalField()*mesh().V0()
						- coefft00 * vf.oldTime().oldTime().internalField()
						*mesh().V00()
						);
			}
			else
			{
				fvm.source() = rDeltaT * mesh().V()*rho.value()*
					(
						coefft0*vf.oldTime().internalField()
						- coefft00 * vf.oldTime().oldTime().internalField()
						);
			}

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			backwardDdtScheme<Type>::fvmDdt
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

			scalar rDeltaT = 1.0 / deltaT_();

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(vf);

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

			fvm.diag() = (coefft*rDeltaT)*rho.internalField()*mesh().V();

			if (mesh().moving())
			{
				fvm.source() = rDeltaT *
					(
						coefft0*rho.oldTime().internalField()
						*vf.oldTime().internalField()*mesh().V0()
						- coefft00 * rho.oldTime().oldTime().internalField()
						*vf.oldTime().oldTime().internalField()*mesh().V00()
						);
			}
			else
			{
				fvm.source() = rDeltaT * mesh().V()*
					(
						coefft0*rho.oldTime().internalField()
						*vf.oldTime().internalField()
						- coefft00 * rho.oldTime().oldTime().internalField()
						*vf.oldTime().oldTime().internalField()
						);
			}

			return tfvm;
		}


		template<class Type>
		tmp<typename backwardDdtScheme<Type>::fluxFieldType>
			backwardDdtScheme<Type>::fvcDdtPhiCorr
			(
				const volScalarField& rA,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			)
		{
			dimensionedScalar rDeltaT = 1.0 / mesh().time().deltaT();

			IOobject ddtIOobject
			(
				"ddtPhiCorr(" + rA.name() + ',' + U.name() + ',' + phi.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(U);

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

			return tmp<fluxFieldType>
				(
					new fluxFieldType
					(
						ddtIOobject,
						rDeltaT*this->fvcDdtPhiCoeff(U.oldTime(), phi.oldTime())
						*(
							fvc::interpolate(rA)
							*(
								coefft0*phi.oldTime()
								- coefft00 * phi.oldTime().oldTime()
								)
							- (
								fvc::interpolate
								(
									rA*
									(
										coefft0*U.oldTime()
										- coefft00 * U.oldTime().oldTime()
										)
								) & mesh().Sf()
								)
							)
					)
					);
		}


		template<class Type>
		tmp<typename backwardDdtScheme<Type>::fluxFieldType>
			backwardDdtScheme<Type>::fvcDdtPhiCorr
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

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(U);

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

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
							rDeltaT*this->fvcDdtPhiCoeff(U.oldTime(), phiAbs.oldTime())
							*(
								coefft0*fvc::interpolate(rA*rho.oldTime())
								*phiAbs.oldTime()
								- coefft00 * fvc::interpolate(rA*rho.oldTime().oldTime())
								*phiAbs.oldTime().oldTime()
								- (
									fvc::interpolate
									(
										rA*
										(
											coefft0*rho.oldTime()*U.oldTime()
											- coefft00 * rho.oldTime().oldTime()
											*U.oldTime().oldTime()
											)
									) & mesh().Sf()
									)
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
								*(
									coefft0*phiAbs.oldTime()
									/ fvc::interpolate(rho.oldTime())
									- coefft00 * phiAbs.oldTime().oldTime()
									/ fvc::interpolate(rho.oldTime().oldTime())
									)
								- (
									fvc::interpolate
									(
										rA*rho.oldTime()*
										(
											coefft0*U.oldTime()
											- coefft00 * U.oldTime().oldTime()
											)
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
							*this->fvcDdtPhiCoeff(rho.oldTime(), U.oldTime(), phiAbs.oldTime())
							*(
								fvc::interpolate(rA)
								*(
									coefft0*phiAbs.oldTime()
									- coefft00 * phiAbs.oldTime().oldTime()
									)
								- (
									fvc::interpolate
									(
										rA*
										(
											coefft0*U.oldTime()
											- coefft00 * U.oldTime().oldTime()
											)
									) & mesh().Sf()
									)
								)
						)
						);
			}
			else
			{
				FatalErrorIn
				(
					"backwardDdtScheme<Type>::fvcDdtPhiCorr"
				) << "dimensions of phiAbs are not correct"
					<< abort(FatalError);

				return fluxFieldType::null();
			}
		}


		template<class Type>
		tmp<surfaceScalarField> backwardDdtScheme<Type>::meshPhi
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		)
		{
			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(vf);

			// Coefficient for t-3/2 (between times 0 and 00)
			scalar coefft0_00 = deltaT / (deltaT + deltaT0);

			// Coefficient for t-1/2 (between times n and 0)
			scalar coefftn_0 = 1 + coefft0_00;

			return coefftn_0 * mesh().phi() - coefft0_00 * mesh().phi().oldTime();
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //