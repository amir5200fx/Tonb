//#include <MarineBase_Tools.hxx>
//
//#include <TModel_Surface.hxx>
//#include <Cad3d_TModel.hxx>
//#include <Marine_CmpSection.hxx>
//
//#include <BRepAlgoAPI_Section.hxx>
//#include <BRepBuilderAPI_MakeFace.hxx>
//#include <TopTools_ListOfShape.hxx>
//
//namespace tnbLib
//{
//
//	
//
//	
//
//
//}
//
//std::shared_ptr<tnbLib::Marine_CmpSection> 
//tnbLib::MarineBase_Tools::CreateSection
//(
//	const Cad3d_TModel & theModel,
//	const gp_Pln & thePlane,
//	const Standard_Boolean ParallelFalg
//)
//{
//	const auto& surfaces = theModel.RetrieveFaces();
//
//	std::map<Standard_Integer, std::shared_ptr<TModel_Surface>>
//		allSurfaces, meetSurface;
//	for (const auto& x : surfaces)
//	{
//		Debug_Null_Pointer(x);
//
//		auto insert = allSurfaces.insert(std::make_pair(x->Index(), x));
//		if (NOT insert.second)
//		{
//			FatalErrorIn("std::shared_ptr<tnbLib::Marine_CmpSection> MarineBase_Tools::CreateSection()")
//				<< "duplicate data: cannot insert the face into the map: " << x->Index() << endl
//				<< abort(FatalError);
//		}
//	}
//
//	auto builder = BRepBuilderAPI_MakeFace(thePlane);
//	auto plane = builder.Face();
//
//	for (const auto& x : surfaces)
//	{
//		Debug_Null_Pointer(x);
//
//		auto iter = meetSurface.find(x->Index());
//		if (iter IS_EQUAL meetSurface.end())
//		{
//			auto insert = meetSurface.insert(std::make_pair(x->Index(), x));
//			if (NOT insert.second)
//			{
//				FatalErrorIn("std::shared_ptr<tnbLib::Marine_CmpSection> MarineBase_Tools::CreateSection()")
//					<< "duplicate data: cannot insert the face into the map: " << x->Index() << endl
//					<< abort(FatalError);
//			}
//
//			auto intShape =
//				CrossSection(plane, x->Face(), ParallelFalg);
//
//			if (NOT intShape.IsNull())
//			{
//
//			}
//		}
//	}
//
//	
//}