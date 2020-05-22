#include <fvmAdjDiv.hxx>

#include <adjConvectionScheme.hxx>
#include <volMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvm
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<fvMatrix<Type> >
			adjDiv
			(
				const volVectorField& Up,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::adjConvectionScheme<Type>::New
			(
				vf.mesh(),
				Up,
				vf.mesh().schemesDict().divScheme(name)
			)().fvmAdjDiv(Up, vf);
		}

		template<class Type>
		tmp<fvMatrix<Type> >
			adjDiv
			(
				const tmp<volVectorField>& tUp,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			tmp<fvMatrix<Type> > AdjDiv(fvm::adjDiv(tUp(), vf, name));
			tUp.clear();
			return AdjDiv;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			adjDiv
			(
				const volVectorField& Up,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::adjDiv(Up, vf, "adjDiv(" + Up.name() + ',' + vf.name() + ')');
		}

		template<class Type>
		tmp<fvMatrix<Type> >
			adjDiv
			(
				const tmp<volVectorField>& tUp,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type> > AdjDiv(fvm::adjDiv(tUp(), vf));
			tUp.clear();
			return AdjDiv;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvm

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //