#include <scalarField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<>
	tmp<scalarField> scalarField::component(const direction) const
	{
		return *this;
	}

	void component(scalarField& sf, const UList<scalar>& f, const direction)
	{
		sf = f;
	}

	template<>
	void scalarField::replace(const direction, const UList<scalar>& sf)
	{
		*this = sf;
	}

	template<>
	void scalarField::replace(const direction, const scalar& s)
	{
		*this = s;
	}


	void stabilise(scalarField& res, const UList<scalar>& sf, const scalar s)
	{
		TFOR_ALL_F_OP_FUNC_S_F
		(
			scalar, res, =, ::tnbLib::stabilise, scalar, s, scalar, sf
		)
	}

	tmp<scalarField> stabilise(const UList<scalar>& sf, const scalar s)
	{
		tmp<scalarField> tRes(new scalarField(sf.size()));
		stabilise(tRes(), sf, s);
		return tRes;
	}

	tmp<scalarField> stabilise(const tmp<scalarField>& tsf, const scalar s)
	{
		tmp<scalarField> tRes = reuseTmp<scalar, scalar>::New(tsf);
		stabilise(tRes(), tsf(), s);
		reuseTmp<scalar, scalar>::clear(tsf);
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	TEMPLATE void add ( Field<scalar>& res, const scalar& s1, const UList<scalar>& f2 ) 
	{ TFOR_ALL_F_OP_S_OP_F(scalar, res, =, scalar, s1, +, scalar, f2) } 
	TEMPLATE tmp<Field<scalar>> operator + ( const scalar& s1, const UList<scalar>& f2 ) 
	{ tmp<Field<scalar>> tRes(new Field<scalar>(f2.size())); add(tRes(), s1, f2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator + ( const scalar& s1, const tmp<Field<scalar>>& tf2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2); add(tRes(), s1, tf2()); reuseTmp<scalar, scalar>::clear(tf2); return tRes; }
	
	TEMPLATE void add ( Field<scalar>& res, const UList<scalar>& f1, const scalar& s2 ) 
	{ TFOR_ALL_F_OP_F_OP_S(scalar, res, =, scalar, f1, +, scalar, s2) } 
	TEMPLATE tmp<Field<scalar>> operator + ( const UList<scalar>& f1, const scalar& s2 ) 
	{ tmp<Field<scalar>> tRes(new Field<scalar>(f1.size())); add(tRes(), f1, s2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator + ( const tmp<Field<scalar>>& tf1, const scalar& s2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1); add(tRes(), tf1(), s2); reuseTmp<scalar, scalar>::clear(tf1); return tRes; }
		
	TEMPLATE void subtract ( Field<scalar>& res, const scalar& s1, const UList<scalar>& f2 ) 
	{ TFOR_ALL_F_OP_S_OP_F(scalar, res, =, scalar, s1, -, scalar, f2) } 
	TEMPLATE tmp<Field<scalar>> operator - ( const scalar& s1, const UList<scalar>& f2 ) 
	{ tmp<Field<scalar>> tRes(new Field<scalar>(f2.size())); subtract(tRes(), s1, f2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator - ( const scalar& s1, const tmp<Field<scalar>>& tf2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2); subtract(tRes(), s1, tf2()); reuseTmp<scalar, scalar>::clear(tf2); return tRes; } 
	
	TEMPLATE void subtract ( Field<scalar>& res, const UList<scalar>& f1, const scalar& s2 ) 
	{ TFOR_ALL_F_OP_F_OP_S(scalar, res, =, scalar, f1, -, scalar, s2) } 
	TEMPLATE tmp<Field<scalar>> operator - ( const UList<scalar>& f1, const scalar& s2 ) 
	{ tmp<Field<scalar>> tRes(new Field<scalar>(f1.size())); subtract(tRes(), f1, s2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator - ( const tmp<Field<scalar>>& tf1, const scalar& s2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1); subtract(tRes(), tf1(), s2); 
		reuseTmp<scalar, scalar>::clear(tf1); return tRes; }

		
	TEMPLATE void multiply ( Field<scalar>& res, const UList<scalar>& f1, const UList<scalar>& f2 ) 
	{ TFOR_ALL_F_OP_F_OP_F(scalar, res, =, scalar, f1, *, scalar, f2) } 
	TEMPLATE tmp<Field<scalar>> operator * ( const UList<scalar>& f1, const UList<scalar>& f2 ) 
	{ tmp<Field<scalar>> tRes(new Field<scalar>(f1.size())); multiply(tRes(), f1, f2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator * ( const UList<scalar>& f1, const tmp<Field<scalar>>& tf2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2); multiply(tRes(), f1, tf2());
		reuseTmp<scalar, scalar>::clear(tf2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator * ( const tmp<Field<scalar>>& tf1, const UList<scalar>& f2 )
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1); multiply(tRes(), tf1(), f2); 
		reuseTmp<scalar, scalar>::clear(tf1); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator * ( const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmpTmp<scalar, scalar, scalar, scalar>::New(tf1, tf2); 
		multiply(tRes(), tf1(), tf2()); reuseTmpTmp<scalar, scalar, scalar, scalar>::clear(tf1, tf2); 
		return tRes; }
		
	TEMPLATE void divide ( Field<scalar>& res, const UList<scalar>& f1, const UList<scalar>& f2 ) 
	{ TFOR_ALL_F_OP_F_OP_F(scalar, res, =, scalar, f1, /, scalar, f2) } 
	TEMPLATE tmp<Field<scalar>> operator / ( const UList<scalar>& f1, const UList<scalar>& f2 ) 
	{ tmp<Field<scalar>> tRes(new Field<scalar>(f1.size())); divide(tRes(), f1, f2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator / ( const UList<scalar>& f1, const tmp<Field<scalar>>& tf2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2); divide(tRes(), f1, tf2());
		reuseTmp<scalar, scalar>::clear(tf2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator / ( const tmp<Field<scalar>>& tf1, const UList<scalar>& f2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1); divide(tRes(), tf1(), f2);
		reuseTmp<scalar, scalar>::clear(tf1); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator / ( const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmpTmp<scalar, scalar, scalar, scalar>::New(tf1, tf2); 
		divide(tRes(), tf1(), tf2()); reuseTmpTmp<scalar, scalar, scalar, scalar>::clear(tf1, tf2); 
		return tRes; }

		
	TEMPLATE void divide ( Field<scalar>& res, const scalar& s1, const UList<scalar>& f2 ) 
	{ TFOR_ALL_F_OP_S_OP_F(scalar, res, =, scalar, s1, /, scalar, f2) } 
	TEMPLATE tmp<Field<scalar>> operator / ( const scalar& s1, const UList<scalar>& f2 )
	{ tmp<Field<scalar>> tRes(new Field<scalar>(f2.size())); divide(tRes(), s1, f2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> operator / ( const scalar& s1, const tmp<Field<scalar>>& tf2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2); 
		divide(tRes(), s1, tf2()); reuseTmp<scalar, scalar>::clear(tf2); return tRes; }

		
	TEMPLATE void pow ( Field<scalar>& res, const UList<scalar>& f1, const UList<scalar>& f2 ) 
	{ TFOR_ALL_F_OP_FUNC_F_F ( scalar, res, =, ::tnbLib::pow, scalar, f1, scalar, f2 ) } 
	TEMPLATE tmp<Field<scalar>> pow ( const UList<scalar>& f1, const UList<scalar>& f2 ) 
	{ tmp<Field<scalar>> tRes(new Field<scalar>(f1.size())); pow(tRes(), f1, f2); return tRes; } 
	TEMPLATE tmp<Field<scalar>> pow ( const UList<scalar>& f1, const tmp<Field<scalar>>& tf2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2); pow(tRes(), f1, tf2()); 
		reuseTmp<scalar, scalar>::clear(tf2); return tRes; }
	TEMPLATE tmp<Field<scalar>> pow ( const tmp<Field<scalar>>& tf1, const UList<scalar>& f2 ) 
	{ tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1); 
		pow(tRes(), tf1(), f2); reuseTmp<scalar, scalar>::clear(tf1); return tRes; } 
	TEMPLATE tmp<Field<scalar>> pow ( const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2 )
	{ tmp<Field<scalar>> tRes = reuseTmpTmp<scalar, scalar, scalar, scalar>::New(tf1, tf2); pow(tRes(), tf1(), tf2()); 
		reuseTmpTmp<scalar, scalar, scalar, scalar>::clear(tf1, tf2); return tRes; }
		
	BINARY_TYPE_FUNCTION(scalar, scalar, scalar, pow)

		BINARY_FUNCTION(scalar, scalar, scalar, atan2)
		BINARY_TYPE_FUNCTION(scalar, scalar, scalar, atan2)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		UNARY_FUNCTION(scalar, scalar, pow3)
		UNARY_FUNCTION(scalar, scalar, pow4)
		UNARY_FUNCTION(scalar, scalar, pow5)
		UNARY_FUNCTION(scalar, scalar, pow6)
		UNARY_FUNCTION(scalar, scalar, sqrt)
		UNARY_FUNCTION(scalar, scalar, sign)
		UNARY_FUNCTION(scalar, scalar, pos)
		UNARY_FUNCTION(scalar, scalar, neg)
		UNARY_FUNCTION(scalar, scalar, exp)
		UNARY_FUNCTION(scalar, scalar, log)
		UNARY_FUNCTION(scalar, scalar, log10)
		UNARY_FUNCTION(scalar, scalar, sin)
		UNARY_FUNCTION(scalar, scalar, cos)
		UNARY_FUNCTION(scalar, scalar, tan)
		UNARY_FUNCTION(scalar, scalar, asin)
		UNARY_FUNCTION(scalar, scalar, acos)
		UNARY_FUNCTION(scalar, scalar, atan)
		UNARY_FUNCTION(scalar, scalar, sinh)
		UNARY_FUNCTION(scalar, scalar, cosh)
		UNARY_FUNCTION(scalar, scalar, tanh)
		UNARY_FUNCTION(scalar, scalar, asinh)
		UNARY_FUNCTION(scalar, scalar, acosh)
		UNARY_FUNCTION(scalar, scalar, atanh)
		UNARY_FUNCTION(scalar, scalar, erf)
		UNARY_FUNCTION(scalar, scalar, erfc)
		UNARY_FUNCTION(scalar, scalar, lgamma)
		UNARY_FUNCTION(scalar, scalar, j0)
		UNARY_FUNCTION(scalar, scalar, j1)
		UNARY_FUNCTION(scalar, scalar, y0)
		UNARY_FUNCTION(scalar, scalar, y1)


#define BesselFunc(func)                                                      \
void func(scalarField& res, const int n, const UList<scalar>& sf)             \
{                                                                             \
    TFOR_ALL_F_OP_FUNC_S_F(scalar, res, =, ::tnbLib::func, int, n, scalar, sf)  \
}                                                                             \
                                                                              \
tmp<scalarField> func(const int n, const UList<scalar>& sf)                   \
{                                                                             \
    tmp<scalarField> tRes(new scalarField(sf.size()));                        \
    func(tRes(), n, sf);                                                      \
    return tRes;                                                              \
}                                                                             \
                                                                              \
tmp<scalarField> func(const int n, const tmp<scalarField>& tsf)               \
{                                                                             \
    tmp<scalarField> tRes = reuseTmp<scalar, scalar>::New(tsf);               \
    func(tRes(), n, tsf());                                                   \
    reuseTmp<scalar, scalar>::clear(tsf);                                     \
    return tRes;                                                              \
}

		BesselFunc(jn)
		BesselFunc(yn)

#undef BesselFunc


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>