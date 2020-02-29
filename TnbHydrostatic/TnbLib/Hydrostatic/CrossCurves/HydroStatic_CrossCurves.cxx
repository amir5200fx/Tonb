#include <HydroStatic_CrossCurves.hxx>

#include <Dir3d.hxx>
#include <Entity2d_Box.hxx>
#include <Pln_Tools.hxx>
#include <CrossSection_xShapeStation.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_SectionDistribution.hxx>
#include <Marine_Body.hxx>
#include <Marine_Section.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_Graph.hxx>
#include <Marine_GraphCurve.hxx>
#include <Marine_WaterDomain.hxx>
#include <Geo_UniDistb.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <gp_Ax2.hxx>
#include <Bnd_Box2d.hxx>

#include <map>

namespace tnbLib
{
	const Standard_Integer HydroStatic_CrossCurves::DEFAULT_NB_WATERS(8);
}

tnbLib::HydroStatic_CrossCurves::HydroStatic_CrossCurves
(
	const std::shared_ptr<Marine_Domain>& theDomain
)
	: theDomain_(theDomain)
	, theNbWaters_(DEFAULT_NB_WATERS)
{
}

tnbLib::HydroStatic_CrossCurves::HydroStatic_CrossCurves
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Marine_Domain>& theDomain
)
	: Global_Indexed(theIndex)
	, theDomain_(theDomain)
	, theNbWaters_(DEFAULT_NB_WATERS)
{
}

tnbLib::HydroStatic_CrossCurves::HydroStatic_CrossCurves
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Marine_Domain>& theDomain
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theDomain_(theDomain)
	, theNbWaters_(DEFAULT_NB_WATERS)
{
}

namespace tnbLib
{

	std::vector<std::shared_ptr<Marine_CmpSection>> 
		Copy
		(
			const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
		)
	{
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());

		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x->Copy());
		}
		return std::move(sections);
	}

	namespace hsLib
	{
		static marineLib::xSectionParam
			LeverArm
			(
				const std::vector<std::shared_ptr<Marine_Section>>& theWaters,
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const gp_Ax2d& theIx,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			)
		{
			auto body = MarineBase_Tools::WettedSections(theSections, theWaters);
			Debug_Null_Pointer(body);

			const auto volQ = MarineBase_Tools::CalcVolume(body->Sections(), theInfo);
			const auto vol = MarineBase_Tools::CalcArea(volQ, theInfo);

			const auto IvQ = MarineBase_Tools::CalcIv(theSections, theIx, theInfo);
			const auto Iv = MarineBase_Tools::CalcArea(IvQ, theInfo);

			if (ABS(vol) <= gp::Resolution())
			{
				FatalErrorIn(FunctionSIG)
					<< "divided by zero encountered!" << endl
					<< abort(FatalError);
			}

			marineLib::xSectionParam v;
			v.value = Iv / vol;
			v.x = vol;

			return std::move(v);
		}

		static void DisplaceWaters
		(
			const std::vector<std::shared_ptr<Marine_Section>>& theWaters,
			const Standard_Real z
		)
		{
			for (const auto& x : theWaters)
			{
				Debug_Null_Pointer(x);

				gp_Trsf2d t;
				t.SetTranslation(gp_Vec2d(0, z - x->CoordinateSystem().Location().Y()));

				x->Transform(t);
			}
		}

		static Handle(Geom2d_Curve)
			CrossCurve
			(
				const gp_Ax1& theK,
				const Geo_xDistb& theZ, 
				const std::vector<std::shared_ptr<Marine_Section>>& theWaters, 
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			)
		{
			const auto& loc3 = theK.Location();
			Pnt2d loc(loc3.Y(), loc3.Z());
			gp_Ax2d ax(loc, gp_Dir2d(0, 1));

			std::vector<marineLib::xSectionParam> values;
			for (const auto z : theZ.Values())
			{
				DisplaceWaters(theWaters, z);

				auto v = LeverArm(theWaters, theSections, ax, theInfo);
				values.push_back(std::move(v));
			}

			auto curve = MarineBase_Tools::Curve(values);
			Debug_Null_Pointer(curve);

			return std::move(curve);
		}

		static void 
			Heel
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const gp_Ax2d& theAx
			)
		{
			for (const auto& x : theSections)
			{
				Debug_Null_Pointer(x);
				MarineBase_Tools::Heel(x, theAx);
			}
		}

		static std::shared_ptr<Geo_xDistb>
			Z
			(
				const Standard_Real theZmin, 
				const Standard_Real theZmax, 
				const Standard_Integer n
			)
		{
			const auto Dz = theZmax - theZmin;
			const auto dz = Dz / (Standard_Real)n;

			auto disZ = std::make_shared<Geo_UniDistb>(n);
			Debug_Null_Pointer(disZ);

			disZ->SetLower(theZmin + 0.5*dz);
			disZ->SetUpper(theZmax + 0.5*dz);
			disZ->Perform();

			return std::move(disZ);
		}

		static std::map<Standard_Integer, std::vector<std::shared_ptr<Marine_Section>>>
			Waters
			(
				const Marine_CrossSection& model, 
				const Entity3d_Box& domain,
				const Geo_xDistb& theZ
			)
		{
			const auto xm = MEAN(domain.P0().X(), domain.P1().X());
			const auto ym = MEAN(domain.P0().Y(), domain.P1().Y());

			Standard_Integer k = 0;

			std::map<Standard_Integer, std::vector<std::shared_ptr<Marine_Section>>>
				waters;
			for (const auto z : theZ.Values())
			{
				auto wave = std::make_shared<Marine_FlatWave>(domain);
				Debug_Null_Pointer(wave);

				wave->SetVerticalDirection(Dir3d(0, 0, 1));
				wave->SetPointOnWater(Pnt3d(xm, ym, z));
				wave->Perform();

				auto waterSections =
					MarineBase_Tools::WaterSections(model, *wave, domain, 1.0E-3, 1.0E-6);

				auto pair = std::make_pair(k++, std::move(waterSections));
				waters.insert(std::move(pair));
			}
			return std::move(waters);
		}

		static Entity2d_Box 
			BoundingBox
			(
				const std::vector<Handle(Geom2d_Curve)>& curves
			)
		{
			auto iter = curves.begin();
			auto box = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox((*iter)));

			iter++;
			while (iter NOT_EQUAL curves.end())
			{
				box = Entity2d_Box::Union(box, Pln_Tools::BoundingBox(Pln_Tools::BoundingBox((*iter))));
				iter++;
			}
			return std::move(box);
		}

		static std::shared_ptr<Marine_Graph>
			Graph
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves
			)
		{
			auto box = BoundingBox(theCurves);

			auto g = std::make_shared<Marine_Graph>();
			Debug_Null_Pointer(g);

			g->X().SetLower(box.P0().X());
			g->X().SetUpper(box.P1().X());

			g->Y().SetLower(box.P0().Y());
			g->Y().SetUpper(box.P1().Y());

			g->Y().SetName("Lever Arm");
			g->X().SetName("Displacement Volume");

			g->Title().SetName("Cross-curves of stability");

			auto& curves = g->ChangeCurves();
			curves.reserve(theCurves.size());

			Standard_Integer k = 0;
			for (const auto& x : theCurves)
			{
				Debug_Null_Pointer(x);

				auto c = std::make_shared<Marine_GraphCurve>(++k, x);
				Debug_Null_Pointer(c);

				c->SetPattern(Marine_GraphLinePattern::Solid);

				curves.push_back(c);
			}
			return std::move(g);
		}
	}
}

void tnbLib::HydroStatic_CrossCurves::Perform()
{
	if (NOT Model())
	{
		FatalErrorIn("void HydroStatic_CrossCurves::Perform()")
			<< "the model is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Heel())
	{
		FatalErrorIn("void HydroStatic_CrossCurves::Perform()")
			<< "the distribution of heel is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& model = *Model();
	if (NOT model.IsDone())
	{
		FatalErrorIn("void HydroStatic_CrossCurves::Perform()")
			<< "the cross section algorithm is not performed!" << endl
			<< abort(FatalError);
	}

	fileName myFileName("out2.plt");
	OFstream myFile(myFileName);

	const auto& keel = K().Location();

	auto info = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	Debug_Null_Pointer(info);

	info->SetNbInitIterations(2);
	info->SetTolerance(1.0E-4);

	auto sections = Copy(Model()->Sections());

	std::vector<Handle(Geom2d_Curve)> curves;
	curves.reserve(Heel()->Size());

	for (const auto h : Heel()->Values())
	{

		gp_Ax2d ax(Pnt2d(keel.Y(), keel.Z()), gp_Dir2d(cos(h), sin(h)));

		hsLib::Heel(sections, ax);
		for (const auto& x : sections)
		{
			x->ExportToPlt(myFile);
		}
		const auto b = MarineBase_Tools::BoundingBox(sections);

		const auto Z = hsLib::Z(b.P0().Z(), b.P1().Z(), NbWaters());
		Debug_Null_Pointer(Z);

		auto domains = MarineBase_Tools::RetrieveStillWaterDomains(Domain(), sections, *Z);

		auto curveQ = MarineBase_Tools::CrossCurve(sections, domains, 0, K(), info);
		auto curve = MarineBase_Tools::Curve(curveQ);
		Debug_Null_Pointer(curve);

		curves.push_back(std::move(curve));

		gp_Ax2d ax1(Pnt2d(keel.Y(), keel.Z()), gp_Dir2d(cos(-h), sin(-h)));

		hsLib::Heel(sections, ax1);
	}

	/*auto domain = Domain().OffSet(Domain().Diameter()*0.25);
	
	auto waters = hsLib::Waters(model, domain, *Z);

	const auto& keel = K().Location();

	auto info = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	Debug_Null_Pointer(info);

	info->SetNbInitIterations(2);
	info->SetTolerance(1.0E-4);

	Pnt2d loc(keel.Y(), keel.Z());
	gp_Ax2d Ix(loc, gp_Dir2d(0, 1));

	std::vector<Handle(Geom2d_Curve)> curves;
	curves.reserve(Heel()->Size());

	auto sections = Copy(Model()->Sections());
	for (const auto h : Heel()->Values())
	{
		gp_Ax2d ax(Pnt2d(keel.Y(), keel.Z()), gp_Dir2d(cos(-h), sin(-h)));

		hsLib::Heel(sections, ax);

		std::vector<marineLib::xSectionParam> values;
		for (const auto& x : waters)
		{
			auto z = Z->Value(x.first);
			const auto& w = x.second;

			auto v = hsLib::LeverArm(w, sections, Ix, info);
			values.push_back(std::move(v));
		}

		auto curve = MarineBase_Tools::Curve(values);
		Debug_Null_Pointer(curve);

		curves.push_back(std::move(curve));
	}*/

	ChangeGraph() = hsLib::Graph(curves);

	Change_IsDone() = Standard_True;
}