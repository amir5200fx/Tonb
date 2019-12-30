#include <dimensionedVectorTensorN.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define UNARY_FUNCTION(returnType, type, fun, text)                 \
inline dimensioned< returnType > fun(const dimensioned< type >& t)  \
{                                                                   \
    return dimensioned< returnType >                                \
    (                                                               \
        #text "(" + t.name() + ')',                                 \
        fun(t.dimensions()),                                        \
        fun(t.value())                                              \
    );                                                              \
}


#define BINARY_OPERATOR(returnType, type1, type2, op, text)            \
dimensioned< returnType > op(const dimensioned< type1 >& dt1,          \
    const dimensioned< type2 >& dt2)                                   \
{                                                                      \
    return dimensioned<returnType>                                     \
    (                                                                  \
        '(' + dt1.name() + #text + dt2.name() + ')',                   \
        op(dt1.dimensions(), dt2.dimensions()),                        \
        op(dt1.value(), dt2.value())                                   \
    );                                                                 \
}

#define dimensionedType_Funs(tensorType, diagTensorType,                            \
    sphericalTensorType, vectorType, cmptType, args)                             \
UNARY_FUNCTION(tensorType, tensorType, inv, inv)                                    \
UNARY_FUNCTION(diagTensorType, diagTensorType, inv, inv)                            \
UNARY_FUNCTION(sphericalTensorType, sphericalTensorType, inv, inv)                  \
                                                                                    \
UNARY_FUNCTION(diagTensorType, tensorType, diag, diag)                              \
UNARY_FUNCTION(diagTensorType, diagTensorType, diag, diag)                          \
UNARY_FUNCTION(sphericalTensorType, sphericalTensorType, diag, diag)                \
                                                                                    \
BINARY_OPERATOR(tensorType, tensorType, diagTensorType, operator+, +)               \
BINARY_OPERATOR(tensorType, diagTensorType, tensorType, operator+, +)               \
BINARY_OPERATOR(tensorType, tensorType, sphericalTensorType, operator+, +)          \
BINARY_OPERATOR(tensorType, sphericalTensorType, tensorType, operator+, +)          \
BINARY_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, operator+, +)  \
BINARY_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, operator+, +)  \
                                                                                    \
BINARY_OPERATOR(tensorType, tensorType, diagTensorType, operator-, -)               \
BINARY_OPERATOR(tensorType, diagTensorType, tensorType, operator-, -)               \
BINARY_OPERATOR(tensorType, tensorType, sphericalTensorType, operator-, -)          \
BINARY_OPERATOR(tensorType, sphericalTensorType, tensorType, operator-, -)          \
BINARY_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, operator-, -)  \
BINARY_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, operator-, -)

	inline dimensioned<tensor2> inv(const dimensioned<tensor2>& t)
	{
		return dimensioned<tensor2>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor2> inv(const dimensioned<diagTensor2>& t)
	{
		return dimensioned<diagTensor2>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<sphericalTensor2> inv(const dimensioned<sphericalTensor2>& t)
	{
		return dimensioned<sphericalTensor2>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor2> diag(const dimensioned<tensor2>& t)
	{
		return dimensioned<diagTensor2>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<diagTensor2> diag(const dimensioned<diagTensor2>& t)
	{
		return dimensioned<diagTensor2>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<sphericalTensor2> diag(const dimensioned<sphericalTensor2>& t)
	{
		return dimensioned<sphericalTensor2>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	dimensioned<tensor2> operator+(const dimensioned<tensor2>& dt1, const dimensioned<diagTensor2>& dt2)
	{
		return dimensioned<tensor2>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor2> operator+(const dimensioned<diagTensor2>& dt1, const dimensioned<tensor2>& dt2)
	{
		return dimensioned<tensor2>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor2> operator+(const dimensioned<tensor2>& dt1, const dimensioned<sphericalTensor2>& dt2)
	{
		return dimensioned<tensor2>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor2> operator+(const dimensioned<sphericalTensor2>& dt1, const dimensioned<tensor2>& dt2)
	{
		return dimensioned<tensor2>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor2> operator+(const dimensioned<diagTensor2>& dt1, const dimensioned<sphericalTensor2>& dt2)
	{
		return dimensioned<diagTensor2>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor2> operator+(const dimensioned<sphericalTensor2>& dt1, const dimensioned<diagTensor2>& dt2)
	{
		return dimensioned<diagTensor2>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor2> operator-(const dimensioned<tensor2>& dt1, const dimensioned<diagTensor2>& dt2)
	{
		return dimensioned<tensor2>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor2> operator-(const dimensioned<diagTensor2>& dt1, const dimensioned<tensor2>& dt2)
	{
		return dimensioned<tensor2>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor2> operator-(const dimensioned<tensor2>& dt1, const dimensioned<sphericalTensor2>& dt2)
	{
		return dimensioned<tensor2>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor2> operator-(const dimensioned<sphericalTensor2>& dt1, const dimensioned<tensor2>& dt2)
	{
		return dimensioned<tensor2>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor2> operator-(const dimensioned<diagTensor2>& dt1, const dimensioned<sphericalTensor2>& dt2)
	{
		return dimensioned<diagTensor2>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor2> operator-(const dimensioned<sphericalTensor2>& dt1, const dimensioned<diagTensor2>& dt2)
	{
		return dimensioned<diagTensor2>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

	inline dimensioned<tensor3> inv(const dimensioned<tensor3>& t)
	{
		return dimensioned<tensor3>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor3> inv(const dimensioned<diagTensor3>& t)
	{
		return dimensioned<diagTensor3>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<sphericalTensor3> inv(const dimensioned<sphericalTensor3>& t)
	{
		return dimensioned<sphericalTensor3>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor3> diag(const dimensioned<tensor3>& t)
	{
		return dimensioned<diagTensor3>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<diagTensor3> diag(const dimensioned<diagTensor3>& t)
	{
		return dimensioned<diagTensor3>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<sphericalTensor3> diag(const dimensioned<sphericalTensor3>& t)
	{
		return dimensioned<sphericalTensor3>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	dimensioned<tensor3> operator+(const dimensioned<tensor3>& dt1, const dimensioned<diagTensor3>& dt2)
	{
		return dimensioned<tensor3>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor3> operator+(const dimensioned<diagTensor3>& dt1, const dimensioned<tensor3>& dt2)
	{
		return dimensioned<tensor3>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor3> operator+(const dimensioned<tensor3>& dt1, const dimensioned<sphericalTensor3>& dt2)
	{
		return dimensioned<tensor3>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor3> operator+(const dimensioned<sphericalTensor3>& dt1, const dimensioned<tensor3>& dt2)
	{
		return dimensioned<tensor3>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor3> operator+(const dimensioned<diagTensor3>& dt1, const dimensioned<sphericalTensor3>& dt2)
	{
		return dimensioned<diagTensor3>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor3> operator+(const dimensioned<sphericalTensor3>& dt1, const dimensioned<diagTensor3>& dt2)
	{
		return dimensioned<diagTensor3>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor3> operator-(const dimensioned<tensor3>& dt1, const dimensioned<diagTensor3>& dt2)
	{
		return dimensioned<tensor3>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor3> operator-(const dimensioned<diagTensor3>& dt1, const dimensioned<tensor3>& dt2)
	{
		return dimensioned<tensor3>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor3> operator-(const dimensioned<tensor3>& dt1, const dimensioned<sphericalTensor3>& dt2)
	{
		return dimensioned<tensor3>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor3> operator-(const dimensioned<sphericalTensor3>& dt1, const dimensioned<tensor3>& dt2)
	{
		return dimensioned<tensor3>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor3> operator-(const dimensioned<diagTensor3>& dt1, const dimensioned<sphericalTensor3>& dt2)
	{
		return dimensioned<diagTensor3>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor3> operator-(const dimensioned<sphericalTensor3>& dt1, const dimensioned<diagTensor3>& dt2)
	{
		return dimensioned<diagTensor3>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

	inline dimensioned<tensor4> inv(const dimensioned<tensor4>& t)
	{
		return dimensioned<tensor4>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor4> inv(const dimensioned<diagTensor4>& t)
	{
		return dimensioned<diagTensor4>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<sphericalTensor4> inv(const dimensioned<sphericalTensor4>& t)
	{
		return dimensioned<sphericalTensor4>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor4> diag(const dimensioned<tensor4>& t)
	{
		return dimensioned<diagTensor4>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<diagTensor4> diag(const dimensioned<diagTensor4>& t)
	{
		return dimensioned<diagTensor4>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<sphericalTensor4> diag(const dimensioned<sphericalTensor4>& t)
	{
		return dimensioned<sphericalTensor4>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	dimensioned<tensor4> operator+(const dimensioned<tensor4>& dt1, const dimensioned<diagTensor4>& dt2)
	{
		return dimensioned<tensor4>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor4> operator+(const dimensioned<diagTensor4>& dt1, const dimensioned<tensor4>& dt2)
	{
		return dimensioned<tensor4>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor4> operator+(const dimensioned<tensor4>& dt1, const dimensioned<sphericalTensor4>& dt2)
	{
		return dimensioned<tensor4>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor4> operator+(const dimensioned<sphericalTensor4>& dt1, const dimensioned<tensor4>& dt2)
	{
		return dimensioned<tensor4>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor4> operator+(const dimensioned<diagTensor4>& dt1, const dimensioned<sphericalTensor4>& dt2)
	{
		return dimensioned<diagTensor4>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor4> operator+(const dimensioned<sphericalTensor4>& dt1, const dimensioned<diagTensor4>& dt2)
	{
		return dimensioned<diagTensor4>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor4> operator-(const dimensioned<tensor4>& dt1, const dimensioned<diagTensor4>& dt2)
	{
		return dimensioned<tensor4>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor4> operator-(const dimensioned<diagTensor4>& dt1, const dimensioned<tensor4>& dt2)
	{
		return dimensioned<tensor4>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor4> operator-(const dimensioned<tensor4>& dt1, const dimensioned<sphericalTensor4>& dt2)
	{
		return dimensioned<tensor4>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor4> operator-(const dimensioned<sphericalTensor4>& dt1, const dimensioned<tensor4>& dt2)
	{
		return dimensioned<tensor4>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor4> operator-(const dimensioned<diagTensor4>& dt1, const dimensioned<sphericalTensor4>& dt2)
	{
		return dimensioned<diagTensor4>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor4> operator-(const dimensioned<sphericalTensor4>& dt1, const dimensioned<diagTensor4>& dt2)
	{
		return dimensioned<diagTensor4>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

	inline dimensioned<tensor6> inv(const dimensioned<tensor6>& t)
	{
		return dimensioned<tensor6>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor6> inv(const dimensioned<diagTensor6>& t)
	{
		return dimensioned<diagTensor6>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<sphericalTensor6> inv(const dimensioned<sphericalTensor6>& t)
	{
		return dimensioned<sphericalTensor6>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor6> diag(const dimensioned<tensor6>& t)
	{
		return dimensioned<diagTensor6>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<diagTensor6> diag(const dimensioned<diagTensor6>& t)
	{
		return dimensioned<diagTensor6>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<sphericalTensor6> diag(const dimensioned<sphericalTensor6>& t)
	{
		return dimensioned<sphericalTensor6>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	dimensioned<tensor6> operator+(const dimensioned<tensor6>& dt1, const dimensioned<diagTensor6>& dt2)
	{
		return dimensioned<tensor6>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor6> operator+(const dimensioned<diagTensor6>& dt1, const dimensioned<tensor6>& dt2)
	{
		return dimensioned<tensor6>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor6> operator+(const dimensioned<tensor6>& dt1, const dimensioned<sphericalTensor6>& dt2)
	{
		return dimensioned<tensor6>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor6> operator+(const dimensioned<sphericalTensor6>& dt1, const dimensioned<tensor6>& dt2)
	{
		return dimensioned<tensor6>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor6> operator+(const dimensioned<diagTensor6>& dt1, const dimensioned<sphericalTensor6>& dt2)
	{
		return dimensioned<diagTensor6>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor6> operator+(const dimensioned<sphericalTensor6>& dt1, const dimensioned<diagTensor6>& dt2)
	{
		return dimensioned<diagTensor6>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor6> operator-(const dimensioned<tensor6>& dt1, const dimensioned<diagTensor6>& dt2)
	{
		return dimensioned<tensor6>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor6> operator-(const dimensioned<diagTensor6>& dt1, const dimensioned<tensor6>& dt2)
	{
		return dimensioned<tensor6>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor6> operator-(const dimensioned<tensor6>& dt1, const dimensioned<sphericalTensor6>& dt2)
	{
		return dimensioned<tensor6>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor6> operator-(const dimensioned<sphericalTensor6>& dt1, const dimensioned<tensor6>& dt2)
	{
		return dimensioned<tensor6>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor6> operator-(const dimensioned<diagTensor6>& dt1, const dimensioned<sphericalTensor6>& dt2)
	{
		return dimensioned<diagTensor6>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor6> operator-(const dimensioned<sphericalTensor6>& dt1, const dimensioned<diagTensor6>& dt2)
	{
		return dimensioned<diagTensor6>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

	inline dimensioned<tensor8> inv(const dimensioned<tensor8>& t)
	{
		return dimensioned<tensor8>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor8> inv(const dimensioned<diagTensor8>& t)
	{
		return dimensioned<diagTensor8>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<sphericalTensor8> inv(const dimensioned<sphericalTensor8>& t)
	{
		return dimensioned<sphericalTensor8>("inv" "(" + t.name() + ')', inv(t.dimensions()), inv(t.value()));
	}

	inline dimensioned<diagTensor8> diag(const dimensioned<tensor8>& t)
	{
		return dimensioned<diagTensor8>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<diagTensor8> diag(const dimensioned<diagTensor8>& t)
	{
		return dimensioned<diagTensor8>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	inline dimensioned<sphericalTensor8> diag(const dimensioned<sphericalTensor8>& t)
	{
		return dimensioned<sphericalTensor8>("diag" "(" + t.name() + ')', diag(t.dimensions()), diag(t.value()));
	}

	dimensioned<tensor8> operator+(const dimensioned<tensor8>& dt1, const dimensioned<diagTensor8>& dt2)
	{
		return dimensioned<tensor8>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor8> operator+(const dimensioned<diagTensor8>& dt1, const dimensioned<tensor8>& dt2)
	{
		return dimensioned<tensor8>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor8> operator+(const dimensioned<tensor8>& dt1, const dimensioned<sphericalTensor8>& dt2)
	{
		return dimensioned<tensor8>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor8> operator+(const dimensioned<sphericalTensor8>& dt1, const dimensioned<tensor8>& dt2)
	{
		return dimensioned<tensor8>('(' + dt1.name() + "+" + dt2.name() + ')', operator+(dt1.dimensions(), dt2.dimensions())
		                            , operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor8> operator+(const dimensioned<diagTensor8>& dt1, const dimensioned<sphericalTensor8>& dt2)
	{
		return dimensioned<diagTensor8>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor8> operator+(const dimensioned<sphericalTensor8>& dt1, const dimensioned<diagTensor8>& dt2)
	{
		return dimensioned<diagTensor8>('(' + dt1.name() + "+" + dt2.name() + ')'
		                                , operator+(dt1.dimensions(), dt2.dimensions()), operator+(dt1.value(), dt2.value()));
	}

	dimensioned<tensor8> operator-(const dimensioned<tensor8>& dt1, const dimensioned<diagTensor8>& dt2)
	{
		return dimensioned<tensor8>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor8> operator-(const dimensioned<diagTensor8>& dt1, const dimensioned<tensor8>& dt2)
	{
		return dimensioned<tensor8>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor8> operator-(const dimensioned<tensor8>& dt1, const dimensioned<sphericalTensor8>& dt2)
	{
		return dimensioned<tensor8>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<tensor8> operator-(const dimensioned<sphericalTensor8>& dt1, const dimensioned<tensor8>& dt2)
	{
		return dimensioned<tensor8>('(' + dt1.name() + "-" + dt2.name() + ')', operator-(dt1.dimensions(), dt2.dimensions())
		                            , operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor8> operator-(const dimensioned<diagTensor8>& dt1, const dimensioned<sphericalTensor8>& dt2)
	{
		return dimensioned<diagTensor8>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

	dimensioned<diagTensor8> operator-(const dimensioned<sphericalTensor8>& dt1, const dimensioned<diagTensor8>& dt2)
	{
		return dimensioned<diagTensor8>('(' + dt1.name() + "-" + dt2.name() + ')'
		                                , operator-(dt1.dimensions(), dt2.dimensions()), operator-(dt1.value(), dt2.value()));
	}

#undef dimensionedType_Funs
#undef UNARY_FUNCTION
#undef BINARY_OPERATOR

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //