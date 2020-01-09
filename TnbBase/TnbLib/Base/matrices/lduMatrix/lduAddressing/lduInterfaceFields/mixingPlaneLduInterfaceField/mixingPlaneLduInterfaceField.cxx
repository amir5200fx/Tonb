#include <mixingPlaneLduInterfaceField.hxx>

#include <diagTensorField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mixingPlaneLduInterfaceField, 0);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::mixingPlaneLduInterfaceField::~mixingPlaneLduInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mixingPlaneLduInterfaceField::transformCoupleField
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