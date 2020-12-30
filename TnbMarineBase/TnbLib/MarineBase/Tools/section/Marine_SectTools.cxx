#include <Marine_SectTools.hxx>

#include <Entity3d_Box.hxx>
#include <Pln_Wire.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Edge.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_xCmpSection.hxx>
#include <Marine_zCmpSection.hxx>
#include <Marine_Sections.hxx>
#include <Marine_PlnCurves.hxx>
#include <Marine_PlnCurves.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>

#include <TopoDS_Edge.hxx>

void tnbLib::Marine_SectTools::Section
(
	const std::shared_ptr<Pln_Wire>& theWire,
	const marineLib::curveType target,
	const marineLib::curveType to
)
{
	const auto cmpEdge = theWire->CmpEdge();
	switch (to)
	{
	case marineLib::curveType::displacer:
	{
		for (const auto& x : cmpEdge->Edges())
		{
			Debug_Null_Pointer(x);

			const auto& curve = x->Curve();
			auto m = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
			if (NOT m)
			{
				FatalErrorIn(FunctionSIG)
					<< "the section has one non-marine curve, at least" << endl
					<< abort(FatalError);
			}

			if (m->CurveType() IS_EQUAL target)
			{
				const auto curve =
					std::make_shared<Marine_DisplacerCurve>(std::move(*x->Curve()));
				x->SetCurve(curve);
			}
		}
		break;
	}
	case marineLib::curveType::dry:
	{
		for (const auto& x : cmpEdge->Edges())
		{
			Debug_Null_Pointer(x);

			const auto& curve = x->Curve();
			auto m = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
			if (NOT m)
			{
				FatalErrorIn(FunctionSIG)
					<< "the section has one non-marine curve, at least" << endl
					<< abort(FatalError);
			}

			if (m->CurveType() IS_EQUAL target)
			{
				const auto curve =
					std::make_shared<Marine_DryCurve>(std::move(*x->Curve()));
				x->SetCurve(curve);
			}			
		}
		break;
	}
	case marineLib::curveType::sail:
	{
		for (const auto& x : cmpEdge->Edges())
		{
			Debug_Null_Pointer(x);

			const auto& curve = x->Curve();
			auto m = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
			if (NOT m)
			{
				FatalErrorIn(FunctionSIG)
					<< "the section has one non-marine curve, at least" << endl
					<< abort(FatalError);
			}

			if (m->CurveType() IS_EQUAL target)
			{
				const auto curve =
					std::make_shared<Marine_SailCurve>(std::move(*x->Curve()));
				x->SetCurve(curve);
			}		
		}
		break;
	}
	case marineLib::curveType::tank:
	{
		for (const auto& x : cmpEdge->Edges())
		{
			Debug_Null_Pointer(x);

			const auto& curve = x->Curve();
			auto m = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
			if (NOT m)
			{
				FatalErrorIn(FunctionSIG)
					<< "the section has one non-marine curve, at least" << endl
					<< abort(FatalError);
			}

			if (m->CurveType() IS_EQUAL target)
			{
				const auto curve =
					std::make_shared<Marine_TankCurve>(std::move(*x->Curve()));
				x->SetCurve(curve);
			}	
		}
		break;
	}
	case marineLib::curveType::water:
	{
		for (const auto& x : cmpEdge->Edges())
		{
			Debug_Null_Pointer(x);

			const auto& curve = x->Curve();
			auto m = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
			if (NOT m)
			{
				FatalErrorIn(FunctionSIG)
					<< "the section has one non-marine curve, at least" << endl
					<< abort(FatalError);
			}

			if (m->CurveType() IS_EQUAL target)
			{
				const auto curve =
					std::make_shared<Marine_WaterCurve>(std::move(*x->Curve()));
				x->SetCurve(curve);
			}	
		}
		break;
	}
	case marineLib::curveType::waterLine:
	{
		for (const auto& x : cmpEdge->Edges())
		{
			Debug_Null_Pointer(x);

			const auto& curve = x->Curve();
			auto m = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
			if (NOT m)
			{
				FatalErrorIn(FunctionSIG)
					<< "the section has one non-marine curve, at least" << endl
					<< abort(FatalError);
			}

			if (m->CurveType() IS_EQUAL target)
			{
				const auto curve =
					std::make_shared<Marine_WaterLineCurve>(std::move(*x->Curve()));
				x->SetCurve(curve);
			}		
		}
		break;
	}
	case marineLib::curveType::wetted:
	{
		for (const auto& x : cmpEdge->Edges())
		{
			Debug_Null_Pointer(x);

			const auto& curve = x->Curve();
			auto m = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
			if (NOT m)
			{
				FatalErrorIn(FunctionSIG)
					<< "the section has one non-marine curve, at least" << endl
					<< abort(FatalError);
			}

			if (m->CurveType() IS_EQUAL target)
			{
				const auto curve =
					std::make_shared<Marine_WettedCurve>(std::move(*x->Curve()));
				x->SetCurve(curve);
			}		
		}
		break;
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "undefined section type!" << endl
			<< abort(FatalError);
		break;
	}
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsOuter
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	if (theSection->IsTank())
	{
		auto tank = std::dynamic_pointer_cast<marineLib::Section_Tank>(theSection);
		Debug_Null_Pointer(tank);

		return tank->IsOuter();
	}
	else if (theSection->IsSail())
	{
		auto sail = std::dynamic_pointer_cast<marineLib::Section_Sail>(theSection);
		Debug_Null_Pointer(sail);

		return sail->IsOuter();
	}
	else if (theSection->IsHull())
	{
		auto hull = std::dynamic_pointer_cast<Marine_HullSection>(theSection);
		Debug_Null_Pointer(hull);

		if (hull->IsXsect())
		{
			auto xSect = std::dynamic_pointer_cast<Marine_xSection>(theSection);
			Debug_Null_Pointer(xSect);

			if (xSect->IsDry())
			{
				auto dry = std::dynamic_pointer_cast<marineLib::Section_Dry>(theSection);
				Debug_Null_Pointer(dry);

				return dry->IsOuter();
			}
			else if (xSect->IsWetted())
			{
				auto wetted = std::dynamic_pointer_cast<marineLib::Section_Wetted>(theSection);
				Debug_Null_Pointer(wetted);

				return wetted->IsOuter();
			}
			else if (xSect->IsDisplacer())
			{
				auto disp = std::dynamic_pointer_cast<marineLib::Section_Displacer>(theSection);
				Debug_Null_Pointer(disp);

				return disp->IsOuter();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Boolean IsOuter(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "invalid type of the xSection" << endl
					<< abort(FatalError);
				return Standard_True;
			}
		}
		else if (hull->IsZsect())
		{
			auto zSect = std::dynamic_pointer_cast<Marine_zSection>(theSection);
			Debug_Null_Pointer(zSect);

			if (zSect->IsWaterLine())
			{
				auto wl = std::dynamic_pointer_cast<marineLib::Section_WaterLine>(theSection);
				Debug_Null_Pointer(wl);

				return wl->IsOuter();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Boolean IsOuter(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "invalid type of the zSection" << endl
					<< abort(FatalError);
				return Standard_True;
			}
		}
		else
		{
			FatalErrorIn
			(
				"Standard_Boolean IsOuter(const std::shared_ptr<Marine_Section>& theSection)"
			)
				<< "invalid type of the hull section" << endl
				<< abort(FatalError);
			return Standard_True;
		}
	}
	else if (theSection->IsWaterSection())
	{
#ifdef _DEBUG
		auto water = std::dynamic_pointer_cast<marineLib::Section_Water>(theSection);
		Debug_Null_Pointer(water);
#endif // _DEBUG
		return Standard_True;
	}
	else
	{
		FatalErrorIn
		(
			"Standard_Boolean IsOuter(const std::shared_ptr<Marine_Section>& theSection)"
		)
			<< "invalid type of the section" << endl
			<< abort(FatalError);
		return Standard_True;
	}
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsInner
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	if (theSection->IsTank())
	{
		auto tank = std::dynamic_pointer_cast<marineLib::Section_Tank>(theSection);
		Debug_Null_Pointer(tank);

		return tank->IsInner();
	}
	else if (theSection->IsSail())
	{
		auto sail = std::dynamic_pointer_cast<marineLib::Section_Sail>(theSection);
		Debug_Null_Pointer(sail);

		return sail->IsInner();
	}
	else if (theSection->IsHull())
	{
		auto hull = std::dynamic_pointer_cast<Marine_HullSection>(theSection);
		Debug_Null_Pointer(hull);

		if (hull->IsXsect())
		{
			auto xSect = std::dynamic_pointer_cast<Marine_xSection>(theSection);
			Debug_Null_Pointer(xSect);

			if (xSect->IsDry())
			{
				auto dry = std::dynamic_pointer_cast<marineLib::Section_Dry>(theSection);
				Debug_Null_Pointer(dry);

				return dry->IsInner();
			}
			else if (xSect->IsWetted())
			{
				auto wetted = std::dynamic_pointer_cast<marineLib::Section_Wetted>(theSection);
				Debug_Null_Pointer(wetted);

				return wetted->IsInner();
			}
			else if (xSect->IsDisplacer())
			{
				auto disp = std::dynamic_pointer_cast<marineLib::Section_Displacer>(theSection);
				Debug_Null_Pointer(disp);

				return disp->IsInner();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Boolean IsInner(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "invalid type of the xSection" << endl
					<< abort(FatalError);
				return Standard_False;
			}
		}
		else if (hull->IsZsect())
		{
			auto zSect = std::dynamic_pointer_cast<Marine_zSection>(theSection);
			Debug_Null_Pointer(zSect);

			if (zSect->IsWaterLine())
			{
				auto wl = std::dynamic_pointer_cast<marineLib::Section_WaterLine>(theSection);
				Debug_Null_Pointer(wl);

				return wl->IsInner();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Boolean IsInner(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "invalid type of the zSection" << endl
					<< abort(FatalError);
				return Standard_True;
			}
		}
		else
		{
			FatalErrorIn
			(
				"Standard_Boolean IsInner(const std::shared_ptr<Marine_Section>& theSection)"
			)
				<< "invalid type of the hull section" << endl
				<< abort(FatalError);
			return Standard_True;
		}
	}
	else if (theSection->IsWaterSection())
	{
#ifdef _DEBUG
		auto water = std::dynamic_pointer_cast<marineLib::Section_Water>(theSection);
		Debug_Null_Pointer(water);
#endif // _DEBUG
		return Standard_False;
	}
	else
	{
		FatalErrorIn
		(
			"Standard_Boolean IsInner(const std::shared_ptr<Marine_Section>& theSection)"
		)
			<< "invalid type of the section" << endl
			<< abort(FatalError);
		return Standard_False;
	}
}

Standard_Integer 
tnbLib::Marine_SectTools::NbInners
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	if (theSection->IsWaterSection())
	{
		return 0;
	}
	else
	{
		switch (theSection->Type())
		{
		case Marine_SectionType::waterLine:
		{
			const auto wl = WaterLineSection(theSection);
			Debug_Null_Pointer(wl);

			if (wl->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_WaterLine>
					>(theSection);
				Debug_Null_Pointer(outer);

				return outer->NbInners();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Integer NbInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return 0;
			}
		}
		case Marine_SectionType::tank:
		{
			const auto tank = TankSection(theSection);
			Debug_Null_Pointer(tank);

			if (tank->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Tank>
					>(theSection);
				Debug_Null_Pointer(outer);

				return outer->NbInners();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Integer NbInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return 0;
			}
		}
		case Marine_SectionType::sail:
		{
			const auto sail = SailSection(theSection);
			Debug_Null_Pointer(sail);

			if (sail->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Sail>
					>(theSection);
				Debug_Null_Pointer(outer);

				return outer->NbInners();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Integer NbInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not sail!" << endl
					<< abort(FatalError);
				return 0;
			}
		}
		case Marine_SectionType::dry:
		{
			const auto dry = DrySection(theSection);
			Debug_Null_Pointer(dry);

			if (dry->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Dry>
					>(theSection);
				Debug_Null_Pointer(outer);

				return outer->NbInners();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Integer NbInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return 0;
			}
		}
		case Marine_SectionType::wetted:
		{
			const auto wetted = WettedSection(theSection);
			Debug_Null_Pointer(wetted);

			if (wetted->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Wetted>
					>(theSection);
				Debug_Null_Pointer(outer);

				return outer->NbInners();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Integer NbInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return 0;
			}
		}
		case Marine_SectionType::displacer:
		{
			const auto disp = DisplacerSection(theSection);
			Debug_Null_Pointer(disp);

			if (disp->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Displacer>
					>(theSection);
				Debug_Null_Pointer(outer);

				return outer->NbInners();
			}
			else
			{
				FatalErrorIn
				(
					"Standard_Integer NbInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not displacer!" << endl
					<< abort(FatalError);
				return 0;
			}
		}
		default:
			FatalErrorIn
			(
				"Standard_Integer NbInners(const std::shared_ptr<Marine_Section>& theSection)"
			)
				<< "contradictory data!" << endl
				<< " - invalid section type = " << (int)theSection->Type() << endl
				<< abort(FatalError);
			return 0;
			break;
		}
	}
}

Standard_Boolean 
tnbLib::Marine_SectTools::HasInnerSection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	return (Standard_Boolean)NbInners(theSection);
}

Standard_Boolean 
tnbLib::Marine_SectTools::HasInnerSection
(
	const Marine_CmpSection & theSection
)
{
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		if (HasInnerSection(x))
			return Standard_True;
	}
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_SectTools::RetrieveInners
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	if (theSection->IsWaterSection())
	{
		/*FatalErrorIn
		(
			"std::vector<std::shared_ptr<Marine_Section>> "
			"RetriveInners(const std::shared_ptr<Marine_Section>& theSection)"
		)
			<< "the section is a water type!" << endl
			<< abort(FatalError);*/
		return std::vector<std::shared_ptr<Marine_Section>>();
	}
	else
	{
		switch (theSection->Type())
		{
		case Marine_SectionType::waterLine:
		{
			const auto wl = WaterLineSection(theSection);
			Debug_Null_Pointer(wl);

			if (wl->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_WaterLine>
					>(theSection);
				Debug_Null_Pointer(outer);

				auto inners = RetrieveInners(*outer);
				return std::move(inners);
			}
			else
			{
				FatalErrorIn
				(
					"std::vector<std::shared_ptr<Marine_Section>> "
					"RetriveInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return std::vector<std::shared_ptr<Marine_Section>>();
			}
		}
		case Marine_SectionType::tank:
		{
			const auto tank = TankSection(theSection);
			Debug_Null_Pointer(tank);

			if (tank->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Tank>
					>(theSection);
				Debug_Null_Pointer(outer);

				auto inners = RetrieveInners(*outer);
				return std::move(inners);
			}
			else
			{
				FatalErrorIn
				(
					"std::vector<std::shared_ptr<Marine_Section>> "
					"RetriveInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return std::vector<std::shared_ptr<Marine_Section>>();
			}
		}
		case Marine_SectionType::sail:
		{
			const auto sail = SailSection(theSection);
			Debug_Null_Pointer(sail);

			if (sail->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Sail>
					>(theSection);
				Debug_Null_Pointer(outer);

				auto inners = RetrieveInners(*outer);
				return std::move(inners);
			}
			else
			{
				FatalErrorIn
				(
					"std::vector<std::shared_ptr<Marine_Section>> "
					"RetriveInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return std::vector<std::shared_ptr<Marine_Section>>();
			}
		}
		case Marine_SectionType::dry:
		{
			const auto dry = DrySection(theSection);
			Debug_Null_Pointer(dry);

			if (dry->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Dry>
					>(theSection);
				Debug_Null_Pointer(outer);

				auto inners = RetrieveInners(*outer);
				return std::move(inners);
			}
			else
			{
				FatalErrorIn
				(
					"std::vector<std::shared_ptr<Marine_Section>> "
					"RetriveInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return std::vector<std::shared_ptr<Marine_Section>>();
			}
		}
		case Marine_SectionType::wetted:
		{
			const auto wetted = WettedSection(theSection);
			Debug_Null_Pointer(wetted);

			if (wetted->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Wetted>
					>(theSection);
				Debug_Null_Pointer(outer);

				auto inners = RetrieveInners(*outer);
				return std::move(inners);
			}
			else
			{
				FatalErrorIn
				(
					"std::vector<std::shared_ptr<Marine_Section>> "
					"RetriveInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return std::vector<std::shared_ptr<Marine_Section>>();
			}
		}
		case Marine_SectionType::displacer:
		{
			const auto disp = DisplacerSection(theSection);
			Debug_Null_Pointer(disp);

			if (disp->IsOuter())
			{
				auto outer = std::dynamic_pointer_cast
					<
					marineLib::OuterSection<marineLib::Section_Displacer>
					>(theSection);
				Debug_Null_Pointer(outer);

				auto inners = RetrieveInners(*outer);
				return std::move(inners);
			}
			else
			{
				FatalErrorIn
				(
					"std::vector<std::shared_ptr<Marine_Section>> "
					"RetriveInners(const std::shared_ptr<Marine_Section>& theSection)"
				)
					<< "the section is not outer!" << endl
					<< abort(FatalError);
				return std::vector<std::shared_ptr<Marine_Section>>();
			}
		}
		default:
			FatalErrorIn
			(
				"std::vector<std::shared_ptr<Marine_Section>> "
				"RetriveInners(const std::shared_ptr<Marine_Section>& theSection)"
			)
				<< "contradictory data!" << endl
				<< " - invalid section type = " << (int)theSection->Type() << endl
				<< abort(FatalError);
			return std::vector<std::shared_ptr<Marine_Section>>();
			break;
		}
	}
}

std::shared_ptr<tnbLib::marineLib::Section_Dry> 
tnbLib::Marine_SectTools::DrySection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	auto dry = std::dynamic_pointer_cast<marineLib::Section_Dry>(theSection);
	if (NOT dry)
	{
		FatalErrorIn
		(
			FunctionSIG
		)
			<< "the Section is not dry!" << endl
			<< abort(FatalError);
	}
	return std::move(dry);
}

std::shared_ptr<tnbLib::marineLib::Section_Wetted> 
tnbLib::Marine_SectTools::WettedSection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	auto wetted = std::dynamic_pointer_cast<marineLib::Section_Wetted>(theSection);
	if (NOT wetted)
	{
		FatalErrorIn
		(
			FunctionSIG
		)
			<< "the sections is not wet" << endl
			<< abort(FatalError);
	}
	return std::move(wetted);
}

std::shared_ptr<tnbLib::marineLib::Section_Displacer> 
tnbLib::Marine_SectTools::DisplacerSection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	auto wetted = std::dynamic_pointer_cast<marineLib::Section_Displacer>(theSection);
	if (NOT wetted)
	{
		FatalErrorIn
		(
			FunctionSIG
		)
			<< "the sections is not displacer" << endl
			<< abort(FatalError);
	}
	return std::move(wetted);
}

std::shared_ptr<tnbLib::marineLib::Section_Sail> 
tnbLib::Marine_SectTools::SailSection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	auto sail = std::dynamic_pointer_cast<marineLib::Section_Sail>(theSection);
	if (NOT sail)
	{
		FatalErrorIn
		(
			FunctionSIG
		)
			<< "the sections is not Sail" << endl
			<< abort(FatalError);
	}
	return std::move(sail);
}

std::shared_ptr<tnbLib::marineLib::Section_Tank> 
tnbLib::Marine_SectTools::TankSection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	auto tank = std::dynamic_pointer_cast<marineLib::Section_Tank>(theSection);
	if (NOT tank)
	{
		FatalErrorIn
		(
			FunctionSIG
		)
			<< "the sections is not tank" << endl
			<< abort(FatalError);
	}
	return std::move(tank);
}

std::shared_ptr<tnbLib::marineLib::Section_WaterLine> 
tnbLib::Marine_SectTools::WaterLineSection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	auto wl = std::dynamic_pointer_cast<marineLib::Section_WaterLine>(theSection);
	if (NOT wl)
	{
		FatalErrorIn
		(
			FunctionSIG
		)
			<< "the section is not waterLine" << endl
			<< abort(FatalError);
	}
	return std::move(wl);
}

std::shared_ptr<tnbLib::marineLib::Section_Water> 
tnbLib::Marine_SectTools::WaterSection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	if (NOT theSection->IsWaterSection())
	{
		FatalErrorIn
		(
			"std::shared_ptr<Marine_WaterSection> "
			"WaterSection(const std::shared_ptr<Marine_Section>& theSection)"
		)
			<< "the section is not water!" << endl
			<< abort(FatalError);
	}
	auto water = std::dynamic_pointer_cast<marineLib::Section_Water>(theSection);
	Debug_Null_Pointer(water);
	return std::move(water);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Marine_SectTools::ConvertToPlane
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	if (NOT IsOuter(theSection))
	{
		FatalErrorIn
		(
			"std::shared_ptr<Cad2d_Plane> ConvertToPlane(const std::shared_ptr<Marine_Section>& theSection)"
		)
			<< "the section is not outer!" << endl
			<< " to construct a plane, the section must be a outer" << endl
			<< abort(FatalError);
	}

	const auto inners = RetrieveInners(theSection);

#ifdef _DEBUG
	for (const auto& x : inners)
	{
		if (NOT IsInner(x))
		{
			FatalErrorIn
			(
				"std::shared_ptr<Cad2d_Plane> ConvertToPlane(const std::shared_ptr<Marine_Section>& theSection)"
			)
				<< "the section is not inner!" << endl
				<< abort(FatalError);
		}
	}
#endif // _DEBUG

	auto innerWires_p = std::make_shared<std::vector<std::shared_ptr<Pln_Wire>>>();
	if (inners.size())
	{
		auto& innerWires = *innerWires_p;
		innerWires.reserve(inners.size());
		for (const auto& x : inners)
		{
			Debug_Null_Pointer(x);
			innerWires.push_back(x->Wire());
		}
	}
	
	auto plane = Cad2d_Plane::MakePlane(theSection->Wire(), innerWires_p);
	Debug_Null_Pointer(plane);
	return std::move(plane);
}

std::shared_ptr<tnbLib::Marine_Section> 
tnbLib::Marine_SectTools::ConvertToSection
(
	const std::shared_ptr<Cad2d_Plane>& thePlane, 
	const Marine_SectionType t
)
{
	const auto& outerWire = thePlane->OuterWire();
	const auto& innerWires = thePlane->InnerWires();

	switch (t)
	{
	case Marine_SectionType::water:
	{
		auto sect = CreateSection<marineLib::Section_Water>::_(outerWire);
		return std::move(sect);
	}
	case Marine_SectionType::waterLine:
	{
		auto sect = CreateSection<marineLib::Section_WaterLine>::_(outerWire, innerWires);
		return std::move(sect);
	}
	case Marine_SectionType::tank:
	{
		auto sect = CreateSection<marineLib::Section_Tank>::_(outerWire, innerWires);
		return std::move(sect);
	}
	case Marine_SectionType::sail:
	{
		auto sect = CreateSection<marineLib::Section_Sail>::_(outerWire, innerWires);
		return std::move(sect);
	}
	case Marine_SectionType::dry:
	{
		auto sect = CreateSection<marineLib::Section_Dry>::_(outerWire, innerWires);
		return std::move(sect);
	}
	case Marine_SectionType::wetted:
	{
		auto sect = CreateSection<marineLib::Section_Wetted>::_(outerWire, innerWires);
		return std::move(sect);
	}
	case Marine_SectionType::displacer:
	{
		auto sect = CreateSection<marineLib::Section_Displacer>::_(outerWire, innerWires);
		return std::move(sect);
	}
	default:
		FatalErrorIn
		(
			"std::shared_ptr<Marine_Section>"
			" ConvertToSection(const std::shared_ptr<Cad2d_Plane>& thePlane, const Marine_SectionType t)"
		)
			<< "invalid type of the section!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>> 
tnbLib::Marine_SectTools::RetrievePalnes
(
	const std::shared_ptr<Marine_CmpSection>& theSection
)
{
	const auto& outers = theSection->Sections();

	std::vector<std::shared_ptr<Cad2d_Plane>> planes;
	planes.reserve(outers.size());
	for (const auto& x : outers)
	{
		Debug_Null_Pointer(x);

		auto plane = ConvertToPlane(x);
		Debug_Null_Pointer(plane);

		planes.push_back(std::move(plane));
	}
	return std::move(planes);
}

std::shared_ptr<tnbLib::Marine_CmpSection> 
tnbLib::Marine_SectTools::ConvertToComposite
(
	const std::shared_ptr<Marine_Section>& theSect
)
{
	if (IsXSection(theSect))
	{
		auto cmpSect = std::make_shared<Marine_xCmpSection>(theSect);
		Debug_Null_Pointer(cmpSect);
		return std::move(cmpSect);
	}
	else
	{
		auto cmpSect = std::make_shared<Marine_zCmpSection>(theSect);
		Debug_Null_Pointer(cmpSect);
		return std::move(cmpSect);
	}
}

#include <Marine_PlnCurves.hxx>

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::Marine_SectTools::CurveCreator
(
	const Handle(Geom2d_Curve)& theCurve, 
	const Marine_SectionType & t
)
{
	switch (t)
	{
	case Marine_SectionType::displacer:
	{
		auto c = std::make_shared<Marine_DisplacerCurve>(theCurve);
		return std::move(c);
	}
	case Marine_SectionType::dry:
	{
		auto c = std::make_shared<Marine_DryCurve>(theCurve);
		return std::move(c);
	}
	case Marine_SectionType::sail:
	{
		auto c = std::make_shared<Marine_SailCurve>(theCurve);
		return std::move(c);
	}
	case Marine_SectionType::tank:
	{
		auto c = std::make_shared<Marine_TankCurve>(theCurve);
		return std::move(c);
	}
	case Marine_SectionType::water:
	{
		auto c = std::make_shared<Marine_WaterCurve>(theCurve);
		return std::move(c);
	}
	case Marine_SectionType::waterLine:
	{
		auto c = std::make_shared<Marine_WaterLineCurve>(theCurve);
		return std::move(c);
	}
	case Marine_SectionType::wetted:
	{
		auto c = std::make_shared<Marine_WettedCurve>(theCurve);
		return std::move(c);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "undefined type of the curve!" << endl
			<< abort(FatalError);
		return nullptr;
		break;
	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Marine_SectTools::CurveCreator
(
	const std::vector<Handle(Geom2d_Curve)>& theCurves, 
	const Marine_SectionType & t
)
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(theCurves.size());
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);
		auto curve = CurveCreator(x, t);
		curves.push_back(std::move(curve));
	}
	return std::move(curves);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>>
tnbLib::Marine_SectTools::SectionCreator
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const gp_Ax2 & theSystem,
	const Marine_SectionType & t,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	auto wires = Pln_Tools::RetrieveWires(theCurves, theMinTol, theMaxTol);

	Pln_Tools::SortWires(wires);

	Standard_Integer K = 0;
	for (const auto& x : wires)
	{
		Debug_Null_Pointer(x);
		x->SetIndex(++K);
	}

	std::list<std::shared_ptr<Pln_Wire>> wireList;
	for (const auto& x : wires)
	{
		Debug_Null_Pointer(x);
		wireList.push_back(x);
	}

	std::vector<std::shared_ptr<Marine_Section>> sections;
	while (NOT wireList.empty())
	{
		std::shared_ptr<Pln_Wire> outer;
		auto inners = std::make_shared<std::vector<std::shared_ptr<Pln_Wire>>>();
		Debug_Null_Pointer(inners);

		Pln_Tools::RetrieveInnerOuterWires(wireList, outer, *inners);

		if (NOT outer)
		{
			FatalErrorIn
			(
				"std::vector<std::shared_ptr<Marine_Section>> Marine_SectTools::SectionCreator(Args...)"
			)
				<< "Invalid section" << endl
				<< abort(FatalError);
		}

		if (outer->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CCW)
		{
			outer->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);
		}

		if (inners->empty())
		{
			auto section = SectionCreator(outer, theSystem, t);
			Debug_Null_Pointer(section);

			section->SetIndex(++K);
			sections.push_back(std::move(section));
		}
		else
		{
			FatalErrorIn
			(
				"std::vector<std::shared_ptr<Marine_Section>> Marine_SectTools::SectionCreator(Args...)"
			)
				<< "the section shouldn't contain any inner wire" << endl
				<< abort(FatalError);

			/*for (const auto& x : *inners)
			{
				Debug_Null_Pointer(x);
				if (x->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CW)
				{
					x->ApplyOrientation(Pln_Orientation::Pln_Orientation_CW);
				}
			}

			auto section = std::make_shared<Marine_Section>(++K, outer, inners);
			Debug_Null_Pointer(section);

			sections.push_back(std::move(section));*/
		}
	}
	return std::move(sections);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>>
tnbLib::Marine_SectTools::SectionCreator
(
	const std::vector<Handle(Geom2d_Curve)>& theCurves, 
	const gp_Ax2 & theSystem,
	const Marine_SectionType & t, 
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(theCurves.size());

	Standard_Integer K = 0;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		if (NOT Pln_Tools::IsBounded(x))
		{
			FatalErrorIn
			(
				"std::shared_ptr<Marine_Section> Marine_SectTools::SectionCreator(Args....)"
			)
				<< "the curve is not bounded" << endl
				<< abort(FatalError);
		}

		auto curve = CurveCreator(x, t);
		Debug_Null_Pointer(curve);

		curve->SetIndex(++K);
		curves.push_back(std::move(curve));
	}

	auto section = 
		SectionCreator(curves, theSystem, t, theMinTol, theMaxTol);
	return std::move(section);
}

std::shared_ptr<tnbLib::Marine_Section> 
tnbLib::Marine_SectTools::SectionCreator
(
	const std::shared_ptr<Pln_Wire>& theOuter, 
	const gp_Ax2 & theSystem, 
	const Marine_SectionType & t
)
{
	switch (t)
	{
	case Marine_SectionType::displacer:
	{
		auto section = CreateSection<marineLib::Section_Displacer>::_(theOuter, nullptr);
		Debug_Null_Pointer(section);

		section->SetCoordinateSystem(theSystem);

		return std::move(section);
	}
	case Marine_SectionType::dry:
	{
		auto section = CreateSection<marineLib::Section_Dry>::_(theOuter, nullptr);
		Debug_Null_Pointer(section);

		section->SetCoordinateSystem(theSystem);

		return std::move(section);
	}
	case Marine_SectionType::sail:
	{
		auto section = CreateSection<marineLib::Section_Sail>::_(theOuter, nullptr);
		Debug_Null_Pointer(section);

		section->SetCoordinateSystem(theSystem);

		return std::move(section);
	}
	case Marine_SectionType::tank:
	{
		auto section = CreateSection<marineLib::Section_Tank>::_(theOuter, nullptr);
		Debug_Null_Pointer(section);

		section->SetCoordinateSystem(theSystem);

		return std::move(section);
	}
	case Marine_SectionType::water:
	{
		auto section = CreateSection<marineLib::Section_Water>::_(theOuter);
		Debug_Null_Pointer(section);

		section->SetCoordinateSystem(theSystem);

		return std::move(section);
	}
	case Marine_SectionType::waterLine:
	{
		auto section = CreateSection<marineLib::Section_WaterLine>::_(theOuter, nullptr);
		Debug_Null_Pointer(section);

		section->SetCoordinateSystem(theSystem);

		return std::move(section);
	}
	case Marine_SectionType::wetted:
	{
		auto section = CreateSection<marineLib::Section_Wetted>::_(theOuter, nullptr);
		Debug_Null_Pointer(section);

		section->SetCoordinateSystem(theSystem);

		return std::move(section);
	}
	default:
		FatalErrorIn
		(
			"std::shared_ptr<Marine_Section>"
			" SectionCreator(Args...)"
		)
			<< "invalid type of the section!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Marine_Section> 
tnbLib::Marine_SectTools::SectionCreator
(
	const std::shared_ptr<Pln_Wire>& theOuter, 
	const Marine_SectionType & t
)
{
	auto sect = SectionCreator(theOuter, gp::XOY(), t);
	Debug_Null_Pointer(sect);

	return std::move(sect);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>>
tnbLib::Marine_SectTools::SectionCreator
(
	const TopoDS_Shape & theEdges, 
	const gp_Ax2 & theSystem,
	const Marine_SectionType & t,
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
	auto edges = Pln_Tools::RetrieveEdges(theEdges);
	auto curves = Pln_Tools::RetrieveParaCurves(edges, theSystem);

	auto section = 
		SectionCreator(curves, theSystem, t, theMinTol, theMaxTol);
	return std::move(section);
}

Standard_Boolean
tnbLib::Marine_SectTools::IsXSection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	if (NOT std::dynamic_pointer_cast<marineLib::Section_WaterLine>(theSection))
	{
		return Standard_True;
	}
	return Standard_False;
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsDry
(
	const Marine_CmpSection & theSect
)
{
	return theSect.Type() IS_EQUAL Marine_SectionType::dry;
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsDry
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	auto curve = std::dynamic_pointer_cast<Marine_DryCurve>(theCurve);
	return (Standard_Boolean)curve;
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsWetted
(
	const Marine_CmpSection & theSect
)
{
	return theSect.Type() IS_EQUAL Marine_SectionType::wetted;
}

Standard_Boolean
tnbLib::Marine_SectTools::IsWetted
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	auto curve = std::dynamic_pointer_cast<Marine_WettedCurve>(theCurve);
	return (Standard_Boolean)curve;
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsDisplacer
(
	const Marine_CmpSection & theSect
)
{
	return theSect.Type() IS_EQUAL Marine_SectionType::displacer;
}

Standard_Boolean
tnbLib::Marine_SectTools::IsDisplacer
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	auto curve = std::dynamic_pointer_cast<Marine_DisplacerCurve>(theCurve);
	return (Standard_Boolean)curve;
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsSail
(
	const Marine_CmpSection & theSect
)
{
	return theSect.Type() IS_EQUAL Marine_SectionType::sail;
}

Standard_Boolean
tnbLib::Marine_SectTools::IsSail
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	auto curve = std::dynamic_pointer_cast<Marine_SailCurve>(theCurve);
	return (Standard_Boolean)curve;
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsTank
(
	const Marine_CmpSection & theSect
)
{
	return theSect.Type() IS_EQUAL Marine_SectionType::tank;
}

Standard_Boolean
tnbLib::Marine_SectTools::IsTank
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	auto curve = std::dynamic_pointer_cast<Marine_TankCurve>(theCurve);
	return (Standard_Boolean)curve;
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsWaterLine
(
	const Marine_CmpSection & theSect
)
{
	return theSect.Type() IS_EQUAL Marine_SectionType::waterLine;
}

Standard_Boolean
tnbLib::Marine_SectTools::IsWaterLine
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	auto curve = std::dynamic_pointer_cast<Marine_WaterLineCurve>(theCurve);
	return (Standard_Boolean)curve;
}

Standard_Boolean 
tnbLib::Marine_SectTools::IsWater
(
	const Marine_CmpSection & theSect
)
{
	return theSect.Type() IS_EQUAL Marine_SectionType::water;
}

Standard_Boolean
tnbLib::Marine_SectTools::IsWater
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	auto curve = std::dynamic_pointer_cast<Marine_WaterCurve>(theCurve);
	return (Standard_Boolean)curve;
}

namespace tnbLib
{

	void CheckSections(const std::vector<std::shared_ptr<Marine_Section>>& theSections)
	{
		auto iter = theSections.begin();
		const auto t = (*iter)->Type();

		iter++;

		while (iter NOT_EQUAL theSections.end())
		{
			if ((*iter)->Type() NOT_EQUAL t)
			{
				FatalErrorIn(FunctionSIG)
					<< "the sections are not the same type!" << endl
					<< abort(FatalError);
			}
			iter++;
		}
	}
}

Standard_Boolean 
tnbLib::Marine_SectTools::SameDirection
(
	const Marine_CmpSection & theSect0, 
	const Marine_CmpSection & theSect1
)
{
	const auto& sys0 = theSect0.CoordinateSystem();
	const auto& sys1 = theSect1.CoordinateSystem();

	if (sys0.Direction().IsParallel(sys1.Direction(), gp::Resolution()))
	{
		return Standard_True;
	}
	return Standard_False;
}

gp_Pln 
tnbLib::Marine_SectTools::gpPln
(
	const Marine_Section & theSect
)
{
	const auto& sys = theSect.CoordinateSystem();
	auto plane = gp_Pln(sys.Location(), sys.Direction());
	return std::move(plane);
}

gp_Pln 
tnbLib::Marine_SectTools::gpPln
(
	const Marine_CmpSection & theSect
)
{
	const auto& sys = theSect.CoordinateSystem();
	auto plane = gp_Pln(sys.Location(), sys.Direction());
	return std::move(plane);
}

tnbLib::Entity3d_Box 
tnbLib::Marine_SectTools::BoundingBox
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel
)
{
	const auto& sections = theModel;

	auto iter = sections.begin();
	auto b = (*iter)->BoundingBox();

	const auto x0 = sections[0]->X();
	const auto x1 = sections[sections.size() - 1]->X();

	iter++;
	while (iter NOT_EQUAL sections.end())
	{
		b = Entity2d_Box::Union(b, (*iter)->BoundingBox());
		iter++;
	}

	const auto y0 = b.P0().X();
	const auto y1 = b.P1().X();

	const auto z0 = b.P0().Y();
	const auto z1 = b.P1().Y();

	Entity3d_Box box(Pnt3d(x0, y0, z0), Pnt3d(x1, y1, z1));
	return std::move(box);
}

std::shared_ptr<tnbLib::Marine_CmpSection>
tnbLib::Marine_SectTools::CmpSectionCreator
(
	const std::vector<std::shared_ptr<Marine_Section>>& theSections
)
{
	if (theSections.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "empty list" << endl
			<< abort(FatalError);
	}

	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		CheckTypeConsistency(x);
		//CheckInnerSection(x);
	}

	if (IsXSection(theSections[0]))
	{
		auto cmp = std::make_shared<Marine_xCmpSection>();
		Debug_Null_Pointer(cmp);

		for (const auto& x : theSections)
		{
			cmp->Insert(x);
		}
		return std::move(cmp);
	}
	else
	{
		auto cmp = std::make_shared<Marine_zCmpSection>();
		Debug_Null_Pointer(cmp);

		for (const auto& x : theSections)
		{
			cmp->Insert(x);
		}
		return std::move(cmp);
	}
}

#include <Marine_BooleanOps.hxx>

std::shared_ptr<tnbLib::Marine_Section> 
tnbLib::Marine_SectTools::FitTankToHull
(
	const std::shared_ptr<Marine_Section>& theTank, 
	const std::shared_ptr<Marine_Section>& theHull
)
{
	if (NOT theTank->BoundingBox().IsIntersect(theHull->BoundingBox()))
	{
		return nullptr;
	}

	auto sum = Marine_BooleanOps::Intersection(theTank, theHull);

	if (sum.empty())
	{
		return nullptr;
	}

	if (sum.size() > 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "unexpected situation is happened for fitting the tank section to the hull!" << endl
			<< abort(FatalError);
	}
	return std::move(sum[0]);
}

std::shared_ptr<tnbLib::Marine_Section>
tnbLib::Marine_SectTools::FitTankToHull
(
	const std::shared_ptr<Marine_Section>& theTank, 
	const std::shared_ptr<Marine_CmpSection>& theHull
)
{
	std::vector<std::shared_ptr<Marine_Section>> sections;
	for (const auto& x : theHull->Sections())
	{
		auto sect = FitTankToHull(theTank, theHull);
		if (sect)
		{
			sections.push_back(std::move(sect));
		}
	}
	if (sections.size() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "unexpected situation is happened for fitting the tank section to the hull!" << endl
			<< abort(FatalError);
	}
	return std::move(sections[0]);
}

namespace tnbLib
{
	template<>
	std::vector<std::shared_ptr<Marine_Section>> Marine_SectTools::RetrieveInners
	(
		const marineLib::OuterSection<marineLib::Section_Water>& theSection
	)
	{
		FatalErrorIn
		(
			"std::vector<std::shared_ptr<Marine_Section>>"
			" RetrieveInners<Marine_WaterSection>(const Marine_OuterSection<Marine_WaterSection>& theSection)"
		)
			<< "a water section doesn't have any inner section!" << endl
			<< abort(FatalError);
		return std::vector<std::shared_ptr<Marine_Section>>();
	}

	std::shared_ptr<Marine_Section> 
		tnbLib::Marine_SectTools::CreateSection<marineLib::Section_Water>::_
		(
			const std::shared_ptr<Pln_Wire>& theOuter
		)
	{
		auto sect = 
			std::make_shared
			<
			marineLib::OuterSection<marineLib::Section_Water>
			>(theOuter->Index(), theOuter);
		Debug_Null_Pointer(sect);

		return std::move(sect);
	}
}

void tnbLib::Marine_SectTools::SetLocation
(
	const std::shared_ptr<Marine_CmpSection>& theSection,
	const Standard_Real x
)
{
	Debug_Null_Pointer(theSection);
	if (theSection->IsXsection())
	{
		auto loc = theSection->CoordinateSystem().Location();
		loc.ChangeCoord().SetX(x);

		theSection->CoordinateSystem().SetLocation(loc);

	}
	else if (theSection->IsZsection())
	{
		auto loc = theSection->CoordinateSystem().Location();
		loc.ChangeCoord().SetZ(x);

		theSection->CoordinateSystem().SetLocation(loc);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unspecified section direction" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Marine_SectTools::CheckTypeConsistency
(
	const std::shared_ptr<Marine_Section>& theSect
)
{
	if (HasInnerSection(theSect))
	{
		auto inners = RetrieveInners(theSect);

		const auto t = theSect->Type();

		for (const auto& x : inners)
		{
			Debug_Null_Pointer(x);
			if (t NOT_EQUAL x->Type())
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data!" << endl
					<< " type of the inners are not the same with the outer" << endl
					<< abort(FatalError);
			}
		}
	}
}

void tnbLib::Marine_SectTools::CheckTypeConsistency
(
	const Marine_CmpSection & theSect
)
{
	const auto& sections = theSect.Sections();
	if (sections.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "null list" << endl
			<< abort(FatalError);
	}

	auto iter = sections.begin();
	const auto type = (*iter)->Type();

	iter++;
	while (iter NOT_EQUAL sections.end())
	{
		if ((*iter)->Type() NOT_EQUAL type)
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data!" << endl
				<< abort(FatalError);
		}
		iter++;
	}
}