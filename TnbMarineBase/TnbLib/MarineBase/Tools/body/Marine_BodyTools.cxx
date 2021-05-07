#include <Marine_BodyTools.hxx>

#include <Cad2d_Modeler.hxx>
#include <Cad_Tools.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Marine_Water.hxx>
#include <Marine_BooleanOps.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_Wave.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_SectTools.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_Shape.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif

#include <Geom_Plane.hxx>
#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>

tnbLib::Entity3d_Box 
tnbLib::Marine_BodyTools::BoundingBox
(
	const Marine_Body & theBody
)
{
	const auto& sections = theBody.Sections();
	auto b3 = MarineBase_Tools::CalcBoundingBox(sections);
	return std::move(b3);
}

Standard_Boolean 
tnbLib::Marine_BodyTools::IsWetted
(
	const Marine_Body & theBody
)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::wetted;
}

Standard_Boolean 
tnbLib::Marine_BodyTools::IsDry
(
	const Marine_Body & theBody
)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::dry;
}

Standard_Boolean 
tnbLib::Marine_BodyTools::IsTank
(
	const Marine_Body & theBody
)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::tank;
}

Standard_Boolean 
tnbLib::Marine_BodyTools::IsSail
(
	const Marine_Body & theBody
)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::sail;
}

Standard_Boolean 
tnbLib::Marine_BodyTools::IsDisplacer
(
	const Marine_Body & theBody
)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::displacer;
}

Standard_Real 
tnbLib::Marine_BodyTools::CalcLateralArea
(
	const std::shared_ptr<Marine_Body>& theBody,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	if (NOT theBody)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is null" << endl
			<< abort(FatalError);
	}
	auto areaQ = MarineBase_Tools::CalcLateralArea(theBody->Sections());
	auto area = MarineBase_Tools::CalcArea(areaQ, theInfo);
	return area;
}

Standard_Real 
tnbLib::Marine_BodyTools::CalcLateralZbar
(
	const std::shared_ptr<Marine_Body>& theBody,
	const Standard_Real z0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	if (NOT theBody)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is null" << endl
			<< abort(FatalError);
	}
	auto zBarQ = MarineBase_Tools::CalcLateralZbar(theBody->Sections(), z0);
	auto zBar = MarineBase_Tools::CalcArea(zBarQ, theInfo);
	return zBar;
}

Standard_Real 
tnbLib::Marine_BodyTools::CalcVolume
(
	const Marine_Body & theBody,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	auto volQ = MarineBase_Tools::CalcVolume(theBody.Sections(), theInfo);
	auto vol = MarineBase_Tools::CalcArea(volQ, theInfo);
	return vol;
}

std::shared_ptr<tnbLib::marineLib::Body_Wetted> 
tnbLib::Marine_BodyTools::WettedBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto wetted = std::dynamic_pointer_cast<marineLib::Body_Wetted>(theBody);
	if (NOT wetted)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not wetted!" << endl
			<< abort(FatalError);
	}
	return std::move(wetted);
}

std::shared_ptr<tnbLib::marineLib::Body_Dry> 
tnbLib::Marine_BodyTools::DryBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto dry = std::dynamic_pointer_cast<marineLib::Body_Dry>(theBody);
	if (NOT dry)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not dry!" << endl
			<< abort(FatalError);
	}
	return std::move(dry);
}

std::shared_ptr<tnbLib::marineLib::Body_Tank> 
tnbLib::Marine_BodyTools::TankBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto tank = std::dynamic_pointer_cast<marineLib::Body_Tank>(theBody);
	if (NOT tank)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not tank!" << endl
			<< abort(FatalError);
	}
	return std::move(tank);
}

std::shared_ptr<tnbLib::marineLib::Body_Sail> 
tnbLib::Marine_BodyTools::SailBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto sail = std::dynamic_pointer_cast<marineLib::Body_Sail>(theBody);
	if (NOT sail)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not sail!" << endl
			<< abort(FatalError);
	}
	return std::move(sail);
}

std::shared_ptr<tnbLib::marineLib::Body_Displacer> 
tnbLib::Marine_BodyTools::DisplacerBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto displacer = std::dynamic_pointer_cast<marineLib::Body_Displacer>(theBody);
	if (NOT displacer)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not displacer!" << endl
			<< abort(FatalError);
	}
	return std::move(displacer);
}

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::Marine_BodyTools::BodyCreator
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const Marine_BodyType t
)
{
	CheckTypeConsistency(theSections);

	switch (t)
	{
	case Marine_BodyType::displacer:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = 
			std::make_shared
			<
			marineLib::BodyConstructor_noShape<marineLib::Body_Displacer>
			>(std::move(sections));
		Debug_Null_Pointer(body);
		return std::move(body);
	}
	case Marine_BodyType::dry:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = 
			std::make_shared
			<
			marineLib::BodyConstructor_noShape<marineLib::Body_Dry>
			>(std::move(sections));
		Debug_Null_Pointer(body);
		return std::move(body);
	}
	case Marine_BodyType::wetted:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = 
			std::make_shared
			<
			marineLib::BodyConstructor_noShape<marineLib::Body_Wetted>
			>(std::move(sections));
		Debug_Null_Pointer(body);
		return std::move(body);
	}
	case Marine_BodyType::sail:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = std::make_shared
			<
			marineLib::BodyConstructor_noShape<marineLib::Body_Sail>
			>(std::move(sections));
		Debug_Null_Pointer(body);
		return std::move(body);
	}
	case Marine_BodyType::tank:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = 
			std::make_shared
			<
			marineLib::BodyConstructor_noShape<marineLib::Body_Tank>
			>(std::move(sections));
		Debug_Null_Pointer(body);
		return std::move(body);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "Wrong body type!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::Marine_BodyTools::BodyCreator
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const std::shared_ptr<Marine_Shape>& theShape, 
	const Marine_BodyType t
)
{
	CheckTypeConsistency(theSections);

	switch (t)
	{
	case Marine_BodyType::displacer:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = 
			std::make_shared
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>
			>(std::move(sections));
		Debug_Null_Pointer(body);

		body->SetShape(theShape);
		return std::move(body);
	}
	case Marine_BodyType::dry:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = 
			std::make_shared
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Dry>
			>(std::move(sections));
		Debug_Null_Pointer(body);

		body->SetShape(theShape);
		return std::move(body);
	}
	case Marine_BodyType::wetted:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = 
			std::make_shared
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>
			>(std::move(sections));
		Debug_Null_Pointer(body);

		body->SetShape(theShape);
		return std::move(body);
	}
	case Marine_BodyType::sail:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = 
			std::make_shared
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Sail>
			>(std::move(sections));
		Debug_Null_Pointer(body);

		body->SetShape(theShape);
		return std::move(body);
	}
	case Marine_BodyType::tank:
	{
		//auto& sections = body->ChangeSections();
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		auto body = 
			std::make_shared
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Tank>
			>(std::move(sections));
		Debug_Null_Pointer(body);

		body->SetShape(theShape);
		return std::move(body);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "Wrong body type!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::Marine_BodyTools::WettedBody
(
	const std::shared_ptr<marineLib::Body_Displacer>& theBody,
	const std::shared_ptr<Marine_WaterDomain>& theDomain
)
{
	Debug_Null_Pointer(theBody);
	Debug_Null_Pointer(theDomain);
	Debug_Null_Pointer(theDomain->Water());
	auto sections = 
		Marine_BooleanOps::WettedSections
		(
			theBody->Sections(), 
			theDomain->Water()->Sections()
		);

	if (sections.empty())
	{
		return nullptr;
	}

	if (theBody->ShapeType())
	{
		auto t = 
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>
			>(theBody);
		Debug_Null_Pointer(t);

		auto body = BodyCreator(sections, t->Shape(), Marine_BodyType::wetted);
		auto wetted = std::dynamic_pointer_cast<marineLib::Body_Wetted>(body);
		Debug_Null_Pointer(wetted);
		wetted->SetDisplacer(theBody);

		auto shapeBody = std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape
			<
			marineLib::Body_Wetted
			>
			>(body);
		Debug_Null_Pointer(shapeBody);
		Marine_BodyTools::WaterSectionOnBody
		(
			shapeBody,
			theDomain
		);
		return std::move(body);
	}
	else
	{
		auto body = BodyCreator(sections, Marine_BodyType::wetted);
		auto wetted = std::dynamic_pointer_cast<marineLib::Body_Wetted>(body);
		Debug_Null_Pointer(wetted);
		wetted->SetDisplacer(theBody);
		return std::move(body);
	}	
}

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::Marine_BodyTools::DryBody
(
	const std::shared_ptr<marineLib::Body_Displacer>& theBody,
	const std::shared_ptr<Marine_WaterDomain>& theDomain
)
{
	Debug_Null_Pointer(theBody);
	Debug_Null_Pointer(theDomain);
	Debug_Null_Pointer(theDomain->Water());

	auto sections =
		Marine_BooleanOps::DrySections
		(
			theBody->Sections(),
			theDomain->Water()->Sections()
		);

	if (theBody->ShapeType())
	{
		auto t =
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>
			>(theBody);
		Debug_Null_Pointer(t);

		auto wetted = BodyCreator(sections, t->Shape(), Marine_BodyType::dry);
		return std::move(wetted);
	}
	else
	{
		auto dry = BodyCreator(sections, Marine_BodyType::dry);
		return std::move(dry);
	}	
}

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::Marine_BodyTools::RetrieveLateralArea
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto tri = MarineBase_Tools::RetrieveLateralArea(theBody->Sections());
	return std::move(tri);
}

namespace tnbLib
{
	Entity2d_Box CalcBoundingBox
	(
		const std::vector<std::shared_ptr<Pln_Curve>>& curves
	)
	{
		auto iter = curves.begin();
		auto b = (*iter)->BoundingBox(0);

		iter++;
		while (iter NOT_EQUAL curves.end())
		{
			b = Entity2d_Box::Union(b, (*iter)->BoundingBox(0));
			iter++;
		}
		return std::move(b);
	}
}

void tnbLib::Marine_BodyTools::WaterSectionOnBody
(
	const std::shared_ptr<marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>>& theBody,
	const std::shared_ptr<Marine_WaterDomain>& theDomain
)
{
	Debug_Null_Pointer(theBody);
	Debug_Null_Pointer(theDomain);
	Debug_Null_Pointer(theDomain->Wave());

	const auto& shape = theBody->Shape();
	Debug_Null_Pointer(shape);

	const auto& wave = theDomain->Wave();
	const auto& surfaceG = wave->SurfaceGeometry();
	Debug_Null_Pointer(surfaceG);

	BRepAlgoAPI_Section alg;
	alg.ComputePCurveOn1(Standard_True);
	alg.SetRunParallel(Standard_True);
	
	alg.Init2(shape->Shape());
	alg.Approximation(Standard_True);

	auto flat = std::dynamic_pointer_cast<Marine_FlatWave>(wave);
	if (flat)
	{
		alg.Init1(gp_Pln(wave->PointOnWater(), wave->VerticalDirection()));
	}
	else
	{
		alg.Init1(wave->SurfaceGeometry());
	}

	alg.Build();

	if (alg.Shape().IsNull())
	{
		return;
	}

	auto tedges = Cad_Tools::RetrieveEdges(alg.Shape());
	
	std::vector<Handle(Geom2d_Curve)> paraCurves;
	if (flat)
	{
		paraCurves = Cad_Tools::RetrieveParaCurves
		(
			tedges,
			gp_Ax2(wave->PointOnWater(), wave->VerticalDirection())
		);
	}
	else
	{
		paraCurves = Cad_Tools::RetrieveParaCurves
		(
			tedges,
			wave->SurfaceGeometry()
		);
	}
	/*auto curves =
		Pln_Tools::RetrieveCurves
		(
			paraCurves
		);
	cout << "curve size = " << curves.size() << std::endl;
	for (const auto& x : curves)
	{
		cout << x->FirstCoord() << std::endl;
		cout << x->LastCoord() << std::endl;
		cout << std::endl;

	}

	const auto b = CalcBoundingBox(curves);*/

	//auto curves = Pln_Tools::RetrieveCurves(paraCurves);
	auto curves = Marine_SectTools::CurveCreator(paraCurves, Marine_SectionType::waterLine);
	auto edges = Pln_Tools::RetrieveMergedEdges(curves, 1.0e-3, 1.0e-6);

	/*auto modeler = std::make_shared<Cad2d_Modeler>();
	modeler->Import(edges);

	Cad2d_Modeler::selctList l;
	modeler->SelectAll(l);
	modeler->MakePlane(l);*/
	//PAUSE;
	//auto cedges = Pln_Tools::MakeConsecutive(edges, 1.0e-3);

	auto wires = Pln_Tools::RetrieveWiresNonManifold(edges);
	auto planes = 
		Pln_Tools::RetrievePlanes
		(
			wires,
			gp_Ax2(wave->PointOnWater(), wave->VerticalDirection())
		);

	std::vector<std::shared_ptr<Marine_Section>> sections;
	sections.reserve(planes.size());
	for (const auto& x : planes)
	{
		Debug_Null_Pointer(x);
		auto sect = 
			Marine_SectTools::ConvertToSection
			(
				x,
				Marine_SectionType::waterLine
			);
		Debug_Null_Pointer(sect);
		sections.push_back(std::move(sect));
	}

	auto cmpSect = Marine_SectTools::CmpSectionCreator(sections);
	Debug_Null_Pointer(cmpSect);
	
	cmpSect->SetLocation(wave->PointOnWater());
	theBody->SetWL(std::move(cmpSect));
}

void tnbLib::Marine_BodyTools::Heel
(
	const std::shared_ptr<Marine_Body>& theBody, 
	const gp_Ax1& theAx, 
	const Standard_Real theAngle
)
{
#ifdef _DEBUG
	CheckTypeConsistency(*theBody);
#endif // _DEBUG
	const auto& sections = theBody->Sections();
	MarineBase_Tools::Heel(sections, theAx, theAngle);
}

void tnbLib::Marine_BodyTools::Heel(const std::shared_ptr<Marine_Body>& theBody, const gp_Ax2d& theAx)
{
#ifdef _DEBUG
	CheckTypeConsistency(*theBody);
#endif // _DEBUG
	const auto& sections = theBody->Sections();
	MarineBase_Tools::Heel(sections, theAx);
}

void tnbLib::Marine_BodyTools::CheckTypeConsistency
(
	const Marine_Body & theBody
)
{
	CheckTypeConsistency(theBody.Sections());
}

void tnbLib::Marine_BodyTools::CheckTypeConsistency
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
{
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		Marine_SectTools::CheckTypeConsistency(*x);
	}
}