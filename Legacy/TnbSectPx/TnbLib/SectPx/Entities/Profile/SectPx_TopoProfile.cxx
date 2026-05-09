#include <SectPx_TopoProfile.hxx>

#include <SectPx_Node.hxx>
#include <SectPx_InterfaceMaker.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_Pnt.hxx>
#include <SectPx_KnotVector.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/StdFail_NotDone.hxx>
#include <opencascade/Geom2d_BSplineCurve.hxx>
#include <opencascade/BSplCLib.hxx>

tnbLib::SectPx_TopoProfile::SectPx_TopoProfile
(
	const std::shared_ptr<SectPx_Node>& theNode0, 
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: theNode0_(theNode0)
	, theNode1_(theNode1)
	, SectPx_RegObj(0, "topoProfile")
{
	//- empty body
}

tnbLib::SectPx_TopoProfile::SectPx_TopoProfile
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: theNode0_(theNode0)
	, theNode1_(theNode1)
	, SectPx_RegObj(theIndex, "topoProfile")
{
	//- empty body
}

tnbLib::SectPx_TopoProfile::SectPx_TopoProfile
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: theNode0_(theNode0)
	, theNode1_(theNode1)
	, SectPx_RegObj(theIndex, theName)
{
	//- empty body
}

void tnbLib::SectPx_TopoProfile::SetProfile
(
	const std::shared_ptr<SectPx_Node>& theNode,
	const std::shared_ptr<SectPx_TopoProfile>& theProfile
)
{
	Debug_Null_Pointer(theNode);
	Debug_Null_Pointer(theProfile);
	theNode->SetProfile(theProfile);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::SectPx_TopoProfile::RetrieveCoords() const
{
	Update();

	auto pnts = SectPx_PntTools::TrackPnts(Node0(), Node1());

	std::vector<Pnt2d> coords;
	coords.reserve(pnts.size());
	for (const auto& x : pnts)
	{
		auto coord = x->Coord();
		coords.push_back(std::move(coord));
	}
	return std::move(coords);
}

tnbLib::sectPxLib::regObjType
tnbLib::SectPx_TopoProfile::RegObjType() const
{
	return sectPxLib::regObjType::profile;
}

Standard_Boolean
tnbLib::SectPx_TopoProfile::IsProfile() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_TopoProfile::IsFrameRegObj() const
{
	return Standard_True;
}

//Handle(Geom2d_Curve) 
//tnbLib::SectPx_TopoProfile::RetrieveGeomCurve
//(
//	const Standard_Integer deg
//) const
//{
//	if (NOT Knots())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "there is no algorithm for creating a knot vector" << endl
//			<< abort(FatalError);
//	}
//
//	auto pnts = RetrieveCoords();
//	auto knotVector = Knots()->CreateKnots(pnts, deg);
//	TColStd_Array1OfReal knotsSeq(1, (Standard_Integer)knotVector.size());
//	for (Standard_Integer i = 1; i <= knotVector.size(); i++)
//	{
//		knotsSeq.SetValue(i, knotVector[i - 1]);
//	}
//
//	TColStd_Array1OfReal knots;
//	TColStd_Array1OfInteger mults;
//	BSplCLib::Knots(knotsSeq, knots, mults);
//
//	TColgp_Array1OfPnt2d Poles(1, (Standard_Integer)pnts.size());
//	for (Standard_Integer i = 1; i <= pnts.size(); i++)
//	{
//		Poles.SetValue(i, pnts[i - 1]);
//	}
//
//	try
//	{
//		Handle(Geom2d_BSplineCurve) curve =
//			new Geom2d_BSplineCurve(Poles, knots, mults, deg);
//		return std::move(curve);
//	}
//	catch (const StdFail_NotDone& x)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "unable to create bspline curve: " << endl
//			<< x.GetMessageString() << endl
//			<< abort(FatalError);
//		return nullptr;
//	}
//}
