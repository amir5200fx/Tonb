#include <lduAddressing.hxx>

#include <extendedLduAddressing.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::lduAddressing::calcLosort() const
{
	if (losortPtr_)
	{
		FatalErrorIn("lduAddressing::calcLosort() const")
			<< "losort already calculated"
			<< abort(FatalError);
	}

	// Scan the neighbour list to find out how many times the cell
	// appears as a neighbour of the face. Done this way to avoid guessing
	// and resizing list
	labelList nNbrOfFace(size(), 0);

	const unallocLabelList& nbr = upperAddr();

	forAll(nbr, nbrI)
	{
		nNbrOfFace[nbr[nbrI]]++;
	}

	// Create temporary neighbour addressing
	labelListList cellNbrFaces(size());

	forAll(cellNbrFaces, cellI)
	{
		cellNbrFaces[cellI].setSize(nNbrOfFace[cellI]);
	}

	// Reset the list of number of neighbours to zero
	nNbrOfFace = 0;

	// Scatter the neighbour faces
	forAll(nbr, nbrI)
	{
		cellNbrFaces[nbr[nbrI]][nNbrOfFace[nbr[nbrI]]] = nbrI;

		nNbrOfFace[nbr[nbrI]]++;
	}

	// Gather the neighbours into the losort array
	losortPtr_ = new labelList(nbr.size(), -1);

	labelList& lst = *losortPtr_;

	// Set counter for losort
	label lstI = 0;

	forAll(cellNbrFaces, cellI)
	{
		const labelList& curNbr = cellNbrFaces[cellI];

		forAll(curNbr, curNbrI)
		{
			lst[lstI] = curNbr[curNbrI];
			lstI++;
		}
	}
}


void tnbLib::lduAddressing::calcOwnerStart() const
{
	if (ownerStartPtr_)
	{
		FatalErrorIn("lduAddressing::calcOwnerStart() const")
			<< "owner start already calculated"
			<< abort(FatalError);
	}

	const labelList& own = lowerAddr();

	ownerStartPtr_ = new labelList(size() + 1, own.size());

	labelList& ownStart = *ownerStartPtr_;

	// Set up first lookup by hand
	ownStart[0] = 0;
	label nOwnStart = 0;
	label i = 1;

	forAll(own, faceI)
	{
		label curOwn = own[faceI];

		if (curOwn > nOwnStart)
		{
			while (i <= curOwn)
			{
				ownStart[i++] = faceI;
			}

			nOwnStart = curOwn;
		}
	}
}


void tnbLib::lduAddressing::calcLosortStart() const
{
	if (losortStartPtr_)
	{
		FatalErrorIn("lduAddressing::calcLosortStart() const")
			<< "losort start already calculated"
			<< abort(FatalError);
	}

	losortStartPtr_ = new labelList(size() + 1, 0);

	labelList& lsrtStart = *losortStartPtr_;

	const labelList& nbr = upperAddr();

	const labelList& lsrt = losortAddr();

	// Set up first lookup by hand
	lsrtStart[0] = 0;
	label nLsrtStart = 0;
	label i = 0;

	forAll(lsrt, faceI)
	{
		// Get neighbour
		const label curNbr = nbr[lsrt[faceI]];

		if (curNbr > nLsrtStart)
		{
			while (i <= curNbr)
			{
				lsrtStart[i++] = faceI;
			}

			nLsrtStart = curNbr;
		}
	}

	// Set up last lookup by hand
	lsrtStart[size()] = nbr.size();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::lduAddressing::lduAddressing(const label nEqns)
	:
	size_(nEqns),
	losortPtr_(NULL),
	ownerStartPtr_(NULL),
	losortStartPtr_(NULL),
	extendedAddr_(5)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::lduAddressing::~lduAddressing()
{
	deleteDemandDrivenData(losortPtr_);
	deleteDemandDrivenData(ownerStartPtr_);
	deleteDemandDrivenData(losortStartPtr_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::unallocLabelList& tnbLib::lduAddressing::losortAddr() const
{
	if (!losortPtr_)
	{
		calcLosort();
	}

	return *losortPtr_;
}


const tnbLib::unallocLabelList& tnbLib::lduAddressing::ownerStartAddr() const
{
	if (!ownerStartPtr_)
	{
		calcOwnerStart();
	}

	return *ownerStartPtr_;
}


const tnbLib::unallocLabelList& tnbLib::lduAddressing::losortStartAddr() const
{
	if (!losortStartPtr_)
	{
		calcLosortStart();
	}

	return *losortStartPtr_;
}


// Return edge index given owner and neighbour label
tnbLib::label tnbLib::lduAddressing::triIndex(const label a, const label b) const
{
	label own = min(a, b);

	label nbr = max(a, b);

	label startLabel = ownerStartAddr()[own];

	label endLabel = ownerStartAddr()[own + 1];

	const unallocLabelList& neighbour = upperAddr();

	for (label i = startLabel; i < endLabel; i++)
	{
		if (neighbour[i] == nbr)
		{
			return i;
		}
	}

	// If neighbour has not been found, something has gone seriously
	// wrong with the addressing mechanism
	FatalErrorIn
	(
		"lduAddressing::triIndex(const label owner, const label nbr) const"
	) << "neighbour " << nbr << " not found for owner " << own << ". "
		<< "Problem with addressing"
		<< abort(FatalError);

	return -1;
}


const tnbLib::extendedLduAddressing&
tnbLib::lduAddressing::extendedAddr(const label p) const
{
	if (p == 0 || p > 4)
	{
		FatalErrorIn
		(
			"const tnbLib::extendedLduAddressing& "
			"tnbLib::lduAddressing::extendedAddr(const label p) const"
		) << "Currently supported extended addressing fill-in only "
			<< "between order 1 and 4"
			<< abort(FatalError);
	}

	if (!extendedAddr_.set(p))
	{
		extendedAddr_.set(p, new extendedLduAddressing(*this, p));
	}

	return extendedAddr_[p];
}


// ************************************************************************* //