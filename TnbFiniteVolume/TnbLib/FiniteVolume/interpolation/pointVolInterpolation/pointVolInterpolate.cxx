#include <pointVolInterpolation.hxx>

#include <volFields.hxx>
#include <pointFields.hxx>
#include <primitiveMesh.hxx>
#include <emptyFvPatch.hxx>
#include <globalMeshData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::pointVolInterpolation::interpolate
(
	const GeometricField<Type, pointPatchField, pointMesh>& pf,
	GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
	if (debug)
	{
		Info << "pointVolInterpolation::interpolate("
			<< "const GeometricField<Type, pointPatchField, pointMesh>&, "
			<< "GeometricField<Type, fvPatchField, volMesh>&) : "
			<< "interpolating field from points to cells"
			<< endl;
	}

	const FieldField<Field, scalar>& weights = volWeights();
	const labelListList& cellPoints = vf.mesh().cellPoints();

	// Multiply pointField by weighting factor matrix to create volField
	forAll(cellPoints, cellI)
	{
		vf[cellI] = pTraits<Type>::zero;

		const labelList& curCellPoints = cellPoints[cellI];

		forAll(curCellPoints, cellPointI)
		{
			vf[cellI] +=
				weights[cellI][cellPointI] * pf[curCellPoints[cellPointI]];
		}
	}


	// Interpolate patch values: over-ride the internal values for the points
	// on the patch with the interpolated point values from the faces
	const fvBoundaryMesh& bm = vMesh().boundary();

	const PtrList<primitivePatchInterpolation>& pi = patchInterpolators();
	forAll(bm, patchI)
	{
		// If the patch is empty, skip it
		if
			(
				bm[patchI].type() != emptyFvPatch::typeName
				)
		{
			vf.boundaryField()[patchI] =
				pi[patchI].pointToFaceInterpolate
				(
					pf.boundaryField()[patchI].patchInternalField()
				);
		}
	}

	vf.correctBoundaryConditions();

	if (debug)
	{
		Info << "pointVolInterpolation::interpolate("
			<< "const GeometricField<Type, pointPatchField, pointMesh>&, "
			<< "GeometricField<Type, fvPatchField, volMesh>&) : "
			<< "finished interpolating field from points to cells"
			<< endl;
	}
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh> >
tnbLib::pointVolInterpolation::interpolate
(
	const GeometricField<Type, pointPatchField, pointMesh>& pf
) const
{
	// Construct tmp<pointField>
	tmp<GeometricField<Type, fvPatchField, volMesh> > tvf
	(
		new GeometricField<Type, fvPatchField, volMesh>
		(
			IOobject
			(
				"pointVolInterpolate(" + pf.name() + ')',
				pf.instance(),
				pf.db()
			),
			vMesh(),
			pf.dimensions()
			)
	);

	// Perform interpolation
	interpolate(pf, tvf());

	return tvf;
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh> >
tnbLib::pointVolInterpolation::interpolate
(
	const tmp<GeometricField<Type, pointPatchField, pointMesh> >& tpf
) const
{
	// Construct tmp<volField>
	tmp<GeometricField<Type, fvPatchField, volMesh> > tvf =
		interpolate(tpf());
	tpf.clear();
	return tvf;
}


// ************************************************************************* //