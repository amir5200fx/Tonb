#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class CurveType, class MetricPrcsr>
	Standard_Boolean Mesh_BndEdgeAdaptor
		<
		CurveType, void,
		void, MetricPrcsr
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