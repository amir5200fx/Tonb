#include <PtdShapeFit_LinExtruded.hxx>

#include <PtdShapeFit_Section.hxx>
#include <Geo_Tools.hxx>
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

	std::vector<std::vector<Standard_Real>> approximated;
	for (size_t m = 0; m < nbPars; m++)
	{
		const auto& chromosome = chromosomes.at(m);
		/*std::cout << std::endl;
		for (auto xx : chromosome)
		{
			std::cout << xx << ", " << std::endl;
		}
		std::cout << std::endl;
		PAUSE;*/
		std::vector<std::pair<Standard_Real, Standard_Real>> qs;
		qs.reserve(n);
		for (size_t i = 0; i < chromosome.size(); i++)
		{
			auto q = std::make_pair(xs.at(i), chromosome.at(i));
			qs.push_back(std::move(q));
		}
		auto approx = CalcLS(qs);
		/*std::cout << std::endl;
		for (auto xx : approx)
		{
			std::cout << "- approx: " << xx << ", " << std::endl;
		}
		std::cout << std::endl;
		PAUSE;*/
		approximated.push_back(std::move(approx));
		
	}

	for (size_t i = 0; i < theSections.size(); i++)
	{
		std::vector<Standard_Real> approx;
		for (size_t m = 0; m < nbPars; m++)
		{
			approx.push_back(approximated.at(m).at(i));
		}
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
	if (theQs.size() IS_EQUAL 2)
	{
		std::vector<Standard_Real> values;
		values.reserve(theQs.size());
		values.push_back(theQs.at(0).second);
		values.push_back(theQs.at(1).second);
		return std::move(values);
	}
	else
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
		const auto m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX2);
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
}