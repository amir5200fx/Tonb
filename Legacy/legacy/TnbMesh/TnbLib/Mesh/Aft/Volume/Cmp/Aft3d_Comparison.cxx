#include <Aft3d_Comparison.hxx>

#include <Aft3d_Element.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer
tnbLib::legLib::Index(const std::shared_ptr<Aft3d_Node>& theNode)
{
	Debug_Null_Pointer(theNode);
	return theNode->Index();
}

Standard_Integer
tnbLib::legLib::Index(const std::shared_ptr<Aft3d_Element>& theElement)
{
	Debug_Null_Pointer(theElement);
	return theElement->Index();
}

Standard_Integer
tnbLib::legLib::Index(const std::shared_ptr<Aft3d_Facet>& theFacet)
{
	Debug_Null_Pointer(theFacet);
	return theFacet->Index();
}

Standard_Integer
tnbLib::legLib::Index(const std::shared_ptr<Aft3d_Edge>& theEdge)
{
	Debug_Null_Pointer(theEdge);
	return theEdge->Index();
}