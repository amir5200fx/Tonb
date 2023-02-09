#include <SeriesProps_WagenBBlade.hxx>

#include <SeriesProps_WagenB_TablePlusThreeBladed.hxx>
#include <SeriesProps_WagenB_TableThreeBladed.hxx>
#include <SeriesProps_WagenB_Section.hxx>
#include <SeriesProps_EdgeThick.hxx>
#include <Geo_xDistb.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::tuple
<
	tnbLib::SeriesProps_WagenBBlade::Chord,
	tnbLib::SeriesProps_WagenBBlade::A,
	tnbLib::SeriesProps_WagenBBlade::B,
	tnbLib::SeriesProps_WagenBBlade::Thick
>
tnbLib::SeriesProps_WagenBBlade::CalcThreeBladedParameters(const Standard_Real rPerR) const
{
	auto chord = Chord{ wagenB::TableThreeBladed::CalcChord(rPerR,Diameter(),AEPerAO(),NbBlades()) };
	auto a = A{ wagenB::TableThreeBladed::CalcA(rPerR,chord.value) };
	auto b = B{ wagenB::TableThreeBladed::CalcB(rPerR,chord.value) };
	auto thick = Thick{ wagenB::TableThreeBladed::CalcThickness(rPerR,Diameter(),NbBlades()) };
	auto t = std::make_tuple(std::move(chord), std::move(a), std::move(b), std::move(thick));
	return std::move(t);
}

std::tuple
<
	tnbLib::SeriesProps_WagenBBlade::Chord,
	tnbLib::SeriesProps_WagenBBlade::A,
	tnbLib::SeriesProps_WagenBBlade::B,
	tnbLib::SeriesProps_WagenBBlade::Thick
>
tnbLib::SeriesProps_WagenBBlade::CalcParameters
(
	const Standard_Real rPerR
) const
{
	auto chord = Chord{ wagenB::TablePlusThreeBladed::CalcChord(rPerR,Diameter(),AEPerAO(),NbBlades()) };
	auto a = A{ wagenB::TablePlusThreeBladed::CalcA(rPerR,chord.value) };
	auto b = B{ wagenB::TablePlusThreeBladed::CalcB(rPerR,chord.value) };
	auto thick = Thick{ wagenB::TablePlusThreeBladed::CalcThickness(rPerR,Diameter(),NbBlades()) };
	auto t = std::make_tuple(std::move(chord), std::move(a), std::move(b), std::move(thick));
	return std::move(t);
}

std::shared_ptr<tnbLib::SeriesProps_WagenB_Section> 
tnbLib::SeriesProps_WagenBBlade::CalcSectionThreeBladed
(
	const Standard_Real rPerR
) const
{
	auto [chord, a, b, thick] = CalcThreeBladedParameters(rPerR);
	const auto le = LE()->Value(rPerR);
	const auto te = TE()->Value(rPerR);

	auto sect = 
		std::make_shared<SeriesProps_WagenB_Section>
		(
			le, te, 
			thick.value, chord.value,
			a.value, b.value, rPerR
			);
	sect->Perform(SectionXs());
	Debug_If_Condition_Message(NOT sect->IsDone(), "the application is not performed.");
	return std::move(sect);
}

std::shared_ptr<tnbLib::SeriesProps_WagenB_Section> 
tnbLib::SeriesProps_WagenBBlade::CalcSection
(
	const Standard_Real rPerR
) const
{
	auto [chord, a, b, thick] = CalcParameters(rPerR);
	const auto le = LE()->Value(rPerR);
	const auto te = TE()->Value(rPerR);

	auto sect =
		std::make_shared<SeriesProps_WagenB_Section>
		(
			le, te,
			thick.value, chord.value,
			a.value, b.value, rPerR
			);
	sect->Perform(SectionXs());
	Debug_If_Condition_Message(NOT sect->IsDone(), "the application is not performed.");
	return std::move(sect);
}

void tnbLib::SeriesProps_WagenBBlade::Perform()
{
	if (NOT rPerR())
	{
		FatalErrorIn(FunctionSIG)
			<< "the radius distribution is not found." << endl
			<< abort(FatalError);
	}
	if (NbBlades() < 3 AND NbBlades() > 7)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid number of blades has been detected." << endl
			<< " - Z: " << NbBlades() << endl
			<< abort(FatalError);
	}
	if (NOT SectionXs())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section distribution function has been found." << endl
			<< abort(FatalError);
	}
	if (NOT rPerR())
	{
		FatalErrorIn(FunctionSIG)
			<< "no radial distribution function has been found." << endl
			<< abort(FatalError);
	}
	std::vector<std::shared_ptr<SeriesProps_WagenB_Section>> sections;
	sections.reserve(rPerR()->Size());

	for (auto r : rPerR()->Values())
	{
		if (NbBlades() IS_EQUAL 3)
		{
			auto section = CalcSectionThreeBladed(r);
			sections.push_back(std::move(section));
		}
		else
		{
			auto section = CalcSection(r);
			sections.push_back(std::move(section));
		}
	}

	SectionsRef() = std::move(sections);
	Change_IsDone() = Standard_True;
}