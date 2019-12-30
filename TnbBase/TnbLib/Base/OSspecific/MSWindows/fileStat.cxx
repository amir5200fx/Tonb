#include <fileStat.hxx>

#include <IOstreams.hxx>
#include <timer.hxx>

#undef major
#undef minor
#undef makedev

# define major(dev) ((int)(((dev) >> 8) & 0xff))
# define minor(dev) ((int)((dev) & 0xff))
# define makedev(major, minor) ((((unsigned int) (major)) << 8) \
    | ((unsigned int) (minor)))

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct null
	fileStat::fileStat()
		:
		isValid_(false)
	{}


	// Construct from components
	fileStat::fileStat(const fileName& fName, const unsigned int maxTime)
	{
		// Work on volatile
		volatile bool locIsValid = false;

		timer myTimer(maxTime);

		if (!timedOut(myTimer))
		{
			if (::stat(fName.c_str(), &status_) != 0)
			{
				locIsValid = false;
			}
			else
			{
				locIsValid = true;
			}
		}

		// Copy into (non-volatile, possible register based) member var
		isValid_ = locIsValid;
	}


	// Construct from Istream.
	fileStat::fileStat(Istream& is)
	{
		is >> *this;
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// compare two fileStates for same device
	bool fileStat::sameDevice(const fileStat& stat2) const
	{
		return
			isValid_
			&& (
				major(status_.st_dev) == major(stat2.status().st_dev)
				&& minor(status_.st_dev) == minor(stat2.status().st_dev)
				);
	}

	// compare two fileStates for same Inode
	bool fileStat::sameINode(const fileStat& stat2) const
	{
		return isValid_ && (status_.st_ino == stat2.status().st_ino);
	}

	// compare state against inode
	bool fileStat::sameINode(const label iNode) const
	{
		return isValid_ && (status_.st_ino == ino_t(iNode));
	}


	// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

	// Input in list syntax
	Istream& operator>>(Istream& is, fileStat& fStat)
	{
		// Read beginning of machine info list
		is.readBegin("fileStat");

		label
			devMaj, devMin,
			ino, mode, uid, gid,
			rdevMaj, rdevMin,
			size, atime, mtime, ctime;

		is >> fStat.isValid_
			>> devMaj
			>> devMin
			>> ino
			>> mode
			>> uid
			>> gid
			>> rdevMaj
			>> rdevMin
			>> size
			>> atime
			>> mtime
			>> ctime;

		dev_t st_dev = makedev(devMaj, devMin);
		fStat.status_.st_dev = st_dev;

		fStat.status_.st_ino = ino;
		fStat.status_.st_mode = mode;
		fStat.status_.st_uid = uid;
		fStat.status_.st_gid = gid;

		dev_t st_rdev = makedev(rdevMaj, rdevMin);
		fStat.status_.st_rdev = st_rdev;

		fStat.status_.st_size = size;
		fStat.status_.st_atime = atime;
		fStat.status_.st_mtime = mtime;
		fStat.status_.st_ctime = ctime;

		// Read end of machine info list
		is.readEnd("fileStat");

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, fileStat&)");

		return is;
	}


	// Output in list syntax
	Ostream& operator<<(Ostream& os, const fileStat& fStat)
	{
		// Set precision so 32bit unsigned int can be printed
		// int oldPrecision = os.precision();
		int oldPrecision = 0;
		os.precision(10);

		os << token::BEGIN_LIST << fStat.isValid_
			<< token::SPACE << label(major(fStat.status_.st_dev))
			<< token::SPACE << label(minor(fStat.status_.st_dev))
			<< token::SPACE << label(fStat.status_.st_ino)
			<< token::SPACE << label(fStat.status_.st_mode)
			<< token::SPACE << label(fStat.status_.st_uid)
			<< token::SPACE << label(fStat.status_.st_gid)
			<< token::SPACE << label(major(fStat.status_.st_rdev))
			<< token::SPACE << label(minor(fStat.status_.st_rdev))
			<< token::SPACE << label(fStat.status_.st_size)
			<< token::SPACE << label(fStat.status_.st_atime)
			<< token::SPACE << label(fStat.status_.st_mtime)
			<< token::SPACE << label(fStat.status_.st_ctime)
			<< token::END_LIST;

		os.precision(oldPrecision);
		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //