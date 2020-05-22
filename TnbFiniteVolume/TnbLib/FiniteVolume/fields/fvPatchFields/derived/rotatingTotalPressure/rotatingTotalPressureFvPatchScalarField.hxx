#pragma once
#ifndef _rotatingTotalPressureFvPatchScalarField_Header
#define _rotatingTotalPressureFvPatchScalarField_Header

#include <totalPressureFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class rotatingTotalPressureFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class rotatingTotalPressureFvPatchScalarField
		:
		public totalPressureFvPatchScalarField
	{
		// Private data

			//- Angular velocity of the frame
		vector omega_;


	public:

		//- Runtime type information
		TypeName("rotatingTotalPressure");


		// Constructors

			//- Construct from patch and internal field
		rotatingTotalPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		rotatingTotalPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given rotatingTotalPressureFvPatchScalarField
		//  onto a new patch
		rotatingTotalPressureFvPatchScalarField
		(
			const rotatingTotalPressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		rotatingTotalPressureFvPatchScalarField
		(
			const rotatingTotalPressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new rotatingTotalPressureFvPatchScalarField(*this)
					);
		}

		//- Construct as copy setting internal field reference
		rotatingTotalPressureFvPatchScalarField
		(
			const rotatingTotalPressureFvPatchScalarField&,
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
					new rotatingTotalPressureFvPatchScalarField(*this, iF)
					);
		}


		// Member functions

			// Access

				//- Return the angular velocity of rotation
		const vector& omega() const
		{
			return omega_;
		}

		//- Return the angular velocity of rotation
		vector& omega()
		{
			return omega_;
		}


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_rotatingTotalPressureFvPatchScalarField_Header
