#pragma once
#ifndef _fvMeshLduAddressing_Header
#define _fvMeshLduAddressing_Header

#include <lduAddressing.hxx>
#include <fvMesh.hxx>
#include <globalMeshData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class fvMeshLduAddressing Declaration
	\*---------------------------------------------------------------------------*/

	class fvMeshLduAddressing
		:
		public lduAddressing
	{
		// Private data

			//- Lower as a subList of allOwner
		labelList::subList lowerAddr_;

		//- Upper as a reference to neighbour
		const labelList& upperAddr_;

		//- Patch addressing as a list of sublists
		List<const unallocLabelList*> patchAddr_;

		//- Patch field evaluation schedule
		const lduSchedule& patchSchedule_;


		// Private Member Functions

			//- Disallow default bitwise copy construct
		fvMeshLduAddressing(const fvMeshLduAddressing&);

		//- Disallow default bitwise assignment
		void operator=(const fvMeshLduAddressing&);


	public:

		// Constructors

			//- Construct from components
		fvMeshLduAddressing(const fvMesh& mesh)
			:
			lduAddressing(mesh.nCells()),
			lowerAddr_
			(
				labelList::subList
				(
					mesh.faceOwner(),
					mesh.nInternalFaces()
				)
			),
			upperAddr_(mesh.faceNeighbour()),
			patchAddr_(mesh.boundary().size()),
			patchSchedule_(mesh.globalData().patchSchedule())
		{
			forAll(mesh.boundary(), patchI)
			{
				patchAddr_[patchI] = &mesh.boundary()[patchI].faceCells();
			}
		}


		// Destructor

		virtual ~fvMeshLduAddressing()
		{}


		// Member Functions

			//- Return number of interfaces
		virtual label nPatches() const
		{
			return patchAddr_.size();
		}

		//- Return lower addressing (i.e. lower label = upper triangle)
		virtual const unallocLabelList& lowerAddr() const
		{
			return lowerAddr_;
		}

		//- Return upper addressing (i.e. upper label)
		virtual const unallocLabelList& upperAddr() const
		{
			return upperAddr_;
		}

		//- Return patch addressing
		virtual const unallocLabelList& patchAddr(const label i) const
		{
			return *patchAddr_[i];
		}

		// Return patch field evaluation schedule
		virtual const lduSchedule& patchSchedule() const
		{
			return patchSchedule_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvMeshLduAddressing_Header
