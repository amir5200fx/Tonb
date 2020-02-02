#pragma once
#ifndef _surfaceInterpolation_Header
#define _surfaceInterpolation_Header

#include <tmp.hxx>
#include <scalar.hxx>
#include <fvSchemes.hxx>
#include <fvSolution.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <className.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;
	/*---------------------------------------------------------------------------*\
						 Class surfaceInterpolation Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceInterpolation
	{
		// Private data

			// Reference to fvMesh
		const fvMesh& mesh_;

		//- Discretisation schemes
		fvSchemes schemesDict_;

		//- Solver settings
		fvSolution solutionDict_;


		// Demand-driven data

			//- Central-differencing weighting factors
		mutable surfaceScalarField* weightingFactors_;

		//- Face-gradient difference factors
		mutable surfaceScalarField* differenceFactors_;

		//- Is mesh orthogonal
		mutable bool orthogonal_;

		//- Non-orthogonality correction vectors
		mutable surfaceVectorField* correctionVectors_;


		// Private member functions

			//- Construct central-differencing weighting factors
		void makeWeights() const;

		//- Construct face-gradient difference factors
		void makeDeltaCoeffs() const;

		//- Construct non-orthogonality correction vectors
		void makeCorrectionVectors() const;


	protected:

		// Protected member functions

			// Storage management

				//- Clear all geometry and addressing
		void clearOut();


	public:

		// Declare name of the class and its debug switch
		ClassName("surfaceInterpolation");


		// Constructors

			//- Construct given an fvMesh
		explicit surfaceInterpolation(const fvMesh&);


		// Destructor

		~surfaceInterpolation();


		// Member functions

			//- Return schemes
		const fvSchemes& schemesDict() const
		{
			return schemesDict_;
		}

		//- Return access to schemes
		fvSchemes& schemesDict()
		{
			return schemesDict_;
		}

		//- Return solver settings
		const fvSolution& solutionDict() const
		{
			return solutionDict_;
		}

		//- Return access to solver settings
		fvSolution& solutionDict()
		{
			return solutionDict_;
		}

		//- Return reference to weighting factors array
		const surfaceScalarField& weights() const;

		//- Return reference to difference factors array
		const surfaceScalarField& deltaCoeffs() const;

		//- Return whether mesh is orthogonal or not
		bool orthogonal() const;

		//- Return reference to non-orthogonality correction vectors array
		const surfaceVectorField& correctionVectors() const;

		//- Do what is neccessary if the mesh has moved
		bool movePoints();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceInterpolation_Header
