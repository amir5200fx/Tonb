#include <Marine_SectionDistribution_Uniform.hxx>

#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::Marine_SectionDistribution_Uniform::Perform()
{
	if (NbSections() < 2)
	{
		FatalErrorIn("void tnbLib::Marine_SectionDistribution_Uniform::Perform()")
			<< "Not enough nb. of sections" << endl
			<< abort(FatalError);
	}

	const auto dx = (Upper() - Lower()) / (Standard_Real)(NbSections() + 1);
	const auto x0 = Lower();

	auto sections = ChangeSections();
	sections.reserve(NbSections());

	forThose(Index, 1, NbSections())
	{
		auto x = x0 + Index * dx - 0.5*dx;
		sections.push_back(x);
	}

	Change_IsDone() = Standard_True;
}
