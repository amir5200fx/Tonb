#include <ValuePointPatchField.hxx>

#include <PointPatchFieldMapper.hxx>

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
		void ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		checkFieldSize() const
	{
		if (size() != this->patch().size())
		{
			FatalErrorIn
			(
				"void ValuePointPatchField<PatchField, Mesh, PointPatch, "
				"MatrixType, Type>::checkField() const"
			) << "field does not correspond to patch. " << endl
				<< "Field size: " << size() << " patch size: "
				<< this->patch().size()
				<< abort(FatalError);
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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ValuePointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		PatchField<Type>(p, iF),
		Field<Type>(p.size(), pTraits<Type>::zero)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ValuePointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const dictionary& dict
		)
		:
		PatchField<Type>(p, iF),
		Field<Type>("value", dict, p.size())
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ValuePointPatchField
		(
			const ValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const PointPatchFieldMapper& mapper
		)
		:
		PatchField<Type>(p, iF),
		Field<Type>(ptf, mapper)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ValuePointPatchField
		(
			const ValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
		)
		:
		PatchField<Type>(ptf),
		Field<Type>(ptf)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		ValuePointPatchField
		(
			const ValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		PatchField<Type>(ptf, iF),
		Field<Type>(ptf)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Map and resize from self given a mapper
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::autoMap
		(
			const PointPatchFieldMapper& m
		)
	{
		Field<Type>::autoMap(m);
	}


	// Grab the values using rmap
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::rmap
		(
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const labelList& addr
		)
	{
		Field<Type>::rmap
		(
			refCast
			<
			const ValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>
			>(ptf),
			addr
		);
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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		updateCoeffs()
	{
		if (this->updated())
		{
			return;
		}

		if (this->isPointField())
		{
			// Get value
			const Field<Type>& values = *this;

			// Get internal field to insert values into
			Field<Type>& iF = const_cast<Field<Type>&>(this->internalField());

			this->setInInternalField(iF, values);
		}

		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
			updateCoeffs();
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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::evaluate
		(
			const Pstream::commsTypes commsType
		)
	{
		// Evaluate boundary condition
		this->updateBoundaryField();

		if (this->isPointField())
		{
			// Get value
			const Field<Type>& values = *this;

			// Get internal field to insert values into
			Field<Type>& iF = const_cast<Field<Type>&>(this->internalField());

			this->setInInternalField(iF, values);
		}

		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::evaluate
		(commsType);
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		write(Ostream& os) const
	{
		PatchField<Type>::write(os);
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		operator=
		(
			const ValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
			)
	{
		Field<Type>::operator=(ptf);
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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::operator=
		(
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
			)
	{
		Field<Type>::operator=(ptf.patchInternalField());
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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::operator=
		(
			const Field<Type>& tf
			)
	{
		Field<Type>::operator=(tf);
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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		operator=
		(
			const Type& t
			)
	{
		Field<Type>::operator=(t);
	}


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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		operator==
		(
			const ValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
			)
	{
		Field<Type>::operator=(ptf);
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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::operator==
		(
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
			)
	{
		Field<Type>::operator=(ptf.patchInternalField());
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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		operator==
		(
			const Field<Type>& tf
			)
	{
		Field<Type>::operator=(tf);
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
		ValuePointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		operator==
		(
			const Type& t
			)
	{
		Field<Type>::operator=(t);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //