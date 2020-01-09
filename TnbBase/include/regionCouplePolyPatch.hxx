#pragma once
#ifndef _regionCouplePolyPatch_Header
#define _regionCouplePolyPatch_Header

#include <coupledPolyPatch.hxx>
#include <ggiInterpolation.hxx>
#include <faceZone.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
						 Class regionCouplePolyPatch Declaration
	\*---------------------------------------------------------------------------*/

	class regionCouplePolyPatch
		:
		public coupledPolyPatch
	{
		// Private data

			//- Shadow region name
		const word shadowRegionName_;

		//- Shadow patch name
		const word shadowPatchName_;

		//- Interpolation zone name
		const word zoneName_;

		//- Are the regions attached
		mutable Switch attached_;

		//- Master side.  Defined by user, checked for consistency
		Switch master_;

		//- Are the region attached walls
		Switch isWall_;

		//- Use bridging to fix overlap error in interpolation
		Switch bridgeOverlap_;

		//- Shadow patch index.  Delayed evaluation for construction
		mutable label shadowIndex_;

		//- Interpolation zone index.  Delayed evaluation for construction
		mutable label zoneIndex_;


		//- Patch-to-patch interpolation
		mutable ggiZoneInterpolation* patchToPatchPtr_;

		//- Patch-to-zone addressing
		mutable labelList* zoneAddressingPtr_;

		//- Remote zone addressing: data needed for interpolation
		mutable labelList* remoteZoneAddressingPtr_;

		//- Reconstructed patch neighbour cell centres
		mutable vectorField* reconFaceCellCentresPtr_;


		// Parallel communication optimisation, stored on master processor

			//- Is the patch localised on a single processor
			// (single processor in a parallel run)?
			//  Used for parallel optimisation
		mutable bool* localParallelPtr_;

		//- List of zone faces indices received from each processor
		mutable labelListList* receiveAddrPtr_;

		//- List of zone faces indices to send to each processor
		mutable labelListList* sendAddrPtr_;


		// Private member functions

			//- Calculate patch-to-zone addressing
		virtual void calcZoneAddressing() const;

		//- Calculate remote patch-to-zone addressing
		virtual void calcRemoteZoneAddressing() const;

		//- Calculate interpolation
		virtual void calcPatchToPatch() const;


		// Geometry

			//- Calculate reconstructed cell centres
		void calcReconFaceCellCentres() const;

		//- Force calculation of transformation tensors
		virtual void calcTransforms() const;


		// Parallel communication optimisation, stored on master processor

			//- Calculate local parallel switch
		void calcLocalParallel() const;

		//- Calculate send and receive addressing
		void calcSendReceive() const;


		//- Return receive addressing
		const labelListList& receiveAddr() const;

		//- Return send addressing
		const labelListList& sendAddr() const;


		// Memory management

			//- Clear delta coefficients
		void clearDeltas() const;

		//- Clear geometry
		void clearGeom() const;

		//- Clear out
		void clearOut() const;


	protected:

		// Protected Member functions

			//- Is the region couple active? (zone and shadow present)
		bool active() const;

		//- Initialise the calculation of the patch addressing
		virtual void initAddressing();

		//- Calculate the patch addressing
		virtual void calcAddressing();

		//- Initialise the calculation of the patch geometry
		virtual void initGeometry();

		//- Calculate the patch geometry
		virtual void calcGeometry();

		//- Initialise the patches for moving points
		virtual void initMovePoints(const pointField&);

		//- Correct patches after moving points
		virtual void movePoints(const pointField&);

		//- Initialise the update of the patch topology
		virtual void initUpdateMesh();

		//- Update of the patch topology
		virtual void updateMesh();


		//- Return non-constant access to shadow patch
		regionCouplePolyPatch& shadow();


	public:

		//- Runtime type information
		TypeName("regionCouple");


		// Constructors

			//- Construct from components
		regionCouplePolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm
		);

		//- Construct from components
		regionCouplePolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm,
			const word& shadowRegionName,
			const word& shadowPatchName,
			const word& zoneName,
			const bool attached,
			const bool master,
			const bool isWall,
			const bool bridgeOverlap
		);

		//- Construct from dictionary
		regionCouplePolyPatch
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh&
		);

		//- Construct as copy, resetting the boundary mesh
		regionCouplePolyPatch
		(
			const regionCouplePolyPatch&,
			const polyBoundaryMesh&
		);

		//- Construct as given the original patch and resetting the
		//  face list and boundary mesh information
		regionCouplePolyPatch
		(
			const regionCouplePolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		);

		//- Construct and return a clone, resetting the boundary mesh
		virtual autoPtr<polyPatch> clone(const polyBoundaryMesh& bm) const
		{
			return autoPtr<polyPatch>(new regionCouplePolyPatch(*this, bm));
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new regionCouplePolyPatch
					(
						refCast<const regionCouplePolyPatch>(*this),
						bm,
						index,
						newSize,
						newStart
					)
					);
		}


		// Destructor

		virtual ~regionCouplePolyPatch();


		// Member functions

			// Basic info

				//- Return true if coupled
		virtual bool coupled() const;

		//- Return shadow region name
		const word& shadowRegionName() const
		{
			return shadowRegionName_;
		}

		//- Return shadow patch name
		const word& shadowPatchName() const
		{
			return shadowPatchName_;
		}

		//- Return name of interpolation face zone
		const word& zoneName() const
		{
			return zoneName_;
		}

		//- Return shadow region
		const polyMesh& shadowRegion() const;

		//- Return shadow patch index
		label shadowIndex() const;

		//- Return zone patch index
		label zoneIndex() const;

		// Return true if patch is considered a wall
		bool isWall() const
		{
			return isWall_;
		}

		//- Return shadow patch
		const regionCouplePolyPatch& shadow() const;

		//- Return interpolation face zone
		const faceZone& zone() const;


		// Edit state

			//- Attach regions
		void attach() const;

		//- Attach regions
		void detach() const;


		// Interpolation data

			//- Is this the master side?
		bool master() const
		{
			return master_;
		}

		//- Is this the slave side?
		bool slave() const
		{
			return !master();
		}

		//- Use bridging to fix overlap error in interpolation
		bool bridgeOverlap() const
		{
			return bridgeOverlap_;
		}

		//- Return patch-to-zone addressing
		const labelList& zoneAddressing() const;

		//- Return remote patch-to-zone addressing
		const labelList& remoteZoneAddressing() const;

		//- Is the patch localised on a single processor
		bool localParallel() const;

		//- Return reference to patch-to-patch interpolation
		const ggiZoneInterpolation& patchToPatch() const;


		// Interpolation functions

			//- Expand face field to full zone size, including reduction
		template<class Type>
		tmp<Field<Type> > fastExpand(const Field<Type>& pf) const;

		//- Interpolate face field
		template<class Type>
		tmp<Field<Type> > interpolate(const Field<Type>& pf) const;

		template<class Type>
		tmp<Field<Type> > interpolate(const tmp<Field<Type> >& tpf) const;

		//- Bridge interpolated face field for uncovered faces
		template<class Type>
		void bridge
		(
			const Field<Type>& bridgeField,
			Field<Type>& ff
		) const;


		// Geometric data

			//- Return reconstructed cell centres
		const vectorField& reconFaceCellCentres() const;


		// Patch ordering

			//- Initialize ordering for primitivePatch. Does not
			//  refer to *this (except for name() and type() etc.)
		virtual void initOrder(const primitivePatch&) const;

		//- Return new ordering for primitivePatch.
		//  Ordering is -faceMap: for every face
		//  index of the new face -rotation: for every new face the
		//  clockwise shift of the original face. Return false if nothing
		//  changes (faceMap is identity, rotation is 0), true otherwise.
		virtual bool order
		(
			const primitivePatch&,
			labelList& faceMap,
			labelList& rotation
		) const;

		//- Synchronise communications of ordering for primitivePatch
		//  Used in cases when no topological change happens locally,
		//  but is happening on other processors
		virtual void syncOrder() const;


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <regionCouplePolyPatchTemplates.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionCouplePolyPatch_Header
