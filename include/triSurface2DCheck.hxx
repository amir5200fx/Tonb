#pragma once
#ifndef _triSurface2DCheck_Header
#define _triSurface2DCheck_Header

#include <triSurf.hxx>
#include <symmTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class triSurface2DCheck Declaration
	\*---------------------------------------------------------------------------*/

	class triSurface2DCheck
	{
		// Private data
			//- reference to triSurf
		const triSurf& surf_;

		//- covariance matrix
		symmTensor covarianceMatrix_;

		// Private member functions
			//- create covariance matrix
		void createCovarianceMatrix();

		//- Disallow default bitwise copy construct
		triSurface2DCheck(const triSurface2DCheck&);

		//- Disallow default bitwise assignment
		void operator=(const triSurface2DCheck&);

	public:

		// Constructors

			//- Construct from octree
		triSurface2DCheck(const triSurf& surface);

		// Destructor

		~triSurface2DCheck();


		// Member Functions

			//- checks if the surface is a 2D triangulation
		bool is2DSurface() const;

		//- create subset containing invalid facets
		void createSubsets();
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_triSurface2DCheck_Header
