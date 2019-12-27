#include <IOobject.hxx>

#include <IFstream.hxx>
#include <objectRegistry.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::IOobject, 0);

// * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * * //

// Return components following the IOobject requirements
//
// behaviour
//    input               IOobject(instance, local, name)
//    -----               ------
//    "foo"               ("", "", "foo")
//    "foo/bar"           ("foo", "", "bar")
//    "/XXX"              ERROR - no absolute path
//    "foo/bar/"          ERROR - no name
//    "foo/xxx/bar"       ("foo", "xxx", "bar")
//    "foo/xxx/yyy/bar"   ("foo", "xxx/yyy", "bar")
bool tnbLib::IOobject::IOobject::fileNameComponents
(
	const fileName& path,
	fileName& instance,
	fileName& local,
	word& name
)
{
	instance.clear();
	local.clear();
	name.clear();

	// called with directory
	if (isDir(path))
	{
		WarningIn("IOobject::fileNameComponents(const fileName&, ...)")
			<< " called with directory: " << path << "\n";
		return false;
	}

	string::size_type first = path.find('/');

	if (first == 0)
	{
		// called with absolute path
		WarningIn("IOobject::fileNameComponents(const fileName&, ...)")
			<< "called with absolute path: " << path << "\n";
		return false;
	}

	if (first == string::npos)
	{
		// no '/' found - no instance or local

		// check afterwards
		name.string::operator=(path);
	}
	else
	{
		instance = path.substr(0, first);

		string::size_type last = path.rfind('/');
		if (last > first)
		{
			// with local
			local = path.substr(first + 1, last - first - 1);
		}

		// check afterwards
		name.string::operator=(path.substr(last + 1));
	}


	// check for valid (and stripped) name, regardless of the debug level
	if (name.empty() || string::stripInvalid<word>(name))
	{
		WarningIn("IOobject::fileNameComponents(const fileName&, ...)")
			<< "has invalid word for name: \"" << name
			<< "\"\nwhile processing path: " << path << "\n";
		return false;
	}

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IOobject::IOobject
(
	const word& name,
	const Time& time,
	readOption ro,
	writeOption wo
)
	:
	name_(name),
	headerClassName_(typeName),
	note_(),
	instance_(""),
	local_(),
	db_(time),
	rOpt_(ro),
	wOpt_(wo),
	registerObject_(false),
	objState_(GOOD)
{
	if (objectRegistry::debug)
	{
		Info << "Constructing IOobject called " << name_
			<< " of type " << headerClassName_
			<< endl;
	}
}


tnbLib::IOobject::IOobject
(
	const word& name,
	const fileName& instance,
	const objectRegistry& registry,
	readOption ro,
	writeOption wo,
	bool registerObject
)
	:
	name_(registry.mangleFileName(name)),
	headerClassName_(typeName),
	note_(),
	instance_(instance),
	local_(),
	db_(registry),
	rOpt_(ro),
	wOpt_(wo),
	registerObject_(registerObject),
	objState_(GOOD)
{
	if (objectRegistry::debug)
	{
		Info << "Constructing IOobject called " << name_
			<< " of type " << headerClassName_
			<< endl;
	}
}


tnbLib::IOobject::IOobject
(
	const word& name,
	const fileName& instance,
	const fileName& local,
	const objectRegistry& registry,
	readOption ro,
	writeOption wo,
	bool registerObject
)
	:
	name_(registry.mangleFileName(name)),
	headerClassName_(typeName),
	note_(),
	instance_(instance),
	local_(local),
	db_(registry),
	rOpt_(ro),
	wOpt_(wo),
	registerObject_(registerObject),
	objState_(GOOD)
{
	if (objectRegistry::debug)
	{
		Info << "Constructing IOobject called " << name_
			<< " of type " << headerClassName_
			<< endl;
	}
}


tnbLib::IOobject::IOobject
(
	const fileName& path,
	const objectRegistry& registry,
	readOption ro,
	writeOption wo,
	bool registerObject
)
	:
	name_(),
	headerClassName_(typeName),
	note_(),
	instance_(),
	local_(),
	db_(registry),
	rOpt_(ro),
	wOpt_(wo),
	registerObject_(registerObject),
	objState_(GOOD)
{
	if (!fileNameComponents(path, instance_, local_, name_))
	{
		FatalErrorIn
		(
			"IOobject::IOobject" "(const fileName&, const objectRegistry&, ...)"
		)
			<< " invalid path specification\n"
			<< exit(FatalError);
	}

	if (objectRegistry::debug)
	{
		Info << "Constructing IOobject called " << name_
			<< " of type " << headerClassName_
			<< endl;
	}
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::IOobject::~IOobject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::objectRegistry& tnbLib::IOobject::db() const
{
	return db_;
}


const tnbLib::Time& tnbLib::IOobject::time() const
{
	return db_.time();
}


const tnbLib::fileName& tnbLib::IOobject::caseName() const
{
	return time().caseName();
}


const tnbLib::fileName& tnbLib::IOobject::rootPath() const
{
	return time().rootPath();
}


tnbLib::fileName tnbLib::IOobject::path() const
{
	return rootPath() / caseName() / instance() / db_.dbDir() / local();
}


tnbLib::fileName tnbLib::IOobject::path
(
	const word& instance,
	const fileName& local
) const
{
	return rootPath() / caseName() / instance / db_.dbDir() / local;
}


tnbLib::fileName tnbLib::IOobject::filePath() const
{
	fileName path = this->path();
	fileName objectPath = path / name();

	if (isFile(objectPath))
	{
		return objectPath;
	}
	else
	{
		if
			(
				time().processorCase()
				&& (
					instance() == time().system()
					|| instance() == time().constant()
					)
				)
		{
			fileName parentObjectPath =
				rootPath() / caseName()
				/ ".." / instance() / db_.dbDir() / local() / name();

			if (isFile(parentObjectPath))
			{
				return parentObjectPath;
			}
		}

		if (!isDir(path))
		{
			word newInstancePath = time().findInstancePath(instant(instance()));

			if (newInstancePath.size())
			{
				fileName fName
				(
					rootPath() / caseName()
					/ newInstancePath / db_.dbDir() / local() / name()
				);

				if (isFile(fName))
				{
					return fName;
				}
			}
		}
	}

	return fileName::null;
}


tnbLib::Istream* tnbLib::IOobject::objectStream()
{
	fileName fName = filePath();

	if (fName.size())
	{
		IFstream* isPtr = new IFstream(fName);

		if (isPtr->good())
		{
			return isPtr;
		}
		else
		{
			delete isPtr;
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}


bool tnbLib::IOobject::headerOk()
{
	bool ok = true;

	Istream* isPtr = objectStream();

	// If the stream has failed return
	if (!isPtr)
	{
		if (objectRegistry::debug)
		{
			Info
				<< "IOobject::headerOk() : "
				<< "file " << objectPath() << " could not be opened"
				<< endl;
		}

		ok = false;
	}
	else
	{
		// Try reading header
		if (!readHeader(*isPtr))
		{
			if (objectRegistry::debug)
			{
				IOWarningIn("IOobject::headerOk()", (*isPtr))
					<< "failed to read header of file " << objectPath()
					<< endl;
			}

			ok = false;
		}
	}

	delete isPtr;

	return ok;
}


void tnbLib::IOobject::setBad(const string& s)
{
	if (objState_ != GOOD)
	{
		FatalErrorIn("IOobject::setBad(const string&)")
			<< "recurrent failure for object " << s
			<< exit(FatalError);
	}

	if (error::level)
	{
		Info << "IOobject::setBad(const string&) : "
			<< "broken object " << s << info() << endl;
	}

	objState_ = BAD;
}


void tnbLib::IOobject::operator=(const IOobject& io)
{
	name_ = io.name_;
	headerClassName_ = io.headerClassName_;
	note_ = io.note_;
	instance_ = io.instance_;
	local_ = io.local_;
	rOpt_ = io.rOpt_;
	wOpt_ = io.wOpt_;
	objState_ = io.objState_;
}


// ************************************************************************* //