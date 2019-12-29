#include <VectorNFields.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define VectorN_FieldFunctions(tensorType,diagTensorType,                    \
                               sphericalTensorType,vectorType,CmptType,      \
                               args)										\
                                                                             \
UNARY_FUNCTION(CmptType, vectorType, cmptSum)                                \
                                                                             \
BINARY_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)            \
BINARY_TYPE_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)       \
                                                                             \
BINARY_OPERATOR(vectorType, CmptType, vectorType, /, divide)                 \
BINARY_TYPE_OPERATOR(vectorType, CmptType, vectorType, /, divide)            \
                                                                             \
BINARY_OPERATOR(vectorType, vectorType, vectorType, +, add)                  \
BINARY_OPERATOR(vectorType, vectorType, vectorType, -, subtract)             \
                                                                             \
BINARY_TYPE_OPERATOR(vectorType, vectorType, vectorType, +, add)             \
BINARY_TYPE_OPERATOR(vectorType, vectorType, vectorType, -, subtract)        \

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	forAllVectorTensorNTypes(VectorN_FieldFunctions)
}

#undef VectorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>