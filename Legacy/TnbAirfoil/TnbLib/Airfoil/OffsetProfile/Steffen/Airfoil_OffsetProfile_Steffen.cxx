#include <Airfoil_OffsetProfile_Steffen.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Airfoil_OffsetProfile_Steffen::Value(const Standard_Real x) const
{
	return gsl_spline_eval(spline_steffen_, x, acc_);
}

void tnbLib::Airfoil_OffsetProfile_Steffen::Perform()
{
	if (Qs().size() < 5)
	{
		FatalErrorIn(FunctionSIG)
			<< "no enough offset point!" << endl
			<< abort(FatalError);
	}
	
	acc_ = gsl_interp_accel_alloc();
	spline_steffen_ = gsl_spline_alloc(gsl_interp_steffen, Qs().size());

	auto x = new double[Qs().size()];
	auto y = new double[Qs().size()];

	const auto& qs = Qs();
	for (size_t i = 0; i < Qs().size(); i++)
	{
		x[i] = qs[i].first;
		y[i] = qs[i].second;
		//std::cout << "stefen: " << x[i] << ", " << y[i] << std::endl;
	}

	gsl_spline_init(spline_steffen_, x, y, qs.size());

	Change_IsDone() = Standard_True;
}