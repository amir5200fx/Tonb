#include <wedgeFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	wedgeFvsPatchField<Type>::wedgeFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(p, iF)
	{}


	template<class Type>
	wedgeFvsPatchField<Type>::wedgeFvsPatchField
	(
		const wedgeFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fvsPatchField<Type>(ptf, p, iF, mapper)
	{
		if (!isType<wedgeFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"wedgeFvsPatchField<Type>::wedgeFvsPatchField\n"
				"(\n"
				"    const wedgeFvsPatchField<Type>& ptf,\n"
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
	wedgeFvsPatchField<Type>::wedgeFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		fvsPatchField<Type>(p, iF, dict)
	{
		if (!isType<wedgeFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"wedgeFvsPatchField<Type>::wedgeFvsPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const Field<Type>& field,\n"
				"    dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not wedge type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	wedgeFvsPatchField<Type>::wedgeFvsPatchField
	(
		const wedgeFvsPatchField<Type>& ptf
	)
		:
		fvsPatchField<Type>(ptf)
	{}


	template<class Type>
	wedgeFvsPatchField<Type>::wedgeFvsPatchField
	(
		const wedgeFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Write
	template<class Type>
	void wedgeFvsPatchField<Type>::write(Ostream& os) const
	{
		fvsPatchField<Type>::write(os);
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //