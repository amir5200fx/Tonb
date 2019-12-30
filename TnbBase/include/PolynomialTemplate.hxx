#pragma once
#ifndef _PolynomialTemplate_Header
#define _PolynomialTemplate_Header

#include <word.hxx>
#include <scalar.hxx>
#include <Ostream.hxx>
#include <VectorSpace.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	template<int PolySize>
	class Polynomial;

	// Forward declaration of friend functions
	template<int PolySize>
	Ostream& operator<<
		(
			Ostream&,
			const Polynomial<PolySize>&
			);


	/*---------------------------------------------------------------------------*\
							Class Polynomial Declaration
	\*---------------------------------------------------------------------------*/

	template<int PolySize>
	class Polynomial
		: public VectorSpace<Polynomial<PolySize>, scalar, PolySize>
	{

		typedef VectorSpace<Polynomial<PolySize>, scalar, PolySize>
			base;
		// Private data

			//- Include the log term? - only activated using integrateMinus1()
		bool logActive_;

		//- Log coefficient - only activated using integrateMinus1()
		scalar logCoeff_;


	public:

		typedef Polynomial<PolySize> polyType;

		typedef Polynomial<PolySize + 1> intPolyType;


		// Constructors

			//- Construct null
		Polynomial();

		//- Construct from name and Istream
		Polynomial(const word& name, Istream& is);

		//- Copy constructor
		Polynomial(const Polynomial& poly);


		// Member Functions

			// Access

				//- Return access to the log term active flag
		bool& logActive();

		//- Return access to the log coefficient
		scalar& logCoeff();


		// Evaluation

			//- Return polynomial value
		scalar evaluate(const scalar x) const;

		//- Return integrated polynomial coefficients
		//  argument becomes zeroth element (constant of integration)
		intPolyType integrate(const scalar intConstant = 0.0);

		//- Return integrated polynomial coefficients when lowest order
		//  is -1. Argument added to zeroth element
		polyType integrateMinus1(const scalar intConstant = 0.0);

		//- Integrate between two values
		scalar integrateLimits(const scalar x1, const scalar x2) const;


		//- Ostream Operator
		friend Ostream& operator<< <PolySize>
			(
				Ostream&,
				const Polynomial&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <PolynomialTemplate.cxx>
#   include <PolynomialTemplateIO.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !1
