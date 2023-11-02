#include <iostream>

#include "Objects/Int/Server_IntObj.hxx"
#include "Objects/Real/Server_RealObj.hxx"
#include "Objects/Exit/Server_ExitObj.hxx"

#include "Server.hxx"

std::map<std::string, tnbLib::Server::objects> tnbLib::Server::Commands;

const std::string tnbLib::Server_IntObj::commandName = "make_real";

namespace tnbLib
{
	class make_int_RunTime
	{

		static void Run();

	public:

		make_int_RunTime()
		{
			Run();
		}
	};

}

void tnbLib::make_int_RunTime::Run()
{
	Server::Commands.insert({ Server_IntObj::commandName, Server::objects::real });
}

static const tnbLib::make_int_RunTime make_int_RunTime_obj;

const std::string tnbLib::Server_RealObj::commandName = "make_real";

namespace tnbLib
{
	class make_real_RunTime
	{

		static void Run();

	public:

		make_real_RunTime()
		{
			Run();
		}
	};

}

void tnbLib::make_real_RunTime::Run()
{
	Server::Commands.insert({ Server_RealObj::commandName, Server::objects::real });
}

static const tnbLib::make_real_RunTime make_real_RunTime_obj;

const std::string tnbLib::Server_ExitObj::commandName = "EXIT";

namespace tnbLib
{
	class make_exit_RunTime
	{

		static void Run();

	public:

		make_exit_RunTime()
		{
			Run();
		}
	};

}

void tnbLib::make_exit_RunTime::Run()
{
	Server::Commands.insert({ Server_ExitObj::commandName, Server::objects::exit });
}

static const tnbLib::make_exit_RunTime make_exit_RunTime_obj;