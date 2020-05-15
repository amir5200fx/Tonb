#include <polyMeshGenGeometryModification.hxx>

#include <dictionary.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * Private member functions* * * * * * * * * * * //

	void polyMeshGenGeometryModification::checkModification()
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

	polyMeshGenGeometryModification::polyMeshGenGeometryModification
	(
		polyMeshGen& mesh,
		const dictionary& meshDict
	)
		:
		mesh_(mesh),
		meshDict_(meshDict),
		coordinateModifierPtr_(NULL),
		modificationActive_(false)
	{
		checkModification();
	}

	polyMeshGenGeometryModification::~polyMeshGenGeometryModification()
	{
		deleteDemandDrivenData(coordinateModifierPtr_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	bool polyMeshGenGeometryModification::activeModification() const
	{
		return modificationActive_;
	}

	void polyMeshGenGeometryModification::modifyGeometry()
	{
		if (!modificationActive_)
		{
			WarningIn
			(
				"const triSurf* polyMeshGenGeometryModification"
				"::modifyGeometry() const"
			) << "Modification is not active" << endl;

			return;
		}

		pointFieldPMG& pts = mesh_.points();

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(pts, pointI)
			pts[pointI] = coordinateModifierPtr_->modifiedPoint(pts[pointI]);
	}

	void polyMeshGenGeometryModification::revertGeometryModification()
	{
		if (!modificationActive_)
		{
			WarningIn
			(
				"const triSurf* polyMeshGenGeometryModification"
				"::revertGeometryModification() const"
			) << "Modification is not active" << endl;

			return;
		}

		pointFieldPMG& pts = mesh_.points();

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(pts, pointI)
			pts[pointI] =
			coordinateModifierPtr_->backwardModifiedPoint(pts[pointI]);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //