#include <lduMatrix.hxx>

#include <IPstream.hxx>
#include <OPstream.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::lduMatrix::initMatrixInterfaces
(
	const FieldField<Field, scalar>& coupleCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const scalarField& psiif,
	scalarField& result,
	const direction cmpt,
	const bool switchToLhs
) const
{
	if
		(
			Pstream::defaultComms() == Pstream::blocking
			|| Pstream::defaultComms() == Pstream::nonBlocking
			)
	{
		forAll(interfaces, interfaceI)
		{
			if (interfaces.set(interfaceI))
			{
				interfaces[interfaceI].initInterfaceMatrixUpdate
				(
					psiif,
					result,
					*this,
					coupleCoeffs[interfaceI],
					cmpt,
					Pstream::defaultComms(),
					switchToLhs
				);
			}
		}
	}
	else if (Pstream::defaultComms() == Pstream::scheduled)
	{
		const lduSchedule& patchSchedule = this->patchSchedule();

		// Loop over the "global" patches are on the list of interfaces but
		// beyond the end of the schedule which only handles "normal" patches
		for
			(
				label interfaceI = patchSchedule.size() / 2;
				interfaceI < interfaces.size();
				interfaceI++
				)
		{
			if (interfaces.set(interfaceI))
			{
				interfaces[interfaceI].initInterfaceMatrixUpdate
				(
					psiif,
					result,
					*this,
					coupleCoeffs[interfaceI],
					cmpt,
					Pstream::blocking,
					switchToLhs
				);
			}
		}
	}
	else
	{
		FatalErrorIn("lduMatrix::initMatrixInterfaces")
			<< "Unsuported communications type "
			<< Pstream::commsTypeNames[Pstream::defaultCommsType()]
			<< exit(FatalError);
	}
}


void tnbLib::lduMatrix::updateMatrixInterfaces
(
	const FieldField<Field, scalar>& coupleCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const scalarField& psiif,
	scalarField& result,
	const direction cmpt,
	const bool switchToLhs
) const
{
	if (Pstream::defaultComms() == Pstream::blocking)
	{
		forAll(interfaces, interfaceI)
		{
			if (interfaces.set(interfaceI))
			{
				interfaces[interfaceI].updateInterfaceMatrix
				(
					psiif,
					result,
					*this,
					coupleCoeffs[interfaceI],
					cmpt,
					Pstream::defaultComms(),
					switchToLhs
				);
			}
		}
	}
	else if (Pstream::defaultComms() == Pstream::nonBlocking)
	{
		// FOAM-3.1 implementation

		// Block until all sends/receives have been finished
		IPstream::waitRequests();
		OPstream::waitRequests();

		forAll(interfaces, interfaceI)
		{
			if (interfaces.set(interfaceI))
			{
				interfaces[interfaceI].updateInterfaceMatrix
				(
					psiif,
					result,
					*this,
					coupleCoeffs[interfaceI],
					cmpt,
					Pstream::defaultComms(),
					switchToLhs
				);
			}
		}
	}
	else if (Pstream::defaultComms() == Pstream::scheduled)
	{
		const lduSchedule& patchSchedule = this->patchSchedule();

		// Loop over all the "normal" interfaces relating to standard patches
		forAll(patchSchedule, i)
		{
			label interfaceI = patchSchedule[i].patch;

			if (interfaces.set(interfaceI))
			{
				if (patchSchedule[i].init)
				{
					interfaces[interfaceI].initInterfaceMatrixUpdate
					(
						psiif,
						result,
						*this,
						coupleCoeffs[interfaceI],
						cmpt,
						Pstream::scheduled,
						switchToLhs
					);
				}
				else
				{
					interfaces[interfaceI].updateInterfaceMatrix
					(
						psiif,
						result,
						*this,
						coupleCoeffs[interfaceI],
						cmpt,
						Pstream::scheduled,
						switchToLhs
					);
				}
			}
		}

		// Loop over the "global" patches are on the list of interfaces but
		// beyond the end of the schedule which only handles "normal" patches
		for
			(
				label interfaceI = patchSchedule.size() / 2;
				interfaceI < interfaces.size();
				interfaceI++
				)
		{
			if (interfaces.set(interfaceI))
			{
				interfaces[interfaceI].updateInterfaceMatrix
				(
					psiif,
					result,
					*this,
					coupleCoeffs[interfaceI],
					cmpt,
					Pstream::blocking,
					switchToLhs
				);
			}
		}
	}
	else
	{
		FatalErrorIn("lduMatrix::updateMatrixInterfaces")
			<< "Unsuported communications type "
			<< Pstream::commsTypeNames[Pstream::defaultCommsType()]
			<< exit(FatalError);
	}
}


// ************************************************************************* //