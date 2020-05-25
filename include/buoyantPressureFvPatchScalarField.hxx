#pragma once
#ifndef _buoyantPressureFvPatchScalarField_Header
#define _buoyantPressureFvPatchScalarField_Header

#include <fvPatchFields.hxx>
#include <fixedGradientFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				Class buoyantPressureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class buoyantPressureFvPatchScalarField
		:
		public fixedGradientFvPatchScalarField
	{
		// Private data

			//- Name of the density field used to calculate the buoyancy force
		word rhoName_;


	public:

		//- Runtime type information
		TypeName("buoyantPressure");


		// Constructors

			//- Construct from patch and internal field
		buoyantPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		buoyantPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  buoyantPressureFvPatchScalarField onto a new patch
		buoyantPressureFvPatchScalarField
		(
			const buoyantPressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		buoyantPressureFvPatchScalarField
		(
			const buoyantPressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new buoyantPressureFvPatchScalarField(*this)
					);
		}

		//- Construct as copy setting internal field reference
		buoyantPressureFvPatchScalarField
		(
			const buoyantPressureFvPatchScalarField&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchScalarField> clone
		(
			const DimensionedField<scalar, volMesh>& iF
		) const
		{
			return tmp<fvPatchScalarField>
				(
					new buoyantPressureFvPatchScalarField(*this, iF)
					);
		}


		// Member functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();

		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_buoyantPressureFvPatchScalarField_Header
