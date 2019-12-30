#include <VectorNFieldFields.hxx>

#define TEMPLATE template<template<class> class Field>
#include <FieldFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define VectorN_FieldFunctions(tensorType, diagTensorType, sphericalTensorType,         \
    vectorType, CmptType, args)                                                      \
                                                                                        \
UNARY_FUNCTION(CmptType, vectorType, cmptSum)                                           \
                                                                                        \
BINARY_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)                       \
BINARY_TYPE_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)                  \
                                                                                        \
BINARY_OPERATOR(vectorType, vectorType, CmptType, /,divide)                             \
BINARY_TYPE_OPERATOR(vectorType, vectorType, CmptType, /,divide)                        \
                                                                                        \
BINARY_OPERATOR(vectorType, vectorType, vectorType, +, add)                             \
BINARY_OPERATOR(vectorType, vectorType, vectorType, -, subtract)                        \
                                                                                        \
BINARY_TYPE_OPERATOR(vectorType, vectorType, vectorType, +, add)                        \
BINARY_TYPE_OPERATOR(vectorType, vectorType, vectorType, -, subtract)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	
	template <template<class> class Field>
	void cmptSum(FieldField<Field, scalar>& res, const FieldField<Field, vector2>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { cmptSum(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const FieldField<Field, vector2>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cmptSum(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const tmp<FieldField<Field, vector2>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf));
		cmptSum(tRes(), tf());
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1
	                  , const FieldField<Field, vector2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> cmptMultiply(const FieldField<Field, vector2>& f1
	                                             , const FieldField<Field, vector2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> cmptMultiply(const FieldField<Field, vector2>& f1
	                                             , const tmp<FieldField<Field, vector2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf2));
		cmptMultiply(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> cmptMultiply(const tmp<FieldField<Field, vector2>>& tf1
	                                             , const FieldField<Field, vector2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> cmptMultiply(const tmp<FieldField<Field, vector2>>& tf1
	                                             , const tmp<FieldField<Field, vector2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpTmpFieldField<Field, vector2, vector2, vector2, vector2>::New(tf1, tf2));
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector2, vector2, vector2, vector2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1, const vector2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> cmptMultiply(const FieldField<Field, vector2>& f1, const vector2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> cmptMultiply(const tmp<FieldField<Field, vector2>>& tf1, const vector2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		cmptMultiply(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector2>& f, const vector2& s, const FieldField<Field, vector2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> cmptMultiply(const vector2& s, const FieldField<Field, vector2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f2));
		cmptMultiply(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> cmptMultiply(const vector2& s, const tmp<FieldField<Field, vector2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf2));
		cmptMultiply(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const FieldField<Field, vector2>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const FieldField<Field, vector2>& f1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, scalar>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector2, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpTmpFieldField<Field, vector2, vector2, vector2, scalar>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector2, vector2, vector2, scalar>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector2>& f, const vector2& s, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const vector2& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const vector2& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, scalar>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector2, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1, const scalar& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const FieldField<Field, vector2>& f1, const scalar& s)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const tmp<FieldField<Field, vector2>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1, const FieldField<Field, vector2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator +(const FieldField<Field, vector2>& f1, const FieldField<Field, vector2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator +(const FieldField<Field, vector2>& f1
	                                           , const tmp<FieldField<Field, vector2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator +(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const FieldField<Field, vector2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator +(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const tmp<FieldField<Field, vector2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpTmpFieldField<Field, vector2, vector2, vector2, vector2>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector2, vector2, vector2, vector2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1
	              , const FieldField<Field, vector2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator -(const FieldField<Field, vector2>& f1, const FieldField<Field, vector2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator -(const FieldField<Field, vector2>& f1
	                                           , const tmp<FieldField<Field, vector2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator -(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const FieldField<Field, vector2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator -(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const tmp<FieldField<Field, vector2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpTmpFieldField<Field, vector2, vector2, vector2, vector2>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector2, vector2, vector2, vector2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector2>& f, const vector2& s, const FieldField<Field, vector2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator +(const vector2& s, const FieldField<Field, vector2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator +(const vector2& s, const tmp<FieldField<Field, vector2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1, const vector2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator +(const FieldField<Field, vector2>& f1, const vector2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator +(const tmp<FieldField<Field, vector2>>& tf1, const vector2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector2>& f, const vector2& s, const FieldField<Field, vector2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator -(const vector2& s, const FieldField<Field, vector2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator -(const vector2& s, const tmp<FieldField<Field, vector2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1, const vector2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator -(const FieldField<Field, vector2>& f1, const vector2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator -(const tmp<FieldField<Field, vector2>>& tf1, const vector2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void cmptSum(FieldField<Field, scalar>& res, const FieldField<Field, vector3>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { cmptSum(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const FieldField<Field, vector3>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cmptSum(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const tmp<FieldField<Field, vector3>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf));
		cmptSum(tRes(), tf());
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1
	                  , const FieldField<Field, vector3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> cmptMultiply(const FieldField<Field, vector3>& f1
	                                             , const FieldField<Field, vector3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> cmptMultiply(const FieldField<Field, vector3>& f1
	                                             , const tmp<FieldField<Field, vector3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf2));
		cmptMultiply(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> cmptMultiply(const tmp<FieldField<Field, vector3>>& tf1
	                                             , const FieldField<Field, vector3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> cmptMultiply(const tmp<FieldField<Field, vector3>>& tf1
	                                             , const tmp<FieldField<Field, vector3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpTmpFieldField<Field, vector3, vector3, vector3, vector3>::New(tf1, tf2));
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector3, vector3, vector3, vector3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1, const vector3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> cmptMultiply(const FieldField<Field, vector3>& f1, const vector3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> cmptMultiply(const tmp<FieldField<Field, vector3>>& tf1, const vector3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		cmptMultiply(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector3>& f, const vector3& s, const FieldField<Field, vector3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> cmptMultiply(const vector3& s, const FieldField<Field, vector3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f2));
		cmptMultiply(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> cmptMultiply(const vector3& s, const tmp<FieldField<Field, vector3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf2));
		cmptMultiply(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const FieldField<Field, vector3>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const FieldField<Field, vector3>& f1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, scalar>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector3, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpTmpFieldField<Field, vector3, vector3, vector3, scalar>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector3, vector3, vector3, scalar>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector3>& f, const vector3& s, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const vector3& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const vector3& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, scalar>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector3, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1, const scalar& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const FieldField<Field, vector3>& f1, const scalar& s)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const tmp<FieldField<Field, vector3>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1, const FieldField<Field, vector3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator +(const FieldField<Field, vector3>& f1, const FieldField<Field, vector3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator +(const FieldField<Field, vector3>& f1
	                                           , const tmp<FieldField<Field, vector3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator +(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const FieldField<Field, vector3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator +(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const tmp<FieldField<Field, vector3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpTmpFieldField<Field, vector3, vector3, vector3, vector3>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector3, vector3, vector3, vector3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1
	              , const FieldField<Field, vector3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator -(const FieldField<Field, vector3>& f1, const FieldField<Field, vector3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator -(const FieldField<Field, vector3>& f1
	                                           , const tmp<FieldField<Field, vector3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator -(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const FieldField<Field, vector3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator -(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const tmp<FieldField<Field, vector3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpTmpFieldField<Field, vector3, vector3, vector3, vector3>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector3, vector3, vector3, vector3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector3>& f, const vector3& s, const FieldField<Field, vector3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator +(const vector3& s, const FieldField<Field, vector3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator +(const vector3& s, const tmp<FieldField<Field, vector3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1, const vector3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator +(const FieldField<Field, vector3>& f1, const vector3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator +(const tmp<FieldField<Field, vector3>>& tf1, const vector3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector3>& f, const vector3& s, const FieldField<Field, vector3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator -(const vector3& s, const FieldField<Field, vector3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator -(const vector3& s, const tmp<FieldField<Field, vector3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1, const vector3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator -(const FieldField<Field, vector3>& f1, const vector3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator -(const tmp<FieldField<Field, vector3>>& tf1, const vector3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void cmptSum(FieldField<Field, scalar>& res, const FieldField<Field, vector4>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { cmptSum(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const FieldField<Field, vector4>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cmptSum(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const tmp<FieldField<Field, vector4>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf));
		cmptSum(tRes(), tf());
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1
	                  , const FieldField<Field, vector4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> cmptMultiply(const FieldField<Field, vector4>& f1
	                                             , const FieldField<Field, vector4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> cmptMultiply(const FieldField<Field, vector4>& f1
	                                             , const tmp<FieldField<Field, vector4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf2));
		cmptMultiply(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> cmptMultiply(const tmp<FieldField<Field, vector4>>& tf1
	                                             , const FieldField<Field, vector4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> cmptMultiply(const tmp<FieldField<Field, vector4>>& tf1
	                                             , const tmp<FieldField<Field, vector4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpTmpFieldField<Field, vector4, vector4, vector4, vector4>::New(tf1, tf2));
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector4, vector4, vector4, vector4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1, const vector4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> cmptMultiply(const FieldField<Field, vector4>& f1, const vector4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> cmptMultiply(const tmp<FieldField<Field, vector4>>& tf1, const vector4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		cmptMultiply(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector4>& f, const vector4& s, const FieldField<Field, vector4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> cmptMultiply(const vector4& s, const FieldField<Field, vector4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f2));
		cmptMultiply(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> cmptMultiply(const vector4& s, const tmp<FieldField<Field, vector4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf2));
		cmptMultiply(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const FieldField<Field, vector4>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const FieldField<Field, vector4>& f1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, scalar>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector4, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpTmpFieldField<Field, vector4, vector4, vector4, scalar>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector4, vector4, vector4, scalar>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector4>& f, const vector4& s, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const vector4& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const vector4& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, scalar>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector4, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1, const scalar& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const FieldField<Field, vector4>& f1, const scalar& s)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const tmp<FieldField<Field, vector4>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1, const FieldField<Field, vector4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator +(const FieldField<Field, vector4>& f1, const FieldField<Field, vector4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator +(const FieldField<Field, vector4>& f1
	                                           , const tmp<FieldField<Field, vector4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator +(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const FieldField<Field, vector4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator +(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const tmp<FieldField<Field, vector4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpTmpFieldField<Field, vector4, vector4, vector4, vector4>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector4, vector4, vector4, vector4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1
	              , const FieldField<Field, vector4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator -(const FieldField<Field, vector4>& f1, const FieldField<Field, vector4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator -(const FieldField<Field, vector4>& f1
	                                           , const tmp<FieldField<Field, vector4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator -(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const FieldField<Field, vector4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator -(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const tmp<FieldField<Field, vector4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpTmpFieldField<Field, vector4, vector4, vector4, vector4>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector4, vector4, vector4, vector4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector4>& f, const vector4& s, const FieldField<Field, vector4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator +(const vector4& s, const FieldField<Field, vector4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator +(const vector4& s, const tmp<FieldField<Field, vector4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1, const vector4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator +(const FieldField<Field, vector4>& f1, const vector4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator +(const tmp<FieldField<Field, vector4>>& tf1, const vector4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector4>& f, const vector4& s, const FieldField<Field, vector4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator -(const vector4& s, const FieldField<Field, vector4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator -(const vector4& s, const tmp<FieldField<Field, vector4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1, const vector4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator -(const FieldField<Field, vector4>& f1, const vector4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator -(const tmp<FieldField<Field, vector4>>& tf1, const vector4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void cmptSum(FieldField<Field, scalar>& res, const FieldField<Field, vector6>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { cmptSum(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const FieldField<Field, vector6>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cmptSum(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const tmp<FieldField<Field, vector6>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf));
		cmptSum(tRes(), tf());
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1
	                  , const FieldField<Field, vector6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> cmptMultiply(const FieldField<Field, vector6>& f1
	                                             , const FieldField<Field, vector6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> cmptMultiply(const FieldField<Field, vector6>& f1
	                                             , const tmp<FieldField<Field, vector6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf2));
		cmptMultiply(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> cmptMultiply(const tmp<FieldField<Field, vector6>>& tf1
	                                             , const FieldField<Field, vector6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> cmptMultiply(const tmp<FieldField<Field, vector6>>& tf1
	                                             , const tmp<FieldField<Field, vector6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpTmpFieldField<Field, vector6, vector6, vector6, vector6>::New(tf1, tf2));
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector6, vector6, vector6, vector6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1, const vector6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> cmptMultiply(const FieldField<Field, vector6>& f1, const vector6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> cmptMultiply(const tmp<FieldField<Field, vector6>>& tf1, const vector6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		cmptMultiply(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector6>& f, const vector6& s, const FieldField<Field, vector6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> cmptMultiply(const vector6& s, const FieldField<Field, vector6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f2));
		cmptMultiply(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> cmptMultiply(const vector6& s, const tmp<FieldField<Field, vector6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf2));
		cmptMultiply(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const FieldField<Field, vector6>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const FieldField<Field, vector6>& f1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, scalar>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector6, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpTmpFieldField<Field, vector6, vector6, vector6, scalar>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector6, vector6, vector6, scalar>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector6>& f, const vector6& s, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const vector6& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const vector6& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, scalar>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector6, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1, const scalar& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const FieldField<Field, vector6>& f1, const scalar& s)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const tmp<FieldField<Field, vector6>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1, const FieldField<Field, vector6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator +(const FieldField<Field, vector6>& f1, const FieldField<Field, vector6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator +(const FieldField<Field, vector6>& f1
	                                           , const tmp<FieldField<Field, vector6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator +(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const FieldField<Field, vector6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator +(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const tmp<FieldField<Field, vector6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpTmpFieldField<Field, vector6, vector6, vector6, vector6>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector6, vector6, vector6, vector6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1
	              , const FieldField<Field, vector6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator -(const FieldField<Field, vector6>& f1, const FieldField<Field, vector6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator -(const FieldField<Field, vector6>& f1
	                                           , const tmp<FieldField<Field, vector6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator -(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const FieldField<Field, vector6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator -(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const tmp<FieldField<Field, vector6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpTmpFieldField<Field, vector6, vector6, vector6, vector6>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector6, vector6, vector6, vector6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector6>& f, const vector6& s, const FieldField<Field, vector6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator +(const vector6& s, const FieldField<Field, vector6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator +(const vector6& s, const tmp<FieldField<Field, vector6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1, const vector6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator +(const FieldField<Field, vector6>& f1, const vector6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator +(const tmp<FieldField<Field, vector6>>& tf1, const vector6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector6>& f, const vector6& s, const FieldField<Field, vector6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator -(const vector6& s, const FieldField<Field, vector6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator -(const vector6& s, const tmp<FieldField<Field, vector6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1, const vector6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator -(const FieldField<Field, vector6>& f1, const vector6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator -(const tmp<FieldField<Field, vector6>>& tf1, const vector6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void cmptSum(FieldField<Field, scalar>& res, const FieldField<Field, vector8>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { cmptSum(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const FieldField<Field, vector8>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cmptSum(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cmptSum(const tmp<FieldField<Field, vector8>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf));
		cmptSum(tRes(), tf());
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1
	                  , const FieldField<Field, vector8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> cmptMultiply(const FieldField<Field, vector8>& f1
	                                             , const FieldField<Field, vector8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> cmptMultiply(const FieldField<Field, vector8>& f1
	                                             , const tmp<FieldField<Field, vector8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf2));
		cmptMultiply(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> cmptMultiply(const tmp<FieldField<Field, vector8>>& tf1
	                                             , const FieldField<Field, vector8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> cmptMultiply(const tmp<FieldField<Field, vector8>>& tf1
	                                             , const tmp<FieldField<Field, vector8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpTmpFieldField<Field, vector8, vector8, vector8, vector8>::New(tf1, tf2));
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector8, vector8, vector8, vector8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1, const vector8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> cmptMultiply(const FieldField<Field, vector8>& f1, const vector8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> cmptMultiply(const tmp<FieldField<Field, vector8>>& tf1, const vector8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		cmptMultiply(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void cmptMultiply(FieldField<Field, vector8>& f, const vector8& s, const FieldField<Field, vector8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { cmptMultiply(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> cmptMultiply(const vector8& s, const FieldField<Field, vector8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f2));
		cmptMultiply(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> cmptMultiply(const vector8& s, const tmp<FieldField<Field, vector8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf2));
		cmptMultiply(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const FieldField<Field, vector8>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const FieldField<Field, vector8>& f1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, scalar>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector8, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpTmpFieldField<Field, vector8, vector8, vector8, scalar>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector8, vector8, vector8, scalar>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector8>& f, const vector8& s, const FieldField<Field, scalar>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const vector8& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const vector8& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, scalar>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector8, scalar>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1, const scalar& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const FieldField<Field, vector8>& f1, const scalar& s)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const tmp<FieldField<Field, vector8>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1, const FieldField<Field, vector8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator +(const FieldField<Field, vector8>& f1, const FieldField<Field, vector8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator +(const FieldField<Field, vector8>& f1
	                                           , const tmp<FieldField<Field, vector8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator +(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const FieldField<Field, vector8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator +(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const tmp<FieldField<Field, vector8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpTmpFieldField<Field, vector8, vector8, vector8, vector8>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector8, vector8, vector8, vector8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1
	              , const FieldField<Field, vector8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator -(const FieldField<Field, vector8>& f1, const FieldField<Field, vector8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator -(const FieldField<Field, vector8>& f1
	                                           , const tmp<FieldField<Field, vector8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator -(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const FieldField<Field, vector8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator -(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const tmp<FieldField<Field, vector8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpTmpFieldField<Field, vector8, vector8, vector8, vector8>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector8, vector8, vector8, vector8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector8>& f, const vector8& s, const FieldField<Field, vector8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator +(const vector8& s, const FieldField<Field, vector8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator +(const vector8& s, const tmp<FieldField<Field, vector8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1, const vector8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator +(const FieldField<Field, vector8>& f1, const vector8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator +(const tmp<FieldField<Field, vector8>>& tf1, const vector8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector8>& f, const vector8& s, const FieldField<Field, vector8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator -(const vector8& s, const FieldField<Field, vector8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator -(const vector8& s, const tmp<FieldField<Field, vector8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1, const vector8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator -(const FieldField<Field, vector8>& f1, const vector8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator -(const tmp<FieldField<Field, vector8>>& tf1, const vector8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

}

#undef VectorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>