#include <SphericalTensorNFields.hxx>


#include <transformField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define SphericalTensorN_FieldFunctions(tensorType, diagTensorType,                 \
    sphericalTensorType, vectorType, CmptType, args)                             \
                                                                                    \
UNARY_FUNCTION(sphericalTensorType, sphericalTensorType, inv)                       \
UNARY_FUNCTION(sphericalTensorType, sphericalTensorType, diag)                      \
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
	void inv(Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor2, res, =, ::tnbLib::inv, sphericalTensor2, f)
	} 
	tmp<Field<sphericalTensor2>> inv(const UList<sphericalTensor2>& f)
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f.size())); inv(tRes(), f); return tRes;
	} 
	tmp<Field<sphericalTensor2>> inv(const tmp<Field<sphericalTensor2>>& tf)
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf); inv(tRes(), tf());
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf); return tRes;
	}
	
	void diag(Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor2, res, =, ::tnbLib::diag, sphericalTensor2, f)
	}
	tmp<Field<sphericalTensor2>> diag(const UList<sphericalTensor2>& f)
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f.size())); diag(tRes(), f); return tRes;
	}
	tmp<Field<sphericalTensor2>> diag(const tmp<Field<sphericalTensor2>>& tf)
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf); diag(tRes(), tf()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf); return tRes;
	}
	
	void divide ( Field<sphericalTensor2>& res, const UList<scalar>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor2, res, =, scalar, f1, /, sphericalTensor2, f2)
	} 
	tmp<Field<sphericalTensor2>> operator / ( const UList<scalar>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); divide(tRes(), f1, f2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator / ( const UList<scalar>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); divide(tRes(), f1, tf2()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<scalar>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, scalar>::New(tf1); divide(tRes(), tf1(), f2); 
		reuseTmp<sphericalTensor2, scalar>::clear(tf1); return tRes;
	}
	tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<scalar>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmpTmp<sphericalTensor2, scalar, scalar, sphericalTensor2>::New(tf1, tf2); 
		divide(tRes(), tf1(), tf2()); 
		reuseTmpTmp<sphericalTensor2, scalar, scalar, sphericalTensor2>::clear(tf1, tf2); 
		return tRes;
	}
	
	void divide ( Field<sphericalTensor2>& res, const scalar& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor2, res, =, scalar, s1, /, sphericalTensor2, f2)
	} 
	tmp<Field<sphericalTensor2>> operator / ( const scalar& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f2.size())); divide(tRes(), s1, f2); return tRes;
	}
	tmp<Field<sphericalTensor2>> operator / ( const scalar& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); divide(tRes(), s1, tf2()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	
	void divide ( Field<sphericalTensor2>& res, const UList<scalar>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor2, res, =, scalar, f1, /, sphericalTensor2, s2)
	} 
	tmp<Field<sphericalTensor2>> operator / ( const UList<scalar>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); divide(tRes(), f1, s2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<scalar>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, scalar>::New(tf1); divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor2, scalar>::clear(tf1); 
		return tRes;
	}
	
	void divide ( Field<vector2>& res, const UList<vector2>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(vector2, res, =, vector2, f1, /, sphericalTensor2, f2)
	} 
	tmp<Field<vector2>> operator / ( const UList<vector2>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size())); divide(tRes(), f1, f2); return tRes;
	} 
	tmp<Field<vector2>> operator / ( const UList<vector2>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, sphericalTensor2>::New(tf2); divide(tRes(), f1, tf2());
		reuseTmp<vector2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	tmp<Field<vector2>> operator / ( const tmp<Field<vector2>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1); divide(tRes(), tf1(), f2); 
		reuseTmp<vector2, vector2>::clear(tf1); return tRes;
	}
	tmp<Field<vector2>> operator / ( const tmp<Field<vector2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<vector2>> tRes = reuseTmpTmp<vector2, vector2, vector2, sphericalTensor2>::New(tf1, tf2); divide(tRes(), tf1(), tf2()); 
		reuseTmpTmp<vector2, vector2, vector2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide ( Field<vector2>& res, const vector2& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(vector2, res, =, vector2, s1, /, sphericalTensor2, f2)
	} 
	tmp<Field<vector2>> operator / ( const vector2& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f2.size())); divide(tRes(), s1, f2); return tRes;
	} 
	tmp<Field<vector2>> operator / ( const vector2& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, sphericalTensor2>::New(tf2); 
		divide(tRes(), s1, tf2()); reuseTmp<vector2, sphericalTensor2>::clear(tf2); 
		return tRes;
	} 
	
	void divide ( Field<vector2>& res, const UList<vector2>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(vector2, res, =, vector2, f1, /, sphericalTensor2, s2)
	} 
	tmp<Field<vector2>> operator / ( const UList<vector2>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size())); divide(tRes(), f1, s2); return tRes;
	} 
	tmp<Field<vector2>> operator / ( const tmp<Field<vector2>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1); 
		divide(tRes(), tf1(), s2); reuseTmp<vector2, vector2>::clear(tf1); 
		return tRes;
	} 
	
	void divide ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor2, res, =, sphericalTensor2, f1, /, sphericalTensor2, f2)
	}
	tmp<Field<sphericalTensor2>> operator / ( const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); divide(tRes(), f1, f2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator / ( const UList<sphericalTensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2);
		divide(tRes(), f1, tf2()); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); 
		return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<sphericalTensor2>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); 
		divide(tRes(), tf1(), f2); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); 
		return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<sphericalTensor2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::New(tf1, tf2); 
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::clear(tf1, tf2); 
		return tRes;
	}
	
	void divide ( Field<sphericalTensor2>& res, const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor2, res, =, sphericalTensor2, s1, /, sphericalTensor2, f2)
	} 
	tmp<Field<sphericalTensor2>> operator / ( const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f2.size())); 
		divide(tRes(), s1, f2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator / ( const sphericalTensor2& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); 
		divide(tRes(), s1, tf2()); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); 
		return tRes;
	} 
	void divide ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor2, res, =, sphericalTensor2, f1, /, sphericalTensor2, s2)
	} 
	tmp<Field<sphericalTensor2>> operator / ( const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); 
		divide(tRes(), f1, s2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<sphericalTensor2>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); 
		divide(tRes(), tf1(), s2); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	} 
	
	void add ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor2, res, =, sphericalTensor2, f1, +, sphericalTensor2, f2)
	} 
	tmp<Field<sphericalTensor2>> operator + ( const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); add(tRes(), f1, f2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator + ( const UList<sphericalTensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); add(tRes(), f1, tf2()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator + ( const tmp<Field<sphericalTensor2>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); add(tRes(), tf1(), f2); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator + ( const tmp<Field<sphericalTensor2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::New(tf1, tf2); 
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::clear(tf1, tf2); return tRes;
	}
	
	void subtract ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor2, res, =, sphericalTensor2, f1, -, sphericalTensor2, f2)
	} 
	tmp<Field<sphericalTensor2>> operator - ( const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); 
		subtract(tRes(), f1, f2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator - ( const UList<sphericalTensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); subtract(tRes(), f1, tf2()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator - ( const tmp<Field<sphericalTensor2>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); subtract(tRes(), tf1(), f2); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator - ( const tmp<Field<sphericalTensor2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::New(tf1, tf2); 
		subtract(tRes(), tf1(), tf2()); reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	void add ( Field<sphericalTensor2>& res, const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor2, res, =, sphericalTensor2, s1, +, sphericalTensor2, f2)
	} 
	tmp<Field<sphericalTensor2>> operator + ( const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f2.size())); add(tRes(), s1, f2); 
		return tRes;
	}
	tmp<Field<sphericalTensor2>> operator + ( const sphericalTensor2& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); 
		add(tRes(), s1, tf2()); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); 
		return tRes;
	} 
	
	void add ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor2, res, =, sphericalTensor2, f1, +, sphericalTensor2, s2)
	} 
	tmp<Field<sphericalTensor2>> operator + ( const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); add(tRes(), f1, s2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator + ( const tmp<Field<sphericalTensor2>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); 
		add(tRes(), tf1(), s2); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); 
		return tRes;
	} 
	
	void subtract ( Field<sphericalTensor2>& res, const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor2, res, =, sphericalTensor2, s1, -, sphericalTensor2, f2)
	} 
	tmp<Field<sphericalTensor2>> operator - ( const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f2.size())); 
		subtract(tRes(), s1, f2); return tRes;
	} 
	tmp<Field<sphericalTensor2>> operator - ( const sphericalTensor2& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); 
		subtract(tRes(), s1, tf2()); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); 
		return tRes;
	}
	
	void subtract ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor2, res, =, sphericalTensor2, f1, -, sphericalTensor2, s2)
	} 
	tmp<Field<sphericalTensor2>> operator - ( const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); 
		subtract(tRes(), f1, s2); return tRes;
	}
	tmp<Field<sphericalTensor2>> operator - ( const tmp<Field<sphericalTensor2>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); 
		subtract(tRes(), tf1(), s2); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); 
		return tRes;
	}
	
	void inv(Field<sphericalTensor3>& res, const UList<sphericalTensor3>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor3, res, =, ::tnbLib::inv, sphericalTensor3, f)
	}

	tmp<Field<sphericalTensor3>> inv(const UList<sphericalTensor3>& f)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> inv(const tmp<Field<sphericalTensor3>>& tf)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf);
		inv(tRes(), tf());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf);
		return tRes;
	} 
	
	void diag(Field<sphericalTensor3>& res, const UList<sphericalTensor3>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor3, res, =, ::tnbLib::diag, sphericalTensor3, f)
	}

	tmp<Field<sphericalTensor3>> diag(const UList<sphericalTensor3>& f)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> diag(const tmp<Field<sphericalTensor3>>& tf)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf);
		diag(tRes(), tf());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf);
		return tRes;
	} 
	
	void divide(Field<sphericalTensor3>& res, const UList<scalar>& f1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor3, res, =, scalar, f1, /, sphericalTensor3, f2)
	}

	tmp<Field<sphericalTensor3>> operator /(const UList<scalar>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const UList<scalar>& f1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const tmp<Field<scalar>>& tf1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor3, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const tmp<Field<scalar>>& tf1,
	                                                 const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmpTmp<sphericalTensor3, scalar, scalar, sphericalTensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor3, scalar, scalar, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<sphericalTensor3>& res, const scalar& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor3, res, =, scalar, s1, /, sphericalTensor3, f2)
	}

	tmp<Field<sphericalTensor3>> operator /(const scalar& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const scalar& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor3>& res, const UList<scalar>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor3, res, =, scalar, f1, /, sphericalTensor3, s2)
	}

	tmp<Field<sphericalTensor3>> operator /(const UList<scalar>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const tmp<Field<scalar>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor3, scalar>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector3>& res, const UList<vector3>& f1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector3, res, =, vector3, f1, /, sphericalTensor3, f2)
	}

	tmp<Field<vector3>> operator /(const UList<vector3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const UList<vector3>& f1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, sphericalTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<vector3>>& tf1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<vector3>>& tf1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmpTmp<vector3, vector3, vector3, sphericalTensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector3, vector3, vector3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector3>& res, const vector3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector3, res, =, vector3, s1, /, sphericalTensor3, f2)
	}

	tmp<Field<vector3>> operator /(const vector3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const vector3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, sphericalTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector3, sphericalTensor3>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<vector3>& res, const UList<vector3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector3, res, =, vector3, f1, /, sphericalTensor3, s2)
	}

	tmp<Field<vector3>> operator /(const UList<vector3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<vector3>> tRes(new Field<vector3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector3>> operator /(const tmp<Field<vector3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<vector3>> tRes = reuseTmp<vector3, vector3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector3, vector3>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<sphericalTensor3>& res, const UList<sphericalTensor3>& f1,
	                     const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor3, res, =, sphericalTensor3, f1, /, sphericalTensor3, f2)
	}

	tmp<Field<sphericalTensor3>> operator /(const UList<sphericalTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const UList<sphericalTensor3>& f1,
	                                                 const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const tmp<Field<sphericalTensor3>>& tf1,
	                                                 const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const tmp<Field<sphericalTensor3>>& tf1,
	                                                 const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmpTmp<
			sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor3>& res, const sphericalTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor3, res, =, sphericalTensor3, s1, /, sphericalTensor3, f2)
	}

	tmp<Field<sphericalTensor3>> operator /(const sphericalTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const sphericalTensor3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor3>& res, const UList<sphericalTensor3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor3, res, =, sphericalTensor3, f1, /, sphericalTensor3, s2)
	}

	tmp<Field<sphericalTensor3>> operator /(const UList<sphericalTensor3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator /(const tmp<Field<sphericalTensor3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}
	
	void add(Field<sphericalTensor3>& res, const UList<sphericalTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor3, res, =, sphericalTensor3, f1, +, sphericalTensor3, f2)
	}

	tmp<Field<sphericalTensor3>> operator +(const UList<sphericalTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator +(const UList<sphericalTensor3>& f1,
	                                                 const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator +(const tmp<Field<sphericalTensor3>>& tf1,
	                                                 const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator +(const tmp<Field<sphericalTensor3>>& tf1,
	                                                 const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmpTmp<
			sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<sphericalTensor3>& res, const UList<sphericalTensor3>& f1,
	                       const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor3, res, =, sphericalTensor3, f1, -, sphericalTensor3, f2)
	}

	tmp<Field<sphericalTensor3>> operator -(const UList<sphericalTensor3>& f1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator -(const UList<sphericalTensor3>& f1,
	                                                 const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator -(const tmp<Field<sphericalTensor3>>& tf1,
	                                                 const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator -(const tmp<Field<sphericalTensor3>>& tf1,
	                                                 const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmpTmp<
			sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<sphericalTensor3>& res, const sphericalTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor3, res, =, sphericalTensor3, s1, +, sphericalTensor3, f2)
	}

	tmp<Field<sphericalTensor3>> operator +(const sphericalTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator +(const sphericalTensor3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}
	
	void add(Field<sphericalTensor3>& res, const UList<sphericalTensor3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor3, res, =, sphericalTensor3, f1, +, sphericalTensor3, s2)
	}

	tmp<Field<sphericalTensor3>> operator +(const UList<sphericalTensor3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator +(const tmp<Field<sphericalTensor3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<sphericalTensor3>& res, const sphericalTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor3, res, =, sphericalTensor3, s1, -, sphericalTensor3, f2)
	}

	tmp<Field<sphericalTensor3>> operator -(const sphericalTensor3& s1, const UList<sphericalTensor3>& f2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator -(const sphericalTensor3& s1, const tmp<Field<sphericalTensor3>>& tf2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf2);
		return tRes;
	}
	
	void subtract(Field<sphericalTensor3>& res, const UList<sphericalTensor3>& f1, const sphericalTensor3& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor3, res, =, sphericalTensor3, f1, -, sphericalTensor3, s2)
	}

	tmp<Field<sphericalTensor3>> operator -(const UList<sphericalTensor3>& f1, const sphericalTensor3& s2)
	{
		tmp<Field<sphericalTensor3>> tRes(new Field<sphericalTensor3>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor3>> operator -(const tmp<Field<sphericalTensor3>>& tf1, const sphericalTensor3& s2)
	{
		tmp<Field<sphericalTensor3>> tRes = reuseTmp<sphericalTensor3, sphericalTensor3>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor3, sphericalTensor3>::clear(tf1);
		return tRes;
	}
	
	void inv(Field<sphericalTensor4>& res, const UList<sphericalTensor4>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor4, res, =, ::tnbLib::inv, sphericalTensor4, f)
	}

	tmp<Field<sphericalTensor4>> inv(const UList<sphericalTensor4>& f)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> inv(const tmp<Field<sphericalTensor4>>& tf)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf);
		inv(tRes(), tf());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf);
		return tRes;
	}
	
	void diag(Field<sphericalTensor4>& res, const UList<sphericalTensor4>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor4, res, =, ::tnbLib::diag, sphericalTensor4, f)
	}

	tmp<Field<sphericalTensor4>> diag(const UList<sphericalTensor4>& f)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> diag(const tmp<Field<sphericalTensor4>>& tf)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf);
		diag(tRes(), tf());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf);
		return tRes;
	}
	
	void divide(Field<sphericalTensor4>& res, const UList<scalar>& f1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor4, res, =, scalar, f1, /, sphericalTensor4, f2)
	}

	tmp<Field<sphericalTensor4>> operator /(const UList<scalar>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const UList<scalar>& f1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const tmp<Field<scalar>>& tf1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor4, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const tmp<Field<scalar>>& tf1,
	                                                 const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmpTmp<sphericalTensor4, scalar, scalar, sphericalTensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor4, scalar, scalar, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor4>& res, const scalar& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor4, res, =, scalar, s1, /, sphericalTensor4, f2)
	}

	tmp<Field<sphericalTensor4>> operator /(const scalar& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const scalar& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor4>& res, const UList<scalar>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor4, res, =, scalar, f1, /, sphericalTensor4, s2)
	}

	tmp<Field<sphericalTensor4>> operator /(const UList<scalar>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const tmp<Field<scalar>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor4, scalar>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<vector4>& res, const UList<vector4>& f1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector4, res, =, vector4, f1, /, sphericalTensor4, f2)
	}

	tmp<Field<vector4>> operator /(const UList<vector4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const UList<vector4>& f1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, sphericalTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<vector4>>& tf1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<vector4>>& tf1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmpTmp<vector4, vector4, vector4, sphericalTensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector4, vector4, vector4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector4>& res, const vector4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector4, res, =, vector4, s1, /, sphericalTensor4, f2)
	}

	tmp<Field<vector4>> operator /(const vector4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const vector4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, sphericalTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector4, sphericalTensor4>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<vector4>& res, const UList<vector4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector4, res, =, vector4, f1, /, sphericalTensor4, s2)
	}

	tmp<Field<vector4>> operator /(const UList<vector4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<vector4>> tRes(new Field<vector4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector4>> operator /(const tmp<Field<vector4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<vector4>> tRes = reuseTmp<vector4, vector4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector4, vector4>::clear(tf1);
		return tRes;
	}
	
	void divide(Field<sphericalTensor4>& res, const UList<sphericalTensor4>& f1,
	                     const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor4, res, =, sphericalTensor4, f1, /, sphericalTensor4, f2)
	}

	tmp<Field<sphericalTensor4>> operator /(const UList<sphericalTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const UList<sphericalTensor4>& f1,
	                                                 const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const tmp<Field<sphericalTensor4>>& tf1,
	                                                 const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const tmp<Field<sphericalTensor4>>& tf1,
	                                                 const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmpTmp<
			sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor4>& res, const sphericalTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor4, res, =, sphericalTensor4, s1, /, sphericalTensor4, f2)
	}

	tmp<Field<sphericalTensor4>> operator /(const sphericalTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const sphericalTensor4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor4>& res, const UList<sphericalTensor4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor4, res, =, sphericalTensor4, f1, /, sphericalTensor4, s2)
	}

	tmp<Field<sphericalTensor4>> operator /(const UList<sphericalTensor4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator /(const tmp<Field<sphericalTensor4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}
	
	void add(Field<sphericalTensor4>& res, const UList<sphericalTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor4, res, =, sphericalTensor4, f1, +, sphericalTensor4, f2)
	}

	tmp<Field<sphericalTensor4>> operator +(const UList<sphericalTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator +(const UList<sphericalTensor4>& f1,
	                                                 const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator +(const tmp<Field<sphericalTensor4>>& tf1,
	                                                 const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator +(const tmp<Field<sphericalTensor4>>& tf1,
	                                                 const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmpTmp<
			sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void subtract(Field<sphericalTensor4>& res, const UList<sphericalTensor4>& f1,
	                       const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor4, res, =, sphericalTensor4, f1, -, sphericalTensor4, f2)
	}

	tmp<Field<sphericalTensor4>> operator -(const UList<sphericalTensor4>& f1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator -(const UList<sphericalTensor4>& f1,
	                                                 const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator -(const tmp<Field<sphericalTensor4>>& tf1,
	                                                 const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator -(const tmp<Field<sphericalTensor4>>& tf1,
	                                                 const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmpTmp<
			sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4>::clear(tf1, tf2);
		return tRes;
	}
	
	void add(Field<sphericalTensor4>& res, const sphericalTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor4, res, =, sphericalTensor4, s1, +, sphericalTensor4, f2)
	}

	tmp<Field<sphericalTensor4>> operator +(const sphericalTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator +(const sphericalTensor4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}
	
	void add(Field<sphericalTensor4>& res, const UList<sphericalTensor4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor4, res, =, sphericalTensor4, f1, +, sphericalTensor4, s2)
	}

	tmp<Field<sphericalTensor4>> operator +(const UList<sphericalTensor4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator +(const tmp<Field<sphericalTensor4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}
	
	void subtract(Field<sphericalTensor4>& res, const sphericalTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor4, res, =, sphericalTensor4, s1, -, sphericalTensor4, f2)
	}

	tmp<Field<sphericalTensor4>> operator -(const sphericalTensor4& s1, const UList<sphericalTensor4>& f2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator -(const sphericalTensor4& s1, const tmp<Field<sphericalTensor4>>& tf2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf2);
		return tRes;
	}
	
	void subtract(Field<sphericalTensor4>& res, const UList<sphericalTensor4>& f1, const sphericalTensor4& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor4, res, =, sphericalTensor4, f1, -, sphericalTensor4, s2)
	}

	tmp<Field<sphericalTensor4>> operator -(const UList<sphericalTensor4>& f1, const sphericalTensor4& s2)
	{
		tmp<Field<sphericalTensor4>> tRes(new Field<sphericalTensor4>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor4>> operator -(const tmp<Field<sphericalTensor4>>& tf1, const sphericalTensor4& s2)
	{
		tmp<Field<sphericalTensor4>> tRes = reuseTmp<sphericalTensor4, sphericalTensor4>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor4, sphericalTensor4>::clear(tf1);
		return tRes;
	}
	
	void inv(Field<sphericalTensor6>& res, const UList<sphericalTensor6>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor6, res, =, ::tnbLib::inv, sphericalTensor6, f)
	}

	tmp<Field<sphericalTensor6>> inv(const UList<sphericalTensor6>& f)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> inv(const tmp<Field<sphericalTensor6>>& tf)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf);
		inv(tRes(), tf());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf);
		return tRes;
	} 
	
	void diag(Field<sphericalTensor6>& res, const UList<sphericalTensor6>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor6, res, =, ::tnbLib::diag, sphericalTensor6, f)
	}

	tmp<Field<sphericalTensor6>> diag(const UList<sphericalTensor6>& f)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> diag(const tmp<Field<sphericalTensor6>>& tf)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf);
		diag(tRes(), tf());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf);
		return tRes;
	} 
	
	void divide(Field<sphericalTensor6>& res, const UList<scalar>& f1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor6, res, =, scalar, f1, /, sphericalTensor6, f2)
	}

	tmp<Field<sphericalTensor6>> operator /(const UList<scalar>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const UList<scalar>& f1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const tmp<Field<scalar>>& tf1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor6, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const tmp<Field<scalar>>& tf1,
	                                                 const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmpTmp<sphericalTensor6, scalar, scalar, sphericalTensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor6, scalar, scalar, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<sphericalTensor6>& res, const scalar& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor6, res, =, scalar, s1, /, sphericalTensor6, f2)
	}

	tmp<Field<sphericalTensor6>> operator /(const scalar& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const scalar& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor6>& res, const UList<scalar>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor6, res, =, scalar, f1, /, sphericalTensor6, s2)
	}

	tmp<Field<sphericalTensor6>> operator /(const UList<scalar>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const tmp<Field<scalar>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor6, scalar>::clear(tf1);
		return tRes;
	} 
	
	void divide(Field<vector6>& res, const UList<vector6>& f1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector6, res, =, vector6, f1, /, sphericalTensor6, f2)
	}

	tmp<Field<vector6>> operator /(const UList<vector6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const UList<vector6>& f1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, sphericalTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<vector6>>& tf1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<vector6>>& tf1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmpTmp<vector6, vector6, vector6, sphericalTensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector6, vector6, vector6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<vector6>& res, const vector6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector6, res, =, vector6, s1, /, sphericalTensor6, f2)
	}

	tmp<Field<vector6>> operator /(const vector6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const vector6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, sphericalTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector6, sphericalTensor6>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<vector6>& res, const UList<vector6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector6, res, =, vector6, f1, /, sphericalTensor6, s2)
	}

	tmp<Field<vector6>> operator /(const UList<vector6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<vector6>> tRes(new Field<vector6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector6>> operator /(const tmp<Field<vector6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<vector6>> tRes = reuseTmp<vector6, vector6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector6, vector6>::clear(tf1);
		return tRes;
	} 
	
	void divide(Field<sphericalTensor6>& res, const UList<sphericalTensor6>& f1,
	                     const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor6, res, =, sphericalTensor6, f1, /, sphericalTensor6, f2)
	}

	tmp<Field<sphericalTensor6>> operator /(const UList<sphericalTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const UList<sphericalTensor6>& f1,
	                                                 const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const tmp<Field<sphericalTensor6>>& tf1,
	                                                 const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const tmp<Field<sphericalTensor6>>& tf1,
	                                                 const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmpTmp<
			sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<sphericalTensor6>& res, const sphericalTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor6, res, =, sphericalTensor6, s1, /, sphericalTensor6, f2)
	}

	tmp<Field<sphericalTensor6>> operator /(const sphericalTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const sphericalTensor6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor6>& res, const UList<sphericalTensor6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor6, res, =, sphericalTensor6, f1, /, sphericalTensor6, s2)
	}

	tmp<Field<sphericalTensor6>> operator /(const UList<sphericalTensor6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator /(const tmp<Field<sphericalTensor6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	} 
	
	void add(Field<sphericalTensor6>& res, const UList<sphericalTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor6, res, =, sphericalTensor6, f1, +, sphericalTensor6, f2)
	}

	tmp<Field<sphericalTensor6>> operator +(const UList<sphericalTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator +(const UList<sphericalTensor6>& f1,
	                                                 const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator +(const tmp<Field<sphericalTensor6>>& tf1,
	                                                 const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator +(const tmp<Field<sphericalTensor6>>& tf1,
	                                                 const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmpTmp<
			sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	} 
	
	void subtract(Field<sphericalTensor6>& res, const UList<sphericalTensor6>& f1,
	                       const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor6, res, =, sphericalTensor6, f1, -, sphericalTensor6, f2)
	}

	tmp<Field<sphericalTensor6>> operator -(const UList<sphericalTensor6>& f1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator -(const UList<sphericalTensor6>& f1,
	                                                 const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator -(const tmp<Field<sphericalTensor6>>& tf1,
	                                                 const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator -(const tmp<Field<sphericalTensor6>>& tf1,
	                                                 const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmpTmp<
			sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6>::clear(tf1, tf2);
		return tRes;
	} 
	
	void add(Field<sphericalTensor6>& res, const sphericalTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor6, res, =, sphericalTensor6, s1, +, sphericalTensor6, f2)
	}

	tmp<Field<sphericalTensor6>> operator +(const sphericalTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator +(const sphericalTensor6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}
	
	void add(Field<sphericalTensor6>& res, const UList<sphericalTensor6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor6, res, =, sphericalTensor6, f1, +, sphericalTensor6, s2)
	}

	tmp<Field<sphericalTensor6>> operator +(const UList<sphericalTensor6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator +(const tmp<Field<sphericalTensor6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	} 
	
	void subtract(Field<sphericalTensor6>& res, const sphericalTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor6, res, =, sphericalTensor6, s1, -, sphericalTensor6, f2)
	}

	tmp<Field<sphericalTensor6>> operator -(const sphericalTensor6& s1, const UList<sphericalTensor6>& f2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator -(const sphericalTensor6& s1, const tmp<Field<sphericalTensor6>>& tf2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf2);
		return tRes;
	}
	
	void subtract(Field<sphericalTensor6>& res, const UList<sphericalTensor6>& f1, const sphericalTensor6& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor6, res, =, sphericalTensor6, f1, -, sphericalTensor6, s2)
	}

	tmp<Field<sphericalTensor6>> operator -(const UList<sphericalTensor6>& f1, const sphericalTensor6& s2)
	{
		tmp<Field<sphericalTensor6>> tRes(new Field<sphericalTensor6>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor6>> operator -(const tmp<Field<sphericalTensor6>>& tf1, const sphericalTensor6& s2)
	{
		tmp<Field<sphericalTensor6>> tRes = reuseTmp<sphericalTensor6, sphericalTensor6>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor6, sphericalTensor6>::clear(tf1);
		return tRes;
	} 
	
	void inv(Field<sphericalTensor8>& res, const UList<sphericalTensor8>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor8, res, =, ::tnbLib::inv, sphericalTensor8, f)
	}

	tmp<Field<sphericalTensor8>> inv(const UList<sphericalTensor8>& f)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f.size()));
		inv(tRes(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> inv(const tmp<Field<sphericalTensor8>>& tf)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf);
		inv(tRes(), tf());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf);
		return tRes;
	} 
	
	void diag(Field<sphericalTensor8>& res, const UList<sphericalTensor8>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor8, res, =, ::tnbLib::diag, sphericalTensor8, f)
	}

	tmp<Field<sphericalTensor8>> diag(const UList<sphericalTensor8>& f)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f.size()));
		diag(tRes(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> diag(const tmp<Field<sphericalTensor8>>& tf)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf);
		diag(tRes(), tf());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf);
		return tRes;
	} 
	
	void divide(Field<sphericalTensor8>& res, const UList<scalar>& f1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor8, res, =, scalar, f1, /, sphericalTensor8, f2)
	}

	tmp<Field<sphericalTensor8>> operator /(const UList<scalar>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const UList<scalar>& f1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const tmp<Field<scalar>>& tf1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, scalar>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor8, scalar>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const tmp<Field<scalar>>& tf1,
	                                                 const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmpTmp<sphericalTensor8, scalar, scalar, sphericalTensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor8, scalar, scalar, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	} 
	
	void divide(Field<sphericalTensor8>& res, const scalar& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor8, res, =, scalar, s1, /, sphericalTensor8, f2)
	}

	tmp<Field<sphericalTensor8>> operator /(const scalar& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const scalar& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor8>& res, const UList<scalar>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor8, res, =, scalar, f1, /, sphericalTensor8, s2)
	}

	tmp<Field<sphericalTensor8>> operator /(const UList<scalar>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const tmp<Field<scalar>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, scalar>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor8, scalar>::clear(tf1);
		return tRes;
	} 
	
	void divide(Field<vector8>& res, const UList<vector8>& f1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector8, res, =, vector8, f1, /, sphericalTensor8, f2)
	}

	tmp<Field<vector8>> operator /(const UList<vector8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const UList<vector8>& f1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, sphericalTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<vector8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<vector8>>& tf1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<vector8>>& tf1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmpTmp<vector8, vector8, vector8, sphericalTensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<vector8, vector8, vector8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<vector8>& res, const vector8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector8, res, =, vector8, s1, /, sphericalTensor8, f2)
	}

	tmp<Field<vector8>> operator /(const vector8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const vector8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, sphericalTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<vector8, sphericalTensor8>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<vector8>& res, const UList<vector8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector8, res, =, vector8, f1, /, sphericalTensor8, s2)
	}

	tmp<Field<vector8>> operator /(const UList<vector8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<vector8>> tRes(new Field<vector8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<vector8>> operator /(const tmp<Field<vector8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<vector8>> tRes = reuseTmp<vector8, vector8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<vector8, vector8>::clear(tf1);
		return tRes;
	} 
	
	void divide(Field<sphericalTensor8>& res, const UList<sphericalTensor8>& f1,
	                     const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor8, res, =, sphericalTensor8, f1, /, sphericalTensor8, f2)
	}

	tmp<Field<sphericalTensor8>> operator /(const UList<sphericalTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f1.size()));
		divide(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const UList<sphericalTensor8>& f1,
	                                                 const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf2);
		divide(tRes(), f1, tf2());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const tmp<Field<sphericalTensor8>>& tf1,
	                                                 const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf1);
		divide(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const tmp<Field<sphericalTensor8>>& tf1,
	                                                 const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmpTmp<
			sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::New(tf1, tf2);
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor8>& res, const sphericalTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor8, res, =, sphericalTensor8, s1, /, sphericalTensor8, f2)
	}

	tmp<Field<sphericalTensor8>> operator /(const sphericalTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f2.size()));
		divide(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const sphericalTensor8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf2);
		divide(tRes(), s1, tf2());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}
	
	void divide(Field<sphericalTensor8>& res, const UList<sphericalTensor8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor8, res, =, sphericalTensor8, f1, /, sphericalTensor8, s2)
	}

	tmp<Field<sphericalTensor8>> operator /(const UList<sphericalTensor8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f1.size()));
		divide(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator /(const tmp<Field<sphericalTensor8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf1);
		divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}
	
	void add(Field<sphericalTensor8>& res, const UList<sphericalTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor8, res, =, sphericalTensor8, f1, +, sphericalTensor8, f2)
	}

	tmp<Field<sphericalTensor8>> operator +(const UList<sphericalTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f1.size()));
		add(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator +(const UList<sphericalTensor8>& f1,
	                                                 const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf2);
		add(tRes(), f1, tf2());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator +(const tmp<Field<sphericalTensor8>>& tf1,
	                                                 const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf1);
		add(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator +(const tmp<Field<sphericalTensor8>>& tf1,
	                                                 const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmpTmp<
			sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::New(tf1, tf2);
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	} 
	
	void subtract(Field<sphericalTensor8>& res, const UList<sphericalTensor8>& f1,
	                       const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor8, res, =, sphericalTensor8, f1, -, sphericalTensor8, f2)
	}

	tmp<Field<sphericalTensor8>> operator -(const UList<sphericalTensor8>& f1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f1.size()));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator -(const UList<sphericalTensor8>& f1,
	                                                 const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf2);
		subtract(tRes(), f1, tf2());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator -(const tmp<Field<sphericalTensor8>>& tf1,
	                                                 const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf1);
		subtract(tRes(), tf1(), f2);
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator -(const tmp<Field<sphericalTensor8>>& tf1,
	                                                 const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmpTmp<
			sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::New(tf1, tf2);
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8>::clear(tf1, tf2);
		return tRes;
	} 
	
	void add(Field<sphericalTensor8>& res, const sphericalTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor8, res, =, sphericalTensor8, s1, +, sphericalTensor8, f2)
	}

	tmp<Field<sphericalTensor8>> operator +(const sphericalTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f2.size()));
		add(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator +(const sphericalTensor8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf2);
		add(tRes(), s1, tf2());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}
	
	void add(Field<sphericalTensor8>& res, const UList<sphericalTensor8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor8, res, =, sphericalTensor8, f1, +, sphericalTensor8, s2)
	}

	tmp<Field<sphericalTensor8>> operator +(const UList<sphericalTensor8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f1.size()));
		add(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator +(const tmp<Field<sphericalTensor8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf1);
		add(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	} 
	
	void subtract(Field<sphericalTensor8>& res, const sphericalTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor8, res, =, sphericalTensor8, s1, -, sphericalTensor8, f2)
	}

	tmp<Field<sphericalTensor8>> operator -(const sphericalTensor8& s1, const UList<sphericalTensor8>& f2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f2.size()));
		subtract(tRes(), s1, f2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator -(const sphericalTensor8& s1, const tmp<Field<sphericalTensor8>>& tf2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf2);
		subtract(tRes(), s1, tf2());
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf2);
		return tRes;
	}
	
	void subtract(Field<sphericalTensor8>& res, const UList<sphericalTensor8>& f1, const sphericalTensor8& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor8, res, =, sphericalTensor8, f1, -, sphericalTensor8, s2)
	}

	tmp<Field<sphericalTensor8>> operator -(const UList<sphericalTensor8>& f1, const sphericalTensor8& s2)
	{
		tmp<Field<sphericalTensor8>> tRes(new Field<sphericalTensor8>(f1.size()));
		subtract(tRes(), f1, s2);
		return tRes;
	}

	tmp<Field<sphericalTensor8>> operator -(const tmp<Field<sphericalTensor8>>& tf1, const sphericalTensor8& s2)
	{
		tmp<Field<sphericalTensor8>> tRes = reuseTmp<sphericalTensor8, sphericalTensor8>::New(tf1);
		subtract(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor8, sphericalTensor8>::clear(tf1);
		return tRes;
	}
}

#include <undefFieldFunctionsM.hxx>