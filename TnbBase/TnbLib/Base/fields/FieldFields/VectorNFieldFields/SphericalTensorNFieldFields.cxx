#include <SphericalTensorNFieldFields.hxx>

#define TEMPLATE template<template<class> class Field>
#include <FieldFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define SphericalTensorN_FieldFunctions(tensorType, diagTensorType,                 \
    sphericalTensorType, vectorType, CmptType, args)								\
                                                                                    \
UNARY_FUNCTION(sphericalTensorType, sphericalTensorType, inv)                       \
UNARY_FUNCTION(sphericalTensorType, sphericalTensorType, diag)                      \
UNARY_FUNCTION(CmptType, sphericalTensorType, contractLinear)                       \
UNARY_FUNCTION(CmptType, sphericalTensorType, contractScalar)                       \
                                                                                    \
BINARY_OPERATOR(sphericalTensorType, CmptType, sphericalTensorType, /, divide)      \
BINARY_TYPE_OPERATOR(sphericalTensorType, CmptType, sphericalTensorType, /, divide) \
                                                                                    \
BINARY_OPERATOR(vectorType, vectorType, sphericalTensorType, /, divide)             \
BINARY_TYPE_OPERATOR(vectorType, vectorType, sphericalTensorType, /, divide)        \
                                                                                    \
BINARY_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, /, divide)           \
BINARY_TYPE_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, /, divide)      \
                                                                                    \
BINARY_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, +, add)             \
BINARY_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, -, subtract)        \
                                                                                    \
BINARY_TYPE_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, +, add)        \
BINARY_TYPE_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, -, subtract)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	template <template<class> class Field>
	void inv(FieldField<Field, sphericalTensor2>& res, const FieldField<Field, sphericalTensor2>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> inv(const FieldField<Field, sphericalTensor2>& f)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> inv(const tmp<FieldField<Field, sphericalTensor2>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, sphericalTensor2>& res, const FieldField<Field, sphericalTensor2>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> diag(const FieldField<Field, sphericalTensor2>& f)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> diag(const tmp<FieldField<Field, sphericalTensor2>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor2>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const FieldField<Field, sphericalTensor2>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const tmp<FieldField<Field, sphericalTensor2>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor2>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, sphericalTensor2>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, sphericalTensor2>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor2>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(reuseTmpFieldField<Field, sphericalTensor2, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor2, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor2, scalar, scalar, sphericalTensor2>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor2, scalar, scalar, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor2>& f, const scalar& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const scalar& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const scalar& s
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor2>& f, const FieldField<Field, scalar>& f1, const sphericalTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const FieldField<Field, scalar>& f1, const sphericalTensor2& s)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(reuseTmpFieldField<Field, sphericalTensor2, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor2, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1
	            , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const FieldField<Field, vector2>& f1
	                                           , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const FieldField<Field, vector2>& f1
	                                           , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, sphericalTensor2>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(
			reuseTmpTmpFieldField<Field, vector2, vector2, vector2, sphericalTensor2>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector2, vector2, vector2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector2>& f, const vector2& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const vector2& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const vector2& s, const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, sphericalTensor2>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1, const sphericalTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const FieldField<Field, vector2>& f1, const sphericalTensor2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const tmp<FieldField<Field, vector2>>& tf1, const sphericalTensor2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor2>& f, const FieldField<Field, sphericalTensor2>& f1
	            , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const FieldField<Field, sphericalTensor2>& f1
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const FieldField<Field, sphericalTensor2>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor2>& f, const sphericalTensor2& s
	            , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const sphericalTensor2& s
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const sphericalTensor2& s
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor2>& f, const FieldField<Field, sphericalTensor2>& f1
	            , const sphericalTensor2& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const FieldField<Field, sphericalTensor2>& f1
	                                                    , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator /(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                                    , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor2>& f, const FieldField<Field, sphericalTensor2>& f1
	         , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator +(const FieldField<Field, sphericalTensor2>& f1
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator +(const FieldField<Field, sphericalTensor2>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator +(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator +(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor2>& f, const FieldField<Field, sphericalTensor2>& f1
	              , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator -(const FieldField<Field, sphericalTensor2>& f1
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator -(const FieldField<Field, sphericalTensor2>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator -(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator -(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor2>& f, const sphericalTensor2& s
	         , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator +(const sphericalTensor2& s
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator +(const sphericalTensor2& s
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor2>& f, const FieldField<Field, sphericalTensor2>& f1
	         , const sphericalTensor2& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator +(const FieldField<Field, sphericalTensor2>& f1
	                                                    , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator +(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                                    , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor2>& f, const sphericalTensor2& s
	              , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator -(const sphericalTensor2& s
	                                                    , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator -(const sphericalTensor2& s
	                                                    , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor2>& f, const FieldField<Field, sphericalTensor2>& f1
	              , const sphericalTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator -(const FieldField<Field, sphericalTensor2>& f1
	                                                    , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, sphericalTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor2>> operator -(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                                    , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, sphericalTensor2>>
			tRes(reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void inv(FieldField<Field, sphericalTensor3>& res, const FieldField<Field, sphericalTensor3>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> inv(const FieldField<Field, sphericalTensor3>& f)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> inv(const tmp<FieldField<Field, sphericalTensor3>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, sphericalTensor3>& res, const FieldField<Field, sphericalTensor3>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> diag(const FieldField<Field, sphericalTensor3>& f)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> diag(const tmp<FieldField<Field, sphericalTensor3>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor3>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const FieldField<Field, sphericalTensor3>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const tmp<FieldField<Field, sphericalTensor3>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor3>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, sphericalTensor3>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, sphericalTensor3>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor3>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(reuseTmpFieldField<Field, sphericalTensor3, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor3, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor3, scalar, scalar, sphericalTensor3>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor3, scalar, scalar, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor3>& f, const scalar& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const scalar& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const scalar& s
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor3>& f, const FieldField<Field, scalar>& f1, const sphericalTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const FieldField<Field, scalar>& f1, const sphericalTensor3& s)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(reuseTmpFieldField<Field, sphericalTensor3, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor3, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1
	            , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const FieldField<Field, vector3>& f1
	                                           , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const FieldField<Field, vector3>& f1
	                                           , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, sphericalTensor3>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(
			reuseTmpTmpFieldField<Field, vector3, vector3, vector3, sphericalTensor3>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector3, vector3, vector3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector3>& f, const vector3& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const vector3& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const vector3& s, const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, sphericalTensor3>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1, const sphericalTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const FieldField<Field, vector3>& f1, const sphericalTensor3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const tmp<FieldField<Field, vector3>>& tf1, const sphericalTensor3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor3>& f, const FieldField<Field, sphericalTensor3>& f1
	            , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const FieldField<Field, sphericalTensor3>& f1
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const FieldField<Field, sphericalTensor3>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor3>& f, const sphericalTensor3& s
	            , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const sphericalTensor3& s
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const sphericalTensor3& s
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor3>& f, const FieldField<Field, sphericalTensor3>& f1
	            , const sphericalTensor3& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const FieldField<Field, sphericalTensor3>& f1
	                                                    , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator /(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                                    , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor3>& f, const FieldField<Field, sphericalTensor3>& f1
	         , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator +(const FieldField<Field, sphericalTensor3>& f1
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator +(const FieldField<Field, sphericalTensor3>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator +(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator +(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor3>& f, const FieldField<Field, sphericalTensor3>& f1
	              , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator -(const FieldField<Field, sphericalTensor3>& f1
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator -(const FieldField<Field, sphericalTensor3>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator -(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator -(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor3>& f, const sphericalTensor3& s
	         , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator +(const sphericalTensor3& s
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator +(const sphericalTensor3& s
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor3>& f, const FieldField<Field, sphericalTensor3>& f1
	         , const sphericalTensor3& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator +(const FieldField<Field, sphericalTensor3>& f1
	                                                    , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator +(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                                    , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor3>& f, const sphericalTensor3& s
	              , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator -(const sphericalTensor3& s
	                                                    , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator -(const sphericalTensor3& s
	                                                    , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor3>& f, const FieldField<Field, sphericalTensor3>& f1
	              , const sphericalTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator -(const FieldField<Field, sphericalTensor3>& f1
	                                                    , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, sphericalTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor3>> operator -(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                                    , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, sphericalTensor3>>
			tRes(reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void inv(FieldField<Field, sphericalTensor4>& res, const FieldField<Field, sphericalTensor4>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> inv(const FieldField<Field, sphericalTensor4>& f)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> inv(const tmp<FieldField<Field, sphericalTensor4>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, sphericalTensor4>& res, const FieldField<Field, sphericalTensor4>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> diag(const FieldField<Field, sphericalTensor4>& f)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> diag(const tmp<FieldField<Field, sphericalTensor4>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor4>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const FieldField<Field, sphericalTensor4>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const tmp<FieldField<Field, sphericalTensor4>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor4>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, sphericalTensor4>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, sphericalTensor4>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor4>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(reuseTmpFieldField<Field, sphericalTensor4, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor4, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor4, scalar, scalar, sphericalTensor4>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor4, scalar, scalar, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor4>& f, const scalar& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const scalar& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const scalar& s
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor4>& f, const FieldField<Field, scalar>& f1, const sphericalTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const FieldField<Field, scalar>& f1, const sphericalTensor4& s)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(reuseTmpFieldField<Field, sphericalTensor4, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor4, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1
	            , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const FieldField<Field, vector4>& f1
	                                           , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const FieldField<Field, vector4>& f1
	                                           , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, sphericalTensor4>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(
			reuseTmpTmpFieldField<Field, vector4, vector4, vector4, sphericalTensor4>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector4, vector4, vector4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector4>& f, const vector4& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const vector4& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const vector4& s, const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, sphericalTensor4>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1, const sphericalTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const FieldField<Field, vector4>& f1, const sphericalTensor4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const tmp<FieldField<Field, vector4>>& tf1, const sphericalTensor4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor4>& f, const FieldField<Field, sphericalTensor4>& f1
	            , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const FieldField<Field, sphericalTensor4>& f1
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const FieldField<Field, sphericalTensor4>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor4>& f, const sphericalTensor4& s
	            , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const sphericalTensor4& s
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const sphericalTensor4& s
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor4>& f, const FieldField<Field, sphericalTensor4>& f1
	            , const sphericalTensor4& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const FieldField<Field, sphericalTensor4>& f1
	                                                    , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator /(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                                    , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor4>& f, const FieldField<Field, sphericalTensor4>& f1
	         , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator +(const FieldField<Field, sphericalTensor4>& f1
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator +(const FieldField<Field, sphericalTensor4>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator +(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator +(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor4>& f, const FieldField<Field, sphericalTensor4>& f1
	              , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator -(const FieldField<Field, sphericalTensor4>& f1
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator -(const FieldField<Field, sphericalTensor4>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator -(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator -(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor4>& f, const sphericalTensor4& s
	         , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator +(const sphericalTensor4& s
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator +(const sphericalTensor4& s
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor4>& f, const FieldField<Field, sphericalTensor4>& f1
	         , const sphericalTensor4& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator +(const FieldField<Field, sphericalTensor4>& f1
	                                                    , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator +(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                                    , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor4>& f, const sphericalTensor4& s
	              , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator -(const sphericalTensor4& s
	                                                    , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator -(const sphericalTensor4& s
	                                                    , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor4>& f, const FieldField<Field, sphericalTensor4>& f1
	              , const sphericalTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator -(const FieldField<Field, sphericalTensor4>& f1
	                                                    , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, sphericalTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor4>> operator -(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                                    , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, sphericalTensor4>>
			tRes(reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void inv(FieldField<Field, sphericalTensor6>& res, const FieldField<Field, sphericalTensor6>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> inv(const FieldField<Field, sphericalTensor6>& f)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> inv(const tmp<FieldField<Field, sphericalTensor6>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, sphericalTensor6>& res, const FieldField<Field, sphericalTensor6>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> diag(const FieldField<Field, sphericalTensor6>& f)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> diag(const tmp<FieldField<Field, sphericalTensor6>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor6>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const FieldField<Field, sphericalTensor6>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const tmp<FieldField<Field, sphericalTensor6>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor6>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, sphericalTensor6>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, sphericalTensor6>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor6>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(reuseTmpFieldField<Field, sphericalTensor6, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor6, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor6, scalar, scalar, sphericalTensor6>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor6, scalar, scalar, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor6>& f, const scalar& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const scalar& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const scalar& s
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor6>& f, const FieldField<Field, scalar>& f1, const sphericalTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const FieldField<Field, scalar>& f1, const sphericalTensor6& s)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(reuseTmpFieldField<Field, sphericalTensor6, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor6, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1
	            , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const FieldField<Field, vector6>& f1
	                                           , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const FieldField<Field, vector6>& f1
	                                           , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, sphericalTensor6>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(
			reuseTmpTmpFieldField<Field, vector6, vector6, vector6, sphericalTensor6>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector6, vector6, vector6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector6>& f, const vector6& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const vector6& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const vector6& s, const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, sphericalTensor6>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1, const sphericalTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const FieldField<Field, vector6>& f1, const sphericalTensor6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const tmp<FieldField<Field, vector6>>& tf1, const sphericalTensor6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor6>& f, const FieldField<Field, sphericalTensor6>& f1
	            , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const FieldField<Field, sphericalTensor6>& f1
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const FieldField<Field, sphericalTensor6>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor6>& f, const sphericalTensor6& s
	            , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const sphericalTensor6& s
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const sphericalTensor6& s
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor6>& f, const FieldField<Field, sphericalTensor6>& f1
	            , const sphericalTensor6& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const FieldField<Field, sphericalTensor6>& f1
	                                                    , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator /(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                                    , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor6>& f, const FieldField<Field, sphericalTensor6>& f1
	         , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator +(const FieldField<Field, sphericalTensor6>& f1
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator +(const FieldField<Field, sphericalTensor6>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator +(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator +(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor6>& f, const FieldField<Field, sphericalTensor6>& f1
	              , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator -(const FieldField<Field, sphericalTensor6>& f1
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator -(const FieldField<Field, sphericalTensor6>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator -(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator -(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor6>& f, const sphericalTensor6& s
	         , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator +(const sphericalTensor6& s
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator +(const sphericalTensor6& s
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor6>& f, const FieldField<Field, sphericalTensor6>& f1
	         , const sphericalTensor6& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator +(const FieldField<Field, sphericalTensor6>& f1
	                                                    , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator +(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                                    , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor6>& f, const sphericalTensor6& s
	              , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator -(const sphericalTensor6& s
	                                                    , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator -(const sphericalTensor6& s
	                                                    , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor6>& f, const FieldField<Field, sphericalTensor6>& f1
	              , const sphericalTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator -(const FieldField<Field, sphericalTensor6>& f1
	                                                    , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, sphericalTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor6>> operator -(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                                    , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, sphericalTensor6>>
			tRes(reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void inv(FieldField<Field, sphericalTensor8>& res, const FieldField<Field, sphericalTensor8>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> inv(const FieldField<Field, sphericalTensor8>& f)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> inv(const tmp<FieldField<Field, sphericalTensor8>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, sphericalTensor8>& res, const FieldField<Field, sphericalTensor8>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> diag(const FieldField<Field, sphericalTensor8>& f)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> diag(const tmp<FieldField<Field, sphericalTensor8>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor8>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const FieldField<Field, sphericalTensor8>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractLinear(const tmp<FieldField<Field, sphericalTensor8>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor8>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, sphericalTensor8>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, sphericalTensor8>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor8>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const FieldField<Field, scalar>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(reuseTmpFieldField<Field, sphericalTensor8, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor8, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor8, scalar, scalar, sphericalTensor8>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor8, scalar, scalar, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor8>& f, const scalar& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const scalar& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const scalar& s
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor8>& f, const FieldField<Field, scalar>& f1, const sphericalTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const FieldField<Field, scalar>& f1, const sphericalTensor8& s)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                    , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(reuseTmpFieldField<Field, sphericalTensor8, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor8, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1
	            , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const FieldField<Field, vector8>& f1
	                                           , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const FieldField<Field, vector8>& f1
	                                           , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, sphericalTensor8>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(
			reuseTmpTmpFieldField<Field, vector8, vector8, vector8, sphericalTensor8>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector8, vector8, vector8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector8>& f, const vector8& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const vector8& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const vector8& s, const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, sphericalTensor8>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1, const sphericalTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const FieldField<Field, vector8>& f1, const sphericalTensor8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const tmp<FieldField<Field, vector8>>& tf1, const sphericalTensor8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor8>& f, const FieldField<Field, sphericalTensor8>& f1
	            , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const FieldField<Field, sphericalTensor8>& f1
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const FieldField<Field, sphericalTensor8>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor8>& f, const sphericalTensor8& s
	            , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const sphericalTensor8& s
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const sphericalTensor8& s
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor8>& f, const FieldField<Field, sphericalTensor8>& f1
	            , const sphericalTensor8& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const FieldField<Field, sphericalTensor8>& f1
	                                                    , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator /(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                                    , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor8>& f, const FieldField<Field, sphericalTensor8>& f1
	         , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator +(const FieldField<Field, sphericalTensor8>& f1
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator +(const FieldField<Field, sphericalTensor8>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator +(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator +(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor8>& f, const FieldField<Field, sphericalTensor8>& f1
	              , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator -(const FieldField<Field, sphericalTensor8>& f1
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator -(const FieldField<Field, sphericalTensor8>& f1
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator -(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator -(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor8>& f, const sphericalTensor8& s
	         , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator +(const sphericalTensor8& s
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator +(const sphericalTensor8& s
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, sphericalTensor8>& f, const FieldField<Field, sphericalTensor8>& f1
	         , const sphericalTensor8& s) { for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); } }

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator +(const FieldField<Field, sphericalTensor8>& f1
	                                                    , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator +(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                                    , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor8>& f, const sphericalTensor8& s
	              , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator -(const sphericalTensor8& s
	                                                    , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator -(const sphericalTensor8& s
	                                                    , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, sphericalTensor8>& f, const FieldField<Field, sphericalTensor8>& f1
	              , const sphericalTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator -(const FieldField<Field, sphericalTensor8>& f1
	                                                    , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, sphericalTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor8>> operator -(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                                    , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, sphericalTensor8>>
			tRes(reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}
}

#undef SphericalTensorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //