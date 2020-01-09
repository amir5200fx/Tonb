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

		
	TEMPLATE void pow3(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pow3, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> pow3(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pow3(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> pow3(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pow3(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void pow4(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pow4, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> pow4(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pow4(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> pow4(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pow4(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void pow5(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pow5, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> pow5(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pow5(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> pow5(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pow5(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void pow6(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pow6, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> pow6(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pow6(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> pow6(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pow6(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void sqrt(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::sqrt, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> sqrt(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		sqrt(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> sqrt(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		sqrt(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void sign(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::sign, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> sign(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		sign(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> sign(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		sign(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void pos(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pos, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> pos(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pos(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> pos(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pos(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void neg(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::neg, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> neg(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		neg(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> neg(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		neg(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void exp(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::exp, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> exp(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		exp(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> exp(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		exp(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void log(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::log, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> log(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		log(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> log(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		log(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void log10(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::log10, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> log10(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		log10(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> log10(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		log10(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void sin(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::sin, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> sin(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		sin(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> sin(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		sin(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void cos(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cos, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> cos(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cos(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> cos(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		cos(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void tan(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tan, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> tan(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		tan(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> tan(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		tan(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void asin(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::asin, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> asin(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		asin(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> asin(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		asin(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void acos(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::acos, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> acos(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		acos(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> acos(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		acos(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void atan(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::atan, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> atan(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		atan(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> atan(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		atan(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void sinh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::sinh, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> sinh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		sinh(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> sinh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		sinh(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void cosh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cosh, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> cosh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cosh(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> cosh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		cosh(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void tanh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tanh, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> tanh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		tanh(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> tanh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		tanh(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void asinh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::asinh, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> asinh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		asinh(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> asinh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		asinh(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void acosh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::acosh, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> acosh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		acosh(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> acosh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		acosh(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void atanh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::atanh, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> atanh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		atanh(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> atanh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		atanh(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void erf(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::erf, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> erf(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		erf(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> erf(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		erf(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void erfc(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::erfc, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> erfc(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		erfc(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> erfc(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		erfc(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void lgamma(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::lgamma, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> lgamma(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		lgamma(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> lgamma(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		lgamma(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void j0(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::j0, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> j0(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		j0(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> j0(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		j0(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void j1(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::j1, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> j1(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		j1(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> j1(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		j1(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void y0(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::y0, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> y0(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		y0(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> y0(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		y0(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}
		
	TEMPLATE void y1(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::y1, scalar, f)
	}

	TEMPLATE tmp<Field<scalar>> y1(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		y1(tRes(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> y1(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		y1(tRes(), tf());
		reuseTmp<scalar, scalar>::clear(tf);
		return tRes;
	}


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

		
	void jn(scalarField& res, const int n, const UList<scalar>& sf)
	{
		TFOR_ALL_F_OP_FUNC_S_F(scalar, res, =, ::tnbLib::jn, int, n, scalar, sf)
	}

	tmp<scalarField> jn(const int n, const UList<scalar>& sf)
	{
		tmp<scalarField> tRes(new scalarField(sf.size()));
		jn(tRes(), n, sf);
		return tRes;
	}

	tmp<scalarField> jn(const int n, const tmp<scalarField>& tsf)
	{
		tmp<scalarField> tRes = reuseTmp<scalar, scalar>::New(tsf);
		jn(tRes(), n, tsf());
		reuseTmp<scalar, scalar>::clear(tsf);
		return tRes;
	}
		
	void yn(scalarField& res, const int n, const UList<scalar>& sf)
	{
		TFOR_ALL_F_OP_FUNC_S_F(scalar, res, =, ::tnbLib::yn, int, n, scalar, sf)
	}

	tmp<scalarField> yn(const int n, const UList<scalar>& sf)
	{
		tmp<scalarField> tRes(new scalarField(sf.size()));
		yn(tRes(), n, sf);
		return tRes;
	}

	tmp<scalarField> yn(const int n, const tmp<scalarField>& tsf)
	{
		tmp<scalarField> tRes = reuseTmp<scalar, scalar>::New(tsf);
		yn(tRes(), n, tsf());
		reuseTmp<scalar, scalar>::clear(tsf);
		return tRes;
	}

#undef BesselFunc


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>