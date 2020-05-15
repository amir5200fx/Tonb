#include <meshSurfaceOptimizer.hxx>

#include <demandDrivenData.hxx>
#include <meshSurfaceEngine.hxx>

//#define DEBUGTriangulation

# ifdef DEBUGTriangulation
#include <triSurf.hxx>
#include <triSurfModifier.hxx>
#include <helperFunctions.hxx>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshSurfaceOptimizer::calculateTrianglesAndAddressing() const
	{
		if (triMeshPtr_)
			FatalErrorIn
			(
				"void meshSurfaceOptimizer::calculateTrianglesAndAddressing() const"
			) << "Addressing is already calculated!" << abort(FatalError);

		triMeshPtr_ = new partTriMesh(*partitionerPtr_);

# ifdef DEBUGTriangulation
		const labelList& sPoints = triMeshPtr_->meshSurfacePointLabelInTriMesh();

		forAll(sPoints, bpI)
		{
			triSurf surf;

			const label spI = sPoints[bpI];

			partTriMeshSimplex simplex(*triMeshPtr_, spI);

			triSurfModifier sMod(surf);

			pointField& pts = sMod.pointsAccess();
			pts.setSize(simplex.pts().size());
			forAll(pts, i)
				pts[i] = simplex.pts()[i];

			LongList<labelledTri>& trias = sMod.facetsAccess();
			trias.setSize(simplex.triangles().size());
			forAll(trias, i)
			{
				const triFace& t = simplex.triangles()[i];
				trias[i] = labelledTri(t[0], t[1], t[2], 0);
			}

			sMod.patchesAccess().setSize(1);
			sMod.patchesAccess()[0].name() = "bnd";
			sMod.patchesAccess()[0].geometricType() = "patch";

			fileName sName("bndPointSimplex_");
			sName += help::scalarToText(bpI);
			sName += ".stl";
			surf.writeSurface(sName);
		}
# endif
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //