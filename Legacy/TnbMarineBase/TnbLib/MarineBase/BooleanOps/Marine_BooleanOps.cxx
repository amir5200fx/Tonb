#include <Marine_BooleanOps.hxx>

#include <Cad2d_Boolean.hxx>
#include <Pln_Tools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>
#include <Marine_Sections.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_PlnCurve.hxx>
#include <MarineBase_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef _SaveData
#include <filesystem>
#endif // _SaveData


//#ifdef _DEBUG
//#ifdef _PLOT
//namespace tnbLib
//{
//	OFstream myBooleanOpsSectionViewFile(fileName("wettedSection_handler.plt"));
//}
//#endif // _PLOT
//#endif // _DEBUG

unsigned short tnbLib::Marine_BooleanOps::verbose(0);

std::shared_ptr<tnbLib::Marine_Section>
tnbLib::Marine_BooleanOps::Union
(
	const std::shared_ptr<Marine_Section>& theSect0, 
	const std::shared_ptr<Marine_Section>& theSect1
)
{
	Debug_Null_Pointer(theSect0);
	Debug_Null_Pointer(theSect1);

	if (theSect0->Type() NOT_EQUAL theSect1->Type())
	{
		FatalErrorIn(FunctionSIG)
			<< "the sections must be in the same type!" << endl
			<< abort(FatalError);
	}

	auto plane0 = Marine_SectTools::ConvertToPlane(theSect0);
	Debug_Null_Pointer(plane0);

	auto plane1 = Marine_SectTools::ConvertToPlane(theSect1);
	Debug_Null_Pointer(plane1);

	auto sum = Cad2d_Boolean::Union(plane0, plane1);
	if (sum)
	{
		auto sect = Marine_SectTools::ConvertToSection(sum, theSect0->Type());
		Debug_Null_Pointer(sect);

		return std::move(sect);
	}
	else
	{
		return nullptr;
	}
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_BooleanOps::Subtract
(
	const std::shared_ptr<Marine_Section>& theSect0,
	const std::shared_ptr<Marine_Section>& theSect1
)
{
	Debug_Null_Pointer(theSect0);
	Debug_Null_Pointer(theSect1);

	if (theSect0->Type() NOT_EQUAL theSect1->Type())
	{
		FatalErrorIn(FunctionSIG)
			<< "the sections must be in the same type!" << endl
			<< abort(FatalError);
	}

	auto plane0 = Marine_SectTools::ConvertToPlane(theSect0);
	Debug_Null_Pointer(plane0);

	auto plane1 = Marine_SectTools::ConvertToPlane(theSect1);
	Debug_Null_Pointer(plane1);

	auto sum = Cad2d_Boolean::Subtract(plane0, plane1);

	std::vector<std::shared_ptr<Marine_Section>> sections;
	sections.reserve(sum.size());
	for (const auto& x : sum)
	{
		auto sect = Marine_SectTools::ConvertToSection(x, theSect0->Type());
		Debug_Null_Pointer(sect);

		sections.push_back(std::move(sect));
	}
	return std::move(sections);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_BooleanOps::Intersection
(
	const std::shared_ptr<Marine_Section>& theSect0, 
	const std::shared_ptr<Marine_Section>& theSect1
)
{
	Debug_Null_Pointer(theSect0);
	Debug_Null_Pointer(theSect1);

	if (theSect0->Type() NOT_EQUAL theSect1->Type())
	{
		FatalErrorIn(FunctionSIG)
			<< "the sections must be in the same type!" << endl
			<< abort(FatalError);
	}

	auto plane0 = Marine_SectTools::ConvertToPlane(theSect0);
	Debug_Null_Pointer(plane0);

	auto plane1 = Marine_SectTools::ConvertToPlane(theSect1);
	Debug_Null_Pointer(plane1);

	auto sum = Cad2d_Boolean::Intersection(plane0, plane1);

	std::vector<std::shared_ptr<Marine_Section>> sections;
	sections.reserve(sum.size());
	for (const auto& x : sum)
	{
		auto sect = Marine_SectTools::ConvertToSection(x, theSect0->Type());
		Debug_Null_Pointer(sect);

		sections.push_back(std::move(sect));
	}
	return std::move(sections);
}

#include <Cad2d_Plane.hxx>
#include <Marine_SectTools.hxx>

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_BooleanOps::WettedSection
(
	const std::shared_ptr<Pln_Wire>& theSection,
	const std::shared_ptr<Pln_Wire>& theWater,
	const marineLib::curveType targetSection
)
{
	if (verbose)
	{
		Info << endl
			<< " Entering into the function:" << endl
			<< FunctionSIG << endl;
	}
#ifdef _DEBUG
	Pln_Tools::CheckManifold(theSection);
	Pln_Tools::CheckManifold(theWater);
#endif // _DEBUG

	Pln_Tools::SetPrecision(theSection);
	Pln_Tools::SetPrecision(theWater);

	if (verbose)
	{
		Info << endl
			<< " Making a plane from the section wire" << endl;
	}

	auto section = Cad2d_Plane::MakePlane(theSection, nullptr);
	Debug_Null_Pointer(section);

	if (verbose)
	{
		Info << endl
			<< " Making a plane from the water wire" << endl;
	}

	auto water = Cad2d_Plane::MakePlane(theWater, nullptr);
	Debug_Null_Pointer(water);

	if (verbose)
	{
		Info << endl
			<< " Calculating the intersection between the section and the water plane" << endl;
	}

	std::vector<std::shared_ptr<Cad2d_Plane>> planes;
#ifdef _DEBUG
	try
	{
		planes = Cad2d_Boolean::Intersection(section, water);
	}
	catch (const error&)
	{
#ifdef _SaveData
		{//- saving scope
			size_t i = 0;
			const auto name = "plane";
			const auto folder = "results_booleanOps/" + std::to_string(i);
			std::string address = ".\\results_booleanOps\\" + std::to_string(i) + "\\" + name;
			//boost::filesystem::path dir(folder);
			std::filesystem::create_directories(folder);

			fileName fn(address);

			std::ofstream myFile(fn);
			TNB_oARCH_FILE_TYPE ar(myFile);
			ar << section;
	}

		{//- saving scope
			size_t i = 1;
			const auto name = "plane";
			const auto folder = "results_booleanOps/" + std::to_string(i);
			std::string address = ".\\results_booleanOps\\" + std::to_string(i) + "\\" + name;
			//boost::filesystem::path dir(folder);
			std::filesystem::create_directories(folder);

			fileName fn(address);

			std::ofstream myFile(fn);
			TNB_oARCH_FILE_TYPE ar(myFile);
			ar << water;
		}
		std::exit(1);
#else
		FatalErrorIn(FunctionSIG)
			<< "unable to retrieve wetted section" << endl
			<< abort(FatalError);
#endif // _SaveData

	}
#else
	planes = Cad2d_Boolean::Intersection(section, water);
#endif // _DEBUG
	
	if (planes.empty())
	{
		if (verbose)
		{
			Info << endl
				<< " no intersection has been found!" << endl
				<< " leaving the function" << endl;
		}
		return std::vector<std::shared_ptr<Marine_Section>>();
	}

	if (verbose)
	{
		Info << endl
			<< " nb. of planes: " << planes.size() << endl;
	}
	if (planes.size() IS_EQUAL 1)
	{
		const auto& intsct = planes[0];
		if (intsct IS_EQUAL section)
		{
			if (verbose)
			{
				Info << endl
					<< " the section is underwater, completely!" << endl
					<< " - deep condition is applied" << endl;
			}
			Debug_Null_Pointer(intsct->OuterWire());

			Marine_SectTools::Section
			(
				intsct->OuterWire(), 
				targetSection,
				marineLib::curveType::wetted
			);

			auto sect = 
				Marine_SectTools::SectionCreator
				(
					intsct->OuterWire(), 
					Marine_SectionType::wetted
				);
			Debug_Null_Pointer(sect);

			auto wetted = Marine_SectTools::WettedSection(sect);
			Debug_Null_Pointer(wetted);

			wetted->SetDeep(Standard_True);

			std::vector<std::shared_ptr<tnbLib::Marine_Section>> l;
			l.push_back(std::move(wetted));

			if (verbose)
			{
				Info << endl
					<< "Leaving the function" << endl;
			}
			return std::move(l);
		}
		else
		{
			if (verbose)
			{
				Info << endl
					<< " the section is in touch with the water surface" << endl;
			}
			Debug_Null_Pointer(intsct->OuterWire());

			Marine_SectTools::Section
			(
				intsct->OuterWire(),
				targetSection,
				marineLib::curveType::wetted
			);

			auto sect =
				Marine_SectTools::SectionCreator
				(
					intsct->OuterWire(),
					Marine_SectionType::wetted
				);
			Debug_Null_Pointer(sect);

			auto wetted = Marine_SectTools::WettedSection(sect);
			Debug_Null_Pointer(wetted);

			wetted->SetDeep(Standard_False);

			std::vector<std::shared_ptr<tnbLib::Marine_Section>> l;
			l.push_back(std::move(wetted));

			if (verbose)
			{
				Info << endl
					<< "Leaving the function" << endl;
			}
			return std::move(l);
		}
	}

	if (verbose)
	{
		Info << endl
			<< " the section is in touch with the water surface" << endl;
	}

	std::vector<std::shared_ptr<tnbLib::Marine_Section>> l;
	l.reserve(planes.size());
	for (const auto& x : planes)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->OuterWire());

		Marine_SectTools::Section
		(
			x->OuterWire(), 
			targetSection,
			marineLib::curveType::wetted
		);

		auto sect =
			Marine_SectTools::SectionCreator
			(
				x->OuterWire(),
				Marine_SectionType::wetted
			);
		Debug_Null_Pointer(sect);
		
		auto wetted = Marine_SectTools::WettedSection(sect);
		Debug_Null_Pointer(wetted);

		wetted->SetDeep(Standard_False);

		l.push_back(std::move(wetted));
	}
	if (verbose)
	{
		Info << endl
			<< "Leaving the function" << endl;
	}
	return std::move(l);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_BooleanOps::DrySection
(
	const std::shared_ptr<Pln_Wire>& theSection,
	const std::shared_ptr<Pln_Wire>& theWater,
	const marineLib::curveType targetSection
)
{
	if (verbose)
	{
		Info << endl
			<< " Entering into the function:" << endl
			<< FunctionSIG << endl;
	}

#ifdef _DEBUG
	Pln_Tools::CheckManifold(theSection);
	Pln_Tools::CheckManifold(theWater);
#endif // _DEBUG

	Pln_Tools::SetPrecision(theSection);
	Pln_Tools::SetPrecision(theWater);

	if (verbose)
	{
		Info << endl
			<< " Making a plane from the section wire" << endl;
	}

	auto section = Cad2d_Plane::MakePlane(theSection, nullptr);
	Debug_Null_Pointer(section);

	if (verbose)
	{
		Info << endl
			<< " Making a plane from the water wire" << endl;
	}

	auto water = Cad2d_Plane::MakePlane(theWater, nullptr);
	Debug_Null_Pointer(water);

	if (verbose)
	{
		Info << endl
			<< " Subtracting the water plane from the section" << endl;
	}
	auto subs = Cad2d_Boolean::Subtract(section, water);
	
	if (verbose)
	{
		Info << endl
			<< " nb. of planes: " << subs.size() << endl;
	}
	if (subs.empty())
	{
		return std::vector<std::shared_ptr<Marine_Section>>();
	}

	std::vector<std::shared_ptr<Marine_Section>> sections;
	sections.reserve(subs.size());
	if (subs.size() IS_EQUAL 1)
	{
		const auto& sect = subs[0];
		Marine_SectTools::Section
		(
			sect->OuterWire(), 
			targetSection,
			marineLib::curveType::dry
		);

		auto dry = 
			Marine_SectTools::SectionCreator
			(
				sect->OuterWire(),
				Marine_SectionType::dry
			);
		Debug_Null_Pointer(dry);

		sections.push_back(std::move(dry));

		if (verbose)
		{
			Info << endl
				<< "Leaving the function" << endl;
		}
		return std::move(sections);
	}
	else
	{
		for (const auto& sect : subs)
		{
			Marine_SectTools::Section
			(
				sect->OuterWire(), 
				targetSection,
				marineLib::curveType::dry
			);

			auto dry =
				Marine_SectTools::SectionCreator
				(
					sect->OuterWire(), 
					Marine_SectionType::dry
				);
			Debug_Null_Pointer(dry);

			sections.push_back(std::move(dry));
		}

		if (verbose)
		{
			Info << endl
				<< "Leaving the function" << endl;
		}
		return std::move(sections);
	}
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>>
tnbLib::Marine_BooleanOps::WettedSection
(
	const std::shared_ptr<marineLib::Section_Displacer>& theSection,
	const std::shared_ptr<Marine_Section>& theWater
)
{
	if (Marine_SectTools::HasInnerSection(theSection))
	{
		FatalErrorIn(FunctionSIG)
			<< "the Section is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	if (Marine_SectTools::HasInnerSection(theWater))
	{
		FatalErrorIn(FunctionSIG)
			<< "the water section is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	auto sections = WettedSection(theSection->Wire(), theWater->Wire(), marineLib::curveType::displacer);
	return std::move(sections);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>>
tnbLib::Marine_BooleanOps::WettedSection
(
	const std::shared_ptr<marineLib::Section_Tank>& theSection,
	const std::shared_ptr<Marine_Section>& theWater
)
{
	if (Marine_SectTools::HasInnerSection(theSection))
	{
		FatalErrorIn(FunctionSIG)
			<< "the Section is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	if (Marine_SectTools::HasInnerSection(theWater))
	{
		FatalErrorIn(FunctionSIG)
			<< "the water section is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	auto sections = WettedSection(theSection->Wire(), theWater->Wire(), marineLib::curveType::tank);
	return std::move(sections);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_BooleanOps::DrySection
(
	const std::shared_ptr<marineLib::Section_Displacer>& theSection, 
	const std::shared_ptr<Marine_Section>& theWater
)
{
	if (Marine_SectTools::HasInnerSection(theSection))
	{
		FatalErrorIn(FunctionSIG)
			<< "the Section is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	if (Marine_SectTools::HasInnerSection(theWater))
	{
		FatalErrorIn(FunctionSIG)
			<< "the water section is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	auto sections = DrySection(theSection->Wire(), theWater->Wire(), marineLib::curveType::displacer);
	return std::move(sections);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_BooleanOps::DrySection
(
	const std::shared_ptr<marineLib::Section_Tank>& theSection, 
	const std::shared_ptr<Marine_Section>& theWater
)
{
	if (Marine_SectTools::HasInnerSection(theSection))
	{
		FatalErrorIn(FunctionSIG)
			<< "the Section is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	if (Marine_SectTools::HasInnerSection(theWater))
	{
		FatalErrorIn(FunctionSIG)
			<< "the water section is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	auto sections = DrySection(theSection->Wire(), theWater->Wire(), marineLib::curveType::tank);
	return std::move(sections);
}

std::shared_ptr<tnbLib::Marine_CmpSection>
tnbLib::Marine_BooleanOps::WettedSection
(
	const std::shared_ptr<Marine_CmpSection>& theSection,
	const std::shared_ptr<Marine_Section>& theWater
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(*theSection);
#endif // _DEBUG

	if (Marine_SectTools::HasInnerSection(*theSection))
	{
		FatalErrorIn(FunctionSIG)
			<< "the compSection is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	if (Marine_SectTools::HasInnerSection(theWater))
	{
		FatalErrorIn(FunctionSIG)
			<< "the water section is allow to have no inner section!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Marine_Section>> sectList;
	for (const auto& x : theSection->Sections())
	{
		Debug_Null_Pointer(x);

		auto displacer = std::dynamic_pointer_cast<marineLib::Section_Displacer>(x);
		if (displacer)
		{
			auto sections = WettedSection(displacer, theWater);
			for (const auto& sect : sections)
			{
				sectList.push_back(std::move(sect));
			}
			continue;
		}

		auto tank = std::dynamic_pointer_cast<marineLib::Section_Tank>(x);
		if (tank)
		{
			auto sections = WettedSection(tank, theWater);
			for (const auto& sect : sections)
			{
				sectList.push_back(std::move(sect));
			}
			continue;
		}
		
		FatalErrorIn(FunctionSIG)
			<< "the section is not displacer or tank" << endl
			<< abort(FatalError);
	}

	if (sectList.empty())
	{
		return nullptr;
	}

	auto cmpSect = Marine_SectTools::CmpSectionCreator(sectList);
	Debug_Null_Pointer(cmpSect);

	auto loc = theSection->CoordinateSystem().Location();
	cmpSect->SetLocation(loc);

	return std::move(cmpSect);
}

std::shared_ptr<tnbLib::Marine_CmpSection> 
tnbLib::Marine_BooleanOps::DrySection
(
	const std::shared_ptr<Marine_CmpSection>& theSection, 
	const std::shared_ptr<Marine_Section>& theWater
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(*theSection);
#endif // _DEBUG

	if (Marine_SectTools::HasInnerSection(*theSection))
	{
		FatalErrorIn(FunctionSIG)
			<< "the compSection is allowed to have no inner section!" << endl
			<< abort(FatalError);
	}

	if (Marine_SectTools::HasInnerSection(theWater))
	{
		FatalErrorIn(FunctionSIG)
			<< "the water section is allowed to have no inner section!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Marine_Section>> sectList;
	for (const auto& x : theSection->Sections())
	{
		Debug_Null_Pointer(x);

		auto displacer = std::dynamic_pointer_cast<marineLib::Section_Displacer>(x);
		if (displacer)
		{
			auto sections = DrySection(displacer, theWater);
			for (const auto& sect : sections)
			{
				sectList.push_back(std::move(sect));
			}
			continue;
		}

		auto tank = std::dynamic_pointer_cast<marineLib::Section_Tank>(x);
		if (tank)
		{
			auto sections = DrySection(tank, theWater);
			for (const auto& sect : sections)
			{
				sectList.push_back(std::move(sect));
			}
			continue;
		}

		FatalErrorIn(FunctionSIG)
			<< "the section is not displacer or tank" << endl
			<< abort(FatalError);
	}

	if (sectList.empty())
	{
		return nullptr;
	}

	auto cmpSect = Marine_SectTools::CmpSectionCreator(sectList);
	Debug_Null_Pointer(cmpSect);

	auto loc = theSection->CoordinateSystem().Location();
	cmpSect->SetLocation(loc);

	return std::move(cmpSect);
}

std::vector<std::shared_ptr<tnbLib::Marine_CmpSection>> 
tnbLib::Marine_BooleanOps::WettedSections
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel, 
	const std::vector<std::shared_ptr<Marine_Section>>& theWaterSections
)
{
	std::vector<std::shared_ptr<Marine_CmpSection>> sections;
	Standard_Integer K = 0;
	for (const auto& x : theModel)
	{
		Debug_Null_Pointer(x);

		if (NOT(Marine_SectTools::IsDisplacer(*x) OR Marine_SectTools::IsTank(*x)))
		{
			FatalErrorIn(FunctionSIG)
				<< "the sections must be displacer or tank!" << endl
				<< abort(FatalError);
		}

		const auto& wa = theWaterSections[K++];
		Debug_Null_Pointer(wa);

		std::shared_ptr<Marine_CmpSection> wetted;
#ifdef _DEBUG
		try
		{
			wetted = WettedSection(x, wa);
		}
		catch (const error&)
		{
#ifdef _PLOT

			OFstream myFile(fileName(".\\results_booleanOps\\wettedSection.plt"));

			auto tri0 = MarineBase_Tools::RetrieveTriangulation(*x);
			Debug_Null_Pointer(tri0);
			tri0->ExportToPlt(myBooleanOpsSectionViewFile);

			auto tri1 = MarineBase_Tools::RetrieveTriangulation(*wa);
			Debug_Null_Pointer(tri1);
			tri1->ExportToPlt(myBooleanOpsSectionViewFile);
			std::exit(1);
#elif _SaveData
			{//- saving scope
				size_t i = 0;
				const auto name = "section";
				const auto folder = "results_booleanOps/" + std::to_string(i);
				std::string address = ".\\results_booleanOps\\" + std::to_string(i) + "\\" + name;
				//boost::filesystem::path dir(folder);
				std::filesystem::create_directories(folder);

				fileName fn(address);

				std::ofstream myFile(fn);
				TNB_oARCH_FILE_TYPE ar(myFile);
				ar << x;
			}

			{//- saving scope
				size_t i = 1;
				const auto name = "section";
				const auto folder = "results_booleanOps/" + std::to_string(i);
				std::string address = ".\\results_booleanOps\\" + std::to_string(i) + "\\" + name;
				//boost::filesystem::path dir(folder);
				std::filesystem::create_directories(folder);

				fileName fn(address);

				std::ofstream myFile(fn);
				TNB_oARCH_FILE_TYPE ar(myFile);
				ar << wa;
			}
			std::exit(1);
#else
			FatalErrorIn(FunctionSIG)
				<< "unable to retrieve wetted section" << endl
				<< abort(FatalError);
#endif // _PLOT
		}
#else
		wetted = WettedSection(x, wa);
#endif // _DEBUG

		if (wetted)
		{
			sections.push_back(std::move(wetted));
		}
	}
	return std::move(sections);
}

std::vector<std::shared_ptr<tnbLib::Marine_CmpSection>> 
tnbLib::Marine_BooleanOps::DrySections
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel, 
	const std::vector<std::shared_ptr<Marine_Section>>& theWaterSections
)
{
	std::vector<std::shared_ptr<Marine_CmpSection>> sections;
	Standard_Integer K = 0;
	for (const auto& x : theModel)
	{
		Debug_Null_Pointer(x);

		if (NOT(Marine_SectTools::IsDisplacer(*x) OR Marine_SectTools::IsTank(*x)))
		{
			FatalErrorIn(FunctionSIG)
				<< "the sections must be displacer or tank!" << endl
				<< abort(FatalError);
		}

		const auto& wa = theWaterSections[K++];
		Debug_Null_Pointer(wa);

		auto dry = DrySection(x, wa);
		if (dry)
		{
			sections.push_back(std::move(dry));
		}
	}
	return std::move(sections);
}