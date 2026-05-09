#pragma once
#ifndef _SockProtocol_Header
#define _SockProtocol_Header

namespace tnbLib
{

	enum class SockProtocol
	{
		tcp = 0,
		udp,
		sctp
	};
}

#endif