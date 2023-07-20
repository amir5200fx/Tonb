#include <HydDyna_Holtrop.hxx>

void tnbLib::HydDyna_Holtrop::CalcLR()
{
	theLR_ =
		Ship()->L() *
		(1.0 - 
			Ship()->CP() + 
			0.06 * Ship()->CP() * Ship()->LCB() / (4.0 * Ship()->CP() - 1.0));
}

void tnbLib::HydDyna_Holtrop::CalcFircResist()
{
	const auto re = Density() * Velocity() * Ship()->L() / Viscosity();
	
	const auto c = std::log10(re) - 2.0;
	const auto cf = 0.075 / (c * c);

	theResist_.SetRF(0.5 * Density() * Velocity() * Velocity() * theCoeffs_.S * cf);
}

void tnbLib::HydDyna_Holtrop::CalcTransomPressResist()
{
	theResist_.SetRTR(0.5 * Density() * Velocity() * Velocity() * Ship()->AT() * theCoeffs_.c6);
}

void tnbLib::HydDyna_Holtrop::CalcCorrlResist()
{
	theResist_.SetRA(0.5 * Density() * Velocity() * Velocity() * theCoeffs_.S * theCoeffs_.CA);
}

void tnbLib::HydDyna_Holtrop::CalcWaveResist()
{
	const auto d = -0.9;
	const auto Fn = Velocity() / std::sqrt(Gravity() * Ship()->L());

}

void tnbLib::HydDyna_Holtrop::CalcFrouds()
{
	theFroudes_.CalcVariables(*Ship(), Velocity(), Gravity());
	if (theFroudes_.FnT < 5.0)
		theCoeffs_.c6 = 0.2 * (1.0 - 0.2 * theFroudes_.FnT);
	else
		theCoeffs_.c6 = 0.0;
}