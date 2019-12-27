#include <IPstream.hxx>
#include <OPstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::IPstream::print(Ostream& os) const
{
	os << "Reading from processor " << fromProcNo_
		<< " to processor " << myProcNo() << tnbLib::endl;
}


void tnbLib::OPstream::print(Ostream& os) const
{
	os << "Writing from processor " << toProcNo_
		<< " to processor " << myProcNo() << tnbLib::endl;
}


// ************************************************************************* //