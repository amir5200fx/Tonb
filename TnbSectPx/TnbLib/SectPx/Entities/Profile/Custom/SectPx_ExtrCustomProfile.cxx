#include <SectPx_ExtrCustomProfile.hxx>

#include <SectPx_FrameRegistry.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_TPnt.hxx>
#include <SectPx_Node.hxx>
#include <SectPx_NodeMaker.hxx>
#include <SectPx_InterfaceMaker.hxx>
#include <SectPx_UniKnots.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_Tools.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_Interface.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::SectPx_ExtrCustomProfile::SectPx_ExtrCustomProfile
(
	const std::shared_ptr<SectPx_Node>& theNode0, 
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: SectPx_CustomProfile(theNode0, theNode1)
{
	//- empty body
}

tnbLib::SectPx_ExtrCustomProfile::SectPx_ExtrCustomProfile
(
	const Standard_Integer theIndex,
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: SectPx_CustomProfile(theIndex, theNode0, theNode1)
{
	//- empty body
}

tnbLib::SectPx_ExtrCustomProfile::SectPx_ExtrCustomProfile
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: SectPx_CustomProfile(theIndex, theName, theNode0, theNode1)
{
	//- empty body
}


std::shared_ptr<tnbLib::SectPx_ExtrCustomProfile>
tnbLib::SectPx_ExtrCustomProfile::MakeProfile
(
	const std::shared_ptr<SectPx_Pnt>& theP0, 
	const std::shared_ptr<SectPx_Pnt>& theP1, 
	const std::shared_ptr<SectPx_FrameRegistry>& theReg
)
{
	auto seg = SectPx_Tools::MakeEdge(theP0, theP1, theReg);

	auto nodeMaker = std::make_shared<maker::Node>(theReg);
	Debug_Null_Pointer(nodeMaker);

	const auto n0_id = nodeMaker->CreateNode(theP0);
	const auto n1_id = nodeMaker->CreateNode(theP1);

	const auto n0 = nodeMaker->SelectNode(n0_id);
	Debug_Null_Pointer(n0);

	const auto n1 = nodeMaker->SelectNode(n1_id);
	Debug_Null_Pointer(n1);

	auto profile = std::make_shared<SectPx_ExtrCustomProfile>(n0, n1);
	Debug_Null_Pointer(profile);

	SetProfile(n0, std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));
	SetProfile(n1, std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));

	const auto interfaceMaker = std::make_shared<maker::Interface>(theReg);
	Debug_Null_Pointer(interfaceMaker);

	if (theP0->IsMaster())
	{
		interfaceMaker->CreateEmpty(n0);
	}
	else  //- the point is slave
	{
		auto slave = std::dynamic_pointer_cast<SectPx_SlavePnt>(theP0);
		Debug_Null_Pointer(slave);

		const auto& master = slave->Master();
		auto bndMaster = std::dynamic_pointer_cast<sectPxLib::OuterPnt<sectPxLib::Pnt_Compnt>>(master);
		Debug_Null_Pointer(bndMaster);

		const auto node = bndMaster->Node().lock();
		Debug_Null_Pointer(node);

		const auto bndInterface = node->Interface().lock();
		Debug_Null_Pointer(bndInterface);

		interfaceMaker->RemoveInterface(bndInterface->Index());

		interfaceMaker->CreateJoint(node, n0);
	}

	if (theP1->IsMaster())
	{
		interfaceMaker->CreateEmpty(n1);
	}
	else   //- the point is slave
	{
		auto slave = std::dynamic_pointer_cast<SectPx_SlavePnt>(theP1);
		Debug_Null_Pointer(slave);

		const auto& master = slave->Master();
		auto bndMaster = std::dynamic_pointer_cast<sectPxLib::OuterPnt<sectPxLib::Pnt_Compnt>>(master);
		Debug_Null_Pointer(bndMaster);

		const auto node = bndMaster->Node().lock();
		Debug_Null_Pointer(node);

		const auto bndInterface = node->Interface().lock();
		Debug_Null_Pointer(bndInterface);

		interfaceMaker->RemoveInterface(bndInterface->Index());

		interfaceMaker->CreateJoint(n1, node);
	}

	return std::move(profile);
}