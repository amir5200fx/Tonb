#include <objectRefinement.hxx>

#include <IOstream.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(objectRefinement, 0);
	defineRunTimeSelectionTable(objectRefinement, dictionary);

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	objectRefinement::objectRefinement()
		:
		name_(),
		cellSize_(-1.0),
		additionalRefLevel_(0),
		refThickness_(0.0)
	{}

	objectRefinement::objectRefinement
	(
		const word& name,
		const dictionary& dict
	)
		:
		name_(name),
		cellSize_(-1.0),
		additionalRefLevel_(0),
		refThickness_(0.0)
	{
		if (dict.found("cellSize"))
		{
			cellSize_ = readScalar(dict.lookup("cellSize"));

			if (cellSize_ < 0.0)
			{
				FatalErrorIn
				(
					"objectRefinement::objectRefinement"
					"(const word&, const dictionary&)"
				) << "Specified cell size for object " << name_
					<< " is negative" << exit(FatalError);
			}
		}
		else if (dict.found("additionalRefinementLevels"))
		{
			additionalRefLevel_ =
				readLabel(dict.lookup("additionalRefinementLevels"));

			if (additionalRefLevel_ < 0)
			{
				FatalErrorIn
				(
					"objectRefinement::objectRefinement"
					"(const word&, const dictionary&)"
				) << "Specified additionalRefinementLevel for object " << name_
					<< " is negative" << exit(FatalError);
			}
		}

		if (dict.found("refinementThickness"))
			refThickness_ = readScalar(dict.lookup("refinementThickness"));
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	objectRefinement::~objectRefinement()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	Ostream& operator<<(Ostream& os, const objectRefinement& obr)
	{
		os << obr.name() << nl;
		obr.writeDict(os, true);
		return os;
	}

	void objectRefinement::calculateAdditionalRefLevels(const scalar globalCellSize)
	{
		if (cellSize_ < 0.0 || additionalRefLevel_ != 0)
			return;

		scalar s = globalCellSize;

		label nMarked;
		do
		{
			nMarked = 0;

			if (cellSize_ <= s * (1. + SMALL))
			{
				++nMarked;
				++additionalRefLevel_;
			}

			s /= 2.0;

		} while (nMarked != 0);

	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //