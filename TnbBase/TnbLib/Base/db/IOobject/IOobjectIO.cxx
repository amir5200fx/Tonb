#include <IOobject.hxx>

#include <token.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#if defined (__GNUC__)
template<>
#endif
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const InfoProxy<IOobject>& ip)
{
	const IOobject& io = ip.t_;

	os << "IOobject: "
		<< io.type() << token::SPACE
		<< io.name() << token::SPACE
		<< io.path() << endl;

	return os;
}


// ************************************************************************* //