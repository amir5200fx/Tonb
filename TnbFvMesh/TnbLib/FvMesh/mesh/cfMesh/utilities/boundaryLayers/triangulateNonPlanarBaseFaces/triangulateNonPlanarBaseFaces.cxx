#include <triangulateNonPlanarBaseFaces.hxx>

#include <demandDrivenData.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	triangulateNonPlanarBaseFaces::triangulateNonPlanarBaseFaces
	(
		polyMeshGen& mesh
	)
		:
		mesh_(mesh),
		invertedCell_(mesh_.cells().size(), false),
		decomposeFace_(mesh_.faces().size(), false),
		tol_(0.5)
	{}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	triangulateNonPlanarBaseFaces::~triangulateNonPlanarBaseFaces()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void triangulateNonPlanarBaseFaces::setRelativeTolerance(const scalar tol)
	{
		tol_ = tol;
	}

	void triangulateNonPlanarBaseFaces::triangulateLayers()
	{
		if (findNonPlanarBoundaryFaces())
		{
			Info << "Decomposing twisted boundary faces" << endl;

			decomposeBoundaryFaces();

			decomposeCellsIntoPyramids();
		}
		else
		{
			Info << "All boundary faces are flat" << endl;
		}
	}

	void triangulateNonPlanarBaseFaces::readSettings
	(
		const dictionary& meshDict,
		triangulateNonPlanarBaseFaces& triangulator
	)
	{
		if (meshDict.found("boundaryLayers"))
		{
			const dictionary& layersDict = meshDict.subDict("boundaryLayers");

			if (layersDict.found("optimisationParameters"))
			{
				const dictionary& optLayerDict =
					layersDict.subDict("optimisationParameters");

				if (optLayerDict.found("relFlatnessTol"))
				{
					const scalar relTol =
						readScalar(optLayerDict.lookup("relFlatnessTol"));

					triangulator.setRelativeTolerance(relTol);
				}
			}
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //