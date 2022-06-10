#include <Cad_gMetricRepair.hxx>

#include <GModel_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>
#include <gp_Trsf2d.hxx>

template<>
void tnbLib::Cad_gMetricRepair::Perform()
{
	if (CharLenU() <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid char length has been detected." << endl
			<< abort(FatalError);
	}

	if (CharLenV() <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid char length has been detected." << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Domain());
	const auto& b = *Domain();

	const auto& P0 = b.P0();
	const auto& P1 = b.P1();

	const auto du = P1.X() - P0.X();
	const auto dv = P1.Y() - P0.Y();

	const auto ar = std::max(CharLenU() / CharLenV(), CharLenV() / CharLenU());

	const auto scale = 100 * ar; //std::max(CharLenU(), CharLenV()) / std::max(du, dv);

	gp_Trsf2d transf;
	transf.SetScale(P0, scale);

	if (scale > 1)
	{
		ReparameterizedRef() = GModel_Tools::ReParameterization(Patch(), scale);
	}
	else
	{
		ReparameterizedRef() = Patch();
	}
	
	theTrsf_ = std::move(transf);

	Change_IsDone() = Standard_True;
}