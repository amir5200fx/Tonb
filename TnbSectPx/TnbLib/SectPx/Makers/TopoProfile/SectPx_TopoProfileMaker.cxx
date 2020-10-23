#include <SectPx_TopoProfileMaker.hxx>

#include <SectPx_Registry.hxx>
#include <SectPx_Node.hxx>
#include <SectPx_NodeMaker.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_CustomProfile.hxx>
#include <SectPx_InterplProfile.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_TopoProfile> 
tnbLib::maker::TopoProfile::SelectProfile
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());
	const auto& registry = *Registry();

	auto item = registry.SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto profile = std::dynamic_pointer_cast<SectPx_TopoProfile>(item);
	if (NOT profile)
	{
		FatalErrorIn(FunctionSIG)
			<< " the selected item is not a profile!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
	return std::move(profile);
}

Standard_Integer 
tnbLib::maker::TopoProfile::CreateCustomProfile
(
	const std::shared_ptr<SectPx_Pnt>& theP0, 
	const std::shared_ptr<SectPx_Pnt>& theP1
)
{
	auto nodeMaker = std::make_shared<Node>(Registry());
	Debug_Null_Pointer(nodeMaker);

	const auto n0_id = nodeMaker->CreateNode(theP0);
	const auto n1_id = nodeMaker->CreateNode(theP1);

	const auto n0 = nodeMaker->SelectNode(n0_id);
	Debug_Null_Pointer(n0);

	const auto n1 = nodeMaker->SelectNode(n1_id);
	Debug_Null_Pointer(n1);

	return CreateCustomProfile(n0, n1);
}

Standard_Integer 
tnbLib::maker::TopoProfile::CreateCustomProfile
(
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1
)
{
	auto profile = 
		SectPx_CustomProfile::MakeProfile
		(
			theNode0, 
			theNode1,
			Registry()
		);
	Debug_Null_Pointer(profile);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(profile));
}

Standard_Integer 
tnbLib::maker::TopoProfile::CreateInterplProfile
(
	const std::shared_ptr<SectPx_Cloud>& theCloud
)
{
	auto profile = 
		SectPx_InterplProfile::MakeProfile(theCloud, Registry());
	Debug_Null_Pointer(profile);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(profile));
}

std::shared_ptr<tnbLib::SectPx_TopoProfile> 
tnbLib::maker::TopoProfile::RemoveProfile
(
	const Standard_Integer theIndex
)
{
	auto item = SelectProfile(theIndex);
	Debug_Null_Pointer(item);

	if (NOT std::dynamic_pointer_cast<SectPx_TopoProfile>(item))
	{
		FatalErrorIn(FunctionSIG)
			<< " the selected item is not profile!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Registry());
	Registry()->Remove(item);
	return std::move(item);
}

std::vector<std::shared_ptr<tnbLib::SectPx_TopoProfile>> 
tnbLib::maker::TopoProfile::RetrieveProfiles() const
{
	std::vector<std::shared_ptr<SectPx_TopoProfile>> profiles;
	RetrieveProfilesTo(profiles);
	return std::move(profiles);
}

void tnbLib::maker::TopoProfile::RetrieveProfilesTo
(
	std::vector<std::shared_ptr<SectPx_TopoProfile>>& theProfiles
) const
{
	std::vector<std::shared_ptr<SectPx_TopoProfile>>
		profiles;
	for (const auto& x : Registry()->Objects())
	{
		Debug_Null_Pointer(x.second);
		const auto& obj = x.second;

		auto ptr = std::dynamic_pointer_cast<SectPx_TopoProfile>(obj);
		if (ptr)
		{
			theProfiles.push_back(std::move(ptr));
		}
	}
}