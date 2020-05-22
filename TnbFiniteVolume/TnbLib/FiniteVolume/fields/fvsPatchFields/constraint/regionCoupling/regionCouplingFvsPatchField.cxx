#include <regionCouplingFvsPatchField.hxx>

#include <fvPatchField.hxx>
#include <volMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	template<class Type>
	const tnbLib::Field<Type>& regionCouplingFvsPatchField<Type>::originalPatchField() const
	{
		if (curTimeIndex_ != this->db().time().timeIndex())
		{
			// Store original field for symmetric evaluation
			// Henrik Rusche, Aug/2011

			originalPatchField_ = *this;
			curTimeIndex_ = this->db().time().timeIndex();
		}

		return originalPatchField_;
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	regionCouplingFvsPatchField<Type>::regionCouplingFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(p, iF),
		regionCouplePatch_(refCast<const regionCoupleFvPatch>(p)),
		remoteFieldName_(),
		matrixUpdateBuffer_()
	{}


	template<class Type>
	regionCouplingFvsPatchField<Type>::regionCouplingFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		coupledFvsPatchField<Type>(p, iF, dict),
		regionCouplePatch_(refCast<const regionCoupleFvPatch>(p)),
		remoteFieldName_(dict.lookup("remoteField")),
		matrixUpdateBuffer_()
	{
		if (!isType<regionCoupleFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"regionCouplingFvsPatchField<Type>::regionCouplingFvsPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, surfaceMesh>& iF,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not regionCouple type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	regionCouplingFvsPatchField<Type>::regionCouplingFvsPatchField
	(
		const regionCouplingFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		coupledFvsPatchField<Type>(ptf, p, iF, mapper),
		regionCouplePatch_(refCast<const regionCoupleFvPatch>(p)),
		remoteFieldName_(ptf.remoteFieldName_),
		matrixUpdateBuffer_()
	{
		if (!isType<regionCoupleFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"regionCouplingFvsPatchField<Type>::regionCouplingFvsPatchField\n"
				"(\n"
				"    const regionCouplingFvsPatchField<Type>& ptf,\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, surfaceMesh>& iF,\n"
				"    const fvPatchFieldMapper& mapper\n"
				")\n"
			) << "Field type does not correspond to patch type for patch "
				<< this->patch().index() << "." << endl
				<< "Field type: " << typeName << endl
				<< "Patch type: " << this->patch().type()
				<< exit(FatalError);
		}
	}


	template<class Type>
	regionCouplingFvsPatchField<Type>::regionCouplingFvsPatchField
	(
		const regionCouplingFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(ptf, iF),
		regionCouplePatch_(refCast<const regionCoupleFvPatch>(ptf.patch())),
		remoteFieldName_(ptf.remoteFieldName_),
		matrixUpdateBuffer_()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Return a named shadow patch field
	template<class Type>
	template<class LookupField, class LookupType>
	const typename LookupField::PatchFieldType&
		regionCouplingFvsPatchField<Type>::lookupShadowPatchField
		(
			const word& name,
			const LookupField*,
			const LookupType*
		) const
	{
		// Lookup neighbour field
		const LookupField& shadowField =
			regionCouplePatch_.shadowRegion().
			objectRegistry::template lookupObject<LookupField>(name);

		return shadowField.boundaryField()[regionCouplePatch_.shadowIndex()];
	}


	// Return shadow patch field
	template<class Type>
	const regionCouplingFvsPatchField<Type>&
		regionCouplingFvsPatchField<Type>::shadowPatchField() const
	{
		// Lookup neighbour field
		typedef GeometricField<Type, fvPatchField, volMesh> GeoField;

		return refCast<const regionCouplingFvsPatchField<Type> >
			(
				lookupShadowPatchField<GeoField, Type>(remoteFieldName_)
				);
	}


	// Write
	template<class Type>
	void regionCouplingFvsPatchField<Type>::write(Ostream& os) const
	{
		fvsPatchField<Type>::write(os);
		os.writeKeyword("remoteField")
			<< remoteFieldName_ << token::END_STATEMENT << nl;
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
