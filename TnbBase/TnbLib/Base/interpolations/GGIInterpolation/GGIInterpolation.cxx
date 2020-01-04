#include <GGIInterpolationTemplate.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	template<class MasterPatch, class SlavePatch>
	label GGIInterpolation<MasterPatch, SlavePatch>::parMasterStart() const
	{
		if (globalData())
		{
			// Integer division intended
			return tnbLib::min
			(
				masterPatch_.size(),
				Pstream::myProcNo()*(masterPatch_.size() / Pstream::nProcs() + 1)
			);
		}
		else
		{
			// No parallel search: do complete patch
			return 0;
		}
	}


	template<class MasterPatch, class SlavePatch>
	label GGIInterpolation<MasterPatch, SlavePatch>::parMasterEnd() const
	{
		if (globalData())
		{
			// Integer division intended
			return tnbLib::min
			(
				masterPatch_.size(),
				(Pstream::myProcNo() + 1)*
				(masterPatch_.size() / Pstream::nProcs() + 1)
			);
		}
		else
		{
			// No parallel search: do complete patch
			return masterPatch_.size();
		}
	}


	template<class MasterPatch, class SlavePatch>
	label GGIInterpolation<MasterPatch, SlavePatch>::parMasterSize() const
	{
		return tnbLib::max
		(
			0,
			this->parMasterEnd() - this->parMasterStart()
		);
	}


	template<class MasterPatch, class SlavePatch>
	void GGIInterpolation<MasterPatch, SlavePatch>::clearOut()
	{
		deleteDemandDrivenData(masterAddrPtr_);
		deleteDemandDrivenData(masterWeightsPtr_);
		deleteDemandDrivenData(slaveAddrPtr_);
		deleteDemandDrivenData(slaveWeightsPtr_);

		deleteDemandDrivenData(uncoveredMasterAddrPtr_);
		deleteDemandDrivenData(uncoveredSlaveAddrPtr_);

		deleteDemandDrivenData(masterPointAddressingPtr_);
		deleteDemandDrivenData(masterPointWeightsPtr_);
		deleteDemandDrivenData(masterPointDistancePtr_);

		deleteDemandDrivenData(slavePointAddressingPtr_);
		deleteDemandDrivenData(slavePointWeightsPtr_);
		deleteDemandDrivenData(slavePointDistancePtr_);
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from components
	template<class MasterPatch, class SlavePatch>
	GGIInterpolation<MasterPatch, SlavePatch>::GGIInterpolation
	(
		const MasterPatch& masterPatch,
		const SlavePatch&  slavePatch,
		const tensorField& forwardT,
		const tensorField& reverseT,
		const vectorField& forwardSep,
		const bool globalData,
		const scalar masterNonOverlapFaceTol,
		const scalar slaveNonOverlapFaceTol,
		const bool rescaleGGIWeightingFactors,
		const quickReject reject
	)
		:
		masterPatch_(masterPatch),
		slavePatch_(slavePatch),
		forwardT_(forwardT),
		reverseT_(reverseT),
		forwardSep_(forwardSep),
		globalData_(globalData),
		masterNonOverlapFaceTol_(masterNonOverlapFaceTol),
		slaveNonOverlapFaceTol_(slaveNonOverlapFaceTol),
		rescaleGGIWeightingFactors_(rescaleGGIWeightingFactors),
		reject_(reject),
		masterAddrPtr_(NULL),
		masterWeightsPtr_(NULL),
		masterPointAddressingPtr_(NULL),
		masterPointWeightsPtr_(NULL),
		masterPointDistancePtr_(NULL),
		slaveAddrPtr_(NULL),
		slaveWeightsPtr_(NULL),
		slavePointAddressingPtr_(NULL),
		slavePointWeightsPtr_(NULL),
		slavePointDistancePtr_(NULL),
		uncoveredMasterAddrPtr_(NULL),
		uncoveredSlaveAddrPtr_(NULL)
	{
		// Check size of transform.  They should be equal to slave patch size
		// if the transform is not constant
		if (forwardT_.size() > 1 || reverseT_.size() > 1)
		{
			if
				(
					forwardT_.size() != slavePatch_.size()
					|| reverseT_.size() != masterPatch_.size()
					)
			{
				FatalErrorIn
				(
					"GGIInterpolation<MasterPatch, SlavePatch>::GGIInterpolation"
				) << "Incorrectly defined transform: forwardT: "
					<< forwardT_.size() << " patch: " << slavePatch_.size()
					<< " reverseT: " << reverseT_.size()
					<< " patch: " << masterPatch_.size()
					<< abort(FatalError);
			}
		}
	}


	// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

	template<class MasterPatch, class SlavePatch>
	GGIInterpolation<MasterPatch, SlavePatch>::~GGIInterpolation()
	{
		clearOut();
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class MasterPatch, class SlavePatch>
	const labelListList&
		GGIInterpolation<MasterPatch, SlavePatch>::masterAddr() const
	{
		if (!masterAddrPtr_)
		{
			calcAddressing();
		}

		return *masterAddrPtr_;
	}


	template<class MasterPatch, class SlavePatch>
	const scalarListList&
		GGIInterpolation<MasterPatch, SlavePatch>::masterWeights() const
	{
		if (!masterWeightsPtr_)
		{
			calcAddressing();
		}

		return *masterWeightsPtr_;
	}


	template<class MasterPatch, class SlavePatch>
	const labelListList&
		GGIInterpolation<MasterPatch, SlavePatch>::slaveAddr() const
	{
		if (!slaveAddrPtr_)
		{
			calcAddressing();
		}

		return *slaveAddrPtr_;
	}


	template<class MasterPatch, class SlavePatch>
	const scalarListList&
		GGIInterpolation<MasterPatch, SlavePatch>::slaveWeights() const
	{
		if (!slaveWeightsPtr_)
		{
			calcAddressing();
		}

		return *slaveWeightsPtr_;
	}


	template<class MasterPatch, class SlavePatch>
	const labelList&
		GGIInterpolation<MasterPatch, SlavePatch>::uncoveredMasterFaces() const
	{
		if (!uncoveredMasterAddrPtr_)
		{
			calcAddressing();
		}

		return *uncoveredMasterAddrPtr_;
	}


	template<class MasterPatch, class SlavePatch>
	const labelList&
		GGIInterpolation<MasterPatch, SlavePatch>::uncoveredSlaveFaces() const
	{
		if (!uncoveredSlaveAddrPtr_)
		{
			calcAddressing();
		}

		return *uncoveredSlaveAddrPtr_;
	}


	template<class MasterPatch, class SlavePatch>
	bool GGIInterpolation<MasterPatch, SlavePatch>::movePoints
	(
		const tensorField& forwardT,
		const tensorField& reverseT,
		const vectorField& forwardSep
	)
	{
		this->forwardT_ = forwardT;
		this->reverseT_ = reverseT;
		this->forwardSep_ = forwardSep;

		clearOut();

		return true;
	}

	template<class MasterPatch, class SlavePatch>
	const tnbLib::List<labelPair>&
		GGIInterpolation<MasterPatch, SlavePatch>::masterPointAddr() const
	{
		if (!masterPointAddressingPtr_)
		{
			calcMasterPointAddressing();
		}

		return *masterPointAddressingPtr_;
	}

	template<class MasterPatch, class SlavePatch>
	const tnbLib::FieldField<Field, scalar>&
		GGIInterpolation<MasterPatch, SlavePatch>::masterPointWeights() const
	{
		if (!masterPointWeightsPtr_)
		{
			calcMasterPointWeights();
		}

		return *masterPointWeightsPtr_;
	}


	template<class MasterPatch, class SlavePatch>
	const scalarField&
		GGIInterpolation<MasterPatch, SlavePatch>
		::masterPointDistanceToIntersection() const
	{
		if (!masterPointDistancePtr_)
		{
			calcMasterPointAddressing();
		}

		return *masterPointDistancePtr_;
	}


	template<class MasterPatch, class SlavePatch>
	const tnbLib::List<labelPair>&
		GGIInterpolation<MasterPatch, SlavePatch>::slavePointAddr() const
	{
		if (!slavePointAddressingPtr_)
		{
			calcSlavePointAddressing();
		}

		return *slavePointAddressingPtr_;
	}

	template<class MasterPatch, class SlavePatch>
	const tnbLib::FieldField<Field, scalar>&
		GGIInterpolation<MasterPatch, SlavePatch>::slavePointWeights() const
	{
		if (!slavePointWeightsPtr_)
		{
			calcSlavePointWeights();
		}

		return *slavePointWeightsPtr_;
	}


	template<class MasterPatch, class SlavePatch>
	const scalarField&
		GGIInterpolation<MasterPatch, SlavePatch>
		::slavePointDistanceToIntersection() const
	{
		if (!slavePointDistancePtr_)
		{
			calcSlavePointAddressing();
		}

		return *slavePointDistancePtr_;
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	tmp<Field<Type> > GGIInterpolation<MasterPatch, SlavePatch>::
		slaveToMasterPointInterpolate
		(
			const Field<Type>& pf
		) const
	{
		if (pf.size() != this->slavePatch().nPoints())
		{
			FatalErrorIn
			(
				"ExtendedGGIInterpolation::slaveToMasterPointInterpolate"
				"(const Field<Type> pf)"
			) << "given field does not correspond to patch. Patch size: "
				<< this->slavePatch().nPoints() << " field size: " << pf.size()
				<< abort(FatalError);
		}

		tmp<Field<Type> > tresult
		(
			new Field<Type>
			(
				this->masterPatch().nPoints(),
				pTraits<Type>::zero
				)
		);

		// Escape the interpolation if there are no faces in the target patch
		if (this->masterPatch().nPoints() == 0)
		{
			return tresult;
		}

		Field<Type>& result = tresult();

		const List<typename SlavePatch::FaceType>& slaveFaces =
			this->slavePatch().localFaces();

		const List<labelPair>& addr = masterPointAddr();

		const FieldField<Field, scalar>& weights = masterPointWeights();

		forAll(result, pointI)
		{
			if (addr[pointI].first() > -1)
			{
				const face& hitFace =
					slaveFaces[addr[pointI].first()];

				label pI = addr[pointI].second();

				Type ctrF = average(Field<Type>(pf, hitFace));

				result[pointI] =
					weights[pointI][0] * pf[hitFace[pI]]
					+ weights[pointI][1] * pf[hitFace.nextLabel(pI)]
					+ weights[pointI][2] * ctrF;
			}
			else
			{
				FatalErrorIn
				(
					"ExtendedGGIInterpolation::masterToSlavePointInterpolate"
					"(const Field<Type> pf)"
				) << "Master point addressing is not correct"
					<< abort(FatalError);
			}
		}

		return tresult;
	}


	template<class MasterPatch, class SlavePatch>
	template<class Type>
	tmp<Field<Type> > GGIInterpolation<MasterPatch, SlavePatch>::
		masterToSlavePointInterpolate
		(
			const Field<Type>& pf
		) const
	{
		if (pf.size() != this->masterPatch().nPoints())
		{
			FatalErrorIn
			(
				"ExtendedGGIInterpolation::masterToSlavePointInterpolate"
				"(const Field<Type> pf)"
			) << "given field does not correspond to patch. Patch size: "
				<< this->masterPatch().nPoints() << " field size: " << pf.size()
				<< abort(FatalError);
		}

		tmp<Field<Type> > tresult
		(
			new Field<Type>
			(
				this->slavePatch().nPoints(),
				pTraits<Type>::zero
				)
		);

		// Escape the interpolation if there are no faces in the target patch
		if (this->slavePatch().nPoints() == 0)
		{
			return tresult;
		}

		Field<Type>& result = tresult();

		const List<typename SlavePatch::FaceType>& masterFaces =
			this->masterPatch().localFaces();

		const List<labelPair>& addr = slavePointAddr();

		const FieldField<Field, scalar>& weights = slavePointWeights();

		forAll(result, pointI)
		{
			if (addr[pointI].first() > -1)
			{
				const face& hitFace =
					masterFaces[addr[pointI].first()];

				label pI = addr[pointI].second();

				Type ctrF = average(Field<Type>(pf, hitFace));

				result[pointI] =
					weights[pointI][0] * pf[hitFace[pI]]
					+ weights[pointI][1] * pf[hitFace.nextLabel(pI)]
					+ weights[pointI][2] * ctrF;
			}
			else
			{
				FatalErrorIn
				(
					"ExtendedGGIInterpolation::masterToSlavePointInterpolate"
					"(const Field<Type> pf)"
				) << "Slave point addressing is not correct"
					<< abort(FatalError);
			}
		}

		return tresult;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#   include <GGIInterpolationPolygonIntersection.cxx>
#   include <GGIInterpolationQuickRejectTests.cxx>
#   include <GGIInterpolationWeights.cxx>
#   include <GGIInterpolate.cxx>

// ************************************************************************* //