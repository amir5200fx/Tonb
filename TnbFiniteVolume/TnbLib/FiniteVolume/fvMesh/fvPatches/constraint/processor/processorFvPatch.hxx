#pragma once
#ifndef _processorFvPatch_Header
#define _processorFvPatch_Header

#include <coupledFvPatch.hxx>
#include <processorLduInterface.hxx>
#include <processorPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class processorFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class processorFvPatch
		: public coupledFvPatch
		, public processorLduInterface
	{
		// Private Data

			//- Reference to processor patch
		const processorPolyPatch& procPolyPatch_;


	protected:

		// Protected Member functions

			//- Make patch weighting factors
		void makeWeights(scalarField&) const;

		//- Make patch face - neighbour cell distances
		void makeDeltaCoeffs(scalarField&) const;


	public:

		//- Runtime type information
		TypeName(processorPolyPatch::typeName_());


		// Constructors

			//- Construct from components
		processorFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			coupledFvPatch(patch, bm),
			procPolyPatch_(refCast<const processorPolyPatch>(patch))
		{}


		// Destructor

		virtual ~processorFvPatch()
		{}


		// Member functions

			//- Return processor number
		int myProcNo() const
		{
			return procPolyPatch_.myProcNo();
		}

		//- Return neigbour processor number
		int neighbProcNo() const
		{
			return procPolyPatch_.neighbProcNo();
		}

		//- Return true if running parallel
		virtual bool coupled() const
		{
			if (Pstream::parRun())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		//- Return face transformation tensor
		virtual const tensorField& forwardT() const
		{
			return procPolyPatch_.forwardT();
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

		//- Initialise interface data transfer
		virtual void initTransfer
		(
			const Pstream::commsTypes commsType,
			const unallocLabelList& interfaceData
		) const;

		//- Transfer and return neighbour field
		virtual tmp<labelField> transfer
		(
			const Pstream::commsTypes commsType,
			const unallocLabelList& interfaceData
		) const;

		//- Initialise neighbour field transfer
		virtual void initInternalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const unallocLabelList& internalData
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

#endif // !_processorFvPatch_Header
