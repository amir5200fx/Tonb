#include <StbGMaker_TankCreator_Shape.hxx>

#include <Marine_Shapes.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::stbGmakerLib::TankCreator_Shape::TankCreator_Shape
(
	const std::shared_ptr<marineLib::Shape_Tank>& theTank
)
	: theTank_(theTank)
{
	// empty body
}

tnbLib::stbGmakerLib::TankCreator_Shape::TankCreator_Shape
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<marineLib::Shape_Tank>& theTank
)
	: StbGMaker_TankCreator(theIndex, theName)
	, theTank_(theTank)
{
	// empty body
}

Standard_Integer 
tnbLib::stbGmakerLib::TankCreator_Shape::CreateWorkingPlane
(
	const Standard_Real x
)
{
	Debug_Null_Pointer(Shape());
	return CreateWpFromShape(Shape()->Shape(), x, Marine_SectionType::tank);
}

#include <Cad2d_Plane.hxx>
#include <StbGMaker_WP.hxx>
#include <Marine_Model_Tank.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>

void tnbLib::stbGmakerLib::TankCreator_Shape::ExportAs
(
	std::shared_ptr<Marine_Model>& theModel
) const
{
	auto WPs = RetrieveWPs();
	SortWPs(WPs);

	std::vector<std::shared_ptr<Marine_CmpSection>> cmpSections;
	cmpSections.reserve(WPs.size());

	for (const auto& x : WPs)
	{
		Debug_Null_Pointer(x);
		if (NOT x->NbPlanes())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "there is no plane to construct a section" << endl
				<< abort(FatalError);
		}

		std::vector<std::shared_ptr<Marine_Section>> sections;
		sections.reserve(x->NbPlanes());
		
		const auto planes = x->RetrievePlanes();
		for (const auto& pl : planes)
		{
			Debug_Null_Pointer(pl);

			auto sect = Marine_SectTools::ConvertToSection
			(
				pl,
				Marine_SectionType::tank
			);
			Debug_Null_Pointer(sect);
			
			sections.push_back(std::move(sect));
		}

		auto cmpSect = Marine_SectTools::CmpSectionCreator(sections);
		Debug_Null_Pointer(cmpSect);

		Marine_SectTools::SetLocation(cmpSect, x->X());

		cmpSections.push_back(std::move(cmpSect));
	}

	auto body =
		Marine_BodyTools::BodyCreator
		(
			cmpSections,
			Shape(),
			Marine_BodyType::tank
		);
	Debug_Null_Pointer(body);

	Debug_If_Condition(body->Type() NOT_EQUAL Marine_BodyType::tank);
	auto tank = std::dynamic_pointer_cast<marineLib::Body_Tank>(body);
	Debug_Null_Pointer(tank);

	theModel = std::make_shared<marineLib::Model_Tank>
		(
			Index(),
			Name(),
			std::move(tank)
			);
}