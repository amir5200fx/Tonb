#include <ShapePx_ContinProfile_ThreePoints.hxx>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_spline.h>

tnbLib::shapePxLib::ContinProfile_ThreePoints::~ContinProfile_ThreePoints()
{
	gsl_spline_free(theSpline_);
	gsl_interp_accel_free(theAcc_);
}

Standard_Real 
tnbLib::shapePxLib::ContinProfile_ThreePoints::Value
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

void tnbLib::shapePxLib::ContinProfile_ThreePoints::Perform()
{
	if (NOT theAcc_)
	{
		theAcc_ = gsl_interp_accel_alloc();
	}
	if (NOT theSpline_)
	{
		switch (theType_)
		{
		case tnbLib::shapePxLib::ContinProfile_ThreePoints::interplType::cspline:
			theSpline_ = gsl_spline_alloc(gsl_interp_cspline, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_ThreePoints::interplType::cspline_periodic:
			theSpline_ = gsl_spline_alloc(gsl_interp_cspline_periodic, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_ThreePoints::interplType::linear:
			theSpline_ = gsl_spline_alloc(gsl_interp_linear, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_ThreePoints::interplType::polynomial:
			theSpline_ = gsl_spline_alloc(gsl_interp_polynomial, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_ThreePoints::interplType::akima:
			theSpline_ = gsl_spline_alloc(gsl_interp_akima, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_ThreePoints::interplType::akima_perodic:
			theSpline_ = gsl_spline_alloc(gsl_interp_akima_periodic, 5);
			break;
		case tnbLib::shapePxLib::ContinProfile_ThreePoints::interplType::steffen:
			theSpline_ = gsl_spline_alloc(gsl_interp_steffen, 5);
			break;
		default:
			FatalErrorIn(FunctionSIG)
				<< "unrecognized interpolation type!" << endl
				<< abort(FatalError);
			break;
		}
	}

	double x[5], y[5];
	x[0] = X0();
	x[1] = X1();
	x[2] = X2();
	x[3] = x[2] + (X2() - X1());
	x[4] = x[3] + (X1() - X0());

	y[0] = Value0();
	y[1] = Value1();
	y[2] = Value2();
	y[3] = y[2] + (Value2() - Value1());
	y[4] = y[3] + (Value1() - Value0());

	gsl_spline_init(theSpline_, x, y, 5);

	Change_IsDone() = Standard_True;
}