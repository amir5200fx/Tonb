#pragma once
#ifndef _timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField_Header
#define _timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField_Header

#include <timeVaryingMappedFixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		Class timeVaryingMappedPressureDirectedInletVelocityFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField
		:
		public timeVaryingMappedFixedValueFvPatchVectorField
	{
		// Private data

		word phiName_;
		word rhoName_;


	public:

		//- Runtime type information
		TypeName("timeVaryingMappedPressureDirectedInletVelocity");


		// Constructors

			//- Construct from patch and internal field
		timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField
		//  onto a new patch
		timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField
		(
			const timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField
		(
			const timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new
					timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField
					(
						*this
					)
					);
		}

		//- Construct as copy setting internal field reference
		timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField
		(
			const timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchVectorField> clone
		(
			const DimensionedField<vector, volMesh>& iF
		) const
		{
			return tmp<fvPatchVectorField>
				(
					new
					timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField
					(
						*this,
						iF
					)
					);
		}


		// Member functions

			// Access

				//- Return the name of rho
		const word& rhoName() const
		{
			return rhoName_;
		}

		//- Return reference to the name of rho to allow adjustment
		word& rhoName()
		{
			return rhoName_;
		}

		//- Return the name of phi
		const word& phiName() const
		{
			return phiName_;
		}

		//- Return reference to the name of phi to allow adjustment
		word& phiName()
		{
			return phiName_;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
		virtual void autoMap
		(
			const fvPatchFieldMapper&
		);

		//- Reverse map the given fvPatchField onto this fvPatchField
		virtual void rmap
		(
			const fvPatchVectorField&,
			const labelList&
		);


		//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();

		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_timeVaryingMappedPressureDirectedInletVelocityFvPatchVectorField_Header
