#include <UniformFixedValuePointPatchField.hxx>

#include <transformField.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		UniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		UniformFixedValuePointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF),
		uniformValue_(pTraits<Type>::zero)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		UniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		UniformFixedValuePointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const dictionary& dict
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF),
		uniformValue_(pTraits<Type>(dict.lookup("uniformValue")))
	{
		FixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>::operator==
			(uniformValue_);
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		UniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		UniformFixedValuePointPatchField
		(
			const
			UniformFixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const PointPatchFieldMapper& mapper
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF),
		uniformValue_(ptf.uniformValue_)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		UniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		UniformFixedValuePointPatchField
		(
			const UniformFixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(ptf),
		uniformValue_(ptf.uniformValue_)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		UniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		UniformFixedValuePointPatchField
		(
			const UniformFixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(ptf, iF),
		uniformValue_(ptf.uniformValue_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		UniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::initEvaluate
		(
			const Pstream::commsTypes commsType
		)
	{
		Field<Type>& patchField = *this;
		patchField = uniformValue_;

		FixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>::
			initEvaluate(commsType);
	}


	// Write
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		UniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::write(Ostream& os) const
	{
		PatchField<Type>::write(os);
		os.writeKeyword("uniformValue")
			<< uniformValue_ << token::END_STATEMENT << nl;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //