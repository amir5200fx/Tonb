#include <HydStatic_CustomSpacing.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::HydStatic_CustomSpacing::HydStatic_CustomSpacing
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::vector<Standard_Real>& xs
)
	: HydStatic_Spacing(theIndex, theName)
	, theX_(xs)
{
	// empty body
}

tnbLib::HydStatic_CustomSpacing::HydStatic_CustomSpacing
(
	const Standard_Integer theIndex,
	const word & theName,
	std::vector<Standard_Real>&& xs
)
	: HydStatic_Spacing(theIndex, theName)
	, theX_(std::move(xs))
{
	// empty body
}

Standard_Real 
tnbLib::HydStatic_CustomSpacing::Lower() const
{
	if (theX_.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty" << endl
			<< abort(FatalError);
	}
	return theX_[0];
}

Standard_Real 
tnbLib::HydStatic_CustomSpacing::Upper() const
{
	if (theX_.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty" << endl
			<< abort(FatalError);
	}
	return theX_[theX_.size() - 1];
}