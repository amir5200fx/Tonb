#include <triSurfaceMetaData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void triSurfaceMetaData::createMetaData()
	{
		metaDict_.clear();

		metaDict_.add("nPoints", surf_.points().size());
		metaDict_.add("nFacets", surf_.facets().size());
		metaDict_.add("nPatches", surf_.patches().size());
		metaDict_.add("nFeatureEdges", surf_.featureEdges().size());

		dictionary dict;

		//- store nformation about surface patches
		labelList nInPatch(surf_.patches().size(), 0);
		forAll(surf_, triI)
			++nInPatch[surf_[triI].region()];

		forAll(surf_.patches(), patchI)
		{
			const geometricSurfacePatch& patch = surf_.patches()[patchI];

			dictionary pDict;
			pDict.add("type", patch.geometricType());
			pDict.add("nFacets", nInPatch[patchI]);

			dict.add(patch.name(), pDict);
		}

		metaDict_.add("patches", dict);

		//- store information about point subsets
		DynList<label> subsetIds;
		surf_.pointSubsetIndices(subsetIds);
		dict.clear();
		forAll(subsetIds, i)
		{
			dictionary sDict;

			labelLongList inSubset;
			surf_.pointsInSubset(subsetIds[i], inSubset);
			sDict.add("nPoints", inSubset.size());

			dict.add(surf_.pointSubsetName(subsetIds[i]), sDict);
		}

		metaDict_.add("pointSubsets", dict);

		//- store information about facet subsets
		subsetIds.clear();
		surf_.facetSubsetIndices(subsetIds);
		dict.clear();
		forAll(subsetIds, i)
		{
			dictionary sDict;

			labelLongList inSubset;
			surf_.facetsInSubset(subsetIds[i], inSubset);
			sDict.add("nFacets", inSubset.size());

			dict.add(surf_.facetSubsetName(subsetIds[i]), sDict);
		}

		metaDict_.add("facetSubsets", dict);

		//- store information about feature edge subsets
		subsetIds.clear();
		surf_.edgeSubsetIndices(subsetIds);
		dict.clear();
		forAll(subsetIds, i)
		{
			dictionary sDict;

			labelLongList inSubset;
			surf_.edgesInSubset(subsetIds[i], inSubset);
			sDict.add("nEdges", inSubset.size());

			dict.add(surf_.edgeSubsetName(subsetIds[i]), sDict);
		}

		metaDict_.add("featureEdgeSubsets", dict);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	triSurfaceMetaData::triSurfaceMetaData(const triSurf& surface)
		:
		surf_(surface),
		metaDict_()
	{
		createMetaData();
	}

	triSurfaceMetaData::~triSurfaceMetaData()
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //