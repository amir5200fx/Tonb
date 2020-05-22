//#include <basicSymmetryFvPatchField.hxx>
//
//#include <volFields.hxx>
//#include <transformField.hxx>
//
//// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//
//namespace tnbLib
//{
//
//	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//	template<>
//	tmp<scalarField > basicSymmetryFvPatchField<scalar>::snGrad() const
//	{
//		return tmp<scalarField>(new scalarField(size(), scalar(0)));
//	}
//
//
//	// Note:
//	// Skew correction and second order is currently handled in template
//	// specialisations because
//	// Note 2: Currently repeated code in evaluate after typedefs.
//	// Refactor.  HJ, 18/Mar/2015
//	template<>
//	void basicSymmetryFvPatchField<scalar>::evaluate(const Pstream::commsTypes)
//	{
//		// Local typedefs
//		typedef scalar Type;
//		typedef outerProduct<vector, Type>::type gradType;
//		typedef GeometricField<gradType, tnbLib::fvPatchField, volMesh>
//			gradFieldType;
//
//		if (!updated())
//		{
//			updateCoeffs();
//		}
//
//		vectorField nHat = this->patch().nf();
//
//		// Get patch internal field
//		Field<Type> pif = this->patchInternalField();
//
//		// Skew corrected treatment
//		if (skewCorrected_)
//		{
//			// Access the gradient
//			const word DName = this->dimensionedInternalField().name();
//			const word gradDName("grad(" + DName + ")");
//
//			if (!this->db().foundObject<gradFieldType>(gradDName))
//			{
//				InfoIn
//				(
//					"void basicSymmetryFvPatchField<Type>::"
//					"evaluate(const Pstream::commsTypes)"
//				) << "Cannot access " << gradDName << " field for field "
//					<< DName << " for patch " << this->patch().name()
//					<< ".  Evaluating without skew correction"
//					<< endl;
//			}
//			else
//			{
//				// Calculate skew correction vector k
//				vectorField delta = patch().delta();
//				vectorField k = delta - nHat * (nHat&delta);
//
//				// Get gradient
//				const fvPatchField<gradType>& gradD =
//					patch().lookupPatchField<gradFieldType, gradType>(gradDName);
//
//				// Correct cell value for k
//				pif += (k & gradD.patchInternalField());
//
//				if (secondOrder_)
//				{
//					Field<Type> nGradD = (nHat & gradD.patchInternalField());
//
//					Field<Type>::operator=
//						(
//							transform
//							(
//								I - sqr(nHat),
//								pif + 0.5*nGradD / this->patch().deltaCoeffs()
//							)
//							);
//
//					// Return, skew corrected, second order
//					transformFvPatchField<Type>::evaluate();
//					return;
//				}
//				else
//				{
//					Field<Type>::operator=
//						(
//							0.5*(pif + transform(I - 2.0*sqr(nHat), pif))
//							);
//
//					// Return, skew corrected without second order correction
//					transformFvPatchField<Type>::evaluate();
//					return;
//				}
//			}
//		}
//
//		// Without skew correction
//		Field<Type>::operator=
//			(
//				0.5*(pif + transform(I - 2.0*sqr(nHat), pif))
//				);
//
//		transformFvPatchField<Type>::evaluate();
//	}
//
//
//	template<>
//	tmp<vectorField> basicSymmetryFvPatchField<vector>::snGrad() const
//	{
//		// Local typedefs
//		typedef vector Type;
//		typedef outerProduct<vector, Type>::type gradType;
//		typedef GeometricField<gradType, tnbLib::fvPatchField, volMesh>
//			gradFieldType;
//
//		vectorField nHat = this->patch().nf();
//
//		// Get patch internal field
//		Field<Type> pif = this->patchInternalField();
//
//		// Skew corrected treatment
//		if (skewCorrected_)
//		{
//			// Access the gradient
//			const word DName = this->dimensionedInternalField().name();
//			const word gradDName("grad(" + DName + ")");
//
//			if (!this->db().foundObject<gradFieldType>(gradDName))
//			{
//				InfoIn
//				(
//					"void basicSymmetryFvPatchField<Type>::snGrad() const"
//				) << "Cannot access " << gradDName << " field for field "
//					<< DName << " for patch " << this->patch().name()
//					<< ".  Evaluating without skew correction"
//					<< endl;
//			}
//			else
//			{
//				// Calculate skew correction vector k
//				vectorField delta = patch().delta();
//				vectorField k = delta - nHat * (nHat&delta);
//
//				// Get gradient
//				const fvPatchField<gradType>& gradD =
//					patch().lookupPatchField<gradFieldType, gradType>(gradDName);
//
//				// Correct cell value for k
//				pif += (k & gradD.patchInternalField());
//
//				if (secondOrder_)
//				{
//					Field<Type> nGradD = (nHat & gradD.patchInternalField());
//
//					// Return, skew corrected, second order
//					return 2 *
//						(
//							transform(I - 2.0*sqr(nHat), pif) - pif
//							)*(this->patch().deltaCoeffs() / 2.0)
//						- transform(sqr(nHat), nGradD);
//				}
//				else
//				{
//					// Return, skew corrected, without second order correction
//					return
//						(
//							transform(I - 2.0*sqr(nHat), pif) - pif
//							)*(this->patch().deltaCoeffs() / 2.0);
//				}
//			}
//		}
//
//		// Without skew correction
//		return
//			(
//				transform(I - 2.0*sqr(nHat), pif) - pif
//				)*(this->patch().deltaCoeffs() / 2.0);
//	}
//
//
//	template<>
//	void basicSymmetryFvPatchField<vector>::evaluate(const Pstream::commsTypes)
//	{
//		// Local typedefs
//		typedef vector Type;
//		typedef outerProduct<vector, Type>::type gradType;
//		typedef GeometricField<gradType, tnbLib::fvPatchField, volMesh>
//			gradFieldType;
//
//		if (!updated())
//		{
//			updateCoeffs();
//		}
//
//		if (!updated())
//		{
//			updateCoeffs();
//		}
//
//		vectorField nHat = this->patch().nf();
//
//		// Get patch internal field
//		Field<Type> pif = this->patchInternalField();
//
//		// Skew corrected treatment
//		if (skewCorrected_)
//		{
//			// Access the gradient
//			const word DName = this->dimensionedInternalField().name();
//			const word gradDName("grad(" + DName + ")");
//
//			if (!this->db().foundObject<gradFieldType>(gradDName))
//			{
//				InfoIn
//				(
//					"void basicSymmetryFvPatchField<Type>::"
//					"evaluate(const Pstream::commsTypes)"
//				) << "Cannot access " << gradDName << " field for field "
//					<< DName << " for patch " << this->patch().name()
//					<< ".  Evaluating without skew correction"
//					<< endl;
//			}
//			else
//			{
//				// Calculate skew correction vector k
//				vectorField delta = patch().delta();
//				vectorField k = delta - nHat * (nHat&delta);
//
//				// Get gradient
//				const fvPatchField<gradType>& gradD =
//					patch().lookupPatchField<gradFieldType, gradType>(gradDName);
//
//				// Correct cell value for k
//				pif += (k & gradD.patchInternalField());
//
//				if (secondOrder_)
//				{
//					Field<Type> nGradD = (nHat & gradD.patchInternalField());
//
//					Field<Type>::operator=
//						(
//							transform
//							(
//								I - sqr(nHat),
//								pif + 0.5*nGradD / this->patch().deltaCoeffs()
//							)
//							);
//
//					// Return, skew corrected, second order
//					transformFvPatchField<Type>::evaluate();
//					return;
//				}
//				else
//				{
//					Field<Type>::operator=
//						(
//							0.5*(pif + transform(I - 2.0*sqr(nHat), pif))
//							);
//
//					// Return, skew corrected without second order correction
//					transformFvPatchField<Type>::evaluate();
//					return;
//				}
//			}
//		}
//
//		// Without skew correction
//		Field<Type>::operator=
//			(
//				0.5*(pif + transform(I - 2.0*sqr(nHat), pif))
//				);
//
//		transformFvPatchField<Type>::evaluate();
//	}
//
//
//	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//
//} // End namespace tnbLib
//
//// ************************************************************************* //