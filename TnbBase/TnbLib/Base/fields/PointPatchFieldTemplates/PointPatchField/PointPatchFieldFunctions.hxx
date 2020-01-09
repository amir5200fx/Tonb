#pragma once
namespace tnbLib
{

	/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>

		inline void component
		(
			PointPatchField
			<
			PatchField,
			Mesh,
			PointPatch,
			MatrixType,
			typename Field<Type>::cmptType
			>& sf,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
			const direction d
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>

		inline void T
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f2
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type,
		int r
		>
		inline void pow
		(
			Field<typename powProduct<Type, r>::type>& f,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& vf
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>

		inline void sqr
		(
			Field<typename outerProduct<Type, Type>::type>& f,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& vf
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>

		inline void magSqr
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, scalar>& sf,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>

		inline void mag
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, scalar>& sf,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>

		inline void cmptAv
		(
			PointPatchField
			<
			PatchField,
			Mesh,
			PointPatch,
			MatrixType,
			typename Field<Type>::cmptType
			>& cf,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>

		inline void cmptMag
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& cf,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f
		)
	{}


#define BINARY_FUNCTION(func)                                                 \
                                                                              \
template                                                                      \
<                                                                             \
    template<class> class PatchField,                                         \
    class Mesh,                                                               \
    class PointPatch,                                                         \
    template<class> class MatrixType,                                         \
    class Type                                                                \
>                                                                             \
inline void func                                                              \
(                                                                             \
    PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,       \
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1,\
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f2 \
){}                                                                           \
                                                                              \
template                                                                      \
<                                                                             \
    template<class> class PatchField,                                         \
    class Mesh,                                                               \
    class PointPatch,                                                         \
    template<class> class MatrixType,                                         \
    class Type                                                                \
>                                                                             \
inline void func                                                              \
(                                                                             \
    PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,       \
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1,\
    const Type& s                                                             \
){}

	BINARY_FUNCTION(max)
		BINARY_FUNCTION(min)
		BINARY_FUNCTION(scale)
		BINARY_FUNCTION(invScale)

#undef BINARY_FUNCTION


		/* * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * */

#define UNARY_OPERATOR(op, opFunc)                                            \
                                                                              \
template                                                                      \
<                                                                             \
    template<class> class PatchField,                                         \
    class Mesh,                                                               \
    class PointPatch,                                                         \
    template<class> class MatrixType,                                         \
    class Type                                                                \
>                                                                             \
inline void opFunc                                                            \
(                                                                             \
    PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,       \
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1 \
){}

		
	template 
	<
	template<class> class PatchField,
	class Mesh, 
	class PointPatch,
	template<class> class MatrixType,
	class Type
	>	
	inline void negate(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
		                   const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1)
		{}

#undef UNARY_OPERATOR


#define BINARY_OPERATOR_FF(Type1, Type2, op, opFunc)                          \
                                                                              \
template                                                                      \
<                                                                             \
    template<class> class PatchField,                                         \
    class Mesh,                                                               \
    class PointPatch,                                                         \
    template<class> class MatrixType,                                         \
    class Type                                                                \
>                                                                             \
inline void opFunc                                                            \
(                                                                             \
    PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,       \
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type1>& f1,\
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type2>& f2 \
){}

#define BINARY_OPERATOR_R(Type1, Type2, op, opFunc)                           \
    BINARY_OPERATOR_FF(Type1, Type2, op, opFunc)

		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void add(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
	                const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1,
	                const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f2)
	{
	}
		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void subtract(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
	                     const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1,
	                     const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f2)
	{
	}
		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void multiply(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
	                     const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, scalar>& f1,
	                     const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f2)
	{
	}
		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void divide(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
	                   const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1,
	                   const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, scalar>& f2)
	{
	}

		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void add(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
	                const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, symmTensor>& f1,
	                const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, sphericalTensor>& f2)
	{
	}

#undef BINARY_OPERATOR_R
#undef BINARY_OPERATOR_FF
#undef BINARY_OPERATOR_FTR
#undef BINARY_OPERATOR_TF
#undef BINARY_OPERATOR_TTR
#undef BINARY_OPERATOR_FT
#undef BINARY_OPERATOR_TRF
#undef BINARY_OPERATOR_TRT


#define BINARY_TYPE_OPERATOR_TF(TYPE, op, opFunc)                             \
                                                                              \
template                                                                      \
<                                                                             \
    template<class> class PatchField,                                         \
    class Mesh,                                                               \
    class PointPatch,                                                         \
    template<class> class MatrixType,                                         \
    class Type                                                                \
>                                                                             \
inline void opFunc                                                            \
(                                                                             \
    PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,       \
    const TYPE& s,                                                            \
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1 \
){}


#define BINARY_TYPE_OPERATOR_FT(TYPE, op, opFunc)                             \
                                                                              \
template                                                                      \
<                                                                             \
    template<class> class PatchField,                                         \
    class Mesh,                                                               \
    class PointPatch,                                                         \
    template<class> class MatrixType,                                         \
    class Type                                                                \
>                                                                             \
inline void opFunc                                                            \
(                                                                             \
    PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,       \
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1,\
    const TYPE& s                                                             \
){}


#define BINARY_TYPE_OPERATOR(TYPE, op, opFunc)                                \
    BINARY_TYPE_OPERATOR_TF(TYPE, op, opFunc)                                 \
    BINARY_TYPE_OPERATOR_FT(TYPE, op, opFunc)

		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void add(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f, const Type& s,
	                const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void add(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
	                const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1, const Type& s)
	{
	}
		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void subtract(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f, const Type& s,
	                     const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void subtract(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
	                     const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1, const Type& s)
	{
	}

		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void multiply(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f, const scalar& s,
	                     const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void multiply(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
	                     const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1, const scalar& s)
	{
	}
		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type>
	inline void divide(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f,
	                   const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1, const scalar& s)
	{
	}

#undef BINARY_TYPE_OPERATOR
#undef BINARY_TYPE_OPERATOR_TF
#undef BINARY_TYPE_OPERATOR_FT


#define PRODUCT_OPERATOR(product, op, opFunc)                                 \
                                                                              \
template                                                                      \
<                                                                             \
    template<class> class PatchField,                                         \
    class Mesh,                                                               \
    class PointPatch,                                                         \
    template<class> class MatrixType,                                         \
    class Type1,                                                              \
    class Type2                                                               \
>                                                                             \
inline void opFunc                                                            \
(                                                                             \
    PointPatchField                                                           \
    <PatchField, Mesh, PointPatch, MatrixType,                                \
     typename product<Type1, Type2>::type>& f,                                \
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type1>& f1,\
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type2>& f2 \
){}                                                                           \
                                                                              \
                                                                              \
template                                                                      \
<                                                                             \
    template<class> class PatchField,                                         \
    class Mesh,                                                               \
    class PointPatch,                                                         \
    template<class> class MatrixType,                                         \
    class Type,                                                               \
    class Form,                                                               \
    class Cmpt,                                                               \
    int nCmpt                                                                 \
>                                                                             \
inline void opFunc                                                            \
(                                                                             \
    PointPatchField                                                           \
    <PatchField, Mesh, PointPatch, MatrixType,                                \
     typename product<Type, Form>::type>& f,                                  \
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1,\
    const VectorSpace<Form,Cmpt,nCmpt>& vs                                    \
){}                                                                           \
                                                                              \
                                                                              \
template                                                                      \
<                                                                             \
    template<class> class PatchField,                                         \
    class Mesh,                                                               \
    class PointPatch,                                                         \
    template<class> class MatrixType,                                         \
    class Form,                                                               \
    class Cmpt,                                                               \
    int nCmpt,                                                                \
    class Type                                                                \
>                                                                             \
inline void opFunc                                                            \
(                                                                             \
    PointPatchField                                                           \
    <PatchField, Mesh, PointPatch, MatrixType,                                \
     typename product<Form, Type>::type>& f,                                  \
    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                   \
    const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1 \
){}


		template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class
		          Type1, class Type2>
	inline void outer(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename outerProduct<Type1, Type2>::type>& f,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type1>& f1,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type2>& f2)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type,
	          class Form, class Cmpt, int nCmpt>
	inline void outer(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename outerProduct<Type, Form>::type>& f,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Form,
	          class Cmpt, int nCmpt, class Type>
	inline void outer(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename outerProduct<Form, Type>::type>& f,
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1)
	{
	}
		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type1
	          , class Type2>
	inline void cross(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename crossProduct<Type1, Type2>::type>& f,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type1>& f1,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type2>& f2)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type,
	          class Form, class Cmpt, int nCmpt>
	inline void cross(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename crossProduct<Type, Form>::type>& f,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Form,
	          class Cmpt, int nCmpt, class Type>
	inline void cross(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename crossProduct<Form, Type>::type>& f,
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1)
	{
	}
		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type1
	          , class Type2>
	inline void dot(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename innerProduct<Type1, Type2>::type>& f,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type1>& f1,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type2>& f2)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type,
	          class Form, class Cmpt, int nCmpt>
	inline void dot(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename innerProduct<Type, Form>::type>& f,
	                const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1,
	                const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Form,
	          class Cmpt, int nCmpt, class Type>
	inline void dot(PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename innerProduct<Form, Type>::type>& f,
	                const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1)
	{
	}
		
	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type1
	          , class Type2>
	inline void dotdot(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename scalarProduct<Type1, Type2>::type>& f,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type1>& f1,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type2>& f2)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Type,
	          class Form, class Cmpt, int nCmpt>
	inline void dotdot(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename scalarProduct<Type, Form>::type>& f,
		const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
	}

	template <template<class> class PatchField, class Mesh, class PointPatch, template<class> class MatrixType, class Form,
	          class Cmpt, int nCmpt, class Type>
	inline void dotdot(
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, typename scalarProduct<Form, Type>::type>& f,
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& f1)
	{
	}

#undef PRODUCT_OPERATOR


		template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void hdual
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, vector>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void hdual
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, vector>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void diag
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, vector>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void tr
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, scalar>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void dev
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void dev2
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void det
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, scalar>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void inv
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void hinv
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void symm
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, symmTensor>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void skew
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void eigenValues
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, vector>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType
		>
		void eigenVectors
		(
			PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, tensor>&
		) {}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
