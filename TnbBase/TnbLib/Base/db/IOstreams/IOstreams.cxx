#include <IOstreams.hxx>

#include <OFstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Define the default IOstream versions and precision

	const IOstream::versionNumber IOstream::originalVersion(0.5);
	const IOstream::versionNumber IOstream::currentVersion(2.0);

	tnbLib::debug::infoSwitch
		IOstream::precision_
		(
			"writePrecision",
			6
		);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Global IO streams

	ISstream Sin(cin, "Sin");
	OSstream Sout(cout, "Sout");
	OSstream Serr(cerr, "Serr");
	OFstream Snull("/dev/null");

	prefixOSstream Pout(cout, "Pout");
	prefixOSstream Perr(cerr, "Perr");

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //