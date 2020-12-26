#include <Marine_MidSection.hxx>

#include <Marine_Bodies.hxx>
#include <Marine_DisctTools.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_WaterTools.hxx>
#include <Marine_Shape.hxx>
#include <Marine_Sections.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_BooleanOps.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TopoDS_Shape.hxx>

tnbLib::Marine_MidSection::Marine_MidSection
(
	const std::shared_ptr<marineLib::Body_Displacer>& theDisplacer, 
	const std::shared_ptr<marineLib::Body_Wetted>& theBody,
	const std::shared_ptr<Marine_Wave>& theWave
)
	: theDisplacer_(theDisplacer)
	, theBody_(theBody)
	, theWave_(theWave)
	, theMinTol_(1.0E-4)
	, theMaxTol_(1.0E-4)
{
	// empty body
}

Standard_Boolean 
tnbLib::Marine_MidSection::HasShape() const
{
	Debug_Null_Pointer(Displacer());
	return Displacer()->ShapeType();
}

void tnbLib::Marine_MidSection::ApplyAt(const Standard_Real x)
{
	Debug_Null_Pointer(Displacer());
	Debug_Null_Pointer(Body());
	Debug_Null_Pointer(Wave());

	if (NOT HasShape())
	{
		Info << "retrieving the midship section for the non-shape body is not performed yet!" << endl;
		NotImplemented;
		return;
	}

	const auto& sys = Displacer()->CoordinateSystem();
	gp_Ax2 syst0(sys.Location(), sys.XDirection(), sys.YDirection());

	auto x0 = syst0.Location().Z();
	auto syst = syst0.Translated(gp_Vec(x - x0, 0, 0));

	auto displacer = 
		std::dynamic_pointer_cast
		<
		marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>
		>(Displacer());
	Debug_Null_Pointer(displacer);

	const auto& marineShape = displacer->Shape();
	Debug_Null_Pointer(marineShape);

	auto sectionShape = 
		Marine_DisctTools::Section(marineShape->Shape(), syst);
	if (sectionShape.IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section has been retrieved from the displacer" << endl
			<< abort(FatalError);
	}

	auto section =
		Marine_SectTools::CmpSectionCreator
		(
			Marine_SectTools::SectionCreator
			(
				sectionShape, syst,
				Marine_SectionType::wetted,
				MinTol(), MaxTol()
			));
	Debug_Null_Pointer(section);

	auto water = 
		Marine_WaterTools::WaterSection
		(
			*Wave(), *section, 
			MinTol(), MaxTol()
		);
	Debug_Null_Pointer(water);

	auto wetted = Marine_BooleanOps::WettedSection(section, water);
	if (NOT wetted)
	{
		FatalErrorIn(FunctionSIG)
			<< "something went wrong! there is no intersection between section and water" << endl
			<< abort(FatalError);
	}

	wetted->SetName("MidShip Section");
	wetted->SetCoordinateSystem(section->CoordinateSystem());

	Body()->SetMid(std::move(wetted));
}