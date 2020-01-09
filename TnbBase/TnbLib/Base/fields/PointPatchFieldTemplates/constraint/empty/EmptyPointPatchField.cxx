#include <EmptyPointPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		class EmptyPointPatch,
		template<class> class MatrixType,
		class Type
		>
		EmptyPointPatchField
		<PatchField, Mesh, PointPatch, EmptyPointPatch, MatrixType, Type>::
		EmptyPointPatchField
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
		class EmptyPointPatch,
		template<class> class MatrixType,
		class Type
		>
		EmptyPointPatchField
		<PatchField, Mesh, PointPatch, EmptyPointPatch, MatrixType, Type>::
		EmptyPointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const dictionary& dict
		)
		:
		PatchField<Type>(p, iF)
	{
		if (!isType<EmptyPointPatch>(p))
		{
			FatalIOErrorIn
			(
				"EmptyPointPatchField"
				"<PatchField, Mesh, PointPatch, EmptyPointPatch, "
				"MatrixType, Type>::EmptyPointPatchField\n"
				"(\n"
				"    const PointPatch& p,\n"
				"    const DimensionedField<Type, Mesh>& iF,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not empty type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		class EmptyPointPatch,
		template<class> class MatrixType,
		class Type
		>
		EmptyPointPatchField
		<PatchField, Mesh, PointPatch, EmptyPointPatch, MatrixType, Type>::
		EmptyPointPatchField
		(
			const EmptyPointPatchField
			<PatchField, Mesh, PointPatch, EmptyPointPatch, MatrixType, Type>&,
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const PointPatchFieldMapper&
		)
		:
		PatchField<Type>(p, iF)
	{
		if (!isType<EmptyPointPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"EmptyPointPatchField"
				"<PatchField, Mesh, PointPatch, EmptyPointPatch, "
				"MatrixType, Type>::EmptyPointPatchField\n"
				"(\n"
				"    const EmptyPointPatchField<PatchField, Mesh, PointPatch, "
				"EmptyPointPatch, MatrixType, Type>& ptf,\n"
				"    const PointPatch& p,\n"
				"    const DimensionedField<Type, Mesh>& iF,\n"
				"    const PointPatchFieldMapper& mapper\n"
				")\n"
			) << "Field type does not correspond to patch type for patch "
				<< this->patch().index() << "." << endl
				<< "Field type: " << typeName << endl
				<< "Patch type: " << this->patch().type()
				<< exit(FatalError);
		}
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		class EmptyPointPatch,
		template<class> class MatrixType,
		class Type
		>
		EmptyPointPatchField
		<PatchField, Mesh, PointPatch, EmptyPointPatch, MatrixType, Type>::
		EmptyPointPatchField
		(
			const EmptyPointPatchField
			<PatchField, Mesh, PointPatch, EmptyPointPatch, MatrixType, Type>& ptf
		)
		:
		PatchField<Type>(ptf)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		class EmptyPointPatch,
		template<class> class MatrixType,
		class Type
		>
		EmptyPointPatchField
		<PatchField, Mesh, PointPatch, EmptyPointPatch, MatrixType, Type>::
		EmptyPointPatchField
		(
			const EmptyPointPatchField
			<PatchField, Mesh, PointPatch, EmptyPointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		PatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //