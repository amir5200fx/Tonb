#include <FixedValuePointPatchField.hxx>

#include <boolList.hxx>
#include <Map.hxx>

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
		FixedValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		FixedValuePointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		FixedValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		FixedValuePointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const dictionary& dict
		)
		:
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>
		(p, iF, dict)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		FixedValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		FixedValuePointPatchField
		(
			const FixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const PointPatchFieldMapper& mapper
		)
		:
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>
		(ptf, p, iF, mapper)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		FixedValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		FixedValuePointPatchField
		(
			const FixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
		)
		:
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>(ptf)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		FixedValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		FixedValuePointPatchField
		(
			const FixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>
		(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Set boundary condition to matrix
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		FixedValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		setBoundaryCondition
		(
			Map<typename MatrixType<Type>::ConstraintType>& fix
		) const
	{
		const Field<Type>& values = *this;

		// get addressing
		const labelList& meshPoints = this->patch().meshPoints();

		forAll(meshPoints, pointI)
		{
			const label curPoint = meshPoints[pointI];

			// create a constraint
			typename MatrixType<Type>::ConstraintType bc
			(
				curPoint,
				values[pointI],
				pTraits<Type>::one
			);

			// If not set add it, otherwise combine with
			// already existing value
			if (!fix.found(curPoint))
			{
				fix.insert(curPoint, bc);
			}
			else
			{
				fix[curPoint].combine(bc);
			}
		}
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	// Force an assignment
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		FixedValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>
		::operator==
		(
			const ValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
			)
	{
		Field<Type>::operator=(ptf);

		// Insert the result into the internal field
		initEvaluate();
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		FixedValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>
		::operator==
		(
			const Field<Type>& tf
			)
	{
		Field<Type>::operator=(tf);

		// insert the result into the internal field
		initEvaluate();
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		FixedValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		operator==
		(
			const Type& t
			)
	{
		Field<Type>::operator=(t);

		// Insert the result into the internal field
		initEvaluate();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //