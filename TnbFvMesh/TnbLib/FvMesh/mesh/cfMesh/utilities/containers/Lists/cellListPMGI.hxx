#pragma once
#include <SubList.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Constructors

	inline cellListPMG::cellListPMG()
		:
		cellList(),
		nElmts_(0)
	{
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Destructor

	inline cellListPMG::~cellListPMG()
	{
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline label cellListPMG::size() const
	{
		return nElmts_;
	}

	inline void cellListPMG::setSize(const label nElmts)
	{
		if (nElmts >= cellList::size())
		{
			if (cellList::size() != 0)
			{
				Info << "Resizing cells!" << endl;
				cellList copy(label(1.5*nElmts));
				for (label i = 0; i < nElmts_; ++i)
					copy[i].transfer(this->operator[](i));

				cellList::transfer(copy);
			}
			else
			{
				cellList::setSize(label(1.5*nElmts));
			}
		}

		nElmts_ = nElmts;
	}

	inline void cellListPMG::clear()
	{
		nElmts_ = 0;
	}

	inline void cellListPMG::append(const cell& c)
	{
		const label i = nElmts_;
		setSize(i + 1);
		this->operator[](i) = c;
	}

	inline cell& cellListPMG::newElmt(const label cI)
	{
		setSize(cI + 1);
		return this->operator[](cI);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline void cellListPMG::operator=(const cellList& cls)
	{
		setSize(cls.size());
		forAll(cls, cI)
			this->operator[](cI) = cls[cI];
	}

	inline Ostream& operator<<(Ostream& os, const cellListPMG& cls)
	{
		SubList<cell> c(cls, cls.nElmts_, 0);

		os << c;
		return os;
	}

	inline Istream& operator>>(Istream& is, cellListPMG& cls)
	{
		cellList& cells = static_cast<cellList&>(cls);
		is >> cells;
		cls.nElmts_ = cells.size();

		return is;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //