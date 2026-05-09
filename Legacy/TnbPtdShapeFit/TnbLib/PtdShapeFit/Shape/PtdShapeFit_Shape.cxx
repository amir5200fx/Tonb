#include <PtdShapeFit_Shape.hxx>

#include <PtdShapeFit_Section.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <algorithm>

const std::string tnbLib::PtdShapeFit_Shape::extension = ".pshfitext";

std::pair
<
	std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Section>>,
	std::vector<Standard_Real>
>
tnbLib::PtdShapeFit_Shape::Sort
(
	const std::vector<std::shared_ptr<PtdShapeFit_Section>>& theSections,
	const std::vector<Standard_Real>& theXs
)
{
	if (theXs.size() NOT_EQUAL theSections.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data has been detected." << endl
			<< abort(FatalError);
	}

	typedef std::pair<std::shared_ptr<PtdShapeFit_Section>, Standard_Real> xSect;
	static auto cmpScet = [](const xSect& s0, const xSect& s1)
	{
		return s0.second < s1.second;
	};

	std::vector<xSect> sorted;
	sorted.reserve(theSections.size());
	for (size_t i = 0; i < theSections.size(); i++)
	{
		auto paired = std::make_pair(theSections.at(i), theXs.at(i));
		sorted.push_back(std::move(paired));
	}
	std::sort(sorted.begin(), sorted.end(), cmpScet);

	std::vector<Standard_Real> xs;
	std::vector<std::shared_ptr<PtdShapeFit_Section>> sections;
	xs.reserve(sorted.size());
	sections.reserve(sorted.size());
	for (const auto& x : sorted)
	{
		xs.push_back(x.second);
		sections.push_back(x.first);
	}

	auto t = std::make_pair(std::move(sections), std::move(xs));
	return std::move(t);
}

std::vector<std::vector<Standard_Real>> 
tnbLib::PtdShapeFit_Shape::RetrieveChromosomes
(
	const std::vector<std::shared_ptr<PtdShapeFit_Section>>& theSections
)
{
	std::vector<std::vector<Standard_Real>> pars;
	const auto& sect = theSections.at(0);
	const auto nbPars = sect->NbPars();
	for (size_t m = 0; m < nbPars; m++)
	{
		std::vector<Standard_Real> chromosome;
		chromosome.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			auto iPars = x->RetrieveChromosome(x->Pars());
			chromosome.push_back(iPars.at(m));
		}
		pars.push_back(std::move(chromosome));
	}
	return std::move(pars);
}