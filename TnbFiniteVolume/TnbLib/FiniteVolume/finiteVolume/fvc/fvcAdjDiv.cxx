#include <fvcAdjDiv.hxx>

#include <fvMesh.hxx>
#include <fvcSurfaceIntegrate.hxx>
#include <adjConvectionScheme.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			adjDiv
			(
				const volVectorField& Up,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::template adjConvectionScheme<Type>::New
			(
				vf.mesh(),
				Up,
				vf.mesh().schemesDict().divScheme(name)
			)().fvcAdjDiv(Up, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			adjDiv
			(
				const tmp<volVectorField>& tUp,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > AdjDiv
			(
				fvc::adjDiv(tUp(), vf, name)
			);
			tUp.clear();
			return AdjDiv;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			adjDiv
			(
				const volVectorField& Up,
				const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > AdjDiv
			(
				fvc::adjDiv(Up, tvf(), name)
			);
			tvf.clear();
			return AdjDiv;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			adjDiv
			(
				const tmp<volVectorField>& tUp,
				const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > AdjDiv
			(
				fvc::adjDiv(tUp(), tvf(), name)
			);
			tUp.clear();
			tvf.clear();
			return AdjDiv;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			adjDiv
			(
				const volVectorField& Up,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvc::adjDiv
			(
				Up, vf, "adjDiv(" + Up.name() + ',' + vf.name() + ')'
			);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			adjDiv
			(
				const tmp<volVectorField>& tUp,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > AdjDiv
			(
				fvc::adjDiv(tUp(), vf)
			);
			tUp.clear();
			return AdjDiv;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			adjDiv
			(
				const volVectorField& Up,
				const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > AdjDiv
			(
				fvc::adjDiv(Up, tvf())
			);
			tvf.clear();
			return AdjDiv;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			adjDiv
			(
				const tmp<volVectorField>& tUp,
				const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > AdjDiv
			(
				fvc::adjDiv(tUp(), tvf())
			);
			tUp.clear();
			tvf.clear();
			return AdjDiv;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //