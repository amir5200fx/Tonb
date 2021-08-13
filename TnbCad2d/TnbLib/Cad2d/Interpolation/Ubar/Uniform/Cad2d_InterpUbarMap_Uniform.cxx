#include <Cad2d_InterpUbarMap_Uniform.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<Standard_Real> 
tnbLib::Cad2d_InterpUbarMap_Uniform::CalcUk(const std::vector<Pnt2d>& theQ) const
{
	if (theQ.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid data: not enough nb. of points" << endl
			<< abort(FatalError);
	}
	const auto n = theQ.size() - (size_t)1;

	std::vector<Standard_Real> us;
	us.resize(theQ.size());

	us[0] = 0.0;
	for (size_t k = 1; k <= n - 1; k++)
	{
		us[k] = (Standard_Real)k / (Standard_Real)n;
	}
	us[n] = 1.0;
	return std::move(us);
}