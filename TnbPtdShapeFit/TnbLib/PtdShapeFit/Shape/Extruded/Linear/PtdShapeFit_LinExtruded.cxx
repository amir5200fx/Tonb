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

namespace tnbLib
{

	auto CalcLinearProfile(const std::vector<std::pair<std::shared_ptr<PtdShapeFit_Section::Parameters>, Standard_Real>>& theParams, const std::shared_ptr<PtdShapeFit_Section>& theSection)
	{	
		const auto nbPars = theSection->NbPars();
		std::vector<Standard_Real> a(nbPars);
		std::vector<Standard_Real> b(nbPars);
		if (theParams.size() IS_EQUAL 2)
		{
			Standard_Real x0;
			std::vector<Standard_Real> chrom0;
			{// #loc0
				auto [pars, loc] = theParams.at(0);
				x0 = loc;
				chrom0 = theSection->RetrieveChromosome(pars);
			}
			Standard_Real x1;
			std::vector<Standard_Real> chrom1;
			{// #loc1
				auto [pars, loc] = theParams.at(1);
				x1 = loc;
				chrom1 = theSection->RetrieveChromosome(pars);
			}
			for (size_t m = 0; m < nbPars; m++)
			{
				a.at(m) = (chrom1.at(m) - chrom0.at(m)) / (x1 - x0);
				b.at(m) = chrom0.at(m) - a.at(m) * x0;
			}
		}
		else
		{
			for (size_t m = 0; m < nbPars; m++)
			{
				Standard_Real sumX = 0;
				Standard_Real sumY = 0;
				Standard_Real sumX2 = 0;
				Standard_Real sumXY = 0;

				for (const auto& p : theParams)
				{
					auto [pars, loc] = p;
					auto chrom = theSection->RetrieveChromosome(pars);

					auto x = loc;
					auto y = chrom.at(m);

					auto x2 = x * x;
					auto xy = x * y;

					sumX += x;
					sumY += y;

					sumX2 += x2;
					sumXY += xy;
				}

				const auto n = (Standard_Real)theParams.size();
				a.at(m) = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX2);
				b.at(m) = (sumY - a.at(m) * sumX) / n;
			}
			
		}
		auto t = std::make_pair(std::move(a), std::move(b));
		return std::move(t);
	}
}

std::shared_ptr<tnbLib::Cad_Shape> 
tnbLib::PtdShapeFit_LinExtruded::CreateExtrapolated
(
	const std::vector<std::pair<std::shared_ptr<PtdShapeFit_Section::Parameters>, Standard_Real>>& theParams,
	const std::shared_ptr<PtdShapeFit_Section>& theSection, 
	const gp_Ax1& theAxis, 
	const std::vector<Standard_Real>& theLocs
) const
{
	std::vector<std::shared_ptr<PtdShapeFit_Section::Parameters>> params;
	params.reserve(theLocs.size());
	const auto nbPars = theSection->NbPars();
	
	auto [A, B] = CalcLinearProfile(theParams, theSection);

	for (auto x : theLocs)
	{
		std::vector<Standard_Real> chrom(nbPars);
		for (size_t m = 0; m < nbPars; m++)
		{
			chrom.at(m) = A.at(m) * x + B.at(m);
		}
		auto pars = theSection->RetrieveParChromosome(chrom);
		params.push_back(std::move(pars));
	}
	return CreateShape(params, theSection, theAxis, theLocs);
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