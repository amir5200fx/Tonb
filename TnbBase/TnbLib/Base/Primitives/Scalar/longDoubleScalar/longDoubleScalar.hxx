#pragma once
#ifndef _longDoubleScalar_Header
#define _longDoubleScalar_Header

#include <doubleFloat.hxx>
#include <direction.hxx>
#include <word.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef long double longDoubleScalar;

	// Largest and smallest scalar values allowed in certain parts of the code.
	// (15 is the number of significant figures in an
	//  IEEE double precision number.  See limits.h or float.h)
	static const longDoubleScalar longDoubleScalarGREAT = 1.0e+15;
	static const longDoubleScalar longDoubleScalarVGREAT = 1.0e+300;
	static const longDoubleScalar longDoubleScalarROOTVGREAT = 1.0e+150;
	static const longDoubleScalar longDoubleScalarSMALL = 1.0e-15;
	static const longDoubleScalar longDoubleScalarVSMALL = 1.0e-300;
	static const longDoubleScalar longDoubleScalarROOTVSMALL = 1.0e-150;


#define Scalar longDoubleScalar
#define ScalarVGREAT longDoubleScalarVGREAT
#define ScalarVSMALL longDoubleScalarVSMALL
#define readScalar readLongDoubleScalar

	inline Scalar mag(const Scalar s)
	{
		return ::fabsl(s);
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

#endif // !_longDoubleScalar_Header
