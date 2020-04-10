#include <NModel_Wire.hxx>

#include <Entity2d_Box.hxx>
#include <NModel_CmpEdge.hxx>
#include <NModel_Edge.hxx>
#include <NModel_ParaCurve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::NModel_Wire::NModel_Wire
(
	const std::shared_ptr<NModel_CmpEdge>& theEdge
)
	: theEdge_(theEdge)
{
}

tnbLib::NModel_Wire::NModel_Wire
(
	const Standard_Integer theIndex,
	const std::shared_ptr<NModel_CmpEdge>& theEdge
)
	: NModel_Entity(theIndex)
	, theEdge_(theEdge)
{
}

tnbLib::NModel_Wire::NModel_Wire
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<NModel_CmpEdge>& theEdge
)
	: NModel_Entity(theIndex, theName)
	, theEdge_(theEdge)
{
}

tnbLib::Entity2d_Box
tnbLib::NModel_Wire::CalcParametricBoundingBox() const
{
	Debug_Null_Pointer(CmpEdge());
	const auto& cmpEdge = *CmpEdge();

	if (NOT cmpEdge.NbEdges())
	{
		FatalErrorIn("Entity2d_Box CalcParametricBoundingBox() const")
			<< "the edge list is empty" << endl
			<< abort(FatalError);
	}

	const auto& l = cmpEdge.Edges();

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