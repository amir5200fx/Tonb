#include <simplexSmoother.hxx>

#include <tetrahedron.hxx>
#include <partTetMeshSimplex.hxx>

//#define DEBUGSmooth

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	simplexSmoother::simplexSmoother(partTetMeshSimplex& simplex)
		:
		points_(simplex.pts()),
		tets_(simplex.tets()),
		pointI_(tets_[0][3]),
		bb_()
	{
		point min(VGREAT, VGREAT, VGREAT), max(-VGREAT, -VGREAT, -VGREAT);
		forAll(tets_, tetI)
		{
			const partTet& pt = tets_[tetI];
			const tetrahedron<point, point> tet
			(
				points_[pt.a()],
				points_[pt.b()],
				points_[pt.c()],
				points_[pt.d()]
			);

			min = tnbLib::min(min, tet.a());
			max = tnbLib::max(max, tet.a());

			min = tnbLib::min(min, tet.b());
			max = tnbLib::max(max, tet.b());

			min = tnbLib::min(min, tet.c());
			max = tnbLib::max(max, tet.c());
		}

		bb_.max() = max;
		bb_.min() = min;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	simplexSmoother::~simplexSmoother()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Member functions

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //