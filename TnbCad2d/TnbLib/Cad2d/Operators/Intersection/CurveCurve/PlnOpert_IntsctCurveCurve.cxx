#include <PlnOpert_IntsctCurveCurve.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <PlnOpert_IntsctPoint.hxx>
#include <PlnOpert_IntsctSegment.hxx>
#include <PlnOpert_IntsctPair.hxx>
#include <Pln_Tools.hxx>
#include <PlnOpert_IntsctCurveCurve_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Standard_Handle.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2dInt_GInter.hxx>
#include <Geom2d_Curve.hxx>

void tnbLib::PlnOpert_IntsctCurveCurve::Perform()
{
	if (NOT Curve0())
	{
		FatalErrorIn("void Perform()")
			<< "Null edge0" << endl
			<< abort(FatalError);
	}

	if (NOT Curve1())
	{
		FatalErrorIn("void Perform()")
			<< "Null edge1" << endl
			<< abort(FatalError);
	}

	if (NOT Info())
	{
		FatalErrorIn("void Perform()")
			<< "no info has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& curve0 = *Curve0();
	const auto& curve1 = *Curve1();

	auto Inter =
		Pln_Tools::Intersection
		(
			curve0.Geometry(),
			curve1.Geometry(), Info()->Tolerance());

	const auto& alg = Inter->Intersector();

	auto& entities = ChangeEntities();
	entities.reserve(alg.NbPoints() + alg.NbPoints());

	forThose(Index, 1, alg.NbPoints())
	{
		const auto& pt = alg.Point(Index);

		

		auto entity0 = std::make_shared<PlnOpert_IntsctPoint>(0);
		auto entity1 = std::make_shared<PlnOpert_IntsctPoint>(0);
		Debug_Null_Pointer(entity0);
		Debug_Null_Pointer(entity1);

		entity0->SetParentCurve(Curve0());
		entity1->SetParentCurve(Curve1());

		entity0->SetCoord(pt.Value());
		entity1->SetCoord(pt.Value());

		entity0->SetParameter(pt.ParamOnFirst());
		entity1->SetParameter(pt.ParamOnSecond());

		auto pair = std::make_shared<PlnOpert_IntsctPair>(0, entity0, entity1);
		Debug_Null_Pointer(pair);

		entities.push_back(pair);
	}

	forThose(Index, 1, alg.NbSegments())
	{
		const auto& seg = alg.Segment(Index);

		if (NOT seg.HasFirstPoint())
		{
			FatalErrorIn("void Perform()") << endl
				<< "the segment deos not have first point!" << endl
				<< abort(FatalError);
		}

		if (NOT seg.HasLastPoint())
		{
			FatalErrorIn("void Perform()") << endl
				<< "the segment deos not have first point!" << endl
				<< abort(FatalError);
		}

		

		auto entity0 = std::make_shared<PlnOpert_IntsctSegment>(0);
		auto entity1 = std::make_shared<PlnOpert_IntsctSegment>(0);
		Debug_Null_Pointer(entity0);
		Debug_Null_Pointer(entity1);

		entity0->SetParentCurve(Curve0());
		entity1->SetParentCurve(Curve1());

		const auto& pt0 = seg.FirstPoint();
		const auto& pt1 = seg.LastPoint();

		entity0->SetCoord0(pt0.Value());
		entity0->SetCoord1(pt1.Value());
		entity0->SetParameter0(pt0.ParamOnFirst());
		entity0->SetParameter1(pt1.ParamOnFirst());

		if (seg.IsOpposite())
		{
			entity1->SetCoord0(pt1.Value());
			entity1->SetCoord1(pt0.Value());
			entity1->SetParameter0(pt1.ParamOnSecond());
			entity1->SetParameter1(pt0.ParamOnSecond());
		}
		else
		{
			entity1->SetCoord0(pt0.Value());
			entity1->SetCoord1(pt1.Value());
			entity1->SetParameter0(pt0.ParamOnSecond());
			entity1->SetParameter1(pt1.ParamOnSecond());
		}

		auto pair = std::make_shared<PlnOpert_IntsctPair>(0, entity0, entity1);
		Debug_Null_Pointer(pair);

		entities.push_back(pair);
	}
}