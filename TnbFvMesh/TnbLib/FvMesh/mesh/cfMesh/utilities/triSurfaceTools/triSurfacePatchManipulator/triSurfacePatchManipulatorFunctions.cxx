#include <triSurfacePatchManipulator.hxx>

#include <helperFunctions.hxx>
#include <demandDrivenData.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void triSurfacePatchManipulator::allocateFeatureEdges()
	{
		const edgeLongList& edges = surf_.edges();
		const VRWGraph& pEdges = surf_.pointEdges();

		//- allocate featureEdges list
		featureEdges_.setSize(edges.size());
		featureEdges_ = direction(0);

		const edgeLongList& featureEdges = surf_.featureEdges();

		forAll(featureEdges, feI)
		{
			const edge& e = featureEdges[feI];

			forAllRow(pEdges, e.start(), peI)
			{
				const label eI = pEdges(e.start(), peI);

				if (edges[eI] == e)
					featureEdges_[eI] |= 1;
			}
		}
	}

	void triSurfacePatchManipulator::createPatches()
	{
		nPatches_ = 0;
		facetInPatch_.setSize(surf_.size());
		facetInPatch_ = -1;

		const VRWGraph& faceEdges = surf_.facetEdges();
		const VRWGraph& edgeFaces = surf_.edgeFacets();

		forAll(facetInPatch_, triI)
		{
			if (facetInPatch_[triI] != -1)
				continue;

			labelLongList front;
			front.append(triI);
			facetInPatch_[triI] = nPatches_;

			while (front.size())
			{
				const label fLabel = front.removeLastElement();

				const constRow fEdges = faceEdges[fLabel];

				forAll(fEdges, feI)
				{
					const label edgeI = fEdges[feI];

					//- check if th edges is marked as a feature edge
					if (featureEdges_[edgeI])
						continue;

					const constRow eFaces = edgeFaces[edgeI];

					//- stop at non-manifold edges
					if (eFaces.size() != 2)
						continue;

					label neiTri = eFaces[0];
					if (neiTri == fLabel)
						neiTri = eFaces[1];

					//- do not overwrite existing patch information
					if (surf_[fLabel].region() != surf_[neiTri].region())
						continue;
					if (facetInPatch_[neiTri] != -1)
						continue;

					facetInPatch_[neiTri] = nPatches_;
					front.append(neiTri);
				}
			}

			++nPatches_;
		}

		Info << "Created " << nPatches_ << " surface patches" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //