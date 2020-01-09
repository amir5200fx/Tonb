#include <pointPatchField.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	pointPatchField<Type>::pointPatchField
	(
		const pointPatch& p,
		const DimensionedField<Type, pointMesh>& iF
	)
		:
		PointPatchField
		<tnbLib::pointPatchField, pointMesh, pointPatch, DummyMatrix, Type>(p, iF)
	{}


	template<class Type>
	pointPatchField<Type>::pointPatchField
	(
		const pointPatchField<Type>& ptf
	)
		:
		PointPatchField
		<tnbLib::pointPatchField, pointMesh, pointPatch, DummyMatrix, Type>(ptf)
	{}


	template<class Type>
	pointPatchField<Type>::pointPatchField
	(
		const pointPatchField<Type>& ptf,
		const DimensionedField<Type, pointMesh>& iF
	)
		:
		PointPatchField
		<tnbLib::pointPatchField, pointMesh, pointPatch, DummyMatrix, Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //