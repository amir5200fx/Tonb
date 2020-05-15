#include <edgeMeshGeometryModification.hxx>

#include <demandDrivenData.hxx>
#include <dictionary.hxx>
#include <edgeMesh.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * Private member functions* * * * * * * * * * * //

	void edgeMeshGeometryModification::checkModification()
	{
		if (meshDict_.found("anisotropicSources"))
		{
			modificationActive_ = true;

			const dictionary& anisotropicDict =
				meshDict_.subDict("anisotropicSources");

			coordinateModifierPtr_ = new coordinateModifier(anisotropicDict);
		}
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	edgeMeshGeometryModification::edgeMeshGeometryModification
	(
		const edgeMesh& em,
		const dictionary& meshDict
	)
		:
		edgeMesh_(em),
		meshDict_(meshDict),
		coordinateModifierPtr_(NULL),
		modificationActive_(false)
	{
		checkModification();
	}

	edgeMeshGeometryModification::~edgeMeshGeometryModification()
	{
		deleteDemandDrivenData(coordinateModifierPtr_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	bool edgeMeshGeometryModification::activeModification() const
	{
		return modificationActive_;
	}

	const edgeMesh* edgeMeshGeometryModification::modifyGeometry() const
	{
		if (!modificationActive_)
		{
			WarningIn
			(
				"const edgeMesh* edgeMeshGeometryModification"
				"::modifyGeometry() const"
			) << "Modification is not active" << endl;

			return NULL;
		}

		const pointField& pts = edgeMesh_.points();

		pointField newPts(pts.size());

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(pts, pointI)
			newPts[pointI] = coordinateModifierPtr_->modifiedPoint(pts[pointI]);

		const edgeMesh* newEdgeMesh = new edgeMesh(newPts, edgeMesh_.edges());

		return newEdgeMesh;
	}

	const edgeMesh* edgeMeshGeometryModification::
		revertGeometryModification() const
	{
		if (!modificationActive_)
		{
			WarningIn
			(
				"const edgeMesh* edgeMeshGeometryModification"
				"::revertGeometryModification() const"
			) << "Modification is not active" << endl;

			return NULL;
		}

		const pointField& pts = edgeMesh_.points();

		pointField newPts(pts.size());

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(pts, pointI)
		{
			newPts[pointI] =
				coordinateModifierPtr_->backwardModifiedPoint(pts[pointI]);
		}

		const edgeMesh* newEdgeMeshPtr = new edgeMesh(newPts, edgeMesh_.edges());

		return newEdgeMeshPtr;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //