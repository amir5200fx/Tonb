#include <ShapePx_ConicSection.hxx>

#include <ShapePx_TopoSection.hxx>
#include <ShapePx_TopoSectSegment.hxx>
#include <ShapePx_TopoSectPoles.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{


	static Standard_Real coeffW1, coeffW3;

	auto CalcNbCorners(const std::vector<std::shared_ptr<ShapePx_TopoSectPole>>& poles)
	{
		Standard_Integer k = 0;
		for (const auto& x : poles)
		{
			if (std::dynamic_pointer_cast<shapePxLib::TopoSect_Corner>(x))
			{
				k++;
			}
		}
		return k;
	}

	auto CalcNbBackwardInnerPoles(const std::shared_ptr<shapePxLib::TopoSect_Corner>& corner)
	{
		Standard_Integer k = 0;
		auto x = ShapePx_ConicSection::PreviousPole(corner);
		while (x->IsInterior())
		{
			x = ShapePx_ConicSection::PreviousPole(x);
			++k;
		}
		return k;
	}

	auto CalcNbForwardInnerPoles(const std::shared_ptr<shapePxLib::TopoSect_Corner>& corner)
	{
		Standard_Integer k = 0;
		auto x = ShapePx_ConicSection::NextPole(corner);
		while (x->IsInterior())
		{
			x = ShapePx_ConicSection::NextPole(x);
			++k;
		}
		return k;
	}

	auto RetrieveBackwardInnerPoles(const std::shared_ptr<shapePxLib::TopoSect_Corner>& corner)
	{
		std::vector<std::shared_ptr<ShapePx_TopoSectPole>> poles;
		auto x = ShapePx_ConicSection::PreviousPole(corner);
		while (x->IsInterior())
		{
			poles.push_back(x);
			x = ShapePx_ConicSection::PreviousPole(x);
		}
		return std::move(poles);
	}

	auto RetrieveForwardInnerPoles(const std::shared_ptr<shapePxLib::TopoSect_Corner>& corner)
	{
		std::vector<std::shared_ptr<ShapePx_TopoSectPole>> poles;
		auto x = ShapePx_ConicSection::NextPole(corner);
		while (x->IsInterior())
		{
			poles.push_back(x);
			x = ShapePx_ConicSection::NextPole(x);
		}
		return std::move(poles);
	}

	auto IdentSectionType(const ShapePx_TopoSection& section)
	{
		auto poles = ShapePx_ConicSection::RetrievePoles(section);
		if (CalcNbCorners(poles) NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "the section has no corner" << endl
				<< abort(FatalError);
		}
		auto corner = ShapePx_ConicSection::RetrieveCorner(poles);
		Debug_Null_Pointer(corner);

		auto nbBwd = CalcNbBackwardInnerPoles(corner);
		auto nbFwd = CalcNbForwardInnerPoles(corner);

		if (nbBwd IS_EQUAL 0 AND nbBwd IS_EQUAL 0)
		{
			return ShapePx_ConicSection::sectType::quadratic;
		}
		else if (nbBwd IS_EQUAL 1 AND nbFwd IS_EQUAL 1)
		{
			return ShapePx_ConicSection::sectType::quartic;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid type of section to create a conic section has been detected!" << endl
				<< abort(FatalError);
		}
		return ShapePx_ConicSection::sectType::quartic;
	}

	auto RetrieveBoundaryPoles(const ShapePx_TopoSection& section)
	{
		const auto& segments = section.Segments();
		auto t = std::make_pair(FirstItem(segments)->Pole0(), LastItem(segments)->Pole1());
		return std::move(t);
	}

	auto RetrieveCornerPole(const ShapePx_TopoSection& section)
	{
		auto corner = ShapePx_ConicSection::RetrieveCorner(ShapePx_ConicSection::RetrievePoles(section));
		return std::move(corner);
	}

	auto CalcR0R1R2R3R4(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		auto R1 = MEAN(p0, p1);
		auto R3 = MEAN(p1, p2);

		auto O = MEAN(R1, R3);
		auto R2 = MEAN(p1, O);

		auto t = std::make_tuple(p0, std::move(R1), std::move(R2), std::move(R3), p2);
		return std::move(t);
	}

	auto CalcWeights
	(
		const Pnt2d& R0,
		const Pnt2d& R1, 
		const Pnt2d& R2, 
		const Pnt2d& R3,
		const Pnt2d& R4, 
		const Standard_Real wb
	)
	{
		const auto B1 = std::abs(Geo_Tools::Area_cgal(R0, R1, R4));
		const auto B2 = std::abs(Geo_Tools::Area_cgal(R0, R2, R4));
		const auto B3 = std::abs(Geo_Tools::Area_cgal(R0, R3, R4));

		const auto D0 = std::abs(Geo_Tools::Area_cgal(R1, R3, R4));
		const auto D1 = std::abs(Geo_Tools::Area_cgal(R2, R3, R4));
		const auto D2 = std::abs(Geo_Tools::Area_cgal(R0, R1, R3));

		Standard_Real w0 = 1.0;
		Standard_Real w4 = 1.0;

		const auto H1 = 3.0*B2*B3 / (8.0*B1*D0);
		const auto H2 = 4.0*B3*D0 / (9.0*B2*D1);
		const auto H3 = 3.0*B1*B2 / (8.0*B3*D2);

		const auto II = std::sqrt(H3 / H1);

		coeffW1 = 1.0 / std::sqrt(H2*II);
		coeffW3 = std::sqrt(II / H2);

		auto w1 = coeffW1*wb;
		auto w3 = coeffW3*wb;
		auto w2 = wb;

		auto t = std::make_tuple(w0, w1, w2, w3, w4);
		return std::move(t);
	}

	auto CalcQuadraticQs(const ShapePx_TopoSection& section, const Standard_Real wb)
	{
		const auto[t0, t1, t2] = ShapePx_ConicSection::RetrieveSuperTriangle(section);

		auto Q0 = std::make_pair(t0->Coord(), 1.0);
		auto Q1 = std::make_pair(t1->Coord(), wb);
		auto Q2 = std::make_pair(t2->Coord(), 1.0);

		auto t = std::make_tuple(std::move(Q0), std::move(Q1), std::move(Q2));
		return std::move(t);
	}

	auto CalcQuarticQs(const ShapePx_TopoSection& section, const Standard_Real wb)
	{
		const auto[t0, t1, t2] = ShapePx_ConicSection::RetrieveSuperTriangle(section);

		auto[R0, R1, R2, R3, R4] = CalcR0R1R2R3R4(t0->Coord(), t1->Coord(), t2->Coord());
		auto[w0, w1, w2, w3, w4] = CalcWeights(R0, R1, R2, R3, R4, wb);

		auto Q0 = std::make_pair(std::move(R0), w0);
		auto Q1 = std::make_pair(std::move(R1), w1);
		auto Q2 = std::make_pair(std::move(R2), w2);
		auto Q3 = std::make_pair(std::move(R3), w3);
		auto Q4 = std::make_pair(std::move(R4), w4);

		auto t = std::make_tuple
		(
			std::move(Q0), std::move(Q1), 
			std::move(Q2), std::move(Q3), 
			std::move(Q4)
		);
		return std::move(t);
	}
}

std::shared_ptr<tnbLib::ShapePx_TopoSectPole>
tnbLib::ShapePx_ConicSection::NextPole
(
	const std::shared_ptr<ShapePx_TopoSectPole>& pole
)
{
	Debug_If_Condition_Message(NOT pole->IsInterior(), "the pole is not interior");
	auto inter = std::dynamic_pointer_cast<shapePxLib::TopoSectPole_Inter>(pole);
	Debug_Null_Pointer(inter);

	auto seg = inter->ForwardSegment().lock();
	Debug_Null_Pointer(seg);

	return seg->Pole1();
}

std::shared_ptr<tnbLib::ShapePx_TopoSectPole>
tnbLib::ShapePx_ConicSection::PreviousPole
(
	const std::shared_ptr<ShapePx_TopoSectPole>& pole
)
{
	Debug_If_Condition_Message(NOT pole->IsInterior(), "the pole is not interior");
	auto inter = std::dynamic_pointer_cast<shapePxLib::TopoSectPole_Inter>(pole);
	Debug_Null_Pointer(inter);

	auto seg = inter->BackwardSegment().lock();
	Debug_Null_Pointer(seg);

	return seg->Pole0();
}

std::vector<std::shared_ptr<tnbLib::ShapePx_TopoSectPole>>
tnbLib::ShapePx_ConicSection::RetrievePoles(const ShapePx_TopoSection & section)
{
	const auto& segments = section.Segments();
	std::vector<std::shared_ptr<ShapePx_TopoSectPole>> nodes;
	nodes.reserve(segments.size() + 1);
	for (const auto& x : segments)
	{
		Debug_Null_Pointer(x);
		nodes.push_back(x->Pole0());
	}
	nodes.push_back(LastItem(segments)->Pole1());
	return std::move(nodes);
}

std::shared_ptr<tnbLib::shapePxLib::TopoSect_Corner>
tnbLib::ShapePx_ConicSection::RetrieveCorner
(
	const std::vector<std::shared_ptr<ShapePx_TopoSectPole>>& poles
)
{
	for (const auto& x : poles)
	{
		Debug_Null_Pointer(x);
		if (auto p = std::dynamic_pointer_cast<shapePxLib::TopoSect_Corner>(x))
		{
			return std::move(p);
		}
	}
	FatalErrorIn(FunctionSIG)
		<< "found no corner!" << endl
		<< abort(FatalError);
	std::shared_ptr<shapePxLib::TopoSect_Corner> corner;
	return std::move(corner);
}

std::tuple
<
	std::shared_ptr<tnbLib::ShapePx_TopoSectPole>,
	std::shared_ptr<tnbLib::ShapePx_TopoSectPole>,
	std::shared_ptr<tnbLib::ShapePx_TopoSectPole>
>
tnbLib::ShapePx_ConicSection::RetrieveSuperTriangle
(
	const ShapePx_TopoSection & section
)
{
	auto[P0, P2] = RetrieveBoundaryPoles(section);
	auto P1 = RetrieveCornerPole(section);

	auto t = std::make_tuple(std::move(P0), std::move(P1), std::move(P2));
	return std::move(t);
}

void tnbLib::ShapePx_ConicSection::Perform()
{
	if (NOT Section())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& section = Section();
	auto sectionType = IdentSectionType(*section);
	theType_ = sectionType;

	if (sectionType IS_EQUAL sectType::quadratic)
	{
		auto [q0, q1, q2] = CalcQuadraticQs(*section, BaseWeight());

		auto poles = RetrievePoles(*section);
		
		poles[0]->SetCoord(std::move(q0.first));
		poles[0]->SetWeight(q0.second);

		poles[1]->SetCoord(std::move(q1.first));
		poles[1]->SetWeight(q1.second);

		poles[2]->SetCoord(std::move(q2.first));
		poles[2]->SetWeight(q2.second);

		theWeightCoffs_.resize(3, 1.0);
	}
	else if (sectionType IS_EQUAL sectType::quartic)
	{
		auto[q0, q1, q2, q3, q4] = CalcQuarticQs(*section, BaseWeight());

		auto poles = RetrievePoles(*section);

		poles[0]->SetCoord(std::move(q0.first));
		poles[0]->SetWeight(q0.second);

		poles[1]->SetCoord(std::move(q1.first));
		poles[1]->SetWeight(q1.second);

		poles[2]->SetCoord(std::move(q2.first));
		poles[2]->SetWeight(q2.second);

		poles[3]->SetCoord(std::move(q3.first));
		poles[3]->SetWeight(q3.second);

		poles[4]->SetCoord(std::move(q4.first));
		poles[4]->SetWeight(q4.second);

		theWeightCoffs_.resize(5, 1.0);
		theWeightCoffs_[1] = coeffW1;
		theWeightCoffs_[3] = coeffW3;
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "non recognized type of section has been detected!" << endl
			<< abort(FatalError);
	}

	Change_IsDone() = Standard_True;
}