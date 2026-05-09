#include <Model_DisplNo1.hxx>

#include <Model_LinearParamProfile.hxx>
#include <Model_UniformParamProfile.hxx>
#include <Model_CmpProfile.hxx>

std::shared_ptr<tnbLib::Model_ParamProfile> 
tnbLib::Model_DisplNo1::CreateKeelProfile() const
{
	const auto& dimens = Parameters().Dimensions();
	const auto nbSections = dimens.NbNetColumns();

	const auto& xs = XPars().XCoords();
	const auto length = xs.at(nbSections - 2);

	const auto& keel = Parameters().Keel();
	const auto xPos = keel.Position()->Value() * length;
	
	std::vector<std::shared_ptr<Model_ParamProfile>> profiles;
	profiles.reserve(2);
	// constructing the first part of the profile [12/29/2022 Payvand]
	{
		auto p0 = std::make_pair(Model_DisplNo1::Zero, dimens.DepthAtTransom());
		auto p1 = std::make_pair(xPos, Model_DisplNo1::Keel);

		auto profile = 
			std::make_shared<Model_LinearParamProfile>(std::move(p0), std::move(p1));
		profiles.push_back(std::move(profile));
	}

	// constructing the second part of the profile [12/29/2022 Payvand]
	{
		auto profile = 
			std::make_shared<Model_UniformParamProfile>(xPos, length, Model_DisplNo1::Keel);
		profiles.push_back(std::move(profile));
	}
	auto p = std::make_shared<Model_CmpProfile>(std::move(profiles));
	return std::move(p);
}