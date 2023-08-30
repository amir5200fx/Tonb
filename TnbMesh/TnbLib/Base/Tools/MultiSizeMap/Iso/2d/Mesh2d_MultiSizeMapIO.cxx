#include <Mesh2d_MultiSizeMap.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Mesh2d_MultiSizeMap::ExportToPlt(OFstream& theFile) const
{
	for (const auto& x : this->SizeMaps())
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(theFile);
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Mesh2d_MultiSizeMap);