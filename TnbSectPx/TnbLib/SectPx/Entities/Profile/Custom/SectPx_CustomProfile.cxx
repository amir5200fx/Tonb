#include <SectPx_CustomProfile.hxx>

#include <SectPx_Node.hxx>
#include <SectPx_InterfaceMaker.hxx>
#include <SectPx_UniKnots.hxx>
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
	const std::shared_ptr<SectPx_Node>& theNode0, 
	const std::shared_ptr<SectPx_Node>& theNode1,
	const std::shared_ptr<SectPx_Registry>& theReg
)
{
	auto profile = std::make_shared<SectPx_CustomProfile>(theNode0, theNode1);
	Debug_Null_Pointer(profile);

	SetProfile(theNode0, std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));
	SetProfile(theNode1, std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));

	const auto interfaceMaker = std::make_shared<maker::Interface>(theReg);
	Debug_Null_Pointer(interfaceMaker);

	/*const auto intf0_id = */interfaceMaker->CreateEmpty(theNode0);
	/*const auto intf1_id = */interfaceMaker->CreateEmpty(theNode1);

	/*const auto intf0 = interfaceMaker->SelectInterface(intf0_id);
	Debug_Null_Pointer(intf0);

	const auto intf1 = interfaceMaker->SelectInterface(intf1_id);
	Debug_Null_Pointer(intf1);*/

	/*theNode0->SetInterface(intf0);
	theNode1->SetInterface(intf1);*/

	auto knotAlg = std::make_shared<SectPx_UniKnots>();
	Debug_Null_Pointer(knotAlg);

	profile->SetKnot(std::move(knotAlg));

	return std::move(profile);
}