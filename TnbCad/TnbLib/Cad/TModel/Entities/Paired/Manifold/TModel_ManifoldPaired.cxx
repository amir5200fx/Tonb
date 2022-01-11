#include <TModel_ManifoldPaired.hxx>

#include <TModel_Edges.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::TModel_ManifoldPaired::CheckManifold()
{
	if (NOT Edge0() OR NOT Edge1())
	{
		FatalErrorIn(FunctionSIG)
			<< "the segment is not manifold!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::TModel_ManifoldPaired::SetPairs() const
{
	auto g0 = std::dynamic_pointer_cast<TModel_GeneratedEdge>(theEdge0_);
	Debug_Null_Pointer(g0);

	auto g1 = std::dynamic_pointer_cast<TModel_GeneratedEdge>(theEdge1_);
	Debug_Null_Pointer(g1);

	g0->SetPairedEdge(g1);
	g1->SetPairedEdge(g0);

	auto thisPaired = 
		std::dynamic_pointer_cast<TModel_Paired>
		(
			std::const_pointer_cast<TModel_Entity>(This())
			);
	g0->SetPaired(thisPaired);
	g1->SetPaired(thisPaired);
}

const std::shared_ptr<tnbLib::TModel_Edge>& 
tnbLib::TModel_ManifoldPaired::Other
(
	const std::shared_ptr<TModel_Edge>& theEdge
)
{
	if (theEdge == theEdge0_)
	{
		return theEdge1_;
	}

	if (theEdge == theEdge1_)
	{
		return theEdge0_;
	}

	FatalErrorIn(FunctionSIG)
		<< "the edge doesn't belong to the segment!" << endl
		<< abort(FatalError);

	return theEdge0_;
}