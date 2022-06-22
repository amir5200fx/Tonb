#include <TModel_Wire.hxx>

#include <Entity2d_Box.hxx>
#include <TModel_CmpEdge.hxx>
#include <TModel_Edge.hxx>
#include <TModel_ParaCurve.hxx>
#include <TModel_Wire.hxx>
#include <TModel_ParaWire.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::TModel_Wire::NbEdges() const
{
	Debug_Null_Pointer(Edges());
	return (Standard_Integer)Edges()->size();
}

tnbLib::Entity2d_Box 
tnbLib::TModel_Wire::CalcParametricBoundingBox() const
{
	Debug_Null_Pointer(Edges());
	const auto& cmpEdge = *Edges();

	if (NOT cmpEdge.size())
	{
		FatalErrorIn("Entity2d_Box CalcParametricBoundingBox() const")
			<< "the edge list is empty" << endl
			<< abort(FatalError);
	}

	const auto& l = cmpEdge;

	auto iter = l.begin();

	Debug_Null_Pointer((*iter)->ParaCurve());
	auto box = (*iter)->ParaCurve()->CalcBoundingBox();

	iter++;

	while (iter NOT_EQUAL l.end())
	{
		Debug_Null_Pointer((*iter)->ParaCurve());
		box = Entity2d_Box::Union(box, (*iter)->ParaCurve()->CalcBoundingBox());

		iter++;
	}
	return std::move(box);
}

std::shared_ptr<std::vector<std::shared_ptr<tnbLib::TModel_ParaCurve>>>
tnbLib::TModel_Wire::RetrieveParaCurves
(
	const TModel_Wire & theWire
)
{
	auto paraCurves = std::make_shared<std::vector<std::shared_ptr<TModel_ParaCurve>>>();
	Debug_Null_Pointer(paraCurves);
	const auto& edges = theWire.Edges();
	for (const auto& x : *edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->ParaCurve());
		paraCurves->push_back(x->ParaCurve());
	}
	return std::move(paraCurves);
}

std::shared_ptr<tnbLib::TModel_ParaWire> 
tnbLib::TModel_Wire::RetrieveParaWire
(
	const TModel_Wire & theWire
)
{
	auto curves = RetrieveParaCurves(theWire);
	auto wire = std::make_shared<TModel_ParaWire>(std::move(curves));
	return std::move(wire);
}