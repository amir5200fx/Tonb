#pragma once
#ifndef _mixingPlaneFvPatch_Header
#define _mixingPlaneFvPatch_Header

#include <coupledFvPatch.hxx>
#include <mixingPlaneLduInterface.hxx>
#include <mixingPlanePolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class mixingPlaneFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class mixingPlaneFvPatch
		:
		public coupledFvPatch,
		public mixingPlaneLduInterface
	{
		// Private Data

			//- Reference to polyPatch
		const mixingPlanePolyPatch& mixingPlanePolyPatch_;


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
		TypeName(mixingPlanePolyPatch::typeName_());


		// Constructors

			//- Construct from components
		mixingPlaneFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			coupledFvPatch(patch, bm),
			mixingPlanePolyPatch_(refCast<const mixingPlanePolyPatch>(patch))
		{}


		// Destructor

		virtual ~mixingPlaneFvPatch();


		// Member functions

			// Access

				//- Return shadow patch
		const mixingPlaneFvPatch& shadow() const;

		//- Return number of profile bands
		label nProfileBands() const
		{
			return mixingPlanePolyPatch_.nProfileBands();
		}

		//- Return delta (P to N) vectors across coupled patch
		virtual tmp<vectorField> delta() const;


		// Interpolation

			//- Interpolate face field
		template<class Type>
		tmp<Field<Type> > interpolate(const Field<Type>& pf) const
		{
			return mixingPlanePolyPatch_.interpolate(pf);
		}

		template<class Type>
		tmp<Field<Type> > interpolate(const tmp<Field<Type> >& tpf) const
		{
			return mixingPlanePolyPatch_.interpolate(tpf);
		}

		//- Profile average field.  Return field size is equal to
		//  the number of bands
		template<class Type>
		tmp<Field<Type> > toProfile
		(
			const Field<Type>& pf
		) const
		{
			return mixingPlanePolyPatch_.toProfile(pf);
		}

		template<class Type>
		tmp<Field<Type> > toProfile
		(
			const tmp<Field<Type> >& tpf
		) const
		{
			return mixingPlanePolyPatch_.toProfile(tpf);
		}

		//- Field from profile field.  Return field size is equal to
		//  patch size
		template<class Type>
		tmp<Field<Type> > fromProfile
		(
			const Field<Type>& pf
		) const
		{
			return mixingPlanePolyPatch_.fromProfile(pf);
		}

		template<class Type>
		tmp<Field<Type> > fromProfile
		(
			const tmp<Field<Type> >& tpf
		) const
		{
			return mixingPlanePolyPatch_.fromProfile(tpf);
		}

		//- Circumferential average face field
		template<class Type>
		tmp<Field<Type> > circumferentialAverage
		(
			const Field<Type>& pf
		) const
		{
			return mixingPlanePolyPatch_.circumferentialAverage(pf);
		}

		template<class Type>
		tmp<Field<Type> > circumferentialAverage
		(
			const tmp<Field<Type> >& tpf
		) const
		{
			return mixingPlanePolyPatch_.circumferentialAverage(tpf);
		}


		// Interface transfer functions

			//- Is this the master side?
		virtual bool master() const;

		//- Return shadow patch index
		virtual label shadowIndex() const;

		//- Return shadow interface
		virtual const mixingPlaneLduInterface& shadowInterface() const;

		//- Return addressing.  Master side returns own addressing and
		//  slave side returns addressing from master
		virtual const labelListList& addressing() const;

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

#endif // !_mixingPlaneFvPatch_Header
