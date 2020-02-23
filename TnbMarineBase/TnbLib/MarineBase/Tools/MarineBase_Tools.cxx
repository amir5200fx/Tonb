#include <MarineBase_Tools.hxx>

#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <Cad2d_CmptLib.hxx>
#include <Marine_Section.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_CrossSection.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <UnitSystem.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Trsf2d.hxx>
#include <gp_Ax22d.hxx>
#include <gp_Ax2d.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <StdFail_NotDone.hxx>

Handle(Geom2d_Curve)
tnbLib::MarineBase_Tools::Curve
(
	const std::vector<marineLib::xSectionParam>& theQ
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn("Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)")
			<< "Not enough points"
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) PtsPtr = new TColgp_HArray1OfPnt2d(1, (Standard_Integer)theQ.size());
	auto& Pts = *PtsPtr;

	Standard_Integer K = 0;
	for (const auto& x : theQ)
	{
		Pts.SetValue(++K, gp_Pnt2d(x.x, x.value));
	}

	Geom2dAPI_Interpolate Interpolation(PtsPtr, Standard_False, 1.0e-6);
	Interpolation.Perform();

	if (!Interpolation.IsDone())
	{
		FatalErrorIn("Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)")
			<< "Failed to interpolation!"
			<< abort(FatalError);
	}

	try
	{
		return Interpolation.Curve();
	}
	catch (StdFail_NotDone&)
	{
		return nullptr;
	}
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcArea
(
	const std::vector<marineLib::xSectionParam>& theQ,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn("Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)")
			<< "Not enough points"
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) PtsPtr = new TColgp_HArray1OfPnt2d(1, (Standard_Integer)theQ.size());
	auto& Pts = *PtsPtr;

	Standard_Integer K = 0;
	for (const auto& x : theQ)
	{
		Pts.SetValue(++K, gp_Pnt2d(x.x, x.value));
	}

	Geom2dAPI_Interpolate Interpolation(PtsPtr, Standard_False, 1.0e-6);
	Interpolation.Perform();

	if (!Interpolation.IsDone())
	{
		FatalErrorIn("Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)")
			<< "Failed to interpolation!"
			<< abort(FatalError);
	}

	try
	{
		return Cad2d_CmptLib::AreaUnderCurve(Interpolation.Curve(), 0, theInfo);
	}
	catch (StdFail_NotDone&)
	{
		FatalErrorIn("Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)")
			<< "Failed to interpolation!"
			<< abort(FatalError);

		return 0;
	}
}

Standard_Real
tnbLib::MarineBase_Tools::CalcArea
(
	const Marine_Section & theSection, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	if (NOT theSection.Wire())
	{
		FatalErrorIn("Standard_Real CalcArea(const Marine_Section& theSection, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)")
			<< "invalid section: null wire" << endl
			<< abort(FatalError);
	}

	return Cad2d_CmptLib::Area(*theSection.Wire(), theInfo);
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcArea
(
	const Marine_CmpSection & theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sumArea = 0;
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		sumArea += CalcArea(*x, theInfo);
	}
	return sumArea;
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcWetArea
(
	const Marine_CmpSection & theSection, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sumArea = 0;
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		if(x->IsDry())
			continue;

		sumArea += CalcArea(*x, theInfo);
	}
	return sumArea;
}

tnbLib::Pnt2d 
tnbLib::MarineBase_Tools::CalcCentre
(
	const Marine_Section & theSection, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	if (NOT theSection.Wire())
	{
		FatalErrorIn("Pnt2d CalcCentre(const Marine_Section& theSection, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)")
			<< "invalid section: null wire" << endl
			<< abort(FatalError);
	}

	auto c = Cad2d_CmptLib::Centre(*theSection.Wire(), theInfo);
	return std::move(c);
}

tnbLib::Pnt2d 
tnbLib::MarineBase_Tools::CalcCentre
(
	const Marine_CmpSection & theSection, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<Pnt2d> cs;
	cs.reserve(theSection.NbSections());

	std::vector<Standard_Real> h;
	h.reserve(theSection.NbSections());

	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);

		auto area = CalcArea(*x, theInfo);
		auto c = CalcCentre(*x, theInfo);

		cs.push_back(std::move(c));
		h.push_back(area);
	}

	if (cs.size() IS_EQUAL 1)
		return cs[0];

	Pnt2d sum;
	Standard_Integer K = 0;
	for (const auto& x : cs)
	{
		sum += h[K] * x;
	}

	Standard_Real sumA = 0;
	for (const auto x : h)
	{
		sumA += x;
	}

	return sum / sumA;
}

tnbLib::Pnt2d 
tnbLib::MarineBase_Tools::CalcWetCentre
(
	const Marine_CmpSection & theSection, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<Pnt2d> cs;
	std::vector<Standard_Real> h;

	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);

		if(x->IsDry())
			continue;

		auto area = CalcArea(*x, theInfo);
		auto c = CalcCentre(*x, theInfo);

		cs.push_back(std::move(c));
		h.push_back(area);
	}

	if (cs.size() IS_EQUAL 1)
		return cs[0];

	Pnt2d sum;
	Standard_Integer K = 0;
	for (const auto& x : cs)
	{
		sum += h[K] * x;
	}

	Standard_Real sumA = 0;
	for (const auto x : h)
	{
		sumA += x;
	}

	return sum / sumA;
}

//tnbLib::Pnt2d 
//tnbLib::MarineBase_Tools::CalcWetCentre
//(
//	const Marine_CmpSection & theSection, 
//	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
//)
//{
//	
//}

Standard_Real 
tnbLib::MarineBase_Tools::CalcVolume
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<marineLib::xSectionParam> params;
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam xParam;

		xParam.x = x->X();
		xParam.value = CalcArea(*x, theInfo);

		params.push_back(std::move(xParam));
	}

	return CalcArea(params, theInfo);
}

tnbLib::Pnt3d 
tnbLib::MarineBase_Tools::CalcCentreProductVolume
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<Pnt2d> Bx;
	Bx.reserve(theSections.size());

	std::vector<Standard_Real> Ax;
	Ax.reserve(theSections.size());

	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		
		auto bx = CalcCentre(*x, theInfo);

		Bx.push_back(std::move(bx));
		Ax.push_back(CalcArea(*x, theInfo));
	}

	std::vector<marineLib::xSectionParam> xBarQ;
	xBarQ.reserve(theSections.size());

	Standard_Integer K = 0;
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		
		marineLib::xSectionParam xSect;
		xSect.x = x->X();
		xSect.value = Ax[K++] * x->X();

		xBarQ.push_back(std::move(xSect));
	}

	const auto xBarC = Curve(xBarQ);
	if (NOT xBarC)
	{
		FatalErrorIn("Pnt3d MarineBase_Tools::CalcCentre(Args...)")
			<< "Unable to interpolate the offset points: xBarC" << endl
			<< abort(FatalError);
	}

	std::vector<marineLib::xSectionParam> yBarQ;
	yBarQ.reserve(theSections.size());

	K = 0;
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam xSect;
		xSect.x = x->X();
		xSect.value = Bx[K].X() * Ax[K];

		K++;

		yBarQ.push_back(std::move(xSect));
	}

	const auto yBarC = Curve(yBarQ);
	if (NOT yBarC)
	{
		FatalErrorIn("Pnt3d MarineBase_Tools::CalcCentre(Args...)")
			<< "Unable to interpolate the offset points: yBarC" << endl
			<< abort(FatalError);
	}

	std::vector<marineLib::xSectionParam> zBarQ;
	zBarQ.reserve(theSections.size());

	K = 0;
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam xSect;
		xSect.x = x->X();
		xSect.value = Bx[K++].Y() * Ax[K];

		K++;

		zBarQ.push_back(std::move(xSect));
	}

	const auto zBarC = Curve(zBarQ);
	if (NOT zBarC)
	{
		FatalErrorIn("Pnt3d MarineBase_Tools::CalcCentre(Args...)")
			<< "Unable to interpolate the offset points: zBarC" << endl
			<< abort(FatalError);
	}

	//const auto vol = Cad2d_CmptLib::AreaUnderCurve(xBarC, 0, theInfo);

	const auto xBar = Cad2d_CmptLib::AreaUnderCurve(xBarC, 0, theInfo);
	const auto yBar = Cad2d_CmptLib::AreaUnderCurve(yBarC, 0, theInfo);
	const auto zBar = Cad2d_CmptLib::AreaUnderCurve(zBarC, 0, theInfo);

	return Pnt3d(xBar, yBar, zBar);
}

void tnbLib::MarineBase_Tools::Heel
(
	const std::shared_ptr<Marine_CmpSection>& theSection,
	const gp_Ax2d & theAx
)
{
	const auto& sys = theSection->CoordinateSystem();
	const auto& loc = sys.Location();

	gp_Ax2d O(Pnt2d(loc.X(), loc.Y()), gp_Dir2d(1, 0));

	gp_Trsf2d t;
	t.SetTransformation(O, theAx);

	theSection->Transform(t.Inverted());

	gp_Trsf2d t1;
	t1.SetTranslation(theAx.Location(), O.Location());

	theSection->Transform(t1);
}

//void tnbLib::MarineBase_Tools::Heel
//(
//	const std::shared_ptr<Marine_Section>& theSection,
//	const gp_Ax2d & theAx
//)
//{
//	const auto& sys = theSection->CoordinateSystem();
//	const auto& loc = sys.Location();
//
//	gp_Ax2d O(Pnt2d(loc.X(), loc.Y()), gp_Dir2d(1, 0));
//
//	gp_Trsf2d t;
//	t.SetTransformation(O, theAx);
//
//	theSection->Transform(t.Inverted());
//
//	
//}

void tnbLib::MarineBase_Tools::Heel
(
	const std::shared_ptr<Marine_CrossSection>& theModel, 
	const gp_Ax1 & theAx, 
	const Standard_Real theAngle
)
{
	const auto& loc = theAx.Location();
	const auto angle = ConvertUnit(UnitSystem_Angle_deg, UnitSystem_Angle_rad)*theAngle;

	Pnt2d O(loc.Y(), loc.Z());
	gp_Dir2d dir(cos(angle), sin(angle));

	gp_Ax2d ax(O, dir);

	for (const auto& x : theModel->Sections())
	{
		Debug_Null_Pointer(x);
		Heel(x, ax);
	}
}

//Standard_Real 
//tnbLib::MarineBase_Tools::CalcWetVolume
//(
//	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
//	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
//)
//{
//	std::vector<marineLib::xSectionParam> params;
//	for (const auto& x : theSections)
//	{
//		Debug_Null_Pointer(x);
//
//		marineLib::xSectionParam xParam;
//
//		xParam.x = x->X();
//		xParam.value = CalcWetArea(*x, theInfo);
//
//		params.push_back(std::move(xParam));
//	}
//
//	return CalcArea(params, theInfo);
//}

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

