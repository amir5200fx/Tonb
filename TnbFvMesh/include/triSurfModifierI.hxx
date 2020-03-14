#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline pointField& triSurfModifier::pointsAccess()
	{
		return const_cast<pointField&>(surface_.points());
	}

	inline LongList<labelledTri>& triSurfModifier::facetsAccess()
	{
		return const_cast<LongList<labelledTri>&>(surface_.facets());
	}

	inline edgeLongList& triSurfModifier::featureEdgesAccess()
	{
		return const_cast<edgeLongList&>(surface_.featureEdges());
	}

	inline geometricSurfacePatchList& triSurfModifier::patchesAccess()
	{
		return const_cast<geometricSurfacePatchList&>(surface_.patches());
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //