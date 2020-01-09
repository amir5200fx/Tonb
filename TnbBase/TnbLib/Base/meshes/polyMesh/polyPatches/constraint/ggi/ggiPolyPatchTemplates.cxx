#include <ggiPolyPatch.hxx>

#include <OSspecific.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::ggiPolyPatch::fastExpand
(
	const Field<Type>& ff
) const
{
	// Check and expand the field from patch size to zone size
	// with communication
	if (ff.size() != size())
	{
		FatalErrorIn
		(
			"tmp<Field<Type> > ggiPolyPatch::fastExpand\n"
			"(\n"
			"    const Field<Type>& ff\n"
			") const"
		) << "Incorrect patch field size.  Field size: "
			<< ff.size() << " patch size: " << size()
			<< abort(FatalError);
	}

	if (localParallel())
	{
		FatalErrorIn
		(
			"tmp<Field<Type> > ggiPolyPatch::fastExpand"
			"("
			"    const Field<Type>& ff"
			") const"
		) << "Requested expand on local parallel.  This is not allowed"
			<< abort(FatalError);
	}

	// Replaced old comms algorithm.  HJ, 31/May/2016
	// HJ, 4/Jun/2011

	// HR, 10/Jul/2013
	// This function requires send-receive-addressing, but usage is not
	// symmetric across processors. Hence trigger re-calculate at this point
	if (Pstream::parRun() && !localParallel())
	{
		map();
		shadow().map();
	}

	// New version: mapDistribute

	if (Pstream::parRun())
	{
		// Optimised mapDistribute

		// Prepare return field: expand the field to zone size
		tmp<Field<Type> > texpandField
		(
			new Field<Type>(ff)
		);
		Field<Type>& expandField = texpandField();

		map().distribute(expandField);

		return texpandField;
	}
	else
	{
		// Serial.  Expand the field to zone size

		tmp<Field<Type> > texpandField
		(
			new Field<Type>(zone().size())  // filled with nans
		);
		Field<Type>& expandField = texpandField();

		const labelList& zAddr = zoneAddressing();

		forAll(zAddr, i)
		{
			expandField[zAddr[i]] = ff[i];
		}

		return texpandField;
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::ggiPolyPatch::interpolate
(
	const Field<Type>& ff
) const
{
	// Check and expand the field from patch size to zone size
	if (ff.size() != shadow().size())
	{
		FatalErrorIn
		(
			"tmp<Field<Type> > ggiPolyPatch::interpolate\n"
			"(\n"
			"    const Field<Type>& ff\n"
			") const"
		) << "Incorrect slave patch field size.  Field size: "
			<< ff.size() << " patch size: " << shadow().size()
			<< abort(FatalError);
	}

	// New.  HJ, 12/Jun/2011
	if (localParallel())
	{
		// No expansion or filtering needed.  HJ, 4/Jun/2011

		if (empty())
		{
			// Patch empty, no interpolation
			return tmp<Field<Type> >(new Field<Type>());
		}

		// Interpolate field
		if (master())
		{
			return patchToPatch().slaveToMaster(ff);
		}
		else
		{
			return patchToPatch().masterToSlave(ff);
		}
	}
	else
	{
		// Expand shadow
		Field<Type> expandField = shadow().fastExpand(ff);

		tmp<Field<Type> > tresult(new Field<Type>(size()));
		Field<Type>& result = tresult();

		if (master())
		{
			patchToPatch().maskedSlaveToMaster
			(
				expandField,
				result,
				zoneAddressing()
			);
		}
		else
		{
			patchToPatch().maskedMasterToSlave
			(
				expandField,
				result,
				zoneAddressing()
			);
		}

		return tresult;
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::ggiPolyPatch::interpolate
(
	const tmp<Field<Type> >& tff
) const
{
	tmp<Field<Type> > tint = interpolate(tff());
	tff.clear();
	return tint;
}


template<class Type>
void tnbLib::ggiPolyPatch::bridge
(
	const Field<Type>& bridgeField,
	Field<Type>& ff
) const
{
	// Check and expand the field from patch size to zone size
	if (ff.size() != size())
	{
		FatalErrorIn
		(
			"tmp<Field<Type> > ggiPolyPatch::bridge\n"
			"(\n"
			"    const Field<Type>& ff,\n"
			"    Field<Type>& ff\n"
			") const"
		) << "Incorrect patch field size for bridge.  Field size: "
			<< ff.size() << " patch size: " << size()
			<< abort(FatalError);
	}

	if (bridgeOverlap())
	{
		if (empty())
		{
			// Patch empty, no bridging
			return;
		}

		if (localParallel())
		{
			if (master())
			{
				patchToPatch().bridgeMaster(bridgeField, ff);
			}
			else
			{
				patchToPatch().bridgeSlave(bridgeField, ff);
			}
		}
		else
		{
			// Note: since bridging is only a local operation
			if (master())
			{
				patchToPatch().maskedBridgeMaster
				(
					bridgeField,
					ff,
					zoneAddressing()
				);
			}
			else
			{
				patchToPatch().maskedBridgeSlave
				(
					bridgeField,
					ff,
					zoneAddressing()
				);
			}
		}
	}
}


// ************************************************************************* //