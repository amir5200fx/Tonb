#include <BasicSymmetryPointPatchField.hxx>

#include <transformField.hxx>
#include <Map.hxx>
#include <constraints.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		Type
		BasicSymmetryPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		fixFlagMatrix
		(
			const vector& nHat
		) const
	{
		Type fixFlag(pTraits<Type>::zero);

		if (pTraits<Type>::nComponents > 1)
		{
			Type implicitnessIndicator =
				pTraits<Type>::one
				- transform(I - nHat * nHat, pTraits<Type>::one);

			Type cmi = cmptMag(implicitnessIndicator);
			fixFlag = cmptMultiply(cmi, cmi);

			return fixFlag;
		}
		else
		{
			return pTraits<Type>::zero;
		}
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		BasicSymmetryPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		BasicSymmetryPointPatchField
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
		BasicSymmetryPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		BasicSymmetryPointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const dictionary& dict
		)
		:
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF)
	{
		updateBoundaryField();
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		BasicSymmetryPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		BasicSymmetryPointPatchField
		(
			const BasicSymmetryPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>&,
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const PointPatchFieldMapper&
		)
		:
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF)
	{
		updateBoundaryField();
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		BasicSymmetryPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		BasicSymmetryPointPatchField
		(
			const BasicSymmetryPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
		)
		:
		ValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(ptf)
	{
		updateBoundaryField();
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		BasicSymmetryPointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		BasicSymmetryPointPatchField
		(
			const BasicSymmetryPointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		ValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(ptf, iF)
	{
		updateBoundaryField();
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Evaluate patch field
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void BasicSymmetryPointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::updateBoundaryField()
	{
		if (this->isPointField())
		{
			Field<Type>& values = *this;

			tmp<Field<Type> > internalValues = this->patchInternalField();

			const vectorField& nHat = this->patch().pointNormals();

			values = transform(I - nHat * nHat, internalValues);
		}
	}


	// Set boundary condition to matrix
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void BasicSymmetryPointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		setBoundaryCondition
		(
			Map<typename MatrixType<Type>::ConstraintType>& fix
		) const
	{
		const Field<Type>& values = *this;

		// get addressing
		const labelList& meshPoints = this->patch().meshPoints();

		// get point normals
		const vectorField& nHat = this->patch().pointNormals();

		forAll(meshPoints, pointI)
		{
			const label curPoint = meshPoints[pointI];

			// create a constraint
			typename MatrixType<Type>::ConstraintType bc
			(
				curPoint,
				values[pointI],
				fixFlagMatrix(nHat[pointI])
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


	// Write
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void BasicSymmetryPointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		write(Ostream& os) const
	{
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::write(os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //