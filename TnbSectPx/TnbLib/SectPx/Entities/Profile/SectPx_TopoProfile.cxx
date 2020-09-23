//#include <SectPx_TopoProfile.hxx>
//
//#include <SectPx_Node.hxx>
//#include <SectPx_InterfaceMaker.hxx>
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//const char* tnbLib::SectPx_TopoProfile::typeName_("profile");
//
//tnbLib::SectPx_TopoProfile::SectPx_TopoProfile
//(
//	const std::shared_ptr<SectPx_Node>& theNode0, 
//	const std::shared_ptr<SectPx_Node>& theNode1
//)
//	: theNode0_(theNode0)
//	, theNode1_(theNode1)
//	, SectPx_RegObj(0, "topoProfile")
//{
//	//- empty body
//}
//
//tnbLib::SectPx_TopoProfile::SectPx_TopoProfile
//(
//	const Standard_Integer theIndex, 
//	const std::shared_ptr<SectPx_Node>& theNode0,
//	const std::shared_ptr<SectPx_Node>& theNode1
//)
//	: theNode0_(theNode0)
//	, theNode1_(theNode1)
//	, SectPx_RegObj(theIndex, "topoProfile")
//{
//	//- empty body
//}
//
//tnbLib::SectPx_TopoProfile::SectPx_TopoProfile
//(
//	const Standard_Integer theIndex,
//	const word & theName, 
//	const std::shared_ptr<SectPx_Node>& theNode0,
//	const std::shared_ptr<SectPx_Node>& theNode1
//)
//	: theNode0_(theNode0)
//	, theNode1_(theNode1)
//	, SectPx_RegObj(theIndex, theName)
//{
//	//- empty body
//}
//
//tnbLib::word 
//tnbLib::SectPx_TopoProfile::RegObjTypeName() const
//{
//	return typeName_;
//}
//
//tnbLib::sectPxLib::regObjType 
//tnbLib::SectPx_TopoProfile::RegObjType() const
//{
//	return sectPxLib::regObjType::profile;
//}
//
//Standard_Boolean 
//tnbLib::SectPx_TopoProfile::IsProfile() const
//{
//	return Standard_True;
//}
//
//std::shared_ptr<tnbLib::SectPx_TopoProfile> 
//tnbLib::SectPx_TopoProfile::MakeProfile
//(
//	const std::shared_ptr<SectPx_Node>& theNode0,
//	const std::shared_ptr<SectPx_Node>& theNode1,
//	const std::shared_ptr<SectPx_Registry>& theReg
//)
//{
//	auto profile = std::make_shared<SectPx_TopoProfile>(theNode0, theNode1);
//	Debug_Null_Pointer(profile);
//
//	theNode0->SetProfile(std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));
//	theNode1->SetProfile(std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));
//
//	const auto interfaceMaker = std::make_shared<SectPx_InterfaceMaker>(theReg);
//	Debug_Null_Pointer(interfaceMaker);
//
//	/*const auto intf0_id = */interfaceMaker->CreateEmpty(theNode0);
//	/*const auto intf1_id = */interfaceMaker->CreateEmpty(theNode1);
//
//	/*const auto intf0 = interfaceMaker->SelectInterface(intf0_id);
//	Debug_Null_Pointer(intf0);
//
//	const auto intf1 = interfaceMaker->SelectInterface(intf1_id);
//	Debug_Null_Pointer(intf1);*/
//
//	/*theNode0->SetInterface(intf0);
//	theNode1->SetInterface(intf1);*/
//
//	return std::move(profile);
//}