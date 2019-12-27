#include <profilingPool.hxx>

#include <token.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::profilingPool* tnbLib::profilingPool::thePool_(NULL);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::profilingPool::profilingPool(
	const IOobject &ob,
	const Time &owner
)
	:
	regIOobject(ob),
	globalTime_(),
	owner_(owner)
{
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::profilingPool::~profilingPool()
{
	for (mapIterator it = map().begin(); it != map().end(); ++it)
	{
		delete it->second;
	}

	map().erase(allInfo_.begin(), allInfo_.end());
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::profilingPool::initProfiling(
	const IOobject &ob,
	const Time &owner
)
{
	if (!thePool_)
	{
		thePool_ = new profilingPool(ob, owner);
		profilingInfo *master = new profilingInfo();
		thePool_->map().insert(make_pair(master->description(), master));
		thePool_->stack().push(*master);
		profilingPool::rememberTimer(*master, thePool_->globalTime_);
	}
}

void tnbLib::profilingPool::stopProfiling(
	const Time &owner
)
{
	if (thePool_ && (&owner) == &(thePool_->owner()))
	{
		delete thePool_;
		thePool_ = NULL;
	}
}

tnbLib::profilingInfo &tnbLib::profilingPool::getInfo(const string& name)
{
	if (!thePool_)
	{
		FatalErrorIn("profilingPool::addInfo(const string& name)")
			<< "Singleton not initialized\n" << endl
			<< abort(FatalError);
	}

	profilingStack& stack = thePool_->stack();
	mapType& map = thePool_->map();

	profilingInfo* found = NULL;

	for
		(
			mapIterator it = map.lower_bound(name);
			it != map.upper_bound(name);
			++it
			)
	{
		if (it->second->parent().id() == stack.top().id())
		{
			found = it->second;
			break;
		}
	}

	if (!found)
	{
		found = new profilingInfo(stack.top(), name);

		map.insert(make_pair(name, found));
	}

	stack.push(*found);
	return *found;
}


void tnbLib::profilingPool::rememberTimer
(
	const profilingInfo& info,
	clockTime& timer
)
{
	if (!thePool_)
	{
		FatalErrorIn
		(
			"profilingPool::rememberTimer(const profilingInfo tnbLib&info, "
			"clockTime& timer)"
		) << "Singleton not initialized\n" << endl
			<< abort(FatalError);
	}

	thePool_->stack().addTimer(info, timer);
}


void tnbLib::profilingPool::remove(const profilingInfo &info)
{
	if (!thePool_)
	{
		FatalErrorIn("profilingPool::addInfo(const string& name)")
			<< "Singleton not initialized\n" << endl
			<< abort(FatalError);
	}

	profilingStack& stack = thePool_->stack();

	if (info.id() != stack.top().id())
	{
		FatalErrorIn("profilingPool::update(const string &name)")
			<< "The id " << info.id() << " of the updated info "
			<< info.description()
			<< " is no the same as the one on top of the stack: "
			<< stack.top().id() << " (" << stack.top().description()
			<< ")\n" << endl
			<< abort(FatalError);
	}

	stack.pop();
}


bool tnbLib::profilingPool::writeData(Ostream& os) const
{
	os << "profilingInfo" << nl << indent
		<< token::BEGIN_LIST << incrIndent << nl;

	stack().writeStackContents(os);

	for (mapConstIterator it = map().begin(); it != map().end(); ++it)
	{
		if (!it->second->onStack())
		{
			os << *(it->second);
		}
	}

	os << decrIndent << indent << token::END_LIST
		<< token::END_STATEMENT << endl;

	return os;
}

// ************************************************************************* //