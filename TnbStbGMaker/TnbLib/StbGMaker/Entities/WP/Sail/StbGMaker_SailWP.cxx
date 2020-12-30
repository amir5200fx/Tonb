#include <StbGMaker_SailWP.hxx>

#include <Marine_SailModeler.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::StbGMaker_SailWP::MakeModeler()
{
	ChangeModeler() = std::make_shared<Marine_SailModeler>();
}

tnbLib::StbGMaker_SailWP::StbGMaker_SailWP()
{
	MakeModeler();
}

tnbLib::StbGMaker_SailWP::StbGMaker_SailWP
(
	const Standard_Real theX
)
	: StbGMaker_WP(theX)
{
	MakeModeler();
}

tnbLib::StbGMaker_SailWP::StbGMaker_SailWP
(
	const Standard_Integer theIndex,
	const Standard_Real theX
)
	: StbGMaker_WP(theIndex, theX)
{
	MakeModeler();
}

tnbLib::StbGMaker_SailWP::StbGMaker_SailWP
(
	const Standard_Integer theIndex,
	const word & theName,
	const Standard_Real theX
)
	: StbGMaker_WP(theIndex, theName, theX)
{
	MakeModeler();
}