#include <Geo_UniDistb.hxx>

#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Geo_UniDistb::Geo_UniDistb(const Standard_Real lower, const Standard_Real upper, const Standard_Integer size)
	: Geo_xDistb(lower, upper)
	, theSize_(size)
{
	Perform();
}

void tnbLib::Geo_UniDistb::Perform()
{
	if (theSize_ < 2)
	{
		FatalErrorIn("void tnbLib::Geo_UniDistb::Perform()")
			<< "Not enough nb. of sections" << endl
			<< abort(FatalError);
	}

	const auto dx = (Upper() - Lower()) / static_cast<Standard_Real>(theSize_);
	const auto x0 = Lower();

	auto& sections = ChangeValues();
	sections.reserve(theSize_);

	forThose(Index, 0, theSize_)
	{
		auto x = x0 + Index * dx;
		sections.push_back(x);
	}

	Change_IsDone() = Standard_True;
}
