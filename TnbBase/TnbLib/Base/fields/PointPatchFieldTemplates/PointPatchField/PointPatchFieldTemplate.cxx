#include <PointPatchFieldTemplate.hxx>

#include <dictionary.hxx>
#include <Pstream.hxx>

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
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::PointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		patch_(p),
		internalField_(iF),
		updated_(false)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::PointPatchField
		(
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
		)
		:
		patch_(ptf.patch_),
		internalField_(ptf.internalField_),
		updated_(false)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::PointPatchField
		(
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		patch_(ptf.patch_),
		internalField_(iF),
		updated_(false)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Return objectRegistry
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		const objectRegistry&
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::db() const
	{
		//HR 12.3.10: Lookup fields from the field DB rather than the mesh
		return internalField_.db();
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
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		write
		(
			Ostream& os
		) const
	{
		os.writeKeyword("type") << type() << token::END_STATEMENT << nl;
	}


	// Return field created from appropriate internal field values
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		tmp<Field<Type> >
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		patchInternalField() const
	{
		return patchInternalField(internalField());
	}


	// Return field created from appropriate internal field values
	// given the internal field
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		template<class Type1>
	tmp<Field<Type1> >
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		patchInternalField
		(
			const Field<Type1>& iF
		) const
	{
		// Check size
		if (iF.size() != internalField().size())
		{
			FatalErrorIn
			(
				"tmp<Field<Type1> > PointPatchField<PatchField, PointPatch, "
				"Type>::"
				"patchInternalField(const Field<Type1>& iF) const"
			) << "given internal field does not correspond to the mesh. "
				<< "Field size: " << iF.size()
				<< " mesh size: " << internalField().size()
				<< abort(FatalError);
		}

		// get addressing
		const labelList& meshPoints = patch().meshPoints();

		tmp<Field<Type1> > tvalues(new Field<Type1>(meshPoints.size()));
		Field<Type1>& values = tvalues();

		forAll(meshPoints, pointI)
		{
			values[pointI] = iF[meshPoints[pointI]];
		}

		return tvalues;
	}


	// Does this patchField correspond to a pointTypeField
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		bool PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		isPointField() const
	{
		return
			internalField().size()
			== patch().boundaryMesh().mesh().nPoints();
	}

	// Does this patchField correspond to a pointTypeField
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		checkPointField() const
	{
		if (!isPointField())
		{
			FatalErrorIn
			(
				"void PointPatchField<PatchField, Mesh, PointPatch, "
				"MatrixType, Type>::checkPointField() const"
			) << "This " << type() << " patchField"
				<< " is not part of a pointTypeField which may cause "
				<< "undefined behaviour from the evaluate and other functions"
				<< abort(FatalError);
		}
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		template<class Type1>
	void PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		addToInternalField
		(
			Field<Type1>& iF,
			const Field<Type1>& pF
		) const
	{
		// Check size
		if (iF.size() != internalField().size())
		{
			FatalErrorIn
			(
				"void PointPatchField<PatchField, Mesh, PointPatch, "
				"MatrixType, Type>::addToInternalField("
				"Field<Type1>& iF, const Field<Type1>& iF) const"
			) << "given internal field does not correspond to the mesh. "
				<< "Field size: " << iF.size()
				<< " mesh size: " << internalField().size()
				<< abort(FatalError);
		}

		if (pF.size() != size())
		{
			FatalErrorIn
			(
				"void PointPatchField<PatchField, Mesh, PointPatch, "
				"MatrixType, Type>::addToInternalField("
				"Field<Type1>& iF, const Field<Type1>& iF) const"
			) << "given patch field does not correspond to the mesh. "
				<< "Field size: " << pF.size()
				<< " mesh size: " << size()
				<< abort(FatalError);
		}

		// Get the addressing
		const labelList& mp = patch().meshPoints();

		forAll(mp, pointI)
		{
			iF[mp[pointI]] += pF[pointI];
		}
	}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		template<class Type1>
	void PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::
		setInInternalField
		(
			Field<Type1>& iF,
			const Field<Type1>& pF
		) const
	{
		// Check size
		if (iF.size() != internalField().size())
		{
			FatalErrorIn
			(
				"void PointPatchField<PatchField, Mesh, PointPatch, "
				"MatrixType, Type>::setInInternalField("
				"Field<Type1>& iF, const Field<Type1>& iF) const"
			) << "given internal field does not correspond to the mesh. "
				<< "Field size: " << iF.size()
				<< " mesh size: " << internalField().size()
				<< abort(FatalError);
		}

		if (pF.size() != size())
		{
			FatalErrorIn
			(
				"void PointPatchField<PatchField, Mesh, PointPatch, "
				"MatrixType, Type>::setInInternalField("
				"Field<Type1>& iF, const Field<Type1>& iF) const"
			) << "given patch field does not correspond to the mesh. "
				<< "Field size: " << pF.size()
				<< " mesh size: " << size()
				<< abort(FatalError);
		}

		// Get the addressing
		const labelList& mp = patch().meshPoints();

		forAll(mp, pointI)
		{
			iF[mp[pointI]] = pF[pointI];
		}
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
		PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>::evaluate
		(
			const Pstream::commsTypes commsType
		)
	{
		if (!updated_)
		{
			this->updateCoeffs();
		}

		updated_ = false;
	}


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		Ostream& operator<<
		(
			Ostream& os,
			const PointPatchField<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
			)
	{
		ptf.write(os);

		os.check
		(
			"Ostream& operator<<"
			"(Ostream&, const PointPatchField<PatchField, PointPatch, "
			"MatrixType, Type>&"
		);

		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#    include <newPointPatchField.cxx>