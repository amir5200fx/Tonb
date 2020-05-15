#include <tetCreatorOctree.hxx>

#include <demandDrivenData.hxx>

//#define DEBUGTets

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void tetCreatorOctree::createTetsFromSplitFaces()
	{
		Info << "Creating tets from split faces" << endl;

		const labelList& cubeLabel = *cubeLabelPtr_;
		const VRWGraph& subNodeLabels = *subNodeLabelsPtr_;
		const FRWGraph<label, 8>& pLeaves = octreeCheck_.nodeLeaves();

		forAll(pLeaves, pointI)
		{
			for (label i = 0; i < 6; ++i)
			{
				const label* fNodes =
					meshOctreeCubeCoordinates::faceNodes_[i];

				const label cLabel = pLeaves(pointI, fNodes[0]);

				if (cLabel < 0)
					continue;
				if (cubeLabel[cLabel] < 0)
					continue;

				if (
					(cLabel == pLeaves(pointI, fNodes[1])) &&
					(cLabel == pLeaves(pointI, fNodes[2])) &&
					(cLabel == pLeaves(pointI, fNodes[3]))
					)
				{
					//- create 4 tets
					for (label j = 0; j < 4; ++j)
					{
						checkAndAppendTet
						(
							partTet
							(
								pointI,
								subNodeLabels(cLabel, 7 - fNodes[j]),
								subNodeLabels(cLabel, 7 - fNodes[(j + 1) % 4]),
								cubeLabel[cLabel]
							)
						);
					}
				}
			}
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //