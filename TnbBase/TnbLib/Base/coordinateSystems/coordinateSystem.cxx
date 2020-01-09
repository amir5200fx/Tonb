#include <coordinateSystem.hxx>

#include <coordinateSystem.hxx>
#include <coordinateSystems.hxx>
#include <boundBox.hxx>
#include <IOstreams.hxx>
#include <dictionary.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(coordinateSystem, 0);
	defineRunTimeSelectionTable(coordinateSystem, dictionary);
	defineRunTimeSelectionTable(coordinateSystem, origRotation);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::coordinateSystem::coordinateSystem()
	:
	name_(type()),
	note_(),
	origin_(point::zero),
	R_(),
	Rtr_(sphericalTensor::I)
{}


tnbLib::coordinateSystem::coordinateSystem
(
	const word& name,
	const coordinateSystem& cs
)
	:
	name_(name),
	note_(),
	origin_(cs.origin_),
	R_(cs.R_),
	Rtr_(cs.Rtr_)
{}


tnbLib::coordinateSystem::coordinateSystem
(
	const word& name,
	const point& origin,
	const coordinateRotation& cr
)
	:
	name_(name),
	note_(),
	origin_(origin),
	R_(cr),
	Rtr_(R_.T())
{}


tnbLib::coordinateSystem::coordinateSystem
(
	const word& name,
	const point& origin,
	const vector& axis,
	const vector& dirn
)
	:
	name_(name),
	note_(),
	origin_(origin),
	R_(axis, dirn),
	Rtr_(R_.T())
{}


tnbLib::coordinateSystem::coordinateSystem
(
	const word& name,
	const dictionary& dict
)
	:
	name_(name),
	note_(),
	origin_(point::zero),
	R_(),
	Rtr_(sphericalTensor::I)
{
	operator=(dict);
}


tnbLib::coordinateSystem::coordinateSystem
(
	const dictionary& dict
)
	:
	name_(type()),
	note_(),
	origin_(point::zero),
	R_(),
	Rtr_(sphericalTensor::I)
{
	operator=(dict);
}


tnbLib::coordinateSystem::coordinateSystem
(
	const dictionary& dict,
	const objectRegistry& obr
)
	:
	name_(type()),
	note_(),
	origin_(point::zero),
	R_(),
	Rtr_(sphericalTensor::I)
{
	const entry* entryPtr = dict.lookupEntryPtr(typeName_(), false, false);

	// a simple entry is a lookup into global coordinateSystems
	if (entryPtr && !entryPtr->isDict())
	{
		word csName;
		entryPtr->stream() >> csName;

		const coordinateSystems& csLst = coordinateSystems::New(obr);

		label csId = csLst.find(csName);
		if (debug)
		{
			Info << "coordinateSystem::coordinateSystem"
				"(const dictionary&, const objectRegistry&):"
				<< nl << "using global coordinate system: "
				<< csName << "=" << csId << endl;
		}

		if (csId < 0)
		{
			FatalErrorIn
			(
				"coordinateSystem::coordinateSystem"
				"(const dictionary&, const objectRegistry&)"
			) << "could not find coordinate system: " << csName << nl
				<< "available coordinate systems: " << csLst.toc() << nl << nl
				<< exit(FatalError);
		}

		// copy coordinateSystem, but assign the name as the typeName
		// to avoid strange things in writeDict()
		operator=(csLst[csId]);
		name_ = typeName_();
	}
	else
	{
		operator=(dict);
	}
}


tnbLib::coordinateSystem::coordinateSystem(Istream& is)
	:
	name_(is),
	note_(),
	origin_(point::zero),
	R_(),
	Rtr_(sphericalTensor::I)
{
	dictionary dict(is);
	operator=(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::coordinateSystem::~coordinateSystem()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::coordinateSystem::spanInfo tnbLib::coordinateSystem::spanLimited() const
{
	return spanInfo(Pair<bool>(false, false));
}


tnbLib::boundBox tnbLib::coordinateSystem::spanBounds() const
{
	return boundBox::greatBox;
}


tnbLib::dictionary tnbLib::coordinateSystem::dict(bool ignoreType) const
{
	dictionary dict;

	dict.add("name", name_);

	// only write type for derived types
	if (!ignoreType && type() != typeName_())
	{
		dict.add("type", type());
	}

	// The note entry is optional
	if (note_.size())
	{
		dict.add("note", note_);
	}

	dict.add("origin", origin_);
	dict.add("e1", e1());
	dict.add("e3", e3());

	return dict;
}


tnbLib::vector tnbLib::coordinateSystem::localToGlobal
(
	const vector& local,
	bool translate
) const
{
	if (translate)
	{
		return (R_ & local) + origin_;
	}
	else
	{
		return (R_ & local);
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::coordinateSystem::localToGlobal
(
	const vectorField& local,
	bool translate
) const
{
	if (translate)
	{
		return (R_ & local) + origin_;
	}
	else
	{
		return (R_ & local);
	}
}


tnbLib::vector tnbLib::coordinateSystem::globalToLocal
(
	const vector& global,
	bool translate
) const
{
	if (translate)
	{
		return (Rtr_ & (global - origin_));
	}
	else
	{
		return (Rtr_ & global);
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::coordinateSystem::globalToLocal
(
	const vectorField& global,
	bool translate
) const
{
	if (translate)
	{
		return (Rtr_ & (global - origin_));
	}
	else
	{
		return (Rtr_ & global);
	}
}


void tnbLib::coordinateSystem::write(Ostream& os) const
{
	os << type()
		<< " origin: " << origin()
		<< " e1: " << e1() << " e3: " << e3();
}


void tnbLib::coordinateSystem::writeDict(Ostream& os, bool subDict) const
{
	if (subDict)
	{
		os << indent << nl
			<< indent << token::BEGIN_BLOCK << incrIndent << nl;
	}

	// only write type for derived types
	if (type() != typeName_())
	{
		os.writeKeyword("type") << type() << token::END_STATEMENT << nl;
	}

	// The note entry is optional
	if (note_.size())
	{
		os.writeKeyword("note") << note_ << token::END_STATEMENT << nl;
	}

	os.writeKeyword("name") << name_ << token::END_STATEMENT << nl;
	os.writeKeyword("origin") << origin_ << token::END_STATEMENT << nl;
	os.writeKeyword("e1") << e1() << token::END_STATEMENT << nl;
	os.writeKeyword("e3") << e3() << token::END_STATEMENT << nl;

	if (subDict)
	{
		os << decrIndent << indent << token::END_BLOCK << endl;
	}
}

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::coordinateSystem::operator=(const dictionary& rhs)
{
	if (debug)
	{
		Pout << "coordinateSystem::operator=(const dictionary&) : "
			<< "assign from " << rhs << endl;
	}

	// allow as embedded sub-dictionary "coordinateSystem"
	const dictionary& dict =
		(
			rhs.found(typeName_())
			? rhs.subDict(typeName_())
			: rhs
			);

	// unspecified origin is (0 0 0)
	origin_ = point::zero;
	dict.readIfPresent("origin", origin_);

	// The note entry is optional
	note_.clear();
	rhs.readIfPresent("note", note_);

	// specify via coordinateRotation sub-dictionary
	if (dict.found("coordinateRotation"))
	{
		R_ = coordinateRotation::New(dict.subDict("coordinateRotation"))();
	}
	else
	{
		// let coordinateRotation constructor extract the axes specification
		R_ = coordinateRotation(dict);
	}

	Rtr_ = R_.T();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

bool tnbLib::operator!=(const coordinateSystem& a, const coordinateSystem& b)
{
	return (a.origin() != b.origin() || a.R() != b.R() || a.type() != b.type());
}


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const coordinateSystem& cs)
{
	cs.write(os);
	os.check("Ostream& operator<<(Ostream&, const coordinateSystem&");
	return os;
}


// ************************************************************************* //