//#include <Marine_WLVolume.hxx>
//
//#include <Geo_xDistb.hxx>
//#include <Marine_Body.hxx>
//#include <Marine_WaterDomain.hxx>
//#include <Marine_WaterLib.hxx>
//#include <Marine_Graph.hxx>
//#include <Marine_GraphCurve.hxx>
//#include <MarineBase_Tools.hxx>
//#include <Marine_System.hxx>
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//tnbLib::Marine_WLVolume::Marine_WLVolume()
//{
//}
//
//tnbLib::Marine_WLVolume::Marine_WLVolume
//(
//	const std::shared_ptr<Geo_xDistb>& theDistrb,
//	const std::shared_ptr<Marine_Domain>& theDomain,
//	const std::shared_ptr<Marine_Body>& theBody
//)
//	: theZ_(theDistrb)
//	, theDomain_(theDomain)
//	, theBody_(theBody)
//{
//}
//
//void tnbLib::Marine_WLVolume::Perform()
//{
//	if (NOT Z())
//	{
//		FatalErrorIn("void tnbLib::Marine_WLVolume::Perform()")
//			<< "no distribution for water is loaded!" << endl
//			<< abort(FatalError);
//	}
//
//	if (NOT Body())
//	{
//		FatalErrorIn("void tnbLib::Marine_WLVolume::Perform()")
//			<< "no body is loaded!" << endl
//			<< abort(FatalError);
//	}
//
//
//	const auto& sections = Body()->Sections();
//
//	std::vector<marineLib::xSectionParam> Q;
//	for (const auto& x : Z()->Values())
//	{
//		auto water = Marine_WaterLib::StillWaterDomain(Domain(), sections, x);
//		Debug_Null_Pointer(water);
//
//		auto wetted = MarineBase_Tools::WettedSections(sections, water->Waters());
//		if (NOT wetted)
//		{
//			continue;
//		}
//
//		Debug_Null_Pointer(wetted);
//
//		auto volQ = MarineBase_Tools::CalcVolume(wetted->Sections(), sysLib::gl_marine_integration_info);
//		auto vol = MarineBase_Tools::CalcArea(volQ, sysLib::gl_marine_integration_info);
//
//		marineLib::xSectionParam v;
//		v.x = x;
//		v.value = vol;
//
//		Q.push_back(std::move(v));
//	}
//	
//	auto c = MarineBase_Tools::Curve(Q);
//	Debug_Null_Pointer(c);
//
//	auto g = MarineBase_Tools::CreateGraph(c);
//	Debug_Null_Pointer(g);
//
//	g->Title().SetName("Volume of the Body");
//	g->X().SetName("Draft");
//	g->Y().SetName("Volume");
//
//	ChangeGraph() = std::move(g);
//	Change_IsDone() = Standard_True;
//}