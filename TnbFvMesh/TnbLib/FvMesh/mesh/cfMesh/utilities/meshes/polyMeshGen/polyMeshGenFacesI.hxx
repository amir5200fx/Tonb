#pragma once
# ifdef USE_OMP
#include <omp.h>
# endif

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline const faceListPMG& polyMeshGenFaces::faces() const
	{
		return faces_;
	}

	inline label polyMeshGenFaces::nInternalFaces() const
	{
		if (!(ownerPtr_ && neighbourPtr_))
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline label polyMeshGenFaces::nInternalFaces() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calculateOwnersAndNeighbours();
		}

		return nIntFaces_;
	}

	inline const labelList& polyMeshGenFaces::owner() const
	{
		if (!ownerPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline label polyMeshGenFaces::owner() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calculateOwnersAndNeighbours();
		}

		return *ownerPtr_;
	}

	inline const labelList& polyMeshGenFaces::neighbour() const
	{
		if (!neighbourPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline label polyMeshGenFaces::neighbour() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calculateOwnersAndNeighbours();
		}

		return *neighbourPtr_;
	}

	inline const PtrList<processorBoundaryPatch>&
		polyMeshGenFaces::procBoundaries() const
	{
		return procBoundaries_;
	}

	inline const PtrList<boundaryPatch>& polyMeshGenFaces::boundaries() const
	{
		return boundaries_;
	}

	inline void polyMeshGenFaces::addFaceToSubset
	(
		const label setID,
		const label faceI
	)
	{
		std::map<label, meshSubset>::iterator it = faceSubsets_.find(setID);
		if (it == faceSubsets_.end())
			return;

		it->second.addElement(faceI);
	}

	inline void polyMeshGenFaces::removeFaceFromSubset
	(
		const label setI,
		const label faceI)
	{
		std::map<label, meshSubset>::iterator it = faceSubsets_.find(setI);
		if (it == faceSubsets_.end())
			return;

		it->second.removeElement(faceI);
	}

	inline void polyMeshGenFaces::faceInSubsets
	(
		const label faceI,
		DynList<label>& faceSubsets
	) const
	{
		faceSubsets.clear();

		std::map<label, meshSubset>::const_iterator it;
		for
			(
				it = faceSubsets_.begin();
				it != faceSubsets_.end();
				++it
				)
		{
			if (it->second.contains(faceI))
				faceSubsets.append(it->first);
		}
	}

	inline void polyMeshGenFaces::faceSubsetIndices(DynList<label>& indices) const
	{
		indices.clear();

		std::map<label, meshSubset>::const_iterator it;
		for
			(
				it = faceSubsets_.begin();
				it != faceSubsets_.end();
				++it
				)
			indices.append(it->first);
	}

	template<class ListType>
	inline void polyMeshGenFaces::facesInSubset
	(
		const label setI,
		ListType& faceLabels
	) const
	{
		faceLabels.clear();

		std::map<label, meshSubset>::const_iterator it =
			faceSubsets_.find(setI);
		if (it == faceSubsets_.end())
			return;

		it->second.containedElements(faceLabels);
	}

	template<class ListType>
	inline void polyMeshGenFaces::updateFaceSubsets(const ListType& newFaceLabels)
	{
		for
			(
				std::map<label, meshSubset>::iterator it = faceSubsets_.begin();
				it != faceSubsets_.end();
				++it
				)
			it->second.updateSubset(newFaceLabels);
	}

	inline void polyMeshGenFaces::updateFaceSubsets(const VRWGraph& newFacesForFace)
	{
		for
			(
				std::map<label, meshSubset>::iterator it = faceSubsets_.begin();
				it != faceSubsets_.end();
				++it
				)
			it->second.updateSubset(newFacesForFace);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //