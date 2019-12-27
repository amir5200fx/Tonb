#include <FieldM.hxx>
#include <FieldReuseFunctions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define UNARY_FUNCTION(ReturnType, Type, Func)                                \
                                                                              \
TEMPLATE                                                                      \
void Func(Field<ReturnType>& res, const UList<Type>& f)                       \
{                                                                             \
    TFOR_ALL_F_OP_FUNC_F(ReturnType, res, =, ::Foam::Func, Type, f)           \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func(const UList<Type>& f)                            \
{                                                                             \
    tmp<Field<ReturnType> > tRes(new Field<ReturnType>(f.size()));            \
    Func(tRes(), f);                                                          \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func(const tmp<Field<Type> >& tf)                     \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type>::New(tf);       \
    Func(tRes(), tf());                                                       \
    reuseTmp<ReturnType, Type>::clear(tf);                                    \
    return tRes;                                                              \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define UNARY_OPERATOR(ReturnType, Type, Op, OpFunc)                          \
                                                                              \
TEMPLATE                                                                      \
void OpFunc(Field<ReturnType>& res, const UList<Type>& f)                     \
{                                                                             \
    TFOR_ALL_F_OP_OP_F(ReturnType, res, =, Op, Type, f)                       \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op(const UList<Type>& f)                     \
{                                                                             \
    tmp<Field<ReturnType> > tRes(new Field<ReturnType>(f.size()));            \
    OpFunc(tRes(), f);                                                        \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op(const tmp<Field<Type> >& tf)              \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type>::New(tf);       \
    OpFunc(tRes(), tf());                                                     \
    reuseTmp<ReturnType, Type>::clear(tf);                                    \
    return tRes;                                                              \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BINARY_FUNCTION(ReturnType, Type1, Type2, Func)                       \
                                                                              \
TEMPLATE                                                                      \
void Func                                                                     \
(                                                                             \
    Field<ReturnType>& res,                                                   \
    const UList<Type1>& f1,                                                   \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    TFOR_ALL_F_OP_FUNC_F_F                                                    \
    (                                                                         \
        ReturnType, res, =, ::Foam::Func, Type1, f1, Type2, f2                \
    )                                                                         \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func                                                  \
(                                                                             \
    const UList<Type1>& f1,                                                   \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes(new Field<ReturnType>(f1.size()));           \
    Func(tRes(), f1, f2);                                                     \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func                                                  \
(                                                                             \
    const UList<Type1>& f1,                                                   \
    const tmp<Field<Type2> >& tf2                                             \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type2>::New(tf2);     \
    Func(tRes(), f1, tf2());                                                  \
    reuseTmp<ReturnType, Type2>::clear(tf2);                                  \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func                                                  \
(                                                                             \
    const tmp<Field<Type1> >& tf1,                                            \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type1>::New(tf1);     \
    Func(tRes(), tf1(), f2);                                                  \
    reuseTmp<ReturnType, Type1>::clear(tf1);                                  \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func                                                  \
(                                                                             \
    const tmp<Field<Type1> >& tf1,                                            \
    const tmp<Field<Type2> >& tf2                                             \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes =                                            \
        reuseTmpTmp<ReturnType, Type1, Type1, Type2>::New(tf1, tf2);          \
    Func(tRes(), tf1(), tf2());                                               \
    reuseTmpTmp<ReturnType, Type1, Type1, Type2>::clear(tf1, tf2);            \
    return tRes;                                                              \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BINARY_TYPE_FUNCTION_SF(ReturnType, Type1, Type2, Func)               \
                                                                              \
TEMPLATE                                                                      \
void Func                                                                     \
(                                                                             \
    Field<ReturnType>& res,                                                   \
    const Type1& s1,                                                          \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    TFOR_ALL_F_OP_FUNC_S_F                                                    \
    (                                                                         \
        ReturnType, res, =, ::Foam::Func, Type1, s1, Type2, f2                \
    )                                                                         \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func                                                  \
(                                                                             \
    const Type1& s1,                                                          \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes(new Field<ReturnType>(f2.size()));           \
    Func(tRes(), s1, f2);                                                     \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func                                                  \
(                                                                             \
    const Type1& s1,                                                          \
    const tmp<Field<Type2> >& tf2                                             \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type2>::New(tf2);     \
    Func(tRes(), s1, tf2());                                                  \
    reuseTmp<ReturnType, Type2>::clear(tf2);                                  \
    return tRes;                                                              \
}


#define BINARY_TYPE_FUNCTION_FS(ReturnType, Type1, Type2, Func)               \
                                                                              \
TEMPLATE                                                                      \
void Func                                                                     \
(                                                                             \
    Field<ReturnType>& res,                                                   \
    const UList<Type1>& f1,                                                   \
    const Type2& s2                                                           \
)                                                                             \
{                                                                             \
    TFOR_ALL_F_OP_FUNC_F_S                                                    \
    (                                                                         \
        ReturnType, res, =, ::Foam::Func, Type1, f1, Type2, s2                \
    )                                                                         \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func                                                  \
(                                                                             \
    const UList<Type1>& f1,                                                   \
    const Type2& s2                                                           \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes(new Field<ReturnType>(f1.size()));           \
    Func(tRes(), f1, s2);                                                     \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > Func                                                  \
(                                                                             \
    const tmp<Field<Type1> >& tf1,                                            \
    const Type2& s2                                                           \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type1>::New(tf1);     \
    Func(tRes(), tf1(), s2);                                                  \
    reuseTmp<ReturnType, Type1>::clear(tf1);                                  \
    return tRes;                                                              \
}


#define BINARY_TYPE_FUNCTION(ReturnType, Type1, Type2, Func)                  \
    BINARY_TYPE_FUNCTION_SF(ReturnType, Type1, Type2, Func)                   \
    BINARY_TYPE_FUNCTION_FS(ReturnType, Type1, Type2, Func)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BINARY_OPERATOR(ReturnType, Type1, Type2, Op, OpFunc)                 \
                                                                              \
TEMPLATE                                                                      \
void OpFunc                                                                   \
(                                                                             \
    Field<ReturnType>& res,                                                   \
    const UList<Type1>& f1,                                                   \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    TFOR_ALL_F_OP_F_OP_F(ReturnType, res, =, Type1, f1, Op, Type2, f2)        \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op                                           \
(                                                                             \
    const UList<Type1>& f1,                                                   \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes(new Field<ReturnType>(f1.size()));           \
    OpFunc(tRes(), f1, f2);                                                   \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op                                           \
(                                                                             \
    const UList<Type1>& f1,                                                   \
    const tmp<Field<Type2> >& tf2                                             \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type2>::New(tf2);     \
    OpFunc(tRes(), f1, tf2());                                                \
    reuseTmp<ReturnType, Type2>::clear(tf2);                                  \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op                                           \
(                                                                             \
    const tmp<Field<Type1> >& tf1,                                            \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type1>::New(tf1);     \
    OpFunc(tRes(), tf1(), f2);                                                \
    reuseTmp<ReturnType, Type1>::clear(tf1);                                  \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op                                           \
(                                                                             \
    const tmp<Field<Type1> >& tf1,                                            \
    const tmp<Field<Type2> >& tf2                                             \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes =                                            \
        reuseTmpTmp<ReturnType, Type1, Type1, Type2>::New(tf1, tf2);          \
    OpFunc(tRes(), tf1(), tf2());                                             \
    reuseTmpTmp<ReturnType, Type1, Type1, Type2>::clear(tf1, tf2);            \
    return tRes;                                                              \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BINARY_TYPE_OPERATOR_SF(ReturnType, Type1, Type2, Op, OpFunc)         \
                                                                              \
TEMPLATE                                                                      \
void OpFunc                                                                   \
(                                                                             \
    Field<ReturnType>& res,                                                   \
    const Type1& s1,                                                          \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    TFOR_ALL_F_OP_S_OP_F(ReturnType, res, =, Type1, s1, Op, Type2, f2)        \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op                                           \
(                                                                             \
    const Type1& s1,                                                          \
    const UList<Type2>& f2                                                    \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes(new Field<ReturnType>(f2.size()));           \
    OpFunc(tRes(), s1, f2);                                                   \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op                                           \
(                                                                             \
    const Type1& s1,                                                          \
    const tmp<Field<Type2> >& tf2                                             \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type2>::New(tf2);     \
    OpFunc(tRes(), s1, tf2());                                                \
    reuseTmp<ReturnType, Type2>::clear(tf2);                                  \
    return tRes;                                                              \
}


#define BINARY_TYPE_OPERATOR_FS(ReturnType, Type1, Type2, Op, OpFunc)         \
                                                                              \
TEMPLATE                                                                      \
void OpFunc                                                                   \
(                                                                             \
    Field<ReturnType>& res,                                                   \
    const UList<Type1>& f1,                                                   \
    const Type2& s2                                                           \
)                                                                             \
{                                                                             \
    TFOR_ALL_F_OP_F_OP_S(ReturnType, res, =, Type1, f1, Op, Type2, s2)        \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op                                           \
(                                                                             \
    const UList<Type1>& f1,                                                   \
    const Type2& s2                                                           \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes(new Field<ReturnType>(f1.size()));           \
    OpFunc(tRes(), f1, s2);                                                   \
    return tRes;                                                              \
}                                                                             \
                                                                              \
TEMPLATE                                                                      \
tmp<Field<ReturnType> > operator Op                                           \
(                                                                             \
    const tmp<Field<Type1> >& tf1,                                            \
    const Type2& s2                                                           \
)                                                                             \
{                                                                             \
    tmp<Field<ReturnType> > tRes = reuseTmp<ReturnType, Type1>::New(tf1);     \
    OpFunc(tRes(), tf1(), s2);                                                \
    reuseTmp<ReturnType, Type1>::clear(tf1);                                  \
    return tRes;                                                              \
}


#define BINARY_TYPE_OPERATOR(ReturnType, Type1, Type2, Op, OpFunc)            \
    BINARY_TYPE_OPERATOR_SF(ReturnType, Type1, Type2, Op, OpFunc)             \
    BINARY_TYPE_OPERATOR_FS(ReturnType, Type1, Type2, Op, OpFunc)


// ************************************************************************* //