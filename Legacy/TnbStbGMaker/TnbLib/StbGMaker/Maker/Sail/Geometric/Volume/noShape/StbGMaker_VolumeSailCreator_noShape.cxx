#include <StbGMaker_VolumeSailCreator_noShape.hxx>

tnbLib::stbGmakerLib::VolumeSailCreator_noShape::VolumeSailCreator_noShape
(
	const Standard_Integer theIndex,
	const word & theName
)
	: StbGMaker_VolumeSailCreator(theIndex, theName)
{
	// empty body
}

Standard_Integer 
tnbLib::stbGmakerLib::VolumeSailCreator_noShape::CreateWorkingPlane
(
	const Standard_Real x
)
{
	return StbGMaker_Alg::CreateWorkingPlane(x);
}

tnbLib::stbGmakerLib::sailCreatorType 
tnbLib::stbGmakerLib::VolumeSailCreator_noShape::Type() const
{
	return stbGmakerLib::sailCreatorType::noShape;
}

#include <StbGMaker_WP.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>

void tnbLib::stbGmakerLib::VolumeSailCreator_noShape::ExportAs
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