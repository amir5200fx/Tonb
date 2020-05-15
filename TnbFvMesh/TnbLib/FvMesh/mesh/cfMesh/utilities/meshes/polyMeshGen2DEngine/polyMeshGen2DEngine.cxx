#include <polyMeshGen2DEngine.hxx>

#include <polyMeshGenAddressing.hxx>
#include <demandDrivenData.hxx>
#include <Pstream.hxx>
#include <PstreamReduceOps.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void polyMeshGen2DEngine::findActiveFaces() const
	{
		const faceListPMG& faces = mesh_.faces();
		const boolList& zMinPoints = this->zMinPoints();
		const boolList& zMaxPoints = this->zMaxPoints();

		activeFacePtr_ = new boolList(faces.size());

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(faces, faceI)
		{
			bool hasZMin(false), hasZMax(false);

			const face& f = faces[faceI];
			forAll(f, pI)
			{
				hasZMin |= zMinPoints[f[pI]];
				hasZMax |= zMaxPoints[f[pI]];
			}

			activeFacePtr_->operator[](faceI) = (hasZMin && hasZMax);
		}
	}

	void polyMeshGen2DEngine::findActiveFaceLabels() const
	{
		const boolList& activeFace = this->activeFace();

		label counter(0);

		forAll(activeFace, faceI)
			if (activeFace[faceI])
				++counter;

		activeFaceLabelsPtr_ = new labelList(counter);

		counter = 0;
		forAll(activeFace, faceI)
			if (activeFace[faceI])
				activeFaceLabelsPtr_->operator[](counter++) = faceI;
	}

	void polyMeshGen2DEngine::findZMinPoints() const
	{
		const pointFieldPMG& points = mesh_.points();

		zMinPointPtr_ = new boolList(points.size());

		const scalar tZ = 0.05 * (bb_.max().z() - bb_.min().z());;

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(points, pointI)
		{
			if (tnbLib::mag(points[pointI].z() - bb_.min().z()) < tZ)
			{
				zMinPointPtr_->operator[](pointI) = true;
			}
			else
			{
				zMinPointPtr_->operator[](pointI) = false;
			}
		}
	}

	void polyMeshGen2DEngine::findZMinPointLabels() const
	{
		const boolList& zMinPoints = this->zMinPoints();

		label counter(0);

		forAll(zMinPoints, pointI)
			if (zMinPoints[pointI])
				++counter;

		if (2 * counter != zMinPoints.size())
		{
			FatalErrorIn
			(
				"void polyMeshGen2DEngine::findZMinPointLabels()"
			) << "The number of points at smallest z coordinate is"
				<< " not half of the total number of points."
				<< " This is not a 2D mesh or is not aligned with the z axis"
				<< exit(FatalError);
		}

		zMinPointLabelsPtr_ = new labelList(counter);

		counter = 0;
		forAll(zMinPoints, pointI)
			if (zMinPoints[pointI])
				zMinPointLabelsPtr_->operator[](counter++) = pointI;
	}

	void polyMeshGen2DEngine::findZMinOffsetPoints() const
	{
		const boolList& zMinPoints = this->zMinPoints();
		const labelList& zMinPointLabels = this->zMinPointLabels();

		zMinToZMaxPtr_ = new labelList(zMinPointLabels.size());

		const VRWGraph& pointPoints = mesh_.addressingData().pointPoints();
# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(zMinPointLabels, pI)
		{
			const label pointI = zMinPointLabels[pI];

			label nInactive(0), offsetPoint(-1);
			forAllRow(pointPoints, pointI, ppI)
			{
				if (!zMinPoints[pointPoints(pointI, ppI)])
				{
					++nInactive;
					offsetPoint = pointPoints(pointI, ppI);
				}
			}

			if (nInactive == 1)
			{
				zMinToZMaxPtr_->operator[](pI) = offsetPoint;
			}
			else
			{
				FatalErrorIn
				(
					"void polyMeshGen2DEngine::findZMinOffsetPoints()"
				) << "This cannot be a 2D mesh" << exit(FatalError);
			}
		}
	}

	void polyMeshGen2DEngine::findZMaxPoints() const
	{
		const pointFieldPMG& points = mesh_.points();

		zMaxPointPtr_ = new boolList(points.size());

		const scalar tZ = 0.05 * (bb_.max().z() - bb_.min().z());

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(points, pointI)
		{
			if (tnbLib::mag(points[pointI].z() - bb_.max().z()) < tZ)
			{
				zMaxPointPtr_->operator[](pointI) = true;
			}
			else
			{
				zMaxPointPtr_->operator[](pointI) = false;
			}
		}
	}

	void polyMeshGen2DEngine::findZMaxPointLabels() const
	{
		const boolList& zMaxPoints = this->zMaxPoints();

		label counter(0);

		forAll(zMaxPoints, pointI)
			if (zMaxPoints[pointI])
				++counter;

		if (2 * counter != zMaxPoints.size())
		{
			FatalErrorIn
			(
				"void polyMeshGen2DEngine::findZMaxPointLabels()"
			) << "The number of points at largest z coordinate is"
				<< " not half of the total number of points."
				<< " This is not a 2D mesh or is not aligned with the z axis"
				<< exit(FatalError);
		}

		zMaxPointLabelsPtr_ = new labelList(counter);

		counter = 0;
		forAll(zMaxPoints, pointI)
			if (zMaxPoints[pointI])
				zMaxPointLabelsPtr_->operator[](counter++) = pointI;
	}

	void polyMeshGen2DEngine::findZMaxOffsetPoints() const
	{
		const boolList& zMaxPoints = this->zMaxPoints();
		const labelList& zMaxPointLabels = this->zMaxPointLabels();

		zMaxToZMinPtr_ = new labelList(zMaxPointLabels.size());

		const VRWGraph& pointPoints = mesh_.addressingData().pointPoints();
# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(zMaxPointLabels, pI)
		{
			const label pointI = zMaxPointLabels[pI];

			label nInactive(0), offsetPoint(-1);
			forAllRow(pointPoints, pointI, ppI)
			{
				if (!zMaxPoints[pointPoints(pointI, ppI)])
				{
					++nInactive;
					offsetPoint = pointPoints(pointI, ppI);
				}
			}

			if (nInactive == 1)
			{
				zMaxToZMinPtr_->operator[](pI) = offsetPoint;
			}
			else
			{
				FatalErrorIn
				(
					"void polyMeshGen2DEngine::findZMaxOffsetPoints()"
				) << "This cannot be a 2D mesh" << exit(FatalError);
			}
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	polyMeshGen2DEngine::polyMeshGen2DEngine(const polyMeshGen& mesh)
		:
		mesh_(mesh),
		bb_(),
		activeFacePtr_(NULL),
		activeFaceLabelsPtr_(NULL),
		zMinPointPtr_(NULL),
		zMinPointLabelsPtr_(NULL),
		zMinToZMaxPtr_(NULL),
		zMaxPointPtr_(NULL),
		zMaxPointLabelsPtr_(NULL),
		zMaxToZMinPtr_(NULL)
	{
		const pointFieldPMG& points = mesh_.points();

		bb_.min() = point(VGREAT, VGREAT, VGREAT);
		bb_.max() = point(-VGREAT, -VGREAT, -VGREAT);

# ifdef USE_OMP
# pragma omp parallel
# endif
		{
			point localMin(VGREAT, VGREAT, VGREAT);
			point localMax(-VGREAT, -VGREAT, -VGREAT);

# ifdef USE_OMP
# pragma omp for schedule(dynamic, 50)
# endif
			forAll(points, pointI)
			{
				localMin = tnbLib::min(localMin, points[pointI]);
				localMax = tnbLib::max(localMax, points[pointI]);
			}

# ifdef USE_OMP
# pragma omp critical
# endif
			{
				bb_.min() = tnbLib::min(bb_.min(), localMin);
				bb_.max() = tnbLib::max(bb_.max(), localMax);
			}
		}

		if (Pstream::parRun())
		{
			reduce(bb_.min(), minOp<point>());
			reduce(bb_.max(), maxOp<point>());
		}
	}

	polyMeshGen2DEngine::~polyMeshGen2DEngine()
	{
		clearOut();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void polyMeshGen2DEngine::correctPoints()
	{
		pointFieldPMG& points = const_cast<pointFieldPMG&>(mesh_.points());

		const labelList& zMinPointLabels = this->zMinPointLabels();
		const labelList& zMinOffset = this->zMinToZMax();

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(zMinPointLabels, apI)
		{
			point& p = points[zMinPointLabels[apI]];
			point& op = points[zMinOffset[apI]];

			op.x() = p.x();
			op.y() = p.y();
			p.z() = bb_.min().z();
			op.z() = bb_.max().z();
		}
	}

	void polyMeshGen2DEngine::clearOut()
	{
		deleteDemandDrivenData(activeFacePtr_);
		deleteDemandDrivenData(activeFaceLabelsPtr_);
		deleteDemandDrivenData(zMinPointPtr_);
		deleteDemandDrivenData(zMinPointLabelsPtr_);
		deleteDemandDrivenData(zMinToZMaxPtr_);
		deleteDemandDrivenData(zMaxPointPtr_);
		deleteDemandDrivenData(zMaxPointLabelsPtr_);
		deleteDemandDrivenData(zMaxToZMinPtr_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //