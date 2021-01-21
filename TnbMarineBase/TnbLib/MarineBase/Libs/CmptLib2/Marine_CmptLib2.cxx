#include <Marine_CmptLib2.hxx>

#include <Global_Timer.hxx>
#include <Dir3d.hxx>
#include <Marine_Water.hxx>
#include <Marine_CmpSection.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_BooleanOps.hxx>
#include <Marine_WaterDomain.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::Marine_CmptLib2::LeverArm_Verbose1(0);
unsigned short tnbLib::Marine_CmptLib2::LeverArm_Verbose2(0);
unsigned short tnbLib::Marine_CmptLib2::CrossCurve_Verbose(0);

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
	static auto verbose = LeverArm_Verbose2;
	if (verbose)
	{
		Info << endl;
		Info << "******* Marine_CmptLib2: Calculating Lever-Arm ********" << endl;
		Info << endl;
	}
	if (verbose)
	{
		Info << " calculating Iy at every sections ..." << endl;
	}
	/*for (const auto& x : theSections)
	{
		const auto xBar = MarineBase_Tools::CalcXCentre(*x, theInfo);
		Info << xBar << endl;
	}
	PAUSE;*/
	const auto MyQ = MarineBase_Tools::CalcMy(theSections, x0, theInfo);
	if (verbose)
	{
		Info << " calculating the Iy by integrating..." << endl;
	}
	const auto My = MarineBase_Tools::CalcArea(MyQ, theInfo);

	if (ABS(theVolume) <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "divided by zero encountered!" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		Info << endl;
		Info << "******* Marine_CmptLib2: End of the Calculating Lever-Arm ********" << endl;
		Info << endl;
	}
	return My / theVolume;
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
	static auto verbose = CrossCurve_Verbose;
	if (verbose)
	{
		Info << endl;
		Info << "******* Marine_CmptLib2: Calculating Cross-Curve ********" << endl;
		Info << endl;
	}
	const static Standard_Real vol_criterion = 1.0E-4;

	if (theWaters.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "not enough sections for waters" << endl
			<< abort(FatalError);
	}

	const auto& keel = theK.Location();

	if (verbose > 1)
	{
		Info << " keel location: " <<theK.Location() << endl;
		Info << " keel axis: " << theK.Direction() << endl;
	}

	if (verbose)
	{
		Info << " nb. of the waters: " << theWaters.size() << endl;
	}

	std::vector<marineLib::xSectionParam> curves;
	for (const auto& x : theWaters)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Water());

		if (verbose > 1)
		{
			Info << " water's id: " << x->Index() << endl;
			Info << " calculating the wetted sections..." << endl;
		}
		{ // time scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			if (verbose > 1)
			{
				Info << " calculating the wetted sections..." << endl;
			}
			auto wetted = Marine_BooleanOps::WettedSections(theSections, x->Water()->Sections());

			if (wetted.size())
			{
				if (verbose > 1)
				{
					Info << " wetted sections have been detected." << endl;
					Info << " nb. of wetted sections: " << wetted.size() << endl;
					Info << " calculating the volume..." << endl;
				}
				auto volQ = MarineBase_Tools::CalcVolume(wetted, theInfo);
				auto vol = MarineBase_Tools::CalcArea(volQ, theInfo);
				if (verbose > 1)
				{
					Info << " volume= " << vol << endl;
					Info << " for volume bigger than " << vol_criterion << ", the lever arm is calculated" << endl;
				}

				if (vol >= vol_criterion)
				{
					if (verbose > 1) Info << " calculating the lever-arm..." << endl;
					auto la = LeverArm(wetted, x0, vol, theInfo);
					if (verbose > 1)
					{
						Info << " the lever-arm is calculated, successfully..." << endl;
						Info << " lever-arm= " << la;
					}
					marineLib::xSectionParam v;
					v.x = vol;
					v.value = la;

					curves.push_back(std::move(v));
				}
			}
			else
			{
				if (verbose > 1)
				{
					Info << " no wetted section has been detected!" << endl;
				}
			}
		}
		if (verbose > 1)
		{
			Info << " the cross-curve for the domain is calculated in, " << global_time_duration << " ms" << endl;
		}
	}

	if (verbose)
	{
		Info << endl;
		Info << "******* Marine_CmptLib2: End of the Calculating Cross-Curve ********" << endl;
		Info << endl;
	}
	return std::move(curves);
}