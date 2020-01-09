#include <SlipPointPatchField.hxx>

#include <transformField.hxx>

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
		SlipPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		SlipPointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		BasicSymmetryPointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		SlipPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		SlipPointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const dictionary&
		)
		:
		BasicSymmetryPointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		SlipPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		SlipPointPatchField
		(
			const SlipPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>&,
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const PointPatchFieldMapper&
		)
		:
		BasicSymmetryPointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		SlipPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		SlipPointPatchField
		(
			const SlipPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
		)
		:
		BasicSymmetryPointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(ptf)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		SlipPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		SlipPointPatchField
		(
			const SlipPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		BasicSymmetryPointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //