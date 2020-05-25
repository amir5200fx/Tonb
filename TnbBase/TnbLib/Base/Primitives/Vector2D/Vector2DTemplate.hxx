#pragma once
#ifndef _Vector2DTemplate_Header
#define _Vector2DTemplate_Header

#include <VectorSpace.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class Vector2D Declaration
	\*---------------------------------------------------------------------------*/

	template<class Cmpt>
	class Vector2D
		:
		public VectorSpace<Vector2D<Cmpt>, Cmpt, 2>
	{

	public:

		//- Equivalent type of labels used for valid component indexing
		typedef Vector2D<label> labelType;


		// Member constants

			//- Rank of Vector2D is 1
		static const direction rank = 1;


		//- Component labeling enumeration
		enum components { X, Y };


		// Constructors

			//- Construct null
		inline Vector2D();

		//- Construct initialized to zero
		inline Vector2D(const tnbLib::zero);

		//- Construct given VectorSpace
		inline Vector2D(const VectorSpace<Vector2D<Cmpt>, Cmpt, 2>&);

		//- Construct given two components
		inline Vector2D(const Cmpt& vx, const Cmpt& vy);

		//- Construct from Istream
		inline Vector2D(Istream&);


		// Member Functions

			// Access

		inline const Cmpt& x() const;
		inline const Cmpt& y() const;

		inline Cmpt& x();
		inline Cmpt& y();


		// Operators

			//- Perp dot product (dot product with perpendicular vector)
		inline scalar perp(const Vector2D<Cmpt>& b) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <Vector2DTemplateI.hxx>

#endif // !_Vector2DTemplate_Header
