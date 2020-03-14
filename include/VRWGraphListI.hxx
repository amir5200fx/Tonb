#pragma once
namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline void tnbLib::VRWGraphList::checkIndex
	(
		const label i,
		const label j,
		const label k
	) const
	{
		if ((i < 0) || (i >= rows_.size()))
		{
			FatalErrorIn
			(
				"void tnbLib::VRWGraphList<T,width>::"
				"checkIndex(const label i, const label j, const label k) const"
			) << "Position index " << tnbLib::label(i)
				<< " is not in range " << tnbLib::label(0)
				<< " and " << rows_.size() << abort(FatalError);
		}

		if ((j < 0) || (j >= rows_[i].size()))
			FatalErrorIn
			(
				"void tnbLib::VRWGraphList<T,width>::"
				"checkIndex(label const i, const label j, const label k) const"
			) << "Row index " << tnbLib::label(j)
			<< " is not in range " << tnbLib::label(0)
			<< " and " << rows_[i].size() << abort(FatalError);

		if ((k < 0) || (k >= data_.sizeOfRow(rows_[i].start() + j)))
			FatalErrorIn
			(
				"void tnbLib::VRWGraphList<T,width>::"
				"checkIndex(label const i, const label j, const label k) const"
			) << "Data index " << tnbLib::label(k)
			<< " is not in range " << tnbLib::label(0)
			<< " and " << data_.sizeOfRow(rows_[i].start() + j)
			<< abort(FatalError);
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	//- Construct null
	inline tnbLib::VRWGraphList::VRWGraphList()
		:
		data_(),
		rows_()
	{
	}

	inline tnbLib::VRWGraphList::VRWGraphList
	(
		const VRWGraphList& ol
	)
		:
		data_(ol.data_),
		rows_(ol.rows_)
	{
	}

	inline tnbLib::VRWGraphList::~VRWGraphList()
	{
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	inline tnbLib::label tnbLib::VRWGraphList::size() const
	{
		return rows_.size();
	}

	inline tnbLib::label tnbLib::VRWGraphList::sizeOfGraph(const label posI) const
	{
		return rows_[posI].size();
	}

	inline tnbLib::label tnbLib::VRWGraphList::sizeOfRow
	(
		const label posI,
		const label rowI
	) const
	{
		return data_.sizeOfRow(rows_[posI].start() + rowI);
	}

	inline void tnbLib::VRWGraphList::clear()
	{
		data_.setSize(0);
		rows_.setSize(0);
	}

	template<class GraphType>
	inline void tnbLib::VRWGraphList::appendGraph
	(
		const GraphType& l
	)
	{
		rowElement re(data_.size(), l.size());

		for (label i = 0; i < l.size(); ++i)
			data_.appendList(l[i]);

		rows_.append(re);
	}

	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	inline tnbLib::label tnbLib::VRWGraphList::operator()
		(
			const label i,
			const label j,
			const label k
			) const
	{
#ifdef FULLDEBUG
		checkIndex(i, j, k);
#endif

		return data_(rows_[i].start() + j, k);
	}


	inline tnbLib::label& tnbLib::VRWGraphList::operator()
		(
			const label i, const label j, const label k
			)
	{
#ifdef FULLDEBUG
		checkIndex(i, j, k);
#endif

		return data_(rows_[i].start() + j, k);
	}

	inline const tnbLib::subGraph<const VRWGraph> tnbLib::VRWGraphList::operator[]
	(
		const label i
		) const
	{
		return tnbLib::subGraph<const VRWGraph>(data_, i, rows_[i].size());
	}

	inline void tnbLib::VRWGraphList::operator=(const VRWGraphList& l)
	{
		data_ = l.data_;
		rows_ = l.rows_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //