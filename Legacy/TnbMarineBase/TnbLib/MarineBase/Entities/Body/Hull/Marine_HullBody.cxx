#include <Marine_HullBody.hxx>

#include <Global_Macros.hxx>

Standard_Boolean 
tnbLib::Marine_HullBody::IsLaunched() const
{
	return IsWetted() OR IsDry();
}