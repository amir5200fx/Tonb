#include <PtdModel_BladeProfiles.hxx>

#include <PtdModel_BladeProfile.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::PtdModel_BladeProfiles::Import(const std::shared_ptr<PtdModel_BladeProfile>& theProfile)
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

void tnbLib::PtdModel_BladeProfiles::Import(std::shared_ptr<PtdModel_BladeProfile>&& theProfile)
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