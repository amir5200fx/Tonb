#include <SectPx_CmptProfileMaker.hxx>

#include <SectPx_ProfileMaker.hxx>
#include <SectPx_TopoProfileMaker.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::maker::CmptProfile::AddProfile
(
	const Standard_Integer theIndex, 
	std::shared_ptr<Profile>&& theProfile
)
{
	auto paired = std::make_pair(theIndex, std::move(theProfile));
	auto insert = theProfiles_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::maker::Profile> 
tnbLib::maker::CmptProfile::SelectProfile
(
	const Standard_Integer theIndex
) const
{
	auto iter = theProfiles_.find(theIndex);
	if (iter IS_EQUAL theProfiles_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
	return iter->second;
}

Standard_Integer 
tnbLib::maker::CmptProfile::CreateCustomProfile
(
	const std::shared_ptr<SectPx_Pnt>& theP0,
	const std::shared_ptr<SectPx_Pnt>& theP1
)
{
	Debug_Null_Pointer(Registry());

	auto tProfileMaker = std::make_shared<TopoProfile>(Registry());
	Debug_Null_Pointer(tProfileMaker);

	const auto tProfile_id = tProfileMaker->CreateCustomProfile(theP0, theP1);
	const auto tProfile = tProfileMaker->SelectProfile(tProfile_id);
	Debug_Null_Pointer(tProfile);

	auto profileMaker = std::make_shared<Profile>(tProfile, Registry());
	Debug_Null_Pointer(profileMaker);

	const auto id = Counter().RetrieveIndex();
	static const auto name = "profile maker";

	profileMaker->SetIndex(id);
	profileMaker->SetName(name + std::to_string(id));

	AddProfile(id, std::move(profileMaker));
	return id;
}

Standard_Integer
tnbLib::maker::CmptProfile::CreateExtruderCustomProfile
(
	const std::shared_ptr<SectPx_Pnt>& theP0,
	const std::shared_ptr<SectPx_Pnt>& theP1
)
{
	Debug_Null_Pointer(Registry());

	auto tProfileMaker = std::make_shared<TopoProfile>(Registry());
	Debug_Null_Pointer(tProfileMaker);

	const auto tProfile_id = tProfileMaker->CreateExtruderCustomProfile(theP0, theP1);
	const auto tProfile = tProfileMaker->SelectProfile(tProfile_id);
	Debug_Null_Pointer(tProfile);

	auto profileMaker = std::make_shared<Profile>(tProfile, Registry());
	Debug_Null_Pointer(profileMaker);

	const auto id = Counter().RetrieveIndex();
	static const auto name = "profile maker";

	profileMaker->SetIndex(id);
	profileMaker->SetName(name + std::to_string(id));

	AddProfile(id, std::move(profileMaker));
	return id;
}

Standard_Integer 
tnbLib::maker::CmptProfile::CreateInterplProfile
(
	const std::shared_ptr<SectPx_Cloud>& theCloud
)
{
	Debug_Null_Pointer(Registry());

	auto tProfileMaker = std::make_shared<TopoProfile>(Registry());
	Debug_Null_Pointer(tProfileMaker);

	const auto tProfile_id = tProfileMaker->CreateInterplProfile(theCloud);
	const auto tProfile = tProfileMaker->SelectProfile(tProfile_id);
	Debug_Null_Pointer(tProfile);

	auto profileMaker = std::make_shared<Profile>(tProfile, Registry());
	Debug_Null_Pointer(profileMaker);

	const auto id = Counter().RetrieveIndex();
	static const auto name = "profile maker";

	profileMaker->SetIndex(id);
	profileMaker->SetName(name + std::to_string(id));

	AddProfile(id, std::move(profileMaker));
	return id;
}