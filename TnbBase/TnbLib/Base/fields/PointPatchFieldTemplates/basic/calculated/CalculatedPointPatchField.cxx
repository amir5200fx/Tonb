#include <CalculatedPointPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		const word&
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>
		::calculatedType()
	{
		return CalculatedPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>::typeName;
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		CalculatedPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		CalculatedPointPatchField
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
		CalculatedPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		CalculatedPointPatchField
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
		CalculatedPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		CalculatedPointPatchField
		(
			const CalculatedPointPatchField
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
		CalculatedPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		CalculatedPointPatchField
		(
			const CalculatedPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
		)
		:
		PatchField<Type>(ptf)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		CalculatedPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		CalculatedPointPatchField
		(
			const CalculatedPointPatchField
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
		template<class Type2>
	autoPtr<PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type> >
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>
		::NewCalculatedType
		(
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type2>& pf
		)
	{
		typename PointPatchConstructorTable::iterator patchTypeCstrIter =
			PointPatchConstructorTablePtr_->find(pf.patch().type());

		if (patchTypeCstrIter != PointPatchConstructorTablePtr_->end())
		{
			return autoPtr<PatchField<Type> >
				(
					patchTypeCstrIter()
					(
						pf.patch(),
						DimensionedField<Type, Mesh>::null()
						)
					);
		}
		else
		{
			return
				autoPtr
				<
				PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>
				>
				(
					new CalculatedPointPatchField
					<PatchField, Mesh, PointPatch, MatrixType, Type>
					(
						pf.patch(),
						DimensionedField<Type, Mesh>::null()
						)
					);
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //