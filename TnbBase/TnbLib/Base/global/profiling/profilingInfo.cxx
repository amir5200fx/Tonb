#include <profilingInfo.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::label tnbLib::profilingInfo::nextId_(0);

tnbLib::label tnbLib::profilingInfo::getID()
{
	nextId_++;
	return nextId_;
}

void tnbLib::profilingInfo::raiseID(label maxVal)
{
	if (maxVal > nextId_) {
		nextId_ = maxVal;
	}
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::profilingInfo::profilingInfo()
	:
	calls_(0),
	totalTime_(0.),
	childTime_(0.),
	id_(getID()),
	parent_(*this),
	description_("application::main"),
	onStack_(false)
{}


tnbLib::profilingInfo::profilingInfo(profilingInfo &parent, const string &descr)
	:
	calls_(0),
	totalTime_(0.),
	childTime_(0.),
	id_(getID()),
	parent_(parent),
	description_(descr),
	onStack_(false)
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::profilingInfo::~profilingInfo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::profilingInfo::update(scalar elapsedTimee)
{
	calls_++;
	totalTime_ += elapsedTimee;
	if (id() != parent().id()) {
		parent_.childTime_ += elapsedTimee;
	}
}

void tnbLib::profilingInfo::writeWithOffset(Ostream &os, bool offset, scalar time, scalar childTimes) const
{
	dictionary tmp;

	tmp.add("id", id());
	if (id() != parent().id()) {
		tmp.add("parentId", parent().id());
	}
	tmp.add("description", description());
	tmp.add("calls", calls() + (offset ? 1 : 0));
	tmp.add("totalTime", totalTime() + time);
	tmp.add("childTime", childTime() + childTimes);
	tmp.add("onStack", onStack());

	os << tmp;
}

// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const profilingInfo& info)
{
	info.writeWithOffset(os);

	return os;
}

// ************************************************************************* //