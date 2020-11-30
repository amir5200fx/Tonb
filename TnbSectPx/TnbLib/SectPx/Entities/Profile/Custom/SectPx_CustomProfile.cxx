#include <SectPx_CustomProfile.hxx>

#include <SectPx_FrameRegistry.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_TPnt.hxx>
#include <SectPx_Node.hxx>
#include <SectPx_NodeMaker.hxx>
#include <SectPx_InterfaceMaker.hxx>
#include <SectPx_UniKnots.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::SectPx_CustomProfile::typeName_("custom profile");

tnbLib::SectPx_CustomProfile::SectPx_CustomProfile
(
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: SectPx_TopoProfile(theNode0, theNode1)
{
	// empty body
}

tnbLib::SectPx_CustomProfile::SectPx_CustomProfile
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SectPx_Node>& theNode0, 
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: SectPx_TopoProfile(theIndex, theNode0, theNode1)
{
	// empty body
}

tnbLib::SectPx_CustomProfile::SectPx_CustomProfile
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: SectPx_TopoProfile(theIndex, theName, theNode0, theNode1)
{
	// empty body
}

tnbLib::word 
tnbLib::SectPx_CustomProfile::RegObjTypeName() const
{
	return typeName_;
}

std::shared_ptr<tnbLib::SectPx_CustomProfile> 
tnbLib::SectPx_CustomProfile::MakeProfile
(
	const std::shared_ptr<SectPx_Pnt>& theP0,
	const std::shared_ptr<SectPx_Pnt>& theP1,
	const std::shared_ptr<SectPx_FrameRegistry>& theReg
)
{
	std::vector<std::shared_ptr<SectPx_Pnt>> pnts;
	pnts.reserve(2);
	pnts.push_back(theP0);
	pnts.push_back(theP1);

	auto seg = SectPx_Tools::MakeEdge(theP0, theP1, theReg);

	auto nodeMaker = std::make_shared<maker::Node>(theReg);
	Debug_Null_Pointer(nodeMaker);

	const auto n0_id = nodeMaker->CreateNode(theP0);
	const auto n1_id = nodeMaker->CreateNode(theP1);

	const auto n0 = nodeMaker->SelectNode(n0_id);
	Debug_Null_Pointer(n0);

	const auto n1 = nodeMaker->SelectNode(n1_id);
	Debug_Null_Pointer(n1);

	auto profile = std::make_shared<SectPx_CustomProfile>(n0, n1);
	Debug_Null_Pointer(profile);

	SetProfile(n0, std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));
	SetProfile(n1, std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));

	const auto interfaceMaker = std::make_shared<maker::Interface>(theReg);
	Debug_Null_Pointer(interfaceMaker);

	/*const auto intf0_id = */interfaceMaker->CreateEmpty(n0);
	/*const auto intf1_id = */interfaceMaker->CreateEmpty(n1);

	/*const auto intf0 = interfaceMaker->SelectInterface(intf0_id);
	Debug_Null_Pointer(intf0);

	const auto intf1 = interfaceMaker->SelectInterface(intf1_id);
	Debug_Null_Pointer(intf1);*/

	/*theNode0->SetInterface(intf0);
	theNode1->SetInterface(intf1);*/

	// remove this stupid knotAlg from profile structure
	/*auto knotAlg = std::make_shared<SectPx_UniKnots>();
	Debug_Null_Pointer(knotAlg);

	profile->SetKnot(std::move(knotAlg));*/



	return std::move(profile);
}