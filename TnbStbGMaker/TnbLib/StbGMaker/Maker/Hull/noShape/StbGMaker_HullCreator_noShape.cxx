#include <StbGMaker_HullCreator_noShape.hxx>

tnbLib::stbGmakerLib::HullCreator_noShape::HullCreator_noShape()
{
	// empty body
}

tnbLib::stbGmakerLib::HullCreator_noShape::HullCreator_noShape
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: StbGMaker_HullCreator(theIndex, theName)
{
	// empty body
}

Standard_Integer 
tnbLib::stbGmakerLib::HullCreator_noShape::CreateWorkingPlane
(
	const Standard_Real x
)
{
	return StbGMaker_Alg::CreateWorkingPlane(x);
}

#include <Cad2d_Plane.hxx>
#include <StbGMaker_WP.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Model_Hull.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>

void tnbLib::stbGmakerLib::HullCreator_noShape::ExportAs
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
				Marine_SectionType::displacer
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
			Marine_BodyType::displacer
		);
	Debug_Null_Pointer(body);

	Debug_If_Condition(body->Type() NOT_EQUAL Marine_BodyType::displacer);
	auto displacer = std::dynamic_pointer_cast<marineLib::Body_Displacer>(body);
	Debug_Null_Pointer(displacer);

	theModel = std::make_shared<marineLib::Model_Hull>
		(
			Index(),
			Name(),
			std::move(displacer)
			);
}