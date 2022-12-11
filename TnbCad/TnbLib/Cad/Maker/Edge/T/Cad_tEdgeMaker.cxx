#include <Cad_tEdgeMaker.hxx>

#include <TModel_Edges.hxx>
#include <TModel_Curve.hxx>
#include <TModel_ParaCurve.hxx>
#include <TModel_Vertex.hxx>
#include <Pln_Tools.hxx>
#include <Cad_Tools.hxx>
#include <Cad_tEdgeMakerInfo.hxx>
#include <Cad_tEdgeMakerInfo_Absolute.hxx>

#include <TopLoc_Location.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <Geom2d_Curve.hxx>
#include <Precision.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

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

	//if (Shape().Orientation() IS_EQUAL TopAbs_REVERSED)
	//{
		/*const auto P0 = pCurve->Value(u0);
		const auto P1 = pCurve->Value(u1);

		pCurve->Reverse();

		{
			Geom2dAPI_ProjectPointOnCurve alg(P1, pCurve);
			if (NOT alg.NbPoints())
			{
				FatalErrorIn(FunctionSIG)
					<< " Failed to reverse the curve." << endl
					<< abort(FatalError);
			}
			u0 = alg.LowerDistanceParameter();
		}
		{
			Geom2dAPI_ProjectPointOnCurve alg(P0, pCurve);
			if (NOT alg.NbPoints())
			{
				FatalErrorIn(FunctionSIG)
					<< " Failed to reverse the curve." << endl
					<< abort(FatalError);
			}
			u1 = alg.LowerDistanceParameter();
		}*/
		/*std::cout << "it's reversed." << std::endl;
		std::cout << "u0 = " << u0 << std::endl;
		std::cout << "u1 = " << u1 << std::endl;
		std::cout << std::endl;
		auto temp = u1;
		u1 = pCurve->ReversedParameter(u0);
		u0 = pCurve->ReversedParameter(temp);
		
		std::cout << "curve p0: " << pCurve->FirstParameter() << std::endl;
		std::cout << "curve p1: " << pCurve->LastParameter() << std::endl;
		std::cout << std::endl;
		std::cout << "u0 = " << u0 << std::endl;
		std::cout << "u1 = " << u1 << std::endl;
		std::cout << "-------------------------------------" << std::endl;*/
		//u1 = pCurve->ReversedParameter(u1);
		//u0 = pCurve->ReversedParameter(u0);
		//pCurve->Reverse();
	//}

	if (NOT Pln_Tools::IsBounded(pCurve))
	{
		pCurve = Pln_Tools::ConvertToTrimmedCurve(pCurve, u0, u1);
	}
	else
	{
		if (std::abs(pCurve->FirstParameter() - u0) > gp::Resolution() OR std::abs(pCurve->LastParameter() - u1) > gp::Resolution())
		{
			pCurve = Pln_Tools::ConvertToTrimmedCurve(pCurve, u0, u1);
		}
	}
	if (Shape().Orientation() IS_EQUAL TopAbs_REVERSED)
	{
		pCurve->Reverse();
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
			auto pm = MEAN(Pnt3d(Curve->Value(U0)), Pnt3d(Curve->Value(U1)));
			auto vtx = std::make_shared<TModel_Vertex>(0, std::move(pm));

			auto curveOnSurface = std::make_shared<TModel_Curve>(Curve);
			auto edge = std::make_shared<TModel_RingEdge>(vtx, curveOnSurface, curveOnPlane);
			Debug_Null_Pointer(edge);

			auto [tri, params] = Cad_Tools::RetrievePolygonOnTriangulation(Shape(), Face());
			edge->SetMesh(std::move(tri));
			edge->SetParaMesh(std::move(params));

			newEdge = std::move(edge);
		}
		else
		{
			auto p0 = Pnt3d(Curve->Value(U0));
			auto p1 = Pnt3d(Curve->Value(U1));

			auto vtx0 = std::make_shared<TModel_Vertex>(0, std::move(p0));
			auto vtx1 = std::make_shared<TModel_Vertex>(0, std::move(p1));

			auto curveOnSurface = std::make_shared<TModel_Curve>(Curve);
			auto edge = std::make_shared<TModel_SegmentEdge>(vtx0, vtx1, curveOnSurface, curveOnPlane);
			Debug_Null_Pointer(edge);

			auto [tri, params] = Cad_Tools::RetrievePolygonOnTriangulation(Shape(), Face());
			edge->SetMesh(std::move(tri));
			edge->SetParaMesh(std::move(params));

			newEdge = std::move(edge);
		}
	}
	else
	{ // the curve is deGenerated [1/7/2022 Amir]
		/*auto pt2d = curveOnPlane->Value(MEAN(curveOnPlane->FirstParameter(), curveOnPlane->LastParameter()));
		auto pm = patch->Value(pt2d.X(), pt2d.Y());
		auto vtx = std::make_shared<TModel_Vertex>(0, std::move(pm));*/

		newEdge = std::make_shared<TModel_SingularEdge>(curveOnPlane);
	}

	theEdge_ = std::move(newEdge);

	Change_IsDone() = Standard_True;
}