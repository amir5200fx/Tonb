#include <IOobject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

bool tnbLib::IOobject::writeHeader(Ostream& os) const
{
	if (!os.good())
	{
		Info << "IOobject::writeHeader(Ostream&) : "
			<< "no stream open for write" << nl
			<< os.info() << endl;

		return false;
	}

	writeBanner(os, false, true)
		<< "FoamFile\n{\n"
		<< "    version     " << os.version() << ";\n"
		<< "    format      " << os.format() << ";\n"
		<< "    class       " << type() << ";\n";

	if (note().size())
	{
		os << "    note        " << note() << ";\n";
	}

	os << "    location    " << instance() / local() << ";\n"
		<< "    object      " << name() << ";\n"
		<< "}" << nl;

	writeDivider(os) << endl;

	return true;
}


// ************************************************************************* //