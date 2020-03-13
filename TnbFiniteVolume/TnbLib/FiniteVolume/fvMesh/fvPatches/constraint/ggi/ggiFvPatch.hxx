#pragma once
#ifndef _ggiFvPatch_Header
#define _ggiFvPatch_Header

#include <coupledFvPatch.hxx>
#include <ggiLduInterface.hxx>
#include <ggiPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class ggiFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class ggiFvPatch
		:
		public coupledFvPatch,
		public ggiLduInterface
	{
		// Private Data

			//- Reference to polyPatch
		const ggiPolyPatch& ggiPolyPatch_;


	protected:

		// Protected Member functions

			//- Make patch weighting factors
		virtual void makeWeights(scalarField&) const;

		//- Make patch face - neighbour cell distances
		virtual void makeDeltaCoeffs(scalarField&) const;

		//- Make patch face non-orthogonality correction vectors
		virtual void makeCorrVecs(vectorField&) const;


	public:

		//- Runtime type information
		TypeName(ggiPolyPatch::typeName_());


		// Constructors

			//- Construct from components
		ggiFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			coupledFvPatch(patch, bm),
			ggiPolyPatch_(refCast<const ggiPolyPatch>(patch))
		{}


		// Destructor

		virtual ~ggiFvPatch();


		// Member functions

			// Access

				//- Return shadow patch
		const ggiFvPatch& shadow() const;

		//- Use bridging to fix overlap error in interpolation
		bool bridgeOverlap() const
		{
			return ggiPolyPatch_.bridgeOverlap();
		}

		//- Return delta (P to N) vectors across coupled patch
		virtual tmp<vectorField> delta() const;


		// Interpolation

			//- Interpolate face field
		template<class Type>
		tmp<Field<Type> > interpolate(const Field<Type>& pf) const
		{
			return ggiPolyPatch_.interpolate(pf);
		}

		template<class Type>
		tmp<Field<Type> > interpolate(const tmp<Field<Type> >& tpf) const
		{
			return ggiPolyPatch_.interpolate(tpf);
		}

		//- Bridge interpolated face field for uncovered faces
		template<class Type>
		void bridge
		(
			const Field<Type>& bridgeField,
			Field<Type>& ff
		) const
		{
			return ggiPolyPatch_.bridge(bridgeField, ff);
		}


		// Interface transfer functions

			//- Is this the master side?
		virtual bool master() const;

		//- Is this the fine level?
		virtual bool fineLevel() const;

		//- Return shadow patch index
		virtual label shadowIndex() const;

		//- Return shadow interface
		virtual const ggiLduInterface& shadowInterface() const;

		//- Return interface size
		virtual label interfaceSize() const;

		//- Return zone size
		virtual label zoneSize() const;

		//- Return zone addressing
		virtual const labelList& zoneAddressing() const;

		//- Return addressing.  Master side returns own addressing and
		//  slave side returns addressing from master
		virtual const labelListList& addressing() const;

		//- Is the patch localised on a single processor
		virtual bool localParallel() const;

		//- Return weights.  Master side returns own weights and
		//  slave side returns weights from master
		virtual const scalarListList& weights() const;

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

		//- Initialise transfer of internal field adjacent to the interface
		virtual void initInternalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const unallocLabelList& iF
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

#endif // !_ggiFvPatch_Header
