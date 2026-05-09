#include <Aft_FacetAdaptor.hxx>

#include <Aft3d_Facet.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Mesh_FrontAdaptor<tnbLib::Aft3d_FacetTraits>::Length
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	return theFacet->CharLength();
}