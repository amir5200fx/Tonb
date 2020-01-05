#include <ggiLduInterfaceField.hxx>

#include <diagTensorField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ggiLduInterfaceField, 0);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ggiLduInterfaceField::~ggiLduInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::ggiLduInterfaceField::transformCoupleField
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