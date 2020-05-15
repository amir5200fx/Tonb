#include <triSurfaceRemoveFacets.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	triSurfaceRemoveFacets::triSurfaceRemoveFacets(triSurf& surface)
		:
		surf_(surface),
		selectedEntities_()
	{}

	triSurfaceRemoveFacets::~triSurfaceRemoveFacets()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void triSurfaceRemoveFacets::selectFacetsInPatch(const word& patchName)
	{
		selectedEntities_.append(patchName);
	}

	//- add subsets for removal
	void triSurfaceRemoveFacets::selectFacetsInSubset(const word& subsetName)
	{
		selectedEntities_.append(subsetName);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //