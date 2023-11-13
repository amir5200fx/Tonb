#include "SockAddr.hxx"

const std::string tnbLib::SockAddr::THIS_PC = "127.0.0.1";
const int tnbLib::SockAddr::DEFAULT_PORT = 55'555;

tnbLib::SockAddr::SockAddr()
{
	// empty body
}

tnbLib::SockAddr::~SockAddr()
{
	freeaddrinfo(theAddress_);
}
