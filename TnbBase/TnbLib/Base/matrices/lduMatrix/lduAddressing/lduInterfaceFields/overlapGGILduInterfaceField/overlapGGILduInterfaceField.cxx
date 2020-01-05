#include <overlapGGILduInterfaceField.hxx>

#include <diagTensorField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(overlapGGILduInterfaceField, 0);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::overlapGGILduInterfaceField::~overlapGGILduInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::overlapGGILduInterfaceField::transformCoupleField
(
	scalarField& pnf,
	const direction cmpt
) const
{
	if (doTransform())
	{
		if (forwardT().size() == 1)
		{
			pnf *= pow(diag(forwardT()[0]).component(cmpt), rank());
		}
		else
		{
			pnf *= pow(diag(forwardT())().component(cmpt), rank());
		}
	}
}


// ************************************************************************* //