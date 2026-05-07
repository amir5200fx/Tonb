#include <VoyageMesh_RefEdge.hxx>

#include <VoyageMesh_Element.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::VoyageMesh_Node>
tnbLib::VoyageMesh_RefEdge::RetrieveTip() const
{
	const auto element = LeftElement().lock();
	if(NOT element)
	{
		FatalErrorIn(FunctionSIG)
			<< "no element has been found." << endl
			<< abort(FatalError);
	}
	return element->Node2();
}
