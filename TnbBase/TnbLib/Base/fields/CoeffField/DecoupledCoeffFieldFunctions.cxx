#include <DecoupledCoeffField.hxx>

#include <BlockCoeff.hxx>

/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

template<class Type>
tnbLib::tmp<tnbLib::DecoupledCoeffField<Type> > tnbLib::inv
(
	const DecoupledCoeffField<Type>& f
)
{
	// The inverse of a linear coefficient type is currently done "by
	// hand".  The need for this will disappear once the diagonal tensor
	// type is introduced.  HJ, 24/May/2005

	typedef typename DecoupledCoeffField<Type>::linearTypeField fieldType;
	typedef typename DecoupledCoeffField<Type>::linearType linearType;

	// Create result
	tmp<DecoupledCoeffField<Type> > tresult
	(
		new DecoupledCoeffField<Type>(f.size())
	);
	DecoupledCoeffField<Type>& result = tresult();

	if (f.activeType() == blockCoeffBase::SCALAR)
	{
		result = 1.0 / f.asScalar();
	}
	else if (f.activeType() == blockCoeffBase::LINEAR)
	{
		const fieldType& lf = f.asLinear();

		fieldType inverse =
			cmptDivide
			(
				fieldType(lf.size(), pTraits<linearType>::one),
				lf
			);

		result = inverse;
	}

	return tresult;
}


template<class Type>
void tnbLib::multiply
(
	Field<Type>& f,
	const DecoupledCoeffField<Type>& f1,
	const Type& f2
)
{
	if (f1.activeType() == blockCoeffBase::SCALAR)
	{
		f = f1.asScalar()*f2;
	}
	else if (f1.activeType() == blockCoeffBase::LINEAR)
	{
		f = cmptMultiply(f1.asLinear(), f2);
	}
}


template<class Type>
void tnbLib::multiply
(
	Field<Type>& f,
	const DecoupledCoeffField<Type>& f1,
	const Field<Type>& f2
)
{
	if (f1.activeType() == blockCoeffBase::SCALAR)
	{
		f = f1.asScalar()*f2;
	}
	else if (f1.activeType() == blockCoeffBase::LINEAR)
	{
		f = cmptMultiply(f1.asLinear(), f2);
	}
}


template<class Type>
void tnbLib::multiply
(
	Field<Type>& f,
	const Field<Type>& f1,
	const DecoupledCoeffField<Type>& f2
)
{
	if (f2.activeType() == blockCoeffBase::SCALAR)
	{
		f = f1 * f2.asScalar();
	}
	else if (f2.activeType() == blockCoeffBase::LINEAR)
	{
		f = cmptMultiply(f1, f2.asLinear());
	}
}


/* * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * */

#define UNARY_OPERATOR(op, opFunc)                                            \
                                                                              \
template<class Type>                                                          \
void tnbLib::opFunc                                                             \
(                                                                             \
    DecoupledCoeffField<Type>& f,                                             \
    const DecoupledCoeffField<Type>& f1                                       \
)                                                                             \
{                                                                             \
    typedef DecoupledCoeffField<Type> TypeDecoupledCoeffField;                \
                                                                              \
    typedef typename TypeDecoupledCoeffField::scalarTypeField scalarTypeField;\
    typedef typename TypeDecoupledCoeffField::linearTypeField linearTypeField;\
                                                                              \
    if (f.activeType() == blockCoeffBase::SCALAR)                             \
    {                                                                         \
        scalarTypeField sf = f1.asScalar();                                   \
        sf.opFunc();                                                          \
        f = sf;                                                               \
    }                                                                         \
    else if (f.activeType() == blockCoeffBase::LINEAR)                        \
    {                                                                         \
        linearTypeField sf = f1.asLinear();                                   \
        sf.opFunc();                                                          \
        f = sf;                                                               \
    }                                                                         \
}                                                                             \
                                                                              \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::DecoupledCoeffField<Type> > tnbLib::operator op                 \
(                                                                             \
    const DecoupledCoeffField<Type>& f1                                       \
)                                                                             \
{                                                                             \
    tmp<DecoupledCoeffField<Type> > tf                                        \
    (                                                                         \
        new DecoupledCoeffField<Type>(f1.size())                              \
    );                                                                        \
    opFunc(tf(), f1);                                                         \
    return tf;                                                                \
}                                                                             \
                                                                              \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::DecoupledCoeffField<Type> > tnbLib::operator op                 \
(                                                                             \
    const tmp<DecoupledCoeffField<Type> >& tf1                                \
)                                                                             \
{                                                                             \
    tmp<DecoupledCoeffField<Type> > tf(tf1.ptr());                            \
    opFunc(tf(), tf());                                                       \
    return tf;                                                                \
}

template <class Type>
void tnbLib::negate(DecoupledCoeffField<Type>& f, const DecoupledCoeffField<Type>& f1)
{
	typedef DecoupledCoeffField<Type> TypeDecoupledCoeffField;
	typedef typename TypeDecoupledCoeffField::scalarTypeField scalarTypeField;
	typedef typename TypeDecoupledCoeffField::linearTypeField linearTypeField;
	if (f.activeType() == blockCoeffBase::SCALAR)
	{
		scalarTypeField sf = f1.asScalar();
		sf.negate();
		f = sf;
	}
	else if (f.activeType() == blockCoeffBase::LINEAR)
	{
		linearTypeField sf = f1.asLinear();
		sf.negate();
		f = sf;
	}
}

template <class Type>
tnbLib::tmp<tnbLib::DecoupledCoeffField<Type>> tnbLib::operator -(const DecoupledCoeffField<Type>& f1)
{
	tmp<DecoupledCoeffField<Type>> tf(new DecoupledCoeffField<Type>(f1.size()));
	negate(tf(), f1);
	return tf;
}

template <class Type>
tnbLib::tmp<tnbLib::DecoupledCoeffField<Type>> tnbLib::operator -(const tmp<DecoupledCoeffField<Type>>& tf1)
{
	tmp<DecoupledCoeffField<Type>> tf(tf1.ptr());
	negate(tf(), tf());
	return tf;
}

#undef UNARY_OPERATOR


#define BINARY_OPERATOR_FF(Type1, Type2, op, opFunc)                          \
                                                                              \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::operator op                               \
(                                                                             \
    const DecoupledCoeffField<Type1>& f1,                                     \
    const Type2& f2                                                           \
)                                                                             \
{                                                                             \
    tmp<Field<Type> > tf(new Field<Type>(f1.size()));                         \
    opFunc(tf(), f1, f2);                                                     \
    return tf;                                                                \
}                                                                             \
                                                                              \
                                                                              \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::operator op                               \
(                                                                             \
    const DecoupledCoeffField<Type1>& f1,                                     \
    const Field<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    tmp<Field<Type> > tf(new Field<Type>(f1.size()));                         \
    opFunc(tf(), f1, f2);                                                     \
    return tf;                                                                \
}                                                                             \
                                                                              \
                                                                              \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::operator op                               \
(                                                                             \
    const Field<Type2>& f1,                                                   \
    const DecoupledCoeffField<Type1>& f2                                      \
)                                                                             \
{                                                                             \
    tmp<Field<Type> > tf(new Field<Type>(f1.size()));                         \
    opFunc(tf(), f1, f2);                                                     \
    return tf;                                                                \
}

#define BINARY_OPERATOR_FTR(Type1, Type2, op, opFunc)                         \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::operator op                               \
(                                                                             \
    const DecoupledCoeffField<Type1>& f1,                                     \
    const tmp<Field<Type2> >& tf2                                             \
)                                                                             \
{                                                                             \
    tmp<Field<Type> > tf(tf2.ptr());                                          \
    opFunc(tf(), f1, tf());                                                   \
    return tf;                                                                \
}

#define BINARY_OPERATOR_FT(Type1, Type2, op, opFunc)                          \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::operator op                               \
(                                                                             \
    const Field<Type1>& f1,                                                   \
    const tmp<DecoupledCoeffField<Type2> >& tf2                               \
)                                                                             \
{                                                                             \
    tmp<Field<Type> > tf = f1 op tf2();                                       \
    tf2.clear();                                                              \
    return tf;                                                                \
}

#define BINARY_OPERATOR_TRF(Type1, Type2, op, opFunc)                         \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::operator op                               \
(                                                                             \
    const tmp<DecoupledCoeffField<Type1> >& tf1,                              \
    const Field<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    tmp<Field<Type> > tf(tf1.ptr());                                          \
    opFunc(tf(), tf(), f2);                                                   \
    return tf;                                                                \
}

#define BINARY_OPERATOR_TF(Type1, Type2, op, opFunc)                          \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::operator op                               \
(                                                                             \
    const tmp<DecoupledCoeffField<Type1> >& tf1,                              \
    const Field<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    tmp<Field<Type> > tf = tf1() op f2;                                       \
    tf1.clear();                                                              \
    return tf;                                                                \
}

#define BINARY_OPERATOR_TRT(Type1, Type2, op, opFunc)                         \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::operator op                               \
(                                                                             \
    const tmp<DecoupledCoeffField<Type1> >& tf1,                              \
    const tmp<Field<Type2> >& tf2                                             \
)                                                                             \
{                                                                             \
    tmp<Field<Type> > tf(tf1.ptr());                                          \
    opFunc(tf(), tf(), tf2());                                                \
    tf2.clear();                                                              \
    return tf;                                                                \
}

#define BINARY_OPERATOR_TTR(Type1, Type2, op, opFunc)                         \
template<class Type>                                                          \
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::operator op                               \
(                                                                             \
    const tmp<Field<Type1> >& tf1,                                            \
    const tmp<DecoupledCoeffField<Type2> >& tf2                               \
)                                                                             \
{                                                                             \
    tmp<Field<Type> > tf(tf2.ptr());                                          \
    opFunc(tf(), tf1(), tf());                                                \
    tf1.clear();                                                              \
    return tf;                                                                \
}

#define BINARY_OPERATOR_R(Type1, Type2, op, opFunc)                           \
    BINARY_OPERATOR_FF(Type1, Type2, op, opFunc)                              \
    BINARY_OPERATOR_FTR(Type1, Type2, op, opFunc)                             \
    BINARY_OPERATOR_TRF(Type1, Type2, op, opFunc)                             \
    BINARY_OPERATOR_TRT(Type1, Type2, op, opFunc)

// BINARY_OPERATOR_R(Type, Type, *, multiply)

#undef BINARY_OPERATOR_R
#undef BINARY_OPERATOR_FF
#undef BINARY_OPERATOR_FTR
#undef BINARY_OPERATOR_TF
#undef BINARY_OPERATOR_TTR
#undef BINARY_OPERATOR_FT
#undef BINARY_OPERATOR_TRF
#undef BINARY_OPERATOR_TRT


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //