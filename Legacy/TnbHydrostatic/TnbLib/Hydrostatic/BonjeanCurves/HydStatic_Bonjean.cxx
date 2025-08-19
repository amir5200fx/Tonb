#include <HydStatic_Bonjean.hxx>

#include <Pln_Tools.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Body.hxx>
#include <Marine_Water.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <Marine_BooleanOps.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_GraphCurve.hxx>
#include <Marine_Graph.hxx>
#include <Marine_System.hxx>
#include <Marine_xSectionParam.hxx>
#include <Marine_Section.hxx>
#include <HydStatic_BnjCurve.hxx>
#include <HydStatic_Spacing.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Bnd_Box2d.hxx>
#include <Geom2d_Curve.hxx>

unsigned short tnbLib::HydStatic_Bonjean::verbose(0);

tnbLib::HydStatic_Bonjean::HydStatic_Bonjean
(
	const std::shared_ptr<Marine_MultLevWaterDomain>& theWaters
)
	: theWaters_(theWaters)
{
	//- empty body
}

namespace tnbLib
{
	namespace bonjean
	{

		static std::vector<marineLib::xSectionParam>
			GetOffsets
			(
				const std::vector<Standard_Real>& theValues,
				const std::vector<Standard_Real>& theX
			)
		{
			std::vector<marineLib::xSectionParam> Q;

			Standard_Integer indx = -1;
			for (size_t i = 0; i < theValues.size() - 1; i++)
			{
				if (theValues[i + 1] > 0)
				{
					indx = (Standard_Integer)i;
					break;
				}
			}

			indx = 0;  //  [5/29/2021 Amir]
			if (indx < 0)
			{
				FatalErrorIn(FunctionSIG)
					<< "unexpected situation has been occurred!" << endl
					<< abort(FatalError);
			}

			for (size_t i = indx; i < theValues.size(); i++)
			{
				auto x = theX[i];
				auto v = theValues[i];

				marineLib::xSectionParam p;
				p.x = x;
				p.value = v;

				Q.push_back(std::move(p));
			}

			return std::move(Q);
		}

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

			g->Y().SetName("Draught");
			g->X().SetName("area");

			g->Title().SetName("Bonjean curves");

			g->ChangeCurves() = std::move(theCurves);

			return std::move(g);
		}
	}
}

void tnbLib::HydStatic_Bonjean::Perform()
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Calculating Bonjean Curves ********" << endl;
		Info << endl;
	}

	if (NOT Waters())
	{
		FatalErrorIn("void HydStatic_Bonjean::Perform()")
			<< "no water distribution has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Waters()->Body())
	{
		FatalErrorIn("void HydStatic_Bonjean::Perform()")
			<< "the model is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& body = Waters()->Body();

	if (verbose)
	{
		Info << " Body's name: " << body->Name() << endl;
		Info << " nb. of sections: " << body->NbSections() << endl;
	}

	if (NOT Waters()->Domain())
	{
		FatalErrorIn("void HydStatic_Bonjean::Perform()")
			<< "no domain has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& waters = Waters()->Waters();	

	const auto& sections = body->Sections();
	if (sections.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no section in the body!" << endl
			<< abort(FatalError);
	}
	tableOffset qArea(body->NbSections());
	for (auto& x : qArea)
	{
		x.resize(waters.size(), 0);
	}

	if (verbose)
	{
		Info << " - nb. of waters: " << (int)waters.size() << endl;
	}

	Standard_Integer i = 0;
	Standard_Integer iter = 0;

	std::vector<Standard_Real> spacing;
	spacing.reserve(waters.size());
	for (const auto& w : waters)
	{
		Debug_Null_Pointer(w);

		spacing.push_back(w->Z());

		if (verbose)
		{
			Info << endl;
			Info << " - Iteration nb. " << ++iter << ", z = " << w->Z() << endl;
			Info << endl;
			Info << " z = " << w->Z() << endl;
			Info << " Still waters calculations..." << endl;
		}
		//auto domain = Marine_WaterLib::StillWaterDomain(Body(), Domain(), z);
		//Debug_Null_Pointer(domain);

		Debug_Null_Pointer(w->Water());
		if (verbose)
		{
			Info << " Still waters are calculated successfully" << endl;
			Info << " nb. of water sections: " << w->Water()->NbSections() << endl;
		}
	
		const auto& wSections = w->Water()->Sections();

		if (verbose > 1)
		{
			Info << " Wetted section's area calculations..." << endl;
		}
		Standard_Integer k = 0;
		for (const auto& w : wSections)
		{
			Debug_Null_Pointer(w);

			const auto& x = sections[k];
			Debug_Null_Pointer(x);

			if (verbose > 1)
			{
				Info << " water section's id: " << w->Index() << endl;
				Info << " retrieving wetted section via applying boolean operator between water section and" << endl
					<< " section id, " << x->Index() << endl;
			}
			auto wet = Marine_BooleanOps::WettedSection(x, w);

			if (wet)
			{
				if (verbose > 1)
				{
					Info << " the wetted section are retrieved, successfully" << endl;
				}
				wet->SetCoordinateSystem(x->CoordinateSystem());

				if (verbose > 1)
				{
					Info << " calculating the area of the wetted section..." << endl;
				}
				qArea[k][i] = MarineBase_Tools::CalcArea(*wet, sysLib::gl_marine_integration_info);
				if (verbose > 1)
				{
					Info << " Area= " << qArea[k][i] << endl;
				}
			}
			else
			{
				if (verbose > 1)
				{
					Info << " there is no intersection between water and body's section" << endl;
				}
				//qArea[k][i] = 0;
			}
			
			k++;
		}
		i++;
	}

	auto& bj = ChangeBonjean();

	Standard_Integer k = 0;

	if (verbose)
	{
		Info << endl << endl;
		Info << " creating the curves..." << endl;
	}
	std::vector<std::shared_ptr<Marine_GraphCurve>> curves;
	for (const auto& sect : qArea)
	{
		if (verbose > 1)
		{
			Info << " k = " << k + 1 << endl;
			Info << " getting offsets..." << endl;
		}
		auto Q = bonjean::GetOffsets(sect, spacing);

		if (verbose > 1)
		{
			Info << " creating the curve..." << endl;
		}
		auto c = MarineBase_Tools::Curve(Q);
		Debug_Null_Pointer(c);

		const auto& x = sections[k];
		Debug_Null_Pointer(x);

		++k;

		c->Translate(gp_Vec2d(x->X(), 0));

		auto gc = std::make_shared<Marine_GraphCurve>(k, c);
		Debug_Null_Pointer(gc);

		curves.push_back(gc);

		auto ent = 
			std::make_shared<entity>
			(
				x, 
				std::make_shared<HydStatic_BnjCurve>(k, c)
				);
		Debug_Null_Pointer(ent);

		bj.push_back(std::move(ent));
	}

	if (verbose)
	{
		Info << " creating the graph..." << endl;
	}
	auto graph = bonjean::Graph(curves);
	Debug_Null_Pointer(graph);

	ChangeGraph() = std::move(graph);

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of Calculating Bonjean Curves ********" << endl;
		Info << endl;
	}
}