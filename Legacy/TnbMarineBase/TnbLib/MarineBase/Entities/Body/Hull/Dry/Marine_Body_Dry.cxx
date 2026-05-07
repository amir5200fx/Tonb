#include <Marine_Body_Dry.hxx>

#include <Marine_BodyM.cxx>

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::marineLib::Body_Dry::Copy() const
{
	BodyCopy(Body_Dry)
}