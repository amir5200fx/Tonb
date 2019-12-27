#include <dlLibraryTable.hxx>

#include <OSspecific.hxx>
#include <dictionary.hxx>

#include <dlfcn.h>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::dlLibraryTable tnbLib::dlLibraryTable::loadedLibraries;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dlLibraryTable::dlLibraryTable()
	: HashTable<fileName, void*, Hash<void*> >()
{}


tnbLib::dlLibraryTable::readDlLibrary::readDlLibrary
(
	const dictionary& dict,
	const word& libsEntry
)
{
	open(dict, libsEntry);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dlLibraryTable::~dlLibraryTable()
{
	forAllIter(dlLibraryTable, *this, iter)
	{
		dlclose(iter.key());
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::dlLibraryTable::open(const fileName& functionLibName)
{
	if (functionLibName.size())
	{
		void* functionLibPtr =
			dlopen(functionLibName.c_str(), RTLD_LAZY | RTLD_GLOBAL);

#ifdef darwin
		// If failing to load under OS X, let's try some obvious variations
		// before giving up completely
		fileName osxFileName(functionLibName);

		if (!functionLibPtr && functionLibName.ext() == "so")
		{
			osxFileName = functionLibName.lessExt() + ".dylib";

			functionLibPtr =
				dlopen(osxFileName.c_str(), RTLD_LAZY | RTLD_GLOBAL);
		}

		// If unsuccessful, which might be the case under Mac OSX 10.11 (El
		// Capitan) with System Integrity Protection (SIP) enabled, let's try
		// building a full path using well-known environment variables. This is
		// the last resort, unless you provide the full pathname yourself.
		if (!functionLibPtr)
		{
			fileName l_LIBBIN_Name =
				getEnv("TONB_LIBBIN") / osxFileName;
			functionLibPtr =
				dlopen(l_LIBBIN_Name.c_str(), RTLD_LAZY | RTLD_GLOBAL);
		}
		if (!functionLibPtr)
		{
			fileName l_SITE_LIBBIN_Name =
				getEnv("TONB_SITE_LIBBIN") / osxFileName;
			functionLibPtr =
				dlopen(l_SITE_LIBBIN_Name.c_str(), RTLD_LAZY | RTLD_GLOBAL);
		}
		if (!functionLibPtr)
		{
			fileName l_USER_LIBBIN_Name =
				getEnv("TONB_USER_LIBBIN") / osxFileName;
			functionLibPtr =
				dlopen(l_USER_LIBBIN_Name.c_str(), RTLD_LAZY | RTLD_GLOBAL);
		}
#elif defined mingw
		if (!functionLibPtr && functionLibName.ext() == "so") {
			fileName lName = functionLibName.lessExt() + ".dll";
			functionLibPtr =
				dlopen(lName.c_str(), RTLD_LAZY | RTLD_GLOBAL);
		}
#endif
		if (!functionLibPtr)
		{
			WarningIn
			(
				"dlLibraryTable::open(const fileName& functionLibName)"
			) << "could not load " << dlerror()
				<< endl;

			return false;
		}
		else
		{
			if (!loadedLibraries.found(functionLibPtr))
			{
				loadedLibraries.insert(functionLibPtr, functionLibName);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}


bool tnbLib::dlLibraryTable::open
(
	const dictionary& dict,
	const word& libsEntry
)
{
	if (dict.found(libsEntry))
	{
		fileNameList libNames(dict.lookup(libsEntry));

		bool allOpened = (libNames.size() > 0);

		forAll(libNames, i)
		{
			allOpened = dlLibraryTable::open(libNames[i]) && allOpened;
		}

		return allOpened;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //