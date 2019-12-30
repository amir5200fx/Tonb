#pragma once
#ifndef _scalarField_Header
#define _scalarField_Header

#include <Field.hxx>
#include <scalar.hxx>

#define TEMPLATE
#include <FieldFunctionsM.hxx>

namespace tnbLib
{
	typedef Field<scalar> scalarField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<>
	tmp<scalarField> scalarField::component(const direction) const;

	void component
	(
		scalarField& sf,
		const UList<scalar>& f,
		const direction
	);

	template<>
	void scalarField::replace(const direction, const UList<scalar>& sf);

	template<>
	void scalarField::replace(const direction, const scalar& s);


	void stabilise(scalarField& Res, const UList<scalar>& sf, const scalar s);
	tmp<scalarField> stabilise(const UList<scalar>&, const scalar s);
	tmp<scalarField> stabilise(const tmp<scalarField>&, const scalar s);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void add ( Field<scalar>& f, const scalar& s1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> operator + ( const scalar& s1, const UList<scalar>& f2 );
	tmp<Field<scalar>> operator + ( const scalar& s1, const tmp<Field<scalar>>& tf2 ); 
	void add ( Field<scalar>& f, const UList<scalar>& f1, const scalar& s2 ); 
	tmp<Field<scalar>> operator + ( const UList<scalar>& f1, const scalar& s2 ); 
	tmp<Field<scalar>> operator + ( const tmp<Field<scalar>>& tf1, const scalar& s2 );
		
	void subtract ( Field<scalar>& f, const scalar& s1, const UList<scalar>& f2 );
	tmp<Field<scalar>> operator - ( const scalar& s1, const UList<scalar>& f2 );
	tmp<Field<scalar>> operator - ( const scalar& s1, const tmp<Field<scalar>>& tf2 );
	void subtract ( Field<scalar>& f, const UList<scalar>& f1, const scalar& s2 );
	tmp<Field<scalar>> operator - ( const UList<scalar>& f1, const scalar& s2 );
	tmp<Field<scalar>> operator - ( const tmp<Field<scalar>>& tf1, const scalar& s2 );

		
	void multiply ( Field<scalar>& f, const UList<scalar>& f1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> operator * ( const UList<scalar>& f1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> operator * ( const UList<scalar>& f1, const tmp<Field<scalar>>& tf2 );
	tmp<Field<scalar>> operator * ( const tmp<Field<scalar>>& tf1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> operator * ( const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2 );
		
	 void divide ( Field<scalar>& f, const UList<scalar>& f1, const UList<scalar>& f2 );
	tmp<Field<scalar>> operator / ( const UList<scalar>& f1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> operator / ( const UList<scalar>& f1, const tmp<Field<scalar>>& tf2 ); 
	tmp<Field<scalar>> operator / ( const tmp<Field<scalar>>& tf1, const UList<scalar>& f2 );
	tmp<Field<scalar>> operator / ( const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2 );

		
	 void divide ( Field<scalar>& f, const scalar& s1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> operator / ( const scalar& s1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> operator / ( const scalar& s1, const tmp<Field<scalar>>& tf2 );

		
	 void pow ( Field<scalar>& f, const UList<scalar>& f1, const UList<scalar>& f2 );
	tmp<Field<scalar>> pow ( const UList<scalar>& f1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> pow ( const UList<scalar>& f1, const tmp<Field<scalar>>& tf2 ); 
	tmp<Field<scalar>> pow ( const tmp<Field<scalar>>& tf1, const UList<scalar>& f2 );
	tmp<Field<scalar>> pow ( const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2 );
		
	void pow ( Field<scalar>& f, const scalar& s1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> pow ( const scalar& s1, const UList<scalar>& f2 );  
	tmp<Field<scalar>> pow ( const scalar& s1, const tmp<Field<scalar>>& tf2 );
	void pow ( Field<scalar>& f, const UList<scalar>& f1, const scalar& s2 ); 
	tmp<Field<scalar>> pow ( const UList<scalar>& f1, const scalar& s2 ); 
	tmp<Field<scalar>> pow ( const tmp<Field<scalar>>& tf1, const scalar& s2 );

		
	 
	void atan2 ( Field<scalar>& f, const UList<scalar>& f1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> atan2 ( const UList<scalar>& f1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> atan2 ( const UList<scalar>& f1, const tmp<Field<scalar>>& tf2 );
	tmp<Field<scalar>> atan2 ( const tmp<Field<scalar>>& tf1, const UList<scalar>& f2 );
	tmp<Field<scalar>> atan2 ( const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2 );
		
	 
	void atan2 ( Field<scalar>& f, const scalar& s1, const UList<scalar>& f2 );
	tmp<Field<scalar>> atan2 ( const scalar& s1, const UList<scalar>& f2 ); 
	tmp<Field<scalar>> atan2 ( const scalar& s1, const tmp<Field<scalar>>& tf2 );
	void atan2 ( Field<scalar>& f, const UList<scalar>& f1, const scalar& s2 ); 
	tmp<Field<scalar>> atan2 ( const UList<scalar>& f1, const scalar& s2 );  
	tmp<Field<scalar>> atan2 ( const tmp<Field<scalar>>& tf1, const scalar& s2 );

#define BesselFunc(func)                                            \
void func(scalarField& Res, const int n, const UList<scalar>& sf);  \
tmp<scalarField> func(const int n, const UList<scalar>&);           \
tmp<scalarField> func(const int n, const tmp<scalarField>&);

	void jn(scalarField& Res, const int n, const UList<scalar>& sf);
	tmp<scalarField> jn(const int n, const UList<scalar>&); 
	tmp<scalarField> jn(const int n, const tmp<scalarField>&);
		
	void yn(scalarField& Res, const int n, const UList<scalar>& sf);
	tmp<scalarField> yn(const int n, const UList<scalar>&); 
	tmp<scalarField> yn(const int n, const tmp<scalarField>&);

#undef BesselFunc
}

#include <undefFieldFunctionsM.hxx>

#endif // !1

