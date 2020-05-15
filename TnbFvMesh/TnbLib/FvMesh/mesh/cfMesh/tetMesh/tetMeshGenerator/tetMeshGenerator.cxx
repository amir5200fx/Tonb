#include <tetMeshGenerator.hxx>
#include <triSurf.hxx>
#include <demandDrivenData.hxx>
#include <tnbTime.hxx>
#include <meshOctreeCreator.hxx>
#include <tetMeshExtractorOctree.hxx>
#include <meshSurfaceEngine.hxx>
#include <meshSurfaceMapper.hxx>
#include <edgeExtractor.hxx>
#include <meshSurfaceEdgeExtractorNonTopo.hxx>
#include <surfaceMorpherCells.hxx>
#include <meshOptimizer.hxx>
#include <meshSurfaceOptimizer.hxx>
#include <topologicalCleaner.hxx>
#include <boundaryLayers.hxx>
#include <renameBoundaryPatches.hxx>
#include <checkMeshDict.hxx>
#include <triSurfacePatchManipulator.hxx>
#include <refineBoundaryLayers.hxx>
#include <triSurfaceMetaData.hxx>
#include <polyMeshGenGeometryModification.hxx>
#include <surfaceMeshGeometryModification.hxx>

//#define DEBUG

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * Private member functions  * * * * * * * * * * * * //

	void tetMeshGenerator::createTetMesh()
	{
		//- create tet Mesh from octree and Delaunay tets
		tetMeshExtractorOctree tme(*octreePtr_, meshDict_, mesh_);

		tme.createMesh();
	}

	void tetMeshGenerator::surfacePreparation()
	{
		//- removes unnecessary cells and morph the boundary
		//- such that there is only one boundary face per cell
		//- It also checks topology of cells after morphing is performed
		do
		{
			surfaceMorpherCells* cmPtr = new surfaceMorpherCells(mesh_);
			cmPtr->morphMesh();
			deleteDemandDrivenData(cmPtr);
		} while (topologicalCleaner(mesh_).cleanTopology());
	}

	void tetMeshGenerator::mapMeshToSurface()
	{
		//- calculate mesh surface
		meshSurfaceEngine* msePtr = new meshSurfaceEngine(mesh_);

		//- map mesh surface on the geometry surface
		meshSurfaceMapper(*msePtr, *octreePtr_).mapVerticesOntoSurface();

		//- untangle surface faces
		meshSurfaceOptimizer(*msePtr, *octreePtr_).untangleSurface();

		deleteDemandDrivenData(msePtr);
	}

	void tetMeshGenerator::extractPatches()
	{
		edgeExtractor extractor(mesh_, *octreePtr_);

		Info << "Extracting edges" << endl;
		extractor.extractEdges();

		extractor.updateMeshPatches();
	}

	void tetMeshGenerator::mapEdgesAndCorners()
	{
		meshSurfaceEdgeExtractorNonTopo(mesh_, *octreePtr_);
	}

	void tetMeshGenerator::optimiseMeshSurface()
	{
		meshSurfaceEngine mse(mesh_);
		meshSurfaceOptimizer(mse, *octreePtr_).optimizeSurface();
	}

	void tetMeshGenerator::generateBoundaryLayers()
	{
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
	}

	void tetMeshGenerator::optimiseFinalMesh()
	{
		//- final optimisation
		bool enforceConstraints(false);
		if (meshDict_.found("enforceGeometryConstraints"))
		{
			enforceConstraints =
				readBool(meshDict_.lookup("enforceGeometryConstraints"));
		}

		meshOptimizer optimizer(mesh_);
		if (enforceConstraints)
			optimizer.enforceConstraints();

		optimizer.optimizeSurface(*octreePtr_);

		optimizer.optimizeMeshFV();
		optimizer.optimizeLowQualityFaces();
		optimizer.optimizeBoundaryLayer(false);
		optimizer.untangleMeshFV();

		deleteDemandDrivenData(octreePtr_);

		mesh_.clearAddressingData();

		if (modSurfacePtr_)
		{
			polyMeshGenGeometryModification meshMod(mesh_, meshDict_);

			//- revert the mesh into the original space
			meshMod.revertGeometryModification();

			//- delete modified surface mesh
			deleteDemandDrivenData(modSurfacePtr_);
		}
	}

	void tetMeshGenerator::projectSurfaceAfterBackScaling()
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

	void tetMeshGenerator::refBoundaryLayers()
	{
		if (meshDict_.isDict("boundaryLayers"))
		{
			refineBoundaryLayers refLayers(mesh_);

			refineBoundaryLayers::readSettings(meshDict_, refLayers);

			refLayers.refineLayers();

			labelLongList pointsInLayer;
			refLayers.pointsInBndLayer(pointsInLayer);

			meshOptimizer opt(mesh_);
			opt.lockPoints(pointsInLayer);
			opt.untangleBoundaryLayer();
		}
	}

	void tetMeshGenerator::replaceBoundaries()
	{
		renameBoundaryPatches rbp(mesh_, meshDict_);
	}

	void tetMeshGenerator::renumberMesh()
	{
		polyMeshGenModifier(mesh_).renumberMesh();
	}

	void tetMeshGenerator::generateMesh()
	{
		try
		{
			if (controller_.runCurrentStep("templateGeneration"))
			{
				createTetMesh();
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
				generateBoundaryLayers();
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

			controller_.workflowCompleted();
		}
		catch (const std::string& message)
		{
			Info << message << endl;
		}
		catch (...)
		{
			WarningIn
			(
				"void tetMeshGenerator::generateMesh()"
			) << "Meshing process terminated!" << endl;
		}
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from Time
	tetMeshGenerator::tetMeshGenerator(const Time& time)
		:
		runTime_(time),
		surfacePtr_(NULL),
		modSurfacePtr_(NULL),
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
		octreePtr_(NULL),
		mesh_(time),
		controller_(mesh_)
	{
		if (true)
		{
			checkMeshDict cmd(meshDict_);
		}

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

	tetMeshGenerator::~tetMeshGenerator()
	{
		deleteDemandDrivenData(surfacePtr_);
		deleteDemandDrivenData(octreePtr_);
		deleteDemandDrivenData(modSurfacePtr_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void tetMeshGenerator::writeMesh() const
	{
		mesh_.write();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //