#include <VoyageWP_Ref.hxx>

#include <Voyage_Tools.hxx>
#include <VoyageMesh_Element.hxx>
#include <VoyageMesh_Edge.hxx>
#include <VoyageMesh_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::VoyageWP_Ref::CalcReference
(
	const ElmList& theStarboard, 
	const ElmList& thePort
)
{
	auto starboard_ref_edges = Voyage_Tools::RetrieveRefEdges(theStarboard);
	auto port_ref_edges = Voyage_Tools::RetrieveRefEdges(thePort);


}