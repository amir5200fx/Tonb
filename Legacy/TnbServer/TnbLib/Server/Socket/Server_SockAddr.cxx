#include <Server_SockAddr.hxx>

const std::string tnbLib::Server_SockAddr::THIS_PC = "127.0.0.1";
const int tnbLib::Server_SockAddr::DEFAULT_PORT = 55'555;

tnbLib::Server_SockAddr::~Server_SockAddr()
{
	if (theAddress_)
	{
		freeaddrinfo(theAddress_);
	}
}
