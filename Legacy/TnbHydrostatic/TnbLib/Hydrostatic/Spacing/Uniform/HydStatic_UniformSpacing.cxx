#include <HydStatic_UniformSpacing.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::HydStatic_UniformSpacing::HydStatic_UniformSpacing
(
	const Standard_Integer theIndex,
	const word & theName
)
	: HydStatic_Spacing(theIndex, theName)
{
	// empty body
}

tnbLib::HydStatic_UniformSpacing::HydStatic_UniformSpacing
(
	const Standard_Integer NbSections
)
	: theNbSections_(NbSections)
{
	// empty body
}

tnbLib::HydStatic_UniformSpacing::HydStatic_UniformSpacing
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Standard_Integer NbSections
)
	: HydStatic_Spacing(theIndex, theName)
	, theNbSections_(NbSections)
{
	// empty body
}

std::vector<Standard_Real> 
tnbLib::HydStatic_UniformSpacing::Sections() const
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