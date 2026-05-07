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

template<>
void tnbLib::Mesh2d_MultiSizeMap::ExportToVtk(OFstream& File) const
{
	for (const auto& x: this->SizeMaps())
	{
		Debug_Null_Pointer(x);
		x->ExportToVtk(File);
	}
}

template <>
void tnbLib::Mesh2d_MultiSizeMap::ExportToVtk(std::ostream& os) const
{
	for (const auto& x: this->SizeMaps())
	{
		Debug_Null_Pointer(x);
		x->ExportToVtk(os);
	}
}


BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Mesh2d_MultiSizeMap);