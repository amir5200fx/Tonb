#include <VectorNFields.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define VectorN_FieldFunctions(tensorType,diagTensorType,                    \
                               sphericalTensorType,vectorType,CmptType,      \
                               args)										\
                                                                             \
UNARY_FUNCTION(CmptType, vectorType, cmptSum)                                \
                                                                             \
BINARY_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)            \
BINARY_TYPE_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)       \
                                                                             \
BINARY_OPERATOR(vectorType, CmptType, vectorType, /, divide)                 \
BINARY_TYPE_OPERATOR(vectorType, CmptType, vectorType, /, divide)            \
                                                                             \
BINARY_OPERATOR(vectorType, vectorType, vectorType, +, add)                  \
BINARY_OPERATOR(vectorType, vectorType, vectorType, -, subtract)             \
                                                                             \
BINARY_TYPE_OPERATOR(vectorType, vectorType, vectorType, +, add)             \
BINARY_TYPE_OPERATOR(vectorType, vectorType, vectorType, -, subtract)        \

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	void cmptSum(Field<scalar>& res, const UList<vector2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cmptSum, vector2, f)
	}

	tmp<Field<scalar>> cmptSum(const UList<vector2>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cmptSum(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> cmptSum(const tmp<Field<vector2>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, vector2>::New(tf);
		cmptSum(tRes(), tf());
		reuseTmp<scalar, vector2>::clear(tf);
		return tRes;
	}
	
	void cmptMultiply(Field<vector2>& res, const UList<vector2>& f1, const UList<vector2>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F ( vector2, res, =, ::tnbLib::cmptMultiply, vector2, f1, vector2, f2 )
	}

	tmp<Field<vector2>> cmptMultiply(const UList<vector2>& f1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector2>> cmptMultiply(const UList<vector2>& f1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf2);
		cmptMultiply(tRes(), f1, tf2());
		reuseTmp<vector2, vector2>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector2>> cmptMultiply(const tmp<Field<vector2>>& tf1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector2>> cmptMultiply(const tmp<Field<vector2>>& tf1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmpTmp<vector2, vector2, vector2, vector2>::New(tf1, tf2);
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmp<vector2, vector2, vector2, vector2>::clear(tf1, tf2);
		return tRes;
	}
	
	void cmptMultiply(Field<vector2>& res, const vector2& s1, const UList<vector2>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F ( vector2, res, =, ::tnbLib::cmptMultiply, vector2, s1, vector2, f2 )
	}

	tmp<Field<vector2>> cmptMultiply(const vector2& s1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f2.size()));
		cmptMultiply(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector2>> cmptMultiply(const vector2& s1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf2);
		cmptMultiply(tRes(), s1, tf2());
		reuseTmp<vector2, vector2>::clear(tf2);
		return tRes;
	}
	
	void cmptMultiply(Field<vector2>& res, const UList<vector2>& f1, const vector2& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S ( vector2, res, =, ::tnbLib::cmptMultiply, vector2, f1, vector2, s2 )
	}

	tmp<Field<vector2>> cmptMultiply(const UList<vector2>& f1, const vector2& s2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		cmptMultiply(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector2>> cmptMultiply(const tmp<Field<vector2>>& tf1, const vector2& s2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		cmptMultiply(tRes(), tf1(), s2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector2>& res, const UList<scalar>& f1, const UList<vector2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector2, res, =, scalar, f1, /, vector2, f2)
	}

	tmp<Field<vector2>> operator /(const UList<scalar>& f1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const UList<scalar>& f1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector2, vector2>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const tmp<Field<scalar>>& tf1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector2, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmpTmp<vector2, scalar, scalar, vector2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector2, scalar, scalar, vector2>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector2>& res, const scalar& s1, const UList<vector2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector2, res, =, scalar, s1, /, vector2, f2)
	}

	tmp<Field<vector2>> operator /(const scalar& s1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const scalar& s1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector2, vector2>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector2>& res, const UList<scalar>& f1, const vector2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector2, res, =, scalar, f1, /, vector2, s2)
	}

	tmp<Field<vector2>> operator /(const UList<scalar>& f1, const vector2& s2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const tmp<Field<scalar>>& tf1, const vector2& s2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector2, scalar>::clear(tf1);
		return tRes;
	}
	
	void add(Field<vector2>& res, const UList<vector2>& f1, const UList<vector2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector2, res, =, vector2, f1, +, vector2, f2)
	}

	tmp<Field<vector2>> operator +(const UList<vector2>& f1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator +(const UList<vector2>& f1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<vector2, vector2>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector2>> operator +(const tmp<Field<vector2>>& tf1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector2>> operator +(const tmp<Field<vector2>>& tf1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmpTmp<vector2, vector2, vector2, vector2>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<vector2, vector2, vector2, vector2>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<vector2>& res, const UList<vector2>& f1, const UList<vector2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector2, res, =, vector2, f1, -, vector2, f2)
	}

	tmp<Field<vector2>> operator -(const UList<vector2>& f1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator -(const UList<vector2>& f1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<vector2, vector2>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector2>> operator -(const tmp<Field<vector2>>& tf1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector2>> operator -(const tmp<Field<vector2>>& tf1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmpTmp<vector2, vector2, vector2, vector2>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<vector2, vector2, vector2, vector2>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<vector2>& res, const vector2& s1, const UList<vector2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector2, res, =, vector2, s1, +, vector2, f2)
	}

	tmp<Field<vector2>> operator +(const vector2& s1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator +(const vector2& s1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<vector2, vector2>::clear(tf2);
		return tRes;
	}
	
	void add(Field<vector2>& res, const UList<vector2>& f1, const vector2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector2, res, =, vector2, f1, +, vector2, s2)
	}

	tmp<Field<vector2>> operator +(const UList<vector2>& f1, const vector2& s2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector2>> operator +(const tmp<Field<vector2>>& tf1, const vector2& s2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<vector2>& res, const vector2& s1, const UList<vector2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector2, res, =, vector2, s1, -, vector2, f2)
	}

	tmp<Field<vector2>> operator -(const vector2& s1, const UList<vector2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator -(const vector2& s1, const tmp<Field<vector2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<vector2, vector2>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<vector2>& res, const UList<vector2>& f1, const vector2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector2, res, =, vector2, f1, -, vector2, s2)
	}

	tmp<Field<vector2>> operator -(const UList<vector2>& f1, const vector2& s2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector2>> operator -(const tmp<Field<vector2>>& tf1, const vector2& s2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	} 
	
	void cmptSum(Field<scalar>& res, const UList<vector3>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cmptSum, vector3, f)
	}

	tmp<Field<scalar>> cmptSum(const UList<vector3>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cmptSum(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> cmptSum(const tmp<Field<vector3>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, vector3>::New(tf);
		cmptSum(tRes(), tf());
		reuseTmp<scalar, vector3>::clear(tf);
		return tRes;
	}
	
	void cmptMultiply(Field<vector3>& res, const UList<vector3>& f1, const UList<vector3>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F ( vector3, res, =, ::tnbLib::cmptMultiply, vector3, f1, vector3, f2 )
	}

	tmp<Field<vector3>> cmptMultiply(const UList<vector3>& f1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector3>> cmptMultiply(const UList<vector3>& f1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf2);
		cmptMultiply(tRes(), f1, tf2());
		reuseTmp<vector3, vector3>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector3>> cmptMultiply(const tmp<Field<vector3>>& tf1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector3>> cmptMultiply(const tmp<Field<vector3>>& tf1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmpTmp<vector3, vector3, vector3, vector3>::New(tf1, tf2);
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmp<vector3, vector3, vector3, vector3>::clear(tf1, tf2);
		return tRes;
	}
	
	void cmptMultiply(Field<vector3>& res, const vector3& s1, const UList<vector3>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F ( vector3, res, =, ::tnbLib::cmptMultiply, vector3, s1, vector3, f2 )
	}

	tmp<Field<vector3>> cmptMultiply(const vector3& s1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f2.size()));
		cmptMultiply(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector3>> cmptMultiply(const vector3& s1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf2);
		cmptMultiply(tRes(), s1, tf2());
		reuseTmp<vector3, vector3>::clear(tf2);
		return tRes;
	} 
	
	void cmptMultiply(Field<vector3>& res, const UList<vector3>& f1, const vector3& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S ( vector3, res, =, ::tnbLib::cmptMultiply, vector3, f1, vector3, s2 )
	}

	tmp<Field<vector3>> cmptMultiply(const UList<vector3>& f1, const vector3& s2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		cmptMultiply(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector3>> cmptMultiply(const tmp<Field<vector3>>& tf1, const vector3& s2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		cmptMultiply(tRes(), tf1(), s2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector3>& res, const UList<scalar>& f1, const UList<vector3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector3, res, =, scalar, f1, /, vector3, f2)
	}

	tmp<Field<vector3>> operator /(const UList<scalar>& f1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const UList<scalar>& f1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector3, vector3>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<scalar>>& tf1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector3, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmpTmp<vector3, scalar, scalar, vector3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector3, scalar, scalar, vector3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector3>& res, const scalar& s1, const UList<vector3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector3, res, =, scalar, s1, /, vector3, f2)
	}

	tmp<Field<vector3>> operator /(const scalar& s1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const scalar& s1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector3, vector3>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<vector3>& res, const UList<scalar>& f1, const vector3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector3, res, =, scalar, f1, /, vector3, s2)
	}

	tmp<Field<vector3>> operator /(const UList<scalar>& f1, const vector3& s2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<scalar>>& tf1, const vector3& s2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector3, scalar>::clear(tf1);
		return tRes;
	}
	
	void add(Field<vector3>& res, const UList<vector3>& f1, const UList<vector3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector3, res, =, vector3, f1, +, vector3, f2)
	}

	tmp<Field<vector3>> operator +(const UList<vector3>& f1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator +(const UList<vector3>& f1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<vector3, vector3>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector3>> operator +(const tmp<Field<vector3>>& tf1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector3>> operator +(const tmp<Field<vector3>>& tf1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmpTmp<vector3, vector3, vector3, vector3>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<vector3, vector3, vector3, vector3>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<vector3>& res, const UList<vector3>& f1, const UList<vector3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector3, res, =, vector3, f1, -, vector3, f2)
	}

	tmp<Field<vector3>> operator -(const UList<vector3>& f1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator -(const UList<vector3>& f1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<vector3, vector3>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector3>> operator -(const tmp<Field<vector3>>& tf1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector3>> operator -(const tmp<Field<vector3>>& tf1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmpTmp<vector3, vector3, vector3, vector3>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<vector3, vector3, vector3, vector3>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<vector3>& res, const vector3& s1, const UList<vector3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector3, res, =, vector3, s1, +, vector3, f2)
	}

	tmp<Field<vector3>> operator +(const vector3& s1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator +(const vector3& s1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<vector3, vector3>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<vector3>& res, const UList<vector3>& f1, const vector3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector3, res, =, vector3, f1, +, vector3, s2)
	}

	tmp<Field<vector3>> operator +(const UList<vector3>& f1, const vector3& s2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector3>> operator +(const tmp<Field<vector3>>& tf1, const vector3& s2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<vector3>& res, const vector3& s1, const UList<vector3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector3, res, =, vector3, s1, -, vector3, f2)
	}

	tmp<Field<vector3>> operator -(const vector3& s1, const UList<vector3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator -(const vector3& s1, const tmp<Field<vector3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<vector3, vector3>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<vector3>& res, const UList<vector3>& f1, const vector3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector3, res, =, vector3, f1, -, vector3, s2)
	}

	tmp<Field<vector3>> operator -(const UList<vector3>& f1, const vector3& s2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector3>> operator -(const tmp<Field<vector3>>& tf1, const vector3& s2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	} 
	
	void cmptSum(Field<scalar>& res, const UList<vector4>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cmptSum, vector4, f)
	}

	tmp<Field<scalar>> cmptSum(const UList<vector4>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cmptSum(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> cmptSum(const tmp<Field<vector4>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, vector4>::New(tf);
		cmptSum(tRes(), tf());
		reuseTmp<scalar, vector4>::clear(tf);
		return tRes;
	}
	
	void cmptMultiply(Field<vector4>& res, const UList<vector4>& f1, const UList<vector4>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F ( vector4, res, =, ::tnbLib::cmptMultiply, vector4, f1, vector4, f2 )
	}

	tmp<Field<vector4>> cmptMultiply(const UList<vector4>& f1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector4>> cmptMultiply(const UList<vector4>& f1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf2);
		cmptMultiply(tRes(), f1, tf2());
		reuseTmp<vector4, vector4>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector4>> cmptMultiply(const tmp<Field<vector4>>& tf1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector4>> cmptMultiply(const tmp<Field<vector4>>& tf1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmpTmp<vector4, vector4, vector4, vector4>::New(tf1, tf2);
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmp<vector4, vector4, vector4, vector4>::clear(tf1, tf2);
		return tRes;
	}
	
	void cmptMultiply(Field<vector4>& res, const vector4& s1, const UList<vector4>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F ( vector4, res, =, ::tnbLib::cmptMultiply, vector4, s1, vector4, f2 )
	}

	tmp<Field<vector4>> cmptMultiply(const vector4& s1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f2.size()));
		cmptMultiply(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector4>> cmptMultiply(const vector4& s1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf2);
		cmptMultiply(tRes(), s1, tf2());
		reuseTmp<vector4, vector4>::clear(tf2);
		return tRes;
	} 
	
	void cmptMultiply(Field<vector4>& res, const UList<vector4>& f1, const vector4& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S ( vector4, res, =, ::tnbLib::cmptMultiply, vector4, f1, vector4, s2 )
	}

	tmp<Field<vector4>> cmptMultiply(const UList<vector4>& f1, const vector4& s2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		cmptMultiply(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector4>> cmptMultiply(const tmp<Field<vector4>>& tf1, const vector4& s2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		cmptMultiply(tRes(), tf1(), s2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector4>& res, const UList<scalar>& f1, const UList<vector4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector4, res, =, scalar, f1, /, vector4, f2)
	}

	tmp<Field<vector4>> operator /(const UList<scalar>& f1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const UList<scalar>& f1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector4, vector4>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<scalar>>& tf1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector4, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmpTmp<vector4, scalar, scalar, vector4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector4, scalar, scalar, vector4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector4>& res, const scalar& s1, const UList<vector4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector4, res, =, scalar, s1, /, vector4, f2)
	}

	tmp<Field<vector4>> operator /(const scalar& s1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const scalar& s1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector4, vector4>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector4>& res, const UList<scalar>& f1, const vector4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector4, res, =, scalar, f1, /, vector4, s2)
	}

	tmp<Field<vector4>> operator /(const UList<scalar>& f1, const vector4& s2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<scalar>>& tf1, const vector4& s2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector4, scalar>::clear(tf1);
		return tRes;
	}
	
	void add(Field<vector4>& res, const UList<vector4>& f1, const UList<vector4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector4, res, =, vector4, f1, +, vector4, f2)
	}

	tmp<Field<vector4>> operator +(const UList<vector4>& f1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator +(const UList<vector4>& f1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<vector4, vector4>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector4>> operator +(const tmp<Field<vector4>>& tf1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector4>> operator +(const tmp<Field<vector4>>& tf1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmpTmp<vector4, vector4, vector4, vector4>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<vector4, vector4, vector4, vector4>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<vector4>& res, const UList<vector4>& f1, const UList<vector4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector4, res, =, vector4, f1, -, vector4, f2)
	}

	tmp<Field<vector4>> operator -(const UList<vector4>& f1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator -(const UList<vector4>& f1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<vector4, vector4>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector4>> operator -(const tmp<Field<vector4>>& tf1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector4>> operator -(const tmp<Field<vector4>>& tf1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmpTmp<vector4, vector4, vector4, vector4>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<vector4, vector4, vector4, vector4>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<vector4>& res, const vector4& s1, const UList<vector4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector4, res, =, vector4, s1, +, vector4, f2)
	}

	tmp<Field<vector4>> operator +(const vector4& s1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator +(const vector4& s1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<vector4, vector4>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<vector4>& res, const UList<vector4>& f1, const vector4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector4, res, =, vector4, f1, +, vector4, s2)
	}

	tmp<Field<vector4>> operator +(const UList<vector4>& f1, const vector4& s2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector4>> operator +(const tmp<Field<vector4>>& tf1, const vector4& s2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<vector4>& res, const vector4& s1, const UList<vector4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector4, res, =, vector4, s1, -, vector4, f2)
	}

	tmp<Field<vector4>> operator -(const vector4& s1, const UList<vector4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator -(const vector4& s1, const tmp<Field<vector4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<vector4, vector4>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<vector4>& res, const UList<vector4>& f1, const vector4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector4, res, =, vector4, f1, -, vector4, s2)
	}

	tmp<Field<vector4>> operator -(const UList<vector4>& f1, const vector4& s2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector4>> operator -(const tmp<Field<vector4>>& tf1, const vector4& s2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	} 
	
	void cmptSum(Field<scalar>& res, const UList<vector6>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cmptSum, vector6, f)
	}

	tmp<Field<scalar>> cmptSum(const UList<vector6>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cmptSum(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> cmptSum(const tmp<Field<vector6>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, vector6>::New(tf);
		cmptSum(tRes(), tf());
		reuseTmp<scalar, vector6>::clear(tf);
		return tRes;
	}
	
	void cmptMultiply(Field<vector6>& res, const UList<vector6>& f1, const UList<vector6>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F ( vector6, res, =, ::tnbLib::cmptMultiply, vector6, f1, vector6, f2 )
	}

	tmp<Field<vector6>> cmptMultiply(const UList<vector6>& f1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector6>> cmptMultiply(const UList<vector6>& f1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf2);
		cmptMultiply(tRes(), f1, tf2());
		reuseTmp<vector6, vector6>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector6>> cmptMultiply(const tmp<Field<vector6>>& tf1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector6>> cmptMultiply(const tmp<Field<vector6>>& tf1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmpTmp<vector6, vector6, vector6, vector6>::New(tf1, tf2);
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmp<vector6, vector6, vector6, vector6>::clear(tf1, tf2);
		return tRes;
	}
	
	void cmptMultiply(Field<vector6>& res, const vector6& s1, const UList<vector6>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F ( vector6, res, =, ::tnbLib::cmptMultiply, vector6, s1, vector6, f2 )
	}

	tmp<Field<vector6>> cmptMultiply(const vector6& s1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f2.size()));
		cmptMultiply(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector6>> cmptMultiply(const vector6& s1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf2);
		cmptMultiply(tRes(), s1, tf2());
		reuseTmp<vector6, vector6>::clear(tf2);
		return tRes;
	} 
	
	void cmptMultiply(Field<vector6>& res, const UList<vector6>& f1, const vector6& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S ( vector6, res, =, ::tnbLib::cmptMultiply, vector6, f1, vector6, s2 )
	}

	tmp<Field<vector6>> cmptMultiply(const UList<vector6>& f1, const vector6& s2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		cmptMultiply(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector6>> cmptMultiply(const tmp<Field<vector6>>& tf1, const vector6& s2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		cmptMultiply(tRes(), tf1(), s2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector6>& res, const UList<scalar>& f1, const UList<vector6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector6, res, =, scalar, f1, /, vector6, f2)
	}

	tmp<Field<vector6>> operator /(const UList<scalar>& f1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const UList<scalar>& f1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector6, vector6>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<scalar>>& tf1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector6, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmpTmp<vector6, scalar, scalar, vector6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector6, scalar, scalar, vector6>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector6>& res, const scalar& s1, const UList<vector6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector6, res, =, scalar, s1, /, vector6, f2)
	}

	tmp<Field<vector6>> operator /(const scalar& s1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const scalar& s1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector6, vector6>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<vector6>& res, const UList<scalar>& f1, const vector6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector6, res, =, scalar, f1, /, vector6, s2)
	}

	tmp<Field<vector6>> operator /(const UList<scalar>& f1, const vector6& s2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<scalar>>& tf1, const vector6& s2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector6, scalar>::clear(tf1);
		return tRes;
	}
	
	void add(Field<vector6>& res, const UList<vector6>& f1, const UList<vector6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector6, res, =, vector6, f1, +, vector6, f2)
	}

	tmp<Field<vector6>> operator +(const UList<vector6>& f1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator +(const UList<vector6>& f1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<vector6, vector6>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector6>> operator +(const tmp<Field<vector6>>& tf1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector6>> operator +(const tmp<Field<vector6>>& tf1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmpTmp<vector6, vector6, vector6, vector6>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<vector6, vector6, vector6, vector6>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<vector6>& res, const UList<vector6>& f1, const UList<vector6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector6, res, =, vector6, f1, -, vector6, f2)
	}

	tmp<Field<vector6>> operator -(const UList<vector6>& f1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator -(const UList<vector6>& f1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<vector6, vector6>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector6>> operator -(const tmp<Field<vector6>>& tf1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector6>> operator -(const tmp<Field<vector6>>& tf1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmpTmp<vector6, vector6, vector6, vector6>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<vector6, vector6, vector6, vector6>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<vector6>& res, const vector6& s1, const UList<vector6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector6, res, =, vector6, s1, +, vector6, f2)
	}

	tmp<Field<vector6>> operator +(const vector6& s1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator +(const vector6& s1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<vector6, vector6>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<vector6>& res, const UList<vector6>& f1, const vector6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector6, res, =, vector6, f1, +, vector6, s2)
	}

	tmp<Field<vector6>> operator +(const UList<vector6>& f1, const vector6& s2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector6>> operator +(const tmp<Field<vector6>>& tf1, const vector6& s2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<vector6>& res, const vector6& s1, const UList<vector6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector6, res, =, vector6, s1, -, vector6, f2)
	}

	tmp<Field<vector6>> operator -(const vector6& s1, const UList<vector6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator -(const vector6& s1, const tmp<Field<vector6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<vector6, vector6>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<vector6>& res, const UList<vector6>& f1, const vector6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector6, res, =, vector6, f1, -, vector6, s2)
	}

	tmp<Field<vector6>> operator -(const UList<vector6>& f1, const vector6& s2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector6>> operator -(const tmp<Field<vector6>>& tf1, const vector6& s2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	} 
	
	void cmptSum(Field<scalar>& res, const UList<vector8>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cmptSum, vector8, f)
	}

	tmp<Field<scalar>> cmptSum(const UList<vector8>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cmptSum(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> cmptSum(const tmp<Field<vector8>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, vector8>::New(tf);
		cmptSum(tRes(), tf());
		reuseTmp<scalar, vector8>::clear(tf);
		return tRes;
	}
	
	void cmptMultiply(Field<vector8>& res, const UList<vector8>& f1, const UList<vector8>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F ( vector8, res, =, ::tnbLib::cmptMultiply, vector8, f1, vector8, f2 )
	}

	tmp<Field<vector8>> cmptMultiply(const UList<vector8>& f1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector8>> cmptMultiply(const UList<vector8>& f1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf2);
		cmptMultiply(tRes(), f1, tf2());
		reuseTmp<vector8, vector8>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector8>> cmptMultiply(const tmp<Field<vector8>>& tf1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector8>> cmptMultiply(const tmp<Field<vector8>>& tf1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmpTmp<vector8, vector8, vector8, vector8>::New(tf1, tf2);
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmp<vector8, vector8, vector8, vector8>::clear(tf1, tf2);
		return tRes;
	}
	
	void cmptMultiply(Field<vector8>& res, const vector8& s1, const UList<vector8>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F ( vector8, res, =, ::tnbLib::cmptMultiply, vector8, s1, vector8, f2 )
	}

	tmp<Field<vector8>> cmptMultiply(const vector8& s1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f2.size()));
		cmptMultiply(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector8>> cmptMultiply(const vector8& s1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf2);
		cmptMultiply(tRes(), s1, tf2());
		reuseTmp<vector8, vector8>::clear(tf2);
		return tRes;
	} 
	
	void cmptMultiply(Field<vector8>& res, const UList<vector8>& f1, const vector8& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S ( vector8, res, =, ::tnbLib::cmptMultiply, vector8, f1, vector8, s2 )
	}

	tmp<Field<vector8>> cmptMultiply(const UList<vector8>& f1, const vector8& s2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		cmptMultiply(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector8>> cmptMultiply(const tmp<Field<vector8>>& tf1, const vector8& s2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		cmptMultiply(tRes(), tf1(), s2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector8>& res, const UList<scalar>& f1, const UList<vector8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector8, res, =, scalar, f1, /, vector8, f2)
	}

	tmp<Field<vector8>> operator /(const UList<scalar>& f1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const UList<scalar>& f1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector8, vector8>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<scalar>>& tf1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector8, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmpTmp<vector8, scalar, scalar, vector8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector8, scalar, scalar, vector8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector8>& res, const scalar& s1, const UList<vector8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector8, res, =, scalar, s1, /, vector8, f2)
	}

	tmp<Field<vector8>> operator /(const scalar& s1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const scalar& s1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector8, vector8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector8>& res, const UList<scalar>& f1, const vector8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector8, res, =, scalar, f1, /, vector8, s2)
	}

	tmp<Field<vector8>> operator /(const UList<scalar>& f1, const vector8& s2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<scalar>>& tf1, const vector8& s2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector8, scalar>::clear(tf1);
		return tRes;
	}
	
	void add(Field<vector8>& res, const UList<vector8>& f1, const UList<vector8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector8, res, =, vector8, f1, +, vector8, f2)
	}

	tmp<Field<vector8>> operator +(const UList<vector8>& f1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator +(const UList<vector8>& f1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<vector8, vector8>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector8>> operator +(const tmp<Field<vector8>>& tf1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector8>> operator +(const tmp<Field<vector8>>& tf1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmpTmp<vector8, vector8, vector8, vector8>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<vector8, vector8, vector8, vector8>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<vector8>& res, const UList<vector8>& f1, const UList<vector8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector8, res, =, vector8, f1, -, vector8, f2)
	}

	tmp<Field<vector8>> operator -(const UList<vector8>& f1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator -(const UList<vector8>& f1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<vector8, vector8>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector8>> operator -(const tmp<Field<vector8>>& tf1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector8>> operator -(const tmp<Field<vector8>>& tf1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmpTmp<vector8, vector8, vector8, vector8>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<vector8, vector8, vector8, vector8>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<vector8>& res, const vector8& s1, const UList<vector8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector8, res, =, vector8, s1, +, vector8, f2)
	}

	tmp<Field<vector8>> operator +(const vector8& s1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator +(const vector8& s1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<vector8, vector8>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<vector8>& res, const UList<vector8>& f1, const vector8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector8, res, =, vector8, f1, +, vector8, s2)
	}

	tmp<Field<vector8>> operator +(const UList<vector8>& f1, const vector8& s2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector8>> operator +(const tmp<Field<vector8>>& tf1, const vector8& s2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<vector8>& res, const vector8& s1, const UList<vector8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector8, res, =, vector8, s1, -, vector8, f2)
	}

	tmp<Field<vector8>> operator -(const vector8& s1, const UList<vector8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator -(const vector8& s1, const tmp<Field<vector8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<vector8, vector8>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<vector8>& res, const UList<vector8>& f1, const vector8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector8, res, =, vector8, f1, -, vector8, s2)
	}

	tmp<Field<vector8>> operator -(const UList<vector8>& f1, const vector8& s2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector8>> operator -(const tmp<Field<vector8>>& tf1, const vector8& s2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}
}

#undef VectorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>