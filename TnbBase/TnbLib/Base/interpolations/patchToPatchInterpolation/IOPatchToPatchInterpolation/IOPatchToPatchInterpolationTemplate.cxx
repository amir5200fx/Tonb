#include <IOPatchToPatchInterpolationTemplate.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from components
	template<class FromPatch, class ToPatch>
	IOPatchToPatchInterpolation<FromPatch, ToPatch>::IOPatchToPatchInterpolation
	(
		const IOobject& io,
		const FromPatch& fromPatch,
		const ToPatch& toPatch,
		intersection::algorithm alg,
		const intersection::direction dir
	)
		:
		regIOobject(io),
		PatchToPatchInterpolation<FromPatch, ToPatch>(fromPatch, toPatch, alg, dir)
	{
		if (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
		{
			Istream& is = readStream(typeName);

			labelList* paPtr = new labelList(is);
			FieldField<Field, scalar>* pwPtr = new FieldField<Field, scalar>(is);
			scalarField* pdPtr = new scalarField(is);

			labelList* faPtr = new labelList(is);
			FieldField<Field, scalar>* fwPtr = new FieldField<Field, scalar>(is);
			scalarField* fdPtr = new scalarField(is);
			Info << "Setting weights from file" << endl;
			this->setWeights(paPtr, pwPtr, pdPtr, faPtr, fwPtr, fdPtr);
		}
	}

	// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

	template<class FromPatch, class ToPatch>
	IOPatchToPatchInterpolation<FromPatch, ToPatch>::~IOPatchToPatchInterpolation()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class FromPatch, class ToPatch>
	bool IOPatchToPatchInterpolation<FromPatch, ToPatch>::writeData
	(
		Ostream& os
	) const
	{
		os << this->pointAddr() << nl;
		os << this->pointWeights() << nl;
		os << this->pointDistanceToIntersection() << nl;
		os << this->faceAddr() << nl;
		os << this->faceWeights() << nl;
		os << this->faceDistanceToIntersection() << nl;
		return os.good();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //