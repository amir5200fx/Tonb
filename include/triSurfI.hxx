#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline LongList<labelledTri>& triSurf::accessToFacets()
	{
		return triSurfFacets::triangles_;
	}

	inline geometricSurfacePatchList& triSurf::accessToPatches()
	{
		return triSurfFacets::patches_;
	}

	/*
	inline label triSurf::numberOfFaceGroups() const
	{
		if( !faceGroupPtr_ )
			calculateFaceGroups();

		return nFaceGroups_;
	}

	inline const labelLongList& triSurf::faceGroups() const
	{
		if( !faceGroupPtr_ )
			calculateFaceGroups();

		return *faceGroupPtr_;
	}
	*/

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //