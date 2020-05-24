#pragma once
#ifndef _wedgeFvPatch_Header
#define _wedgeFvPatch_Header

#include <fvPatch.hxx>
#include <wedgePolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class wedgeFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class wedgeFvPatch
		:
		public fvPatch
	{
		// Private data

		const wedgePolyPatch& wedgePolyPatch_;

	protected:

		// Protected Member Functions

			//- Make patch face non-orthogonality correction vectors
		virtual void makeCorrVecs(vectorField&) const;


	public:

		//- Runtime type information
		TypeName(wedgePolyPatch::typeName_());


		// Constructors

			//- Construct from polyPatch
		wedgeFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm);


		// Destructor

		virtual ~wedgeFvPatch()
		{}


		// Member functions

			// Access

				//- Return face transformation tensor
		const tensor& faceT() const
		{
			return wedgePolyPatch_.faceT();
		}

		//- Return neighbour-cell transformation tensor
		const tensor& cellT() const
		{
			return wedgePolyPatch_.cellT();
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wedgeFvPatch_Header
