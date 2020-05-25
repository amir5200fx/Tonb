#include <DiagTensorNFields.hxx>

#include <transformField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define DiagTensorN_FieldFunctions(tensorType, diagTensorType, sphericalTensorType, \
    vectorType, CmptType, args)                                                  \
                                                                                    \
UNARY_FUNCTION(diagTensorType, diagTensorType, inv)                                 \
UNARY_FUNCTION(diagTensorType, diagTensorType, diag)                                \
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
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, -, subtract)  \
                                                                                    \
template<>                                                                          \
tmp<Field<diagTensorType> > transformFieldMask<diagTensorType>                      \
(                                                                                   \
    const Field<sphericalTensorType>& stf                                           \
)                                                                                   \
{                                                                                   \
    tmp<Field<diagTensorType> > tRes( new Field<diagTensorType>(stf.size()) );      \
    Field<diagTensorType>& res = tRes();                                            \
    TFOR_ALL_F_OP_F(diagTensorType, res, =, sphericalTensorType, stf)               \
    return tRes;                                                                    \
}

namespace tnbLib
{
	void inv(Field<diagTensor2>& res, const UList<diagTensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor2, res, =, ::tnbLib::inv, diagTensor2, f)
	}

	tmp<Field<diagTensor2>> inv(const UList<diagTensor2>& f)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor2>> inv(const tmp<Field<diagTensor2>>& tf)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf);
		inv(tRes(), tf());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf);
		return tRes;
	}

	void diag(Field<diagTensor2>& res, const UList<diagTensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor2, res, =, ::tnbLib::diag, diagTensor2, f)
	}

	tmp<Field<diagTensor2>> diag(const UList<diagTensor2>& f)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor2>> diag(const tmp<Field<diagTensor2>>& tf)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const UList<scalar>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, scalar, f1, /, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator /(const UList<scalar>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const UList<scalar>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<scalar>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, scalar, scalar, diagTensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, scalar, scalar, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const scalar& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, scalar, s1, /, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator /(const scalar& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const scalar& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const UList<scalar>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, scalar, f1, /, diagTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator /(const UList<scalar>& f1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<scalar>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, scalar>::clear(tf1);
		return tRes;
	}

	void divide(Field<vector2>& res, const UList<vector2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector2, res, =, vector2, f1, /, diagTensor2, f2)
	}

	tmp<Field<vector2>> operator /(const UList<vector2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const UList<vector2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, diagTensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const tmp<Field<vector2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const tmp<Field<vector2>>& tf1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmpTmp<vector2, vector2, vector2, diagTensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector2, vector2, vector2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<vector2>& res, const vector2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector2, res, =, vector2, s1, /, diagTensor2, f2)
	}

	tmp<Field<vector2>> operator /(const vector2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const vector2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, diagTensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector2, diagTensor2>::clear(tf2);
		return tRes;
	}

	void divide(Field<vector2>& res, const UList<vector2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector2, res, =, vector2, f1, /, diagTensor2, s2)
	}

	tmp<Field<vector2>> operator /(const UList<vector2>& f1, const diagTensor2& s2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const tmp<Field<vector2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, diagTensor2, f1, /, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator /(const UList<diagTensor2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const UList<diagTensor2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<diagTensor2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<diagTensor2>>& tf1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, diagTensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const diagTensor2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, diagTensor2, s1, /, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator /(const diagTensor2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const diagTensor2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, diagTensor2, f1, /, diagTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator /(const UList<diagTensor2>& f1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<diagTensor2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const UList<sphericalTensor2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, sphericalTensor2, f1, /, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator /(const UList<sphericalTensor2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const UList<sphericalTensor2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<sphericalTensor2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<sphericalTensor2>>& tf1
	                                            , const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::
			New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const sphericalTensor2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, sphericalTensor2, s1, /, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator /(const sphericalTensor2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const sphericalTensor2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const UList<sphericalTensor2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, sphericalTensor2, f1, /, diagTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator /(const UList<sphericalTensor2>& f1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<sphericalTensor2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, diagTensor2, f1, /, sphericalTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator /(const UList<diagTensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const UList<diagTensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<diagTensor2>>& tf1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<diagTensor2>>& tf1
	                                            , const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const diagTensor2& s1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, diagTensor2, s1, /, sphericalTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator /(const diagTensor2& s1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const diagTensor2& s1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	void divide(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const sphericalTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, diagTensor2, f1, /, sphericalTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator /(const UList<diagTensor2>& f1, const sphericalTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator /(const tmp<Field<diagTensor2>>& tf1, const sphericalTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, diagTensor2, f1, +, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator +(const UList<diagTensor2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const UList<diagTensor2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const tmp<Field<diagTensor2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const tmp<Field<diagTensor2>>& tf1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, diagTensor2>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, diagTensor2, f1, -, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator -(const UList<diagTensor2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const UList<diagTensor2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const tmp<Field<diagTensor2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const tmp<Field<diagTensor2>>& tf1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, diagTensor2>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor2>& res, const diagTensor2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, diagTensor2, s1, +, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator +(const diagTensor2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const diagTensor2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	void add(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, diagTensor2, f1, +, diagTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator +(const UList<diagTensor2>& f1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const tmp<Field<diagTensor2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor2>& res, const diagTensor2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, diagTensor2, s1, -, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator -(const diagTensor2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const diagTensor2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	void subtract(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, diagTensor2, f1, -, diagTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator -(const UList<diagTensor2>& f1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const tmp<Field<diagTensor2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor2>& res, const UList<sphericalTensor2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, sphericalTensor2, f1, +, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator +(const UList<sphericalTensor2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const UList<sphericalTensor2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const tmp<Field<sphericalTensor2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const tmp<Field<sphericalTensor2>>& tf1
	                                            , const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::
			New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor2>& res, const UList<sphericalTensor2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, sphericalTensor2, f1, -, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator -(const UList<sphericalTensor2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const UList<sphericalTensor2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const tmp<Field<sphericalTensor2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const tmp<Field<sphericalTensor2>>& tf1
	                                            , const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::
			New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor2>& res, const sphericalTensor2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, sphericalTensor2, s1, +, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator +(const sphericalTensor2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const sphericalTensor2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	void add(Field<diagTensor2>& res, const UList<sphericalTensor2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, sphericalTensor2, f1, +, diagTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator +(const UList<sphericalTensor2>& f1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const tmp<Field<sphericalTensor2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor2>& res, const sphericalTensor2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, sphericalTensor2, s1, -, diagTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator -(const sphericalTensor2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const sphericalTensor2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	void subtract(Field<diagTensor2>& res, const UList<sphericalTensor2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, sphericalTensor2, f1, -, diagTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator -(const UList<sphericalTensor2>& f1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const tmp<Field<sphericalTensor2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, diagTensor2, f1, +, sphericalTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator +(const UList<diagTensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const UList<diagTensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const tmp<Field<diagTensor2>>& tf1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const tmp<Field<diagTensor2>>& tf1
	                                            , const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor2, res, =, diagTensor2, f1, -, sphericalTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator -(const UList<diagTensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const UList<diagTensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const tmp<Field<diagTensor2>>& tf1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const tmp<Field<diagTensor2>>& tf1
	                                            , const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor2>& res, const diagTensor2& s1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, diagTensor2, s1, +, sphericalTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator +(const diagTensor2& s1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const diagTensor2& s1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	void add(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const sphericalTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, diagTensor2, f1, +, sphericalTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator +(const UList<diagTensor2>& f1, const sphericalTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator +(const tmp<Field<diagTensor2>>& tf1, const sphericalTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor2>& res, const diagTensor2& s1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor2, res, =, diagTensor2, s1, -, sphericalTensor2, f2)
	}

	tmp<Field<diagTensor2>> operator -(const diagTensor2& s1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const diagTensor2& s1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, sphericalTensor2>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	void subtract(Field<diagTensor2>& res, const UList<diagTensor2>& f1, const sphericalTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor2, res, =, diagTensor2, f1, -, sphericalTensor2, s2)
	}

	tmp<Field<diagTensor2>> operator -(const UList<diagTensor2>& f1, const sphericalTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor2>> operator -(const tmp<Field<diagTensor2>>& tf1, const sphericalTensor2& s2)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, diagTensor2>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<diagTensor2>> transformFieldMask<diagTensor2>(const Field<sphericalTensor2>& stf)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(stf.size()));
		Field<diagTensor2>& res = tRes();
		TFOR_ALL_F_OP_F(diagTensor2, res, =, sphericalTensor2, stf)
		return tRes;
	} 
	
	void inv(Field<diagTensor3>& res, const UList<diagTensor3>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor3, res, =, ::tnbLib::inv, diagTensor3, f)
	}

	tmp<Field<diagTensor3>> inv(const UList<diagTensor3>& f)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor3>> inv(const tmp<Field<diagTensor3>>& tf)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf);
		inv(tRes(), tf());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf);
		return tRes;
	}

	void diag(Field<diagTensor3>& res, const UList<diagTensor3>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor3, res, =, ::tnbLib::diag, diagTensor3, f)
	}

	tmp<Field<diagTensor3>> diag(const UList<diagTensor3>& f)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor3>> diag(const tmp<Field<diagTensor3>>& tf)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const UList<scalar>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, scalar, f1, /, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator /(const UList<scalar>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const UList<scalar>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<scalar>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, scalar, scalar, diagTensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, scalar, scalar, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const scalar& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, scalar, s1, /, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator /(const scalar& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const scalar& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const UList<scalar>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, scalar, f1, /, diagTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator /(const UList<scalar>& f1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<scalar>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, scalar>::clear(tf1);
		return tRes;
	}

	void divide(Field<vector3>& res, const UList<vector3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector3, res, =, vector3, f1, /, diagTensor3, f2)
	}

	tmp<Field<vector3>> operator /(const UList<vector3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const UList<vector3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, diagTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<vector3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<vector3>>& tf1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmpTmp<vector3, vector3, vector3, diagTensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector3, vector3, vector3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<vector3>& res, const vector3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector3, res, =, vector3, s1, /, diagTensor3, f2)
	}

	tmp<Field<vector3>> operator /(const vector3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const vector3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, diagTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector3, diagTensor3>::clear(tf2);
		return tRes;
	}

	void divide(Field<vector3>& res, const UList<vector3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector3, res, =, vector3, f1, /, diagTensor3, s2)
	}

	tmp<Field<vector3>> operator /(const UList<vector3>& f1, const diagTensor3& s2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<vector3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, diagTensor3, f1, /, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator /(const UList<diagTensor3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const UList<diagTensor3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<diagTensor3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<diagTensor3>>& tf1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, diagTensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const diagTensor3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, diagTensor3, s1, /, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator /(const diagTensor3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const diagTensor3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, diagTensor3, f1, /, diagTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator /(const UList<diagTensor3>& f1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<diagTensor3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const UList<sphericalTensor3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, sphericalTensor3, f1, /, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator /(const UList<sphericalTensor3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const UList<sphericalTensor3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<sphericalTensor3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<sphericalTensor3>>& tf1
	                                            , const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::
			New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const sphericalTensor3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, sphericalTensor3, s1, /, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator /(const sphericalTensor3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const sphericalTensor3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const UList<sphericalTensor3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, sphericalTensor3, f1, /, diagTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator /(const UList<sphericalTensor3>& f1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<sphericalTensor3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, diagTensor3, f1, /, sphericalTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator /(const UList<diagTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const UList<diagTensor3>& f1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<diagTensor3>>& tf1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<diagTensor3>>& tf1
	                                            , const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const diagTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, diagTensor3, s1, /, sphericalTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator /(const diagTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const diagTensor3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	void divide(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, diagTensor3, f1, /, sphericalTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator /(const UList<diagTensor3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator /(const tmp<Field<diagTensor3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, diagTensor3, f1, +, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator +(const UList<diagTensor3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const UList<diagTensor3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const tmp<Field<diagTensor3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const tmp<Field<diagTensor3>>& tf1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, diagTensor3>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, diagTensor3, f1, -, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator -(const UList<diagTensor3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const UList<diagTensor3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const tmp<Field<diagTensor3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const tmp<Field<diagTensor3>>& tf1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, diagTensor3>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor3>& res, const diagTensor3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, diagTensor3, s1, +, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator +(const diagTensor3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const diagTensor3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	void add(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, diagTensor3, f1, +, diagTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator +(const UList<diagTensor3>& f1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const tmp<Field<diagTensor3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor3>& res, const diagTensor3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, diagTensor3, s1, -, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator -(const diagTensor3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const diagTensor3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	void subtract(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, diagTensor3, f1, -, diagTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator -(const UList<diagTensor3>& f1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const tmp<Field<diagTensor3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor3>& res, const UList<sphericalTensor3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, sphericalTensor3, f1, +, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator +(const UList<sphericalTensor3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const UList<sphericalTensor3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const tmp<Field<sphericalTensor3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const tmp<Field<sphericalTensor3>>& tf1
	                                            , const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::
			New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor3>& res, const UList<sphericalTensor3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, sphericalTensor3, f1, -, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator -(const UList<sphericalTensor3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const UList<sphericalTensor3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const tmp<Field<sphericalTensor3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const tmp<Field<sphericalTensor3>>& tf1
	                                            , const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::
			New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor3>& res, const sphericalTensor3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, sphericalTensor3, s1, +, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator +(const sphericalTensor3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const sphericalTensor3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	void add(Field<diagTensor3>& res, const UList<sphericalTensor3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, sphericalTensor3, f1, +, diagTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator +(const UList<sphericalTensor3>& f1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const tmp<Field<sphericalTensor3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor3>& res, const sphericalTensor3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, sphericalTensor3, s1, -, diagTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator -(const sphericalTensor3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const sphericalTensor3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	void subtract(Field<diagTensor3>& res, const UList<sphericalTensor3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, sphericalTensor3, f1, -, diagTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator -(const UList<sphericalTensor3>& f1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const tmp<Field<sphericalTensor3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, diagTensor3, f1, +, sphericalTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator +(const UList<diagTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const UList<diagTensor3>& f1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const tmp<Field<diagTensor3>>& tf1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const tmp<Field<diagTensor3>>& tf1,
	                                            const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor3, res, =, diagTensor3, f1, -, sphericalTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator -(const UList<diagTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const UList<diagTensor3>& f1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const tmp<Field<diagTensor3>>& tf1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const tmp<Field<diagTensor3>>& tf1,
	                                            const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor3>& res, const diagTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, diagTensor3, s1, +, sphericalTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator +(const diagTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const diagTensor3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}
	
	void add(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, diagTensor3, f1, +, sphericalTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator +(const UList<diagTensor3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator +(const tmp<Field<diagTensor3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor3>& res, const diagTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor3, res, =, diagTensor3, s1, -, sphericalTensor3, f2)
	}

	tmp<Field<diagTensor3>> operator -(const diagTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const diagTensor3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, sphericalTensor3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}
	
	void subtract(Field<diagTensor3>& res, const UList<diagTensor3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor3, res, =, diagTensor3, f1, -, sphericalTensor3, s2)
	}

	tmp<Field<diagTensor3>> operator -(const UList<diagTensor3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor3>> operator -(const tmp<Field<diagTensor3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, diagTensor3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<diagTensor3>> transformFieldMask<diagTensor3>(const Field<sphericalTensor3>& stf)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(stf.size()));
		Field<diagTensor3>& res = tRes();
		TFOR_ALL_F_OP_F(diagTensor3, res, =, sphericalTensor3, stf)
		return tRes;
	} 
	
	void inv(Field<diagTensor4>& res, const UList<diagTensor4>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor4, res, =, ::tnbLib::inv, diagTensor4, f)
	}

	tmp<Field<diagTensor4>> inv(const UList<diagTensor4>& f)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor4>> inv(const tmp<Field<diagTensor4>>& tf)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf);
		inv(tRes(), tf());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf);
		return tRes;
	}

	void diag(Field<diagTensor4>& res, const UList<diagTensor4>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor4, res, =, ::tnbLib::diag, diagTensor4, f)
	}

	tmp<Field<diagTensor4>> diag(const UList<diagTensor4>& f)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor4>> diag(const tmp<Field<diagTensor4>>& tf)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf);
		return tRes;
	}

	void divide(Field<diagTensor4>& res, const UList<scalar>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, scalar, f1, /, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator /(const UList<scalar>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const UList<scalar>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<scalar>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, scalar, scalar, diagTensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, scalar, scalar, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor4>& res, const scalar& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, scalar, s1, /, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator /(const scalar& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const scalar& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<diagTensor4>& res, const UList<scalar>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, scalar, f1, /, diagTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator /(const UList<scalar>& f1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<scalar>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, scalar>::clear(tf1);
		return tRes;
	}

	void divide(Field<vector4>& res, const UList<vector4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector4, res, =, vector4, f1, /, diagTensor4, f2)
	}

	tmp<Field<vector4>> operator /(const UList<vector4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const UList<vector4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, diagTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<vector4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<vector4>>& tf1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmpTmp<vector4, vector4, vector4, diagTensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector4, vector4, vector4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<vector4>& res, const vector4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector4, res, =, vector4, s1, /, diagTensor4, f2)
	}

	tmp<Field<vector4>> operator /(const vector4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const vector4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, diagTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector4, diagTensor4>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector4>& res, const UList<vector4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector4, res, =, vector4, f1, /, diagTensor4, s2)
	}

	tmp<Field<vector4>> operator /(const UList<vector4>& f1, const diagTensor4& s2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<vector4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, diagTensor4, f1, /, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator /(const UList<diagTensor4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const UList<diagTensor4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<diagTensor4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<diagTensor4>>& tf1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, diagTensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor4>& res, const diagTensor4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, diagTensor4, s1, /, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator /(const diagTensor4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const diagTensor4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, diagTensor4, f1, /, diagTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator /(const UList<diagTensor4>& f1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<diagTensor4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor4>& res, const UList<sphericalTensor4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, sphericalTensor4, f1, /, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator /(const UList<sphericalTensor4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const UList<sphericalTensor4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<sphericalTensor4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<sphericalTensor4>>& tf1,
	                                            const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::
			New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor4>& res, const sphericalTensor4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, sphericalTensor4, s1, /, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator /(const sphericalTensor4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const sphericalTensor4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<diagTensor4>& res, const UList<sphericalTensor4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, sphericalTensor4, f1, /, diagTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator /(const UList<sphericalTensor4>& f1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<sphericalTensor4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, diagTensor4, f1, /, sphericalTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator /(const UList<diagTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const UList<diagTensor4>& f1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<diagTensor4>>& tf1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<diagTensor4>>& tf1,
	                                            const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor4>& res, const diagTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, diagTensor4, s1, /, sphericalTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator /(const diagTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const diagTensor4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, diagTensor4, f1, /, sphericalTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator /(const UList<diagTensor4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator /(const tmp<Field<diagTensor4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, diagTensor4, f1, +, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator +(const UList<diagTensor4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const UList<diagTensor4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const tmp<Field<diagTensor4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const tmp<Field<diagTensor4>>& tf1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, diagTensor4>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, diagTensor4, f1, -, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator -(const UList<diagTensor4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const UList<diagTensor4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const tmp<Field<diagTensor4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const tmp<Field<diagTensor4>>& tf1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, diagTensor4>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor4>& res, const diagTensor4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, diagTensor4, s1, +, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator +(const diagTensor4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const diagTensor4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, diagTensor4, f1, +, diagTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator +(const UList<diagTensor4>& f1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const tmp<Field<diagTensor4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor4>& res, const diagTensor4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, diagTensor4, s1, -, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator -(const diagTensor4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const diagTensor4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, diagTensor4, f1, -, diagTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator -(const UList<diagTensor4>& f1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const tmp<Field<diagTensor4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor4>& res, const UList<sphericalTensor4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, sphericalTensor4, f1, +, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator +(const UList<sphericalTensor4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const UList<sphericalTensor4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const tmp<Field<sphericalTensor4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const tmp<Field<sphericalTensor4>>& tf1,
	                                            const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::
			New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor4>& res, const UList<sphericalTensor4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, sphericalTensor4, f1, -, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator -(const UList<sphericalTensor4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const UList<sphericalTensor4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const tmp<Field<sphericalTensor4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const tmp<Field<sphericalTensor4>>& tf1,
	                                            const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::
			New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor4>& res, const sphericalTensor4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, sphericalTensor4, s1, +, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator +(const sphericalTensor4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const sphericalTensor4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	}
	
	void add(Field<diagTensor4>& res, const UList<sphericalTensor4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, sphericalTensor4, f1, +, diagTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator +(const UList<sphericalTensor4>& f1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const tmp<Field<sphericalTensor4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor4>& res, const sphericalTensor4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, sphericalTensor4, s1, -, diagTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator -(const sphericalTensor4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const sphericalTensor4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor4, diagTensor4>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<diagTensor4>& res, const UList<sphericalTensor4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, sphericalTensor4, f1, -, diagTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator -(const UList<sphericalTensor4>& f1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const tmp<Field<sphericalTensor4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, diagTensor4, f1, +, sphericalTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator +(const UList<diagTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const UList<diagTensor4>& f1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const tmp<Field<diagTensor4>>& tf1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const tmp<Field<diagTensor4>>& tf1,
	                                            const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor4, res, =, diagTensor4, f1, -, sphericalTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator -(const UList<diagTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const UList<diagTensor4>& f1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const tmp<Field<diagTensor4>>& tf1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const tmp<Field<diagTensor4>>& tf1,
	                                            const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor4>& res, const diagTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, diagTensor4, s1, +, sphericalTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator +(const diagTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const diagTensor4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, diagTensor4, f1, +, sphericalTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator +(const UList<diagTensor4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator +(const tmp<Field<diagTensor4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor4>& res, const diagTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor4, res, =, diagTensor4, s1, -, sphericalTensor4, f2)
	}

	tmp<Field<diagTensor4>> operator -(const diagTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const diagTensor4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, sphericalTensor4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<diagTensor4>& res, const UList<diagTensor4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor4, res, =, diagTensor4, f1, -, sphericalTensor4, s2)
	}

	tmp<Field<diagTensor4>> operator -(const UList<diagTensor4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor4>> operator -(const tmp<Field<diagTensor4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, diagTensor4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<diagTensor4>> transformFieldMask<diagTensor4>(const Field<sphericalTensor4>& stf)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(stf.size()));
		Field<diagTensor4>& res = tRes();
		TFOR_ALL_F_OP_F(diagTensor4, res, =, sphericalTensor4, stf)
		return tRes;
	} 
	
	void inv(Field<diagTensor6>& res, const UList<diagTensor6>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor6, res, =, ::tnbLib::inv, diagTensor6, f)
	}

	tmp<Field<diagTensor6>> inv(const UList<diagTensor6>& f)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor6>> inv(const tmp<Field<diagTensor6>>& tf)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf);
		inv(tRes(), tf());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf);
		return tRes;
	}

	void diag(Field<diagTensor6>& res, const UList<diagTensor6>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor6, res, =, ::tnbLib::diag, diagTensor6, f)
	}

	tmp<Field<diagTensor6>> diag(const UList<diagTensor6>& f)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor6>> diag(const tmp<Field<diagTensor6>>& tf)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf);
		return tRes;
	}

	void divide(Field<diagTensor6>& res, const UList<scalar>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, scalar, f1, /, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator /(const UList<scalar>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const UList<scalar>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<scalar>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, scalar, scalar, diagTensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, scalar, scalar, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor6>& res, const scalar& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, scalar, s1, /, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator /(const scalar& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const scalar& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<diagTensor6>& res, const UList<scalar>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, scalar, f1, /, diagTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator /(const UList<scalar>& f1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<scalar>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, scalar>::clear(tf1);
		return tRes;
	}

	void divide(Field<vector6>& res, const UList<vector6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector6, res, =, vector6, f1, /, diagTensor6, f2)
	}

	tmp<Field<vector6>> operator /(const UList<vector6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const UList<vector6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, diagTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<vector6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<vector6>>& tf1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmpTmp<vector6, vector6, vector6, diagTensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector6, vector6, vector6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<vector6>& res, const vector6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector6, res, =, vector6, s1, /, diagTensor6, f2)
	}

	tmp<Field<vector6>> operator /(const vector6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const vector6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, diagTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector6>& res, const UList<vector6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector6, res, =, vector6, f1, /, diagTensor6, s2)
	}

	tmp<Field<vector6>> operator /(const UList<vector6>& f1, const diagTensor6& s2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<vector6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, diagTensor6, f1, /, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator /(const UList<diagTensor6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const UList<diagTensor6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<diagTensor6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<diagTensor6>>& tf1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, diagTensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor6>& res, const diagTensor6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, diagTensor6, s1, /, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator /(const diagTensor6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const diagTensor6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, diagTensor6, f1, /, diagTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator /(const UList<diagTensor6>& f1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<diagTensor6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor6>& res, const UList<sphericalTensor6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, sphericalTensor6, f1, /, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator /(const UList<sphericalTensor6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const UList<sphericalTensor6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<sphericalTensor6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<sphericalTensor6>>& tf1,
	                                            const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::
			New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor6>& res, const sphericalTensor6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, sphericalTensor6, s1, /, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator /(const sphericalTensor6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const sphericalTensor6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<diagTensor6>& res, const UList<sphericalTensor6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, sphericalTensor6, f1, /, diagTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator /(const UList<sphericalTensor6>& f1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<sphericalTensor6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, diagTensor6, f1, /, sphericalTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator /(const UList<diagTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const UList<diagTensor6>& f1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<diagTensor6>>& tf1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<diagTensor6>>& tf1,
	                                            const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor6>& res, const diagTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, diagTensor6, s1, /, sphericalTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator /(const diagTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const diagTensor6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, diagTensor6, f1, /, sphericalTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator /(const UList<diagTensor6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator /(const tmp<Field<diagTensor6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, diagTensor6, f1, +, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator +(const UList<diagTensor6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const UList<diagTensor6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const tmp<Field<diagTensor6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const tmp<Field<diagTensor6>>& tf1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, diagTensor6>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, diagTensor6, f1, -, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator -(const UList<diagTensor6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const UList<diagTensor6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const tmp<Field<diagTensor6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const tmp<Field<diagTensor6>>& tf1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, diagTensor6>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor6>& res, const diagTensor6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, diagTensor6, s1, +, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator +(const diagTensor6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const diagTensor6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, diagTensor6, f1, +, diagTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator +(const UList<diagTensor6>& f1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const tmp<Field<diagTensor6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor6>& res, const diagTensor6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, diagTensor6, s1, -, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator -(const diagTensor6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const diagTensor6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, diagTensor6, f1, -, diagTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator -(const UList<diagTensor6>& f1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const tmp<Field<diagTensor6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor6>& res, const UList<sphericalTensor6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, sphericalTensor6, f1, +, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator +(const UList<sphericalTensor6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const UList<sphericalTensor6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const tmp<Field<sphericalTensor6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const tmp<Field<sphericalTensor6>>& tf1,
	                                            const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::
			New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor6>& res, const UList<sphericalTensor6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, sphericalTensor6, f1, -, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator -(const UList<sphericalTensor6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const UList<sphericalTensor6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const tmp<Field<sphericalTensor6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const tmp<Field<sphericalTensor6>>& tf1,
	                                            const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::
			New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor6>& res, const sphericalTensor6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, sphericalTensor6, s1, +, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator +(const sphericalTensor6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const sphericalTensor6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<diagTensor6>& res, const UList<sphericalTensor6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, sphericalTensor6, f1, +, diagTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator +(const UList<sphericalTensor6>& f1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const tmp<Field<sphericalTensor6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor6>& res, const sphericalTensor6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, sphericalTensor6, s1, -, diagTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator -(const sphericalTensor6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const sphericalTensor6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<diagTensor6>& res, const UList<sphericalTensor6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, sphericalTensor6, f1, -, diagTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator -(const UList<sphericalTensor6>& f1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const tmp<Field<sphericalTensor6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, diagTensor6, f1, +, sphericalTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator +(const UList<diagTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const UList<diagTensor6>& f1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const tmp<Field<diagTensor6>>& tf1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const tmp<Field<diagTensor6>>& tf1,
	                                            const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor6, res, =, diagTensor6, f1, -, sphericalTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator -(const UList<diagTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const UList<diagTensor6>& f1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const tmp<Field<diagTensor6>>& tf1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const tmp<Field<diagTensor6>>& tf1,
	                                            const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor6>& res, const diagTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, diagTensor6, s1, +, sphericalTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator +(const diagTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const diagTensor6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, diagTensor6, f1, +, sphericalTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator +(const UList<diagTensor6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator +(const tmp<Field<diagTensor6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor6>& res, const diagTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor6, res, =, diagTensor6, s1, -, sphericalTensor6, f2)
	}

	tmp<Field<diagTensor6>> operator -(const diagTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const diagTensor6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, sphericalTensor6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<diagTensor6>& res, const UList<diagTensor6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor6, res, =, diagTensor6, f1, -, sphericalTensor6, s2)
	}

	tmp<Field<diagTensor6>> operator -(const UList<diagTensor6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor6>> operator -(const tmp<Field<diagTensor6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, diagTensor6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<diagTensor6>> transformFieldMask<diagTensor6>(const Field<sphericalTensor6>& stf)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(stf.size()));
		Field<diagTensor6>& res = tRes();
		TFOR_ALL_F_OP_F(diagTensor6, res, =, sphericalTensor6, stf)
		return tRes;
	} 
	
	void inv(Field<diagTensor8>& res, const UList<diagTensor8>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor8, res, =, ::tnbLib::inv, diagTensor8, f)
	}

	tmp<Field<diagTensor8>> inv(const UList<diagTensor8>& f)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor8>> inv(const tmp<Field<diagTensor8>>& tf)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf);
		inv(tRes(), tf());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf);
		return tRes;
	}

	void diag(Field<diagTensor8>& res, const UList<diagTensor8>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor8, res, =, ::tnbLib::diag, diagTensor8, f)
	}

	tmp<Field<diagTensor8>> diag(const UList<diagTensor8>& f)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor8>> diag(const tmp<Field<diagTensor8>>& tf)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf);
		return tRes;
	}

	void divide(Field<diagTensor8>& res, const UList<scalar>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, scalar, f1, /, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator /(const UList<scalar>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const UList<scalar>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<scalar>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, scalar, scalar, diagTensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, scalar, scalar, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor8>& res, const scalar& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, scalar, s1, /, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator /(const scalar& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const scalar& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<diagTensor8>& res, const UList<scalar>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, scalar, f1, /, diagTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator /(const UList<scalar>& f1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<scalar>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, scalar>::clear(tf1);
		return tRes;
	}

	void divide(Field<vector8>& res, const UList<vector8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector8, res, =, vector8, f1, /, diagTensor8, f2)
	}

	tmp<Field<vector8>> operator /(const UList<vector8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const UList<vector8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, diagTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<vector8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<vector8>>& tf1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmpTmp<vector8, vector8, vector8, diagTensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector8, vector8, vector8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<vector8>& res, const vector8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector8, res, =, vector8, s1, /, diagTensor8, f2)
	}

	tmp<Field<vector8>> operator /(const vector8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const vector8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, diagTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector8>& res, const UList<vector8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector8, res, =, vector8, f1, /, diagTensor8, s2)
	}

	tmp<Field<vector8>> operator /(const UList<vector8>& f1, const diagTensor8& s2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<vector8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, diagTensor8, f1, /, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator /(const UList<diagTensor8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const UList<diagTensor8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<diagTensor8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<diagTensor8>>& tf1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, diagTensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor8>& res, const diagTensor8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, diagTensor8, s1, /, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator /(const diagTensor8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const diagTensor8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, diagTensor8, f1, /, diagTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator /(const UList<diagTensor8>& f1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<diagTensor8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor8>& res, const UList<sphericalTensor8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, sphericalTensor8, f1, /, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator /(const UList<sphericalTensor8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const UList<sphericalTensor8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<sphericalTensor8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<sphericalTensor8>>& tf1,
	                                            const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::
			New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor8>& res, const sphericalTensor8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, sphericalTensor8, s1, /, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator /(const sphericalTensor8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const sphericalTensor8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<diagTensor8>& res, const UList<sphericalTensor8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, sphericalTensor8, f1, /, diagTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator /(const UList<sphericalTensor8>& f1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<sphericalTensor8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	void divide(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, diagTensor8, f1, /, sphericalTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator /(const UList<diagTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const UList<diagTensor8>& f1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<diagTensor8>>& tf1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<diagTensor8>>& tf1,
	                                            const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void divide(Field<diagTensor8>& res, const diagTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, diagTensor8, s1, /, sphericalTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator /(const diagTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const diagTensor8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, diagTensor8, f1, /, sphericalTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator /(const UList<diagTensor8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator /(const tmp<Field<diagTensor8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, diagTensor8, f1, +, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator +(const UList<diagTensor8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const UList<diagTensor8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const tmp<Field<diagTensor8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const tmp<Field<diagTensor8>>& tf1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, diagTensor8>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, diagTensor8, f1, -, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator -(const UList<diagTensor8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const UList<diagTensor8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const tmp<Field<diagTensor8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const tmp<Field<diagTensor8>>& tf1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, diagTensor8>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor8>& res, const diagTensor8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, diagTensor8, s1, +, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator +(const diagTensor8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const diagTensor8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, diagTensor8, f1, +, diagTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator +(const UList<diagTensor8>& f1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const tmp<Field<diagTensor8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor8>& res, const diagTensor8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, diagTensor8, s1, -, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator -(const diagTensor8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const diagTensor8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, diagTensor8, f1, -, diagTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator -(const UList<diagTensor8>& f1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const tmp<Field<diagTensor8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor8>& res, const UList<sphericalTensor8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, sphericalTensor8, f1, +, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator +(const UList<sphericalTensor8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const UList<sphericalTensor8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const tmp<Field<sphericalTensor8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const tmp<Field<sphericalTensor8>>& tf1,
	                                            const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::
			New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor8>& res, const UList<sphericalTensor8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, sphericalTensor8, f1, -, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator -(const UList<sphericalTensor8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const UList<sphericalTensor8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const tmp<Field<sphericalTensor8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const tmp<Field<sphericalTensor8>>& tf1,
	                                            const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::
			New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor8>& res, const sphericalTensor8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, sphericalTensor8, s1, +, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator +(const sphericalTensor8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const sphericalTensor8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<diagTensor8>& res, const UList<sphericalTensor8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, sphericalTensor8, f1, +, diagTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator +(const UList<sphericalTensor8>& f1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const tmp<Field<sphericalTensor8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor8>& res, const sphericalTensor8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, sphericalTensor8, s1, -, diagTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator -(const sphericalTensor8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const sphericalTensor8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<diagTensor8>& res, const UList<sphericalTensor8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, sphericalTensor8, f1, -, diagTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator -(const UList<sphericalTensor8>& f1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const tmp<Field<sphericalTensor8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	void add(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, diagTensor8, f1, +, sphericalTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator +(const UList<diagTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const UList<diagTensor8>& f1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const tmp<Field<diagTensor8>>& tf1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const tmp<Field<diagTensor8>>& tf1,
	                                            const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void subtract(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(diagTensor8, res, =, diagTensor8, f1, -, sphericalTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator -(const UList<diagTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const UList<diagTensor8>& f1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const tmp<Field<diagTensor8>>& tf1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const tmp<Field<diagTensor8>>& tf1,
	                                            const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}

	void add(Field<diagTensor8>& res, const diagTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, diagTensor8, s1, +, sphericalTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator +(const diagTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const diagTensor8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, diagTensor8, f1, +, sphericalTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator +(const UList<diagTensor8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator +(const tmp<Field<diagTensor8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	void subtract(Field<diagTensor8>& res, const diagTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(diagTensor8, res, =, diagTensor8, s1, -, sphericalTensor8, f2)
	}

	tmp<Field<diagTensor8>> operator -(const diagTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const diagTensor8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, sphericalTensor8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<diagTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<diagTensor8>& res, const UList<diagTensor8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(diagTensor8, res, =, diagTensor8, f1, -, sphericalTensor8, s2)
	}

	tmp<Field<diagTensor8>> operator -(const UList<diagTensor8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<diagTensor8>> operator -(const tmp<Field<diagTensor8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, diagTensor8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<diagTensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<diagTensor8>> transformFieldMask<diagTensor8>(const Field<sphericalTensor8>& stf)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(stf.size()));
		Field<diagTensor8>& res = tRes();
		TFOR_ALL_F_OP_F(diagTensor8, res, =, sphericalTensor8, stf)
		return tRes;
	}
}

#undef DiagTensorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>