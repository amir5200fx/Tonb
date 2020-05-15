#include <polyMeshGenModifier.hxx>

#include <demandDrivenData.hxx>
#include <labelList.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void polyMeshGenModifier::removeUnusedVertices()
	{
		faceListPMG& faces = mesh_.faces_;
		pointFieldPMG& points = mesh_.points_;

		boolList usePoint(points.size(), false);
		forAll(faces, faceI)
		{
			const face& f = faces[faceI];

			forAll(f, pI)
				usePoint[f[pI]] = true;
		}

		labelLongList newLabel(points.size(), -1);
		label nPoints(0);
		forAll(points, pI)
			if (usePoint[pI])
				newLabel[pI] = nPoints++;

		//- remove unused points from the list
		forAll(newLabel, pI)
			if ((newLabel[pI] != -1) && (newLabel[pI] < pI))
			{
				points[newLabel[pI]] = points[pI];
			}

		points.setSize(nPoints);

		forAll(faces, faceI)
		{
			face& f = faces[faceI];

			forAll(f, pI)
				f[pI] = newLabel[f[pI]];
		}

		mesh_.updatePointSubsets(newLabel);

		mesh_.clearOut();
		this->clearOut();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //