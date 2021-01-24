#pragma once
#ifndef _SectPx_InterfaceType_Header
#define _SectPx_InterfaceType_Header

namespace tnbLib
{

	enum class SectPx_InterfaceType
	{
		empty,
		joint
	};

	namespace sectPxLib
	{
		typedef SectPx_InterfaceType interfaceType;
	}
}

#endif // !_SectPx_InterfaceType_Header
