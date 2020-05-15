#include <patchRefinement.hxx>

#include <triSurf.hxx>
#include <Istream.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	patchRefinement::patchRefinement()
		:
		patchName_(),
		cellSize_(0.0)
	{
	}

	patchRefinement::patchRefinement(const word& n, const scalar& s)
		:
		patchName_(n),
		cellSize_(s)
	{
	}

	patchRefinement::patchRefinement(Istream& is)
		:
		patchName_(is),
		cellSize_(readScalar(is))
	{
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	patchRefinement::~patchRefinement()
	{
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	word patchRefinement::patchName() const
	{
		return patchName_;
	}

	label patchRefinement::patchInSurface(const triSurf& ts) const
	{
		forAll(ts.patches(), patchI)
			if (ts.patches()[patchI].name() == patchName_)
				return patchI;

		FatalErrorIn
		(
			"label patchRefinement::patchInSurface(const triSurf& ts) const"
		) << "Patch " << patchName_
			<< " does not exist in surface " << ts.patches()
			<< exit(FatalError);

		return -1;
	}

	scalar patchRefinement::cellSize() const
	{
		return cellSize_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void patchRefinement::operator=(const patchRefinement& pr)
	{
		patchName_ = pr.patchName_;
		cellSize_ = pr.cellSize_;
	}

	Istream& operator>>(Istream& is, patchRefinement& pr)
	{
		pr.patchName_ = word(is);
		pr.cellSize_ = readScalar(is);
		return is;
	}

	Ostream& operator<<(Ostream& os, const patchRefinement& pr)
	{
		os << pr.patchName_ << " " << pr.cellSize_ << nl;
		return os;
	}

	bool operator==(const patchRefinement& p1, const patchRefinement& p2)
	{
		if (p1.patchName() == p2.patchName())
			return true;

		return false;
	}

	bool operator!=(const patchRefinement& p1, const patchRefinement& p2)
	{
		return !(p1 == p2);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //