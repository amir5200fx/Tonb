#pragma once
#ifndef _SockType_Header
#define _SockType_Header

namespace tnbLib
{

	enum class SockType
	{
		stream = 0,
		dgram,
		seqpacket,
		raw
	};
}

#endif