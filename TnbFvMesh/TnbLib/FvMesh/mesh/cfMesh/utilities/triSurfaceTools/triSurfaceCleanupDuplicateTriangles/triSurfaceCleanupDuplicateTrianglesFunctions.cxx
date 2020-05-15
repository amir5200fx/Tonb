#include <triSurfaceCleanupDuplicateTriangles.hxx>

#include <triSurfModifier.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void triSurfaceCleanupDuplicateTriangles::checkDuplicateTriangles()
	{
		labelLongList newTriangleLabel(surf_.size(), -1);

		const VRWGraph& pointTriangles = surf_.pointFacets();

		//- check if there exist duplicate triangles
		label counter(0);

		forAll(surf_, triI)
		{
			if (newTriangleLabel[triI] != -1)
				continue;

			newTriangleLabel[triI] = counter;
			++counter;

			const labelledTri& tri = surf_[triI];

			forAll(pointTriangles[tri[0]], ptI)
			{
				const label triJ = pointTriangles(tri[0], ptI);

				if (triJ <= triI)
					continue;

				const labelledTri& otherTri = surf_[triJ];

				if (tri == otherTri)
					newTriangleLabel[triJ] = newTriangleLabel[triI];
			}
		}

		Info << "Found " << (newTriangleLabel.size() - counter)
			<< " duplicate triangles" << endl;

		//- return if there exist no duplicate triangles
		if (counter == newTriangleLabel.size())
			return;

		Info << "Current number of triangles" << surf_.size() << endl;
		Info << "New number of triangles " << counter << endl;

		//- create new list of triangles and store it in the surface mesh
		LongList<labelledTri> newTriangles(counter);

		forAll(newTriangleLabel, triI)
		{
			newTriangles[newTriangleLabel[triI]] = surf_[triI];
		}

		triSurfModifier(surf_).facetsAccess().transfer(newTriangles);
		surf_.updateFacetsSubsets(newTriangleLabel);

		surf_.clearAddressing();
		surf_.clearGeometry();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //