#include <meshUntangler.hxx>

#include <demandDrivenData.hxx>
#include <plane.hxx>

//#define DEBUGSmooth

#ifdef DEBUGSmooth
#include <foamTime.hxx>
#include <objectRegistry.hxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	meshUntangler::meshUntangler
	(
		partTetMeshSimplex& simplex
	)
		:
		simplexSmoother(simplex)
	{
	}

	meshUntangler::~meshUntangler()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshUntangler::optimizeNodePosition(const scalar tol)
	{
# ifdef DEBUGSmooth
		Info << "Untangling point " << pointI_ << endl;
# endif

		cutRegion cr(bb_);

		forAll(tets_, tetI)
		{
			const partTet& tet = tets_[tetI];
			vector n
			(
				(points_[tet.b()] - points_[tet.a()]) ^
				(points_[tet.c()] - points_[tet.a()])
			);

			if (mag(n) < VSMALL) continue;

			plane pl(points_[tet.a()], n);

# ifdef DEBUGSmooth
			Info << "tet.a() " << tet.a() << endl;
			Info << "Cutting plane ref point " << pl.refPoint() << endl;
			Info << "Cutting plane normal " << pl.normal() << endl;
# endif

			cr.planeCut(pl);
		}

		if (cr.points().size())
		{
			point p(vector::zero);

			const DynList<point, 64>& pts = cr.points();
			forAll(pts, pI)
				p += pts[pI];

			p /= pts.size();

# ifdef DEBUGSmooth
			Info << "Corners of the feasible region " << pts << endl;
# endif

			for (direction i = 0; i < vector::nComponents; ++i)
			{
				const scalar& val = p[i];
				if ((val != val) || ((val - val) != (val - val)))
					return;
			}

			points_[pointI_] = p;
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //