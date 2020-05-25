#pragma once
#ifndef _DiagTensorTemplate_Header
#define _DiagTensorTemplate_Header

#include <TensorTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class DiagTensor Declaration
	\*---------------------------------------------------------------------------*/

	template<class Cmpt>
	class DiagTensor
		:
		public VectorSpace<DiagTensor<Cmpt>, Cmpt, 3>
	{

	public:

		//- Equivalent type of labels used for valid component indexing
		typedef DiagTensor<label> labelType;


		// Member constants

			//- Rank of DiagTensor is 2
		static const direction rank = 2;


		//- Component labeling enumeration
		enum components { XX, YY, ZZ };


		// Constructors

			//- Construct null
		inline DiagTensor();

		//- Construct initialized to zero
		inline DiagTensor(const tnbLib::zero);

		//- Construct given VectorSpace
		template<class Cmpt2>
		inline DiagTensor(const VectorSpace<DiagTensor<Cmpt2>, Cmpt2, 3>&);

		//- Construct given three components
		inline DiagTensor(const Cmpt& txx, const Cmpt& tyy, const Cmpt& tzz);

		//- Construct from Istream
		inline DiagTensor(Istream&);


		// Member Functions

			// Access

		inline const Cmpt& xx() const;
		inline const Cmpt& yy() const;
		inline const Cmpt& zz() const;

		inline Cmpt& xx();
		inline Cmpt& yy();
		inline Cmpt& zz();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <DiagTensorTemplateI.hxx>

#endif // !_DiagTensorTemplate_Header
