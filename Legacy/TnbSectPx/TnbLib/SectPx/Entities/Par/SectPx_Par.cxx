#include <SectPx_Par.hxx>

#include <SectPx_FreePar.hxx>
#include <SectPx_BinaryOpFieldFuns.hxx>
#include <SectPx_FieldFun_Uni.hxx>

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Par::RegObjType() const
{
	return sectPxLib::regObjType::parameter;
}

//namespace tnbLib
//{
//
//	std::shared_ptr<SectPx_Par>
//		operator+
//		(
//			const std::shared_ptr<SectPx_Par>& p0, 
//			const std::shared_ptr<SectPx_Par>& p1
//			)
//	{
//		auto f0 = std::make_shared<sectPxLib::FieldFun_Uni>();
//		Debug_Null_Pointer(f0);
//
//		f0->SetIndex(0);
//		f0->SetName("uniform field of " + p0->Name());
//
//		f0->SetPar(p0);
//
//		auto f1 = std::make_shared<sectPxLib::FieldFun_Uni>();
//		Debug_Null_Pointer(f1);
//
//		f1->SetIndex(0);
//		f1->SetName("uniform field of " + p1->Name());
//
//		f1->SetPar(p1);
//
//		auto f = f0 + f1;
//
//		auto par = std::make_shared<SectPx_FreePar>(std::move(f));
//		Debug_Null_Pointer(par);
//		return std::move(par);
//	}
//
//	std::shared_ptr<SectPx_Par>
//		operator-
//		(
//			const std::shared_ptr<SectPx_Par>& p0,
//			const std::shared_ptr<SectPx_Par>& p1
//			)
//	{
//		auto f0 = std::make_shared<sectPxLib::FieldFun_Uni>();
//		Debug_Null_Pointer(f0);
//
//		f0->SetIndex(0);
//		f0->SetName("uniform field of " + p0->Name());
//
//		f0->SetPar(p0);
//
//		auto f1 = std::make_shared<sectPxLib::FieldFun_Uni>();
//		Debug_Null_Pointer(f1);
//
//		f1->SetIndex(0);
//		f1->SetName("uniform field of " + p1->Name());
//
//		f1->SetPar(p1);
//
//		auto f = f0 - f1;
//
//		auto par = std::make_shared<SectPx_FreePar>(std::move(f));
//		Debug_Null_Pointer(par);
//		return std::move(par);
//	}
//
//	std::shared_ptr<SectPx_Par>
//		operator*
//		(
//			const std::shared_ptr<SectPx_Par>& p0,
//			const std::shared_ptr<SectPx_Par>& p1
//			)
//	{
//		auto f0 = std::make_shared<sectPxLib::FieldFun_Uni>();
//		Debug_Null_Pointer(f0);
//
//		f0->SetIndex(0);
//		f0->SetName("uniform field of " + p0->Name());
//
//		f0->SetPar(p0);
//
//		auto f1 = std::make_shared<sectPxLib::FieldFun_Uni>();
//		Debug_Null_Pointer(f1);
//
//		f1->SetIndex(0);
//		f1->SetName("uniform field of " + p1->Name());
//
//		f1->SetPar(p1);
//
//		auto f = f0 * f1;
//
//		auto par = std::make_shared<SectPx_FreePar>(std::move(f));
//		Debug_Null_Pointer(par);
//		return std::move(par);
//	}
//
//	std::shared_ptr<SectPx_Par>
//		operator/
//		(
//			const std::shared_ptr<SectPx_Par>& p0,
//			const std::shared_ptr<SectPx_Par>& p1
//			)
//	{
//		auto f0 = std::make_shared<sectPxLib::FieldFun_Uni>();
//		Debug_Null_Pointer(f0);
//
//		f0->SetIndex(0);
//		f0->SetName("uniform field of " + p0->Name());
//
//		f0->SetPar(p0);
//
//		auto f1 = std::make_shared<sectPxLib::FieldFun_Uni>();
//		Debug_Null_Pointer(f1);
//
//		f1->SetIndex(0);
//		f1->SetName("uniform field of " + p1->Name());
//
//		f1->SetPar(p1);
//
//		auto f = f0 / f1;
//
//		auto par = std::make_shared<SectPx_FreePar>(std::move(f));
//		Debug_Null_Pointer(par);
//		return std::move(par);
//	}
//}