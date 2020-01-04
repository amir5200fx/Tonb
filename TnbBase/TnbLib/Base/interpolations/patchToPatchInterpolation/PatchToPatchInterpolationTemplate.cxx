#include <PatchToPatchInterpolationTemplate.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<class FromPatch, class ToPatch>
	const tnbLib::debug::tolerancesSwitch
		PatchToPatchInterpolation<FromPatch, ToPatch>::directHitTol_
		(
			"patchToPatchDirectHit",
			1e-5
		);

	template<class FromPatch, class ToPatch>
	const tnbLib::debug::tolerancesSwitch
		PatchToPatchInterpolation<FromPatch, ToPatch>::projectionTol_
		(
			"patchToPatchProjectionTol",
			0.05
		);

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	template<class FromPatch, class ToPatch>
	void PatchToPatchInterpolation<FromPatch, ToPatch>::clearOut()
	{
		deleteDemandDrivenData(pointAddressingPtr_);
		deleteDemandDrivenData(pointWeightsPtr_);
		deleteDemandDrivenData(pointDistancePtr_);
		deleteDemandDrivenData(faceAddressingPtr_);
		deleteDemandDrivenData(faceWeightsPtr_);
		deleteDemandDrivenData(faceDistancePtr_);
	}


	template<class FromPatch, class ToPatch>
	void PatchToPatchInterpolation<FromPatch, ToPatch>::setWeights
	(
		labelList* paPtr,
		FieldField<Field, scalar>* pwPtr,
		scalarField* pdPtr,
		labelList* faPtr,
		FieldField<Field, scalar>* fwPtr,
		scalarField* fdPtr
	)
	{
		clearOut();

		pointAddressingPtr_ = paPtr;
		pointWeightsPtr_ = pwPtr;
		pointDistancePtr_ = pdPtr;
		faceAddressingPtr_ = faPtr;;
		faceWeightsPtr_ = fwPtr;
		faceDistancePtr_ = fdPtr;;
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from components
	template<class FromPatch, class ToPatch>
	PatchToPatchInterpolation<FromPatch, ToPatch>::PatchToPatchInterpolation
	(
		const FromPatch& fromPatch,
		const ToPatch& toPatch,
		intersection::algorithm alg,
		const intersection::direction dir
	)
		:
		fromPatch_(fromPatch),
		toPatch_(toPatch),
		alg_(alg),
		dir_(dir),
		pointAddressingPtr_(NULL),
		pointWeightsPtr_(NULL),
		pointDistancePtr_(NULL),
		faceAddressingPtr_(NULL),
		faceWeightsPtr_(NULL),
		faceDistancePtr_(NULL)
	{
	}


	// Construct as copy
	template<class FromPatch, class ToPatch>
	PatchToPatchInterpolation<FromPatch, ToPatch>::PatchToPatchInterpolation
	(
		const PatchToPatchInterpolation<FromPatch, ToPatch>& ppi
	)
		:
		PatchToPatchInterpolationName(),
		fromPatch_(ppi.fromPatch_),
		toPatch_(ppi.toPatch_),
		alg_(ppi.alg_),
		dir_(ppi.dir_),
		pointAddressingPtr_(NULL),
		pointWeightsPtr_(NULL),
		pointDistancePtr_(NULL),
		faceAddressingPtr_(NULL),
		faceWeightsPtr_(NULL),
		faceDistancePtr_(NULL)
	{}


	// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

	template<class FromPatch, class ToPatch>
	PatchToPatchInterpolation<FromPatch, ToPatch>::~PatchToPatchInterpolation()
	{
		clearOut();
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class FromPatch, class ToPatch>
	const labelList&
		PatchToPatchInterpolation<FromPatch, ToPatch>::pointAddr() const
	{
		if (!pointAddressingPtr_)
		{
			calcPointAddressing();
		}

		return *pointAddressingPtr_;
	}


	template<class FromPatch, class ToPatch>
	const FieldField<Field, scalar>&
		PatchToPatchInterpolation<FromPatch, ToPatch>::pointWeights() const
	{
		if (!pointWeightsPtr_)
		{
			calcPointAddressing();
		}

		return *pointWeightsPtr_;
	}


	template<class FromPatch, class ToPatch>
	const labelList&
		PatchToPatchInterpolation<FromPatch, ToPatch>::faceAddr() const
	{
		if (!faceAddressingPtr_)
		{
			calcFaceAddressing();
		}

		return *faceAddressingPtr_;
	}


	template<class FromPatch, class ToPatch>
	const FieldField<Field, scalar>&
		PatchToPatchInterpolation<FromPatch, ToPatch>::faceWeights() const
	{
		if (!faceWeightsPtr_)
		{
			calcFaceAddressing();
		}

		return *faceWeightsPtr_;
	}


	template<class FromPatch, class ToPatch>
	const scalarField&
		PatchToPatchInterpolation<FromPatch, ToPatch>
		::pointDistanceToIntersection() const
	{
		if (!pointDistancePtr_)
		{
			calcPointAddressing();
		}

		return *pointDistancePtr_;
	}


	template<class FromPatch, class ToPatch>
	const scalarField&
		PatchToPatchInterpolation<FromPatch, ToPatch>
		::faceDistanceToIntersection() const
	{
		if (!faceDistancePtr_)
		{
			calcFaceAddressing();
		}

		return *faceDistancePtr_;
	}


	template<class FromPatch, class ToPatch>
	bool PatchToPatchInterpolation<FromPatch, ToPatch>::movePoints()
	{
		clearOut();

		return true;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#   include <CalcPatchToPatchWeights.cxx>
#   include <PatchToPatchInterpolate.cxx>

// ************************************************************************* //