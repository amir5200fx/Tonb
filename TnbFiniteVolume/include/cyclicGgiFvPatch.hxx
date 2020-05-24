#pragma once
#ifndef _cyclicGgiFvPatch_Header
#define _cyclicGgiFvPatch_Header

#include <ggiFvPatch.hxx>
#include <cyclicGgiPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class cyclicGgiFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicGgiFvPatch
		: public ggiFvPatch
	{
		// Private Data

			//- Reference to polyPatch
		const cyclicGgiPolyPatch& cyclicGgiPolyPatch_;


	protected:

		// Protected Member functions

			//- Make patch weighting factors
		virtual void makeWeights(scalarField&) const;

		//- Make patch face - neighbour cell distances
		virtual void makeDeltaCoeffs(scalarField&) const;


	public:

		//- Runtime type information
		TypeName(cyclicGgiPolyPatch::typeName_());


		// Constructors

			//- Construct from components
		cyclicGgiFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			ggiFvPatch(patch, bm),
			cyclicGgiPolyPatch_(refCast<const cyclicGgiPolyPatch>(patch))
		{}


		// Destructor

		virtual ~cyclicGgiFvPatch()
		{}


		// Member functions

			// Access

				//- Return shadow patch
		const cyclicGgiFvPatch& shadow() const;

		//- Interpolate face field
		template<class Type>
		tmp<Field<Type> > interpolate(const Field<Type>& pf) const
		{
			return cyclicGgiPolyPatch_.interpolate(pf);
		}

		template<class Type>
		tmp<Field<Type> > interpolate(const tmp<Field<Type> >& tpf) const
		{
			return cyclicGgiPolyPatch_.interpolate(tpf);
		}

		//- Return delta (P to N) vectors across coupled patch
		virtual tmp<vectorField> delta() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicGgiFvPatch_Header
