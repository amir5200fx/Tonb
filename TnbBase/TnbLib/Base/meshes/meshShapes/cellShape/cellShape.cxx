#include <cellShape.hxx>

#include <degenerateMatcher.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Remove duplicate vertices and reset correct cell model
void tnbLib::cellShape::collapse()
{
	operator=(degenerateMatcher::match(*this));
}


// ************************************************************************* //