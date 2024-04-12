#include <Mesh2d_SizeMapVolume.hxx>

void tnbLib::Mesh2d_SizeMapVolume::Perform()
{
	Change_IsDone() = Standard_True;
}

Standard_Boolean tnbLib::Mesh2d_SizeMapVolume::IsShape() const
{
	return Standard_False;
}

Standard_Boolean tnbLib::Mesh2d_SizeMapVolume::IsPolygon() const
{
	return Standard_False;
}


