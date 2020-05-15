#include <voronoiMeshGenerator.hxx>

#include <triSurf.hxx>
#include <demandDrivenData.hxx>
#include <objectRegistry.hxx>
#include <tnbTime.hxx>
#include <meshOctreeCreator.hxx>
#include <voronoiMeshExtractor.hxx>
#include <meshSurfaceEngine.hxx>
#include <meshSurfaceMapper.hxx>
#include <surfaceMorpherCells.hxx>
#include <meshOptimizer.hxx>
#include <meshSurfaceOptimizer.hxx>
#include <topologicalCleaner.hxx>
#include <boundaryLayers.hxx>
#include <refineBoundaryLayers.hxx>
#include <renameBoundaryPatches.hxx>
#include <checkMeshDict.hxx>
#include <triSurfacePatchManipulator.hxx>
#include <triSurfaceMetaData.hxx>
#include <surfaceMeshGeometryModification.hxx>
#include <polyMeshGenGeometryModification.hxx>
#include <edgeExtractor.hxx>
#include <meshSurfaceEdgeExtractorFUN.hxx>

//#define DEBUG

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * Private member functions  * * * * * * * * * * * * //

	void voronoiMeshGenerator::createVoronoiMesh()
	{
		//- create voronoi mesh from octree and Delaunay tets
		voronoiMeshExtractor vme(*octreePtr_, meshDict_, mesh_);

		vme.createMesh();

# ifdef DEBUG
		mesh_.write();
		//::exit(EXIT_FAILURE);
# endif
	}

	void voronoiMeshGenerator::surfacePreparation()
	{
		//- removes unnecessary cells and morphs the boundary
		//- such that there exists only one boundary face per cell

		surfaceMorpherCells* cmPtr = new surfaceMorpherCells(mesh_);
		cmPtr->morphMesh();
		deleteDemandDrivenData(cmPtr);

# ifdef DEBUG
		mesh_.write();
		//::exit(EXIT_FAILURE);
# endif
	}

	void voronoiMeshGenerator::mapMeshToSurface()
	{
		//- calculate mesh surface
		meshSurfaceEngine* msePtr = new meshSurfaceEngine(mesh_);

		//- map mesh surface on the geometry surface
		meshSurfaceMapper mapper(*msePtr, *octreePtr_);
		mapper.preMapVertices();
		mapper.mapVerticesOntoSurface();

# ifdef DEBUG
		mesh_.write();
		//::exit(EXIT_FAILURE);
# endif

//- untangle surface faces
		meshSurfaceOptimizer(*msePtr, *octreePtr_).untangleSurface();

# ifdef DEBUG
		mesh_.write();
		::exit(EXIT_FAILURE);
# endif

		deleteDemandDrivenData(msePtr);
	}

	void voronoiMeshGenerator::extractPatches()
	{
		edgeExtractor extractor(mesh_, *octreePtr_);

		Info << "Extracting edges" << endl;
		extractor.extractEdges();

		extractor.updateMeshPatches();
	}

	void voronoiMeshGenerator::mapEdgesAndCorners()
	{
		meshSurfaceEdgeExtractorFUN(mesh_, *octreePtr_, false);

# ifdef DEBUG
		mesh_.write();
		//::exit(EXIT_FAILURE);
# endif
	}

	void voronoiMeshGenerator::optimiseMeshSurface()
	{
		meshSurfaceEngine mse(mesh_);
		meshSurfaceOptimizer surfOptimiser(mse, *octreePtr_);
		surfOptimiser.optimizeSurface();
		surfOptimiser.untangleSurface();

# ifdef DEBUG
		mesh_.write();
		//::exit(EXIT_FAILURE);
# endif
	}

	void voronoiMeshGenerator::generateBoudaryLayers()
	{
		boundaryLayers bl(mesh_);

		if (meshDict_.found("boundaryLayers"))
		{
			boundaryLayers bl(mesh_);

			const dictionary& bndLayers = meshDict_.subDict("boundaryLayers");

			if (bndLayers.found("nLayers"))
			{
				const label nLayers = readLabel(bndLayers.lookup("nLayers"));

				if (nLayers > 0)
					bl.addLayerForAllPatches();
			}
			else if (bndLayers.found("patchBoundaryLayers"))
			{
				const dictionary& patchLayers =
					bndLayers.subDict("patchBoundaryLayers");
				const wordList createLayers = patchLayers.toc();

				forAll(createLayers, patchI)
					bl.addLayerForPatch(createLayers[patchI]);
			}
		}

# ifdef DEBUG
		mesh_.write();
		//::exit(EXIT_FAILURE);
# endif
	}

	void voronoiMeshGenerator::refBoundaryLayers()
	{
		if (meshDict_.isDict("boundaryLayers"))
		{
			refineBoundaryLayers refLayers(mesh_);

			refineBoundaryLayers::readSettings(meshDict_, refLayers);

			refLayers.refineLayers();

			labelLongList pointsInLayer;
			refLayers.pointsInBndLayer(pointsInLayer);

			meshOptimizer mOpt(mesh_);
			mOpt.lockPoints(pointsInLayer);
			mOpt.untangleBoundaryLayer();
		}
	}

	void voronoiMeshGenerator::optimiseFinalMesh()
	{
		//- untangle the surface if needed
		bool enforceConstraints(false);
		if (meshDict_.found("enforceGeometryConstraints"))
		{
			enforceConstraints =
				readBool(meshDict_.lookup("enforceGeometryConstraints"));
		}

		if (true)
		{
			meshSurfaceEngine mse(mesh_);
			meshSurfaceOptimizer surfOpt(mse, *octreePtr_);

			if (enforceConstraints)
				surfOpt.enforceConstraints();

			surfOpt.optimizeSurface();
		}

		deleteDemandDrivenData(octreePtr_);

		//- final optimisation
		meshOptimizer optimizer(mesh_);
		if (enforceConstraints)
			optimizer.enforceConstraints();
		optimizer.optimizeMeshFV();

		optimizer.optimizeLowQualityFaces();
		optimizer.optimizeBoundaryLayer(false);
		optimizer.untangleMeshFV();

		mesh_.clearAddressingData();

		if (modSurfacePtr_)
		{
			polyMeshGenGeometryModification meshMod(mesh_, meshDict_);

			//- revert the mesh into the original space
			meshMod.revertGeometryModification();

			//- delete modified surface mesh
			deleteDemandDrivenData(modSurfacePtr_);
		}

# ifdef DEBUG
		mesh_.write();
		//::exit(0);
# endif
	}

	void voronoiMeshGenerator::projectSurfaceAfterBackScaling()
	{
		if (!meshDict_.found("anisotropicSources"))
			return;

		deleteDemandDrivenData(octreePtr_);
		octreePtr_ = new meshOctree(*surfacePtr_);

		meshOctreeCreator
		(
			*octreePtr_,
			meshDict_
		).createOctreeWithRefinedBoundary(20, 30);

		//- calculate mesh surface
		meshSurfaceEngine mse(mesh_);

		//- pre-map mesh surface
		meshSurfaceMapper mapper(mse, *octreePtr_);

		//- map mesh surface on the geometry surface
		mapper.mapVerticesOntoSurface();

		optimiseFinalMesh();
	}

	void voronoiMeshGenerator::replaceBoundaries()
	{
		renameBoundaryPatches rbp(mesh_, meshDict_);

# ifdef DEBUG
		mesh_.write();
		//::exit(0);
# endif
	}

	void voronoiMeshGenerator::renumberMesh()
	{
		polyMeshGenModifier(mesh_).renumberMesh();

# ifdef DEBUG
		mesh_.write();
		//::exit(0);
# endif
	}

	void voronoiMeshGenerator::generateMesh()
	{
		try
		{
			if (controller_.runCurrentStep("templateGeneration"))
			{
				createVoronoiMesh();
			}

			if (controller_.runCurrentStep("surfaceTopology"))
			{
				surfacePreparation();
			}

			if (controller_.runCurrentStep("surfaceProjection"))
			{
				mapMeshToSurface();
			}

			if (controller_.runCurrentStep("patchAssignment"))
			{
				extractPatches();
			}

			if (controller_.runCurrentStep("edgeExtraction"))
			{
				mapEdgesAndCorners();

				optimiseMeshSurface();
			}

			if (controller_.runCurrentStep("boundaryLayerGeneration"))
			{
				generateBoudaryLayers();
			}

			if (controller_.runCurrentStep("meshOptimisation"))
			{
				optimiseFinalMesh();

				projectSurfaceAfterBackScaling();
			}

			if (controller_.runCurrentStep("boundaryLayerRefinement"))
			{
				refBoundaryLayers();
			}

			renumberMesh();

			replaceBoundaries();
		}
		catch (const std::string& message)
		{
			Info << message << endl;
		}
		catch (...)
		{
			WarningIn
			(
				"void voronoiMeshGenerator::generateMesh()"
			) << "Meshing process terminated!" << endl;
		}
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	voronoiMeshGenerator::voronoiMeshGenerator(const Time& time)
		:
		runTime_(time),
		surfacePtr_(NULL),
		modSurfacePtr_(NULL),
		octreePtr_(NULL),
		pointRegionsPtr_(NULL),
		meshDict_
		(
			IOobject
			(
				"meshDict",
				runTime_.system(),
				runTime_,
				IOobject::MUST_READ,
				IOobject::NO_WRITE
			)
		),
		mesh_(time),
		controller_(mesh_)
	{
		if (true)
			checkMeshDict cmd(meshDict_);

		const fileName surfaceFile = meshDict_.lookup("surfaceFile");

		surfacePtr_ = new triSurf(runTime_.path() / surfaceFile);

		if (true)
		{
			//- save meta data with the mesh (surface mesh + its topology info)
			triSurfaceMetaData sMetaData(*surfacePtr_);
			const dictionary& surfMetaDict = sMetaData.metaData();

			mesh_.metaData().add("surfaceFile", surfaceFile, true);
			mesh_.metaData().add("surfaceMeta", surfMetaDict, true);
		}

		if (surfacePtr_->featureEdges().size() != 0)
		{
			//- create surface patches based on the feature edges
			//- and update the meshDict based on the given data
			triSurfacePatchManipulator manipulator(*surfacePtr_);

			const triSurf* surfaceWithPatches =
				manipulator.surfaceWithPatches(&meshDict_);

			//- delete the old surface and assign the new one
			deleteDemandDrivenData(surfacePtr_);
			surfacePtr_ = surfaceWithPatches;
		}

		if (meshDict_.found("anisotropicSources"))
		{
			surfaceMeshGeometryModification surfMod(*surfacePtr_, meshDict_);

			modSurfacePtr_ = surfMod.modifyGeometry();

			octreePtr_ = new meshOctree(*modSurfacePtr_);
		}
		else
		{
			octreePtr_ = new meshOctree(*surfacePtr_);
		}

		meshOctreeCreator(*octreePtr_, meshDict_).createOctreeBoxes();

		generateMesh();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	voronoiMeshGenerator::~voronoiMeshGenerator()
	{
		deleteDemandDrivenData(surfacePtr_);
		deleteDemandDrivenData(modSurfacePtr_);
		deleteDemandDrivenData(octreePtr_);
		deleteDemandDrivenData(pointRegionsPtr_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void voronoiMeshGenerator::writeMesh() const
	{
		mesh_.write();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //