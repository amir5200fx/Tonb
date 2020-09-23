#include <Geo_CosineDistb.hxx>

#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Geo_CosineDistb::Perform()
{
	static const Standard_Real phi = 3.14159265358979323846;

	if (theSize_ < 2)
	{
		FatalErrorIn("void tnbLib::Geo_CosineDistb::Perform()")
			<< "Not enough nb. of sections" << endl
			<< abort(FatalError);
	}

	const auto c = (Upper() - Lower()) / 2;
	const auto dt =  phi / (Standard_Real)theSize_;

	const auto x0 = Lower();

	auto& sections = ChangeValues();
	sections.reserve(theSize_);

	forThose(Index, 0, theSize_)
	{
		auto t = Index * dt;
		auto x = c * ((Standard_Real)1.0 - std::cos(t));

		sections.push_back(x);
	}
	Change_IsDone() = Standard_True;
}