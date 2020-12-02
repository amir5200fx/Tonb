//#include <SectPx_FrameAPI.hxx>
//
//#include <SectPx_Pars.hxx>
//#include <SectPx_ParameterMaker.hxx>
//#include <SectPx_Frame.hxx>
//#include <IOstreams.hxx>
//
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//std::shared_ptr<tnbLib::SectPx_Frame>
//tnbLib::SectPx_FrameAPI::CreateFrame()
//{
//	auto f = std::make_shared<SectPx_Frame>();
//	return std::move(f);
//}
//
//std::shared_ptr<tnbLib::SectPx_Par> 
//tnbLib::SectPx_FrameAPI::SelectParameter
//(
//	const Standard_Integer theIndex, 
//	const std::shared_ptr<SectPx_Frame>& theFrame
//)
//{
//	Debug_Null_Pointer(theFrame);
//	const auto& paramMaker = theFrame->ParameterMaker();
//	auto item = paramMaker->SelectParameter(theIndex);
//	return std::move(item);
//}
//
//std::shared_ptr<tnbLib::SectPx_Par> 
//tnbLib::SectPx_FrameAPI::RemoveParameter
//(
//	const Standard_Integer theIndex,
//	const std::shared_ptr<SectPx_Frame>& theFrame
//)
//{
//	Debug_Null_Pointer(theFrame);
//	const auto& paramMaker = theFrame->ParameterMaker();
//	auto item = paramMaker->RemoveParameter(theIndex);
//	return std::move(item);
//}
//
//Standard_Integer 
//tnbLib::SectPx_FrameAPI::CreateFreeParameter
//(
//	const std::shared_ptr<SectPx_FieldFun>& theField,
//	const std::shared_ptr<SectPx_Frame>& theFrame
//)
//{
//	Debug_Null_Pointer(theFrame);
//	const auto& paramMaker = theFrame->ParameterMaker();
//	return paramMaker->CreateFree(theField);
//}
//
//Standard_Integer 
//tnbLib::SectPx_FrameAPI::CreateFixedParameter
//(
//	const Standard_Real x,
//	const std::shared_ptr<SectPx_Frame>& theFrame
//)
//{
//	Debug_Null_Pointer(theFrame);
//	const auto& paramMaker = theFrame->ParameterMaker();
//	return paramMaker->CreateFixed(x);
//}
//
//Standard_Integer 
//tnbLib::SectPx_FrameAPI::CreateConstantParameter
//(
//	const Standard_Real x,
//	const std::shared_ptr<SectPx_Frame>& theFrame
//)
//{
//	Debug_Null_Pointer(theFrame);
//	const auto& paramMaker = theFrame->ParameterMaker();
//	return paramMaker->CreateConstant(x);
//}
//
//std::vector<std::shared_ptr<tnbLib::SectPx_Par>> 
//tnbLib::SectPx_FrameAPI::RetrieveFreeParameters
//(
//	const std::shared_ptr<SectPx_Frame>& theFrame
//)
//{
//	Debug_Null_Pointer(theFrame);
//	const auto& paramMaker = theFrame->ParameterMaker();
//	auto parameters = paramMaker->RetrieveFreeParameters();
//	return std::move(parameters);
//}
//
//std::vector<std::shared_ptr<tnbLib::SectPx_Par>>
//tnbLib::SectPx_FrameAPI::RetrieveFixedParameters
//(
//	const std::shared_ptr<SectPx_Frame>& theFrame
//)
//{
//	Debug_Null_Pointer(theFrame);
//	const auto& paramMaker = theFrame->ParameterMaker();
//	auto parameters = paramMaker->RetrieveFixedParameters();
//	return std::move(parameters);
//}
//
//std::vector<std::shared_ptr<tnbLib::SectPx_Par>>
//tnbLib::SectPx_FrameAPI::RetrieveConstantParameters
//(
//	const std::shared_ptr<SectPx_Frame>& theFrame
//)
//{
//	Debug_Null_Pointer(theFrame);
//	const auto& paramMaker = theFrame->ParameterMaker();
//	auto parameters = paramMaker->RetrieveConstParameters();
//	return std::move(parameters);
//}
//
//std::vector<std::shared_ptr<tnbLib::SectPx_Par>>
//tnbLib::SectPx_FrameAPI::RetrieveParameters
//(
//	const std::shared_ptr<SectPx_Frame>& theFrame
//)
//{
//	Debug_Null_Pointer(theFrame);
//	const auto& paramMaker = theFrame->ParameterMaker();
//	auto parameters = paramMaker->RetrieveParameters();
//	return std::move(parameters);
//}
//
//void tnbLib::SectPx_FrameAPI::Print(const std::shared_ptr<SectPx_Par> & p)
//{
//	Debug_Null_Pointer(p);
//	Info << p->Name() << " [" << p->RegObjTypeName() << "]: " << (*p)() << endl;
//}