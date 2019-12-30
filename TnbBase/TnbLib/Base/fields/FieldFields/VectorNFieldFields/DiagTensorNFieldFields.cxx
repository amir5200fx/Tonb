#include <DiagTensorNFieldFields.hxx>

#define TEMPLATE template<template<class> class Field>
#include <FieldFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define DiagTensorN_FieldFunctions(tensorType, diagTensorType, sphericalTensorType, \
    vectorType, CmptType, args)														\
                                                                                    \
UNARY_FUNCTION(diagTensorType, diagTensorType, inv)                                 \
UNARY_FUNCTION(diagTensorType, diagTensorType, diag)                                \
UNARY_FUNCTION(vectorType, diagTensorType, contractLinear)                          \
UNARY_FUNCTION(CmptType, diagTensorType, contractScalar)                            \
                                                                                    \
BINARY_OPERATOR(diagTensorType, CmptType, diagTensorType, /, divide)                \
BINARY_TYPE_OPERATOR(diagTensorType, CmptType, diagTensorType, /, divide)           \
                                                                                    \
BINARY_OPERATOR(vectorType, vectorType, diagTensorType, /, divide)                  \
BINARY_TYPE_OPERATOR(vectorType, vectorType, diagTensorType, /, divide)             \
                                                                                    \
BINARY_OPERATOR(diagTensorType, diagTensorType, diagTensorType, /, divide)          \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, diagTensorType, /, divide)     \
                                                                                    \
BINARY_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, /, divide)     \
BINARY_TYPE_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, /, divide)\
                                                                                    \
BINARY_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, /, divide)     \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, /, divide)\
                                                                                    \
BINARY_OPERATOR(diagTensorType, diagTensorType, diagTensorType, +, add)             \
BINARY_OPERATOR(diagTensorType, diagTensorType, diagTensorType, -, subtract)        \
                                                                                    \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, diagTensorType, +, add)        \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, diagTensorType, -, subtract)   \
                                                                                    \
BINARY_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, +, add)        \
BINARY_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, -, subtract)   \
                                                                                    \
BINARY_TYPE_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, +, add)   \
BINARY_TYPE_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, -, subtract)  \
                                                                                    \
BINARY_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, +, add)        \
BINARY_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, -, subtract)   \
                                                                                    \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, +, add)   \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, -, subtract)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template <template<class> class Field>
	void inv(FieldField<Field, diagTensor2>& res, const FieldField<Field, diagTensor2>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> inv(const FieldField<Field, diagTensor2>& f)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> inv(const tmp<FieldField<Field, diagTensor2>>& tf)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, diagTensor2>& res, const FieldField<Field, diagTensor2>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> diag(const FieldField<Field, diagTensor2>& f)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> diag(const tmp<FieldField<Field, diagTensor2>>& tf)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, vector2>& res, const FieldField<Field, diagTensor2>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> contractLinear(const FieldField<Field, diagTensor2>& f)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> contractLinear(const tmp<FieldField<Field, diagTensor2>>& tf)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, diagTensor2>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, diagTensor2>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, diagTensor2>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, scalar>& f1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, scalar>& f1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, scalar, scalar, diagTensor2>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, scalar, scalar, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const scalar& s, const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const scalar& s, const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const scalar& s, const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const FieldField<Field, scalar>& f1, const diagTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, scalar>& f1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, scalar>>& tf1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1
	            , const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const FieldField<Field, vector2>& f1
	                                           , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const FieldField<Field, vector2>& f1
	                                           , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, diagTensor2>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const tmp<FieldField<Field, vector2>>& tf1
	                                           , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(
			reuseTmpTmpFieldField<Field, vector2, vector2, vector2, diagTensor2>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector2, vector2, vector2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector2>& f, const vector2& s, const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const vector2& s, const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const vector2& s, const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, diagTensor2>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector2>& f, const FieldField<Field, vector2>& f1, const diagTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const FieldField<Field, vector2>& f1, const diagTensor2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(FieldField<Field, vector2>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector2>> operator /(const tmp<FieldField<Field, vector2>>& tf1, const diagTensor2& s)
	{
		tmp<FieldField<Field, vector2>> tRes(reuseTmpFieldField<Field, vector2, vector2>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector2, vector2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1
	            , const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, diagTensor2>& f1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, diagTensor2>& f1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, diagTensor2>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const diagTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const diagTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const diagTensor2& s, const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1, const diagTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, diagTensor2>& f1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, diagTensor2>>& tf1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const FieldField<Field, sphericalTensor2>& f1
	            , const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, sphericalTensor2>& f1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, sphericalTensor2>& f1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const sphericalTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const sphericalTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const sphericalTensor2& s
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const FieldField<Field, sphericalTensor2>& f1, const diagTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, sphericalTensor2>& f1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                               , const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1
	            , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, diagTensor2>& f1
	                                               , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, diagTensor2>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const diagTensor2& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const diagTensor2& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const diagTensor2& s
	                                               , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1, const sphericalTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const FieldField<Field, diagTensor2>& f1, const sphericalTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator /(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1
	         , const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const FieldField<Field, diagTensor2>& f1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const FieldField<Field, diagTensor2>& f1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, diagTensor2>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1
	              , const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const FieldField<Field, diagTensor2>& f1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const FieldField<Field, diagTensor2>& f1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, diagTensor2>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor2>& f, const diagTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const diagTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const diagTensor2& s, const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1, const diagTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const FieldField<Field, diagTensor2>& f1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const tmp<FieldField<Field, diagTensor2>>& tf1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor2>& f, const diagTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const diagTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const diagTensor2& s, const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1, const diagTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const FieldField<Field, diagTensor2>& f1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const tmp<FieldField<Field, diagTensor2>>& tf1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor2>& f, const FieldField<Field, sphericalTensor2>& f1
	         , const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const FieldField<Field, sphericalTensor2>& f1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const FieldField<Field, sphericalTensor2>& f1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor2>& f, const FieldField<Field, sphericalTensor2>& f1
	              , const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const FieldField<Field, sphericalTensor2>& f1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const FieldField<Field, sphericalTensor2>& f1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                               , const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor2>& f, const sphericalTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const sphericalTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const sphericalTensor2& s
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor2>& f, const FieldField<Field, sphericalTensor2>& f1, const diagTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const FieldField<Field, sphericalTensor2>& f1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                               , const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor2>& f, const sphericalTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const sphericalTensor2& s, const FieldField<Field, diagTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const sphericalTensor2& s
	                                               , const tmp<FieldField<Field, diagTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor2>& f, const FieldField<Field, sphericalTensor2>& f1, const diagTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const FieldField<Field, sphericalTensor2>& f1, const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const tmp<FieldField<Field, sphericalTensor2>>& tf1
	                                               , const diagTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1
	         , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const FieldField<Field, diagTensor2>& f1
	                                               , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const FieldField<Field, diagTensor2>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1
	              , const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const FieldField<Field, diagTensor2>& f1
	                                               , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const FieldField<Field, diagTensor2>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor2>& f, const diagTensor2& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const diagTensor2& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const diagTensor2& s
	                                               , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1, const sphericalTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const FieldField<Field, diagTensor2>& f1, const sphericalTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator +(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor2>& f, const diagTensor2& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const diagTensor2& s, const FieldField<Field, sphericalTensor2>& f2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, sphericalTensor2>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const diagTensor2& s
	                                               , const tmp<FieldField<Field, sphericalTensor2>>& tf2)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor2>& f, const FieldField<Field, diagTensor2>& f1, const sphericalTensor2& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const FieldField<Field, diagTensor2>& f1, const sphericalTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(FieldField<Field, diagTensor2>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor2>> operator -(const tmp<FieldField<Field, diagTensor2>>& tf1
	                                               , const sphericalTensor2& s)
	{
		tmp<FieldField<Field, diagTensor2>> tRes(reuseTmpFieldField<Field, diagTensor2, diagTensor2>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void inv(FieldField<Field, diagTensor3>& res, const FieldField<Field, diagTensor3>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> inv(const FieldField<Field, diagTensor3>& f)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> inv(const tmp<FieldField<Field, diagTensor3>>& tf)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, diagTensor3>& res, const FieldField<Field, diagTensor3>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> diag(const FieldField<Field, diagTensor3>& f)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> diag(const tmp<FieldField<Field, diagTensor3>>& tf)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, vector3>& res, const FieldField<Field, diagTensor3>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> contractLinear(const FieldField<Field, diagTensor3>& f)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> contractLinear(const tmp<FieldField<Field, diagTensor3>>& tf)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, diagTensor3>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, diagTensor3>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, diagTensor3>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, scalar>& f1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, scalar>& f1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, scalar, scalar, diagTensor3>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, scalar, scalar, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const scalar& s, const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const scalar& s, const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const scalar& s, const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const FieldField<Field, scalar>& f1, const diagTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, scalar>& f1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, scalar>>& tf1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1
	            , const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const FieldField<Field, vector3>& f1
	                                           , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const FieldField<Field, vector3>& f1
	                                           , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, diagTensor3>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const tmp<FieldField<Field, vector3>>& tf1
	                                           , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(
			reuseTmpTmpFieldField<Field, vector3, vector3, vector3, diagTensor3>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector3, vector3, vector3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector3>& f, const vector3& s, const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const vector3& s, const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const vector3& s, const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, diagTensor3>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector3>& f, const FieldField<Field, vector3>& f1, const diagTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const FieldField<Field, vector3>& f1, const diagTensor3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(FieldField<Field, vector3>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector3>> operator /(const tmp<FieldField<Field, vector3>>& tf1, const diagTensor3& s)
	{
		tmp<FieldField<Field, vector3>> tRes(reuseTmpFieldField<Field, vector3, vector3>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector3, vector3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1
	            , const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, diagTensor3>& f1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, diagTensor3>& f1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, diagTensor3>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const diagTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const diagTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const diagTensor3& s, const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1, const diagTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, diagTensor3>& f1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, diagTensor3>>& tf1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const FieldField<Field, sphericalTensor3>& f1
	            , const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, sphericalTensor3>& f1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, sphericalTensor3>& f1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const sphericalTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const sphericalTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const sphericalTensor3& s
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const FieldField<Field, sphericalTensor3>& f1, const diagTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, sphericalTensor3>& f1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                               , const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1
	            , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, diagTensor3>& f1
	                                               , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, diagTensor3>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const diagTensor3& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const diagTensor3& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const diagTensor3& s
	                                               , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1, const sphericalTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const FieldField<Field, diagTensor3>& f1, const sphericalTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator /(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1
	         , const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const FieldField<Field, diagTensor3>& f1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const FieldField<Field, diagTensor3>& f1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, diagTensor3>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1
	              , const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const FieldField<Field, diagTensor3>& f1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const FieldField<Field, diagTensor3>& f1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, diagTensor3>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor3>& f, const diagTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const diagTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const diagTensor3& s, const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1, const diagTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const FieldField<Field, diagTensor3>& f1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const tmp<FieldField<Field, diagTensor3>>& tf1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor3>& f, const diagTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const diagTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const diagTensor3& s, const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1, const diagTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const FieldField<Field, diagTensor3>& f1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const tmp<FieldField<Field, diagTensor3>>& tf1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor3>& f, const FieldField<Field, sphericalTensor3>& f1
	         , const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const FieldField<Field, sphericalTensor3>& f1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const FieldField<Field, sphericalTensor3>& f1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor3>& f, const FieldField<Field, sphericalTensor3>& f1
	              , const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const FieldField<Field, sphericalTensor3>& f1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const FieldField<Field, sphericalTensor3>& f1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                               , const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor3>& f, const sphericalTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const sphericalTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const sphericalTensor3& s
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor3>& f, const FieldField<Field, sphericalTensor3>& f1, const diagTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const FieldField<Field, sphericalTensor3>& f1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                               , const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor3>& f, const sphericalTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const sphericalTensor3& s, const FieldField<Field, diagTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const sphericalTensor3& s
	                                               , const tmp<FieldField<Field, diagTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor3>& f, const FieldField<Field, sphericalTensor3>& f1, const diagTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const FieldField<Field, sphericalTensor3>& f1, const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const tmp<FieldField<Field, sphericalTensor3>>& tf1
	                                               , const diagTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1
	         , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const FieldField<Field, diagTensor3>& f1
	                                               , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const FieldField<Field, diagTensor3>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1
	              , const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const FieldField<Field, diagTensor3>& f1
	                                               , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const FieldField<Field, diagTensor3>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor3>& f, const diagTensor3& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const diagTensor3& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const diagTensor3& s
	                                               , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1, const sphericalTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const FieldField<Field, diagTensor3>& f1, const sphericalTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator +(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor3>& f, const diagTensor3& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const diagTensor3& s, const FieldField<Field, sphericalTensor3>& f2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, sphericalTensor3>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const diagTensor3& s
	                                               , const tmp<FieldField<Field, sphericalTensor3>>& tf2)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor3>& f, const FieldField<Field, diagTensor3>& f1, const sphericalTensor3& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const FieldField<Field, diagTensor3>& f1, const sphericalTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(FieldField<Field, diagTensor3>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor3>> operator -(const tmp<FieldField<Field, diagTensor3>>& tf1
	                                               , const sphericalTensor3& s)
	{
		tmp<FieldField<Field, diagTensor3>> tRes(reuseTmpFieldField<Field, diagTensor3, diagTensor3>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void inv(FieldField<Field, diagTensor4>& res, const FieldField<Field, diagTensor4>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> inv(const FieldField<Field, diagTensor4>& f)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> inv(const tmp<FieldField<Field, diagTensor4>>& tf)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, diagTensor4>& res, const FieldField<Field, diagTensor4>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> diag(const FieldField<Field, diagTensor4>& f)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> diag(const tmp<FieldField<Field, diagTensor4>>& tf)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, vector4>& res, const FieldField<Field, diagTensor4>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> contractLinear(const FieldField<Field, diagTensor4>& f)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> contractLinear(const tmp<FieldField<Field, diagTensor4>>& tf)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, diagTensor4>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, diagTensor4>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, diagTensor4>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, scalar>& f1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, scalar>& f1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, scalar, scalar, diagTensor4>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, scalar, scalar, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const scalar& s, const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const scalar& s, const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const scalar& s, const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const FieldField<Field, scalar>& f1, const diagTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, scalar>& f1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, scalar>>& tf1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1
	            , const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const FieldField<Field, vector4>& f1
	                                           , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const FieldField<Field, vector4>& f1
	                                           , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, diagTensor4>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const tmp<FieldField<Field, vector4>>& tf1
	                                           , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(
			reuseTmpTmpFieldField<Field, vector4, vector4, vector4, diagTensor4>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector4, vector4, vector4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector4>& f, const vector4& s, const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const vector4& s, const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const vector4& s, const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, diagTensor4>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector4>& f, const FieldField<Field, vector4>& f1, const diagTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const FieldField<Field, vector4>& f1, const diagTensor4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(FieldField<Field, vector4>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector4>> operator /(const tmp<FieldField<Field, vector4>>& tf1, const diagTensor4& s)
	{
		tmp<FieldField<Field, vector4>> tRes(reuseTmpFieldField<Field, vector4, vector4>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector4, vector4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1
	            , const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, diagTensor4>& f1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, diagTensor4>& f1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, diagTensor4>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const diagTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const diagTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const diagTensor4& s, const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1, const diagTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, diagTensor4>& f1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, diagTensor4>>& tf1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const FieldField<Field, sphericalTensor4>& f1
	            , const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, sphericalTensor4>& f1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, sphericalTensor4>& f1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const sphericalTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const sphericalTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const sphericalTensor4& s
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const FieldField<Field, sphericalTensor4>& f1, const diagTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, sphericalTensor4>& f1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                               , const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1
	            , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, diagTensor4>& f1
	                                               , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, diagTensor4>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const diagTensor4& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const diagTensor4& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const diagTensor4& s
	                                               , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1, const sphericalTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const FieldField<Field, diagTensor4>& f1, const sphericalTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator /(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1
	         , const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const FieldField<Field, diagTensor4>& f1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const FieldField<Field, diagTensor4>& f1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, diagTensor4>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1
	              , const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const FieldField<Field, diagTensor4>& f1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const FieldField<Field, diagTensor4>& f1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, diagTensor4>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor4>& f, const diagTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const diagTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const diagTensor4& s, const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1, const diagTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const FieldField<Field, diagTensor4>& f1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const tmp<FieldField<Field, diagTensor4>>& tf1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor4>& f, const diagTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const diagTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const diagTensor4& s, const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1, const diagTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const FieldField<Field, diagTensor4>& f1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const tmp<FieldField<Field, diagTensor4>>& tf1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor4>& f, const FieldField<Field, sphericalTensor4>& f1
	         , const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const FieldField<Field, sphericalTensor4>& f1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const FieldField<Field, sphericalTensor4>& f1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor4>& f, const FieldField<Field, sphericalTensor4>& f1
	              , const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const FieldField<Field, sphericalTensor4>& f1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const FieldField<Field, sphericalTensor4>& f1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                               , const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor4>& f, const sphericalTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const sphericalTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const sphericalTensor4& s
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor4>& f, const FieldField<Field, sphericalTensor4>& f1, const diagTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const FieldField<Field, sphericalTensor4>& f1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                               , const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor4>& f, const sphericalTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const sphericalTensor4& s, const FieldField<Field, diagTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const sphericalTensor4& s
	                                               , const tmp<FieldField<Field, diagTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor4>& f, const FieldField<Field, sphericalTensor4>& f1, const diagTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const FieldField<Field, sphericalTensor4>& f1, const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const tmp<FieldField<Field, sphericalTensor4>>& tf1
	                                               , const diagTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1
	         , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const FieldField<Field, diagTensor4>& f1
	                                               , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const FieldField<Field, diagTensor4>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1
	              , const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const FieldField<Field, diagTensor4>& f1
	                                               , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const FieldField<Field, diagTensor4>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor4>& f, const diagTensor4& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const diagTensor4& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const diagTensor4& s
	                                               , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1, const sphericalTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const FieldField<Field, diagTensor4>& f1, const sphericalTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator +(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor4>& f, const diagTensor4& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const diagTensor4& s, const FieldField<Field, sphericalTensor4>& f2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, sphericalTensor4>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const diagTensor4& s
	                                               , const tmp<FieldField<Field, sphericalTensor4>>& tf2)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor4>& f, const FieldField<Field, diagTensor4>& f1, const sphericalTensor4& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const FieldField<Field, diagTensor4>& f1, const sphericalTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(FieldField<Field, diagTensor4>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor4>> operator -(const tmp<FieldField<Field, diagTensor4>>& tf1
	                                               , const sphericalTensor4& s)
	{
		tmp<FieldField<Field, diagTensor4>> tRes(reuseTmpFieldField<Field, diagTensor4, diagTensor4>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void inv(FieldField<Field, diagTensor6>& res, const FieldField<Field, diagTensor6>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> inv(const FieldField<Field, diagTensor6>& f)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> inv(const tmp<FieldField<Field, diagTensor6>>& tf)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, diagTensor6>& res, const FieldField<Field, diagTensor6>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> diag(const FieldField<Field, diagTensor6>& f)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> diag(const tmp<FieldField<Field, diagTensor6>>& tf)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, vector6>& res, const FieldField<Field, diagTensor6>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> contractLinear(const FieldField<Field, diagTensor6>& f)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> contractLinear(const tmp<FieldField<Field, diagTensor6>>& tf)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, diagTensor6>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, diagTensor6>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, diagTensor6>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, scalar>& f1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, scalar>& f1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, scalar, scalar, diagTensor6>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, scalar, scalar, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const scalar& s, const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const scalar& s, const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const scalar& s, const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const FieldField<Field, scalar>& f1, const diagTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, scalar>& f1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, scalar>>& tf1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1
	            , const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const FieldField<Field, vector6>& f1
	                                           , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const FieldField<Field, vector6>& f1
	                                           , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, diagTensor6>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const tmp<FieldField<Field, vector6>>& tf1
	                                           , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(
			reuseTmpTmpFieldField<Field, vector6, vector6, vector6, diagTensor6>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector6, vector6, vector6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector6>& f, const vector6& s, const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const vector6& s, const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const vector6& s, const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, diagTensor6>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector6>& f, const FieldField<Field, vector6>& f1, const diagTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const FieldField<Field, vector6>& f1, const diagTensor6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(FieldField<Field, vector6>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector6>> operator /(const tmp<FieldField<Field, vector6>>& tf1, const diagTensor6& s)
	{
		tmp<FieldField<Field, vector6>> tRes(reuseTmpFieldField<Field, vector6, vector6>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector6, vector6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1
	            , const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, diagTensor6>& f1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, diagTensor6>& f1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, diagTensor6>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const diagTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const diagTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const diagTensor6& s, const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1, const diagTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, diagTensor6>& f1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, diagTensor6>>& tf1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const FieldField<Field, sphericalTensor6>& f1
	            , const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, sphericalTensor6>& f1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, sphericalTensor6>& f1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const sphericalTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const sphericalTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const sphericalTensor6& s
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const FieldField<Field, sphericalTensor6>& f1, const diagTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, sphericalTensor6>& f1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                               , const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1
	            , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, diagTensor6>& f1
	                                               , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, diagTensor6>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const diagTensor6& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const diagTensor6& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const diagTensor6& s
	                                               , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1, const sphericalTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const FieldField<Field, diagTensor6>& f1, const sphericalTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator /(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1
	         , const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const FieldField<Field, diagTensor6>& f1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const FieldField<Field, diagTensor6>& f1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, diagTensor6>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1
	              , const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const FieldField<Field, diagTensor6>& f1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const FieldField<Field, diagTensor6>& f1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, diagTensor6>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor6>& f, const diagTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const diagTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const diagTensor6& s, const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1, const diagTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const FieldField<Field, diagTensor6>& f1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const tmp<FieldField<Field, diagTensor6>>& tf1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor6>& f, const diagTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const diagTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const diagTensor6& s, const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1, const diagTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const FieldField<Field, diagTensor6>& f1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const tmp<FieldField<Field, diagTensor6>>& tf1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor6>& f, const FieldField<Field, sphericalTensor6>& f1
	         , const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const FieldField<Field, sphericalTensor6>& f1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const FieldField<Field, sphericalTensor6>& f1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor6>& f, const FieldField<Field, sphericalTensor6>& f1
	              , const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const FieldField<Field, sphericalTensor6>& f1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const FieldField<Field, sphericalTensor6>& f1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                               , const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor6>& f, const sphericalTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const sphericalTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const sphericalTensor6& s
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor6>& f, const FieldField<Field, sphericalTensor6>& f1, const diagTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const FieldField<Field, sphericalTensor6>& f1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                               , const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor6>& f, const sphericalTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const sphericalTensor6& s, const FieldField<Field, diagTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const sphericalTensor6& s
	                                               , const tmp<FieldField<Field, diagTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor6>& f, const FieldField<Field, sphericalTensor6>& f1, const diagTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const FieldField<Field, sphericalTensor6>& f1, const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const tmp<FieldField<Field, sphericalTensor6>>& tf1
	                                               , const diagTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1
	         , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const FieldField<Field, diagTensor6>& f1
	                                               , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const FieldField<Field, diagTensor6>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1
	              , const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const FieldField<Field, diagTensor6>& f1
	                                               , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const FieldField<Field, diagTensor6>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor6>& f, const diagTensor6& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const diagTensor6& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const diagTensor6& s
	                                               , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1, const sphericalTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const FieldField<Field, diagTensor6>& f1, const sphericalTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator +(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor6>& f, const diagTensor6& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const diagTensor6& s, const FieldField<Field, sphericalTensor6>& f2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, sphericalTensor6>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const diagTensor6& s
	                                               , const tmp<FieldField<Field, sphericalTensor6>>& tf2)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor6>& f, const FieldField<Field, diagTensor6>& f1, const sphericalTensor6& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const FieldField<Field, diagTensor6>& f1, const sphericalTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(FieldField<Field, diagTensor6>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor6>> operator -(const tmp<FieldField<Field, diagTensor6>>& tf1
	                                               , const sphericalTensor6& s)
	{
		tmp<FieldField<Field, diagTensor6>> tRes(reuseTmpFieldField<Field, diagTensor6, diagTensor6>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void inv(FieldField<Field, diagTensor8>& res, const FieldField<Field, diagTensor8>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { inv(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> inv(const FieldField<Field, diagTensor8>& f)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> inv(const tmp<FieldField<Field, diagTensor8>>& tf)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void diag(FieldField<Field, diagTensor8>& res, const FieldField<Field, diagTensor8>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { diag(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> diag(const FieldField<Field, diagTensor8>& f)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f));
		diag(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> diag(const tmp<FieldField<Field, diagTensor8>>& tf)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf));
		diag(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractLinear(FieldField<Field, vector8>& res, const FieldField<Field, diagTensor8>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractLinear(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> contractLinear(const FieldField<Field, diagTensor8>& f)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f));
		contractLinear(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> contractLinear(const tmp<FieldField<Field, diagTensor8>>& tf)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf));
		contractLinear(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void contractScalar(FieldField<Field, scalar>& res, const FieldField<Field, diagTensor8>& f)
	{
		for (tnbLib::label i = 0; i < (res).size(); i++) { contractScalar(res[i], f[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const FieldField<Field, diagTensor8>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		contractScalar(tRes(), f);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> contractScalar(const tmp<FieldField<Field, diagTensor8>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf));
		contractScalar(tRes(), tf());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, scalar>& f1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, scalar>& f1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, scalar, scalar, diagTensor8>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, scalar, scalar, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const scalar& s, const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const scalar& s, const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const scalar& s, const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const FieldField<Field, scalar>& f1, const diagTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, scalar>& f1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, scalar>>& tf1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, scalar>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1
	            , const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const FieldField<Field, vector8>& f1
	                                           , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const FieldField<Field, vector8>& f1
	                                           , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, diagTensor8>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const tmp<FieldField<Field, vector8>>& tf1
	                                           , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(
			reuseTmpTmpFieldField<Field, vector8, vector8, vector8, diagTensor8>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector8, vector8, vector8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector8>& f, const vector8& s, const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const vector8& s, const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const vector8& s, const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, diagTensor8>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, vector8>& f, const FieldField<Field, vector8>& f1, const diagTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const FieldField<Field, vector8>& f1, const diagTensor8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(FieldField<Field, vector8>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, vector8>> operator /(const tmp<FieldField<Field, vector8>>& tf1, const diagTensor8& s)
	{
		tmp<FieldField<Field, vector8>> tRes(reuseTmpFieldField<Field, vector8, vector8>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector8, vector8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1
	            , const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, diagTensor8>& f1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, diagTensor8>& f1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, diagTensor8>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const diagTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const diagTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const diagTensor8& s, const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1, const diagTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, diagTensor8>& f1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, diagTensor8>>& tf1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const FieldField<Field, sphericalTensor8>& f1
	            , const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, sphericalTensor8>& f1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, sphericalTensor8>& f1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const sphericalTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const sphericalTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const sphericalTensor8& s
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const FieldField<Field, sphericalTensor8>& f1, const diagTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, sphericalTensor8>& f1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                               , const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1
	            , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, diagTensor8>& f1
	                                               , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, diagTensor8>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const diagTensor8& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const diagTensor8& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const diagTensor8& s
	                                               , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void divide(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1, const sphericalTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { divide(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const FieldField<Field, diagTensor8>& f1, const sphericalTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator /(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1
	         , const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const FieldField<Field, diagTensor8>& f1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const FieldField<Field, diagTensor8>& f1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, diagTensor8>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1
	              , const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const FieldField<Field, diagTensor8>& f1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const FieldField<Field, diagTensor8>& f1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, diagTensor8>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor8>& f, const diagTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const diagTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const diagTensor8& s, const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1, const diagTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const FieldField<Field, diagTensor8>& f1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const tmp<FieldField<Field, diagTensor8>>& tf1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor8>& f, const diagTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const diagTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const diagTensor8& s, const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1, const diagTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const FieldField<Field, diagTensor8>& f1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const tmp<FieldField<Field, diagTensor8>>& tf1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor8>& f, const FieldField<Field, sphericalTensor8>& f1
	         , const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const FieldField<Field, sphericalTensor8>& f1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const FieldField<Field, sphericalTensor8>& f1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor8>& f, const FieldField<Field, sphericalTensor8>& f1
	              , const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const FieldField<Field, sphericalTensor8>& f1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const FieldField<Field, sphericalTensor8>& f1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                               , const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor8>& f, const sphericalTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const sphericalTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const sphericalTensor8& s
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor8>& f, const FieldField<Field, sphericalTensor8>& f1, const diagTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const FieldField<Field, sphericalTensor8>& f1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                               , const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor8>& f, const sphericalTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const sphericalTensor8& s, const FieldField<Field, diagTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const sphericalTensor8& s
	                                               , const tmp<FieldField<Field, diagTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor8>& f, const FieldField<Field, sphericalTensor8>& f1, const diagTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const FieldField<Field, sphericalTensor8>& f1, const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const tmp<FieldField<Field, sphericalTensor8>>& tf1
	                                               , const diagTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1
	         , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const FieldField<Field, diagTensor8>& f1
	                                               , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const FieldField<Field, diagTensor8>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1
	              , const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const FieldField<Field, diagTensor8>& f1
	                                               , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const FieldField<Field, diagTensor8>& f1
	                                               , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(
			reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor8>& f, const diagTensor8& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const diagTensor8& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f2));
		add(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const diagTensor8& s
	                                               , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf2));
		add(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void add(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1, const sphericalTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { add(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const FieldField<Field, diagTensor8>& f1, const sphericalTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		add(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator +(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		add(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor8>& f, const diagTensor8& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], s, f2[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const diagTensor8& s, const FieldField<Field, sphericalTensor8>& f2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, sphericalTensor8>::NewCalculatedType(f2));
		subtract(tRes(), s, f2);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const diagTensor8& s
	                                               , const tmp<FieldField<Field, sphericalTensor8>>& tf2)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::New(tf2));
		subtract(tRes(), s, tf2());
		reuseTmpFieldField<Field, diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field>
	void subtract(FieldField<Field, diagTensor8>& f, const FieldField<Field, diagTensor8>& f1, const sphericalTensor8& s)
	{
		for (tnbLib::label i = 0; i < (f).size(); i++) { subtract(f[i], f1[i], s); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const FieldField<Field, diagTensor8>& f1, const sphericalTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(FieldField<Field, diagTensor8>::NewCalculatedType(f1));
		subtract(tRes(), f1, s);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, diagTensor8>> operator -(const tmp<FieldField<Field, diagTensor8>>& tf1
	                                               , const sphericalTensor8& s)
	{
		tmp<FieldField<Field, diagTensor8>> tRes(reuseTmpFieldField<Field, diagTensor8, diagTensor8>::New(tf1));
		subtract(tRes(), tf1(), s);
		reuseTmpFieldField<Field, diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#undef DiagTensorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //