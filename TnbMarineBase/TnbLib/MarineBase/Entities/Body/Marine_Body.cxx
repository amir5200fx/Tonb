#include <Marine_Body.hxx>

Standard_Integer 
tnbLib::Marine_Body::NbSections() const
{
	return (Standard_Integer)theSections_.size();
}
