#pragma once
#ifndef _floatScalar_Header
#define _floatScalar_Header

#include <doubleFloat.hxx>
#include <direction.hxx>
#include <word.hxx>

namespace tnbLib
{
	typedef float floatScalar;

	// Largest and smallest scalar values allowed in certain parts of the code
	// (6 is the number of significant figures in an
	//  IEEE single precision number.  See limits.h or float.h)
	static const floatScalar floatScalarGREAT = (floatScalar)1.0e+6;
	static const floatScalar floatScalarVGREAT = (floatScalar)1.0e+37;
	static const floatScalar floatScalarROOTVGREAT = (floatScalar)1.0e+18;
	static const floatScalar floatScalarSMALL = (floatScalar)1.0e-6;
	static const floatScalar floatScalarVSMALL = (floatScalar)1.0e-37;
	static const floatScalar floatScalarROOTVSMALL = (floatScalar)1.0e-18;


#define Scalar floatScalar
#define ScalarVGREAT floatScalarVGREAT
#define ScalarVSMALL floatScalarVSMALL
#define readScalar readFloatScalar

	inline Scalar mag(const Scalar s)
	{
		return ::fabsf(s);
	}

#define transFunc(func)            \
inline Scalar func(const Scalar s) \
{                                  \
    return ::func##f(s);           \
}

}

#include <ScalarTemplate.hxx>

namespace tnbLib
{

	inline Scalar hypot(const Scalar x, const Scalar y)
	{
		return ::hypotf(x, y);
	}

	inline Scalar atan2(const Scalar y, const Scalar x)
	{
		return ::atan2f(y, x);
	}

	inline Scalar jn(const int n, const Scalar s)
	{
		return ::jnf(n, s);
	}

	inline Scalar yn(const int n, const Scalar s)
	{
		return ::ynf(n, s);
	}

#undef Scalar
#undef ScalarVGREAT
#undef ScalarVSMALL
#undef readScalar
#undef transFunc
}

#endif // !_floatScalar_Header
