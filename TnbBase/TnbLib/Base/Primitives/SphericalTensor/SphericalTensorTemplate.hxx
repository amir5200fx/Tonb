#pragma once
#ifndef _SphericalTensorTemplate_Header
#define _SphericalTensorTemplate_Header

#include <VectorSpace.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class SphericalTensor Declaration
	\*---------------------------------------------------------------------------*/

	template<class Cmpt>
	class SphericalTensor
		:
		public VectorSpace<SphericalTensor<Cmpt>, Cmpt, 1>
	{

	public:

		//- Equivalent type of labels used for valid component indexing
		typedef SphericalTensor<label> labelType;


		// Member constants

			//- Rank of SphericalTensor is 2
		static const direction rank = 2;


		// Static Data Members

		static const SphericalTensor I;
		static const SphericalTensor oneThirdI;
		static const SphericalTensor twoThirdsI;


		//- Component labeling enumeration
		enum components { II };


		// Constructors

			//- Construct null
		inline SphericalTensor();

		//- Construct initialized to zero
		inline SphericalTensor(const tnbLib::zero);

		//- Construct given VectorSpace
		template<class Cmpt2>
		inline SphericalTensor
		(
			const VectorSpace<SphericalTensor<Cmpt2>, Cmpt2, 1>&
		);

		//- Construct given the component
		inline SphericalTensor(const Cmpt& tii);

		//- Construct from Istream
		inline SphericalTensor(Istream&);


		// Member Functions

			// Access

		inline const Cmpt& ii() const;
		inline Cmpt& ii();


		//- Transpose
		inline const SphericalTensor<Cmpt>& T() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SphericalTensorTemplateI.hxx>

#endif // !_SphericalTensorTemplate_Header
