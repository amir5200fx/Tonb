#include <meshOptimizer.hxx>

#include <demandDrivenData.hxx>
#include <meshSurfaceEngine.hxx>
#include <meshSurfacePartitioner.hxx>
#include <polyMeshGenAddressing.hxx>
#include <polyMeshGenChecks.hxx>
#include <labelLongList.hxx>
#include <Pstream.hxx>
#include <PstreamReduceOps.hxx>

// #define DEBUGSmoothing

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * Private member functions * * * * * * * * * * * * * * * * * //

	const meshSurfaceEngine& meshOptimizer::meshSurface() const
	{
		if (!msePtr_)
			msePtr_ = new meshSurfaceEngine(mesh_);

		return *msePtr_;
	}

	void meshOptimizer::clearSurface()
	{
		deleteDemandDrivenData(msePtr_);
	}

	label meshOptimizer::findBadFaces
	(
		labelHashSet& badFaces,
		const boolList& changedFace
	) const
	{
		badFaces.clear();

		polyMeshGenChecks::checkFacePyramids
		(
			mesh_,
			false,
			VSMALL,
			&badFaces,
			&changedFace
		);

		polyMeshGenChecks::checkFaceFlatness
		(
			mesh_,
			false,
			0.8,
			&badFaces,
			&changedFace
		);

		polyMeshGenChecks::checkCellPartTetrahedra
		(
			mesh_,
			false,
			VSMALL,
			&badFaces,
			&changedFace
		);

		polyMeshGenChecks::checkFaceAreas
		(
			mesh_,
			false,
			VSMALL,
			&badFaces,
			&changedFace
		);

		const label nBadFaces = returnReduce(badFaces.size(), sumOp<label>());

		return nBadFaces;
	}

	label meshOptimizer::findLowQualityFaces
	(
		labelHashSet& badFaces,
		const boolList& changedFace
	) const
	{
		badFaces.clear();

		polyMeshGenChecks::checkFaceDotProduct
		(
			mesh_,
			false,
			70.0,
			&badFaces
		);

		polyMeshGenChecks::checkFaceSkewness
		(
			mesh_,
			false,
			2.0,
			&badFaces
		);

		const label nBadFaces = returnReduce(badFaces.size(), sumOp<label>());

		return nBadFaces;
	}

	void meshOptimizer::calculatePointLocations()
	{
		vertexLocation_.setSize(mesh_.points().size());
		vertexLocation_ = INSIDE;

		const meshSurfaceEngine& mse = meshSurface();
		const labelList& bPoints = mse.boundaryPoints();

		//- mark boundary vertices
		forAll(bPoints, bpI)
			vertexLocation_[bPoints[bpI]] = BOUNDARY;

		//- mark edge vertices
		meshSurfacePartitioner mPart(mse);
		forAllConstIter(labelHashSet, mPart.edgePoints(), it)
			vertexLocation_[bPoints[it.key()]] = EDGE;

		//- mark corner vertices
		forAllConstIter(labelHashSet, mPart.corners(), it)
			vertexLocation_[bPoints[it.key()]] = CORNER;

		if (Pstream::parRun())
		{
			const polyMeshGenAddressing& addresing = mesh_.addressingData();
			const VRWGraph& pointAtProcs = addresing.pointAtProcs();

			forAll(pointAtProcs, pointI)
				if (pointAtProcs.sizeOfRow(pointI) != 0)
					vertexLocation_[pointI] |= PARALLELBOUNDARY;
		}
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from mesh
	meshOptimizer::meshOptimizer(polyMeshGen& mesh)
		:
		mesh_(mesh),
		vertexLocation_(),
		lockedFaces_(),
		msePtr_(NULL),
		enforceConstraints_(false),
		badPointsSubsetName_()
	{
		calculatePointLocations();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshOptimizer::~meshOptimizer()
	{
		clearSurface();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshOptimizer::enforceConstraints(const word subsetName)
	{
		enforceConstraints_ = true;

		badPointsSubsetName_ = subsetName;
	}

	void meshOptimizer::lockCellsInSubset(const word& subsetName)
	{
		//- lock the points in the cell subset with the given name
		label subsetI = mesh_.cellSubsetIndex(subsetName);
		if (subsetI >= 0)
		{
			labelLongList lc;
			mesh_.cellsInSubset(subsetI, lc);

			lockCells(lc);
		}
		else
		{
			Warning << "Subset " << subsetName << " is not a cell subset!"
				<< " Cannot lock cells!" << endl;
		}
	}

	void meshOptimizer::lockFacesInSubset(const word& subsetName)
	{
		//- lock the points in the face subset with the given name
		label subsetI = mesh_.faceSubsetIndex(subsetName);
		if (subsetI >= 0)
		{
			labelLongList lf;
			mesh_.facesInSubset(subsetI, lf);

			lockFaces(lf);
		}
		else
		{
			Warning << "Subset " << subsetName << " is not a face subset!"
				<< " Cannot lock faces!" << endl;
		}
	}

	void meshOptimizer::lockPointsInSubset(const word& subsetName)
	{
		//- lock the points in the point subset with the given name
		label subsetI = mesh_.pointSubsetIndex(subsetName);
		if (subsetI >= 0)
		{
			labelLongList lp;
			mesh_.pointsInSubset(subsetI, lp);

			lockCells(lp);
		}
		else
		{
			Warning << "Subset " << subsetName << " is not a point subset!"
				<< " Cannot lock points!" << endl;
		}
	}

	void meshOptimizer::removeUserConstraints()
	{
		lockedFaces_.setSize(0);

		//- unlock points
# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(vertexLocation_, i)
		{
			if (vertexLocation_[i] & LOCKED)
				vertexLocation_[i] ^= LOCKED;
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //