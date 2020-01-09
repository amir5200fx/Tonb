#include <cellZone.hxx>

#include <cellZoneMesh.hxx>
#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <IOstream.hxx>
#include <demandDrivenData.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cellZone, 0);

	defineRunTimeSelectionTable(cellZone, dictionary);
	addToRunTimeSelectionTable(cellZone, cellZone, dictionary);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const tnbLib::Map<tnbLib::label>& tnbLib::cellZone::cellLookupMap() const
{
	if (!cellLookupMapPtr_)
	{
		calcCellLookupMap();
	}

	return *cellLookupMapPtr_;
}


void tnbLib::cellZone::calcCellLookupMap() const
{
	if (debug)
	{
		Info << "void cellZone::calcCellLookupMap() const : "
			<< "Calculating cell lookup map"
			<< endl;
	}

	if (cellLookupMapPtr_)
	{
		FatalErrorIn
		(
			"void cellZone::calcCellLookupMap() const"
		) << "cell lookup map already calculated"
			<< abort(FatalError);
	}

	const labelList& addr = *this;

	cellLookupMapPtr_ = new Map<label>(2 * addr.size());
	Map<label>& clm = *cellLookupMapPtr_;

	forAll(addr, cellI)
	{
		clm.insert(addr[cellI], cellI);
	}

	if (debug)
	{
		Info << "void cellZone::calcCellLookupMap() const : "
			<< "Finished calculating cell lookup map"
			<< endl;
	}
}


void tnbLib::cellZone::clearAddressing()
{
	deleteDemandDrivenData(cellLookupMapPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::cellZone::cellZone
(
	const word& name,
	const labelList& addr,
	const label index,
	const cellZoneMesh& zm
)
	:
	labelList(addr),
	name_(name),
	index_(index),
	zoneMesh_(zm),
	cellLookupMapPtr_(NULL)
{}


tnbLib::cellZone::cellZone
(
	const word& name,
	const Xfer<labelList>& addr,
	const label index,
	const cellZoneMesh& zm
)
	:
	labelList(addr),
	name_(name),
	index_(index),
	zoneMesh_(zm),
	cellLookupMapPtr_(NULL)
{}


// Construct from dictionary
tnbLib::cellZone::cellZone
(
	const word& name,
	const dictionary& dict,
	const label index,
	const cellZoneMesh& zm
)
	:
	labelList(dict.lookup("cellLabels")),
	name_(name),
	index_(index),
	zoneMesh_(zm),
	cellLookupMapPtr_(NULL)
{}


// Construct given the original zone and resetting the
//  cell list and zone mesh information
tnbLib::cellZone::cellZone
(
	const cellZone& cz,
	const labelList& addr,
	const label index,
	const cellZoneMesh& zm
)
	:
	labelList(addr),
	name_(cz.name()),
	index_(index),
	zoneMesh_(zm),
	cellLookupMapPtr_(NULL)
{}

tnbLib::cellZone::cellZone
(
	const cellZone& cz,
	const Xfer<labelList>& addr,
	const label index,
	const cellZoneMesh& zm
)
	:
	labelList(addr),
	name_(cz.name()),
	index_(index),
	zoneMesh_(zm),
	cellLookupMapPtr_(NULL)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cellZone::~cellZone()
{
	clearAddressing();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::cellZone::whichCell(const label globalCellID) const
{
	const Map<label>& clm = cellLookupMap();

	Map<label>::const_iterator clmIter = clm.find(globalCellID);

	if (clmIter == clm.end())
	{
		return -1;
	}
	else
	{
		return clmIter();
	}
}


const tnbLib::cellZoneMesh& tnbLib::cellZone::zoneMesh() const
{
	return zoneMesh_;
}


bool tnbLib::cellZone::checkDefinition(const bool report) const
{
	const labelList& addr = *this;

	bool boundaryError = false;

	forAll(addr, i)
	{
		if (addr[i] < 0 || addr[i] >= zoneMesh_.mesh().nCells())
		{
			boundaryError = true;

			if (report)
			{
				SeriousErrorIn
				(
					"bool cellZone::checkDefinition("
					"const bool report) const"
				) << "Zone " << name()
					<< " contains invalid cell label " << addr[i] << nl
					<< "Valid cell labels are 0.."
					<< zoneMesh_.mesh().nCells() - 1 << endl;
			}
		}
	}
	return boundaryError;
}


void tnbLib::cellZone::updateMesh()
{
	clearAddressing();
}


void tnbLib::cellZone::write(Ostream& os) const
{
	os << nl << name()
		<< nl << static_cast<const labelList&>(*this);
}


void tnbLib::cellZone::writeDict(Ostream& os) const
{
	os << nl << name() << nl << token::BEGIN_BLOCK << incrIndent << nl
		<< indent << "type " << type() << token::END_STATEMENT << nl;

	writeEntry("cellLabels", os);

	os << decrIndent << token::END_BLOCK << endl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::cellZone::operator=(const cellZone& cz)
{
	clearAddressing();
	labelList::operator=(cz);
}


void tnbLib::cellZone::operator=(const labelList& addr)
{
	clearAddressing();
	labelList::operator=(addr);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const cellZone& p)
{
	p.write(os);
	os.check("Ostream& operator<<(Ostream& f, const cellZone& p");
	return os;
}


// ************************************************************************* //