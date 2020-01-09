#include <pointZone.hxx>

#include <pointZoneMesh.hxx>
#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <demandDrivenData.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pointZone, 0);
	defineRunTimeSelectionTable(pointZone, dictionary);
	addToRunTimeSelectionTable(pointZone, pointZone, dictionary);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const tnbLib::Map<tnbLib::label>& tnbLib::pointZone::pointLookupMap() const
{
	if (!pointLookupMapPtr_)
	{
		calcPointLookupMap();
	}

	return *pointLookupMapPtr_;
}


void tnbLib::pointZone::calcPointLookupMap() const
{
	if (debug)
	{
		Info << "void pointZone::calcPointLookupMap() const : "
			<< "Calculating point lookup map"
			<< endl;
	}

	if (pointLookupMapPtr_)
	{
		FatalErrorIn
		(
			"void pointZone::calcPointLookupMap() const"
		) << "point lookup map already calculated"
			<< abort(FatalError);
	}

	const labelList& addr = *this;

	pointLookupMapPtr_ = new Map<label>(2 * addr.size());
	Map<label>& plm = *pointLookupMapPtr_;

	forAll(addr, pointI)
	{
		plm.insert(addr[pointI], pointI);
	}

	if (debug)
	{
		Info << "void pointZone::calcPointLookupMap() const : "
			<< "Finished calculating point lookup map"
			<< endl;
	}
}


void tnbLib::pointZone::clearAddressing()
{
	deleteDemandDrivenData(pointLookupMapPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::pointZone::pointZone
(
	const word& name,
	const labelList& addr,
	const label index,
	const pointZoneMesh& zm
)
	:
	labelList(addr),
	name_(name),
	index_(index),
	zoneMesh_(zm),
	pointLookupMapPtr_(NULL)
{}


tnbLib::pointZone::pointZone
(
	const word& name,
	const Xfer<labelList>& addr,
	const label index,
	const pointZoneMesh& zm
)
	:
	labelList(addr),
	name_(name),
	index_(index),
	zoneMesh_(zm),
	pointLookupMapPtr_(NULL)
{}


// Construct from dictionary
tnbLib::pointZone::pointZone
(
	const word& name,
	const dictionary& dict,
	const label index,
	const pointZoneMesh& zm
)
	:
	labelList(dict.lookup("pointLabels")),
	name_(name),
	index_(index),
	zoneMesh_(zm),
	pointLookupMapPtr_(NULL)
{}


// Construct given the original zone and resetting the
// point list and zone mesh information
tnbLib::pointZone::pointZone
(
	const pointZone& pz,
	const labelList& addr,
	const label index,
	const pointZoneMesh& zm
)
	:
	labelList(addr),
	name_(pz.name()),
	index_(index),
	zoneMesh_(zm),
	pointLookupMapPtr_(NULL)
{}


tnbLib::pointZone::pointZone
(
	const pointZone& pz,
	const Xfer<labelList>& addr,
	const label index,
	const pointZoneMesh& zm
)
	:
	labelList(addr),
	name_(pz.name()),
	index_(index),
	zoneMesh_(zm),
	pointLookupMapPtr_(NULL)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pointZone::~pointZone()
{
	clearAddressing();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::pointZone::whichPoint(const label globalPointID) const
{
	const Map<label>& plm = pointLookupMap();

	Map<label>::const_iterator plmIter = plm.find(globalPointID);

	if (plmIter == plm.end())
	{
		return -1;
	}
	else
	{
		return plmIter();
	}
}


const tnbLib::pointZoneMesh& tnbLib::pointZone::zoneMesh() const
{
	return zoneMesh_;
}


void tnbLib::pointZone::updateMesh()
{
	clearAddressing();
}


bool tnbLib::pointZone::checkDefinition(const bool report) const
{
	const labelList& addr = *this;

	bool boundaryError = false;

	forAll(addr, i)
	{
		if (addr[i] < 0 || addr[i] >= zoneMesh_.mesh().allPoints().size())
		{
			boundaryError = true;

			if (report)
			{
				SeriousErrorIn
				(
					"bool pointZone::checkDefinition("
					"const bool report) const"
				) << "Zone " << name()
					<< " contains invalid point label " << addr[i] << nl
					<< "Valid point labels are 0.."
					<< zoneMesh_.mesh().allPoints().size() - 1 << endl;
			}
		}
	}
	return boundaryError;
}


void tnbLib::pointZone::write(Ostream& os) const
{
	os << nl << name()
		<< nl << static_cast<const labelList&>(*this);
}


void tnbLib::pointZone::writeDict(Ostream& os) const
{
	os << nl << name() << nl << token::BEGIN_BLOCK << incrIndent << nl
		<< indent << "type " << type() << token::END_STATEMENT << nl;

	writeEntry("pointLabels", os);

	os << decrIndent << token::END_BLOCK << endl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::pointZone::operator=(const pointZone& cz)
{
	clearAddressing();
	labelList::operator=(cz);
}


void tnbLib::pointZone::operator=(const labelList& addr)
{
	clearAddressing();
	labelList::operator=(addr);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const pointZone& p)
{
	p.write(os);
	os.check("Ostream& operator<<(Ostream& f, const pointZone& p");
	return os;
}


// ************************************************************************* //