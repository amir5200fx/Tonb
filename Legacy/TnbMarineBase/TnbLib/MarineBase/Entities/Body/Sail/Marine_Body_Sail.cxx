#include <Marine_Body_Sail.hxx>

#include <Marine_BodyM.cxx>

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::marineLib::Body_Sail::Copy() const
{
	BodyCopy(Body_Sail)
}