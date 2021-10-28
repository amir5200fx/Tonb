#include <StbGMaker_VolumeSailCreator_Shape.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::stbGmakerLib::VolumeSailCreator_Shape::VolumeSailCreator_Shape
(
	const std::shared_ptr<marineLib::Shape_Sail>& theShape
)
	: theShape_(theShape)
{
	// empty body
}

tnbLib::stbGmakerLib::VolumeSailCreator_Shape::VolumeSailCreator_Shape
(
	std::shared_ptr<marineLib::Shape_Sail>&& theShape
)
	: theShape_(std::move(theShape))
{
	// empty body
}

tnbLib::stbGmakerLib::VolumeSailCreator_Shape::VolumeSailCreator_Shape
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<marineLib::Shape_Sail>& theShape
)
	: StbGMaker_VolumeSailCreator(theIndex)
	, theShape_(theShape)
{
	// empty body
}

tnbLib::stbGmakerLib::VolumeSailCreator_Shape::VolumeSailCreator_Shape
(
	const Standard_Integer theIndex, 
	std::shared_ptr<marineLib::Shape_Sail>&& theShape
)
	: StbGMaker_VolumeSailCreator(theIndex)
	, theShape_(std::move(theShape)) 
{
	// empty body
}

tnbLib::stbGmakerLib::VolumeSailCreator_Shape::VolumeSailCreator_Shape
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<marineLib::Shape_Sail>& theShape
)
	: StbGMaker_VolumeSailCreator(theIndex, theName)
	, theShape_(theShape)
{
	// empty body
}

tnbLib::stbGmakerLib::VolumeSailCreator_Shape::VolumeSailCreator_Shape
(
	const Standard_Integer theIndex,
	const word & theName,
	std::shared_ptr<marineLib::Shape_Sail>&& theShape
)
	: StbGMaker_VolumeSailCreator(theIndex, theName)
	, theShape_(std::move(theShape))
{
	// empty body
}

#include <Marine_Shapes.hxx>
#include <Geo_xDistb.hxx>

Standard_Integer 
tnbLib::stbGmakerLib::VolumeSailCreator_Shape::CreateWorkingPlane
(
	const Standard_Real x
)
{
	Debug_Null_Pointer(Shape());
	return StbGMaker_Alg::CreateWpFromShape(Shape()->Shape(), x, Marine_SectionType::sail);
}

typename tnbLib::stbGmakerLib::sailCreatorType 
tnbLib::stbGmakerLib::VolumeSailCreator_Shape::Type() const
{
	return stbGmakerLib::sailCreatorType::shape;
}

#include <StbGMaker_WP.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>

void tnbLib::stbGmakerLib::VolumeSailCreator_Shape::ExportAs
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
				Marine_SectionType::sail
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
			Marine_BodyType::sail
		);
	Debug_Null_Pointer(body);

	Debug_If_Condition(body->Type() NOT_EQUAL Marine_BodyType::sail);
	auto sail = std::dynamic_pointer_cast<marineLib::Body_Sail>(body);
	Debug_Null_Pointer(sail);

	theModel = std::make_shared<marineLib::Model_BodySail>
		(
			Index(),
			Name(),
			std::move(sail)
			);
}