#pragma once
#include <Geo_Tools.hxx>
#include <Pln_Tools.hxx>
#include <Entity_Line.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2d_Curve.hxx>
template<class WireType>
inline Standard_Real 
tnbLib::Cad_RepairPlnWire<WireType>::GetParameter
(
	const std::shared_ptr<paraCurveType>& theCurve,
	const CurvePoint thePoint
)
{
	Standard_Real u = 0;
	if (thePoint IS_EQUAL CurvePoint::end)
	{
		u = theCurve->LastParameter();
	}
	else if (thePoint IS_EQUAL CurvePoint::start)
	{
		u = theCurve->FirstParameter();
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of point has been detected!" << endl
			<< abort(FatalError);
	}
	return u;
}

template<class WireType>
inline std::pair<tnbLib::Pnt2d, tnbLib::Vec2d> 
tnbLib::Cad_RepairPlnWire<WireType>::CalcTangent
(
	const std::shared_ptr<paraCurveType>& theCurve,
	const CurvePoint thePoint
)
{
	Pnt2d pt;
	Vec2d vec;

	Debug_Null_Pointer(theCurve);

	const auto& geom = theCurve->Geometry();
	Debug_Null_Pointer(geom);

	geom->D1(GetParameter(theCurve, thePoint), pt, vec);
	auto t = std::make_pair(std::move(pt), std::move(vec));
	return std::move(t);
}

template<class WireType>
inline tnbLib::Pnt2d 
tnbLib::Cad_RepairPlnWire<WireType>::CalcIntersectionPoint
(
	const Pnt2d & thePoint0, 
	const Vec2d & theTang0,
	const Pnt2d & thePoint1,
	const Vec2d & theTang1
)
{
	const auto p0 = thePoint0;
	const auto p1 = thePoint1;
	const Dir2d d0 = theTang0;
	const Dir2d d1 = theTang1;

	const auto angle = std::abs(d0.Angle(d1));
	if (angle <= 0.05*PI OR angle >= 0.95*PI)
	{
		auto pm = MEAN(p0, p1);
		return std::move(pm);
	}

	Entity2d_Line line0(std::move(p0), std::move(d0));
	Entity2d_Line line1(std::move(p1), std::move(d1));

	auto entity = Geo_Tools::Intersection_cgal(line0, line1);
	if (NOT entity->IsPoint())
	{
		auto pm = MEAN(p0, p1);
		return std::move(pm);
		/*FatalErrorIn(FunctionSIG)
			<< "invalid type of geometry has been detected!" << endl
			<< " - P0 : " << p0 << endl
			<< " - P1 : " << p1 << endl
			<< " - t0 : " << d0 << endl
			<< " - t1 : " << d1 << endl
			<< abort(FatalError);*/
	}
	auto ptEnt = std::dynamic_pointer_cast<Geo_Tools::PointIntersectEntity2d>(entity);
	Debug_Null_Pointer(ptEnt);

	auto& pt = ptEnt->IntPnt;
	return std::move(pt);
}

template<class WireType>
inline void tnbLib::Cad_RepairPlnWire<WireType>::CheckTolerance
(
	const Pnt2d & theCentre, 
	const Pnt2d & thePt,
	const Standard_Real theTol
)
{
	if (theCentre.Distance(thePt) >= theTol)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid wire under the tolerance has been detected." << endl
			<< " - tolerance: " << theTol << endl
			<< abort(FatalError);
	}
}

template<class WireType>
inline std::pair<tnbLib::Pnt2d, Standard_Real> 
tnbLib::Cad_RepairPlnWire<WireType>::ProjectPoint
(
	const Pnt2d & theCoord,
	const std::shared_ptr<paraCurveType>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	Geom2dAPI_ProjectPointOnCurve alg(theCoord, theCurve->Geometry());

	if (NOT alg.NbPoints())
	{
		throw Cad_RepairPlnWire_Base::zeroIntPointObj;
	}

	Pnt2d pt = alg.NearestPoint();
	auto u = alg.LowerDistanceParameter();
	if (u < theCurve->FirstParameter())
	{
		u = theCurve->FirstParameter();
		pt = theCurve->Value(u);
	}
	if (u > theCurve->LastParameter())
	{
		u = theCurve->LastParameter();
		pt = theCurve->Value(u);
	}
	auto t = std::make_pair(std::move(pt), u);
	return std::move(t);
}

template<class WireType>
inline std::pair
<
	std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::paraCurveType>,
	Standard_Boolean
>
tnbLib::Cad_RepairPlnWire<WireType>::SplitFirstPart
(
	const Pnt2d & theCoord, 
	const std::shared_ptr<paraCurveType>& theCurve
)
{
	const auto[ppt, u] = ProjectPoint(theCoord, theCurve);
	if (std::abs(u - theCurve->FirstParameter()) <= gp::Resolution())
	{
		auto t = std::make_pair(theCurve, Standard_False);
		return std::move(t);
	}
#ifdef _DEBUG
	if (NOT INSIDE(u, theCurve->FirstParameter(), theCurve->LastParameter()))
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter is outside of the span." << endl
			<< " - x: " << u << endl
			<< " - first parameter: " << theCurve->FirstParameter() << endl
			<< " - last parameter: " << theCurve->LastParameter() << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	Handle(Geom2d_Curve) c0, c1;
	Pln_Tools::SplitCurve(theCurve->Geometry(), u, c0, c1);
	Debug_Null_Pointer(c1);

	auto c = std::make_shared<paraCurveType>(theCurve->Index(), theCurve->Name(), std::move(c1));
	auto t = std::make_pair(std::move(c), Standard_True);
	return std::move(t);
}

template<class WireType>
inline std::pair
<
	std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::paraCurveType>,
	Standard_Boolean
>
tnbLib::Cad_RepairPlnWire<WireType>::SplitLastPart
(
	const Pnt2d & theCoord, 
	const std::shared_ptr<paraCurveType>& theCurve
)
{
	const auto[ppt, u] = ProjectPoint(theCoord, theCurve);
	if (std::abs(u - theCurve->LastParameter()) <= gp::Resolution())
	{
		auto t = std::make_pair(theCurve, Standard_False);
		return std::move(t);
	}
#ifdef _DEBUG
	if (NOT INSIDE(u, theCurve->FirstParameter(), theCurve->LastParameter()))
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter is outside of the span." << endl
			<< " - x: " << u << endl
			<< " - first parameter: " << theCurve->FirstParameter() << endl
			<< " - last parameter: " << theCurve->LastParameter() << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	Handle(Geom2d_Curve) c0, c1;
	Pln_Tools::SplitCurve(theCurve->Geometry(), u, c0, c1);
	Debug_Null_Pointer(c0);

	auto c = std::make_shared<paraCurveType>(theCurve->Index(), theCurve->Name(), std::move(c0));
	auto t = std::make_pair(std::move(c), Standard_True);
	return std::move(t);
}

template<class WireType>
inline std::pair<std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::paraCurveType>, Standard_Boolean>
tnbLib::Cad_RepairPlnWire<WireType>::SplitCurve
(
	const Pnt2d & theCoord, 
	const std::shared_ptr<paraCurveType>& theCurve, 
	const CurvePoint thePt
)
{
	if (thePt IS_EQUAL CurvePoint::start)
	{
		auto t = SplitFirstPart(theCoord, theCurve);
		return std::move(t);
	}
	else if (thePt IS_EQUAL CurvePoint::end)
	{
		auto t = SplitLastPart(theCoord, theCurve);
		return std::move(t);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unspecified type of point has been detected!" << endl
			<< abort(FatalError);
	}
	std::shared_ptr<paraCurveType> c;
	auto t = std::make_pair(std::move(c), Standard_True);
	return std::move(t);
}

template<class WireType>
inline tnbLib::Pnt2d 
tnbLib::Cad_RepairPlnWire<WireType>::CalcCornerPoint
(
	const std::shared_ptr<paraCurveType>& theCurve0, 
	const std::shared_ptr<paraCurveType>& theCurve1
)
{
	const auto[P0, t0] = CalcTangent(theCurve0, CurvePoint::end);
	const auto[P1, t1] = CalcTangent(theCurve1, CurvePoint::start);
	auto coord = CalcIntersectionPoint(P0, t0, P1, t1);
	return std::move(coord);
}

template<class WireType>
inline std::pair
<
	std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::paraCurveType>,
	std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::paraCurveType>
>
tnbLib::Cad_RepairPlnWire<WireType>::TrimCornerCurves
(
	const std::shared_ptr<paraCurveType>& theCurve0,
	const std::shared_ptr<paraCurveType>& theCurve1
)
{
	auto t = std::make_pair(theCurve0, theCurve1);
	return std::move(t);

	try
	{
		const auto coord = CalcCornerPoint(theCurve0, theCurve1);

		auto[c0, trimmed0] = SplitCurve(coord, theCurve0, CurvePoint::end);
		auto[c1, trimmed1] = SplitCurve(coord, theCurve1, CurvePoint::start);
		auto t = std::make_pair(std::move(c0), std::move(c1));
		return std::move(t);
	}
	catch (const zeroIntPoint&)
	{
		auto t = std::make_pair(theCurve0, theCurve1);
		return std::move(t);
	}
}

template<class WireType>
inline Standard_Integer 
tnbLib::Cad_RepairPlnWire<WireType>::MaxIndex
(
	const std::vector<std::shared_ptr<paraCurveType>>& theCurves
)
{
	auto iter = theCurves.begin();
	auto maxIndex = (*iter)->Index();
	iter++;
	while (iter NOT_EQUAL theCurves.end())
	{
		auto id = (*iter)->Index();
		if (id > maxIndex)
		{
			maxIndex = id;
		}
		iter++;
	}
	return maxIndex;
}

template<class WireType>
inline void tnbLib::Cad_RepairPlnWire<WireType>::CheckDuplicateIndex
(
	const std::vector<std::shared_ptr<paraCurveType>>& theCurves
)
{
	const auto maxIndex = MaxIndex(theCurves);
	std::vector<Standard_Integer> curves(maxIndex + 1, 0);
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);
		if (curves.at(x->Index()))
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate index has been detected!" << endl
				<< abort(FatalError);
		}
		curves.at(x->Index()) = 1;
	}
}

template<class WireType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::paraCurveType>>
tnbLib::Cad_RepairPlnWire<WireType>::TrimCurves
(
	const std::vector<std::shared_ptr<paraCurveType>>& theCurves
)
{
	if (theCurves.size() < 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "not enough number of curves has been detected!" << endl
			<< abort(FatalError);
	}
	const auto maxIndex = MaxIndex(theCurves);
	std::vector<std::shared_ptr<paraCurveType>> curves(maxIndex + 1);
	for (const auto& x : theCurves)
	{
		curves.at(x->Index()) = x;
	}

	const auto& c0 = theCurves.at(theCurves.size() - 1);
	const auto& c1 = theCurves.at(0);

	Debug_Null_Pointer(c0);
	Debug_Null_Pointer(c1);

	auto[sub0, sub1] = TrimCornerCurves(c0, c1);
	Debug_Null_Pointer(sub0);
	Debug_Null_Pointer(sub1);

	curves.at(sub0->Index()) = std::move(sub0);
	curves.at(sub1->Index()) = std::move(sub1);

	for (size_t i = 1; i < theCurves.size(); i++)
	{
		const auto& c0 = curves.at(theCurves.at(i - 1)->Index());
		const auto& c1 = curves.at(theCurves.at(i)->Index());

		Debug_Null_Pointer(c0);
		Debug_Null_Pointer(c1);

		auto curve0 = c0;
		if (curves.at(c0->Index()))
		{
			curve0 = curves.at(c0->Index());
		}

		auto curve1 = c1;
		if (curves.at(c1->Index()))
		{
			curve1 = curves.at(c1->Index());
		}

		auto[sub0, sub1] = TrimCornerCurves(curve0, curve1);
		Debug_Null_Pointer(sub0);
		Debug_Null_Pointer(sub1);

		curves.at(sub0->Index()) = std::move(sub0);
		curves.at(sub1->Index()) = std::move(sub1);
	}

	std::vector<std::shared_ptr<paraCurveType>> trimmed;
	trimmed.reserve(theCurves.size());
	for (const auto& x : curves)
	{
		if (x)
		{
			trimmed.push_back(x);
		}
	}
	return std::move(trimmed);
}

template<class WireType>
inline std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::SegmentNode>
tnbLib::Cad_RepairPlnWire<WireType>::CreateNode
(
	const std::shared_ptr<paraCurveType>& theCurve0,
	const std::shared_ptr<paraCurveType>& theCurve1,
	const Standard_Real theTol
)
{
	const auto P0 = theCurve0->LastCoord();
	const auto P1 = theCurve1->FirstCoord();

	const auto coord = MEAN(P0, P1);

	auto node = std::make_shared<SegmentNode>(0, std::move(coord));
	return std::move(node);
}

template<class WireType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::Link>>
tnbLib::Cad_RepairPlnWire<WireType>::CreateWire
(
	const std::shared_ptr<paraCurveType>& theCurve,
	const Standard_Real theTol
)
{
	Debug_Null_Pointer(theCurve);
	std::vector<std::shared_ptr<Link>> links;
	auto P0 = theCurve->FirstCoord();
	auto P1 = theCurve->LastCoord();
	auto Pm = MEAN(P0, P1);

	//CheckTolerance(Pm, P0, theTol);
	auto node = std::make_shared<RingNode>(1, std::move(Pm));

	auto curve = theCurve;
	auto edge = std::make_shared<Ring>(1, std::move(curve), node);

	if (Pm.Distance(P0) <= theTol)
	{
		node->SetRing(edge);
	}
	links.push_back(std::move(edge));
	return std::move(links);
}

template<class WireType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::Link>>
tnbLib::Cad_RepairPlnWire<WireType>::CreateWire
(
	const std::vector<std::shared_ptr<paraCurveType>>& theCurves,
	const Standard_Real theTol
)
{
	std::vector<std::shared_ptr<SegmentNode>> nodes;
	nodes.reserve(theCurves.size());
	{
		const auto& curve0 = theCurves.at(theCurves.size() - 1);
		const auto& curve1 = theCurves.at(0);

		Debug_Null_Pointer(curve0);
		Debug_Null_Pointer(curve1);

		auto node = CreateNode(curve0, curve1, theTol);
		Debug_Null_Pointer(node);
		node->SetIndex(1);

		nodes.push_back(std::move(node));
	}

	for (size_t i = 1; i < theCurves.size(); i++)
	{
		const auto& curve0 = theCurves.at(i - 1);
		const auto& curve1 = theCurves.at(i);

		Debug_Null_Pointer(curve0);
		Debug_Null_Pointer(curve1);

		auto node = CreateNode(curve0, curve1, theTol);
		Debug_Null_Pointer(node);
		node->SetIndex((Standard_Integer)i + 1);

		nodes.push_back(std::move(node));
	}

	std::vector<std::shared_ptr<Link>> links;
	links.reserve(theCurves.size());
	Standard_Integer k = 1;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		const auto& node0 = nodes.at(k - 1);
		const auto& node1 = nodes.at(k % (Standard_Integer)theCurves.size());
		Debug_Null_Pointer(node0);
		Debug_Null_Pointer(node1);

		auto edge = std::make_shared<Segment>(k, x, node0, node1);
		Debug_Null_Pointer(edge);

		auto v0 = x->FirstCoord();
		auto v1 = x->LastCoord();

		if (v0.Distance(node0->Coord()) <= theTol)
		{
			node0->SetForward(edge);
		}

		if (v1.Distance(node1->Coord()) <= theTol)
		{
			node1->SetBackward(edge);
		}
		links.push_back(std::move(edge));
		k++;
	}
	return std::move(links);
}

template<class WireType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_RepairPlnWire<WireType>::Link>>
tnbLib::Cad_RepairPlnWire<WireType>::CreateWire
(
	const std::shared_ptr<WireType>& theWire,
	const Standard_Real theTol
)
{
	Debug_Null_Pointer(theWire);
	if (theWire->Curves().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< " the edge list is empty" << endl
			<< abort(FatalError);
	}
	const auto& curves = theWire->Curves();
	if (curves.size() IS_EQUAL 1)
	{
		auto links = CreateWire(curves.at(0), theTol);
		return std::move(links);
	}
	else
	{
		auto links = CreateWire(curves, theTol);
		return std::move(links);
	}
}

template<class WireType>
inline void tnbLib::Cad_RepairPlnWire<WireType>::CheckWire
(
	const std::vector<std::shared_ptr<Link>>& theLinks
)
{
	if (theLinks.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid wire has been detected!" << endl
			<< abort(FatalError);
	}
	if (theLinks.size() IS_EQUAL 1)
	{
		auto ring = std::dynamic_pointer_cast<Ring>(theLinks.at(0));
		Debug_Null_Pointer(ring);
		auto node = std::dynamic_pointer_cast<RingNode>(ring->GetNode());
		Debug_Null_Pointer(node);
		if (NOT node->GetRing().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "not-manifold type of wire is detected!" << endl
				<< abort(FatalError);
		}
	}
	else
	{
		for (const auto& x : theLinks)
		{
			Debug_Null_Pointer(x);
			auto seg = std::dynamic_pointer_cast<Segment>(x);
			Debug_Null_Pointer(seg);

			auto node0 = std::dynamic_pointer_cast<SegmentNode>(seg->Node0());
			Debug_Null_Pointer(node0);

			if (NOT node0->IsManifold())
			{
				FatalErrorIn(FunctionSIG)
					<< "not-manifold type of wire is detected!" << endl
					<< abort(FatalError);
			}
		}
	}
}

template<class WireType>
inline void tnbLib::Cad_RepairPlnWire<WireType>::CheckWire
(
	const std::shared_ptr<WireType>& theWire, 
	const Standard_Real tol
)
{
	//std::cout << "checking wire...." << std::endl;
	const auto& curves = theWire->Curves();
	for (size_t i = 1; i < curves.size(); i++)
	{
		const auto& c0 = curves.at(i - 1);
		const auto& c1 = curves.at(i);

		if (c0->LastCoord().Distance(c1->FirstCoord()) > tol)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid wire has been detected!" << endl
				<< "- tol: " << tol << endl
				<< abort(FatalError);
		}
	}

	const auto& c0 = curves.at(curves.size() - 1);
	const auto& c1 = curves.at(0);

	if (c0->LastCoord().Distance(c1->FirstCoord()) > tol)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid wire has been detected!" << endl
			<< "- tol: " << tol << endl
			<< abort(FatalError);
	}
}

template<class WireType>
inline std::shared_ptr<WireType> 
tnbLib::Cad_RepairPlnWire<WireType>::CreateWire
(
	const std::vector<std::shared_ptr<Link>>& theLinks
)
{
	std::vector<std::shared_ptr<paraCurveType>> curves;
	curves.reserve(theLinks.size());
	for (const auto& x : theLinks)
	{
		Debug_Null_Pointer(x);
		curves.push_back(x->GetCurve());
	}
	auto curvesPtr = std::make_shared<std::vector<std::shared_ptr<paraCurveType>>>(std::move(curves));
	auto wire = std::make_shared<WireType>(std::move(curvesPtr));
	return std::move(wire);
}

