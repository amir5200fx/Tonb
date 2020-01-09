#include <CoupledPointPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		class CoupledPointPatch,
		template<class> class MatrixType,
		class Type
		>
		CoupledPointPatchField
		<PatchField, Mesh, PointPatch, CoupledPointPatch, MatrixType, Type>::
		CoupledPointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		lduInterfaceField(refCast<const lduInterface>(p)),
		PatchField<Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		class CoupledPointPatch,
		template<class> class MatrixType,
		class Type
		>
		CoupledPointPatchField
		<PatchField, Mesh, PointPatch, CoupledPointPatch, MatrixType, Type>::
		CoupledPointPatchField
		(
			const CoupledPointPatchField
			<PatchField, Mesh, PointPatch, CoupledPointPatch, MatrixType, Type>&,
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const PointPatchFieldMapper&
		)
		:
		lduInterfaceField(refCast<const lduInterface>(p)),
		PatchField<Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		class CoupledPointPatch,
		template<class> class MatrixType,
		class Type
		>
		CoupledPointPatchField
		<PatchField, Mesh, PointPatch, CoupledPointPatch, MatrixType, Type>::
		CoupledPointPatchField
		(
			const CoupledPointPatchField
			<PatchField, Mesh, PointPatch, CoupledPointPatch, MatrixType, Type>& ptf
		)
		:
		lduInterfaceField(refCast<const lduInterface>(ptf.patch())),
		PatchField<Type>(ptf)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		class CoupledPointPatch,
		template<class> class MatrixType,
		class Type
		>
		CoupledPointPatchField
		<PatchField, Mesh, PointPatch, CoupledPointPatch, MatrixType, Type>::
		CoupledPointPatchField
		(
			const CoupledPointPatchField
			<PatchField, Mesh, PointPatch, CoupledPointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		lduInterfaceField(refCast<const lduInterface>(ptf.patch())),
		PatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //