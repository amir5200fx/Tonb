#include <SectPx_Join.hxx>

#include <SectPx_Node.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_Interfaces.hxx>
#include <SectPx_InterfaceMaker.hxx>
#include <SectPx_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::SectPx_Join::MakeJoint(const SectPx_JoinPriority priority)
{
	if (NOT LeftProfile())
	{
		FatalErrorIn(FunctionSIG)
			<< "the left profile is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT RightProfile())
	{
		FatalErrorIn(FunctionSIG)
			<< "the right profile is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& left = LeftProfile();
	const auto& right = RightProfile();

	const auto& leftNode = left->Node1();
	const auto& rightNode = right->Node0();

	const auto leftInterface = leftNode->Interface().lock();
	Debug_Null_Pointer(leftInterface);

	const auto rightInterface = rightNode->Interface().lock();
	Debug_Null_Pointer(rightInterface);

	SectPx_Tools::disJiont(leftInterface);
	SectPx_Tools::disJiont(rightInterface);


	//- remove the old interfaces from the registry
	auto maker = std::make_shared<maker::Interface>(Registry());
	maker->RemoveInterface(leftInterface->Index());
	maker->RemoveInterface(rightInterface->Index());

	const auto [leftId, rightId] = SectPx_Tools::MakeJoint(left, right, Registry(), priority);
	const auto ptId = SectPx_Tools::MakePair(leftNode->Pnt(), rightNode->Pnt(), Registry(), priority);

	ChangeNewLeftInterfaceId() = leftId;
	ChangeNewRightInterfaceId() = rightId;
	ChangeNewPntId() = ptId;

	Change_IsDone() = Standard_True;
}