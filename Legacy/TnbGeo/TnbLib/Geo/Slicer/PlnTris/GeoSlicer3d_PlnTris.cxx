#include <GeoSlicer3d_PlnTris.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::GeoSlicer3d_PlnTris::IsClipped() const
{
	CheckDone((*this));
	return Standard_Boolean(theClipped_);
}
