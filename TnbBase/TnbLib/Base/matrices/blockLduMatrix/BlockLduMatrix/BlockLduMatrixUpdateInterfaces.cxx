#include <BlockLduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::BlockLduMatrix<Type>::initInterfaces
(
	const FieldField<CoeffField, Type>& interfaceCoeffs,
	TypeField& result,
	const TypeField& psi,
	const bool switchToLhs
) const
{
	if
		(
			Pstream::defaultComms() == Pstream::blocking
			|| Pstream::defaultComms() == Pstream::nonBlocking
			)
	{
		forAll(interfaces_, interfaceI)
		{
			if (interfaces_.set(interfaceI))
			{
				interfaces_[interfaceI].initInterfaceMatrixUpdate
				(
					psi,
					result,
					*this,
					interfaceCoeffs[interfaceI],
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
				interfaceI < interfaces_.size();
				interfaceI++
				)
		{
			if (interfaces_.set(interfaceI))
			{
				interfaces_[interfaceI].initInterfaceMatrixUpdate
				(
					psi,
					result,
					*this,
					interfaceCoeffs[interfaceI],
					Pstream::blocking,
					switchToLhs
				);
			}
		}
	}
	else
	{
		FatalErrorIn("BlockLduMatrix<Type>::initMatrixInterfaces")
			<< "Unsuported communications type "
			<< Pstream::commsTypeNames[Pstream::defaultCommsType()]
			<< exit(FatalError);
	}
}


template<class Type>
void tnbLib::BlockLduMatrix<Type>::updateInterfaces
(
	const FieldField<CoeffField, Type>& interfaceCoeffs,
	TypeField& result,
	const TypeField& psi,
	const bool switchToLhs
) const
{
	if (Pstream::defaultComms() == Pstream::blocking)
	{
		forAll(interfaces_, interfaceI)
		{
			if (interfaces_.set(interfaceI))
			{
				interfaces_[interfaceI].updateInterfaceMatrix
				(
					psi,
					result,
					*this,
					interfaceCoeffs[interfaceI],
					Pstream::defaultComms(),
					switchToLhs
				);
			}
		}
	}
	else if (Pstream::defaultComms() == Pstream::nonBlocking)
	{
		// Block until all sends/receives have been finished
		IPstream::waitRequests();
		OPstream::waitRequests();

		forAll(interfaces_, interfaceI)
		{
			if (interfaces_.set(interfaceI))
			{
				interfaces_[interfaceI].updateInterfaceMatrix
				(
					psi,
					result,
					*this,
					interfaceCoeffs[interfaceI],
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

			if (interfaces_.set(interfaceI))
			{
				if (patchSchedule[i].init)
				{
					interfaces_[interfaceI].initInterfaceMatrixUpdate
					(
						psi,
						result,
						*this,
						interfaceCoeffs[interfaceI],
						Pstream::scheduled,
						switchToLhs
					);
				}
				else
				{
					interfaces_[interfaceI].updateInterfaceMatrix
					(
						psi,
						result,
						*this,
						interfaceCoeffs[interfaceI],
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
				interfaceI < interfaces_.size();
				interfaceI++
				)
		{
			if (interfaces_.set(interfaceI))
			{
				interfaces_[interfaceI].updateInterfaceMatrix
				(
					psi,
					result,
					*this,
					interfaceCoeffs[interfaceI],
					Pstream::blocking,
					switchToLhs
				);
			}
		}
	}
	else
	{
		FatalErrorIn("BlockLduMatrix<Type>::updateInterfaces")
			<< "Unsuported communications type "
			<< Pstream::commsTypeNames[Pstream::defaultCommsType()]
			<< exit(FatalError);
	}
}


// ************************************************************************* //