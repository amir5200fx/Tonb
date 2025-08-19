#include <Marine_Body_Tank.hxx>

#include <Marine_BodyM.cxx>

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::marineLib::Body_Tank::Copy() const
{
	BodyCopy(Body_Tank)
}