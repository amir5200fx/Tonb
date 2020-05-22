#include <fanFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <IOmanip.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	fanFvPatchField<Type>::fanFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		jumpCyclicFvPatchField<Type>(p, iF),
		f_(0),
		jump_(this->size() / 2, 0.0)
	{}


	template<class Type>
	fanFvPatchField<Type>::fanFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		jumpCyclicFvPatchField<Type>(p, iF),
		f_(),
		jump_(this->size() / 2, 0.0)
	{
		{
			Istream& is = dict.lookup("f");
			is.format(IOstream::ASCII);
			is >> f_;
		}

		if (dict.found("value"))
		{
			fvPatchField<Type>::operator=
				(
					Field<Type>("value", dict, p.size())
					);
		}
		else
		{
			this->evaluate(Pstream::blocking);
		}
	}


	template<class Type>
	fanFvPatchField<Type>::fanFvPatchField
	(
		const fanFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		jumpCyclicFvPatchField<Type>(ptf, p, iF, mapper),
		f_(ptf.f_),
		jump_(ptf.jump_, mapper)
	{}


	template<class Type>
	fanFvPatchField<Type>::fanFvPatchField
	(
		const fanFvPatchField<Type>& ptf
	)
		:
		cyclicLduInterfaceField(),
		jumpCyclicFvPatchField<Type>(ptf),
		f_(ptf.f_),
		jump_(ptf.jump_)
	{}


	template<class Type>
	fanFvPatchField<Type>::fanFvPatchField
	(
		const fanFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		jumpCyclicFvPatchField<Type>(ptf, iF),
		f_(ptf.f_),
		jump_(ptf.jump_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void fanFvPatchField<Type>::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		jumpCyclicFvPatchField<Type>::autoMap(m);

		// Jump is half size. Expand to full size, map and truncate.
		if (jump_.size() > 0 && jump_.size() == this->size() / 2)
		{
			label oldSize = jump_.size();
			jump_.setSize(this->size());

			for (label i = oldSize; i < jump_.size(); i++)
			{
				jump_[i] = jump_[i - oldSize];
			}

			jump_.autoMap(m);
			jump_.setSize(oldSize);
		}
	}


	template<class Type>
	void fanFvPatchField<Type>::rmap
	(
		const fvPatchField<Type>& ptf,
		const labelList& addr
	)
	{
		jumpCyclicFvPatchField<Type>::rmap(ptf, addr);

		// Jump is half size. Expand to full size, map and truncate.
		if (jump_.size() > 0 && jump_.size() == this->size() / 2)
		{
			label oldSize = jump_.size();
			jump_.setSize(this->size());

			for (label i = oldSize; i < jump_.size(); i++)
			{
				jump_[i] = jump_[i - oldSize];
			}

			const fanFvPatchField<Type>& tiptf =
				refCast<const fanFvPatchField<Type> >(ptf);

			jump_.rmap(tiptf.jump_, addr);

			jump_.setSize(oldSize);
		}
	}


	template<class Type>
	void fanFvPatchField<Type>::write(Ostream& os) const
	{
		fvPatchField<Type>::write(os);
		os.writeKeyword("patchType")
			<< cyclicFvPatch::typeName << token::END_STATEMENT << nl;

		IOstream::streamFormat fmt0 = os.format(IOstream::ASCII);
		os.writeKeyword("f") << f_ << token::END_STATEMENT << nl;
		os.format(fmt0);

		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //