#include <HydStatic_CrossCurves.hxx>

#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <Pln_Tools.hxx>
#include <Geo_UniDistb.hxx>
#include <Marine_Body.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_BodyCmptLib.hxx>
#include <Marine_Graph.hxx>
#include <Marine_GraphCurve.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_CmptLib2.hxx>
#include <Marine_System.hxx>
#include <HydStatic_CrsCurve.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <vector>

#include <gp_Ax2d.hxx>
#include <Bnd_Box2d.hxx>
#include <Geom2d_Curve.hxx>

namespace tnbLib
{
	const gp_Ax1 HydStatic_CrossCurves::null = gp::OX();
	const Standard_Integer HydStatic_CrossCurves::DEFAULT_NB_WATERS(10);
}

tnbLib::HydStatic_CrossCurves::HydStatic_CrossCurves()
	: theAx_(null)
	, theNbWaters_(DEFAULT_NB_WATERS)
{
}

tnbLib::HydStatic_CrossCurves::HydStatic_CrossCurves
(
	const std::shared_ptr<Marine_Domain>& theDomain, 
	const std::shared_ptr<Marine_Body>& theBody,
	const std::shared_ptr<Geo_xDistb>& theHeels,
	const Standard_Integer theNbWaters,
	const gp_Ax1 & theAx
)
	: theDomain_(theDomain)
	, theBody_(theBody)
	, theHeels_(theHeels)
	, theNbWaters_(theNbWaters)
	, theAx_(theAx)
{
}

namespace tnbLib
{

	namespace crossCurves
	{

		static std::shared_ptr<Marine_Graph>
			Graph
			(
				const std::vector<std::shared_ptr<Marine_GraphCurve>>& theCurves
			)
		{
			auto iter = theCurves.begin();
			const auto& x = *iter;
			Debug_Null_Pointer(x);

			auto box = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(x->Curve()));
			iter++;

			while (iter NOT_EQUAL theCurves.end())
			{
				const auto& x = *iter;
				Debug_Null_Pointer(x);

				box = Entity2d_Box::Union
				(
					box,
					Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(x->Curve()))
				);

				iter++;
			}

			auto g = std::make_shared<Marine_Graph>();
			Debug_Null_Pointer(g);

			g->X().SetLower(box.P0().X());
			g->X().SetUpper(box.P1().X());

			g->Y().SetLower(box.P0().Y());
			g->Y().SetUpper(box.P1().Y());

			g->Y().SetName("Lever Arm");
			g->X().SetName("Displacement Volume");

			g->Title().SetName("Cross-curves of stability of the section");

			g->ChangeCurves() = std::move(theCurves);

			return std::move(g);
		}
	}
}

void tnbLib::HydStatic_CrossCurves::Perform()
{
	if (NOT Body())
	{
		FatalErrorIn("void HydStatic_CrossCurves::Perform()")
			<< " no body is loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Domain())
	{
		FatalErrorIn("void HydStatic_CrossCurves::Perform()")
			<< " no domain is loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Heels())
	{
		FatalErrorIn("void HydStatic_CrossCurves::Perform()")
			<< " no heel distribution is loaded!" << endl
			<< abort(FatalError);
	}

	if (&Ax() IS_EQUAL &null)
	{
		FatalErrorIn("void HydStatic_CrossCurves::Perform()")
			<< " no axis is loaded!" << endl
			<< abort(FatalError);
	}

	const auto& keel = Ax().Location();

	auto body = Body()->Copy();

	Standard_Integer K = 0;
	Standard_Real h0 = 0;
	//std::vector<std::shared_ptr<Marine_GraphCurve>> curves;
	auto& curves = ChangeCrossCurves();
	curves.reserve(Heels()->Size());

	for (const auto h : Heels()->Values())
	{
		gp_Ax2d ax(Pnt2d(keel.Y(), keel.Z()), gp_Dir2d(cos(h - h0), sin(h - h0)));

		Marine_BodyTools::Heel(body, ax);

		const auto b = Marine_BodyTools::BoundingBox(*body);
		const auto Z = HydStatic_CrossCurves::Z(b.P0().Z(), b.P1().Z(), NbWaters());

		auto domains = Marine_WaterLib::MultiLevelsStillWaterDomain(Body(), Domain(), *Z);
		Debug_Null_Pointer(domains);

		auto curveQ = 
			Marine_BodyCmptLib::CrossCurve
			(
				body, *domains, 0, Ax(),
				sysLib::gl_marine_integration_info
			);

		auto curve = MarineBase_Tools::Curve(curveQ);
		Debug_Null_Pointer(curve);

		auto cross = std::make_shared<HydStatic_CrsCurve>(++K, curve, h);

		/*auto gc = std::make_shared<Marine_GraphCurve>(++K, curve);
		Debug_Null_Pointer(gc);*/

		curves.push_back(std::move(cross));

		h0 = h;
		/*gp_Ax2d ax1(Pnt2d(keel.Y(), keel.Z()), gp_Dir2d(cos(-h), sin(-h)));

		MarineBase_Tools::Heel(sections, ax1);*/
	}

	/*auto graph = crossCurves::Graph(curves);
	Debug_Null_Pointer(graph);

	ChangeGraph() = std::move(graph);*/

	Change_IsDone() = Standard_True;
}

std::shared_ptr<tnbLib::Geo_xDistb> 
tnbLib::HydStatic_CrossCurves::Z
(
	const Standard_Real theZ0,
	const Standard_Real theZ1,
	const Standard_Integer theN
)
{
	const auto Dz = theZ1 - theZ0;
	const auto dz = Dz / (Standard_Real)theN;

	auto disZ = std::make_shared<Geo_UniDistb>(theN);
	Debug_Null_Pointer(disZ);

	disZ->SetLower(theZ0 + 0.5*dz);
	disZ->SetUpper(theZ1 + 0.5*dz);
	disZ->Perform();

	return std::move(disZ);
}