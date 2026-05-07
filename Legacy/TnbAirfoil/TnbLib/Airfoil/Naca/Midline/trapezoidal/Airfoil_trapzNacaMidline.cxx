#include <Airfoil_trapzNacaMidline.hxx>

Standard_Real 
tnbLib::Airfoil_trapzNacaMidline::CalcY
(
	const Standard_Real xPerc
) const
{
	
	
	const auto oneM_A = 1.0 - A();
	const auto oneM_A_pow2 = oneM_A * oneM_A;
	const auto inv_oneM_A = 1.0 / oneM_A;
	const auto g = -inv_oneM_A*(A()*A()*(0.5*log(A()) - 0.25) + 0.25);
	const auto h = inv_oneM_A * (0.5*oneM_A_pow2*log(oneM_A) - 0.25*oneM_A_pow2) + g;

	const auto c1 = Cli() / (2.0*PI*(A() + 1.0));

	const auto Am_xperc = A() - xPerc;
	const auto oneM_xperc = 1.0 - xPerc;
	const auto Am_xperc_pow2 = Am_xperc * Am_xperc;
	const auto oneM_xperc_pow2 = oneM_xperc * oneM_xperc;

	const auto c2 = 
		0.5*Am_xperc_pow2*log(std::abs(Am_xperc)) 
		- 0.5*oneM_xperc_pow2*log(oneM_xperc) 
		+ 0.25*oneM_xperc_pow2 
		- 0.25*Am_xperc_pow2;
	const auto c3 = inv_oneM_A * c2 - xPerc * log(xPerc) + g - h * xPerc;
	return Chord()*c1 * c3;
}