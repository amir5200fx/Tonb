#include <ZeroGradientPointPatchField.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		ZeroGradientPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ZeroGradientPointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		PatchField<Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		ZeroGradientPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ZeroGradientPointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const dictionary&
		)
		:
		PatchField<Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		ZeroGradientPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ZeroGradientPointPatchField
		(
			const ZeroGradientPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>&,
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const PointPatchFieldMapper&
		)
		:
		PatchField<Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		ZeroGradientPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ZeroGradientPointPatchField
		(
			const ZeroGradientPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		PatchField<Type>(ptf, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		ZeroGradientPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ZeroGradientPointPatchField
		(
			const ZeroGradientPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
		)
		:
		PatchField<Type>(ptf)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //