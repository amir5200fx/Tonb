#include <GModel_Wire.hxx>

#include <GModel_Edge.hxx>
#include <GModel_ParaWire.hxx>

tnbLib::GModel_Wire::GModel_Wire
(
	const std::shared_ptr<edgeList>& theEdges
)
	: theEdges_(theEdges)
{
	//- empty body
}

tnbLib::GModel_Wire::GModel_Wire
(
	std::shared_ptr<edgeList>&& theEdges
)
	: theEdges_(std::move(theEdges))
{
	//- empty body
}

tnbLib::GModel_Wire::GModel_Wire
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<edgeList>& theEdges
)
	: GModel_Entity(theIndex, theName)
{
	//- empty body
}

tnbLib::GModel_Wire::GModel_Wire
(
	const Standard_Integer theIndex,
	const word & theName,
	std::shared_ptr<edgeList>&& theEdges
)
	: GModel_Entity(theIndex, theName)
	, theEdges_(theEdges)
{
	//- empty body
}

Standard_Integer 
tnbLib::GModel_Wire::NbEdges() const
{
	return (Standard_Integer)theEdges_->size();
}

std::shared_ptr<std::vector<std::shared_ptr<tnbLib::GModel_ParaCurve>>> 
tnbLib::GModel_Wire::RetrieveParaCurves
(
	const GModel_Wire & theWire
)
{
	std::shared_ptr<std::vector<std::shared_ptr<GModel_ParaCurve>>> paraCurves;
	const auto& edges = theWire.Edges();
	for (const auto& x : *edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Par());
		paraCurves->push_back(x->Par());
	}
	return std::move(paraCurves);
}

std::shared_ptr<tnbLib::GModel_ParaWire> 
tnbLib::GModel_Wire::RetrieveParaWire(const GModel_Wire & theWire)
{
	auto curves = RetrieveParaCurves(theWire);
	auto wire = std::make_shared<GModel_ParaWire>(std::move(curves));
	return std::move(wire);
}