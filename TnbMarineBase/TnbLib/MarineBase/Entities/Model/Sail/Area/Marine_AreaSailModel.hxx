#pragma once
#ifndef _Marine_AreaSailModel_Header
#define _Marine_AreaSailModel_Header

#include <Pnt2d.hxx>
#include <Marine_SailModel.hxx>

namespace tnbLib
{

	class Marine_AreaSailModel
		: public Marine_SailModel
	{

		/*Private Data*/


	protected:

		template<class... _Types>
		Marine_AreaSailModel(_Types&&... _Args)
			: Marine_SailModel(_Args...)
		{}

	public:

		
	};
}

#endif // !_Marine_AreaSailModel_Header
