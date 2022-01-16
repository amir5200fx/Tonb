#include <Global_EntityTable.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

std::pair<Standard_Real, Standard_Real> 
tnbLib::Global_EntityTable::SpanValues
(
	const Standard_Integer theSpan
) const
{
	try
	{
		auto x0 = theValues_.at(theSpan);
		auto x1 = theValues_.at(theSpan + 1);

		auto t = std::make_pair(x0, x1);
		return std::move(t);
	}
	catch (const std::exception& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.what() << endl
			<< abort(FatalError);
		auto t = std::make_pair(0.0, 0.0);
		return std::move(t);
	}
}

std::vector<Standard_Real> 
tnbLib::Global_EntityTable::Entities
(
	const std::vector<Standard_Integer>& theIndices
) const
{
	std::vector<Standard_Real> ents;
	ents.reserve(theIndices.size());

	for (auto id : theIndices)
	{
		ents.push_back(theValues_[id]);
	}
	return std::move(ents);
}