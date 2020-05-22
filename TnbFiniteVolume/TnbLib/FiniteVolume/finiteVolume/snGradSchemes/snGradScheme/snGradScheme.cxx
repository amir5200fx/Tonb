#include <snGradScheme.hxx>

#include <fv.hxx>
#include <snGradScheme.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<snGradScheme<Type> > snGradScheme<Type>::New
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				Info << "snGradScheme<Type>::New(const fvMesh&, Istream&)"
					" : constructing snGradScheme<Type>"
					<< endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorIn
				(
					"snGradScheme<Type>::New(const fvMesh&, Istream&)",
					schemeData
				) << "Discretisation scheme not specified"
					<< endl << endl
					<< "Valid schemes are :" << endl
					<< MeshConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			const word schemeName(schemeData);

			typename MeshConstructorTable::iterator constructorIter =
				MeshConstructorTablePtr_->find(schemeName);

			if (constructorIter == MeshConstructorTablePtr_->end())
			{
				FatalIOErrorIn
				(
					"snGradScheme<Type>::New(const fvMesh&, Istream&)",
					schemeData
				) << "Unknown discretisation scheme "
					<< schemeName << nl << nl
					<< "Valid schemes are :" << endl
					<< MeshConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return constructorIter()(mesh, schemeData);
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		snGradScheme<Type>::~snGradScheme()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			snGradScheme<Type>::snGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const tmp<surfaceScalarField>& tdeltaCoeffs,
				const word& snGradName
			)
		{
			const fvMesh& mesh = vf.mesh();

			// construct GeometricField<Type, fvsPatchField, surfaceMesh>
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > tssf
			(
				new GeometricField<Type, fvsPatchField, surfaceMesh>
				(
					IOobject
					(
						snGradName + "(" + vf.name() + ')',
						vf.instance(),
						vf.mesh(),
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					vf.dimensions()*tdeltaCoeffs().dimensions()
					)
			);
			GeometricField<Type, fvsPatchField, surfaceMesh>& ssf = tssf();

			// set reference to difference factors array
			const scalarField& deltaCoeffs = tdeltaCoeffs().internalField();

			// owner/neighbour addressing
			const unallocLabelList& owner = mesh.owner();
			const unallocLabelList& neighbour = mesh.neighbour();

			forAll(owner, faceI)
			{
				ssf[faceI] =
					deltaCoeffs[faceI] * (vf[neighbour[faceI]] - vf[owner[faceI]]);
			}

			forAll(vf.boundaryField(), patchI)
			{
				ssf.boundaryField()[patchI] = vf.boundaryField()[patchI].snGrad();
			}

			return tssf;
		}


		//- Return the face-snGrad of the given cell field
		//  with explicit correction
		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			snGradScheme<Type>::snGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > tsf
				= snGrad(vf, deltaCoeffs(vf));

			if (corrected())
			{
				tsf() += correction(vf);
			}

			return tsf;
		}


		//- Return the face-snGrad of the given cell field
		//  with explicit correction
		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			snGradScheme<Type>::snGrad
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf
			) const
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > tinterpVf
				= snGrad(tvf());
			tvf.clear();
			return tinterpVf;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //