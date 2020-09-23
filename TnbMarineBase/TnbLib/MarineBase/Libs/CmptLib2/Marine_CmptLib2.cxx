#include <Marine_CmptLib2.hxx>

#include <Marine_CmpSection.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_BooleanOps.hxx>
#include <Marine_WaterDomain.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::marineLib::xSectionParam 
tnbLib::Marine_CmptLib2::LeverArm
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const Standard_Real x0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	const auto volQ = MarineBase_Tools::CalcVolume(theSections, theInfo);
	const auto vol = MarineBase_Tools::CalcArea(volQ, theInfo);

	const auto IvQ = MarineBase_Tools::CalcIy(theSections, x0, theInfo);
	const auto Iv = MarineBase_Tools::CalcArea(IvQ, theInfo);

	if (ABS(vol) <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "divided by zero encountered! volume = " << vol << endl
			<< abort(FatalError);
	}

	marineLib::xSectionParam v;
	v.value = Iv / vol;
	v.x = vol;

	return std::move(v);
}

Standard_Real 
tnbLib::Marine_CmptLib2::LeverArm
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const Standard_Real x0, 
	const Standard_Real theVolume, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	const auto IyQ = MarineBase_Tools::CalcIy(theSections, x0, theInfo);
	const auto Iy = MarineBase_Tools::CalcArea(IyQ, theInfo);

	if (ABS(theVolume) <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "divided by zero encountered!" << endl
			<< abort(FatalError);
	}

	return Iy / theVolume;
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::Marine_CmptLib2::CrossCurve
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const std::vector<std::shared_ptr<Marine_WaterDomain>>& theWaters, 
	const Standard_Real x0,
	const gp_Ax1 & theK, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	if (theWaters.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "not enough sections for waters" << endl
			<< abort(FatalError);
	}

	const auto& keel = theK.Location();

	std::vector<marineLib::xSectionParam> curves;
	for (const auto& x : theWaters)
	{
		Debug_Null_Pointer(x);

		auto wetted = Marine_BooleanOps::WettedSections(theSections, x->Waters());

		if (wetted.size())
		{
			auto volQ = MarineBase_Tools::CalcVolume(wetted, theInfo);
			auto vol = MarineBase_Tools::CalcArea(volQ, theInfo);

			if (vol >= 1.0E-4)
			{
				auto la = LeverArm(theSections, x0, vol, theInfo);

				marineLib::xSectionParam v;
				v.x = vol;
				v.value = la;

				curves.push_back(std::move(v));
			}
		}
	}
	return std::move(curves);
}