#pragma once
#ifndef _SectPx_FieldCloud_Header
#define _SectPx_FieldCloud_Header

#include <SectPx_Cloud.hxx>
#include <SectPx_ParsFwd.hxx>

namespace tnbLib
{

	class SectPx_FieldCloud
		: public SectPx_Cloud
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_FieldCloud(_Types&&... _Args)
			: SectPx_Cloud(_Args...)
		{}

	public:

		
		
	};
}

#endif // !_SectPx_FieldCloud_Header
