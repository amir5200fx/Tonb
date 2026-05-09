#include <Model_CmpProfile.hxx>

#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>

void tnbLib::Model_CmpProfile::CheckProfiles()
{
	for (size_t i = 1; i < theProfiles_.size(); i++)
	{
		const auto& pr0 = theProfiles_.at(i - 1);
		const auto& pr1 = theProfiles_.at(i);

		if (NOT IsContinuous(pr0, pr1))
		{
			FatalErrorIn(FunctionSIG)
				<< "the two profiles are not continuous." << endl
				<< abort(FatalError);
		}
	}
}

Standard_Boolean 
tnbLib::Model_CmpProfile::IsContinuous
(
	const std::shared_ptr<Model_ParamProfile>& thePr0,
	const std::shared_ptr<Model_ParamProfile>& thePr1
)
{
	const auto val0 = thePr0->UpperValue();
	const auto val1 = thePr1->LowerValue();
	return std::abs(val0 - val1) <= gp::Resolution();
}

std::shared_ptr<tnbLib::Model_ParamProfile>
tnbLib::Model_CmpProfile::FindProfile
(
	const Standard_Real theX,
	const std::vector<std::shared_ptr<Model_ParamProfile>>& theProfiles
)
{
	for (const auto& x : theProfiles)
	{
		Debug_Null_Pointer(x);
		auto x0 = x->Lower();
		auto x1 = x->Upper();

		if (INSIDE(theX, x0, x1))
		{
			return x;
		}
	}
	return nullptr;
}

Standard_Real 
tnbLib::Model_CmpProfile::Lower() const
{
	return theProfiles_.at(0)->Lower();
}

Standard_Real 
tnbLib::Model_CmpProfile::Upper() const
{
	return theProfiles_.at(theProfiles_.size() - 1)->Upper();
}

Standard_Real 
tnbLib::Model_CmpProfile::Value(const Standard_Real x) const
{
	auto p = FindProfile(x, theProfiles_);
	if (NOT p)
	{
		FatalErrorIn(FunctionSIG)
			<< "no profile has been found." << endl
			<< " - x: " << x << endl
			<< " - lower: " << Lower() << endl
			<< " - upper: " << Upper() << endl
			<< abort(FatalError);
	}
	return p->Value(x);
}

std::vector<Standard_Real> 
tnbLib::Model_CmpProfile::Breacks() const
{
	std::vector<Standard_Real> xs;
	xs.reserve(theProfiles_.size() + 1);
	for (const auto& x : theProfiles_)
	{
		Debug_Null_Pointer(x);
		xs.push_back(x->Lower());
	}
	xs.push_back(Upper());
	return std::move(xs);
}