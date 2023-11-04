#include <iostream>

#include "Objects/Int/Server_IntObj.hxx"
#include "Objects/Real/Server_RealObj.hxx"
#include "Objects/Point/Server_PntObj.hxx"
#include "Objects/Dir/Server_DirObj.hxx"
#include "Objects/Vec/Server_VecObj.hxx"
#include "Objects/Axis/Server_AxisObj.hxx"
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

const std::string tnbLib::Server_PntObj::commandName = "make_pnt";
namespace tnbLib
{
	class make_pnt_RunTime
	{

		static void Run();

	public:

		make_pnt_RunTime()
		{
			Run();
		}
	};

}
void tnbLib::make_pnt_RunTime::Run()
{
	Server::Commands.insert({ Server_PntObj::commandName, Server::objects::point });
}
static const tnbLib::make_pnt_RunTime make_pnt_RunTime_obj;

const std::string tnbLib::Server_AxisObj::commandName = "make_axis";
namespace tnbLib
{
	class make_axis_RunTime
	{

		static void Run();

	public:

		make_axis_RunTime()
		{
			Run();
		}
	};

}
void tnbLib::make_axis_RunTime::Run()
{
	Server::Commands.insert({ Server_AxisObj::commandName, Server::objects::axis });
}
static const tnbLib::make_axis_RunTime make_axis_RunTime_obj;

const std::string tnbLib::Server_DirObj::commandName = "make_dir";
namespace tnbLib
{
	class make_dir_RunTime
	{

		static void Run();

	public:

		make_dir_RunTime()
		{
			Run();
		}
	};

}
void tnbLib::make_dir_RunTime::Run()
{
	Server::Commands.insert({ Server_DirObj::commandName, Server::objects::dir });
}
static const tnbLib::make_dir_RunTime make_dir_RunTime_obj;

const std::string tnbLib::Server_VecObj::commandName = "make_vec";
namespace tnbLib
{
	class make_vec_RunTime
	{

		static void Run();

	public:

		make_vec_RunTime()
		{
			Run();
		}
	};

}
void tnbLib::make_vec_RunTime::Run()
{
	Server::Commands.insert({ Server_VecObj::commandName, Server::objects::vector });
}
static const tnbLib::make_dir_RunTime make_vec_RunTime_obj;