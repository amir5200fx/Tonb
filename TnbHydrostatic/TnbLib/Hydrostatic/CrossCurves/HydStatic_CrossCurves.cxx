#include <HydStatic_CrossCurves.hxx>

#include <Global_Timer.hxx>
#include <Pnt2d.hxx>
#include <Dir3d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <Pln_Tools.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <Marine_CmpSection.hxx>
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
#include <Marine_BodyTools.hxx>
#include <Marine_System.hxx>
#include <HydStatic_CrsCurve.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>
#include <HydStatic_HeelSpacing.hxx>
#include <HydStatic_Spacing.hxx>
#include <HydStatic_Tools.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

#include <gp_Ax2d.hxx>
#include <Bnd_Box2d.hxx>
#include <Geom2d_Curve.hxx>

#include <math.h>

namespace tnbLib
{
	const gp_Ax1 HydStatic_CrossCurves::null = gp::OX();
	const Standard_Integer HydStatic_CrossCurves::DEFAULT_NB_WATERS(10);

	unsigned short HydStatic_CrossCurves::verbose(0);
}

tnbLib::HydStatic_CrossCurves::HydStatic_CrossCurves()
	: theAx_(null)
	, theVolCoeff_(0.005)
{
	// empty body
}

tnbLib::HydStatic_CrossCurves::HydStatic_CrossCurves
(
	const std::shared_ptr<Marine_MultLevWaterDomain>& theWaters,
	const std::shared_ptr<HydStatic_HeelSpacing>& theHeels,
	const gp_Ax1 & theAx
)
	: theWaters_(theWaters)
	, theHeels_(theHeels)
	, theAx_(theAx)
	, theVolCoeff_(0.005)
{
	// empty body
}

namespace tnbLib
{

	namespace crossCurves
	{

		/*static std::shared_ptr<Marine_Graph>
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
		}*/

		auto RemoveDegeneracies(const xSectParList& l, const Standard_Real tol)
		{
			xSectParList xs;
			for (const auto& x : l)
			{
				auto p = x;
				if (p.x >= tol)
				{
					xs.push_back(std::move(p));
				}
			}
			return std::move(xs);
		}
	}
}

void tnbLib::HydStatic_CrossCurves::Perform(const hydStcLib::CurveMakerType t)
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Calculating Cross-Curves ********" << endl;
		Info << endl;
	}

	if (NOT Waters())
	{
		FatalErrorIn("void HydStatic_CrossCurves::Perform()")
			<< " no water is loaded!" << endl
			<< abort(FatalError);
	}

	const auto& wbody = Waters()->Body();
	if (NOT wbody)
	{
		FatalErrorIn("void HydStatic_CrossCurves::Perform()")
			<< " no body is loaded!" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		Info << " Body's name: " << wbody->Name() << endl;
		Info << " nb. of sections: " << wbody->NbSections() << endl;
	}

	if (NOT Waters()->Domain())
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
	if (verbose)
	{
		Info << " Keel axis: " << endl;
		Info << "  - location: " << Ax().Location() << endl;
		Info << "  - direction: " << Ax().Direction() << endl;
	}

	const auto& heels = Heels()->Spacing();
	auto body = wbody->Copy();

	//OFstream ff("bodies.plt");

	const auto volume = Marine_BodyTools::CalcVolume(*body, sysLib::gl_marine_integration_info);
	const auto volTol = volume * theVolCoeff_;

	Standard_Integer K = 0;
	Standard_Real h0 = 0;
	//std::vector<std::shared_ptr<Marine_GraphCurve>> curves;
	std::vector<std::shared_ptr<HydStatic_CrsCurve>> curves;
	curves.reserve(heels->NbSections());

	if (verbose)
	{
		Info << " - nb. of heels: " << heels->NbSections() << endl;
		Info << " - nb. of waters: " << Waters()->Waters().size() << endl;
	}
	if (verbose > 1)
	{
		const auto& inf = sysLib::gl_marine_integration_info;
		Info << "integration's settings:" << endl;
		Info << " - max. nb. of iterations: " << inf->MaxNbIterations() << endl;
		Info << " - nb. of initial subdivisions: " << inf->NbInitIterations() << endl;
		Info << " - tolerance: " << inf->Tolerance() << endl;
	}

	for (const auto h : heels->Sections())
	{
		if (verbose)
		{
			Info << endl;
			Info << " - Iteration nb. " << K + 1 << ", heel = " << h << endl;
			Info << endl;
		}

		gp_Ax2d ax(Pnt2d(keel.Y(), keel.Z()), gp_Dir2d(cos(h - h0), -sin(h - h0)));

		if (verbose) Info << " heeling the body..." << endl;
		Marine_BodyTools::Heel(body, ax);
		/*for (const auto& xx : body->Sections())
		{
			xx->ExportToPlt(ff);
		}*/
		if (verbose)
		{
			Info << " calculating the waters..." << endl;
		}
		const auto b = Marine_BodyTools::BoundingBox(*body);

		if (verbose)
		{
			Info << " z0 " << b.P0().Z() << ", z1 = " << b.P1().Z() << endl;
		}
		//const auto Z = HydStatic_CrossCurves::Z(b.P0().Z(), b.P1().Z(), NbWaters());

		const auto& domains = Waters();
		//auto domains = Marine_WaterLib::MultiLevelsStillWaterDomain(Body(), Domain(), *Z);
		Debug_Null_Pointer(domains);

		if (verbose) Info << " nb. of waters: " << domains->Waters().size() << endl;
		if (verbose) Info << " calculating the cross-curve..." << endl;
		Handle(Geom2d_Curve) curve;
		{// timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			auto curveQ =
				Marine_BodyCmptLib::CrossCurve
				(
					body, *domains, 0, Ax(),
					sysLib::gl_marine_integration_info
				);

			curveQ = crossCurves::RemoveDegeneracies(curveQ, volTol);
			if (curveQ.size() < 2)
			{
				FatalErrorIn(FunctionSIG)
					<< "there are not enough data points to create a curve" << endl
					<< abort(FatalError);
			}

			if (verbose) Info << " creating the geometric curve..." << endl;
			curve = MarineBase_Tools::Curve(curveQ);
		}
		Debug_Null_Pointer(curve);
		if (verbose)
		{
			Info << "the cross-curve is calculated in, " << global_time_duration << " ms" << endl;
		}

		auto cross = HydStatic_Tools::CrossCurve(std::move(curve), Heels()->HeelType());
		Debug_Null_Pointer(cross);
		cross->SetHeel(h);
		cross->SetIndex(++K);

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

	auto graph = std::make_shared<HydStatic_CrsCurvesGraph>(0, "cross-curves");
	graph->Perform(curves);
	Debug_If_Condition_Message(NOT graph->IsDone(), "the algorithm is not performed");

	ChangeCrossCurves() = std::move(graph);

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of Calculating Cross-Curves ********" << endl;
		Info << endl;
	}
}

void tnbLib::HydStatic_CrossCurves::SetVolumeCoeff(const Standard_Real x)
{
	theVolCoeff_ = std::min(0.5, std::max(x, 0.0001));
}

std::shared_ptr<tnbLib::Geo_xDistb> 
tnbLib::HydStatic_CrossCurves::Z
(
	const Standard_Real theZ0,
	const Standard_Real theZ1,
	const Standard_Integer theN
)
{
	const auto c = (theZ1 - theZ0) / 2;
	const auto dt = M_PI / (Standard_Real)theN;
	const auto dz = c * ((Standard_Real)1.0 - std::cos(dt));

	/*const auto Dz = theZ1 - theZ0;
	const auto dz = Dz / (Standard_Real)theN;*/

	auto disZ = std::make_shared<Geo_CosineDistb>(theN);
	Debug_Null_Pointer(disZ);

	disZ->SetLower(theZ0 + 0.005*dz);
	disZ->SetUpper(theZ1 + 0.005*dz);
	disZ->Perform();

	return std::move(disZ);
}