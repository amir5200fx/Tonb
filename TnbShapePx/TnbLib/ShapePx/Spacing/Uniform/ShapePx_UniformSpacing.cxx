#include <ShapePx_UniformSpacing.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<Standard_Real> 
tnbLib::ShapePx_UniformSpacing::Sections() const
{
	if (Upper() <= Lower())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid value for the upper bound of the spacing!" << endl
			<< " - lower = " << Lower() << endl
			<< " - upper = " << Upper() << endl
			<< abort(FatalError);
	}

	if (NbSections() <= 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "the nb. of sections must be larger than 3!" << endl
			<< abort(FatalError);
	}

	const auto dx = (Upper() - Lower()) / (Standard_Real)(NbSections() - 1);
	std::vector<Standard_Real> Xs;
	Xs.reserve(NbSections());
	for (Standard_Integer i = 0; i < NbSections(); i++)
	{
		Xs.push_back(Lower() + i * dx);
	}
	return std::move(Xs);
}