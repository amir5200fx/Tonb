#include <profilingStack.hxx>
#include <profilingInfo.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::profilingStack::profilingStack()
	: LIFOStack<profilingInfo*>()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::profilingStack::~profilingStack()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::profilingInfo &tnbLib::profilingStack::top() const
{
	return *LIFOStack<profilingInfo*>::top();
}

tnbLib::profilingInfo &tnbLib::profilingStack::bottom() const
{
	return *LIFOStack<profilingInfo*>::bottom();
}

bool tnbLib::profilingStack::empty() const
{
	return LIFOStack<profilingInfo*>::empty();
}

void tnbLib::profilingStack::push(profilingInfo &a)
{
	LIFOStack<profilingInfo*>::push(&a);
	top().addedToStack();
}

tnbLib::profilingInfo &tnbLib::profilingStack::pop()
{
	top().removedFromStack();
	return *LIFOStack<profilingInfo*>::pop();
}

void tnbLib::profilingStack::writeStackContents(Ostream &os) const
{
	if (empty()) {
		return;
	}
	const_iterator it = begin();
	scalar oldElapsed = 0;
	do {
		const profilingInfo &info = *(*it);
		scalar elapsed = timers_[info.id()]->elapsedTime();

		info.writeWithOffset(os, true, elapsed, oldElapsed);

		oldElapsed = elapsed;
		++it;
	} while (it != end());
}

void tnbLib::profilingStack::addTimer(const profilingInfo &info, clockTime &timer)
{
	timers_.insert(info.id(), &timer);
}

// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// ************************************************************************* //