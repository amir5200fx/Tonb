#include <HydStatic_Bonjean.hxx>

#include <Geo_xDistb.hxx>
#include <Pln_Tools.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Body.hxx>
#include <Marine_Water.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_BooleanOps.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_GraphCurve.hxx>
#include <Marine_Graph.hxx>
#include <Marine_System.hxx>
#include <Marine_xSectionParam.hxx>
#include <HydStatic_BnjCurve.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Bnd_Box2d.hxx>
#include <Geom2d_Curve.hxx>

tnbLib::HydStatic_Bonjean::HydStatic_Bonjean()
{
}

tnbLib::HydStatic_Bonjean::HydStatic_Bonjean
(
	const std::shared_ptr<Marine_Domain>& theDomain, 
	const std::shared_ptr<Marine_Body>& theBody,
	const std::shared_ptr<Geo_xDistb>& theWaters
)
	: theDomain_(theDomain)
	, theBody_(theBody)
	, theWaters_(theWaters)
{
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
	if (NOT Body())
	{
		FatalErrorIn("void HydStatic_Bonjean::Perform()")
			<< "the model is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& sections = Body()->Sections();
	tableOffset qArea;

	Standard_Integer i = 0;
	for (const auto z : Waters()->Values())
	{
		auto domain = Marine_WaterLib::StillWaterDomain(Body(), Domain(), z);
		Debug_Null_Pointer(domain);

		Debug_Null_Pointer(domain->Water());
		const auto& wSections = domain->Water()->Sections();

		Standard_Integer k = 0;
		for (const auto& w : wSections)
		{
			Debug_Null_Pointer(w);

			const auto& x = sections[k++];
			Debug_Null_Pointer(x);

			auto wet = Marine_BooleanOps::WettedSection(x, w);

			if (wet)
			{
				wet->SetCoordinateSystem(x->CoordinateSystem());

				qArea[i][k] = MarineBase_Tools::CalcArea(*wet, sysLib::gl_marine_integration_info);
			}
			else
			{
				qArea[i][k] = 0;
			}

			i++;
			k++;
		}
	}

	auto& bj = ChangeBonjean();

	Standard_Integer k = 0;

	std::vector<std::shared_ptr<Marine_GraphCurve>> curves;
	for (const auto& sect : qArea)
	{
		auto Q = bonjean::GetOffsets(sect, Waters()->Values());

		auto c = MarineBase_Tools::Curve(Q);
		Debug_Null_Pointer(c);

		const auto& x = sections[k];
		Debug_Null_Pointer(x);

		++k;

		c->Translate(gp_Vec2d(x->X(), 0));

		auto gc = std::make_shared<Marine_GraphCurve>(k, c);
		Debug_Null_Pointer(gc);

		curves.push_back(gc);

		auto ent = std::make_shared<entity>(x, std::make_shared<HydStatic_BnjCurve>(k, c));
		Debug_Null_Pointer(ent);

		bj.push_back(std::move(ent));
	}

	auto graph = bonjean::Graph(curves);
	Debug_Null_Pointer(graph);

	ChangeGraph() = std::move(graph);

	Change_IsDone() = Standard_True;
}