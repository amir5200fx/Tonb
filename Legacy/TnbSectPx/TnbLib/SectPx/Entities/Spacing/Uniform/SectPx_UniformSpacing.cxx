#include <SectPx_UniformSpacing.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::SectPx_UniformSpacing::typeName_("uniform-spacing");

tnbLib::SectPx_UniformSpacing::SectPx_UniformSpacing
(
	const std::shared_ptr<SectPx_Limits>& theLimits,
	const Standard_Integer nbSections
)
	: SectPx_Spacing(theLimits)
	, theNbSections_(nbSections)
{
	// empty body
}

tnbLib::SectPx_UniformSpacing::SectPx_UniformSpacing
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<SectPx_Limits>& theLimits,
	const Standard_Integer nbSections
)
	: SectPx_Spacing(theIndex, theName, theLimits)
	, theNbSections_(nbSections)
{
	// empty body
}

tnbLib::word 
tnbLib::SectPx_UniformSpacing::RegObjTypeName() const
{
	return typeName_;
}

std::vector<Standard_Real>
tnbLib::SectPx_UniformSpacing::Sections() const
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