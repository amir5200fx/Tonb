#include <GGIInterpolationTemplate.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::interpolate
	(
		const Field<Type>& ff,
		Field<Type>& result,
		const labelListList& addr,
		const scalarListList& weights
	)
	{
		forAll(result, faceI)
		{
			const labelList& curAddr = addr[faceI];
			const scalarList& curWeights = weights[faceI];

			result[faceI] = pTraits<Type>::zero;

			forAll(curAddr, i)
			{
				result[faceI] += ff[curAddr[i]] * curWeights[i];
			}
		}
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::maskedInterpolate
	(
		const Field<Type>& ff,
		Field<Type>& result,
		const labelList& mask,
		const labelListList& addr,
		const scalarListList& weights
	)
	{
		forAll(mask, maskI)
		{
			// Pick the masked face
			const label faceI = mask[maskI];

			const labelList& curAddr = addr[faceI];

			const scalarList& curWeights = weights[faceI];

			// Clear condensed list entry: masked faces only
			result[maskI] = pTraits<Type>::zero;

			forAll(curAddr, i)
			{
				// Put the result into condensed list: masked faces only
				result[maskI] += ff[curAddr[i]] * curWeights[i];
			}
		}
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::bridge
	(
		const Field<Type>& bridgeField,
		Field<Type>& ff,
		const labelList& addr
	)
	{
		forAll(addr, faceI)
		{
			ff[addr[faceI]] = bridgeField[addr[faceI]];
		}
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::maskedBridge
	(
		const Field<Type>& bridgeField,
		Field<Type>& ff,
		const labelList& mask,
		const labelList& uncoveredFaces
	)
	{
		// Note: tricky algorithm
		// In order for a face to be bridged it needs to be both in the
		// mask and in selection of faces that are bridged (addr).
		// This implies an n-squared search, but we can avoid it by
		// using the fact that both lists are ordered.

		label maskAddrI = 0;

		forAll(uncoveredFaces, uncoI)
		{
			// Pick the uncovered face
			const label faceI = uncoveredFaces[uncoI];

			// Search through the mask
			for (; maskAddrI < mask.size(); maskAddrI++)
			{
				if (faceI == mask[maskAddrI])
				{
					// Found masked bridged face
					// Put the result into condensed list: masked faces only
					ff[maskAddrI] = bridgeField[maskAddrI];

					break;
				}
				else if (mask[maskAddrI] > faceI)
				{
					// Gone beyond my index: my face is not present in the mask
					// Go one back and check for next uncovered face
					if (maskAddrI > 0)
					{
						maskAddrI--;
					}

					break;
				}
			}
		}
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class MasterPatch, class SlavePatch>
	template<class Type>
	tmp<Field<Type> >
		GGIInterpolation<MasterPatch, SlavePatch>::masterToSlave
		(
			const Field<Type>& ff
		) const
	{
		if (ff.size() != masterPatch_.size())
		{
			FatalErrorIn
			(
				"GGIInterpolation::masterToSlave(const Field<Type> ff)"
			) << "given field does not correspond to patch. Patch size: "
				<< masterPatch_.size() << " field size: " << ff.size()
				<< abort(FatalError);
		}

		tmp<Field<Type> > tresult
		(
			new Field<Type>
			(
				slavePatch_.size(),
				pTraits<Type>::zero
				)
		);

		// Do interpolation
		Field<Type>& result = tresult();

		if (this->doTransform() && pTraits<Type>::rank > 0)
		{
			// Transform master data to slave
			Field<Type> transformFF;

			if (reverseT_.size() == 1)
			{
				// Constant transform
				transformFF = transform(reverseT_[0], ff);
			}
			else
			{
				// Full patch transform
				transformFF = transform(reverseT_, ff);
			}

			GGIInterpolation<MasterPatch, SlavePatch>::interpolate
			(
				transformFF,
				result,
				this->slaveAddr(),
				this->slaveWeights()
			);
		}
		else
		{
			GGIInterpolation<MasterPatch, SlavePatch>::interpolate
			(
				ff,
				result,
				this->slaveAddr(),
				this->slaveWeights()
			);
		}

		return tresult;
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	tmp<Field<Type> >
		GGIInterpolation<MasterPatch, SlavePatch>::masterToSlave
		(
			const tmp<Field<Type> >& tff
		) const
	{
		tmp<Field<Type> > tint = masterToSlave(tff());
		tff.clear();
		return tint;
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::maskedMasterToSlave
	(
		const Field<Type>& ff,
		Field<Type>& result,
		const labelList& mask
	) const
	{
		if (ff.size() != masterPatch_.size())
		{
			FatalErrorIn
			(
				"void GGIInterpolation::maskedMasterToSlave\n"
				"(\n"
				"    const Field<Type>& ff,\n"
				"    Field<Type>& result,\n"
				"    const labelList& mask\n"
				") const"
			) << "given field does not correspond to patch. Patch size: "
				<< masterPatch_.size() << " field size: " << ff.size()
				<< abort(FatalError);
		}

		if (result.size() != mask.size())
		{
			FatalErrorIn
			(
				"void GGIInterpolation::maskedMasterToSlave\n"
				"(\n"
				"    const Field<Type>& ff,\n"
				"    Field<Type>& result,\n"
				"    const labelList& mask\n"
				") const"
			) << "result field does not correspond to mask. Field size: "
				<< result.size() << " mask size: " << mask.size()
				<< abort(FatalError);
		}

		if (this->doTransform() && pTraits<Type>::rank > 0)
		{
			// Transform master data to slave
			Field<Type> transformFF(ff.size());

			if (reverseT_.size() == 1)
			{
				// Constant transform
				// Transform only masked elements.  HJ, 25/May/2016
				forAll(mask, maskI)
				{
					transformFF[mask[maskI]] =
						transform(reverseT_[0], ff[mask[maskI]]);
				}
			}
			else
			{
				// Full patch transform
				// Transform only masked elements.  HJ, 25/May/2016
				forAll(mask, maskI)
				{
					transformFF[mask[maskI]] =
						transform(reverseT_[mask[maskI]], ff[mask[maskI]]);
				}
			}

			GGIInterpolation<MasterPatch, SlavePatch>::maskedInterpolate
			(
				transformFF,
				result,
				mask,
				this->slaveAddr(),
				this->slaveWeights()
			);
		}
		else
		{
			GGIInterpolation<MasterPatch, SlavePatch>::maskedInterpolate
			(
				ff,
				result,
				mask,
				this->slaveAddr(),
				this->slaveWeights()
			);
		}
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	tmp<Field<Type> >
		GGIInterpolation<MasterPatch, SlavePatch>::slaveToMaster
		(
			const Field<Type>& ff
		) const
	{
		if (ff.size() != slavePatch_.size())
		{
			FatalErrorIn
			(
				"GGIInterpolation::slaveToMaster"
				"(const Field<Type> ff)"
			) << "given field does not correspond to patch. Patch size: "
				<< slavePatch_.size() << " field size: " << ff.size()
				<< abort(FatalError);
		}

		tmp<Field<Type> > tresult
		(
			new Field<Type>
			(
				masterPatch_.size(),
				pTraits<Type>::zero
				)
		);

		// Do interpolation
		Field<Type>& result = tresult();

		if (this->doTransform() && pTraits<Type>::rank > 0)
		{
			// Transform slave data to master
			Field<Type> transformFF;
			if (forwardT_.size() == 1)
			{
				// Constant transform
				transformFF = transform(forwardT_[0], ff);
			}
			else
			{
				// Full patch transform
				transformFF = transform(forwardT_, ff);
			}

			GGIInterpolation<MasterPatch, SlavePatch>::interpolate
			(
				transformFF,
				result,
				this->masterAddr(),
				this->masterWeights()
			);
		}
		else
		{
			GGIInterpolation<MasterPatch, SlavePatch>::interpolate
			(
				ff,
				result,
				this->masterAddr(),
				this->masterWeights()
			);
		}

		return tresult;
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	tmp<Field<Type> >
		GGIInterpolation<MasterPatch, SlavePatch>::slaveToMaster
		(
			const tmp<Field<Type> >& tff
		) const
	{
		tmp<Field<Type> > tint = slaveToMaster(tff());
		tff.clear();
		return tint;
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::maskedSlaveToMaster
	(
		const Field<Type>& ff,
		Field<Type>& result,
		const labelList& mask
	) const
	{
		if (ff.size() != slavePatch_.size())
		{
			FatalErrorIn
			(
				"void GGIInterpolation::maskedSlaveToMaster"
				"(\n"
				"    const Field<Type>& ff,\n"
				"    Field<Type>& result,\n"
				"    const labelList& mask\n"
				") const"
			) << "given field does not correspond to patch. Patch size: "
				<< slavePatch_.size() << " field size: " << ff.size()
				<< abort(FatalError);
		}

		if (result.size() != mask.size())
		{
			FatalErrorIn
			(
				"void GGIInterpolation::maskedSlaveToMaster\n"
				"(\n"
				"    const Field<Type>& ff,\n"
				"    Field<Type>& result,\n"
				"    const labelList& mask\n"
				") const"
			) << "result field does not correspond to mask. Field size: "
				<< result.size() << " mask size: " << mask.size()
				<< abort(FatalError);
		}

		if (this->doTransform() && pTraits<Type>::rank > 0)
		{
			// Transform slave data to master
			Field<Type> transformFF(ff.size());
			if (forwardT_.size() == 1)
			{
				// Constant transform
				// Transform only masked elements.  HJ, 25/May/2016
				forAll(mask, maskI)
				{
					transformFF[mask[maskI]] =
						transform(forwardT_[0], ff[mask[maskI]]);
				}
			}
			else
			{
				// Full patch transform
				// Transform only masked elements.  HJ, 25/May/2016
				forAll(mask, maskI)
				{
					transformFF[mask[maskI]] =
						transform(forwardT_[mask[maskI]], ff[mask[maskI]]);
				}
			}

			GGIInterpolation<MasterPatch, SlavePatch>::maskedInterpolate
			(
				transformFF,
				result,
				mask,
				this->masterAddr(),
				this->masterWeights()
			);
		}
		else
		{
			GGIInterpolation<MasterPatch, SlavePatch>::maskedInterpolate
			(
				ff,
				result,
				mask,
				this->masterAddr(),
				this->masterWeights()
			);
		}
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::bridgeMaster
	(
		const Field<Type>& bridgeField,
		Field<Type>& ff
	) const
	{
		if
			(
				bridgeField.size() != masterPatch_.size()
				|| ff.size() != masterPatch_.size())
		{
			FatalErrorIn
			(
				"void GGIInterpolation<MasterPatch, SlavePatch>::bridgeMaster\n"
				"(\n"
				"    const Field<Type>& bridgeField,\n"
				"    Field<Type>& ff\n"
				") const"
			) << "given field does not correspond to patch. Patch size: "
				<< masterPatch_.size()
				<< " bridge field size: " << bridgeField.size()
				<< " field size: " << ff.size()
				<< abort(FatalError);
		}

		bridge(bridgeField, ff, uncoveredMasterFaces());
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::maskedBridgeMaster
	(
		const Field<Type>& bridgeField,
		Field<Type>& ff,
		const labelList& mask
	) const
	{
		if (ff.size() != mask.size())
		{
			FatalErrorIn
			(
				"void GGIInterpolation<MasterPatch, SlavePatch>::"
				"maskedBridgeMaster\n"
				"(\n"
				"    const Field<Type>& bridgeField,\n"
				"    Field<Type>& ff,\n"
				"    const labelList& mask\n"
				") const"
			) << "given field does not correspond to patch. Patch size: "
				<< masterPatch_.size()
				<< " bridge field size: " << bridgeField.size()
				<< " field size: " << ff.size()
				<< " mask size: " << mask.size()
				<< abort(FatalError);
		}

		maskedBridge(bridgeField, ff, mask, uncoveredMasterFaces());
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::bridgeSlave
	(
		const Field<Type>& bridgeField,
		Field<Type>& ff
	) const
	{
		if
			(
				bridgeField.size() != slavePatch_.size()
				|| ff.size() != slavePatch_.size()
				)
		{
			FatalErrorIn
			(
				"void GGIInterpolation<MasterPatch, SlavePatch>::"
				"bridgeSlave\n"
				"(\n"
				"    const Field<Type>& bridgeField,\n"
				"    Field<Type>& ff"
				") const"
			) << "given field does not correspond to patch. Patch size: "
				<< slavePatch_.size()
				<< " bridge field size: " << bridgeField.size()
				<< " field size: " << ff.size()
				<< abort(FatalError);
		}

		bridge(bridgeField, ff, uncoveredSlaveFaces());
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	void GGIInterpolation<MasterPatch, SlavePatch>::maskedBridgeSlave
	(
		const Field<Type>& bridgeField,
		Field<Type>& ff,
		const labelList& mask
	) const
	{
		if (ff.size() != mask.size())
		{
			FatalErrorIn
			(
				"void GGIInterpolation<MasterPatch, SlavePatch>::"
				"maskedBridgeSlave\n"
				"(\n"
				"    const Field<Type>& bridgeField,\n"
				"    Field<Type>& ff\n,"
				"    const labelList& mask\n"
				") const"
			) << "given field does not correspond to patch. Patch size: "
				<< slavePatch_.size()
				<< " bridge field size: " << bridgeField.size()
				<< " field size: " << ff.size()
				<< " mask size: " << mask.size()
				<< abort(FatalError);
		}

		maskedBridge(bridgeField, ff, mask, uncoveredSlaveFaces());
	}




	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //