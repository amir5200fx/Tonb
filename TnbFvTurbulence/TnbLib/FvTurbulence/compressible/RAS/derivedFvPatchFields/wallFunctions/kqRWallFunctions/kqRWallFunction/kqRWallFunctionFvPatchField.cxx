#include <kqRWallFunctionFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <wallFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{
		namespace RASModels
		{

			// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

			template<class Type>
			void kqRWallFunctionFvPatchField<Type>::checkType()
			{
				if (!this->patch().isWall())
				{
					FatalErrorIn("kqRWallFunctionFvPatchField::checkType()")
						<< "Invalid wall function specification" << nl
						<< "    Patch type for patch " << this->patch().name()
						<< " must be wall" << nl
						<< "    Current patch type is " << this->patch().type() << nl << endl
						<< abort(FatalError);
				}
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			template<class Type>
			kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
			(
				const fvPatch& p,
				const DimensionedField<Type, volMesh>& iF
			)
				:
				zeroGradientFvPatchField<Type>(p, iF)
			{
				checkType();
			}


			template<class Type>
			kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
			(
				const kqRWallFunctionFvPatchField& ptf,
				const fvPatch& p,
				const DimensionedField<Type, volMesh>& iF,
				const fvPatchFieldMapper& mapper
			)
				:
				zeroGradientFvPatchField<Type>(ptf, p, iF, mapper)
			{
				checkType();
			}


			template<class Type>
			kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
			(
				const fvPatch& p,
				const DimensionedField<Type, volMesh>& iF,
				const dictionary& dict
			)
				:
				zeroGradientFvPatchField<Type>(p, iF, dict)
			{
				checkType();
			}


			template<class Type>
			kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
			(
				const kqRWallFunctionFvPatchField& tkqrwfpf
			)
				:
				zeroGradientFvPatchField<Type>(tkqrwfpf)
			{
				checkType();
			}


			template<class Type>
			kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
			(
				const kqRWallFunctionFvPatchField& tkqrwfpf,
				const DimensionedField<Type, volMesh>& iF
			)
				:
				zeroGradientFvPatchField<Type>(tkqrwfpf, iF)
			{
				checkType();
			}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

			template<class Type>
			void kqRWallFunctionFvPatchField<Type>::evaluate
			(
				const Pstream::commsTypes commsType
			)
			{
				zeroGradientFvPatchField<Type>::evaluate(commsType);
			}


			template<class Type>
			void kqRWallFunctionFvPatchField<Type>::write(Ostream& os) const
			{
				zeroGradientFvPatchField<Type>::write(os);
				this->writeEntry("value", os);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //