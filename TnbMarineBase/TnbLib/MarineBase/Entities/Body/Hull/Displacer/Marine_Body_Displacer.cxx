#include <Marine_Body_Displacer.hxx>

#include <Marine_BodyM.cxx>

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::marineLib::Body_Displacer::Copy() const
{
	BodyCopy(Body_Displacer)
}