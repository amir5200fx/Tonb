#include <Marine_Body_Wetted.hxx>

#include <Marine_BodyM.cxx>

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::marineLib::Body_Wetted::Copy() const
{
	BodyCopy(Body_Wetted)
}
