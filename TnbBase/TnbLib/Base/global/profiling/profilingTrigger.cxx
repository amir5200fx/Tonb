#include <profilingTrigger.hxx>

#include <profilingPool.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::profilingTrigger::profilingTrigger(const string &name)
	: clock_()
	, info_(profilingPool::getInfo(name))
	, running_(true)
{
	profilingPool::rememberTimer(info(), clock());
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::profilingTrigger::~profilingTrigger()
{
	stop();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::profilingTrigger::stop()
{
	if (running_) {
		scalar elapsed = clock_.elapsedTime();
		info_.update(elapsed);
		profilingPool::remove(info_);
		running_ = false;
	}
}



// ************************************************************************* //