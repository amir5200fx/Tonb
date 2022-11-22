#include <Ship_Displ.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Ship_Displ::CalcxXSections()
{
	const auto& dimens = Parameters().Dimensions();

	auto nbSections = dimens.NbNetColumns();

	//Exclusion stem pair
	nbSections--;
	Debug_If_Condition(nbSections < 2);

	auto dx = dimens.LengthOnDeck()() / (Standard_Real)(nbSections - 1);

	nbSections++;

	auto& xs = XParamsRef().xXcoordsRef();
	xs.at(0) = 0;
	xs.at(nbSections - 1) = MIN(nbSections*dx, dimens.LengthOnDeck()());
	xs.at(nbSections - 2) = xs.at(nbSections - 1);

	const auto x0 = 0;
	const auto x1 = dimens.LengthOnDeck()();

	dx = (x1 - x0) / (Standard_Real)(nbSections - 4);
	for (size_t i = 0; i <= nbSections - 4; i++)
	{
		xs.at(i) = i * dx + x0;
	}
}

void tnbLib::Ship_Displ::CalcxYSections()
{
	const auto& deckProfile = Profiles().Deck();
	if (NOT deckProfile)
	{
		FatalErrorIn(FunctionSIG)
			<< "no deck profile has been found." << endl
			<< abort(FatalError);
	}

	const auto& dimens = Parameters().Dimensions();
	const auto nbSections = dimens.NbNetColumns();

	for (auto x : XParams().xSections())
	{

	}
}