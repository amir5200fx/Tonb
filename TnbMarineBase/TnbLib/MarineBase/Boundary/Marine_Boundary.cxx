#include <Marine_Boundary.hxx>

#include <Global_Macros.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::Marine_Boundary::Marine_Boundary()
{
}

tnbLib::Marine_Boundary::Marine_Boundary
(
	const Standard_Integer theIndex
)
	: Global_Indexed(theIndex)
{
}

tnbLib::Marine_Boundary::Marine_Boundary
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
}

Standard_Integer
tnbLib::Marine_Boundary::NbBlocks() const
{
	return (Standard_Integer)theSurfaces_.size();
}

std::vector<std::shared_ptr<typename tnbLib::Marine_Boundary::surfBlock>>
tnbLib::Marine_Boundary::RetrieveBlocks() const
{
	std::vector<std::shared_ptr<surfBlock>> blocks;
	RetrieveBlocksTo(blocks);

	return std::move(blocks);
}

void tnbLib::Marine_Boundary::ImportBlock
(
	const Standard_Integer theIndex,
	const std::shared_ptr<surfBlock>& theBlock
)
{
	auto insert = theSurfaces_.insert(std::make_pair(theIndex, theBlock));
	if (NOT insert.second)
	{
		FatalErrorIn("void ImportBlock(const Standard_Integer theIndex, const std::shared_ptr<surfBlock>& theBlock)")
			<< "Failed to import the item into the boundary" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Marine_Boundary::RemoveBlock
(
	const Standard_Integer theIndex
)
{
	auto iter = theSurfaces_.find(theIndex);
	if (iter IS_EQUAL theSurfaces_.end())
	{
		FatalErrorIn("void RemoveBlock(const Standard_Integer theIndex)")
			<< "Failed to remove the block from the surfaces" << endl
			<< abort(FatalError);
	}
	theSurfaces_.erase(iter);
}

void tnbLib::Marine_Boundary::RetrieveBlocksTo
(
	std::vector<std::shared_ptr<surfBlock>>& theBlocks
) const
{
	theBlocks.reserve(NbBlocks());
	for (const auto& x : SurfaceBlocks())
	{
		Debug_Null_Pointer(x.second);
		theBlocks.push_back(x.second);
	}
}