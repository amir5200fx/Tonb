#include <SectPx_InterfaceMaker.hxx>

#include <SectPx_Registry.hxx>
#include <SectPx_Interfaces.hxx>
#include <SectPx_Node.hxx>
#include <SectPx_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_Interface> 
tnbLib::maker::Interface::SelectInterface
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());
	const auto& registry = *Registry();

	auto item = registry.SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto ptr = std::dynamic_pointer_cast<SectPx_Interface>(item);
	if (NOT ptr)
	{
		FatalErrorIn(FunctionSIG)
			<< "the selected item is not interface!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
	return std::move(ptr);
}

Standard_Integer 
tnbLib::maker::Interface::CreateEmpty
(
	const std::shared_ptr<SectPx_Node>& theNode
) const
{
	auto item = std::make_shared<SectPx_EmptyInterface>(0, "empty interface", theNode);
	Debug_Null_Pointer(item);

	theNode->SetInterface(item);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(item));
}

std::tuple<Standard_Integer, Standard_Integer> 
tnbLib::maker::Interface::CreateJoint
(
	const std::shared_ptr<SectPx_Node>& theNode0, 
	const std::shared_ptr<SectPx_Node>& theNode1
) const
{
	if (NOT SectPx_Tools::IsValidToJoint(theNode0, theNode1))
	{
		FatalErrorIn(FunctionSIG)
			<< "Unable to join the two nodes" << endl
			<< abort(FatalError);
	}

	auto interface0 = std::make_shared<sectPxLib::PairedInterface_Joint>(0, "joint interface", theNode0);
	auto interface1 = std::make_shared<sectPxLib::PairedInterface_Joint>(0, "joint interface", theNode1);

	theNode0->SetInterface(interface0);
	theNode1->SetInterface(interface1);

	Debug_Null_Pointer(Registry());

	const auto id0 = Registry()->Import(interface0);
	const auto id1 = Registry()->Import(interface1);

	interface0->SetPair(interface1);
	interface1->SetPair(interface0);

	auto t = std::make_tuple(id0, id1);
	return std::move(t);
}