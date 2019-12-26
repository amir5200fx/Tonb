#pragma once
#ifndef _doubleScalar_Header
#define _doubleScalar_Header

#include <doubleFloat.hxx>
#include <direction.hxx>
#include <word.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef double doubleScalar;

	// Largest and smallest scalar values allowed in certain parts of the code.
	// (15 is the number of significant figures in an
	//  IEEE double precision number.  See limits.h or float.h)
	static const doubleScalar doubleScalarGREAT = 1.0e+15;
	static const doubleScalar doubleScalarVGREAT = 1.0e+300;
	static const doubleScalar doubleScalarROOTVGREAT = 1.0e+150;
	static const doubleScalar doubleScalarSMALL = 1.0e-15;
	static const doubleScalar doubleScalarVSMALL = 1.0e-300;
	static const doubleScalar doubleScalarROOTVSMALL = 1.0e-150;


#define Scalar doubleScalar
#define ScalarVGREAT doubleScalarVGREAT
#define ScalarVSMALL doubleScalarVSMALL
#define readScalar readDoubleScalar

	inline Scalar mag(const Scalar s)
	{
		return ::fabs(s);
	}

#define transFunc(func)            \
inline Scalar func(const Scalar s) \
{                                  \
    return ::func(s);              \
}
}

#include <ScalarTemplate.hxx>

namespace tnbLib
{

	inline Scalar hypot(const Scalar x, const Scalar y)
	{
		return ::hypot(x, y);
	}

	inline Scalar atan2(const Scalar y, const Scalar x)
	{
		return ::atan2(y, x);
	}

	inline Scalar jn(const int n, const Scalar s)
	{
		return ::_jn(n, s);
	}

	inline Scalar yn(const int n, const Scalar s)
	{
		return ::_yn(n, s);
	}

#undef Scalar
#undef ScalarVGREAT
#undef ScalarVSMALL
#undef readScalar
#undef transFunc


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}

#endif // !_doubleScalar_Header
