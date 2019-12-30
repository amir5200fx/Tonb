#include <scalarFieldField.hxx>

#define TEMPLATE template<template<class> class Field>
#include <FieldFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class Field>
	void stabilise
	(
		FieldField<Field, scalar>& f,
		const FieldField<Field, scalar>& f1,
		const scalar s
	)
	{
		forAll(f, i)
		{
			stabilise(f[i], f1[i], s);
		}
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar> > stabilise
	(
		const FieldField<Field, scalar>& f1,
		const scalar s
	)
	{
		tmp<FieldField<Field, scalar> > tf
		(
			FieldField<Field, scalar>::NewCalculatedType(f1)
		);
		stabilise(tf(), f1, s);
		return tf;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar> > stabilise
	(
		const tmp<FieldField<Field, scalar> >& tf1,
		const scalar s
	)
	{
		tmp<FieldField<Field, scalar> > tf(tf1.ptr());
		stabilise(tf(), tf(), s);
		return tf;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	TEMPLATE
	void add(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { add(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator +(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator +(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf2);
		return tRes;
	} 
	
	TEMPLATE
	void add(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s)
	{
		forAll(f, i) { add(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator +(const FieldField<Field, scalar>& f1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator +(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf1);
		return tRes;
	}
		
	TEMPLATE
	void subtract(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { subtract(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator -(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator -(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	void subtract(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s)
	{
		forAll(f, i) { subtract(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator -(const FieldField<Field, scalar>& f1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator -(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf1);
		return tRes;
	}

		
	TEMPLATE
	void multiply(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { multiply(f[i], f1[i], f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator *(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		multiply(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator *(const FieldField<Field, scalar>& f1
	                                          , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		multiply(tRes(), f1, tf2());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator *(const tmp<FieldField<Field, scalar>>& tf1
	                                          , const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		multiply(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator *(const tmp<FieldField<Field, scalar>>& tf1
	                                          , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::New(tf1, tf2));
		multiply(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::clear(tf1, tf2);
		return tRes;
	}
		
	TEMPLATE
	void divide(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { divide(f[i], f1[i], f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator /(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator /(const FieldField<Field, scalar>& f1
	                                          , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                          , const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                          , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::clear(tf1, tf2);
		return tRes;
	}

		
	TEMPLATE
	void divide(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { divide(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator /(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> operator /(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf2);
		return tRes;
	}

		
	TEMPLATE
	void pow(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { pow(f[i], f1[i], f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		pow(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow(const FieldField<Field, scalar>& f1, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		pow(tRes(), f1, tf2());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow(const tmp<FieldField<Field, scalar>>& tf1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		pow(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow(const tmp<FieldField<Field, scalar>>& tf1
	                                   , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::New(tf1, tf2));
		pow(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::clear(tf1, tf2);
		return tRes;
	}
		
	TEMPLATE
	void pow(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s)
	{
		forAll(f, i) { pow(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow(const FieldField<Field, scalar>& f1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		pow(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		pow(tRes(), tf1(), s);
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf1);
		return tRes;
	}
	
	TEMPLATE
	void pow(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { pow(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		pow(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		pow(tRes(), s, tf2());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf2);
		return tRes;
	}

		
	TEMPLATE
	void atan2(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { atan2(f[i], f1[i], f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan2(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		atan2(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan2(const FieldField<Field, scalar>& f1, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		atan2(tRes(), f1, tf2());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan2(const tmp<FieldField<Field, scalar>>& tf1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		atan2(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan2(const tmp<FieldField<Field, scalar>>& tf1
	                                     , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::New(tf1, tf2));
		atan2(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::clear(tf1, tf2);
		return tRes;
	}
		
	TEMPLATE
	void atan2(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s)
	{
		forAll(f, i) { atan2(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan2(const FieldField<Field, scalar>& f1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		atan2(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan2(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		atan2(tRes(), tf1(), s);
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf1);
		return tRes;
	} 
	
	TEMPLATE
	void atan2(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { atan2(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan2(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		atan2(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan2(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		atan2(tRes(), s, tf2());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf2);
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		
	TEMPLATE
	void pow3(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pow3(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow3(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pow3(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow3(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		pow3(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void pow4(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pow4(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow4(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pow4(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow4(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		pow4(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void pow5(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pow5(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow5(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pow5(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow5(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		pow5(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void pow6(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pow6(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow6(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pow6(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pow6(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		pow6(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void sqrt(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { sqrt(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> sqrt(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		sqrt(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> sqrt(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		sqrt(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void sign(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { sign(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> sign(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		sign(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> sign(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		sign(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void pos(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pos(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pos(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pos(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> pos(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		pos(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void neg(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { neg(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> neg(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		neg(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> neg(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		neg(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void exp(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { exp(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> exp(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		exp(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> exp(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		exp(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void log(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { log(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> log(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		log(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> log(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		log(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void log10(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { log10(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> log10(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		log10(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> log10(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		log10(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void sin(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { sin(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> sin(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		sin(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> sin(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		sin(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void cos(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { cos(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> cos(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cos(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> cos(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		cos(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void tan(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { tan(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tan(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tan(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tan(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		tan(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void asin(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { asin(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> asin(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		asin(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> asin(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		asin(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void acos(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { acos(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> acos(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		acos(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> acos(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		acos(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void atan(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { atan(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		atan(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atan(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		atan(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void sinh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { sinh(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> sinh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		sinh(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> sinh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		sinh(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void cosh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { cosh(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> cosh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cosh(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> cosh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		cosh(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void tanh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { tanh(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tanh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tanh(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tanh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		tanh(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void asinh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { asinh(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> asinh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		asinh(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> asinh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		asinh(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void acosh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { acosh(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> acosh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		acosh(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> acosh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		acosh(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void atanh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { atanh(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atanh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		atanh(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> atanh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		atanh(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void erf(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { erf(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> erf(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		erf(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> erf(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		erf(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void erfc(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { erfc(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> erfc(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		erfc(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> erfc(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		erfc(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void lgamma(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { lgamma(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> lgamma(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		lgamma(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> lgamma(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		lgamma(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void j0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { j0(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> j0(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		j0(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> j0(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		j0(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void j1(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { j1(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> j1(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		j1(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> j1(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		j1(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void y0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { y0(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> y0(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		y0(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> y0(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		y0(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void y1(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { y1(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> y1(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		y1(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> y1(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf));
		y1(tRes(), tf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tf);
		return tRes;
	}


#define BesselFunc(func)                                                      \
                                                                              \
template<template<class> class Field>                                         \
void func                                                                     \
(                                                                             \
    FieldField<Field, scalar>& res,                                           \
    const int n,                                                              \
    const FieldField<Field, scalar>& sf                                       \
)                                                                             \
{                                                                             \
    forAll(res, i)                                                            \
    {                                                                         \
        func(res[i], n, sf[i]);                                               \
    }                                                                         \
}                                                                             \
                                                                              \
template<template<class> class Field>                                         \
tmp<FieldField<Field, scalar> > func                                          \
(                                                                             \
    const int n,                                                              \
    const FieldField<Field, scalar>& sf                                       \
)                                                                             \
{                                                                             \
    tmp<FieldField<Field, scalar> > tRes                                      \
    (                                                                         \
        FieldField<Field, scalar>::NewCalculatedType(sf)                      \
    );                                                                        \
    func(tRes(), n, sf);                                                      \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<template<class> class Field>                                         \
tmp<FieldField<Field, scalar> > func                                          \
(                                                                             \
    const int n,                                                              \
    const tmp<FieldField<Field, scalar> >& tsf                                \
)                                                                             \
{                                                                             \
    tmp<FieldField<Field, scalar> > tRes                                      \
    (                                                                         \
        reuseTmpFieldField<Field, scalar, scalar>::New(tsf)                   \
    );                                                                        \
    func(tRes(), n, tsf());                                                   \
    reuseTmpFieldField<Field, scalar, scalar>::clear(tsf);                    \
    return tRes;                                                              \
}

		
	template <template<class> class Field>
	void jn(FieldField<Field, scalar>& res, const int n, const FieldField<Field, scalar>& sf)
	{
		forAll(res, i) { jn(res[i], n, sf[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> jn(const int n, const FieldField<Field, scalar>& sf)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(sf));
		jn(tRes(), n, sf);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> jn(const int n, const tmp<FieldField<Field, scalar>>& tsf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tsf));
		jn(tRes(), n, tsf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tsf);
		return tRes;
	}
		
	template <template<class> class Field>
	void yn(FieldField<Field, scalar>& res, const int n, const FieldField<Field, scalar>& sf)
	{
		forAll(res, i) { yn(res[i], n, sf[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> yn(const int n, const FieldField<Field, scalar>& sf)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(sf));
		yn(tRes(), n, sf);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> yn(const int n, const tmp<FieldField<Field, scalar>>& tsf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tsf));
		yn(tRes(), n, tsf());
		reuseTmpFieldField<Field, scalar, scalar>::clear(tsf);
		return tRes;
	}

#undef BesselFunc


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>