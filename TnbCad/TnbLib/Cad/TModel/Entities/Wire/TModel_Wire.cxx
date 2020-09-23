#include <TModel_Wire.hxx>

#include <Entity2d_Box.hxx>
#include <TModel_CmpEdge.hxx>
#include <TModel_Edge.hxx>
#include <TModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::TModel_Wire::TModel_Wire
(
	const std::shared_ptr<TModel_CmpEdge>& theEdge
)
	: theEdge_(theEdge)
{
}

tnbLib::TModel_Wire::TModel_Wire
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<TModel_CmpEdge>& theEdge
)
	: TModel_Entity(theIndex)
	, theEdge_(theEdge)
{
}

tnbLib::TModel_Wire::TModel_Wire
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<TModel_CmpEdge>& theEdge
)
	: TModel_Entity(theIndex, theName)
	, theEdge_(theEdge)
{
}

tnbLib::Entity2d_Box 
tnbLib::TModel_Wire::CalcParametricBoundingBox() const
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