#include <Pln_WireAux.hxx>

void tnbLib::Pln_WireAux::SetBoundingBox
(
	const Entity2d_Box && theB
)
{
	theBoundingBox_ = std::move(theB);
}

void tnbLib::Pln_WireAux::SetOrientation
(
	const Pln_Orientation theOrient
)
{
	theOrientation_ = theOrient;
}