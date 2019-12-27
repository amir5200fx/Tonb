#include <Pstream.hxx>

#include <token.hxx>
#include <boolList.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Pstream::commsStruct::commsStruct()
	:
	above_(-1),
	below_(0),
	allBelow_(0),
	allNotBelow_(0)
{}


tnbLib::Pstream::commsStruct::commsStruct
(
	const label above,
	const labelList& below,
	const labelList& allBelow,
	const labelList& allNotBelow
)
	:
	above_(above),
	below_(below),
	allBelow_(allBelow),
	allNotBelow_(allNotBelow)
{}


tnbLib::Pstream::commsStruct::commsStruct
(
	const label nProcs,
	const label myProcID,
	const label above,
	const labelList& below,
	const labelList& allBelow
)
	:
	above_(above),
	below_(below),
	allBelow_(allBelow),
	allNotBelow_(nProcs - allBelow.size() - 1)
{
	boolList inBelow(nProcs, false);

	forAll(allBelow, belowI)
	{
		inBelow[allBelow[belowI]] = true;
	}

	label notI = 0;
	forAll(inBelow, procI)
	{
		if ((procI != myProcID) && !inBelow[procI])
		{
			allNotBelow_[notI++] = procI;
		}
	}
	if (notI != allNotBelow_.size())
	{
		FatalErrorIn("commsStruct") << "problem!" << tnbLib::abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

bool tnbLib::Pstream::commsStruct::operator==(const commsStruct& comm) const
{
	return
		(
		(above_ == comm.above())
			&& (below_ == comm.below())
			&& (allBelow_ == allBelow())
			&& (allNotBelow_ == allNotBelow())
			);
}


bool tnbLib::Pstream::commsStruct::operator!=(const commsStruct& comm) const
{
	return !operator==(comm);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const Pstream::commsStruct& comm)
{
	os << comm.above_ << token::SPACE
		<< comm.below_ << token::SPACE
		<< comm.allBelow_ << token::SPACE
		<< comm.allNotBelow_;

	os.check
	(
		"Ostream& operator<<(Ostream&, const commsStruct&)"
	);

	return os;
}


// ************************************************************************* //