#include <cyclicLduInterfaceField.hxx>

#include <diagTensorField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicLduInterfaceField, 0);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicLduInterfaceField::~cyclicLduInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cyclicLduInterfaceField::transformCoupleField
(
	scalarField& pnf,
	const direction cmpt
) const
{
	if (doTransform())
	{
		label sizeby2 = pnf.size() / 2;

		//HJ This is wrong
		// For a vector, the implicit contribution is correct:
		// power of diagonal of the transformation tensor for the vector
		// For a tensor this is wrong: the diag of transformation tensor
		// is a vector and I am asking for a component cmpt which corresponds
		// to the component of the variable I am offering.  If the variable
		// is a tensor, it has got 6 or 9 components, so the component
		// access is out of range and rubbish anyway
		// The forwardScale/reverseScale should be the power of the complete
		// transformation matrix for a tensor.  Something like:

//         Type powTransform = transform(pTraits<Type>::one);
//         forwardScale = pow(powTransform.component(cmpt), rank());

		// This needs to be moved under templating into cyclicFvPatchField
		// because it requires access to Type
		// HJ, 3/Sep/2015

		scalar forwardScale =
			pow(diag(forwardT()[0]).component(cmpt), rank());

		scalar reverseScale =
			pow(diag(reverseT()[0]).component(cmpt), rank());

		for (label facei = 0; facei < sizeby2; facei++)
		{
			pnf[facei] *= forwardScale;
			pnf[facei + sizeby2] *= reverseScale;
		}
	}
}


// ************************************************************************* //