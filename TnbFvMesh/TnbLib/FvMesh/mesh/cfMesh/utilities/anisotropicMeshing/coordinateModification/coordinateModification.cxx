#include <coordinateModification.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <IOstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(coordinateModification, 0);
	defineRunTimeSelectionTable(coordinateModification, dictionary);

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	coordinateModification::coordinateModification()
		:
		name_()
	{}


	coordinateModification::coordinateModification
	(
		const word& name,
		const dictionary& dict
	)
		:
		name_(name)
	{}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	coordinateModification::~coordinateModification()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	Ostream& operator<<(Ostream& os, const coordinateModification& cm)
	{
		os << cm.name() << nl;
		cm.writeDict(os, true);
		return os;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //