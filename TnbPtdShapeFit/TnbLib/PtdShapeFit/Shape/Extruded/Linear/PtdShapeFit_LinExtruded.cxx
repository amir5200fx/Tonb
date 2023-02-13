#include <PtdShapeFit_LinExtruded.hxx>

#include <PtdShapeFit_Section.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <algorithm>

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Section::Parameters>> 
tnbLib::PtdShapeFit_LinExtruded::CalcParameters
(
	const std::vector<std::shared_ptr<PtdShapeFit_Section>>& theSections, 
	const gp_Ax1& theAxis,
	const std::vector<Standard_Real>& theXs
) const
{
	if (theXs.size() NOT_EQUAL theSections.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data has been detected." << endl
			<< abort(FatalError);
	}

	const auto n = theSections.size();
	auto [sections, xs] = Sort(theSections, theXs);

	const auto& sect = sections.at(0);
	const auto nbPars = sect->NbPars();

	auto chromosomes = RetrieveChromosomes(theSections);

	std::vector<std::shared_ptr<PtdShapeFit_Section::Parameters>> parameters;
	parameters.reserve(theSections.size());
	for (size_t m = 0; m < nbPars; m++)
	{
		const auto& sect = sections.at(m);
		const auto& chromosome = chromosomes.at(m);

		std::vector<std::pair<Standard_Real, Standard_Real>> qs;
		qs.resize(n);
		for (size_t i = 0; i < chromosome.size(); i++)
		{
			auto q = std::make_pair(xs.at(i), chromosome.at(i));
			qs.push_back(std::move(q));
		}
		auto approx = CalcLS(qs);
		auto chrom = sect->RetrieveParChromosome(approx);
		parameters.push_back(std::move(chrom));
	}
	return std::move(parameters);
}

std::vector<Standard_Real> 
tnbLib::PtdShapeFit_LinExtruded::CalcLS
(
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
)
{
	Standard_Real sumX = 0;
	Standard_Real sumY = 0;
	Standard_Real sumX2 = 0;
	Standard_Real sumXY = 0;
	for (const auto& q : theQs)
	{
		auto x = q.first;
		auto y = q.second;

		auto x2 = x * x;
		auto xy = x * y;

		sumX += x;
		sumY += y;

		sumX2 += x2;
		sumXY += xy;
	}

	const auto n = (Standard_Real)theQs.size();
	const auto m = (n * sumXY - sumX * sumY) /(n * sumX2 - sumX2);
	const auto b = (sumY - m * sumX) / n;

	std::vector<Standard_Real> values;
	values.reserve(theQs.size());
	for (const auto& q : theQs)
	{
		auto x = q.first;
		auto y = m * x + b;
		values.push_back(y);
	}
	return std::move(values);
}