#include <Marine_Region.hxx>

#include <Global_Macros.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::Marine_Region::Marine_Region()
{
}

tnbLib::Marine_Region::Marine_Region
(
	const Standard_Integer theIndex
)
	: Global_Indexed(theIndex)
{
}

tnbLib::Marine_Region::Marine_Region
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
}

Standard_Integer 
tnbLib::Marine_Region::NbBoundaries() const
{
	return (Standard_Integer)theBoundaries_.size();
}

std::vector<std::shared_ptr<tnbLib::Marine_Boundary>> 
tnbLib::Marine_Region::RetrieveBoundaries() const
{
	std::vector<std::shared_ptr<Marine_Boundary>> boundaries;
	RetrieveBoundariesTo(boundaries);

	return std::move(boundaries);
}

void tnbLib::Marine_Region::ImportToBoundaries
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Marine_Boundary>& theBoundary
)
{
	auto insert = theBoundaries_.insert(std::make_pair(theIndex, theBoundary));
	if (NOT insert.second)
	{
		FatalErrorIn("void ImportToBoundaries(Args...)")
			<< "Failed to import the boundary to the region" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Marine_Region::RemoveFromBoundaries
(
	const Standard_Integer theIndex
)
{
	auto iter = theBoundaries_.find(theIndex);
	if (iter IS_EQUAL theBoundaries_.end())
	{
		FatalErrorIn("void RemoveFromBoundaries(const Standard_Integer theIndex)")
			<< "Failed to remove the boundary from the region" << endl
			<< abort(FatalError);
	}
	theBoundaries_.erase(iter);
}

void tnbLib::Marine_Region::RetrieveBoundariesTo
(
	std::vector<std::shared_ptr<Marine_Boundary>>& theBoudaries
) const
{
	theBoudaries.reserve(NbBoundaries());
	for (const auto& x : Boundaries())
	{
		Debug_Null_Pointer(x.second);
		theBoudaries.push_back(x.second);
	}
}