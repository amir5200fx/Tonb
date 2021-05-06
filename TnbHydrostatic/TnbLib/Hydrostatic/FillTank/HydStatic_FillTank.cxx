#include <HydStatic_FillTank.hxx>

#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <Geo_CosineDistb.hxx>
#include <Marine_Body_Tank.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_BodyCmptLib.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <Marine_System.hxx>
#include <HydStatic_FillCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

Standard_Real tnbLib::HydStatic_FillTank::DELTA_WATER_COEFF = 0.005;
unsigned short tnbLib::HydStatic_FillTank::verbose = 0;

namespace tnbLib
{
	auto ConvertToOffset(const std::vector<marineLib::xSectionParam>& Qs)
	{
		typedef HydStatic_FillCurve::offSet offset;
		std::vector<offset> offsets;
		offsets.reserve(Qs.size());
		for (const auto& x : Qs)
		{
			auto par = offset{ x.x,x.value };
			offsets.push_back(std::move(par));
		}
		return std::move(offsets);
	}
}

void tnbLib::HydStatic_FillTank::Perform()
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Calculating FillCurve for Tank ********" << endl;
		Info << endl;
	}

	if (NOT Tank())
	{
		FatalErrorIn(FunctionSIG)
			<< "no tank has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< " No domain has been loaded!" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		Info << " Body's name: " << Tank()->Name() << endl;
		Info << " nb. of sections: " << Tank()->NbSections() << endl;
	}

	const auto b = Marine_BodyTools::BoundingBox(*Tank());

	if (verbose)
	{
		Info << endl;
		Info << " - Span of the Z: " << endl;
		Info << "   z0 = " << b.P0().Z() << ", z1 = " << b.P1().Z() << endl;
		Info << endl;
	}
	const auto Z = HydStatic_FillTank::Z(b.P0().Z(), b.P1().Z(), NbWaters());

	const auto& domain = Domain();
	auto domains = Marine_WaterLib::MultiLevelsStillWaterDomain(*Tank(), domain, *Z);
	Debug_Null_Pointer(domains);

	if (verbose) Info << " nb. of waters: " << domains->Waters().size() << endl;
	if (verbose) Info << " calculating the volumes..." << endl;

	Handle(Geom2d_Curve) curve;
	std::vector<HydStatic_FillCurve::offSet> offsets;
	{// timer scope
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		auto curveQ = 
			Marine_BodyCmptLib::Volume
			(
				*Tank(), 
				*domains,
				sysLib::gl_marine_integration_info
			);

		offsets = ConvertToOffset(curveQ);

		if (curveQ.size() < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "there are not enough data points to create a curve" << endl
				<< abort(FatalError);
		}

		if (verbose) Info << " creating the geometric curve..." << endl;
		curve = MarineBase_Tools::Curve(curveQ);
	}
	Debug_Null_Pointer(curve);
	if (verbose)
	{
		Info << "the volume-curve is calculated in, " << global_time_duration << " ms" << endl;
	}

	auto fillCurve = 
		std::make_shared<HydStatic_FillCurve>(0, "fill-curve", std::move(curve));
	Debug_Null_Pointer(fillCurve);

	fillCurve->SetQs(std::move(offsets));

	theCurve_ = std::move(fillCurve);
	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of the FillCurve Calculating ********" << endl;
		Info << endl;
	}
}

std::shared_ptr<tnbLib::Geo_xDistb> 
tnbLib::HydStatic_FillTank::Z
(
	const Standard_Real z0, 
	const Standard_Real z1,
	const Standard_Integer n
)
{
	if (n < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< " invalid nb. of waters has been detected!" << endl
			<< " - nb. of waters: " << n << endl
			<< abort(FatalError);
	}
	const auto c = (z1 - z0) / 2;
	const auto dt = M_PI / (Standard_Real)n;
	const auto dz = c * ((Standard_Real)1.0 - std::cos(dt));

	auto disZ = std::make_shared<Geo_CosineDistb>(n);
	Debug_Null_Pointer(disZ);

	disZ->SetLower(z0 + DELTA_WATER_COEFF*dz);
	disZ->SetUpper(z1 + DELTA_WATER_COEFF *dz);
	disZ->Perform();

	return std::move(disZ);
}