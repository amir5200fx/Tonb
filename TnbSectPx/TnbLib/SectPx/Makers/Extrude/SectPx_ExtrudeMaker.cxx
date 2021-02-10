#include <SectPx_ExtrudeMaker.hxx>

#include <SectPx_ShapeRegistry.hxx>
#include <SectPx_ExtrProfiles.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_ExtrProfile> 
tnbLib::maker::Extrude::SelectProfile
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto profile = std::dynamic_pointer_cast<SectPx_ExtrProfile>(item);
	if (NOT profile)
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not a extrusion profile!" << endl
			<< abort(FatalError) << endl;
	}
	return std::move(profile);
}

Standard_Integer 
tnbLib::maker::Extrude::CreateUniform
(
	const std::shared_ptr<SectPx_Par>& theX0,
	const std::shared_ptr<SectPx_Par>& theX1, 
	const std::shared_ptr<SectPx_Par>& theValue
) const
{
	auto profile = std::make_shared<sectPxLib::ExtrProfile_Uniform>();
	Debug_Null_Pointer(profile);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(profile);

	profile->SetX0(theX0);
	profile->SetX1(theX1);
	profile->SetValue(theValue);

	return id;
}

Standard_Integer 
tnbLib::maker::Extrude::CreateLinear
(
	const std::shared_ptr<SectPx_Par>& theX0, 
	const std::shared_ptr<SectPx_Par>& theX1, 
	const std::shared_ptr<SectPx_Par>& theValue0,
	const std::shared_ptr<SectPx_Par>& theValue1
) const
{
	auto profile = std::make_shared<sectPxLib::ExtrProfile_Linear>();
	Debug_Null_Pointer(profile);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(profile);

	profile->SetX0(theX0);
	profile->SetX1(theX1);
	profile->SetValue0(theValue0);
	profile->SetValue1(theValue1);

	return id;
}

Standard_Integer 
tnbLib::maker::Extrude::CreateThreePoint
(
	const std::shared_ptr<SectPx_Par>& theX0, 
	const std::shared_ptr<SectPx_Par>& theX1, 
	const std::shared_ptr<SectPx_Par>& theX2, 
	const std::shared_ptr<SectPx_Par>& theValue0, 
	const std::shared_ptr<SectPx_Par>& theValue1,
	const std::shared_ptr<SectPx_Par>& theValue2
) const
{
	auto profile = std::make_shared<sectPxLib::ExtrProfile_ThreePoint>();
	Debug_Null_Pointer(profile);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(profile);

	profile->SetX0(theX0);
	profile->SetX1(theX1);
	profile->SetX2(theX2);
	profile->SetValue0(theValue0);
	profile->SetValue1(theValue1);
	profile->SetValue2(theValue2);

	return id;
}

Standard_Integer 
tnbLib::maker::Extrude::CreateFivePoint
(
	const std::shared_ptr<SectPx_Par>& theX0,
	const std::shared_ptr<SectPx_Par>& theX1,
	const std::shared_ptr<SectPx_Par>& theX2,
	const std::shared_ptr<SectPx_Par>& theX3,
	const std::shared_ptr<SectPx_Par>& theX4,
	const std::shared_ptr<SectPx_Par>& theValue0,
	const std::shared_ptr<SectPx_Par>& theValue1,
	const std::shared_ptr<SectPx_Par>& theValue2,
	const std::shared_ptr<SectPx_Par>& theValue3,
	const std::shared_ptr<SectPx_Par>& theValue4
) const
{
	auto profile = std::make_shared<sectPxLib::ExtrProfile_FivePoint>();
	Debug_Null_Pointer(profile);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(profile);

	profile->SetX0(theX0);
	profile->SetX1(theX1);
	profile->SetX2(theX2);
	profile->SetX3(theX3);
	profile->SetX4(theX4);
	profile->SetValue0(theValue0);
	profile->SetValue1(theValue1);
	profile->SetValue2(theValue2);
	profile->SetValue3(theValue3);
	profile->SetValue4(theValue4);

	return id;
}

std::shared_ptr<tnbLib::SectPx_ExtrProfile> 
tnbLib::maker::Extrude::RemoveProfile
(
	const Standard_Integer theIndex
) const
{
	auto item = SelectProfile(theIndex);
	Debug_Null_Pointer(item);

	Debug_Null_Pointer(Registry());
	Registry()->Remove(item);
	return std::move(item);
}