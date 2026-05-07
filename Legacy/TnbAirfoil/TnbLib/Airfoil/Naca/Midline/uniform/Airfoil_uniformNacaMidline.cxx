#include <Airfoil_uniformNacaMidline.hxx>

Standard_Real 
tnbLib::Airfoil_uniformNacaMidline::CalcY
(
	const Standard_Real xPerc
) const
{
	static const auto fourPhi = 4.0*PI;
	const auto ln1 = log(1.0 - xPerc);
	const auto ln2 = log(xPerc);

	return (-Cli() / fourPhi)*((1.0 - xPerc)*ln1 + xPerc * ln2);
}