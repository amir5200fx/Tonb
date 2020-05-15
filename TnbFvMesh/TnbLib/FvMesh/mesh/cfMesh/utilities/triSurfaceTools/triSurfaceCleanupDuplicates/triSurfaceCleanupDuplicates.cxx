#include <triSurfaceCleanupDuplicates.hxx>

#include <meshOctree.hxx>
#include <demandDrivenData.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	triSurfaceCleanupDuplicates::triSurfaceCleanupDuplicates
	(
		const meshOctree& octree,
		const scalar tol
	)
		:
		tolerance_(tol),
		surf_(const_cast<triSurf&>(octree.surface())),
		octree_(octree),
		newTriangleLabel_(),
		done_(false)
	{}

	triSurfaceCleanupDuplicates::~triSurfaceCleanupDuplicates()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void triSurfaceCleanupDuplicates::mergeIdentities()
	{
		if (Pstream::parRun())
			FatalError << "Material detection does not run in parallel"
			<< exit(FatalError);

		if (done_)
		{
			WarningIn("void triSurfaceCleanupDuplicates::mergeIdentities()")
				<< "Operation is already performed" << endl;
			return;
		}

		newTriangleLabel_.setSize(surf_.size());
		forAll(newTriangleLabel_, triI)
			newTriangleLabel_[triI] = triI;

		bool finished;
		do
		{
			finished = true;

			if (checkDuplicateTriangles())
				finished = false;
			if (mergeDuplicatePoints())
				finished = false;
		} while (!finished);

		done_ = true;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //