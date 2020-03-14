#pragma once
namespace tnbLib
{

	template<class graphType>
	inline void tnbLib::subGraph<graphType>::checkIndex(const label i) const
	{
		if ((i < 0) || (i >= size_))
		{
			FatalErrorIn
			(
				"void tnbLib::subGraph<graphType>::"
				"checkIndex(const label i) const"
			) << "Row index " << i
				<< " is not in range " << tnbLib::label(0)
				<< " and " << size_ << abort(FatalError);
		}
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class graphType>
	inline tnbLib::subGraph<graphType>::subGraph
	(
		graphType& g,
		const label start,
		const label size
	)
		:
		data_(g),
		start_(start),
		size_(size)
	{
	}

	template<class graphType>
	inline tnbLib::subGraph<graphType>::subGraph
	(
		const subGraph<graphType>& ol
	)
		:
		data_(ol.data_),
		start_(ol.start_),
		size_(ol.size_)
	{
	}

	template<class graphType>
	inline tnbLib::subGraph<graphType>::~subGraph()
	{
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class graphType>
	inline tnbLib::label tnbLib::subGraph<graphType>::size() const
	{
		return size_;
	}

	template<class graphType>
	inline tnbLib::label tnbLib::subGraph<graphType>::sizeOfRow(const label rowI) const
	{
		return data_.sizeOfRow(start_ + rowI);
	}

	template<class graphType>
	inline void tnbLib::subGraph<graphType>::append(const label rowI, const label el)
	{
		data_.append(start_ + rowI, el);
	}

	template<class graphType>
	inline void tnbLib::subGraph<graphType>::appendIfNotIn
	(
		const label rowI,
		const label el
	)
	{
		data_.appendIfNotIn(start_ + rowI, el);
	}

	template<class graphType>
	inline bool tnbLib::subGraph<graphType>::contains
	(
		const label rowI,
		const label e
	) const
	{
		return data_.contains(start_ + rowI, e);
	}

	template<class graphType>
	inline tnbLib::label tnbLib::subGraph<graphType>::containsAtPosition
	(
		const label rowI,
		const label e
	) const
	{
		return data_.containsAtPosition(start_ + rowI, e);
	}

	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	template<class graphType>
	inline tnbLib::label tnbLib::subGraph<graphType>::operator()
		(
			const label i,
			const label j
			) const
	{
# ifdef FULLDEBUG
		checkIndex(i);
# endif

		return data_(start_ + i, j);
	}

	template<class graphType>
	inline tnbLib::label& tnbLib::subGraph<graphType>::operator()
		(
			const label i,
			const label j
			)
	{
		return data_(start_ + i, j);
	}


	template<class graphType>
	inline const tnbLib::graphRow<const graphType>
		tnbLib::subGraph<graphType>::operator[]
		(
			const label i
			) const
	{
		return data_[start_ + i];
	}

	template<class graphType>
	inline tnbLib::graphRow<graphType>
		tnbLib::subGraph<graphType>::operator[](const label i)
	{
		return data_[start_ + i];
	}

	template<class graphType>
	inline tnbLib::Ostream& operator<<
		(
			tnbLib::Ostream& os,
			const tnbLib::subGraph<graphType>& sg
			)
	{
		os << sg.size() << "\n" << "(";
		for (tnbLib::label i = 0; i < sg.size(); ++i)
		{
			os << "\n" << sg.sizeOfRow(i) << "(";
			for (tnbLib::label j = 0; j < sg.sizeOfRow(i); ++j)
			{
				if (j > 0) os << " ";

				os << sg(i, j);
			}

			os << ")";
		}

		os << "\n" << ")";

		return os;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //