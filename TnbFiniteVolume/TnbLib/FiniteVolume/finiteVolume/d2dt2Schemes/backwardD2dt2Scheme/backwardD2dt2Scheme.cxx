#include <backwardD2dt2Scheme.hxx>

#include <fvcDiv.hxx>
#include <fvMatrices.hxx>
#include <backwardDdtScheme.hxx>
#include <volMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		scalar backwardD2dt2Scheme<Type>::deltaT_() const
		{
			return mesh().time().deltaT().value();
		}


		template<class Type>
		scalar backwardD2dt2Scheme<Type>::deltaT0_() const
		{
			return mesh().time().deltaT0().value();
		}


		template<class Type>
		scalar backwardD2dt2Scheme<Type>::deltaT0_
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		) const
		{
			// Bug fix, Zeljko Tukovic: solver with outer iterations over a time-step
			// HJ, 12/Feb/2010
		//     if (vf.oldTime().timeIndex() == vf.oldTime().oldTime().timeIndex())
			if
				(
					vf.oldTime().oldTime().timeIndex()
					== vf.oldTime().oldTime().oldTime().timeIndex()
					)
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
			backwardD2dt2Scheme<Type>::fvcD2dt2
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			dimensionedScalar rDeltaT2 =
				4.0 / sqr(mesh().time().deltaT() + mesh().time().deltaT0());

			IOobject d2dt2IOobject
			(
				"d2dt2(" + vf.name() + ')',
				mesh().time().timeName(),
				mesh(),
				IOobject::NO_READ,
				IOobject::NO_WRITE
			);

			scalar deltaT = mesh().time().deltaT().value();
			scalar deltaT0 = mesh().time().deltaT0().value();

			scalar coefft = (deltaT + deltaT0) / (2 * deltaT);
			scalar coefft00 = (deltaT + deltaT0) / (2 * deltaT0);
			scalar coefft0 = coefft + coefft00;

			if (mesh().moving())
			{
				notImplemented
				(
					type()
					+ "::fvcD2dt2(const GeometricField<Type, fvPatchField, volMesh>& vf)"
				);

				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							d2dt2IOobject,
							rDeltaT2*
							(
								coefft*vf
								- coefft0 * vf.oldTime()
								+ coefft00 * vf.oldTime().oldTime()
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
							d2dt2IOobject,
							rDeltaT2*
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
			backwardD2dt2Scheme<Type>::fvcD2dt2
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			dimensionedScalar rDeltaT2 =
				4.0 / sqr(mesh().time().deltaT() + mesh().time().deltaT0());

			IOobject d2dt2IOobject
			(
				"d2dt2(" + rho.name() + ',' + vf.name() + ')',
				mesh().time().timeName(),
				mesh(),
				IOobject::NO_READ,
				IOobject::NO_WRITE
			);

			scalar deltaT = mesh().time().deltaT().value();
			scalar deltaT0 = mesh().time().deltaT0().value();

			scalar coefft = (deltaT + deltaT0) / (2 * deltaT);
			scalar coefft00 = (deltaT + deltaT0) / (2 * deltaT0);

			if (mesh().moving())
			{
				notImplemented
				(
					type()
					+ "::fvcD2dt2"
					+ "("
					+ "const volScalarField& rho, "
					+ "const GeometricField<Type, fvPatchField, volMesh>& vf"
					+ ")"
				);

				dimensionedScalar halfRdeltaT2 = 0.5*rDeltaT2;

				volScalarField rhoRho0 = rho + rho.oldTime();
				volScalarField rho0Rho00 = rho.oldTime() + rho.oldTime().oldTime();

				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							d2dt2IOobject,
							halfRdeltaT2*
							(
								coefft*rhoRho0*vf
								- (coefft*rhoRho0 + coefft00 * rho0Rho00)*vf.oldTime()
								+ coefft00 * rho0Rho00*vf.oldTime().oldTime()
								)
							)
						);
			}
			else
			{
				dimensionedScalar halfRdeltaT2 = 0.5*rDeltaT2;

				volScalarField rhoRho0 = rho + rho.oldTime();
				volScalarField rho0Rho00 = rho.oldTime() + rho.oldTime().oldTime();

				return tmp<GeometricField<Type, fvPatchField, volMesh> >
					(
						new GeometricField<Type, fvPatchField, volMesh>
						(
							d2dt2IOobject,
							halfRdeltaT2*
							(
								coefft*rhoRho0*vf
								- (coefft*rhoRho0 + coefft00 * rho0Rho00)*vf.oldTime()
								+ coefft00 * rho0Rho00*vf.oldTime().oldTime()
								)
							)
						);
			}
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			backwardD2dt2Scheme<Type>::fvmD2dt2
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type> > tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					vf.dimensions()*dimVol / dimTime / dimTime
					)
			);

			fvMatrix<Type>& fvm = tfvm();

			scalar rDeltaT = 1.0 / deltaT_();

			scalar deltaT = deltaT_();
			scalar deltaT0 = deltaT0_(vf);

			scalar coefft = 1 + deltaT / (deltaT + deltaT0);
			scalar coefft00 = deltaT * deltaT / (deltaT0*(deltaT + deltaT0));
			scalar coefft0 = coefft + coefft00;

			if (mesh().moving())
			{
				notImplemented
				(
					type()
					+ "::fvmD2dt2(const GeometricField<Type, fvPatchField, volMesh>& vf)"
				);
			}
			else
			{
				fvm = coefft * dimensionedScalar("rDeltaT", dimless / dimTime, rDeltaT)
					*backwardDdtScheme<Type>(mesh()).fvmDdt(vf);

				fvm.source() += rDeltaT * mesh().V()*
					(
						coefft0
						*backwardDdtScheme<Type>(mesh()).fvcDdt(vf.oldTime())
						().internalField()
						- coefft00
						* backwardDdtScheme<Type>(mesh()).fvcDdt(vf.oldTime().oldTime())
						().internalField()
						);
			}

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			backwardD2dt2Scheme<Type>::fvmD2dt2
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
					rho.dimensions()*vf.dimensions()*dimVol
					/ dimTime / dimTime
					)
			);

			fvMatrix<Type>& fvm = tfvm();

			scalar deltaT = mesh().time().deltaT().value();
			scalar deltaT0 = mesh().time().deltaT0().value();

			scalar coefft = (deltaT + deltaT0) / (2 * deltaT);
			scalar coefft00 = (deltaT + deltaT0) / (2 * deltaT0);

			scalar rDeltaT2 = 4.0 / sqr(deltaT + deltaT0);

			if (mesh().moving())
			{
				notImplemented
				(
					type()
					+ "::fvcD2dt2"
					+ "("
					+ "const dimensionedScalar& rho, "
					+ "const GeometricField<Type, fvPatchField, volMesh>& vf"
					+ ")"
				);
			}
			else
			{
				fvm.diag() = (coefft*rDeltaT2)*mesh().V()*rho.value();

				fvm.source() = rDeltaT2 * mesh().V()*rho.value()*
					(
					(coefft + coefft00)*vf.oldTime().internalField()
						- coefft00 * vf.oldTime().oldTime().internalField()
						);
			}

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			backwardD2dt2Scheme<Type>::fvmD2dt2
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
					rho.dimensions()*vf.dimensions()*dimVol
					/ dimTime / dimTime
					)
			);

			fvMatrix<Type>& fvm = tfvm();

			scalar deltaT = mesh().time().deltaT().value();
			scalar deltaT0 = mesh().time().deltaT0().value();

			scalar coefft = (deltaT + deltaT0) / (2 * deltaT);
			scalar coefft00 = (deltaT + deltaT0) / (2 * deltaT0);

			scalar rDeltaT2 = 4.0 / sqr(deltaT + deltaT0);

			if (mesh().moving())
			{
				notImplemented
				(
					type()
					+ "::fvmD2dt2"
					+ "("
					+ "const volScalarField& rho, "
					+ "const GeometricField<Type, fvPatchField, volMesh>& vf"
					+ ")"
				);
			}
			else
			{
				scalar halfRdeltaT2 = 0.5*rDeltaT2;

				scalarField rhoRho0 =
					(rho.internalField() + rho.oldTime().internalField());

				scalarField rho0Rho00 =
					(
						rho.oldTime().internalField()
						+ rho.oldTime().oldTime().internalField()
						);

				fvm.diag() = (coefft*halfRdeltaT2)*mesh().V()*rhoRho0;

				fvm.source() = halfRdeltaT2 * mesh().V()*
					(
					(coefft*rhoRho0 + coefft00 * rho0Rho00)
						*vf.oldTime().internalField()

						- (coefft00*rho0Rho00)
						*vf.oldTime().oldTime().internalField()
						);
			}

			return tfvm;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //