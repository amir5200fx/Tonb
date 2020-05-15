#include <volumeOptimizer.hxx>

#include <demandDrivenData.hxx>
#include <tetrahedron.hxx>
#include <partTetMeshSimplex.hxx>

//#define DEBUGSmooth

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const vector volumeOptimizer::dirVecs[8] =
	{
		vector(-1.0, -1.0, -1.0),
		vector(1.0, -1.0, -1.0),
		vector(-1.0, 1.0, -1.0),
		vector(1.0, 1.0, -1.0),
		vector(-1.0, -1.0, 1.0),
		vector(1.0, -1.0, 1.0),
		vector(-1.0, 1.0, 1.0),
		vector(1.0, 1.0, 1.0)
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	volumeOptimizer::volumeOptimizer(partTetMeshSimplex& simplex)
		:
		simplexSmoother(simplex)
	{}

	volumeOptimizer::~volumeOptimizer()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Member functions

	void volumeOptimizer::optimizeNodePosition(const scalar tol)
	{
		point& p = points_[pointI_];

		if (!bb_.contains(p))
			p = 0.5 * (bb_.max() + bb_.min());

		const scalar scale = 1.0 / bb_.mag();
		forAll(points_, pI)
			points_[pI] *= scale;
		bb_.min() *= scale;
		bb_.max() *= scale;

		//- find the optimum using divide and conquer
		const scalar func = optimiseDivideAndConquer(tol);
		const point copyP = p;

		//- check if the location can be improved using the steepest descent
		const scalar funcAfter = optimiseSteepestDescent(tol);

		if (funcAfter > func)
			p = copyP;

		//- scale back to the original size
		forAll(points_, pI)
			points_[pI] /= scale;
		bb_.min() /= scale;
		bb_.max() /= scale;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //