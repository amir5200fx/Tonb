#include <tolerances.hxx>

#include <IOobject.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	tolerances::tolerances(const Time& t, const fileName& dictName)
		:
		IOdictionary
		(
			IOobject
			(
				dictName,
				t.system(),
				t,
				IOobject::MUST_READ,
				IOobject::NO_WRITE
			)
		),
		relaxationFactors_(ITstream("relaxationFactors", tokenList())()),
		solverTolerances_(ITstream("solverTolerances", tokenList())()),
		solverRelativeTolerances_
		(
			ITstream("solverRelativeTolerances", tokenList())()
		)
	{
		read();
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	bool tolerances::read()
	{
		if (regIOobject::read())
		{
			const word toleranceSetName(lookup("toleranceSet"));
			const dictionary& toleranceSet(subDict(toleranceSetName));

			if (toleranceSet.found("relaxationFactors"))
			{
				relaxationFactors_ = toleranceSet.subDict("relaxationFactors");
			}

			if (toleranceSet.found("solverTolerances"))
			{
				solverTolerances_ = toleranceSet.subDict("solverTolerances");
			}

			if (toleranceSet.found("solverRelativeTolerances"))
			{
				solverRelativeTolerances_ =
					toleranceSet.subDict("solverRelativeTolerances");
			}

			return true;
		}
		else
		{
			return false;
		}
	}


	bool tolerances::relax(const word& name) const
	{
		return relaxationFactors_.found(name);
	}

	scalar tolerances::relaxationFactor(const word& name) const
	{
		return readScalar(relaxationFactors_.lookup(name));
	}

	scalar tolerances::solverTolerance(const word& name) const
	{
		return readScalar(solverTolerances_.lookup(name));
	}

	bool tolerances::solverRelativeTolerances() const
	{
		return solverRelativeTolerances_.size();
	}

	scalar tolerances::solverRelativeTolerance(const word& name) const
	{
		return readScalar(solverRelativeTolerances_.lookup(name));
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //