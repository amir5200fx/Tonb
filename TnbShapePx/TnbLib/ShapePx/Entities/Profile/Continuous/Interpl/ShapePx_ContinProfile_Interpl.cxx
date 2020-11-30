#include <ShapePx_ContinProfile_Interpl.hxx>

tnbLib::shapePxLib::ContinProfile_Interpl::~ContinProfile_Interpl()
{
	gsl_spline_free(theSpline_);
	gsl_interp_accel_free(theAcc_);
}

Standard_Real
tnbLib::shapePxLib::ContinProfile_Interpl::Lower() const
{
	if (theQs_.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "there are not enough offset points for the profile" << endl
			<< abort(FatalError);
	}
	return theQs_[0].x;
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_Interpl::Upper() const
{
	if (theQs_.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "there are not enough offset points for the profile" << endl
			<< abort(FatalError);
	}
	return theQs_[theQs_.size() - 1].x;
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_Interpl::LowerValue() const
{
	if (theQs_.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "there are not enough offset points for the profile" << endl
			<< abort(FatalError);
	}
	return theQs_[0].y;
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_Interpl::UpperValue() const
{
	if (theQs_.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "there are not enough offset points for the profile" << endl
			<< abort(FatalError);
	}
	return theQs_[theQs_.size() - 1].y;
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_Interpl::Value
(
	const Standard_Real x
) const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the interpolation is not performed!" << endl
			<< abort(FatalError);
	}
	return gsl_spline_eval(theSpline_, x, theAcc_);
}

void tnbLib::shapePxLib::ContinProfile_Interpl::Perform()
{
	if (NOT theAcc_)
	{
		theAcc_ = gsl_interp_accel_alloc();
	}
	if (NOT theSpline_)
	{
		switch (theType_)
		{
		case tnbLib::shapePxLib::ContinProfile_Interpl::interplType::cspline:
			theSpline_ = gsl_spline_alloc(gsl_interp_cspline, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_Interpl::interplType::cspline_periodic:
			theSpline_ = gsl_spline_alloc(gsl_interp_cspline_periodic, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_Interpl::interplType::linear:
			theSpline_ = gsl_spline_alloc(gsl_interp_linear, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_Interpl::interplType::polynomial:
			theSpline_ = gsl_spline_alloc(gsl_interp_polynomial, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_Interpl::interplType::akima:
			theSpline_ = gsl_spline_alloc(gsl_interp_akima, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_Interpl::interplType::akima_perodic:
			theSpline_ = gsl_spline_alloc(gsl_interp_akima_periodic, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_Interpl::interplType::steffen:
			theSpline_ = gsl_spline_alloc(gsl_interp_steffen, 5);
			break;
		default:
			FatalErrorIn(FunctionSIG)
				<< "unrecognized interpolation type!" << endl
				<< abort(FatalError);
			break;
		}
	}

	double* xs = new double[theQs_.size()];
	double* ys = new double[theQs_.size()];
	for (size_t i = 0; i < theQs_.size(); i++)
	{
		xs[i] = theQs_[i].x;
		ys[i] = theQs_[i].y;
	}

	gsl_spline_init(theSpline_, xs, ys, theQs_.size());

	delete[] xs;
	delete[] ys;

	Change_IsDone() = Standard_True;
}

