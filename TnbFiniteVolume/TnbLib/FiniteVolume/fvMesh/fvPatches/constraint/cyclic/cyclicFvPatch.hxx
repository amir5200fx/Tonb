#pragma once
#ifndef _cyclicFvPatch_Header
#define _cyclicFvPatch_Header

#include <coupledFvPatch.hxx>
#include <cyclicLduInterface.hxx>
#include <cyclicPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class cyclicFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicFvPatch
		: public coupledFvPatch
		, public cyclicLduInterface
	{
		// Private data

		const cyclicPolyPatch& cyclicPolyPatch_;


	protected:

		// Protected Member functions

			//- Make patch weighting factors
		void makeWeights(scalarField&) const;

		//- Make patch face - neighbour cell distances
		void makeDeltaCoeffs(scalarField&) const;


	public:

		//- Runtime type information
		TypeName(cyclicPolyPatch::typeName_());


		// Constructors

			//- Construct from polyPatch
		cyclicFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			coupledFvPatch(patch, bm),
			cyclicPolyPatch_(refCast<const cyclicPolyPatch>(patch))
		{}


		// Destructor

		virtual ~cyclicFvPatch()
		{}


		// Member functions

			// Access

				//- Return face transformation tensor
		virtual const tensorField& forwardT() const
		{
			return coupledFvPatch::forwardT();
		}

		//- Return neighbour-cell transformation tensor
		virtual const tensorField& reverseT() const
		{
			return coupledFvPatch::reverseT();
		}


		//- Return delta (P to N) vectors across coupled patch
		virtual tmp<vectorField> delta() const;


		// Interface transfer functions

			//- Return the values of the given internal data adjacent to
			//  the interface as a field
		virtual tmp<labelField> interfaceInternalField
		(
			const unallocLabelList& internalData
		) const;

		//- Transfer and return neighbour field
		virtual tmp<labelField> transfer
		(
			const Pstream::commsTypes commsType,
			const unallocLabelList& interfaceData
		) const;

		//- Return neighbour field
		virtual tmp<labelField> internalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const unallocLabelList& internalData
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicFvPatch_Header
