#include <HydStatic_DisContinuBonjean.hxx>

#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::HydStatic_DisContinuBonjean::SectionClips>
tnbLib::HydStatic_DisContinuBonjean::SectionClips::reCalculate
(
	const Standard_Real coeff
) const
{
	std::vector<std::shared_ptr<Clip>> clips;
	clips.reserve(NbClips());
	for (const auto& x : Clips())
	{
		Debug_Null_Pointer(x);
		auto clip = x->Scaled(coeff);

		clips.push_back(std::move(clip));
	}
	auto clip = std::make_shared<SectionClips>();
	Debug_Null_Pointer(clip);

	clip->SetSection(Section());
	clip->SetClips(std::move(clips));

	return std::move(clip);
}

std::shared_ptr<tnbLib::HydStatic_DisContinuBonjean::SectionClips>
tnbLib::HydStatic_DisContinuBonjean::SectionClips::FitToSpan
(
	const span & s
) const
{
	const auto Zmin = s.X0();
	const auto Zmax = s.X1();

	span s0(Zmin, Z0());
	span s1(Z1(), Zmax);

	auto seg0 = MakeSegment(s0, Value0());
	auto seg1 = MakeSegment(s1, Value1());

	auto section = std::make_shared<SectionClips>();
	Debug_Null_Pointer(section);

	section->SetSection(Section());
	for (const auto& x : Clips())
	{
		Debug_Null_Pointer(x);
		section->Add(x);
	}
	return std::move(section);
}

std::pair<std::vector<std::shared_ptr<tnbLib::HydStatic_DisContinuBonjean::SectionClips>>, Standard_Real>
tnbLib::HydStatic_DisContinuBonjean::reCalculate
(
	const std::vector<std::shared_ptr<SectionClips>>& theClips,
	const Standard_Real theMaxDegree
)
{
	Standard_Real maxAngle = 0;
	std::shared_ptr<SectionClips> section;
	for (const auto& x : theClips)
	{
		Debug_Null_Pointer(x);

		auto angle = x->CalcAngle();
		if (angle > maxAngle)
		{
			maxAngle = angle;
			section = x;
		}
	}

	if (maxAngle <= theMaxDegree)
	{
		auto t = std::make_pair(theClips, 1.0);
		return std::move(t);
	}

	const auto dz = section->Dz();
	const auto dx = section->MaxValue();

	const auto coeff = dx / (std::tan(Geo_Tools::DegToRadian(theMaxDegree))*dz);

	std::vector<std::shared_ptr<SectionClips>> clips;
	clips.reserve(theClips.size());
	for (const auto& x : theClips)
	{
		Debug_Null_Pointer(x);
		auto clip = x->reCalculate(coeff);

		clips.push_back(std::move(clip));
	}
	auto t = std::make_pair(std::move(clips), coeff);
	return std::move(t);
}

std::vector<std::shared_ptr<tnbLib::HydStatic_DisContinuBonjean::SectionClips>>
tnbLib::HydStatic_DisContinuBonjean::Sync
(
	const std::vector<std::shared_ptr<SectionClips>>& theClips, 
	const Standard_Real z0, 
	const Standard_Real z1
)
{
	span s(z0, z1);

	std::vector<std::shared_ptr<SectionClips>> clips;
	clips.reserve(theClips.size());
	for (const auto& x : theClips)
	{
		Debug_Null_Pointer(x);

		auto clip = x->FitToSpan(s);
		clips.push_back(std::move(clip));
	}
	return std::move(clips);
}