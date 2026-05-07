#include <StbGMaker_TankWP.hxx>

#include <Marine_TankModeler.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::StbGMaker_TankWP::MakeModeler()
{
	ChangeModeler() = std::make_shared<Marine_TankModeler>();
}

tnbLib::StbGMaker_TankWP::StbGMaker_TankWP()
{
	MakeModeler();
}

tnbLib::StbGMaker_TankWP::StbGMaker_TankWP
(
	const Standard_Real theX
)
	: StbGMaker_WP(theX)
{
	MakeModeler();
}

tnbLib::StbGMaker_TankWP::StbGMaker_TankWP
(
	const Standard_Integer theIndex,
	const Standard_Real theX
)
	: StbGMaker_WP(theIndex, theX)
{
	MakeModeler();
}

tnbLib::StbGMaker_TankWP::StbGMaker_TankWP
(
	const Standard_Integer theIndex,
	const word & theName,
	const Standard_Real theX
)
	: StbGMaker_WP(theIndex, theName, theX)
{
	MakeModeler();
}