#include <basicPsiThermo.hxx>

#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::basicPsiThermo> tnbLib::basicPsiThermo::New
(
	const fvMesh& mesh,
	const objectRegistry& obj
)
{
	word thermoTypeName;

	// Enclose the creation of the thermophysicalProperties to ensure it is
	// deleted before the turbulenceModel is created otherwise the dictionary
	// is entered in the database twice
	{
		IOdictionary thermoDict
		(
			IOobject
			(
				"thermophysicalProperties",
				mesh.time().constant(),
				obj,
				IOobject::MUST_READ,
				IOobject::NO_WRITE
			)
		);

		thermoDict.lookup("thermoType") >> thermoTypeName;
	}

	Info << "Selecting thermodynamics package " << thermoTypeName << endl;

	fvMeshConstructorTable::iterator cstrIter =
		fvMeshConstructorTablePtr_->find(thermoTypeName);

	if (cstrIter == fvMeshConstructorTablePtr_->end())
	{
		FatalErrorIn("basicPsiThermo::New(const fvMesh&, const objectRegistry&)")
			<< "Unknown basicPsiThermo type " << thermoTypeName << nl << nl
			<< "Valid basicPsiThermo types are:" << nl
			<< fvMeshConstructorTablePtr_->sortedToc() << nl
			<< exit(FatalError);
	}

	return autoPtr<basicPsiThermo>(cstrIter()(mesh, obj));
}


// ************************************************************************* //