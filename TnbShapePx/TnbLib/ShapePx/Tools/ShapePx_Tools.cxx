#include <ShapePx_Tools.hxx>

#include <SectPx_Par.hxx>
#include <SectPx_Tools.hxx>
#include <ShapePx_CtrlNet.hxx>
#include <ShapePx_TopoCtrlNet.hxx>
#include <ShapePx_TopoSection.hxx>
#include <ShapePx_TopoSectSegment.hxx>
#include <ShapePx_TopoSectPoles.hxx>
#include <SectPx_WeightController.hxx>
#include <SectPx_SegmentController.hxx>
#include <SectPx_CPtsMap.hxx>
#include <SectPx_Poles.hxx>
#include <Pnt3d.hxx>
#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_BSplineSurface.hxx>

TColgp_Array2OfPnt 
tnbLib::ShapePx_Tools::ControlNet
(
	const ShapePx_CtrlNet & theNet
)
{
	TColgp_Array2OfPnt pnts(1, theNet.NbRows(), 1, theNet.NbColumns());
	Standard_Integer i = 0;
	for (const auto& x : theNet.Rows())
	{
		i++;
		Standard_Integer j = 0;
		auto xi = x.X();
		for (const auto& p : x.Pnts())
		{
			j++;
			auto pt3 = Pnt3d(xi, p.first.X(), p.first.Y());
			pnts.SetValue(i, j, pt3);
		}
	}
	return std::move(pnts);
}

TColStd_Array2OfReal 
tnbLib::ShapePx_Tools::Weights
(
	const ShapePx_CtrlNet & theNet
)
{
	TColStd_Array2OfReal ws(1, theNet.NbRows(), 1, theNet.NbColumns());
	Standard_Integer i = 0;
	for (const auto& x : theNet.Rows())
	{
		i++;
		Standard_Integer j = 0;
		for (const auto& p : x.Pnts())
		{
			j++;
			ws.SetValue(i, j, p.second);
		}
	}
	return std::move(ws);
}

std::shared_ptr<tnbLib::ShapePx_CtrlNet> 
tnbLib::ShapePx_Tools::CreateControlNet(const ShapePx_TopoCtrlNet & theNet)
{
	auto net = std::make_shared<ShapePx_CtrlNet>();
	Debug_Null_Pointer(net);

	const auto& sections = theNet.Sections();
	for (const auto& x : sections)
	{
		Debug_Null_Pointer(x);	
		auto poles = RetrievePoles(x->Segments());
		auto[Qs, Ws] = RetrievePoles(poles);
		
		auto Qw = ShapePx_Tools::CtrlRow(Qs, Ws);

		ShapePx_CtrlRow row(std::move(Qw), x->X());
		net->RowsRef().push_back(std::move(row));
	}

	net->KnotsRef() = theNet.Knots();
	net->SetRowDegree(theNet.RowDegree());
	return std::move(net);
}

std::vector<std::pair<tnbLib::Pnt2d, Standard_Real>>
tnbLib::ShapePx_Tools::CtrlRow
(
	const std::vector<Pnt2d>& theQ, 
	const std::vector<Standard_Real>& theWeights
)
{
	if (theQ.size() NOT_EQUAL theWeights.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "the pole list and weight list must be the same size" << endl
			<< abort(FatalError);
	}

	std::vector<std::pair<Pnt2d, Standard_Real>> paired;
	paired.reserve(theQ.size());
	for (size_t i = 0; i < theQ.size(); i++)
	{
		auto p = std::make_pair(theQ[i], theWeights[i]);
		paired.push_back(std::move(p));
	}
	return std::move(paired);
}

//namespace tnbLib
//{
//
//	auto RetrieveTopoSegments(const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments)
//	{
//		Debug_Null_Pointer(FirstItem(theSegments));
//		Debug_Null_Pointer(FirstItem(theSegments)->Pole0());
//		auto firstPole = std::make_shared<shapePxLib::TopoSectPole_Bnd>(FirstItem(theSegments)->Pole0()->Coord(), 1.0);
//
//		std::vector<std::shared_ptr<ShapePx_TopoSectPole>> poles;
//		poles.push_back(std::move(firstPole));
//
//		for (const auto& x : theSegments)
//		{
//			Debug_Null_Pointer(x);
//
//			std::vector<std::shared_ptr<ShapePx_TopoSectPole>> contrPoles;
//			if (x->HasController())
//			{
//				auto controller = x->Controller().lock();
//				Debug_Null_Pointer(controller);
//
//				const auto& cpts = controller->CPts();
//				Debug_Null_Pointer(cpts);
//
//				auto pts = cpts->Pts();
//				for (auto& p : pts)
//				{
//					auto Q = std::make_shared<shapePxLib::TopoSect_OnSegment>(std::move(p), 1.0);
//					contrPoles.push_back(std::move(Q));
//				}
//			}
//
//			for (auto& p : contrPoles)
//			{
//				poles.push_back(std::move(p));
//			}
//
//			Debug_Null_Pointer(x->Pole1());
//			if (auto innerPole = std::dynamic_pointer_cast<SectPx_InterPole>(x->Pole1()))
//			{
//				if (innerPole->IsCorner())
//				{
//					auto corner = std::dynamic_pointer_cast<sectPxLib::Pole_Corner>(innerPole);
//					Debug_Null_Pointer(corner);
//
//					Standard_Real w = 1.0;
//					if (corner->HasController())
//					{
//						for (const auto& ctrl : corner->Controllers())
//						{
//							auto c = std::dynamic_pointer_cast<sectPxLib::WeightController>(ctrl.second.lock());
//							if (c)
//							{
//								Debug_Null_Pointer(c->Weight().lock());
//								w = c->Weight().lock()->Value();
//							}
//						}
//					}
//					auto Q = std::make_shared<shapePxLib::TopoSect_Corner>(x->Pole1()->Coord(), w);
//					poles.push_back(std::move(Q));
//				}
//				else if (innerPole->IsSlider())
//				{
//					auto Q = std::make_shared<shapePxLib::TopoSect_Slider>(x->Pole1()->Coord(), 1.0);
//					poles.push_back(std::move(Q));
//				}
//				else
//				{
//					FatalErrorIn(FunctionSIG)
//						<< "unrecognized type of pole has been detected!" << endl
//						<< abort(FatalError);
//				}
//			}
//			else if (auto bndPole = std::dynamic_pointer_cast<SectPx_BndPole>(x->Pole1()))
//			{
//				auto Q = std::make_shared<shapePxLib::TopoSectPole_Bnd>(x->Pole1()->Coord(), 1.0);
//				poles.push_back(std::move(Q));
//			}
//			else
//			{
//				FatalErrorIn(FunctionSIG)
//					<< "invalid pole has been detected!" << endl
//					<< abort(FatalError);
//			}
//		}
//
//		std::vector<std::shared_ptr<ShapePx_TopoSectSegment>> segments;
//		segments.reserve(poles.size() - 1);
//		for (size_t i = 1; i < poles.size(); i++)
//		{
//			const auto& pole0 = poles[i - 1];
//			const auto& pole1 = poles[i];
//
//			auto seg = std::make_shared<ShapePx_TopoSectSegment>(pole0, pole1);
//			segments.push_back(std::move(seg));
//		}
//		return std::move(segments);
//	}
//}

std::shared_ptr<tnbLib::ShapePx_TopoSection> 
tnbLib::ShapePx_Tools::MakeTopoSection
(
	const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments,
	const Standard_Real x
)
{
	auto poles = CreateTopoControlPoints(theSegments);
	auto segments = CreateTopoSegments(poles);
	auto section = std::make_shared<ShapePx_TopoSection>(std::move(segments), x);
	return std::move(section);
}

std::shared_ptr<tnbLib::ShapePx_TopoSection> 
tnbLib::ShapePx_Tools::MakeTopoSection
(
	const std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>& theSegments,
	const Standard_Real x
)
{
	auto section = std::make_shared<ShapePx_TopoSection>(theSegments, x);
	return std::move(section);
}

std::shared_ptr<tnbLib::ShapePx_TopoSection> 
tnbLib::ShapePx_Tools::MakeTopoSection
(
	std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>&& theSegments,
	const Standard_Real x
)
{
	auto section = std::make_shared<ShapePx_TopoSection>(std::move(theSegments), x);
	return std::move(section);
}

std::vector<std::shared_ptr<tnbLib::ShapePx_TopoSectPole>> 
tnbLib::ShapePx_Tools::CreateTopoControlPoints
(
	const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
)
{
	Debug_Null_Pointer(FirstItem(theSegments));
	Debug_Null_Pointer(FirstItem(theSegments)->Pole0());
	auto firstPole = std::make_shared<shapePxLib::TopoSectPole_Bnd>(FirstItem(theSegments)->Pole0()->Coord(), 1.0);

	std::vector<std::shared_ptr<ShapePx_TopoSectPole>> poles;
	poles.push_back(std::move(firstPole));

	for (const auto& x : theSegments)
	{
		Debug_Null_Pointer(x);

		std::vector<std::shared_ptr<ShapePx_TopoSectPole>> contrPoles;
		if (x->HasController())
		{
			auto controller = x->Controller().lock();
			Debug_Null_Pointer(controller);

			const auto& cpts = controller->CPts();
			Debug_Null_Pointer(cpts);

			auto pts = cpts->Pts();
			for (auto& p : pts)
			{
				auto Q = std::make_shared<shapePxLib::TopoSect_OnSegment>(std::move(p), 1.0);
				contrPoles.push_back(std::move(Q));
			}
		}

		for (auto& p : contrPoles)
		{
			poles.push_back(std::move(p));
		}

		Debug_Null_Pointer(x->Pole1());
		if (auto innerPole = std::dynamic_pointer_cast<SectPx_InterPole>(x->Pole1()))
		{
			if (innerPole->IsCorner())
			{
				auto corner = std::dynamic_pointer_cast<sectPxLib::Pole_Corner>(innerPole);
				Debug_Null_Pointer(corner);

				Standard_Real w = 1.0;
				if (corner->HasController())
				{
					for (const auto& ctrl : corner->Controllers())
					{
						auto c = std::dynamic_pointer_cast<sectPxLib::WeightController>(ctrl.second.lock());
						if (c)
						{
							Debug_Null_Pointer(c->Weight().lock());
							w = c->Weight().lock()->Value();
						}
					}
				}
				auto Q = std::make_shared<shapePxLib::TopoSect_Corner>(x->Pole1()->Coord(), w);
				poles.push_back(std::move(Q));
			}
			else if (innerPole->IsSlider())
			{
				auto Q = std::make_shared<shapePxLib::TopoSect_Slider>(x->Pole1()->Coord(), 1.0);
				poles.push_back(std::move(Q));
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unrecognized type of pole has been detected!" << endl
					<< abort(FatalError);
			}
		}
		else if (auto bndPole = std::dynamic_pointer_cast<SectPx_BndPole>(x->Pole1()))
		{
			auto Q = std::make_shared<shapePxLib::TopoSectPole_Bnd>(x->Pole1()->Coord(), 1.0);
			poles.push_back(std::move(Q));
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid pole has been detected!" << endl
				<< abort(FatalError);
		}
	}
	return std::move(poles);
}

std::vector<std::shared_ptr<tnbLib::ShapePx_TopoSectSegment>> 
tnbLib::ShapePx_Tools::CreateTopoSegments
(
	const std::vector<std::shared_ptr<ShapePx_TopoSectPole>>& thePoles
)
{
	std::vector<std::shared_ptr<ShapePx_TopoSectSegment>> segments;
	segments.reserve(thePoles.size() - 1);
	for (size_t i = 1; i < thePoles.size(); i++)
	{
		const auto& pole0 = thePoles[i - 1];
		const auto& pole1 = thePoles[i];

		auto seg = std::make_shared<ShapePx_TopoSectSegment>(pole0, pole1);

		if (auto inner = std::dynamic_pointer_cast<shapePxLib::TopoSectPole_Inter>(pole0))
		{
			inner->SetForwardSegment(seg);
		}
		else if (auto bnd = std::dynamic_pointer_cast<shapePxLib::TopoSectPole_Bnd>(pole0))
		{
			bnd->SetSegment(seg);
		}

		if (auto inner = std::dynamic_pointer_cast<shapePxLib::TopoSectPole_Inter>(pole1))
		{
			inner->SetBackwardSegment(seg);
		}
		else if (auto bnd = std::dynamic_pointer_cast<shapePxLib::TopoSectPole_Bnd>(pole1))
		{
			bnd->SetSegment(seg);
		}

		segments.push_back(std::move(seg));
	}
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::ShapePx_TopoSectPole>> 
tnbLib::ShapePx_Tools::RetrievePoles
(
	const std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>& theSegments
)
{
	std::vector<std::shared_ptr<ShapePx_TopoSectPole>> poles;
	poles.reserve(theSegments.size() + 1);
	for (const auto& x : theSegments)
	{
		poles.push_back(x->Pole0());
	}
	poles.push_back(LastItem(theSegments)->Pole1());
	return std::move(poles);
}

std::pair<std::vector<tnbLib::Pnt2d>, std::vector<Standard_Real>> 
tnbLib::ShapePx_Tools::RetrievePoles
(
	const std::vector<std::shared_ptr<ShapePx_TopoSectPole>>& thePoles
)
{
	std::vector<Pnt2d> Qs;
	std::vector<Standard_Real> Ws;

	Qs.reserve(thePoles.size());
	Ws.reserve(thePoles.size());
	for (const auto& x : thePoles)
	{
		Debug_Null_Pointer(x);
		Qs.push_back(x->Coord());
		Ws.push_back(x->Weight());
	}
	auto t = std::make_pair(std::move(Qs), std::move(Ws));
	return std::move(t);
}

Handle(Geom_Surface) 
tnbLib::ShapePx_Tools::Surface
(
	const ShapePx_CtrlNet & theNet,
	const Standard_Integer vDegree
)
{
	auto poles = ControlNet(theNet);
	auto weights = Weights(theNet);

	auto[vknots, vMults] = SectPx_Tools::Knots(theNet.Knots());
	auto[uknots, uMults] = SectPx_Tools::Knots(SectPx_Tools::Knots(theNet.NbRows(), vDegree, 0, 1));

	try
	{
		Handle(Geom_Surface) surface = new Geom_BSplineSurface(poles, weights, uknots, vknots, uMults, vMults, vDegree, theNet.RowDegree());
		return std::move(surface);
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< "opencascade error message has been detected: Unable to create geometric surface" << endl
			<< abort(FatalError);
		return nullptr;
	}
}