#include <Geo_UniDistb.hxx>

#include <Global_Macros.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Geo_UniDistb::Value
(
	const Standard_Integer theIndex
) const
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, MAX(0, theValues_.size() - 1)));

	return theValues_[theIndex];
}

void tnbLib::Geo_UniDistb::Perform()
{
	if (Size() < 2)
	{
		FatalErrorIn("void tnbLib::Geo_UniDistb::Perform()")
			<< "Not enough nb. of sections" << endl
			<< abort(FatalError);
	}

	const auto dx = (Upper() - Lower()) / (Standard_Real)(Size());
	const auto x0 = Lower();

	auto& sections = ChangeValues();
	sections.reserve(Size());

	forThose(Index, 0, Size())
	{
		auto x = x0 + Index * dx;
		sections.push_back(x);
	}

	Change_IsDone() = Standard_True;
}