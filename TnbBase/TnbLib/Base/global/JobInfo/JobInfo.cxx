#include <JobInfo.hxx>

#include <OSspecific.hxx>
#include <clock.hxx>
#include <OFstream.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::debug::infoSwitch
tnbLib::JobInfo::writeJobInfo
(
	"writeJobInfo",
	0
);

tnbLib::JobInfo tnbLib::jobInfo;
bool tnbLib::JobInfo::constructed = false; // added by amir


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
tnbLib::JobInfo::JobInfo()
	:
	runningJobPath_(),
	finishedJobPath_(),
	cpuTime_()
{
	name() = "JobInfo";

	if (writeJobInfo && Pstream::master())
	{
		string baseDir = getEnv("tnbLib_JOB_DIR");
		string jobFile = hostName() + '.' + tnbLib::name(pid());

		fileName runningDir(baseDir / "runningJobs");
		fileName finishedDir(baseDir / "finishedJobs");

		runningJobPath_ = runningDir / jobFile;
		finishedJobPath_ = finishedDir / jobFile;

		if (baseDir.empty())
		{
			FatalErrorIn("JobInfo::JobInfo()")
				<< "Cannot get JobInfo directory $tnbLib_JOB_DIR"
				<< tnbLib::exit(FatalError);
		}

		if (!isDir(runningDir) && !mkDir(runningDir))
		{
			FatalErrorIn("JobInfo::JobInfo()")
				<< "Cannot make JobInfo directory " << runningDir
				<< tnbLib::exit(FatalError);
		}

		if (!isDir(finishedDir) && !mkDir(finishedDir))
		{
			FatalErrorIn("JobInfo::JobInfo()")
				<< "Cannot make JobInfo directory " << finishedDir
				<< tnbLib::exit(FatalError);
		}
	}

	constructed = true;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::JobInfo::~JobInfo()
{
	if (writeJobInfo && constructed && Pstream::master())
	{
		mv(runningJobPath_, finishedJobPath_);
	}

	constructed = false;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::JobInfo::write(Ostream& os) const
{
	if (writeJobInfo && Pstream::master())
	{
		if (os.good())
		{
			dictionary::write(os, false);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}


void tnbLib::JobInfo::write() const
{
	if (writeJobInfo && Pstream::master())
	{
		if (!write(OFstream(runningJobPath_)()))
		{
			FatalErrorIn("JobInfo::write() const")
				<< "Failed to write to JobInfo file "
				<< runningJobPath_
				<< tnbLib::exit(FatalError);
		}
	}
}


void tnbLib::JobInfo::end(const word& terminationType)
{
	if (writeJobInfo && constructed && Pstream::master())
	{
		add("cpuTime", cpuTime_.elapsedCpuTime());
		add("endDate", clock::date());
		add("endTime", clock::clockTime());

		if (!found("termination"))
		{
			add("termination", terminationType);
		}

		rm(runningJobPath_);
		write(OFstream(finishedJobPath_)());
	}

	constructed = false;
}


void tnbLib::JobInfo::end()
{
	end("normal");
}


void tnbLib::JobInfo::exit()
{
	end("exit");
}


void tnbLib::JobInfo::abort()
{
	end("abort");
}


void tnbLib::JobInfo::signalEnd() const
{
	if (writeJobInfo && constructed && Pstream::master())
	{
		mv(runningJobPath_, finishedJobPath_);
	}

	constructed = false;
}


// ************************************************************************* //