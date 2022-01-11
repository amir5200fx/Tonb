#include <Cad_tEdgeMaker.hxx>

#include <TModel_Edges.hxx>
#include <TModel_Curve.hxx>
#include <TModel_ParaCurve.hxx>
#include <Pln_Tools.hxx>
#include <Cad_Tools.hxx>
#include <Cad_tEdgeMakerInfo.hxx>
#include <Cad_tEdgeMakerInfo_Absolute.hxx>

#include <TopLoc_Location.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <Geom2d_Curve.hxx>
#include <Precision.hxx>

const std::shared_ptr<tnbLib::Cad_tEdgeMakerInfo> tnbLib::Cad_tEdgeMaker::DEFAULT_INFO =
std::make_shared<tnbLib::Cad_tEdgeMakerInfo_Absolute>(Precision::Confusion());

void tnbLib::Cad_tEdgeMaker::Perform()
{
	if (NOT Info())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info is found!" << endl
			<< abort(FatalError);
	}

	if (Shape().IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "no edge has been loaded" << endl
			<< abort(FatalError);
	}

	if (Face().IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "no face has been loaded" << endl
			<< abort(FatalError);
	}

	Standard_Real u0, u1, U0, U1;
	TopLoc_Location pLoc, eLoc;
	auto patch = BRep_Tool::Surface(Face(), pLoc);

	if (NOT BRep_Tool::SameRange(Shape()))
	{
		BRepLib::SameRange(Shape());
	}

	if (NOT BRep_Tool::SameParameter(Shape()))
	{
		BRepLib::SameParameter(Shape());
	}

	if (NOT BRep_Tool::SameParameter(Shape()))
	{
		FatalErrorIn(FunctionSIG)
			<< "It's supposed that the edge has SameParameter flag" << endl
			<< abort(FatalError);
	}

	if (NOT BRep_Tool::SameRange(Shape()))
	{
		FatalErrorIn(FunctionSIG)
			<< "It's supposed that the edge has SameRange flag" << endl
			<< abort(FatalError);
	}

	auto pCurve0 = BRep_Tool::CurveOnSurface(Shape(), patch, pLoc, u0, u1);
	auto pCurve = Handle(Geom2d_Curve)::DownCast(pCurve0->Copy());

	auto Curve = BRep_Tool::Curve(Shape(), eLoc, U0, U1);

	if (Shape().Orientation() IS_EQUAL TopAbs_REVERSED)
	{
		auto temp = u1;
		u1 = pCurve->ReversedParameter(u0);
		u0 = pCurve->ReversedParameter(temp);
		pCurve->Reverse();
	}

	if (NOT Pln_Tools::IsBounded(pCurve))
	{
		pCurve = Pln_Tools::ConvertToTrimmedCurve(pCurve, u0, u1);
	}

	auto curveOnPlane = std::make_shared<TModel_ParaCurve>(pCurve);

	std::shared_ptr<TModel_Edge> newEdge;
	if (Curve)
	{// the curve is generated [1/7/2022 Amir]
		const auto tol = Info()->Tolerance();
		Curve = Handle(Geom_Curve)::DownCast(Curve->Copy());
		
		if (NOT Cad_Tools::IsBounded(Curve))
		{
			Curve = Cad_Tools::ConvertToTrimmed(Curve, U0, U1);
		}

		if (Cad_Tools::IsRing(Curve, U0, U1, tol))
		{
			auto curveOnSurface = std::make_shared<TModel_Curve>(Curve);
			newEdge = std::make_shared<TModel_RingEdge>(curveOnSurface, curveOnPlane);
		}
		else
		{
			auto curveOnSurface = std::make_shared<TModel_Curve>(Curve);
			newEdge = std::make_shared<TModel_SegmentEdge>(curveOnSurface, curveOnPlane);
		}
	}
	else
	{ // the curve is deGenerated [1/7/2022 Amir]
		newEdge = std::make_shared<TModel_SingularEdge>(curveOnPlane);
	}

	theEdge_ = std::move(newEdge);

	Change_IsDone() = Standard_True;
}