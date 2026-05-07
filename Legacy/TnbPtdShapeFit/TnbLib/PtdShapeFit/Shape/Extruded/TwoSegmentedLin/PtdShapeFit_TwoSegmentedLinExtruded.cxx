#include <PtdShapeFit_TwoSegmentedLinExtruded.hxx>

#include <PtdShapeFit_Section.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <algorithm>

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Section::Parameters>> 
tnbLib::PtdShapeFit_TwoSegmentedLinExtruded::CalcParameters
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

	const auto xp = Segmented();

	std::vector<std::vector<Standard_Real>> approximated;
	for (size_t m = 0; m < nbPars; m++)
	{
		const auto& chromosome = chromosomes.at(m);

		std::vector<std::pair<Standard_Real, Standard_Real>> qs;
		qs.reserve(n);
		for (size_t i = 0; i < chromosome.size(); i++)
		{
			auto q = std::make_pair(xs.at(i), chromosome.at(i));
			qs.push_back(std::move(q));
		}

		auto approx = CalcLS(qs, xp);
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

#include <PtdShapeFit_LinExtruded.hxx>

namespace tnbLib
{

	struct LinearProfileCoeffs
	{
		std::pair<std::vector<Standard_Real>, std::vector<Standard_Real>> Coeff;
	};

	auto CalcTwoSegmentedLinearProfile
	(
		const std::vector<std::pair<std::shared_ptr<PtdShapeFit_Section::Parameters>, Standard_Real>>& theParams,
		const std::shared_ptr<PtdShapeFit_Section>& theSection,
		const Standard_Real theX
	)
	{
		std::vector
			<
			std::pair
			<
			std::shared_ptr<PtdShapeFit_Section::Parameters>,
			Standard_Real
			>
			> Pars_left, Pars_right;
		for (const auto& x : theParams)
		{
			if (x.second < theX)
			{
				Pars_left.push_back(x);
			}
			else
			{
				Pars_right.push_back(x);
			}
		}
		if (Pars_left.size() < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "not enough number of left samples for the profile." << endl
				<< abort(FatalError);
		}
		if (Pars_right.size() < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "not enough number of right samples for the profile." << endl
				<< abort(FatalError);
		}
		std::pair<LinearProfileCoeffs, LinearProfileCoeffs>
			Coeffs;
		{// the left profile [4/11/2023 Payvand]
			auto left = PtdShapeFit_LinExtruded::CalcLinearProfile(Pars_left, theSection);
			Coeffs.first = { std::move(left) };
		}// the right profile [4/11/2023 Payvand]
		{
			auto right = PtdShapeFit_LinExtruded::CalcLinearProfile(Pars_right, theSection);
			Coeffs.second = { std::move(right) };
		}
		return std::move(Coeffs);
	}
}

std::pair
<
	std::shared_ptr<tnbLib::Cad_Shape>,
	std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Section::Parameters>>
> 
tnbLib::PtdShapeFit_TwoSegmentedLinExtruded::CreateExtrapolated
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

	auto [leftProfile, rightProfile] = 
		CalcTwoSegmentedLinearProfile(theParams, theSection, Segmented());

	auto [A_left, B_left] = leftProfile.Coeff;
	auto [A_right, B_right] = rightProfile.Coeff;

	const auto xSeg = Segmented();
	for (auto x : theLocs)
	{
		std::vector<Standard_Real> chrom(nbPars);
		if (x < xSeg)
		{
			for (size_t m = 0; m < nbPars; m++)
			{
				chrom.at(m) = A_left.at(m) * x + B_left.at(m);
			}
		}
		else
		{
			for (size_t m = 0; m < nbPars; m++)
			{
				chrom.at(m) = A_right.at(m) * x + B_right.at(m);
			}
		}
		auto pars = theSection->RetrieveParChromosome(chrom);
		params.push_back(std::move(pars));
	}
	std::shared_ptr<Cad_Shape> shape;
	try
	{
		shape = CreateShape(params, theSection, theAxis, theLocs);
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}
	auto paired = std::make_pair(std::move(shape), std::move(params));
	return std::move(paired);
}

std::vector<Standard_Real> 
tnbLib::PtdShapeFit_TwoSegmentedLinExtruded::CalcLS
(
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs,
	const Standard_Real theX
)
{
	std::vector<std::pair<Standard_Real, Standard_Real>> Qs_left, Qs_right;
	for (const auto& x : theQs)
	{
		if (x.first < theX)
		{
			Qs_left.push_back(x);
		}
		else
		{
			Qs_right.push_back(x);
		}
	}
	std::vector<Standard_Real> ls;
	ls.reserve(theQs.size());
	{
		auto left_values = PtdShapeFit_LinExtruded::CalcLS(Qs_left);
		for (auto x : left_values)
		{
			ls.push_back(x);
		}
	}
	{
		auto right_values = PtdShapeFit_LinExtruded::CalcLS(Qs_right);
		for (auto x : right_values)
		{
			ls.push_back(x);
		}
	}
	return std::move(ls);
}