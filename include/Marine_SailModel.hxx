#pragma once
#ifndef _Marine_SailModel_Header
#define _Marine_SailModel_Header

#include <Marine_Model.hxx>

namespace tnbLib
{

	class Marine_SailModel
		: public Marine_Model
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		Marine_SailModel(_Types&&... _Args)
			: Marine_Model(_Args...)
		{}

	public:


	};
}

#endif // !_Marine_SailModel_Header
