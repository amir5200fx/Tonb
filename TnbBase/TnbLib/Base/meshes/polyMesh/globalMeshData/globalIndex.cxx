#include <globalIndex.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::globalIndex::globalIndex(const label localSize)
	:
	offsets_(Pstream::nProcs())
{
	labelList localSizes(Pstream::nProcs());
	localSizes[Pstream::myProcNo()] = localSize;
	Pstream::gatherList(localSizes);
	Pstream::scatterList(localSizes);   // just to balance out comms

	label offset = 0;
	forAll(offsets_, procI)
	{
		label oldOffset = offset;
		offset += localSizes[procI];

		if (offset < oldOffset)
		{
			FatalErrorIn("globalIndex::globalIndex(const label)")
				<< "Overflow : sum of sizes " << localSizes
				<< " exceeds capability of label (" << labelMax
				<< "). Please recompile with larger datatype for label."
				<< exit(FatalError);
		}
		offsets_[procI] = offset;
	}
}


tnbLib::globalIndex::globalIndex(Istream& is)
{
	is >> offsets_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, globalIndex& gi)
{
	return is >> gi.offsets_;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const globalIndex& gi)
{
	return os << gi.offsets_;
}


// ************************************************************************* //