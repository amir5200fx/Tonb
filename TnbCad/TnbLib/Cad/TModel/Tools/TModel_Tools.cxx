#include <TModel_Tools.hxx>

#include <Cad_Tools.hxx>
#include <Cad_RepairPlnWire.hxx>
#include <TModel_ParaCurve.hxx>
#include <TModel_Surface.hxx>
#include <TModel_ParaWire.hxx>
#include <TModel_Wire.hxx>
#include <TModel_ParaGapCurve.hxx>
#include <TModel_Plane.hxx>
#include <Cad_GeomSurface.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Cad2d_RepairWire.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2dAPI_InterCurveCurve.hxx>

Standard_Boolean 
tnbLib::TModel_Tools::IsPlane
(
	const std::shared_ptr<TModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	return Cad_Tools::IsPlane(theSurface->GeomSurface());
}

Standard_Boolean 
tnbLib::TModel_Tools::IsCylinder
(
	const std::shared_ptr<TModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	return Cad_Tools::IsCylinder(theSurface->GeomSurface());
}

std::vector<std::shared_ptr<tnbLib::TModel_ParaCurve>> 
tnbLib::TModel_Tools::MakeParaCurves
(
	const std::vector<Handle(Geom2d_Curve)>& theGeometries
)
{
	std::vector<std::shared_ptr<TModel_ParaCurve>> curves;
	curves.reserve(theGeometries.size());
	for (const auto& x : theGeometries)
	{
		Debug_Null_Pointer(x);
		auto curve = std::make_shared<TModel_ParaCurve>(x);
		curves.push_back(std::move(curve));
	}
	return std::move(curves);
}

std::vector<Handle(Geom2d_Curve)>
tnbLib::TModel_Tools::RetrieveGeometries
(
	const std::vector<std::shared_ptr<TModel_ParaCurve>>& theWire
)
{
	std::vector<Handle(Geom2d_Curve)> geometries;
	geometries.reserve(theWire.size());
	for (const auto& x : theWire)
	{
		Debug_Null_Pointer(x);
		geometries.push_back(x->Geometry());
	}
	return std::move(geometries);
}

std::vector<Handle(Geom2d_Curve)> 
tnbLib::TModel_Tools::RetrieveGeometries
(
	const TModel_ParaWire & theWire
)
{
	auto geometries = RetrieveGeometries(theWire.Curves());
	return std::move(geometries);
}

Handle(Geom_Surface)
tnbLib::TModel_Tools::RetrieveGeometry
(
	const TModel_Surface & theSurface
)
{
	Debug_Null_Pointer(theSurface.GeomSurface());
	return theSurface.GeomSurface()->Geometry();
}

std::pair
<
	std::shared_ptr<tnbLib::TModel_ParaCurve>,
	std::shared_ptr<tnbLib::TModel_ParaCurve>
> 
tnbLib::TModel_Tools::Split
(
	const Standard_Real x,
	const std::shared_ptr<TModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	Debug_Null_Pointer(theCurve->Geometry());
#ifdef _DEBUG
	if (NOT INSIDE(x, theCurve->FirstParameter(), theCurve->LastParameter()))
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter is outside of the span." << endl
			<< " - x: " << x << endl
			<< " - first parameter: " << theCurve->FirstParameter() << endl
			<< " - last parameter: " << theCurve->LastParameter() << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	auto[g0, g1] = Pln_Tools::Split(x, theCurve->Geometry());
	Debug_Null_Pointer(g0);
	Debug_Null_Pointer(g1);
	auto c0 = std::make_shared<TModel_ParaCurve>(std::move(g0));
	auto c1 = std::make_shared<TModel_ParaCurve>(std::move(g1));

	auto t = std::make_pair(std::move(c0), std::move(c1));
	return std::move(t);
}

tnbLib::Entity2d_Box 
tnbLib::TModel_Tools::CalcBoundingBox
(
	const TModel_ParaWire & theWire
)
{
	const auto& curves = theWire.Curves();
	if (curves.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve list is empty." << endl
			<< abort(FatalError);
	}
	auto iter = curves.begin();
	auto b = (*iter)->CalcBoundingBox();
	iter++;
	while (iter NOT_EQUAL curves.end())
	{
		b = Geo_BoxTools::Union(b, (*iter)->CalcBoundingBox());
		iter++;
	}
	return std::move(b);
}

std::shared_ptr<tnbLib::TModel_ParaCurve> 
tnbLib::TModel_Tools::Trim
(
	const std::shared_ptr<TModel_ParaCurve>& theCurve, 
	const Standard_Real theU0, 
	const Standard_Real theU1
)
{
	Debug_Null_Pointer(theCurve);
	auto geom = Pln_CurveTools::Trim(theCurve->Curve(), theU0, theU1);

	auto curve = std::make_shared<TModel_ParaCurve>
		(theCurve->Index(), theCurve->Name(), std::move(geom));
	return std::move(curve);
}

std::shared_ptr<tnbLib::TModel_ParaWire> 
tnbLib::TModel_Tools::TrimWire
(
	const std::shared_ptr<TModel_ParaWire>& theWire
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
	if (curves.size() > 1)
	{
		auto trimmed = Cad_RepairPlnWire<TModel_ParaWire>::TrimCurves(curves);
		auto trimmedPtr = std::make_shared<std::vector<std::shared_ptr<TModel_ParaCurve>>>(std::move(trimmed));
		auto wire = std::make_shared<TModel_ParaWire>(theWire->Index(), theWire->Name(), std::move(trimmedPtr));
		return std::move(wire);
	}
	// no changing is applied to the wire with one curve [2/21/2022 Amir]
	return theWire;
}

std::shared_ptr<tnbLib::TModel_ParaWire> 
tnbLib::TModel_Tools::GetOuterParaWire
(
	const std::shared_ptr<TModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	const auto& outerWire = theSurface->Outer();
	if (NOT outerWire)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of surface has been detected!" << endl
			<< abort(FatalError);
	}
	auto wire = TModel_Wire::RetrieveParaWire(*outerWire);
	return std::move(wire);
}

std::vector<std::shared_ptr<tnbLib::TModel_ParaWire>> 
tnbLib::TModel_Tools::GetInnerParaWires
(
	const std::shared_ptr<TModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	const auto& inners = theSurface->Inner();
	std::vector<std::shared_ptr<TModel_ParaWire>> wires;
	if (inners)
	{
		for (const auto& x : *inners)
		{
			Debug_Null_Pointer(x);
			auto wire = TModel_Wire::RetrieveParaWire(*x);
			wires.push_back(std::move(wire));
		}
	}
	return std::move(wires);
}

std::shared_ptr<tnbLib::TModel_Plane> 
tnbLib::TModel_Tools::GetParaPlane
(
	const std::shared_ptr<TModel_Surface>& theSurface,
	const Standard_Real theTol
)
{
	Debug_Null_Pointer(theSurface);
	const auto unRepOuterWire = RepairWire(GetOuterParaWire(theSurface), theTol);
	if (NOT unRepOuterWire)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid surface type has been detected: " << endl
			<< " - the surface has no outer wire!" << endl
			<< abort(FatalError);
	}
	//OFstream myFile0("before_corr.plt");
	//OFstream myFile1("after_corr.plt");
	auto approxInfo = std::make_shared<Geo_ApprxCurve_Info>();

	const auto trimOuterWire = TrimWire(unRepOuterWire);

	Debug_Null_Pointer(trimOuterWire);
	//ExportToPlt(trimOuterWire, approxInfo, myFile0);
	const auto waterTight = FillGaps(trimOuterWire, theTol);
	//ExportToPlt(waterTight, approxInfo, myFile1);
	//std::exit(1);
	const auto outerEdges = Cad_RepairPlnWire<TModel_ParaWire>::CreateWire(waterTight, theTol);

	Cad_RepairPlnWire<TModel_ParaWire>::CheckWire(outerEdges);

	auto outerWire = Cad_RepairPlnWire<TModel_ParaWire>::CreateWire(outerEdges);
	Debug_Null_Pointer(outerWire);

	auto innerWires = std::make_shared<TModel_Plane::wireList>();

	std::vector<std::shared_ptr<TModel_ParaWire>> unRepinnerWires;
	auto paraInnerWires = GetInnerParaWires(theSurface);
	for (const auto& x : paraInnerWires)
	{
		Debug_Null_Pointer(x);
		auto inner = RepairWire(x, theTol);
		unRepinnerWires.push_back(std::move(inner));
	}

	if (unRepinnerWires.size())
	{
		for (const auto& x : unRepinnerWires)
		{
			Debug_Null_Pointer(x);

			auto trimInnerWire = TrimWire(x);
			Debug_Null_Pointer(trimInnerWire);
			//ExportToPlt(trimInnerWire, approxInfo, myFile0);
			auto waterTight = FillGaps(trimInnerWire, theTol);
			//ExportToPlt(waterTight, approxInfo, myFile1);
			auto innerEdges = Cad_RepairPlnWire<TModel_ParaWire>::CreateWire(waterTight, theTol);
			Cad_RepairPlnWire<TModel_ParaWire>::CheckWire(innerEdges);

			auto innerWire = Cad_RepairPlnWire<TModel_ParaWire>::CreateWire(innerEdges);
			Debug_Null_Pointer(innerWire);

			innerWires->push_back(std::move(innerWire));
		}
	}
	//std::exit(1);
#ifdef _DEBUG
	Cad_RepairPlnWire<TModel_ParaWire>::CheckWire(outerWire, theTol);
#endif // _DEBUG

	if (innerWires->size())
	{
#ifdef _DEBUG
		for (const auto& x : *innerWires)
		{
			Cad_RepairPlnWire<TModel_ParaWire>::CheckWire(x, theTol);
		}
#endif // _DEBUG
		auto plane = std::make_shared<TModel_Plane>(std::move(outerWire), std::move(innerWires));
		return std::move(plane);
	}
	else
	{
		auto plane = std::make_shared<TModel_Plane>(outerWire);
		return std::move(plane);
	}
}

std::shared_ptr<tnbLib::TModel_ParaWire> 
tnbLib::TModel_Tools::MakeWire
(
	const std::shared_ptr<TModel_ParaCurve>& theCurve
)
{
	auto l = std::make_shared<std::vector<std::shared_ptr<TModel_ParaCurve>>>();
	l->push_back(theCurve);
	auto wire = std::make_shared<TModel_ParaWire>(std::move(l));
	return std::move(wire);
}

std::shared_ptr<tnbLib::TModel_ParaWire> 
tnbLib::TModel_Tools::MakeWire
(
	const std::vector<std::shared_ptr<TModel_ParaCurve>>& theCurves
)
{
	auto l = std::make_shared<std::vector<std::shared_ptr<TModel_ParaCurve>>>(theCurves);
	auto wire = std::make_shared<TModel_ParaWire>(std::move(l));
	return std::move(wire);
}

std::shared_ptr<tnbLib::TModel_ParaWire> 
tnbLib::TModel_Tools::FillGaps
(
	const std::shared_ptr<TModel_ParaWire>& theWire, 
	const Standard_Real theTol
)
{
	Debug_Null_Pointer(theWire);

	const auto& curves = theWire->Curves();
	if (curves.size() IS_EQUAL 1)
	{
		const auto& curve = curves.at(0);
		Debug_Null_Pointer(curve);

		auto P0 = curve->LastCoord();
		auto P1 = curve->FirstCoord();

		if (P0.Distance(P1) < theTol)
		{
			return theWire;
		}
		else
		{
			auto geom = Pln_CurveTools::MakeSegment(P0, P1);
			auto c = std::make_shared<TModel_ParaGapCurve>(curve->Index() + 1, std::move(geom));

			std::vector<std::shared_ptr<TModel_ParaCurve>> newCurves;
			newCurves.reserve(2);

			newCurves.push_back(curve);
			newCurves.push_back(std::move(c));

			auto wire = MakeWire(newCurves);
			return std::move(wire);
		}
	}
	else
	{
		auto maxId = Cad_RepairPlnWire<TModel_ParaWire>::MaxIndex(curves);
		std::vector<std::shared_ptr<TModel_ParaCurve>> newCurves;
		{
			const auto& c0 = LastItem(curves);
			const auto& c1 = FirstItem(curves);

			auto P0 = c0->LastCoord();
			auto P1 = c1->FirstCoord();

			if (P0.Distance(P1) >= theTol)
			{
				auto geom = Pln_CurveTools::MakeSegment(P0, P1);
				auto c = std::make_shared<TModel_ParaGapCurve>(++maxId, std::move(geom));

				newCurves.push_back(std::move(c));
			}
			newCurves.push_back(c1);
		}

		for (size_t i = 1; i < curves.size(); i++)
		{
			const auto& c0 = curves.at(i - 1);
			const auto& c1 = curves.at(i);

			Debug_Null_Pointer(c0);
			Debug_Null_Pointer(c1);

			auto P0 = c0->LastCoord();
			auto P1 = c1->FirstCoord();

			if (P0.Distance(P1) >= theTol)
			{
				auto geom = Pln_CurveTools::MakeSegment(P0, P1);
				auto c = std::make_shared<TModel_ParaGapCurve>(++maxId, std::move(geom));

				newCurves.push_back(std::move(c));
			}
			newCurves.push_back(c1);
		}
		auto wire = MakeWire(newCurves);
		return std::move(wire);
	}
}

std::shared_ptr<tnbLib::TModel_ParaWire> 
tnbLib::TModel_Tools::RepairWire
(
	const std::shared_ptr<TModel_ParaWire>& theWire, 
	const Standard_Real theTol
)
{
	Debug_Null_Pointer(theWire);
	auto geometries = RetrieveGeometries(*theWire);

	auto alg = std::make_shared<Cad2d_RepairWire>();
	Debug_Null_Pointer(alg);

	alg->SetCurves(std::move(geometries));
	alg->SetTolerance(theTol);

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the appplication is not performed!");

	const auto& gWire = alg->Wire();
	auto curves = MakeParaCurves(gWire);
	for (size_t i = 0; i < theWire->NbCurves(); i++)
	{
		Debug_Null_Pointer(theWire->Curves().at(i));
		auto id = theWire->Curves().at(i)->Index();
		curves.at(i)->SetIndex(id);
	}
	auto wire = MakeWire(curves);
	return std::move(wire);
}

std::shared_ptr<tnbLib::TModel_ParaWire> 
tnbLib::TModel_Tools::RemoveIntersections
(
	const std::shared_ptr<TModel_ParaWire>& theWire, 
	const Standard_Real theTol
)
{
	const auto& curves = theWire->Curves();
	if (curves.size() IS_EQUAL 1)
	{
		return theWire;
	}
	else
	{
		std::map<Standard_Integer, std::shared_ptr<TModel_ParaCurve>> reg;
		Standard_Integer id = 0;
		for (const auto& x : curves)
		{
			Debug_Null_Pointer(x);
			auto paired = std::make_pair(++id, x);
			auto insert = reg.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}
		}

		Debug_Null_Pointer(LastItem(curves));
		Debug_Null_Pointer(FirstItem(curves));

		const auto& c0 = LastItem(curves);
		const auto& c1 = FirstItem(curves);

		auto[trimmed0, trimmed1] = RepairIntersection(c0, c1, theTol);

		reg.at(1) = trimmed1;
		reg.at(curves.size()) = trimmed0;

		for (size_t i = 1; i < curves.size(); i++)
		{
			const auto& c0 = reg.at(i);
			const auto& c1 = reg.at(i + 1);

			Debug_Null_Pointer(c0);
			Debug_Null_Pointer(c1);

			auto[trimmed0, trimmed1] = RepairIntersection(c0, c1, theTol);

			reg.at(i) = trimmed0;
			reg.at(i + 1) = trimmed1;
		}

		std::vector<std::shared_ptr<TModel_ParaCurve>> trimmedCurves;
		trimmedCurves.reserve(curves.size());
		for (const auto& x : reg)
		{
			Debug_Null_Pointer(x.second);
			trimmedCurves.push_back(x.second);
		}

		auto wire = MakeWire(trimmedCurves);
		return std::move(wire);
	}
}

std::pair<std::shared_ptr<tnbLib::TModel_ParaCurve>, std::shared_ptr<tnbLib::TModel_ParaCurve>> 
tnbLib::TModel_Tools::RepairIntersection
(
	const std::shared_ptr<TModel_ParaCurve>& theC0,
	const std::shared_ptr<TModel_ParaCurve>& theC1,
	const Standard_Real theTol
)
{
	const auto& c0 = theC0->Curve();
	Debug_Null_Pointer(c0);
	const auto& c1 = theC1->Curve();
	Debug_Null_Pointer(c1);

	auto alg = Pln_Tools::Intersection(c0, c1, theTol);
	std::vector<Standard_Real> params0;
	std::vector<Standard_Real> params1;
	if (alg->NbPoints())
	{
		for (Standard_Integer i = 1; i <= alg->NbPoints(); i++)
		{
			auto p0 = alg->Intersector().Point(i).ParamOnFirst();
			auto p1 = alg->Intersector().Point(i).ParamOnSecond();

			params0.push_back(p0);
			params1.push_back(p1);
		}
	}
	if (alg->NbSegments())
	{
		for (Standard_Integer i = 1; i <= alg->NbSegments(); i++)
		{
			auto p0 = alg->Intersector().Segment(i).FirstPoint().ParamOnFirst();
			auto p1 = alg->Intersector().Segment(i).LastPoint().ParamOnSecond();

			params0.push_back(p0);
			params1.push_back(p1);
		}
	}

	if (params0.empty())
	{
		auto paired = std::make_pair(theC0, theC1);
		return std::move(paired);
	}

	std::sort(params0.begin(), params0.end());
	std::sort(params1.begin(), params1.end());

	{
		auto p0 = FirstItem(params0);
		if (p0 > theC0->LastParameter()) p0 = theC0->LastParameter();

		std::shared_ptr<TModel_ParaCurve> trimmed0;
		if (std::abs(p0 - theC0->LastParameter()) <= theTol)
		{
			trimmed0 = theC0;
		}
		else
		{
			trimmed0 = Trim(theC0, c0->FirstParameter(), p0);
		}
		if (NOT INSIDE(p0, theC0->FirstParameter(), theC0->LastParameter()))
		{
			FatalErrorIn(FunctionSIG)
				<< "something went wrong in intersection alg." << endl
				<< abort(FatalError);
		}

		auto p1 = LastItem(params1);
		if (p1 < theC1->FirstParameter()) p1 = theC1->FirstParameter();

		std::shared_ptr<TModel_ParaCurve> trimmed1;
		if (std::abs(p1 - theC1->FirstParameter()) <= theTol)
		{
			trimmed1 = theC1;
		}
		else
		{
			trimmed1 = Trim(theC1, p1, c1->LastParameter());
		}
		if (NOT INSIDE(p1, theC1->FirstParameter(), theC1->LastParameter()))
		{
			FatalErrorIn(FunctionSIG)
				<< "something went wrong in intersection alg." << endl
				<< abort(FatalError);
		}

		auto paired = std::make_pair(std::move(trimmed0), std::move(trimmed1));
		return std::move(paired);
	}
}