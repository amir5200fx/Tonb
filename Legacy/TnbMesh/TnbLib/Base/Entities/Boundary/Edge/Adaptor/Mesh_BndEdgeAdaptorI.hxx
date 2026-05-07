#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class CurveType, class EdgeType, class MetricPrcsr>
	Standard_Boolean Mesh_BndEdgeAdaptor
		<
		CurveType, void,
		void, EdgeType, MetricPrcsr
		>::SingularityContraction
		(
			const MetricPrcsr & /*thePrcsr*/
		)
	{
		FatalErrorIn("void SingularityContraction(const MetricPrcsr &)")
			<< "not supposed to be called!" << endl
			<< abort(FatalError);
		return Standard_True;
	}
}