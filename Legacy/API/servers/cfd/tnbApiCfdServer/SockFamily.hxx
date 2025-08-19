#pragma once
#ifndef _SockFamily_Header
#define _SockFamily_Header

namespace tnbLib
{

	enum class SockFamily
	{
		inet = 0,
		inet6,
		local,
		route,
		key
	};
}

#endif