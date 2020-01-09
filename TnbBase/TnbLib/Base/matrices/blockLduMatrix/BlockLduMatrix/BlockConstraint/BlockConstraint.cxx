#include <BlockConstraint.hxx>

#include <demandDrivenData.hxx>
#include <BlockLduMatrix.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from components
	template<class Type>
	BlockConstraint<Type>::BlockConstraint
	(
		const label row,
		const Type value,
		const Type& fixedCmpts
	)
		:
		rowID_(row),
		value_(value),
		fixedComponents_(fixedCmpts),
		matrixCoeffsSet_(false),
		diagCoeff_(),
		upperCoeffsOwnerPtr_(NULL),
		upperCoeffsNeighbourPtr_(NULL),
		lowerCoeffsOwnerPtr_(NULL),
		lowerCoeffsNeighbourPtr_(NULL)
	{}


	// Construct as copy
	template<class Type>
	BlockConstraint<Type>::BlockConstraint(const BlockConstraint& e)
		:
		rowID_(e.rowID_),
		value_(e.value_),
		fixedComponents_(e.fixedComponents_),
		matrixCoeffsSet_(false),
		upperCoeffsOwnerPtr_(NULL),
		upperCoeffsNeighbourPtr_(NULL),
		lowerCoeffsOwnerPtr_(NULL),
		lowerCoeffsNeighbourPtr_(NULL)
	{}


	// Construct from Istream
	template<class Type>
	BlockConstraint<Type>::BlockConstraint(Istream& is)
		:
		rowID_(readLabel(is)),
		value_(pTraits<Type>(is)),
		fixedComponents_(pTraits<Type>(is)),
		matrixCoeffsSet_(false),
		upperCoeffsOwnerPtr_(NULL),
		upperCoeffsNeighbourPtr_(NULL),
		lowerCoeffsOwnerPtr_(NULL),
		lowerCoeffsNeighbourPtr_(NULL)
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	template<class Type>
	BlockConstraint<Type>::~BlockConstraint()
	{
		deleteDemandDrivenData(upperCoeffsOwnerPtr_);
		deleteDemandDrivenData(upperCoeffsNeighbourPtr_);

		deleteDemandDrivenData(lowerCoeffsOwnerPtr_);
		deleteDemandDrivenData(lowerCoeffsNeighbourPtr_);
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	const BlockCoeff<Type>& BlockConstraint<Type>::diagCoeff() const
	{
		if (matrixCoeffsSet_)
		{
			FatalErrorIn
			(
				"const BlockCoeff<Type>& BlockConstraint<Type>::diagCoeff() const"
			) << "matrix coefficients not set"
				<< abort(FatalError);
		}

		return diagCoeff_;
	}


	template<class Type>
	const Type& BlockConstraint<Type>::b() const
	{
		if (matrixCoeffsSet_)
		{
			FatalErrorIn
			(
				"Type BlockConstraint<Type>::b() const"
			) << "matrix coefficients not set"
				<< abort(FatalError);
		}

		return b_;
	}


	template<class Type>
	const CoeffField<Type>& BlockConstraint<Type>::upperCoeffsOwner() const
	{
		if (!upperCoeffsOwnerPtr_ || !matrixCoeffsSet_)
		{
			FatalErrorIn
			(
				"const CoeffField<Type>& BlockConstraint<Type>::"
				"upperCoeffsOwner() const"
			) << "upper matrix coefficients not set"
				<< abort(FatalError);
		}

		return *upperCoeffsOwnerPtr_;
	}


	template<class Type>
	const CoeffField<Type>& BlockConstraint<Type>::upperCoeffsNeighbour() const
	{
		if (!upperCoeffsNeighbourPtr_ || !matrixCoeffsSet_)
		{
			FatalErrorIn
			(
				"const CoeffField<Type>& BlockConstraint<Type>::"
				"upperCoeffsNeighbour() const"
			) << "upper matrix coefficients not set"
				<< abort(FatalError);
		}

		return *upperCoeffsNeighbourPtr_;
	}


	template<class Type>
	const CoeffField<Type>& BlockConstraint<Type>::lowerCoeffsOwner() const
	{
		if (!lowerCoeffsOwnerPtr_ || !matrixCoeffsSet_)
		{
			FatalErrorIn
			(
				"const CoeffField<Type>& BlockConstraint<Type>::"
				"lowerCoeffsOwner() const"
			) << "lower matrix coefficients not set"
				<< abort(FatalError);
		}

		return *lowerCoeffsOwnerPtr_;
	}


	template<class Type>
	const CoeffField<Type>& BlockConstraint<Type>::lowerCoeffsNeighbour() const
	{
		if (!lowerCoeffsNeighbourPtr_ || !matrixCoeffsSet_)
		{
			FatalErrorIn
			(
				"const CoeffField<Type>& BlockConstraint<Type>::"
				"lowerCoeffsNeighbour() const"
			) << "lower matrix coefficients not set"
				<< abort(FatalError);
		}

		return *lowerCoeffsNeighbourPtr_;
	}


	template<class Type>
	void BlockConstraint<Type>::combine
	(
		const BlockConstraint<Type>& e
	)
	{
		for
			(
				direction cmptI = 0;
				cmptI < pTraits<Type>::nComponents;
				cmptI++
				)
		{
			if
				(
					e.fixedComponents_.component(cmptI)
				> fixedComponents_.component(cmptI)
					)
			{
				fixedComponents_.component(cmptI) =
					e.fixedComponents_.component(cmptI);

				value_.replace(cmptI, e.value_.component(cmptI));
			}
		}
	}


	template<class Type>
	void BlockConstraint<Type>::clearMatrix()
	{
		matrixCoeffsSet_ = false;

		diagCoeff_.clear();

		b_ = pTraits<Type>::zero;

		deleteDemandDrivenData(upperCoeffsOwnerPtr_);
		deleteDemandDrivenData(upperCoeffsNeighbourPtr_);

		deleteDemandDrivenData(lowerCoeffsOwnerPtr_);
		deleteDemandDrivenData(lowerCoeffsNeighbourPtr_);
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	template<class Type>
	void BlockConstraint<Type>::operator=
		(
			const BlockConstraint<Type>& rhs
			)
	{
		// Check for assignment to self
		if (this == &rhs)
		{
			FatalErrorIn
			(
				"BlockConstraint::operator=(const BlockConstraint&)"
			) << "attempted assignment to self"
				<< abort(FatalError);
		}

		rowID_ = rhs.rowID_;

		value_ = rhs.value_;

		fixedComponents_ = rhs.fixedComponents_;

		clearMatrix();
	}


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	template<class Type>
	Ostream& operator<<(Ostream& os, const BlockConstraint<Type>& e)
	{
		os << e.rowID_ << nl
			<< e.value_ << nl
			<< e.fixedComponents_ << nl;

		os.check("Ostream& operator<<(Ostream&, BlockConstraint<Type>&");

		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //