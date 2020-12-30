#include <StbGMaker_HullWP.hxx>

#include <Marine_DisplacerModeler.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::StbGMaker_HullWP::MakeModeler()
{
	ChangeModeler() = std::make_shared<Marine_DisplacerModeler>();
}

tnbLib::StbGMaker_HullWP::StbGMaker_HullWP()
{
	MakeModeler();
}

tnbLib::StbGMaker_HullWP::StbGMaker_HullWP
(
	const Standard_Real theX
)
	: StbGMaker_WP(theX)
{
	MakeModeler();
}

tnbLib::StbGMaker_HullWP::StbGMaker_HullWP
(
	const Standard_Integer theIndex,
	const Standard_Real theX
)
	: StbGMaker_WP(theIndex, theX)
{
	MakeModeler();
}

tnbLib::StbGMaker_HullWP::StbGMaker_HullWP
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Standard_Real theX
)
	: StbGMaker_WP(theIndex, theName, theX)
{
	MakeModeler();
}

