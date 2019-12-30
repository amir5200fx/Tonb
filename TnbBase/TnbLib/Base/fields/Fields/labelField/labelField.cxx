#include <labelField.hxx>

#define TEMPLATE
#include <FieldFunctions.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	TEMPLATE void add ( Field<label>& res, const label& s1, const UList<label>& f2 )
	{ TFOR_ALL_F_OP_S_OP_F(label, res, =, label, s1, +, label, f2) }
	TEMPLATE tmp<Field<label>> operator + ( const label& s1, const UList<label>& f2 )
	{ tmp<Field<label>> tRes(new Field<label>(f2.size())); add(tRes(), s1, f2); return tRes; }
	TEMPLATE tmp<Field<label>> operator + ( const label& s1, const tmp<Field<label>>& tf2 ) 
	{ tmp<Field<label>> tRes = reuseTmp<label, label>::New(tf2); 
		add(tRes(), s1, tf2()); reuseTmp<label, label>::clear(tf2); return tRes; }

	TEMPLATE void add ( Field<label>& res, const UList<label>& f1, const label& s2 ) 
	{ TFOR_ALL_F_OP_F_OP_S(label, res, =, label, f1, +, label, s2) } 
	TEMPLATE tmp<Field<label>> operator + ( const UList<label>& f1, const label& s2 ) 
	{ tmp<Field<label>> tRes(new Field<label>(f1.size())); add(tRes(), f1, s2); return tRes; } 
	TEMPLATE tmp<Field<label>> operator + ( const tmp<Field<label>>& tf1, const label& s2 )
	{ tmp<Field<label>> tRes = reuseTmp<label, label>::New(tf1); add(tRes(), tf1(), s2); 
		reuseTmp<label, label>::clear(tf1); return tRes; }

		
	TEMPLATE void subtract ( Field<label>& res, const label& s1, const UList<label>& f2 ) 
	{ TFOR_ALL_F_OP_S_OP_F(label, res, =, label, s1, -, label, f2) } 
	TEMPLATE tmp<Field<label>> operator - ( const label& s1, const UList<label>& f2 ) 
	{ tmp<Field<label>> tRes(new Field<label>(f2.size())); subtract(tRes(), s1, f2); return tRes; }
	TEMPLATE tmp<Field<label>> operator - ( const label& s1, const tmp<Field<label>>& tf2 ) 
	{ tmp<Field<label>> tRes = reuseTmp<label, label>::New(tf2); subtract(tRes(), s1, tf2()); 
		reuseTmp<label, label>::clear(tf2); return tRes; }

	TEMPLATE void subtract ( Field<label>& res, const UList<label>& f1, const label& s2 ) 
	{ TFOR_ALL_F_OP_F_OP_S(label, res, =, label, f1, -, label, s2) }
	TEMPLATE tmp<Field<label>> operator - ( const UList<label>& f1, const label& s2 )
	{ tmp<Field<label>> tRes(new Field<label>(f1.size())); subtract(tRes(), f1, s2); return tRes; }
	TEMPLATE tmp<Field<label>> operator - ( const tmp<Field<label>>& tf1, const label& s2 )
	{ tmp<Field<label>> tRes = reuseTmp<label, label>::New(tf1); subtract(tRes(), tf1(), s2);
		reuseTmp<label, label>::clear(tf1); return tRes; }


		template<>
	tmp<labelField> labelField::component(const direction) const
	{
		return *this;
	}

	template<>
	void component
	(
		labelField& lf,
		const UList<label>& f,
		const direction
	)
	{
		lf = f;
	}

	template<>
	void labelField::replace(const direction, const UList<label>& lf)
	{
		*this = lf;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>