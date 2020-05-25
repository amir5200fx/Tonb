#include <TensorNFields.hxx>

#include <transformField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>
#include <ExpandTensorN.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define TensorN_FieldFunctions(tensorType,diagTensorType,                    \
                               sphericalTensorType,vectorType,CmptType,      \
                               args)                                      \
                                                                             \
UNARY_FUNCTION(CmptType, tensorType, det)                                    \
UNARY_FUNCTION(tensorType, tensorType, inv)                                  \
UNARY_FUNCTION(diagTensorType, tensorType, diag)                             \
UNARY_FUNCTION(tensorType, tensorType, negSumDiag)                           \
                                                                             \
BINARY_OPERATOR(tensorType, CmptType, tensorType, /, divide)                 \
BINARY_TYPE_OPERATOR(tensorType, CmptType, tensorType, /, divide)            \
                                                                             \
BINARY_OPERATOR(vectorType, vectorType, tensorType, /, divide)               \
BINARY_TYPE_OPERATOR(vectorType, vectorType, tensorType, /, divide)          \
                                                                             \
BINARY_OPERATOR(tensorType, tensorType, tensorType, /, divide)               \
BINARY_TYPE_OPERATOR(tensorType, tensorType, tensorType, /, divide)          \
                                                                             \
BINARY_OPERATOR(tensorType, tensorType, diagTensorType, /, divide)           \
BINARY_TYPE_OPERATOR(tensorType, tensorType, diagTensorType, /, divide)      \
                                                                             \
BINARY_OPERATOR(tensorType, diagTensorType, tensorType, /, divide)           \
BINARY_TYPE_OPERATOR(tensorType, diagTensorType, tensorType, /, divide)      \
                                                                             \
BINARY_OPERATOR(tensorType, sphericalTensorType, tensorType, /, divide)      \
BINARY_TYPE_OPERATOR(tensorType, sphericalTensorType, tensorType, /, divide) \
                                                                             \
BINARY_OPERATOR(tensorType, tensorType, sphericalTensorType, /, divide)      \
BINARY_TYPE_OPERATOR(tensorType, tensorType, sphericalTensorType, /, divide) \
                                                                             \
BINARY_OPERATOR(tensorType, tensorType, tensorType, +, add)                  \
BINARY_OPERATOR(tensorType, tensorType, tensorType, -, subtract)             \
                                                                             \
BINARY_TYPE_OPERATOR(tensorType, tensorType, tensorType, +, add)             \
BINARY_TYPE_OPERATOR(tensorType, tensorType, tensorType, -, subtract)        \
                                                                             \
BINARY_OPERATOR(tensorType, diagTensorType, tensorType, +, add)              \
BINARY_OPERATOR(tensorType, diagTensorType, tensorType, -, subtract)         \
                                                                             \
BINARY_TYPE_OPERATOR(tensorType, diagTensorType, tensorType, +, add)         \
BINARY_TYPE_OPERATOR(tensorType, diagTensorType, tensorType, -, subtract)    \
                                                                             \
BINARY_OPERATOR(tensorType, tensorType, diagTensorType, +, add)              \
BINARY_OPERATOR(tensorType, tensorType, diagTensorType, -, subtract)         \
                                                                             \
BINARY_TYPE_OPERATOR(tensorType, tensorType, diagTensorType, +, add)         \
BINARY_TYPE_OPERATOR(tensorType, tensorType, diagTensorType, -, subtract)    \
                                                                             \
BINARY_OPERATOR(tensorType, sphericalTensorType, tensorType, +, add)         \
BINARY_OPERATOR(tensorType, sphericalTensorType, tensorType, -, subtract)    \
                                                                             \
BINARY_TYPE_OPERATOR(tensorType, sphericalTensorType, tensorType, +, add)    \
BINARY_TYPE_OPERATOR(tensorType, sphericalTensorType, tensorType, -, subtract) \
                                                                             \
BINARY_OPERATOR(tensorType, tensorType, sphericalTensorType, +, add)         \
BINARY_OPERATOR(tensorType, tensorType, sphericalTensorType, -, subtract)    \
                                                                             \
BINARY_TYPE_OPERATOR(tensorType, tensorType, sphericalTensorType, +, add)    \
BINARY_TYPE_OPERATOR(tensorType, tensorType, sphericalTensorType, -, subtract) \
                                                                             \
template<>                                                                   \
tmp<Field<tensorType> > transformFieldMask<tensorType>                       \
(                                                                            \
    const Field<diagTensorType>& dtf                                         \
)                                                                            \
{                                                                            \
    tmp<Field<tensorType> > tRes(new Field<tensorType>(dtf.size()));         \
    Field<tensorType>& res = tRes();                                         \
    TFOR_ALL_F_OP_F(tensorType, res, =, diagTensorType, dtf)                 \
    return tRes;                                                             \
}                                                                            \
                                                                             \
template<>                                                                   \
tmp<Field<tensorType> > transformFieldMask<tensorType>                       \
(                                                                            \
    const Field<sphericalTensorType>& stf                                    \
)                                                                            \
{                                                                            \
    tmp<Field<tensorType> > tRes(new Field<tensorType>(stf.size()));         \
    Field<tensorType>& res = tRes();                                         \
    TFOR_ALL_F_OP_F(tensorType, res, =, sphericalTensorType, stf)            \
    return tRes;                                                             \
}                                                                            \


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	void det(Field<scalar>& res, const UList<tensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, tensor2, f)
	}

	tmp<Field<scalar>> det(const UList<tensor2>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		det(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> det(const tmp<Field<tensor2>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, tensor2>::New(tf);
		det(tRes(), tf());
		reuseTmp<scalar, tensor2>::clear(tf);
		return tRes;
	} 
	
	void inv(Field<tensor2>& res, const UList<tensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor2, res, =, ::tnbLib::inv, tensor2, f)
	}

	tmp<Field<tensor2>> inv(const UList<tensor2>& f)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor2>> inv(const tmp<Field<tensor2>>& tf)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf);
		inv(tRes(), tf());
		reuseTmp<tensor2, tensor2>::clear(tf);
		return tRes;
	} 
	
	void diag(Field<diagTensor2>& res, const UList<tensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor2, res, =, ::tnbLib::diag, tensor2, f)
	}

	tmp<Field<diagTensor2>> diag(const UList<tensor2>& f)
	{
		tmp<Field<diagTensor2>> tRes(new Field<diagTensor2>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor2>> diag(const tmp<Field<tensor2>>& tf)
	{
		tmp<Field<diagTensor2>> tRes = reuseTmp<diagTensor2, tensor2>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor2, tensor2>::clear(tf);
		return tRes;
	} 
	
	void negSumDiag(Field<tensor2>& res, const UList<tensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor2, res, =, ::tnbLib::negSumDiag, tensor2, f)
	}

	tmp<Field<tensor2>> negSumDiag(const UList<tensor2>& f)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f.size()));
		negSumDiag(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor2>> negSumDiag(const tmp<Field<tensor2>>& tf)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf);
		negSumDiag(tRes(), tf());
		reuseTmp<tensor2, tensor2>::clear(tf);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const UList<scalar>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, scalar, f1, /, tensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const UList<scalar>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const UList<scalar>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<scalar>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor2, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, scalar, scalar, tensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, scalar, scalar, tensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const scalar& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, scalar, s1, /, tensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const scalar& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const scalar& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor2>& res, const UList<scalar>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, scalar, f1, /, tensor2, s2)
	}

	tmp<Field<tensor2>> operator /(const UList<scalar>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<scalar>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor2, scalar>::clear(tf1);
		return tRes;
	} 
	
	void divide(Field<vector2>& res, const UList<vector2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector2, res, =, vector2, f1, /, tensor2, f2)
	}

	tmp<Field<vector2>> operator /(const UList<vector2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const UList<vector2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, tensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const tmp<Field<vector2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const tmp<Field<vector2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmpTmp<vector2, vector2, vector2, tensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector2, vector2, vector2, tensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<vector2>& res, const vector2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector2, res, =, vector2, s1, /, tensor2, f2)
	}

	tmp<Field<vector2>> operator /(const vector2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const vector2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, tensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector2, tensor2>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector2>& res, const UList<vector2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector2, res, =, vector2, f1, /, tensor2, s2)
	}

	tmp<Field<vector2>> operator /(const UList<vector2>& f1, const tensor2& s2)
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector2>> operator /(const tmp<Field<vector2>>& tf1, const tensor2& s2)
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector2, vector2>::clear(tf1);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const UList<tensor2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, tensor2, f1, /, tensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const UList<tensor2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const UList<tensor2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<tensor2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<tensor2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, tensor2, tensor2, tensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, tensor2, tensor2, tensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const tensor2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, tensor2, s1, /, tensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const tensor2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tensor2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const UList<tensor2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, tensor2, f1, /, tensor2, s2)
	}

	tmp<Field<tensor2>> operator /(const UList<tensor2>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<tensor2>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor2>& res, const UList<tensor2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, tensor2, f1, /, diagTensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const UList<tensor2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const UList<tensor2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<tensor2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<tensor2>>& tf1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, tensor2, tensor2, diagTensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, tensor2, tensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const tensor2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, tensor2, s1, /, diagTensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const tensor2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tensor2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor2, diagTensor2>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor2>& res, const UList<tensor2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, tensor2, f1, /, diagTensor2, s2)
	}

	tmp<Field<tensor2>> operator /(const UList<tensor2>& f1, const diagTensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<tensor2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor2>& res, const UList<diagTensor2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, diagTensor2, f1, /, tensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const UList<diagTensor2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const UList<diagTensor2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<diagTensor2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<diagTensor2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, diagTensor2, diagTensor2, tensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, diagTensor2, diagTensor2, tensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const diagTensor2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, diagTensor2, s1, /, tensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const diagTensor2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const diagTensor2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const UList<diagTensor2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, diagTensor2, f1, /, tensor2, s2)
	}

	tmp<Field<tensor2>> operator /(const UList<diagTensor2>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<diagTensor2>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor2, diagTensor2>::clear(tf1);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const UList<sphericalTensor2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, sphericalTensor2, f1, /, tensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const UList<sphericalTensor2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const UList<sphericalTensor2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<sphericalTensor2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<sphericalTensor2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, sphericalTensor2, sphericalTensor2, tensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, sphericalTensor2, sphericalTensor2, tensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const sphericalTensor2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, sphericalTensor2, s1, /, tensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const sphericalTensor2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const sphericalTensor2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const UList<sphericalTensor2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, sphericalTensor2, f1, /, tensor2, s2)
	}

	tmp<Field<tensor2>> operator /(const UList<sphericalTensor2>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<sphericalTensor2>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor2>& res, const UList<tensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, tensor2, f1, /, sphericalTensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const UList<tensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const UList<tensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<tensor2>>& tf1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<tensor2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, tensor2, tensor2, sphericalTensor2>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, tensor2, tensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<tensor2>& res, const tensor2& s1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, tensor2, s1, /, sphericalTensor2, f2)
	}

	tmp<Field<tensor2>> operator /(const tensor2& s1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tensor2& s1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor2>& res, const UList<tensor2>& f1, const sphericalTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, tensor2, f1, /, sphericalTensor2, s2)
	}

	tmp<Field<tensor2>> operator /(const UList<tensor2>& f1, const sphericalTensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator /(const tmp<Field<tensor2>>& tf1, const sphericalTensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	} 
	
	void add(Field<tensor2>& res, const UList<tensor2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, tensor2, f1, +, tensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const UList<tensor2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const UList<tensor2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<tensor2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<tensor2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, tensor2, tensor2, tensor2>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, tensor2, tensor2, tensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor2>& res, const UList<tensor2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, tensor2, f1, -, tensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const UList<tensor2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const UList<tensor2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<tensor2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<tensor2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, tensor2, tensor2, tensor2>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, tensor2, tensor2, tensor2>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const tensor2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, tensor2, s1, +, tensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const tensor2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tensor2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor2>& res, const UList<tensor2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, tensor2, f1, +, tensor2, s2)
	}

	tmp<Field<tensor2>> operator +(const UList<tensor2>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<tensor2>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const tensor2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, tensor2, s1, -, tensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const tensor2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tensor2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const UList<tensor2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, tensor2, f1, -, tensor2, s2)
	}

	tmp<Field<tensor2>> operator -(const UList<tensor2>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<tensor2>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const UList<diagTensor2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, diagTensor2, f1, +, tensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const UList<diagTensor2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const UList<diagTensor2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<diagTensor2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<diagTensor2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, diagTensor2, diagTensor2, tensor2>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, diagTensor2, diagTensor2, tensor2>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const UList<diagTensor2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, diagTensor2, f1, -, tensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const UList<diagTensor2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const UList<diagTensor2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<diagTensor2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor2, diagTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<diagTensor2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, diagTensor2, diagTensor2, tensor2>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, diagTensor2, diagTensor2, tensor2>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const diagTensor2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, diagTensor2, s1, +, tensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const diagTensor2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const diagTensor2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const UList<diagTensor2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, diagTensor2, f1, +, tensor2, s2)
	}

	tmp<Field<tensor2>> operator +(const UList<diagTensor2>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<diagTensor2>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor2, diagTensor2>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const diagTensor2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, diagTensor2, s1, -, tensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const diagTensor2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const diagTensor2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const UList<diagTensor2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, diagTensor2, f1, -, tensor2, s2)
	}

	tmp<Field<tensor2>> operator -(const UList<diagTensor2>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<diagTensor2>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor2, diagTensor2>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const UList<tensor2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, tensor2, f1, +, diagTensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const UList<tensor2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const UList<tensor2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<tensor2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<tensor2>>& tf1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, tensor2, tensor2, diagTensor2>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, tensor2, tensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const UList<tensor2>& f1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, tensor2, f1, -, diagTensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const UList<tensor2>& f1, const UList<diagTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const UList<tensor2>& f1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor2, diagTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<tensor2>>& tf1, const UList<diagTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<tensor2>>& tf1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, tensor2, tensor2, diagTensor2>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, tensor2, tensor2, diagTensor2>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const tensor2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, tensor2, s1, +, diagTensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const tensor2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tensor2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor2, diagTensor2>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor2>& res, const UList<tensor2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, tensor2, f1, +, diagTensor2, s2)
	}

	tmp<Field<tensor2>> operator +(const UList<tensor2>& f1, const diagTensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<tensor2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const tensor2& s1, const UList<diagTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, tensor2, s1, -, diagTensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const tensor2& s1, const UList<diagTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tensor2& s1, const tmp<Field<diagTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, diagTensor2>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor2, diagTensor2>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor2>& res, const UList<tensor2>& f1, const diagTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, tensor2, f1, -, diagTensor2, s2)
	}

	tmp<Field<tensor2>> operator -(const UList<tensor2>& f1, const diagTensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<tensor2>>& tf1, const diagTensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const UList<sphericalTensor2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, sphericalTensor2, f1, +, tensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const UList<sphericalTensor2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const UList<sphericalTensor2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<sphericalTensor2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<sphericalTensor2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, sphericalTensor2, sphericalTensor2, tensor2>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, sphericalTensor2, sphericalTensor2, tensor2>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const UList<sphericalTensor2>& f1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, sphericalTensor2, f1, -, tensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const UList<sphericalTensor2>& f1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const UList<sphericalTensor2>& f1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<sphericalTensor2>>& tf1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<sphericalTensor2>>& tf1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, sphericalTensor2, sphericalTensor2, tensor2>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, sphericalTensor2, sphericalTensor2, tensor2>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const sphericalTensor2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, sphericalTensor2, s1, +, tensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const sphericalTensor2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const sphericalTensor2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor2>& res, const UList<sphericalTensor2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, sphericalTensor2, f1, +, tensor2, s2)
	}

	tmp<Field<tensor2>> operator +(const UList<sphericalTensor2>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<sphericalTensor2>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const sphericalTensor2& s1, const UList<tensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, sphericalTensor2, s1, -, tensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const sphericalTensor2& s1, const UList<tensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const sphericalTensor2& s1, const tmp<Field<tensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor2, tensor2>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor2>& res, const UList<sphericalTensor2>& f1, const tensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, sphericalTensor2, f1, -, tensor2, s2)
	}

	tmp<Field<tensor2>> operator -(const UList<sphericalTensor2>& f1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<sphericalTensor2>>& tf1, const tensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const UList<tensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, tensor2, f1, +, sphericalTensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const UList<tensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const UList<tensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<tensor2>>& tf1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<tensor2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, tensor2, tensor2, sphericalTensor2>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, tensor2, tensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const UList<tensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor2, res, =, tensor2, f1, -, sphericalTensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const UList<tensor2>& f1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const UList<tensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<tensor2>>& tf1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<tensor2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmpTmp<tensor2, tensor2, tensor2, sphericalTensor2>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor2, tensor2, tensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor2>& res, const tensor2& s1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, tensor2, s1, +, sphericalTensor2, f2)
	}

	tmp<Field<tensor2>> operator +(const tensor2& s1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tensor2& s1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor2>& res, const UList<tensor2>& f1, const sphericalTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, tensor2, f1, +, sphericalTensor2, s2)
	}

	tmp<Field<tensor2>> operator +(const UList<tensor2>& f1, const sphericalTensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator +(const tmp<Field<tensor2>>& tf1, const sphericalTensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor2>& res, const tensor2& s1, const UList<sphericalTensor2>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor2, res, =, tensor2, s1, -, sphericalTensor2, f2)
	}

	tmp<Field<tensor2>> operator -(const tensor2& s1, const UList<sphericalTensor2>& f2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tensor2& s1, const tmp<Field<sphericalTensor2>>& tf2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, sphericalTensor2>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor2, sphericalTensor2>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor2>& res, const UList<tensor2>& f1, const sphericalTensor2& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor2, res, =, tensor2, f1, -, sphericalTensor2, s2)
	}

	tmp<Field<tensor2>> operator -(const UList<tensor2>& f1, const sphericalTensor2& s2)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor2>> operator -(const tmp<Field<tensor2>>& tf1, const sphericalTensor2& s2)
	{
		tmp<Field<tensor2>> tRes = reuseTmp<tensor2, tensor2>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor2, tensor2>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<tensor2>> transformFieldMask<tensor2>(const Field<diagTensor2>& dtf)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(dtf.size()));
		Field<tensor2>& res = tRes();
		TFOR_ALL_F_OP_F(tensor2, res, =, diagTensor2, dtf)
		return tRes;
	}

	template <>
	tmp<Field<tensor2>> transformFieldMask<tensor2>(const Field<sphericalTensor2>& stf)
	{
		tmp<Field<tensor2>> tRes(new Field<tensor2>(stf.size()));
		Field<tensor2>& res = tRes();
		TFOR_ALL_F_OP_F(tensor2, res, =, sphericalTensor2, stf)
		return tRes;
	} 
	
	void det(Field<scalar>& res, const UList<tensor3>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, tensor3, f)
	}

	tmp<Field<scalar>> det(const UList<tensor3>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		det(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> det(const tmp<Field<tensor3>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, tensor3>::New(tf);
		det(tRes(), tf());
		reuseTmp<scalar, tensor3>::clear(tf);
		return tRes;
	}
	
	void inv(Field<tensor3>& res, const UList<tensor3>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor3, res, =, ::tnbLib::inv, tensor3, f)
	}

	tmp<Field<tensor3>> inv(const UList<tensor3>& f)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor3>> inv(const tmp<Field<tensor3>>& tf)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf);
		inv(tRes(), tf());
		reuseTmp<tensor3, tensor3>::clear(tf);
		return tRes;
	}
	
	void diag(Field<diagTensor3>& res, const UList<tensor3>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor3, res, =, ::tnbLib::diag, tensor3, f)
	}

	tmp<Field<diagTensor3>> diag(const UList<tensor3>& f)
	{
		tmp<Field<diagTensor3>> tRes(new Field<diagTensor3>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor3>> diag(const tmp<Field<tensor3>>& tf)
	{
		tmp<Field<diagTensor3>> tRes = reuseTmp<diagTensor3, tensor3>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor3, tensor3>::clear(tf);
		return tRes;
	}
	
	void negSumDiag(Field<tensor3>& res, const UList<tensor3>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor3, res, =, ::tnbLib::negSumDiag, tensor3, f)
	}

	tmp<Field<tensor3>> negSumDiag(const UList<tensor3>& f)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f.size()));
		negSumDiag(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor3>> negSumDiag(const tmp<Field<tensor3>>& tf)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf);
		negSumDiag(tRes(), tf());
		reuseTmp<tensor3, tensor3>::clear(tf);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const UList<scalar>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, scalar, f1, /, tensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const UList<scalar>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const UList<scalar>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<scalar>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor3, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, scalar, scalar, tensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, scalar, scalar, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const scalar& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, scalar, s1, /, tensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const scalar& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const scalar& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor3>& res, const UList<scalar>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, scalar, f1, /, tensor3, s2)
	}

	tmp<Field<tensor3>> operator /(const UList<scalar>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<scalar>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor3, scalar>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector3>& res, const UList<vector3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector3, res, =, vector3, f1, /, tensor3, f2)
	}

	tmp<Field<vector3>> operator /(const UList<vector3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const UList<vector3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, tensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<vector3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<vector3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmpTmp<vector3, vector3, vector3, tensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector3, vector3, vector3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector3>& res, const vector3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector3, res, =, vector3, s1, /, tensor3, f2)
	}

	tmp<Field<vector3>> operator /(const vector3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const vector3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, tensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector3, tensor3>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector3>& res, const UList<vector3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector3, res, =, vector3, f1, /, tensor3, s2)
	}

	tmp<Field<vector3>> operator /(const UList<vector3>& f1, const tensor3& s2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<vector3>>& tf1, const tensor3& s2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const UList<tensor3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, tensor3, f1, /, tensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const UList<tensor3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const UList<tensor3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<tensor3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<tensor3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, tensor3, tensor3, tensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, tensor3, tensor3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const tensor3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, tensor3, s1, /, tensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const tensor3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tensor3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const UList<tensor3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, tensor3, f1, /, tensor3, s2)
	}

	tmp<Field<tensor3>> operator /(const UList<tensor3>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<tensor3>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const UList<tensor3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, tensor3, f1, /, diagTensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const UList<tensor3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const UList<tensor3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<tensor3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<tensor3>>& tf1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, tensor3, tensor3, diagTensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, tensor3, tensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const tensor3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, tensor3, s1, /, diagTensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const tensor3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tensor3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor3, diagTensor3>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const UList<tensor3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, tensor3, f1, /, diagTensor3, s2)
	}

	tmp<Field<tensor3>> operator /(const UList<tensor3>& f1, const diagTensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<tensor3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const UList<diagTensor3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, diagTensor3, f1, /, tensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const UList<diagTensor3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const UList<diagTensor3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<diagTensor3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<diagTensor3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, diagTensor3, diagTensor3, tensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, diagTensor3, diagTensor3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const diagTensor3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, diagTensor3, s1, /, tensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const diagTensor3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const diagTensor3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor3>& res, const UList<diagTensor3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, diagTensor3, f1, /, tensor3, s2)
	}

	tmp<Field<tensor3>> operator /(const UList<diagTensor3>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<diagTensor3>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor3, diagTensor3>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const UList<sphericalTensor3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, sphericalTensor3, f1, /, tensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const UList<sphericalTensor3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const UList<sphericalTensor3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<sphericalTensor3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<sphericalTensor3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, sphericalTensor3, sphericalTensor3, tensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, sphericalTensor3, sphericalTensor3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const sphericalTensor3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, sphericalTensor3, s1, /, tensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const sphericalTensor3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const sphericalTensor3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor3>& res, const UList<sphericalTensor3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, sphericalTensor3, f1, /, tensor3, s2)
	}

	tmp<Field<tensor3>> operator /(const UList<sphericalTensor3>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<sphericalTensor3>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const UList<tensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, tensor3, f1, /, sphericalTensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const UList<tensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const UList<tensor3>& f1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<tensor3>>& tf1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<tensor3>>& tf1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, tensor3, tensor3, sphericalTensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, tensor3, tensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor3>& res, const tensor3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, tensor3, s1, /, sphericalTensor3, f2)
	}

	tmp<Field<tensor3>> operator /(const tensor3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tensor3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor3>& res, const UList<tensor3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, tensor3, f1, /, sphericalTensor3, s2)
	}

	tmp<Field<tensor3>> operator /(const UList<tensor3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator /(const tmp<Field<tensor3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const UList<tensor3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, tensor3, f1, +, tensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const UList<tensor3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const UList<tensor3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<tensor3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<tensor3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, tensor3, tensor3, tensor3>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, tensor3, tensor3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const UList<tensor3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, tensor3, f1, -, tensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const UList<tensor3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const UList<tensor3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<tensor3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<tensor3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, tensor3, tensor3, tensor3>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, tensor3, tensor3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const tensor3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, tensor3, s1, +, tensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const tensor3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tensor3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor3>& res, const UList<tensor3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, tensor3, f1, +, tensor3, s2)
	}

	tmp<Field<tensor3>> operator +(const UList<tensor3>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<tensor3>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const tensor3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, tensor3, s1, -, tensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const tensor3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tensor3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor3>& res, const UList<tensor3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, tensor3, f1, -, tensor3, s2)
	}

	tmp<Field<tensor3>> operator -(const UList<tensor3>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<tensor3>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const UList<diagTensor3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, diagTensor3, f1, +, tensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const UList<diagTensor3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const UList<diagTensor3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<diagTensor3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<diagTensor3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, diagTensor3, diagTensor3, tensor3>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, diagTensor3, diagTensor3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const UList<diagTensor3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, diagTensor3, f1, -, tensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const UList<diagTensor3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const UList<diagTensor3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<diagTensor3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor3, diagTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<diagTensor3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, diagTensor3, diagTensor3, tensor3>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, diagTensor3, diagTensor3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const diagTensor3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, diagTensor3, s1, +, tensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const diagTensor3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const diagTensor3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const UList<diagTensor3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, diagTensor3, f1, +, tensor3, s2)
	}

	tmp<Field<tensor3>> operator +(const UList<diagTensor3>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<diagTensor3>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor3, diagTensor3>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const diagTensor3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, diagTensor3, s1, -, tensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const diagTensor3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const diagTensor3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor3>& res, const UList<diagTensor3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, diagTensor3, f1, -, tensor3, s2)
	}

	tmp<Field<tensor3>> operator -(const UList<diagTensor3>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<diagTensor3>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor3, diagTensor3>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const UList<tensor3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, tensor3, f1, +, diagTensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const UList<tensor3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const UList<tensor3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<tensor3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<tensor3>>& tf1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, tensor3, tensor3, diagTensor3>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, tensor3, tensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const UList<tensor3>& f1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, tensor3, f1, -, diagTensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const UList<tensor3>& f1, const UList<diagTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const UList<tensor3>& f1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor3, diagTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<tensor3>>& tf1, const UList<diagTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<tensor3>>& tf1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, tensor3, tensor3, diagTensor3>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, tensor3, tensor3, diagTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const tensor3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, tensor3, s1, +, diagTensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const tensor3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tensor3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor3, diagTensor3>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor3>& res, const UList<tensor3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, tensor3, f1, +, diagTensor3, s2)
	}

	tmp<Field<tensor3>> operator +(const UList<tensor3>& f1, const diagTensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<tensor3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const tensor3& s1, const UList<diagTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, tensor3, s1, -, diagTensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const tensor3& s1, const UList<diagTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tensor3& s1, const tmp<Field<diagTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, diagTensor3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor3, diagTensor3>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor3>& res, const UList<tensor3>& f1, const diagTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, tensor3, f1, -, diagTensor3, s2)
	}

	tmp<Field<tensor3>> operator -(const UList<tensor3>& f1, const diagTensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<tensor3>>& tf1, const diagTensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const UList<sphericalTensor3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, sphericalTensor3, f1, +, tensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const UList<sphericalTensor3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const UList<sphericalTensor3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<sphericalTensor3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<sphericalTensor3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, sphericalTensor3, sphericalTensor3, tensor3>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, sphericalTensor3, sphericalTensor3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const UList<sphericalTensor3>& f1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, sphericalTensor3, f1, -, tensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const UList<sphericalTensor3>& f1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const UList<sphericalTensor3>& f1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<sphericalTensor3>>& tf1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<sphericalTensor3>>& tf1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, sphericalTensor3, sphericalTensor3, tensor3>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, sphericalTensor3, sphericalTensor3, tensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const sphericalTensor3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, sphericalTensor3, s1, +, tensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const sphericalTensor3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const sphericalTensor3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor3>& res, const UList<sphericalTensor3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, sphericalTensor3, f1, +, tensor3, s2)
	}

	tmp<Field<tensor3>> operator +(const UList<sphericalTensor3>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<sphericalTensor3>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const sphericalTensor3& s1, const UList<tensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, sphericalTensor3, s1, -, tensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const sphericalTensor3& s1, const UList<tensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const sphericalTensor3& s1, const tmp<Field<tensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor3, tensor3>::clear(tf2);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const UList<sphericalTensor3>& f1, const tensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, sphericalTensor3, f1, -, tensor3, s2)
	}

	tmp<Field<tensor3>> operator -(const UList<sphericalTensor3>& f1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<sphericalTensor3>>& tf1, const tensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const UList<tensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, tensor3, f1, +, sphericalTensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const UList<tensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const UList<tensor3>& f1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<tensor3>>& tf1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<tensor3>>& tf1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, tensor3, tensor3, sphericalTensor3>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, tensor3, tensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const UList<tensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor3, res, =, tensor3, f1, -, sphericalTensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const UList<tensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const UList<tensor3>& f1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<tensor3>>& tf1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<tensor3>>& tf1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmpTmp<tensor3, tensor3, tensor3, sphericalTensor3>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor3, tensor3, tensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor3>& res, const tensor3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, tensor3, s1, +, sphericalTensor3, f2)
	}

	tmp<Field<tensor3>> operator +(const tensor3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tensor3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor3>& res, const UList<tensor3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, tensor3, f1, +, sphericalTensor3, s2)
	}

	tmp<Field<tensor3>> operator +(const UList<tensor3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator +(const tmp<Field<tensor3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor3>& res, const tensor3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor3, res, =, tensor3, s1, -, sphericalTensor3, f2)
	}

	tmp<Field<tensor3>> operator -(const tensor3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tensor3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, sphericalTensor3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor3>& res, const UList<tensor3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor3, res, =, tensor3, f1, -, sphericalTensor3, s2)
	}

	tmp<Field<tensor3>> operator -(const UList<tensor3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor3>> operator -(const tmp<Field<tensor3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<tensor3>> tRes = reuseTmp<tensor3, tensor3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor3, tensor3>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<tensor3>> transformFieldMask<tensor3>(const Field<diagTensor3>& dtf)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(dtf.size()));
		Field<tensor3>& res = tRes();
		TFOR_ALL_F_OP_F(tensor3, res, =, diagTensor3, dtf)
		return tRes;
	}

	template <>
	tmp<Field<tensor3>> transformFieldMask<tensor3>(const Field<sphericalTensor3>& stf)
	{
		tmp<Field<tensor3>> tRes(new Field<tensor3>(stf.size()));
		Field<tensor3>& res = tRes();
		TFOR_ALL_F_OP_F(tensor3, res, =, sphericalTensor3, stf)
		return tRes;
	} 
	
	void det(Field<scalar>& res, const UList<tensor4>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, tensor4, f)
	}

	tmp<Field<scalar>> det(const UList<tensor4>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		det(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> det(const tmp<Field<tensor4>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, tensor4>::New(tf);
		det(tRes(), tf());
		reuseTmp<scalar, tensor4>::clear(tf);
		return tRes;
	}
	
	void inv(Field<tensor4>& res, const UList<tensor4>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor4, res, =, ::tnbLib::inv, tensor4, f)
	}

	tmp<Field<tensor4>> inv(const UList<tensor4>& f)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor4>> inv(const tmp<Field<tensor4>>& tf)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf);
		inv(tRes(), tf());
		reuseTmp<tensor4, tensor4>::clear(tf);
		return tRes;
	}
	
	void diag(Field<diagTensor4>& res, const UList<tensor4>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor4, res, =, ::tnbLib::diag, tensor4, f)
	}

	tmp<Field<diagTensor4>> diag(const UList<tensor4>& f)
	{
		tmp<Field<diagTensor4>> tRes(new Field<diagTensor4>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor4>> diag(const tmp<Field<tensor4>>& tf)
	{
		tmp<Field<diagTensor4>> tRes = reuseTmp<diagTensor4, tensor4>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor4, tensor4>::clear(tf);
		return tRes;
	}
	
	void negSumDiag(Field<tensor4>& res, const UList<tensor4>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor4, res, =, ::tnbLib::negSumDiag, tensor4, f)
	}

	tmp<Field<tensor4>> negSumDiag(const UList<tensor4>& f)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f.size()));
		negSumDiag(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor4>> negSumDiag(const tmp<Field<tensor4>>& tf)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf);
		negSumDiag(tRes(), tf());
		reuseTmp<tensor4, tensor4>::clear(tf);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const UList<scalar>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, scalar, f1, /, tensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const UList<scalar>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const UList<scalar>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<scalar>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor4, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, scalar, scalar, tensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, scalar, scalar, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const scalar& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, scalar, s1, /, tensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const scalar& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const scalar& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const UList<scalar>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, scalar, f1, /, tensor4, s2)
	}

	tmp<Field<tensor4>> operator /(const UList<scalar>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<scalar>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor4, scalar>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector4>& res, const UList<vector4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector4, res, =, vector4, f1, /, tensor4, f2)
	}

	tmp<Field<vector4>> operator /(const UList<vector4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const UList<vector4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, tensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<vector4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<vector4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmpTmp<vector4, vector4, vector4, tensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector4, vector4, vector4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector4>& res, const vector4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector4, res, =, vector4, s1, /, tensor4, f2)
	}

	tmp<Field<vector4>> operator /(const vector4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const vector4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, tensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector4, tensor4>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector4>& res, const UList<vector4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector4, res, =, vector4, f1, /, tensor4, s2)
	}

	tmp<Field<vector4>> operator /(const UList<vector4>& f1, const tensor4& s2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<vector4>>& tf1, const tensor4& s2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const UList<tensor4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, tensor4, f1, /, tensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const UList<tensor4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const UList<tensor4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<tensor4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<tensor4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, tensor4, tensor4, tensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, tensor4, tensor4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const tensor4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, tensor4, s1, /, tensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const tensor4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tensor4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const UList<tensor4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, tensor4, f1, /, tensor4, s2)
	}

	tmp<Field<tensor4>> operator /(const UList<tensor4>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<tensor4>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const UList<tensor4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, tensor4, f1, /, diagTensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const UList<tensor4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const UList<tensor4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<tensor4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<tensor4>>& tf1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, tensor4, tensor4, diagTensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, tensor4, tensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const tensor4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, tensor4, s1, /, diagTensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const tensor4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tensor4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor4, diagTensor4>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor4>& res, const UList<tensor4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, tensor4, f1, /, diagTensor4, s2)
	}

	tmp<Field<tensor4>> operator /(const UList<tensor4>& f1, const diagTensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<tensor4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const UList<diagTensor4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, diagTensor4, f1, /, tensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const UList<diagTensor4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const UList<diagTensor4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<diagTensor4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<diagTensor4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, diagTensor4, diagTensor4, tensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, diagTensor4, diagTensor4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const diagTensor4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, diagTensor4, s1, /, tensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const diagTensor4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const diagTensor4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor4>& res, const UList<diagTensor4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, diagTensor4, f1, /, tensor4, s2)
	}

	tmp<Field<tensor4>> operator /(const UList<diagTensor4>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<diagTensor4>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor4, diagTensor4>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const UList<sphericalTensor4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, sphericalTensor4, f1, /, tensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const UList<sphericalTensor4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const UList<sphericalTensor4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<sphericalTensor4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<sphericalTensor4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, sphericalTensor4, sphericalTensor4, tensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, sphericalTensor4, sphericalTensor4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const sphericalTensor4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, sphericalTensor4, s1, /, tensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const sphericalTensor4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const sphericalTensor4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const UList<sphericalTensor4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, sphericalTensor4, f1, /, tensor4, s2)
	}

	tmp<Field<tensor4>> operator /(const UList<sphericalTensor4>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<sphericalTensor4>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const UList<tensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, tensor4, f1, /, sphericalTensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const UList<tensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const UList<tensor4>& f1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<tensor4>>& tf1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<tensor4>>& tf1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, tensor4, tensor4, sphericalTensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, tensor4, tensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor4>& res, const tensor4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, tensor4, s1, /, sphericalTensor4, f2)
	}

	tmp<Field<tensor4>> operator /(const tensor4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tensor4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor4>& res, const UList<tensor4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, tensor4, f1, /, sphericalTensor4, s2)
	}

	tmp<Field<tensor4>> operator /(const UList<tensor4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator /(const tmp<Field<tensor4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const UList<tensor4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, tensor4, f1, +, tensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const UList<tensor4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const UList<tensor4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<tensor4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<tensor4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, tensor4, tensor4, tensor4>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, tensor4, tensor4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const UList<tensor4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, tensor4, f1, -, tensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const UList<tensor4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const UList<tensor4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<tensor4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<tensor4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, tensor4, tensor4, tensor4>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, tensor4, tensor4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const tensor4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, tensor4, s1, +, tensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const tensor4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tensor4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const UList<tensor4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, tensor4, f1, +, tensor4, s2)
	}

	tmp<Field<tensor4>> operator +(const UList<tensor4>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<tensor4>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const tensor4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, tensor4, s1, -, tensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const tensor4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tensor4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor4>& res, const UList<tensor4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, tensor4, f1, -, tensor4, s2)
	}

	tmp<Field<tensor4>> operator -(const UList<tensor4>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<tensor4>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const UList<diagTensor4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, diagTensor4, f1, +, tensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const UList<diagTensor4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const UList<diagTensor4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<diagTensor4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<diagTensor4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, diagTensor4, diagTensor4, tensor4>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, diagTensor4, diagTensor4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const UList<diagTensor4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, diagTensor4, f1, -, tensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const UList<diagTensor4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const UList<diagTensor4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<diagTensor4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor4, diagTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<diagTensor4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, diagTensor4, diagTensor4, tensor4>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, diagTensor4, diagTensor4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const diagTensor4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, diagTensor4, s1, +, tensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const diagTensor4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const diagTensor4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor4>& res, const UList<diagTensor4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, diagTensor4, f1, +, tensor4, s2)
	}

	tmp<Field<tensor4>> operator +(const UList<diagTensor4>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<diagTensor4>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor4, diagTensor4>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const diagTensor4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, diagTensor4, s1, -, tensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const diagTensor4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const diagTensor4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor4>& res, const UList<diagTensor4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, diagTensor4, f1, -, tensor4, s2)
	}

	tmp<Field<tensor4>> operator -(const UList<diagTensor4>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<diagTensor4>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor4, diagTensor4>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const UList<tensor4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, tensor4, f1, +, diagTensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const UList<tensor4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const UList<tensor4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<tensor4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<tensor4>>& tf1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, tensor4, tensor4, diagTensor4>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, tensor4, tensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const UList<tensor4>& f1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, tensor4, f1, -, diagTensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const UList<tensor4>& f1, const UList<diagTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const UList<tensor4>& f1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor4, diagTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<tensor4>>& tf1, const UList<diagTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<tensor4>>& tf1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, tensor4, tensor4, diagTensor4>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, tensor4, tensor4, diagTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const tensor4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, tensor4, s1, +, diagTensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const tensor4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tensor4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor4, diagTensor4>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor4>& res, const UList<tensor4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, tensor4, f1, +, diagTensor4, s2)
	}

	tmp<Field<tensor4>> operator +(const UList<tensor4>& f1, const diagTensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<tensor4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const tensor4& s1, const UList<diagTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, tensor4, s1, -, diagTensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const tensor4& s1, const UList<diagTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tensor4& s1, const tmp<Field<diagTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, diagTensor4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor4, diagTensor4>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor4>& res, const UList<tensor4>& f1, const diagTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, tensor4, f1, -, diagTensor4, s2)
	}

	tmp<Field<tensor4>> operator -(const UList<tensor4>& f1, const diagTensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<tensor4>>& tf1, const diagTensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const UList<sphericalTensor4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, sphericalTensor4, f1, +, tensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const UList<sphericalTensor4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const UList<sphericalTensor4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<sphericalTensor4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<sphericalTensor4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, sphericalTensor4, sphericalTensor4, tensor4>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, sphericalTensor4, sphericalTensor4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const UList<sphericalTensor4>& f1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, sphericalTensor4, f1, -, tensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const UList<sphericalTensor4>& f1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const UList<sphericalTensor4>& f1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<sphericalTensor4>>& tf1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<sphericalTensor4>>& tf1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, sphericalTensor4, sphericalTensor4, tensor4>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, sphericalTensor4, sphericalTensor4, tensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const sphericalTensor4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, sphericalTensor4, s1, +, tensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const sphericalTensor4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const sphericalTensor4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor4>& res, const UList<sphericalTensor4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, sphericalTensor4, f1, +, tensor4, s2)
	}

	tmp<Field<tensor4>> operator +(const UList<sphericalTensor4>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<sphericalTensor4>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const sphericalTensor4& s1, const UList<tensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, sphericalTensor4, s1, -, tensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const sphericalTensor4& s1, const UList<tensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const sphericalTensor4& s1, const tmp<Field<tensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor4, tensor4>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor4>& res, const UList<sphericalTensor4>& f1, const tensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, sphericalTensor4, f1, -, tensor4, s2)
	}

	tmp<Field<tensor4>> operator -(const UList<sphericalTensor4>& f1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<sphericalTensor4>>& tf1, const tensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const UList<tensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, tensor4, f1, +, sphericalTensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const UList<tensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const UList<tensor4>& f1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<tensor4>>& tf1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<tensor4>>& tf1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, tensor4, tensor4, sphericalTensor4>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, tensor4, tensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const UList<tensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor4, res, =, tensor4, f1, -, sphericalTensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const UList<tensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const UList<tensor4>& f1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<tensor4>>& tf1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<tensor4>>& tf1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmpTmp<tensor4, tensor4, tensor4, sphericalTensor4>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor4, tensor4, tensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor4>& res, const tensor4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, tensor4, s1, +, sphericalTensor4, f2)
	}

	tmp<Field<tensor4>> operator +(const tensor4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tensor4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor4>& res, const UList<tensor4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, tensor4, f1, +, sphericalTensor4, s2)
	}

	tmp<Field<tensor4>> operator +(const UList<tensor4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator +(const tmp<Field<tensor4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor4>& res, const tensor4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor4, res, =, tensor4, s1, -, sphericalTensor4, f2)
	}

	tmp<Field<tensor4>> operator -(const tensor4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tensor4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, sphericalTensor4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor4>& res, const UList<tensor4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor4, res, =, tensor4, f1, -, sphericalTensor4, s2)
	}

	tmp<Field<tensor4>> operator -(const UList<tensor4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor4>> operator -(const tmp<Field<tensor4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<tensor4>> tRes = reuseTmp<tensor4, tensor4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor4, tensor4>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<tensor4>> transformFieldMask<tensor4>(const Field<diagTensor4>& dtf)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(dtf.size()));
		Field<tensor4>& res = tRes();
		TFOR_ALL_F_OP_F(tensor4, res, =, diagTensor4, dtf)
		return tRes;
	}

	template <>
	tmp<Field<tensor4>> transformFieldMask<tensor4>(const Field<sphericalTensor4>& stf)
	{
		tmp<Field<tensor4>> tRes(new Field<tensor4>(stf.size()));
		Field<tensor4>& res = tRes();
		TFOR_ALL_F_OP_F(tensor4, res, =, sphericalTensor4, stf)
		return tRes;
	} 
	
	void det(Field<scalar>& res, const UList<tensor6>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, tensor6, f)
	}

	tmp<Field<scalar>> det(const UList<tensor6>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		det(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> det(const tmp<Field<tensor6>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, tensor6>::New(tf);
		det(tRes(), tf());
		reuseTmp<scalar, tensor6>::clear(tf);
		return tRes;
	}
	
	void inv(Field<tensor6>& res, const UList<tensor6>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor6, res, =, ::tnbLib::inv, tensor6, f)
	}

	tmp<Field<tensor6>> inv(const UList<tensor6>& f)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor6>> inv(const tmp<Field<tensor6>>& tf)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf);
		inv(tRes(), tf());
		reuseTmp<tensor6, tensor6>::clear(tf);
		return tRes;
	}
	
	void diag(Field<diagTensor6>& res, const UList<tensor6>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor6, res, =, ::tnbLib::diag, tensor6, f)
	}

	tmp<Field<diagTensor6>> diag(const UList<tensor6>& f)
	{
		tmp<Field<diagTensor6>> tRes(new Field<diagTensor6>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor6>> diag(const tmp<Field<tensor6>>& tf)
	{
		tmp<Field<diagTensor6>> tRes = reuseTmp<diagTensor6, tensor6>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor6, tensor6>::clear(tf);
		return tRes;
	}
	
	void negSumDiag(Field<tensor6>& res, const UList<tensor6>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor6, res, =, ::tnbLib::negSumDiag, tensor6, f)
	}

	tmp<Field<tensor6>> negSumDiag(const UList<tensor6>& f)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f.size()));
		negSumDiag(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor6>> negSumDiag(const tmp<Field<tensor6>>& tf)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf);
		negSumDiag(tRes(), tf());
		reuseTmp<tensor6, tensor6>::clear(tf);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const UList<scalar>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, scalar, f1, /, tensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const UList<scalar>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const UList<scalar>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<scalar>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor6, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, scalar, scalar, tensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, scalar, scalar, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const scalar& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, scalar, s1, /, tensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const scalar& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const scalar& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor6>& res, const UList<scalar>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, scalar, f1, /, tensor6, s2)
	}

	tmp<Field<tensor6>> operator /(const UList<scalar>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<scalar>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor6, scalar>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector6>& res, const UList<vector6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector6, res, =, vector6, f1, /, tensor6, f2)
	}

	tmp<Field<vector6>> operator /(const UList<vector6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const UList<vector6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, tensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<vector6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<vector6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmpTmp<vector6, vector6, vector6, tensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector6, vector6, vector6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector6>& res, const vector6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector6, res, =, vector6, s1, /, tensor6, f2)
	}

	tmp<Field<vector6>> operator /(const vector6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const vector6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, tensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector6>& res, const UList<vector6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector6, res, =, vector6, f1, /, tensor6, s2)
	}

	tmp<Field<vector6>> operator /(const UList<vector6>& f1, const tensor6& s2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<vector6>>& tf1, const tensor6& s2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const UList<tensor6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, tensor6, f1, /, tensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const UList<tensor6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const UList<tensor6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<tensor6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<tensor6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, tensor6, tensor6, tensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, tensor6, tensor6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const tensor6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, tensor6, s1, /, tensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const tensor6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tensor6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor6>& res, const UList<tensor6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, tensor6, f1, /, tensor6, s2)
	}

	tmp<Field<tensor6>> operator /(const UList<tensor6>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<tensor6>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const UList<tensor6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, tensor6, f1, /, diagTensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const UList<tensor6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const UList<tensor6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<tensor6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<tensor6>>& tf1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, tensor6, tensor6, diagTensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, tensor6, tensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const tensor6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, tensor6, s1, /, diagTensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const tensor6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tensor6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor6>& res, const UList<tensor6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, tensor6, f1, /, diagTensor6, s2)
	}

	tmp<Field<tensor6>> operator /(const UList<tensor6>& f1, const diagTensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<tensor6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const UList<diagTensor6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, diagTensor6, f1, /, tensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const UList<diagTensor6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const UList<diagTensor6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<diagTensor6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<diagTensor6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, diagTensor6, diagTensor6, tensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, diagTensor6, diagTensor6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const diagTensor6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, diagTensor6, s1, /, tensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const diagTensor6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const diagTensor6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor6>& res, const UList<diagTensor6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, diagTensor6, f1, /, tensor6, s2)
	}

	tmp<Field<tensor6>> operator /(const UList<diagTensor6>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<diagTensor6>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor6, diagTensor6>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const UList<sphericalTensor6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, sphericalTensor6, f1, /, tensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const UList<sphericalTensor6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const UList<sphericalTensor6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<sphericalTensor6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<sphericalTensor6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, sphericalTensor6, sphericalTensor6, tensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, sphericalTensor6, sphericalTensor6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const sphericalTensor6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, sphericalTensor6, s1, /, tensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const sphericalTensor6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const sphericalTensor6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor6>& res, const UList<sphericalTensor6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, sphericalTensor6, f1, /, tensor6, s2)
	}

	tmp<Field<tensor6>> operator /(const UList<sphericalTensor6>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<sphericalTensor6>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const UList<tensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, tensor6, f1, /, sphericalTensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const UList<tensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const UList<tensor6>& f1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<tensor6>>& tf1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<tensor6>>& tf1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, tensor6, tensor6, sphericalTensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, tensor6, tensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor6>& res, const tensor6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, tensor6, s1, /, sphericalTensor6, f2)
	}

	tmp<Field<tensor6>> operator /(const tensor6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tensor6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor6>& res, const UList<tensor6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, tensor6, f1, /, sphericalTensor6, s2)
	}

	tmp<Field<tensor6>> operator /(const UList<tensor6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator /(const tmp<Field<tensor6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const UList<tensor6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, tensor6, f1, +, tensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const UList<tensor6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const UList<tensor6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<tensor6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<tensor6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, tensor6, tensor6, tensor6>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, tensor6, tensor6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const UList<tensor6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, tensor6, f1, -, tensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const UList<tensor6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const UList<tensor6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<tensor6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<tensor6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, tensor6, tensor6, tensor6>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, tensor6, tensor6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const tensor6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, tensor6, s1, +, tensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const tensor6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tensor6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor6>& res, const UList<tensor6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, tensor6, f1, +, tensor6, s2)
	}

	tmp<Field<tensor6>> operator +(const UList<tensor6>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<tensor6>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const tensor6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, tensor6, s1, -, tensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const tensor6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tensor6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor6>& res, const UList<tensor6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, tensor6, f1, -, tensor6, s2)
	}

	tmp<Field<tensor6>> operator -(const UList<tensor6>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<tensor6>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const UList<diagTensor6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, diagTensor6, f1, +, tensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const UList<diagTensor6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const UList<diagTensor6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<diagTensor6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<diagTensor6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, diagTensor6, diagTensor6, tensor6>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, diagTensor6, diagTensor6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const UList<diagTensor6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, diagTensor6, f1, -, tensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const UList<diagTensor6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const UList<diagTensor6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<diagTensor6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor6, diagTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<diagTensor6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, diagTensor6, diagTensor6, tensor6>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, diagTensor6, diagTensor6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const diagTensor6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, diagTensor6, s1, +, tensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const diagTensor6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const diagTensor6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const UList<diagTensor6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, diagTensor6, f1, +, tensor6, s2)
	}

	tmp<Field<tensor6>> operator +(const UList<diagTensor6>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<diagTensor6>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor6, diagTensor6>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const diagTensor6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, diagTensor6, s1, -, tensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const diagTensor6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const diagTensor6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor6>& res, const UList<diagTensor6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, diagTensor6, f1, -, tensor6, s2)
	}

	tmp<Field<tensor6>> operator -(const UList<diagTensor6>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<diagTensor6>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor6, diagTensor6>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const UList<tensor6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, tensor6, f1, +, diagTensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const UList<tensor6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const UList<tensor6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<tensor6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<tensor6>>& tf1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, tensor6, tensor6, diagTensor6>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, tensor6, tensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const UList<tensor6>& f1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, tensor6, f1, -, diagTensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const UList<tensor6>& f1, const UList<diagTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const UList<tensor6>& f1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor6, diagTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<tensor6>>& tf1, const UList<diagTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<tensor6>>& tf1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, tensor6, tensor6, diagTensor6>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, tensor6, tensor6, diagTensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const tensor6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, tensor6, s1, +, diagTensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const tensor6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tensor6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor6>& res, const UList<tensor6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, tensor6, f1, +, diagTensor6, s2)
	}

	tmp<Field<tensor6>> operator +(const UList<tensor6>& f1, const diagTensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<tensor6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const tensor6& s1, const UList<diagTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, tensor6, s1, -, diagTensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const tensor6& s1, const UList<diagTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tensor6& s1, const tmp<Field<diagTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, diagTensor6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor6, diagTensor6>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor6>& res, const UList<tensor6>& f1, const diagTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, tensor6, f1, -, diagTensor6, s2)
	}

	tmp<Field<tensor6>> operator -(const UList<tensor6>& f1, const diagTensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<tensor6>>& tf1, const diagTensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const UList<sphericalTensor6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, sphericalTensor6, f1, +, tensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const UList<sphericalTensor6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const UList<sphericalTensor6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<sphericalTensor6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<sphericalTensor6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, sphericalTensor6, sphericalTensor6, tensor6>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, sphericalTensor6, sphericalTensor6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const UList<sphericalTensor6>& f1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, sphericalTensor6, f1, -, tensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const UList<sphericalTensor6>& f1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const UList<sphericalTensor6>& f1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<sphericalTensor6>>& tf1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<sphericalTensor6>>& tf1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, sphericalTensor6, sphericalTensor6, tensor6>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, sphericalTensor6, sphericalTensor6, tensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const sphericalTensor6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, sphericalTensor6, s1, +, tensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const sphericalTensor6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const sphericalTensor6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor6>& res, const UList<sphericalTensor6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, sphericalTensor6, f1, +, tensor6, s2)
	}

	tmp<Field<tensor6>> operator +(const UList<sphericalTensor6>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<sphericalTensor6>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const sphericalTensor6& s1, const UList<tensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, sphericalTensor6, s1, -, tensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const sphericalTensor6& s1, const UList<tensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const sphericalTensor6& s1, const tmp<Field<tensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor6, tensor6>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor6>& res, const UList<sphericalTensor6>& f1, const tensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, sphericalTensor6, f1, -, tensor6, s2)
	}

	tmp<Field<tensor6>> operator -(const UList<sphericalTensor6>& f1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<sphericalTensor6>>& tf1, const tensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const UList<tensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, tensor6, f1, +, sphericalTensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const UList<tensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const UList<tensor6>& f1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<tensor6>>& tf1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<tensor6>>& tf1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, tensor6, tensor6, sphericalTensor6>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, tensor6, tensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const UList<tensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor6, res, =, tensor6, f1, -, sphericalTensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const UList<tensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const UList<tensor6>& f1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<tensor6>>& tf1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<tensor6>>& tf1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmpTmp<tensor6, tensor6, tensor6, sphericalTensor6>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor6, tensor6, tensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor6>& res, const tensor6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, tensor6, s1, +, sphericalTensor6, f2)
	}

	tmp<Field<tensor6>> operator +(const tensor6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tensor6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor6>& res, const UList<tensor6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, tensor6, f1, +, sphericalTensor6, s2)
	}

	tmp<Field<tensor6>> operator +(const UList<tensor6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator +(const tmp<Field<tensor6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor6>& res, const tensor6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor6, res, =, tensor6, s1, -, sphericalTensor6, f2)
	}

	tmp<Field<tensor6>> operator -(const tensor6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tensor6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, sphericalTensor6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor6>& res, const UList<tensor6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor6, res, =, tensor6, f1, -, sphericalTensor6, s2)
	}

	tmp<Field<tensor6>> operator -(const UList<tensor6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor6>> operator -(const tmp<Field<tensor6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<tensor6>> tRes = reuseTmp<tensor6, tensor6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor6, tensor6>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<tensor6>> transformFieldMask<tensor6>(const Field<diagTensor6>& dtf)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(dtf.size()));
		Field<tensor6>& res = tRes();
		TFOR_ALL_F_OP_F(tensor6, res, =, diagTensor6, dtf)
		return tRes;
	}

	template <>
	tmp<Field<tensor6>> transformFieldMask<tensor6>(const Field<sphericalTensor6>& stf)
	{
		tmp<Field<tensor6>> tRes(new Field<tensor6>(stf.size()));
		Field<tensor6>& res = tRes();
		TFOR_ALL_F_OP_F(tensor6, res, =, sphericalTensor6, stf)
		return tRes;
	} 
	
	void det(Field<scalar>& res, const UList<tensor8>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, tensor8, f)
	}

	tmp<Field<scalar>> det(const UList<tensor8>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		det(tRes(), f);
		return tRes;
	}

	tmp<Field<scalar>> det(const tmp<Field<tensor8>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, tensor8>::New(tf);
		det(tRes(), tf());
		reuseTmp<scalar, tensor8>::clear(tf);
		return tRes;
	}
	
	void inv(Field<tensor8>& res, const UList<tensor8>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor8, res, =, ::tnbLib::inv, tensor8, f)
	}

	tmp<Field<tensor8>> inv(const UList<tensor8>& f)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor8>> inv(const tmp<Field<tensor8>>& tf)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf);
		inv(tRes(), tf());
		reuseTmp<tensor8, tensor8>::clear(tf);
		return tRes;
	}
	
	void diag(Field<diagTensor8>& res, const UList<tensor8>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor8, res, =, ::tnbLib::diag, tensor8, f)
	}

	tmp<Field<diagTensor8>> diag(const UList<tensor8>& f)
	{
		tmp<Field<diagTensor8>> tRes(new Field<diagTensor8>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<diagTensor8>> diag(const tmp<Field<tensor8>>& tf)
	{
		tmp<Field<diagTensor8>> tRes = reuseTmp<diagTensor8, tensor8>::New(tf);
		diag(tRes(), tf());
		reuseTmp<diagTensor8, tensor8>::clear(tf);
		return tRes;
	}
	
	void negSumDiag(Field<tensor8>& res, const UList<tensor8>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor8, res, =, ::tnbLib::negSumDiag, tensor8, f)
	}

	tmp<Field<tensor8>> negSumDiag(const UList<tensor8>& f)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f.size()));
		negSumDiag(tRes(), f);
		return tRes;
	}

	tmp<Field<tensor8>> negSumDiag(const tmp<Field<tensor8>>& tf)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf);
		negSumDiag(tRes(), tf());
		reuseTmp<tensor8, tensor8>::clear(tf);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const UList<scalar>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, scalar, f1, /, tensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const UList<scalar>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const UList<scalar>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<scalar>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor8, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, scalar, scalar, tensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, scalar, scalar, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const scalar& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, scalar, s1, /, tensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const scalar& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const scalar& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const UList<scalar>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, scalar, f1, /, tensor8, s2)
	}

	tmp<Field<tensor8>> operator /(const UList<scalar>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<scalar>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor8, scalar>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector8>& res, const UList<vector8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector8, res, =, vector8, f1, /, tensor8, f2)
	}

	tmp<Field<vector8>> operator /(const UList<vector8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const UList<vector8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, tensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<vector8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<vector8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmpTmp<vector8, vector8, vector8, tensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector8, vector8, vector8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector8>& res, const vector8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector8, res, =, vector8, s1, /, tensor8, f2)
	}

	tmp<Field<vector8>> operator /(const vector8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const vector8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, tensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector8, tensor8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<vector8>& res, const UList<vector8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector8, res, =, vector8, f1, /, tensor8, s2)
	}

	tmp<Field<vector8>> operator /(const UList<vector8>& f1, const tensor8& s2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<vector8>>& tf1, const tensor8& s2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const UList<tensor8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, tensor8, f1, /, tensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const UList<tensor8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const UList<tensor8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<tensor8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<tensor8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, tensor8, tensor8, tensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, tensor8, tensor8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const tensor8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, tensor8, s1, /, tensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const tensor8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tensor8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const UList<tensor8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, tensor8, f1, /, tensor8, s2)
	}

	tmp<Field<tensor8>> operator /(const UList<tensor8>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<tensor8>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const UList<tensor8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, tensor8, f1, /, diagTensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const UList<tensor8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const UList<tensor8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<tensor8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<tensor8>>& tf1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, tensor8, tensor8, diagTensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, tensor8, tensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const tensor8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, tensor8, s1, /, diagTensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const tensor8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tensor8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor8>& res, const UList<tensor8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, tensor8, f1, /, diagTensor8, s2)
	}

	tmp<Field<tensor8>> operator /(const UList<tensor8>& f1, const diagTensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<tensor8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const UList<diagTensor8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, diagTensor8, f1, /, tensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const UList<diagTensor8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const UList<diagTensor8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<diagTensor8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<diagTensor8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, diagTensor8, diagTensor8, tensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, diagTensor8, diagTensor8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const diagTensor8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, diagTensor8, s1, /, tensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const diagTensor8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const diagTensor8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor8>& res, const UList<diagTensor8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, diagTensor8, f1, /, tensor8, s2)
	}

	tmp<Field<tensor8>> operator /(const UList<diagTensor8>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<diagTensor8>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor8, diagTensor8>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const UList<sphericalTensor8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, sphericalTensor8, f1, /, tensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const UList<sphericalTensor8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const UList<sphericalTensor8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<sphericalTensor8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<sphericalTensor8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, sphericalTensor8, sphericalTensor8, tensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, sphericalTensor8, sphericalTensor8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const sphericalTensor8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, sphericalTensor8, s1, /, tensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const sphericalTensor8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const sphericalTensor8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor8>& res, const UList<sphericalTensor8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, sphericalTensor8, f1, /, tensor8, s2)
	}

	tmp<Field<tensor8>> operator /(const UList<sphericalTensor8>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<sphericalTensor8>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const UList<tensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, tensor8, f1, /, sphericalTensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const UList<tensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const UList<tensor8>& f1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<tensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<tensor8>>& tf1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<tensor8>>& tf1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, tensor8, tensor8, sphericalTensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, tensor8, tensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<tensor8>& res, const tensor8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, tensor8, s1, /, sphericalTensor8, f2)
	}

	tmp<Field<tensor8>> operator /(const tensor8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tensor8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<tensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	} 
	
	void divide(Field<tensor8>& res, const UList<tensor8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, tensor8, f1, /, sphericalTensor8, s2)
	}

	tmp<Field<tensor8>> operator /(const UList<tensor8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator /(const tmp<Field<tensor8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const UList<tensor8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, tensor8, f1, +, tensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const UList<tensor8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const UList<tensor8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<tensor8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<tensor8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, tensor8, tensor8, tensor8>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, tensor8, tensor8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const UList<tensor8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, tensor8, f1, -, tensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const UList<tensor8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const UList<tensor8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<tensor8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<tensor8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, tensor8, tensor8, tensor8>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, tensor8, tensor8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const tensor8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, tensor8, s1, +, tensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const tensor8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tensor8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor8>& res, const UList<tensor8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, tensor8, f1, +, tensor8, s2)
	}

	tmp<Field<tensor8>> operator +(const UList<tensor8>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<tensor8>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const tensor8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, tensor8, s1, -, tensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const tensor8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tensor8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor8>& res, const UList<tensor8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, tensor8, f1, -, tensor8, s2)
	}

	tmp<Field<tensor8>> operator -(const UList<tensor8>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<tensor8>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const UList<diagTensor8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, diagTensor8, f1, +, tensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const UList<diagTensor8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const UList<diagTensor8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<diagTensor8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<diagTensor8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, diagTensor8, diagTensor8, tensor8>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, diagTensor8, diagTensor8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const UList<diagTensor8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, diagTensor8, f1, -, tensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const UList<diagTensor8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const UList<diagTensor8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<diagTensor8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor8, diagTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<diagTensor8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, diagTensor8, diagTensor8, tensor8>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, diagTensor8, diagTensor8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const diagTensor8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, diagTensor8, s1, +, tensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const diagTensor8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const diagTensor8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor8>& res, const UList<diagTensor8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, diagTensor8, f1, +, tensor8, s2)
	}

	tmp<Field<tensor8>> operator +(const UList<diagTensor8>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<diagTensor8>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor8, diagTensor8>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const diagTensor8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, diagTensor8, s1, -, tensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const diagTensor8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const diagTensor8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor8>& res, const UList<diagTensor8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, diagTensor8, f1, -, tensor8, s2)
	}

	tmp<Field<tensor8>> operator -(const UList<diagTensor8>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<diagTensor8>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor8, diagTensor8>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const UList<tensor8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, tensor8, f1, +, diagTensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const UList<tensor8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const UList<tensor8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<tensor8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<tensor8>>& tf1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, tensor8, tensor8, diagTensor8>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, tensor8, tensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const UList<tensor8>& f1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, tensor8, f1, -, diagTensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const UList<tensor8>& f1, const UList<diagTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const UList<tensor8>& f1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor8, diagTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<tensor8>>& tf1, const UList<diagTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<tensor8>>& tf1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, tensor8, tensor8, diagTensor8>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, tensor8, tensor8, diagTensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const tensor8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, tensor8, s1, +, diagTensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const tensor8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tensor8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void add(Field<tensor8>& res, const UList<tensor8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, tensor8, f1, +, diagTensor8, s2)
	}

	tmp<Field<tensor8>> operator +(const UList<tensor8>& f1, const diagTensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<tensor8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const tensor8& s1, const UList<diagTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, tensor8, s1, -, diagTensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const tensor8& s1, const UList<diagTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tensor8& s1, const tmp<Field<diagTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, diagTensor8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor8, diagTensor8>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor8>& res, const UList<tensor8>& f1, const diagTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, tensor8, f1, -, diagTensor8, s2)
	}

	tmp<Field<tensor8>> operator -(const UList<tensor8>& f1, const diagTensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<tensor8>>& tf1, const diagTensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const UList<sphericalTensor8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, sphericalTensor8, f1, +, tensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const UList<sphericalTensor8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const UList<sphericalTensor8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<sphericalTensor8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<sphericalTensor8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, sphericalTensor8, sphericalTensor8, tensor8>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, sphericalTensor8, sphericalTensor8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const UList<sphericalTensor8>& f1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, sphericalTensor8, f1, -, tensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const UList<sphericalTensor8>& f1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const UList<sphericalTensor8>& f1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<sphericalTensor8>>& tf1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<sphericalTensor8>>& tf1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, sphericalTensor8, sphericalTensor8, tensor8>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, sphericalTensor8, sphericalTensor8, tensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const sphericalTensor8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, sphericalTensor8, s1, +, tensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const sphericalTensor8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const sphericalTensor8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const UList<sphericalTensor8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, sphericalTensor8, f1, +, tensor8, s2)
	}

	tmp<Field<tensor8>> operator +(const UList<sphericalTensor8>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<sphericalTensor8>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const sphericalTensor8& s1, const UList<tensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, sphericalTensor8, s1, -, tensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const sphericalTensor8& s1, const UList<tensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const sphericalTensor8& s1, const tmp<Field<tensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor8, tensor8>::clear(tf2);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const UList<sphericalTensor8>& f1, const tensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, sphericalTensor8, f1, -, tensor8, s2)
	}

	tmp<Field<tensor8>> operator -(const UList<sphericalTensor8>& f1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<sphericalTensor8>>& tf1, const tensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const UList<tensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, tensor8, f1, +, sphericalTensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const UList<tensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const UList<tensor8>& f1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<tensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<tensor8>>& tf1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<tensor8>>& tf1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, tensor8, tensor8, sphericalTensor8>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, tensor8, tensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const UList<tensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor8, res, =, tensor8, f1, -, sphericalTensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const UList<tensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const UList<tensor8>& f1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<tensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<tensor8>>& tf1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<tensor8>>& tf1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmpTmp<tensor8, tensor8, tensor8, sphericalTensor8>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<tensor8, tensor8, tensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const tensor8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, tensor8, s1, +, sphericalTensor8, f2)
	}

	tmp<Field<tensor8>> operator +(const tensor8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tensor8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<tensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}
	
	void add(Field<tensor8>& res, const UList<tensor8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, tensor8, f1, +, sphericalTensor8, s2)
	}

	tmp<Field<tensor8>> operator +(const UList<tensor8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator +(const tmp<Field<tensor8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<tensor8>& res, const tensor8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor8, res, =, tensor8, s1, -, sphericalTensor8, f2)
	}

	tmp<Field<tensor8>> operator -(const tensor8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tensor8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, sphericalTensor8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<tensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	} 
	
	void subtract(Field<tensor8>& res, const UList<tensor8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor8, res, =, tensor8, f1, -, sphericalTensor8, s2)
	}

	tmp<Field<tensor8>> operator -(const UList<tensor8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor8>> operator -(const tmp<Field<tensor8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<tensor8>> tRes = reuseTmp<tensor8, tensor8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<tensor8, tensor8>::clear(tf1);
		return tRes;
	}

	template <>
	tmp<Field<tensor8>> transformFieldMask<tensor8>(const Field<diagTensor8>& dtf)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(dtf.size()));
		Field<tensor8>& res = tRes();
		TFOR_ALL_F_OP_F(tensor8, res, =, diagTensor8, dtf)
		return tRes;
	}

	template <>
	tmp<Field<tensor8>> transformFieldMask<tensor8>(const Field<sphericalTensor8>& stf)
	{
		tmp<Field<tensor8>> tRes(new Field<tensor8>(stf.size()));
		Field<tensor8>& res = tRes();
		TFOR_ALL_F_OP_F(tensor8, res, =, sphericalTensor8, stf)
		return tRes;
	}

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#undef TensorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //