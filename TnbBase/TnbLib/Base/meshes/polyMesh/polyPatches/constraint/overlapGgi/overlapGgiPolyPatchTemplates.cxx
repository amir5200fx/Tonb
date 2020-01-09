#include <overlapGgiPolyPatch.hxx>

#include <RodriguesRotation.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type> >
tnbLib::overlapGgiPolyPatch::expandData(const Field<Type>& pf) const
{
	// Check and expand the field from patch size to zone size
	if (pf.size() != size())
	{
		FatalErrorIn
		(
			"tmp<Field<Type> > overlapGgiPolyPatch::expandData"
			"("
			"    const Field<Type>& pf"
			") const"
		) << "Incorrect patch field size.  Field size: "
			<< pf.size() << " patch size: " << size()
			<< abort(FatalError);
	}

	const label ncp = nCopies();

	const scalar myAngle = 360.0 / scalar(ncp);

	tmp<Field<Type> > texpandField
	(
		new Field<Type>(ncp*zone().size(), pTraits<Type>::zero)
	);

	Field<Type>& expandField = texpandField();

	for (label copyI = 0; copyI < ncp; copyI++)
	{
		// Calculate transform
		const tensor curRotation =
			RodriguesRotation(rotationAxis_, copyI*myAngle);

		const label offset = copyI * zone().size();

		forAll(pf, faceI)
		{
			const label zId = zone().whichFace(start() + faceI);
			expandField[offset + zId] = transform(curRotation, pf[faceI]);
		}
	}

	if (!localParallel())
	{
		reduce(expandField, sumOp<Field<Type> >());
	}

	return texpandField;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type> >
tnbLib::overlapGgiPolyPatch::interpolate(const Field<Type>& pf) const
{
	// Check and expand the field from patch size to zone size
	if (pf.size() != shadow().size())
	{
		FatalErrorIn
		(
			"tmp<Field<Type> > ggiPolyPatch::interpolate"
			"("
			"    const Field<Type>& pf"
			") const"
		) << "Incorrect slave patch field size.  Field size: "
			<< pf.size() << " patch size: " << shadow().size()
			<< abort(FatalError);
	}

	// Expand data
	tmp<Field<Type> > expanddata = shadow().expandData(pf);

	tmp<Field<Type> > tresult(new Field<Type>());
	Field<Type>& result = tresult();

	if (master())
	{
		// Expand slave data
		result = patchToPatch().slaveToMaster(expanddata);
	}
	else
	{
		// Expand master data
		result = patchToPatch().masterToSlave(expanddata);
	}

	// Truncate to size
	result.setSize(size());

	return tresult;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type> >
tnbLib::overlapGgiPolyPatch::interpolate(const tmp<Field<Type> >& tpf) const
{
	tmp<Field<Type> > tint = interpolate(tpf());
	tpf.clear();
	return tint;
}


// ************************************************************************* //