#pragma once
template<class EdgeType>
inline Standard_Boolean 
tnbLib::Geo_TopoChainAnalysis_Entity<EdgeType>::IsDangle() const
{
	const auto& f = First()->Node0();
	const auto& l = End()->Node1();
	if (f->NbEdges() IS_EQUAL 1) return Standard_True;
	if (l->NbEdges() IS_EQUAL 1) return Standard_True;
	return Standard_False;
}