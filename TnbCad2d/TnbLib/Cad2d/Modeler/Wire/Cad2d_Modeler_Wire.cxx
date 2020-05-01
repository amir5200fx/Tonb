#include <Cad2d_Modeler_Wire.hxx>

#include <Pln_Wire.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::cad2dLib::Modeler_Wire::Modeler_Wire()
{
}

Standard_Boolean 
tnbLib::cad2dLib::Modeler_Wire::IsContainWire
(
	const Standard_Integer theIndex
) const
{
	auto iter = theWires_.find(theIndex);
	if (iter IS_EQUAL theWires_.end())
	{
		return Standard_False;
	}
	return Standard_True;
}

Standard_Boolean
tnbLib::cad2dLib::Modeler_Wire::IsContain
(
	const std::shared_ptr<Pln_Wire>& theWire
) const
{
	Debug_Null_Pointer(theWire);
	return IsContainWire(theWire->Index());
}

std::shared_ptr<tnbLib::Pln_Wire> 
tnbLib::cad2dLib::Modeler_Wire::RemoveFromWires
(
	const Standard_Integer theIndex
)
{
	auto iter = theWires_.find(theIndex);
	if (iter IS_EQUAL theWires_.end())
	{
		FatalErrorIn("std::shared_ptr<Pln_Wire> RemoveFromWires(const Standard_Integer theIndex)")
			<< "the item is not in the tree: " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theWires_.erase(iter);
	return std::move(item);
}

void tnbLib::cad2dLib::Modeler_Wire::InsertToWires
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Pln_Wire>& theWire
)
{
	auto insert = theWires_.insert(std::make_pair(theIndex, theWire));
	if (NOT insert.second)
	{
		FatalErrorIn("void InsertToWires(const Standard_Integer theIndex, const std::shared_ptr<Pln_Wire>& theWire)")
			<< "duplicate data: " << theIndex << endl
			<< abort(FatalError);
	}
}