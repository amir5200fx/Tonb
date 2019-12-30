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
	TEMPLATE void inv(Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor2, res, =, ::tnbLib::inv, sphericalTensor2, f)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> inv(const UList<sphericalTensor2>& f)
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f.size())); inv(tRes(), f); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> inv(const tmp<Field<sphericalTensor2>>& tf)
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf); inv(tRes(), tf());
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf); return tRes;
	}
	
	TEMPLATE void diag(Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor2, res, =, ::tnbLib::diag, sphericalTensor2, f)
	}
	TEMPLATE tmp<Field<sphericalTensor2>> diag(const UList<sphericalTensor2>& f)
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f.size())); diag(tRes(), f); return tRes;
	}
	TEMPLATE tmp<Field<sphericalTensor2>> diag(const tmp<Field<sphericalTensor2>>& tf)
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf); diag(tRes(), tf()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf); return tRes;
	}
	
	TEMPLATE void divide ( Field<sphericalTensor2>& res, const UList<scalar>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor2, res, =, scalar, f1, /, sphericalTensor2, f2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const UList<scalar>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); divide(tRes(), f1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const UList<scalar>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); divide(tRes(), f1, tf2()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<scalar>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, scalar>::New(tf1); divide(tRes(), tf1(), f2); 
		reuseTmp<sphericalTensor2, scalar>::clear(tf1); return tRes;
	}
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<scalar>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmpTmp<sphericalTensor2, scalar, scalar, sphericalTensor2>::New(tf1, tf2); 
		divide(tRes(), tf1(), tf2()); 
		reuseTmpTmp<sphericalTensor2, scalar, scalar, sphericalTensor2>::clear(tf1, tf2); 
		return tRes;
	}
	
	TEMPLATE void divide ( Field<sphericalTensor2>& res, const scalar& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor2, res, =, scalar, s1, /, sphericalTensor2, f2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const scalar& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f2.size())); divide(tRes(), s1, f2); return tRes;
	}
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const scalar& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); divide(tRes(), s1, tf2()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	
	TEMPLATE void divide ( Field<sphericalTensor2>& res, const UList<scalar>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor2, res, =, scalar, f1, /, sphericalTensor2, s2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const UList<scalar>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); divide(tRes(), f1, s2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<scalar>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, scalar>::New(tf1); divide(tRes(), tf1(), s2);
		reuseTmp<sphericalTensor2, scalar>::clear(tf1); 
		return tRes;
	}
	
	TEMPLATE void divide ( Field<vector2>& res, const UList<vector2>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(vector2, res, =, vector2, f1, /, sphericalTensor2, f2)
	} 
	TEMPLATE tmp<Field<vector2>> operator / ( const UList<vector2>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size())); divide(tRes(), f1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<vector2>> operator / ( const UList<vector2>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, sphericalTensor2>::New(tf2); divide(tRes(), f1, tf2());
		reuseTmp<vector2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	TEMPLATE tmp<Field<vector2>> operator / ( const tmp<Field<vector2>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1); divide(tRes(), tf1(), f2); 
		reuseTmp<vector2, vector2>::clear(tf1); return tRes;
	}
	TEMPLATE tmp<Field<vector2>> operator / ( const tmp<Field<vector2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<vector2>> tRes = reuseTmpTmp<vector2, vector2, vector2, sphericalTensor2>::New(tf1, tf2); divide(tRes(), tf1(), tf2()); 
		reuseTmpTmp<vector2, vector2, vector2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	TEMPLATE void divide ( Field<vector2>& res, const vector2& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(vector2, res, =, vector2, s1, /, sphericalTensor2, f2)
	} 
	TEMPLATE tmp<Field<vector2>> operator / ( const vector2& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f2.size())); divide(tRes(), s1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<vector2>> operator / ( const vector2& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, sphericalTensor2>::New(tf2); 
		divide(tRes(), s1, tf2()); reuseTmp<vector2, sphericalTensor2>::clear(tf2); 
		return tRes;
	} 
	
	TEMPLATE void divide ( Field<vector2>& res, const UList<vector2>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(vector2, res, =, vector2, f1, /, sphericalTensor2, s2)
	} 
	TEMPLATE tmp<Field<vector2>> operator / ( const UList<vector2>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<vector2>> tRes(new Field<vector2>(f1.size())); divide(tRes(), f1, s2); return tRes;
	} 
	TEMPLATE tmp<Field<vector2>> operator / ( const tmp<Field<vector2>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<vector2>> tRes = reuseTmp<vector2, vector2>::New(tf1); 
		divide(tRes(), tf1(), s2); reuseTmp<vector2, vector2>::clear(tf1); 
		return tRes;
	} 
	
	TEMPLATE void divide ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor2, res, =, sphericalTensor2, f1, /, sphericalTensor2, f2)
	}
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); divide(tRes(), f1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const UList<sphericalTensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2);
		divide(tRes(), f1, tf2()); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); 
		return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<sphericalTensor2>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); 
		divide(tRes(), tf1(), f2); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); 
		return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<sphericalTensor2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::New(tf1, tf2); 
		divide(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::clear(tf1, tf2); 
		return tRes;
	}
	
	TEMPLATE void divide ( Field<sphericalTensor2>& res, const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor2, res, =, sphericalTensor2, s1, /, sphericalTensor2, f2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f2.size())); 
		divide(tRes(), s1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const sphericalTensor2& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); 
		divide(tRes(), s1, tf2()); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); 
		return tRes;
	} 
	TEMPLATE void divide ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor2, res, =, sphericalTensor2, f1, /, sphericalTensor2, s2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); 
		divide(tRes(), f1, s2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator / ( const tmp<Field<sphericalTensor2>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); 
		divide(tRes(), tf1(), s2); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1);
		return tRes;
	} 
	
	TEMPLATE void add ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor2, res, =, sphericalTensor2, f1, +, sphericalTensor2, f2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator + ( const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); add(tRes(), f1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator + ( const UList<sphericalTensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); add(tRes(), f1, tf2()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator + ( const tmp<Field<sphericalTensor2>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); add(tRes(), tf1(), f2); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator + ( const tmp<Field<sphericalTensor2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::New(tf1, tf2); 
		add(tRes(), tf1(), tf2());
		reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::clear(tf1, tf2); return tRes;
	}
	
	TEMPLATE void subtract ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor2, res, =, sphericalTensor2, f1, -, sphericalTensor2, f2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator - ( const UList<sphericalTensor2>& f1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); 
		subtract(tRes(), f1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator - ( const UList<sphericalTensor2>& f1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); subtract(tRes(), f1, tf2()); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator - ( const tmp<Field<sphericalTensor2>>& tf1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); subtract(tRes(), tf1(), f2); 
		reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator - ( const tmp<Field<sphericalTensor2>>& tf1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::New(tf1, tf2); 
		subtract(tRes(), tf1(), tf2()); reuseTmpTmp<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2>::clear(tf1, tf2);
		return tRes;
	} 
	
	TEMPLATE void add ( Field<sphericalTensor2>& res, const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor2, res, =, sphericalTensor2, s1, +, sphericalTensor2, f2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator + ( const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f2.size())); add(tRes(), s1, f2); 
		return tRes;
	}
	TEMPLATE tmp<Field<sphericalTensor2>> operator + ( const sphericalTensor2& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); 
		add(tRes(), s1, tf2()); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); 
		return tRes;
	} 
	
	TEMPLATE void add ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor2, res, =, sphericalTensor2, f1, +, sphericalTensor2, s2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator + ( const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); add(tRes(), f1, s2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator + ( const tmp<Field<sphericalTensor2>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); 
		add(tRes(), tf1(), s2); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); 
		return tRes;
	} 
	
	TEMPLATE void subtract ( Field<sphericalTensor2>& res, const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor2, res, =, sphericalTensor2, s1, -, sphericalTensor2, f2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator - ( const sphericalTensor2& s1, const UList<sphericalTensor2>& f2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f2.size())); 
		subtract(tRes(), s1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator - ( const sphericalTensor2& s1, const tmp<Field<sphericalTensor2>>& tf2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf2); 
		subtract(tRes(), s1, tf2()); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf2); 
		return tRes;
	}
	
	TEMPLATE void subtract ( Field<sphericalTensor2>& res, const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor2, res, =, sphericalTensor2, f1, -, sphericalTensor2, s2)
	} 
	TEMPLATE tmp<Field<sphericalTensor2>> operator - ( const UList<sphericalTensor2>& f1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes(new Field<sphericalTensor2>(f1.size())); 
		subtract(tRes(), f1, s2); return tRes;
	}
	TEMPLATE tmp<Field<sphericalTensor2>> operator - ( const tmp<Field<sphericalTensor2>>& tf1, const sphericalTensor2& s2 )
	{
		tmp<Field<sphericalTensor2>> tRes = reuseTmp<sphericalTensor2, sphericalTensor2>::New(tf1); 
		subtract(tRes(), tf1(), s2); reuseTmp<sphericalTensor2, sphericalTensor2>::clear(tf1); 
		return tRes;
	}
	
	SphericalTensorN_FieldFunctions(tensor3, diagTensor3, sphericalTensor3, vector3, scalar, )
	
	SphericalTensorN_FieldFunctions(tensor4, diagTensor4, sphericalTensor4, vector4, scalar, )
	
	SphericalTensorN_FieldFunctions(tensor6, diagTensor6, sphericalTensor6, vector6, scalar, ) 
	
	SphericalTensorN_FieldFunctions(tensor8, diagTensor8, sphericalTensor8, vector8, scalar, )
}

#include <undefFieldFunctionsM.hxx>