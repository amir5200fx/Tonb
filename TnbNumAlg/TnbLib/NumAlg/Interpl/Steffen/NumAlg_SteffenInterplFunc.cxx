#include <NumAlg_SteffenInterplFunc.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::NumAlg_SteffenInterplFunc::NumAlg_SteffenInterplFunc
(
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
)
	: theQs_(theQs)
{
	Perform();
}

tnbLib::NumAlg_SteffenInterplFunc::NumAlg_SteffenInterplFunc
(
	std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
)
	: theQs_(std::move(theQs))
{
	Perform();
}

void tnbLib::NumAlg_SteffenInterplFunc::Perform()
{
	if (Qs().size() < 5)
	{
		FatalErrorIn(FunctionSIG)
			<< "no enough offset points are provided!" << endl
			<< abort(FatalError);
	}

	auto x = new double[Qs().size()];
	auto y = new double[Qs().size()];
	for (size_t i = 0; i < Qs().size(); i++)
	{
		x[i] = Qs().at(i).first;
		y[i] = Qs().at(i).second;
	}
	
	gsl_interp_accel *acc = gsl_interp_accel_alloc();
	gsl_spline *spline_steffen = gsl_spline_alloc(gsl_interp_steffen, Qs().size());
	gsl_spline_init(spline_steffen, x, y, Qs().size());

	SplineInterplRef() = spline_steffen;
	AccelerationRef() = acc;

	Change_IsDone() = Standard_True;
}

tnbLib::NumAlg_SteffenInterplFunc::~NumAlg_SteffenInterplFunc()
{
	gsl_spline_free(theSpline_);
	gsl_interp_accel_free(theAcc_);
}

Standard_Integer 
tnbLib::NumAlg_SteffenInterplFunc::NbSamples() const
{
	return (Standard_Integer)theQs_.size();
}

Standard_Real 
tnbLib::NumAlg_SteffenInterplFunc::Value(const Standard_Real x) const
{
#ifdef _DEBUG
	if (NOT INSIDE(x, FirstItem(Qs()).first, LastItem(Qs()).first))
	{
		FatalErrorIn(FunctionSIG)
			<< "out of domain!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	Debug_If_Condition(NOT IsDone());
	return gsl_spline_eval(SplineInterpl(), x, Acceleration());
}

std::pair<Standard_Real, Standard_Real> 
tnbLib::NumAlg_SteffenInterplFunc::Sample
(
	const Standard_Integer theIndex
) const
{
	return Qs().at(theIndex);
}

std::vector<std::pair<Standard_Real, Standard_Real>> 
tnbLib::NumAlg_SteffenInterplFunc::RetrieveSamples() const
{
	return Qs();
}