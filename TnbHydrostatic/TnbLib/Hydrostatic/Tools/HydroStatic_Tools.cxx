#include <HydroStatic_Tools.hxx>

#include <Cad2d_CmptLib.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <StdFail_NotDone.hxx>

Standard_Real 
tnbLib::HydroStatic_Tools::CalcArea
(
	const std::vector<hsLib::xSection>& theQ
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn("Standard_Real  tnbLib::HydroStatic_Tools::CalcVolume(const std::vector<hsLib::xArea>& theQ)")
			<< "Not enough points"
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) PtsPtr = new TColgp_HArray1OfPnt2d(1, (Standard_Integer)theQ.size());
	auto& Pts = *PtsPtr;

	Standard_Integer K = 0;
	for (const auto& x : theQ)
	{
		Pts.SetValue(++K, gp_Pnt2d(x.x, x.value));
	}

	Geom2dAPI_Interpolate Interpolation(PtsPtr, Standard_False, 1.0-6);
	Interpolation.Perform();

	if (!Interpolation.IsDone())
	{
		FatalErrorIn("Standard_Real  tnbLib::HydroStatic_Tools::CalcVolume(const std::vector<hsLib::xArea>& theQ)")
			<< "Failed to interpolation!"
			<< abort(FatalError);
	}

	try
	{
		auto info = std::make_shared<NumAlg_AdaptiveInteg_Info>();
		Debug_Null_Pointer(info);

		info->SetNbInitIterations(4);
		info->SetTolerance(1.0E-5);

		return Cad2d_CmptLib::AreaUnderCurve(Interpolation.Curve(), 0, info);
	}
	catch (StdFail_NotDone&)
	{
		FatalErrorIn("Standard_Real  tnbLib::HydroStatic_Tools::CalcVolume(const std::vector<hsLib::xArea>& theQ)")
			<< "Failed to interpolation!"
			<< abort(FatalError);

		return 0;
	}
}