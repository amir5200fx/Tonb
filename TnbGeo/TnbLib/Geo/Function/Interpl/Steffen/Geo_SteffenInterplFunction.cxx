#include <Geo_SteffenInterplFunction.hxx>


tnbLib::Geo_SteffenInterplFunction::Geo_SteffenInterplFunction()
	: acc_(nullptr)
	, spline_steffen_(nullptr)
{}

tnbLib::Geo_SteffenInterplFunction::~Geo_SteffenInterplFunction()
{
	if (x) delete x;
	if (y) delete y;
}

Standard_Integer tnbLib::Geo_SteffenInterplFunction::NbSamples() const
{ return static_cast<Standard_Integer>(theQs_.size()); }

Standard_Real tnbLib::Geo_SteffenInterplFunction::Value(const Standard_Real x) const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	return gsl_spline_eval(spline_steffen_, x, acc_);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::Geo_SteffenInterplFunction::Sample(const Standard_Integer theIndex) const
{
	return theQs_.at(theIndex);
}

std::vector<std::pair<Standard_Real, Standard_Real>>
tnbLib::Geo_SteffenInterplFunction::RetrieveSamples() const
{
	return theQs_;
}

void tnbLib::Geo_SteffenInterplFunction::Perform()
{
	if (Qs().size() < 5)
	{
		FatalErrorIn(FunctionSIG)
			<< "no enough offset point!" << endl
			<< abort(FatalError);
	}
	acc_ = gsl_interp_accel_alloc();
	spline_steffen_ = gsl_spline_alloc(gsl_interp_steffen, Qs().size());

	x = new double[Qs().size()];
	y = new double[Qs().size()];

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
