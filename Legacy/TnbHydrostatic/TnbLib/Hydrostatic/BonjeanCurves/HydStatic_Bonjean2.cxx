#include <HydStatic_Bonjean2.hxx>

#include <HydStatic_HydOffsetCurve.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Body.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>
#include <Marine_WaterTools.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_BooleanOps.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_System.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	const unsigned int HydStatic_Bonjean2::DEFAULT_NB_LEVELS(15);
	const unsigned int HydStatic_Bonjean2::MIN_NB_LEVELS(10);
	unsigned short HydStatic_Bonjean2::verbose(0);

	std::shared_ptr<NumAlg_AdaptiveInteg_Info> HydStatic_Bonjean2::integInfo = sysLib::gl_marine_integration_info;
}

namespace tnbLib
{
	auto CalcSpanZ(const std::shared_ptr<Marine_CmpSection>& section)
	{
		Debug_Null_Pointer(section);
		auto b = section->BoundingBox();
		auto z0 = b.P0().Y();
		auto z1 = b.P1().Y();
		auto t = std::make_pair(z0, z1);
		return std::move(t);
	}

	auto CalcArea(const std::shared_ptr<Marine_CmpSection>& section)
	{
		Standard_Real sum = 0;
		for (const auto& x : section->Sections())
		{
			Debug_Null_Pointer(x);
			auto area = MarineBase_Tools::CalcArea(x, HydStatic_Bonjean2::integInfo);

			Debug_If_Condition(area < 0);
			sum += area;
		}
		return sum;
	}

	auto CalcSectionCurve
	(
		const Entity3d_Box& domain,
		const std::shared_ptr<Marine_CmpSection>& section, 
		const std::shared_ptr<Geo_xDistb>& dist
	)
	{
		const auto y0 = domain.P0().Z();

		const auto x0 = domain.P0().Y();
		const auto x1 = domain.P1().Y();

		const auto z0 = dist->Lower();

		const auto nbLevels = dist->Size();
		std::vector<std::pair<Standard_Real, Standard_Real>> As;
		As.reserve(nbLevels);

		for (auto z : dist->Values())
		{
			if (std::abs(z - z0) <= gp::Resolution())
			{
				//auto t = std::make_pair(0.0, z0);
				//As.push_back(std::move(t));
				continue;
			}
			auto y1 = z;

			auto wa = Marine_WaterTools::WaterSection(Pnt2d(x0, y0), Pnt2d(x1, y1));
			Debug_Null_Pointer(wa);

			auto water =
				Marine_SectTools::SectionCreator
				(
					wa,
					Marine_SectionType::water
				);
			Debug_Null_Pointer(water);

			auto wettedSections = Marine_BooleanOps::WettedSection(section, water);
			auto area = CalcArea(wettedSections);
			//std::cout << "z = " << z << ", area: " << area << std::endl;
			auto t = std::make_pair(area, z);
			As.push_back(std::move(t));		
		}
		auto curve = std::make_shared<HydStatic_HydOffsetCurve>(std::move(As));
		return std::move(curve);
	}
}

std::shared_ptr<tnbLib::Geo_xDistb> 
tnbLib::HydStatic_Bonjean2::CreateDistribution
(
	const std::shared_ptr<Marine_CmpSection>& theSection
) const
{
	const auto[z0, z1] = CalcSpanZ(theSection);
	switch (theLevDistb_)
	{
	case tnbLib::HydStatic_Bonjean2::levDistb::uniform:
	{
		auto distb = std::make_shared<Geo_UniDistb>(NbLevels());
		Debug_Null_Pointer(distb);
		distb->SetLower(z0);
		distb->SetUpper(z1);

		distb->Perform();
		Debug_If_Condition_Message(NOT distb->IsDone(), "the algorithm is not performed!");
		return std::move(distb);
		break;
	}
	case tnbLib::HydStatic_Bonjean2::levDistb::cosine:
	{
		auto distb = std::make_shared<Geo_CosineDistb>(NbLevels());
		Debug_Null_Pointer(distb);
		distb->SetLower(z0);
		distb->SetUpper(z1);

		distb->Perform();
		Debug_If_Condition_Message(NOT distb->IsDone(), "the algorithm is not performed!");
		return std::move(distb);
		break;
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "unrecognized type of distb algorithm has been detected!" << endl
			<< abort(FatalError);
		return std::make_shared<Geo_CosineDistb>(NbLevels());
		break;
	}
}

void tnbLib::HydStatic_Bonjean2::Perform()
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Calculating Bonjean Curves ********" << endl;
		Info << endl;
	}

	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< "no domain has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Body())
	{
		FatalErrorIn(FunctionSIG)
			<< "no body has been found!" << endl
			<< abort(FatalError);
	}

	if (NbLevels() < MIN_NB_LEVELS)
	{
		FatalErrorIn(FunctionSIG)
			<< "nb. of levels is insufficient" << endl
			<< "- the acceptable nb of levels is " << MIN_NB_LEVELS << " or more." << endl
			<< "- current nb of levels:" << NbLevels() << endl
			<< abort(FatalError);
	}

	const auto& body = Body();
	if (verbose)
	{
		Info << " Body's name: " << body->Name() << endl;
		Info << " nb. of sections: " << body->NbSections() << endl;
	}

	const auto& sections = body->Sections();
	if (sections.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section has been found in the body!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Domain()->Dim());
	const auto& domain = *Domain()->Dim();

	std::vector<std::shared_ptr<bonjeanEntity>> entities;
	entities.reserve(sections.size());
	for (const auto& x : sections)
	{
		Debug_Null_Pointer(x);

		if (verbose)
		{
			Info << " - section nb. " << x->Index() << endl;
		}

		auto curve = CalcSectionCurve(domain, x, CreateDistribution(x));
		Debug_Null_Pointer(curve);

		auto sect = x;
		auto ent = std::make_shared<bonjeanEntity>(std::move(sect), std::move(curve));
		entities.push_back(std::move(ent));
	}
	theSections_ = std::move(entities);
	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of Calculating Bonjean Curves ********" << endl;
		Info << endl;
	}
}