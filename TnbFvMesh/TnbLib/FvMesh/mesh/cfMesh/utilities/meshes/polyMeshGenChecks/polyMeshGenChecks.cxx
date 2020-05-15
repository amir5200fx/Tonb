#include <polyMeshGenChecks.hxx>

#include <polyMeshGenAddressing.hxx>
#include <pyramidPointFaceRef.hxx>
#include <tetrahedron.hxx>
#include <cell.hxx>
#include <mathematicalConstants.hxx>
#include <ListOps.hxx>
#include <Map.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace polyMeshGenChecks
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		bool checkGeometry(const polyMeshGen& mesh, const bool report)
		{
			label noFailedChecks(0);

			if (checkClosedBoundary(mesh, report)) ++noFailedChecks;
			if (checkClosedCells(mesh, report)) ++noFailedChecks;
			if (checkFaceAreas(mesh, report)) ++noFailedChecks;
			if (checkCellVolumes(mesh, report)) ++noFailedChecks;
			if (checkFaceDotProduct(mesh, report)) ++noFailedChecks;
			if (checkFaceUniformity(mesh, report)) ++noFailedChecks;
			if (checkFacePyramids(mesh, report)) ++noFailedChecks;
			if (checkFaceSkewness(mesh, report)) ++noFailedChecks;
			if (checkCellPartTetrahedra(mesh, report)) ++noFailedChecks;

			if (noFailedChecks == 0)
			{
				if (report)
					Info << "Mesh geometry OK." << endl;

				return false;
			}
			else
			{
				Info << "Failed " << noFailedChecks << " mesh geometry checks." << endl;

				return true;
			}
		}

		bool checkTopology(const polyMeshGen& mesh, const bool report)
		{
			label noFailedChecks(0);

			if (checkPoints(mesh, report)) ++noFailedChecks;
			if (checkUpperTriangular(mesh, report)) ++noFailedChecks;
			if (checkCellsZipUp(mesh, report)) ++noFailedChecks;
			if (checkFaceVertices(mesh, report)) ++noFailedChecks;

			if (noFailedChecks == 0)
			{
				if (report)
					Info << "Mesh topology OK." << endl;

				return false;
			}
			else
			{
				Info << "Failed " << noFailedChecks << " mesh topology checks." << endl;

				return true;
			}
		}

		bool checkMesh(const polyMeshGen& mesh, const bool report)
		{
			bool failedChecks = checkTopology(mesh, report);
			failedChecks |= checkGeometry(mesh, report);

			if (!failedChecks)
			{
				if (report)
					Info << "Mesh OK." << endl;

				return false;
			}
			else
			{
				Info << "Failed some mesh checks." << endl;

				return true;
			}
		}

	} // End namespace polyMeshGenChecks

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //