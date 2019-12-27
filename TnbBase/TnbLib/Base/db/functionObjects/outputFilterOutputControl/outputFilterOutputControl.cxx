#include <outputFilterOutputControl.hxx>

#include <tnbTime.hxx>

// * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * * //

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::outputFilterOutputControl::outputControls,
	2
>::names[] =
{
	"timeStep",
	"outputTime"
};

const tnbLib::NamedEnum<tnbLib::outputFilterOutputControl::outputControls, 2>
tnbLib::outputFilterOutputControl::outputControlNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::outputFilterOutputControl::outputFilterOutputControl
(
	const Time& t,
	const dictionary& dict
)
	: time_(t)
	, outputControl_(ocTimeStep)
	, outputInterval_(0)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::outputFilterOutputControl::~outputFilterOutputControl()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::outputFilterOutputControl::read(const dictionary& dict)
{
	outputControl_ = outputControlNames_.read(dict.lookup("outputControl"));

	switch (outputControl_)
	{
	case ocTimeStep:
	{
		dict.lookup("outputInterval") >> outputInterval_;
	}
	default:
	{
		// do nothing
	}
	}
}


bool tnbLib::outputFilterOutputControl::output() const
{
	switch (outputControl_)
	{
	case ocTimeStep:
	{
		return
			(
			(outputInterval_ <= 1)
				|| !(time_.timeIndex() % outputInterval_)
				);
		break;
	}
	case ocOutputTime:
	{
		return time_.outputTime();
		break;
	}
	default:
	{
		FatalErrorIn("bool tnbLib::outputFilterOutputControl::output()")
			<< "Unknown output control: "
			<< outputControlNames_[outputControl_] << nl
			<< abort(FatalError);
	}
	}

	return false;
}


// ************************************************************************* //