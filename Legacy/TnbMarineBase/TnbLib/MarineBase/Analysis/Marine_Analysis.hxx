#pragma once
#ifndef _Marine_Analysis_Header
#define _Marine_Analysis_Header

#include <Marine_Entity.hxx>
#include <Global_Done.hxx>

namespace tnbLib
{

	class Marine_Analysis
		: public Marine_Entity
		, public Global_Done
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		Marine_Analysis(_Types&&... _Args)
			: Marine_Entity(_Args...)
		{}

	public:


	};
}

#endif // !_Marine_Analysis_Header
