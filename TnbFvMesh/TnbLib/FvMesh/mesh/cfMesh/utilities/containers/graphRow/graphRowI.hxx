#pragma once
#include <error.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class graphType>
	inline void tnbLib::graphRow<graphType>::checkIndex(const label i) const
	{
		if ((i < 0) || (i >= data_.sizeOfRow(rowI_)))
		{
			FatalErrorIn
			(
				"void tnbLib::graphRow<graphType>::"
				"checkIndex(const label i) const"
			) << "Row index " << rowI_
				<< " is not in range " << tnbLib::label(0)
				<< " and " << data_.sizeOfRow(rowI_) << abort(FatalError);
		}
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class graphType>
	inline tnbLib::graphRow<graphType>::graphRow(graphType& g, const label i)
		:
		data_(g),
		rowI_(i)
	{
	}

	template<class graphType>
	inline tnbLib::graphRow<graphType>::graphRow
	(
		const graphRow<graphType>& ol
	)
		:
		data_(ol.data_),
		rowI_(ol.rowI_)
	{
	}

	template<class graphType>
	inline tnbLib::graphRow<graphType>::~graphRow()
	{
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class graphType>
	inline tnbLib::label tnbLib::graphRow<graphType>::size() const
	{
		return data_.sizeOfRow(rowI_);
	}

	template<class graphType>
	inline void tnbLib::graphRow<graphType>::setSize(const label s)
	{
		data_.setRowSize(rowI_, s);
	}

	template<class graphType>
	inline void tnbLib::graphRow<graphType>::clear()
	{
		data_.setRowSize(rowI_, 0);
	}

	template<class graphType>
	inline void tnbLib::graphRow<graphType>::append(const label el)
	{
		data_.append(rowI_, el);
	}

	template<class graphType>
	inline void tnbLib::graphRow<graphType>::appendIfNotIn(const label el)
	{
		data_.appendIfNotIn(rowI_, el);
	}

	template<class graphType>
	inline bool tnbLib::graphRow<graphType>::contains(const label e) const
	{
		return data_.contains(rowI_, e);
	}

	template<class graphType>
	inline tnbLib::label tnbLib::graphRow<graphType>::containsAtPosition
	(
		const label e
	) const
	{
		return data_.containsAtPosition(rowI_, e);
	}

	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	template<class graphType>
	inline tnbLib::label tnbLib::graphRow<graphType>::operator[](const label i) const
	{
		return data_(rowI_, i);
	}

	template<class graphType>
	inline tnbLib::label& tnbLib::graphRow<graphType>::operator[](const label i)
	{
		return data_(rowI_, i);
	}

	template<class graphType>
	inline void tnbLib::graphRow<graphType>::operator=
		(
			const graphRow<graphType>& l
			)
	{
		data_.setRowSize(rowI_, l.size());
		for (label i = 0; i < l.size(); ++i)
			data_(rowI_, i) = l[i];
	}

	template<class graphType>
	template<class listType>
	inline void tnbLib::graphRow<graphType>::operator=(const listType& l)
	{
		data_.setRowSize(rowI_, l.size());
		for (label i = 0; i < l.size(); ++i)
			data_(rowI_, i) = l[i];
	}

	template<class graphType>
	inline tnbLib::Ostream& operator<<
		(
			tnbLib::Ostream& os,
			const tnbLib::graphRow<graphType>& r
			)
	{
		os << r.size() << "(";
		for (tnbLib::label i = 0; i < r.size(); ++i)
			os << r[i] << " ";
		os << ")";

		return os;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //