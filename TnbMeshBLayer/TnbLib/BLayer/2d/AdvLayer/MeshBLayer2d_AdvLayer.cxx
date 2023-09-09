//#include <MeshBLayer2d_AdvLayer.hxx>
//
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//void tnbLib::MeshBLayer2d_AdvLayer::ExecuteOneLevel()
//{
//	while (Fronts().Size())
//	{
//		auto node = FrontsRef().Pop();
//		Debug_Null_Pointer(node);
//
//		auto [pt, cond] = IsMovable(node);
//		ConditionRef() = cond;
//
//
//	}
//}
//
//void tnbLib::MeshBLayer2d_AdvLayer::SetSizeFun(const std::shared_ptr<Geo2d_SizeFun>& theFun)
//{
//	theSizeFun_ = theFun;
//}