#include <SectPx_NodeMaker.hxx>

#include <SectPx_Registry.hxx>
#include <SectPx_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_Node>
tnbLib::maker::Node::SelectNode
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());
	const auto& registry = *Registry();

	auto item = registry.SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto node = std::dynamic_pointer_cast<SectPx_Node>(item);
	if (NOT node)
	{
		FatalErrorIn(FunctionSIG)
			<< " the selected item is not a node!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
	return std::move(node);
}

Standard_Integer 
tnbLib::maker::Node::CreateNode
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	auto node = std::make_shared<SectPx_Node>(thePnt);
	Debug_Null_Pointer(node);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(node));
}

std::shared_ptr<tnbLib::SectPx_Node> 
tnbLib::maker::Node::RemoveNode
(
	const Standard_Integer theIndex
)
{
	auto node = SelectNode(theIndex);
	Debug_Null_Pointer(node);

	if (NOT std::dynamic_pointer_cast<SectPx_Node>(node))
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter is not removable!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Registry());
	Registry()->Remove(node);
	return std::move(node);
}