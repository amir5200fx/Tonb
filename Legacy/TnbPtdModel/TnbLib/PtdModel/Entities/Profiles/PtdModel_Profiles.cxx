#include <PtdModel_Profiles.hxx>

#include <PtdModel_Profile.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::PtdModel_Profiles::Import(const std::shared_ptr<PtdModel_Profile>& theProfile)
{
	auto paired = std::make_pair(theProfile->Name(), theProfile);
	auto insert = theProfiles_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been found!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::PtdModel_Profiles::Import(std::shared_ptr<PtdModel_Profile>&& theProfile)
{
	auto paired = std::make_pair(theProfile->Name(), std::move(theProfile));
	auto insert = theProfiles_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been found!" << endl
			<< abort(FatalError);
	}
}